import networkx as nx
import numpy as np
import scipy as sp
import scipy.cluster.vq as vq
import matplotlib.pyplot as plt
import math
import random
import operator
import time
from mpi4py import MPI

################################################################################
################################################################################
##################  Part 1: Distributed Graph Processing   #####################
################################################################################
################################################################################
# Read in the dataset and select a root
G = nx.read_edgelist("p2p-Gnutella31.data", create_using=nx.MultiGraph())
#G = nx.read_weighted_edgelist("congress.data", comments="%")

# Root is selected simply as the first vertex in G.nodes()
root = list(G.nodes())[0]
print("Root: ", root)

################################################################################
# Determine our parallel environment details. We will need the total number of 
# ranks (nprocs) and the local rank ID (procid). We will use COMM_WORLD for our
# communications, which simply means all ranks will communicate with all other
# ranks.

comm = MPI.COMM_WORLD
nprocs = comm.Get_size()
procid = comm.Get_rank()

################################################################################
# Determine our locally owned vertices for this rank. Recall, that each rank
# will be running the exact same program. The computational differences arise
# from its procid. Here, we break up G.nodes() into a disjoint nprocs-way
# partitioning. Each rank will get int(n / nprocs) vertices, except for the last
# rank, which will get any 'remainder' vertices. Note: nprocs very likely won't
# evenly divide G.order()
n = G.order()
n_local = 0
n_ghost = 0
m_local = 0

# Determine a 'start' and 'end' index in G.nodes() for this rank
procs_per_rank = int(n / nprocs)
start_index = procid * procs_per_rank
end_index = 0
if procid == nprocs - 1:
  end_index = n
else:
  end_index = start_index + procs_per_rank


# Create the local_verts set using the above indices
vert_list = list(G.nodes())
local_verts = set(vert_list[start_index:end_index])
n_local = len(local_verts)

################################################################################
# Time to construct the local graph structure. This will include all locally-
# owned vertices as well as all of their incident edges. We can use the 
# local_verts set to do this. Simply loop through these local vertices, then
# add these vertices as well as all of their incident edges to a new graph.
# Note that some endpoints of edges are not going to be local. These are called
# 'ghost vertices'. As we will communicate these vertices to the owning rank
# when they are discovered, we will also want to keep track of their ranks. We 
# should also have some way to check whether a vertex we see is 'local' or not.

def get_rank(G, u, vertices, nprocs):
  n = G.order()
  i = vertices.index(u)
  procs_per_rank = int(n / nprocs)
  return min(int(i / procs_per_rank), nprocs-1)

G_local = nx.Graph()
ghost_verts = set()
ranks = {}

# Do the business here
for v in local_verts:
    # Add the vertex to the local graph
    G_local.add_node(v)
    
    # Assign the rank or process ID to the vertex
    ranks[v] = procid
    
    # Iterate over neighbors of the vertex in the global graph
    for u in G.neighbors(v):
        # Add the edge to the local graph
        G_local.add_edge(v, u)
        
        # Check if the neighbor vertex 'u' is not in the local subset
        if u not in local_verts:
            # Determine the rank of the ghost vertex 'u' if not already assigned
            if u not in ranks:
                ranks[u] = get_rank(G, u, vert_list, nprocs)
            # Add the ghost vertex to the set of ghost vertices
            ghost_verts.add(u)

# Set the final variables for outputting information about our local graph
n_ghost = G_local.order() - n_local
m_local = G_local.size()

################################################################################
# Delete the original graph. No using this in a distributed setting.
# Note that in reality, all of the above preprocessing would also be done in a
# parallel and distributed fashion, since the goal is often to avoid any single
# compute element from having to store the entire O(|V(G)|+|E(G)|) graph data
# structure in main memory.
G = 0

################################################################################
# Output data about the graphs
for i in range(0, nprocs):
  if i == procid:
    print("Rank: ", procid, " / ", nprocs)
    print("n_local:", n_local, "n_ghost:", n_ghost, "m_local:", m_local)
    comm.barrier()


################################################################################
# Here we will be running our BFS. The primary modification from implementations
# we've looked at earlier in the semester is the addition of communication
# functionality. We need to do two things: first, we need to communicate to 
# figure out when our search is done, as not all ranks will be 'busy' on each
# iteration. We can simply take a sum via an MPI allreduce() to get a total sum
# of every rank's queue size. Second, we need to communicate when we discover a
# non-local ghost vertex during our search, and send it to the owning rank. We
# can construct nprocs empty lists that we append such vertices to.
#
# As part of the BFS, we will be tracking levels. To help with synchronization,
# and to avoid redundant work and correctness issues, consider the following
# scheme for the levels[] state information.
# - levels[v] = -2 for all local+ghost vertices for initialization
# - levels[v] = -1 when a vertex is discovered, as we don't want to place it in
#               the queue multiple times
# - levels[v] = current_level when a vertex is finally processed

# We'll keep track of time and maybe observe some 'strong' scaling
elt = time.perf_counter()

# Initialize our levels array
current_level = 0
levels = {v: -2 for v in local_verts.union(ghost_verts)}

# Initialize our local queue - the rank owning the root needs to place it in
# their local queue now
local_queue = []
if root not in levels:
    # If the root node is not found in levels, initialize an empty local queue
    local_queue = []
else:
    # Initialize the level of the root node to 0
    levels[root] = 0
    # Begin BFS with the root node by adding it to the local queue
    local_queue = [root]
# We'll initialize the global queue size to 1 here, but we'll need to actually
# compute it via a communication later on
global_queue_size = 1
while global_queue_size > 0:
  for i in range(0, nprocs):
    if i == procid:
      print("procid: ", procid, "level: ", current_level, "queue size: ", len(local_queue))
      comm.barrier()
    
  # On each iteration, we will want to discover vertices and build a queue for
  # the next iteration to process. We'll use my_sends[ranks[u]] to determine
  # the rank of these ghost vertices.
  next_queue = []
  my_sends = [[] for _ in range(nprocs)]
  
  # Process our local queue. Update levels[] when we discover a new vertex, and
  # place that vertex in my_sends or next_queue as needed.
  for v in local_queue:
    levels[v] = current_level
    undiscovered_neighbors = [u for u in G_local.neighbors(v) if levels[u] == -2]
    for u in undiscovered_neighbors:
        levels[u] = -1
        (next_queue if u in local_verts else my_sends[ranks[u]]).append(u)
  
  # Here we will do the communication. We want all pairs of rank_i <-> rank_j
  # communications to occur, where rank_i and rank_j are each the sender and
  # the receiver in a communication. We will just use pairwise send()-recv() 
  # function calls to accomplish this using the my_sends array. We can use
  # 'extend()' the next_queue array to append lists that we receive from the 
  # other ranks.
  for i in range(nprocs):
    if i != procid:
        comm.send(my_sends[i], dest=i)  # Send data to process i

  comm.barrier()  # Ensure all processes have sent their data
    
  for i in range(nprocs):
        if i != procid:
            incoming_vertices = comm.recv(source=i)  # Receive data from process i
            next_queue.extend([v for v in incoming_vertices if levels[v] == -2])  # Add undiscovered vertices to next_queue
            levels.update({v: -1 for v in incoming_vertices if levels[v] == -2})

  
  # Finally, set the local_queue to be the next_queue for the following 
  # iteration. In addition, do a MPI.SUM reduction over all queue size for the
  # next iteration to make sure that some rank is still processing. If none are,
  # then the while() loop should terminate.
  current_level += 1
  next_queue = list(set(next_queue))
  local_queue = next_queue
  
  # Do our communication here to set the global queue
  local_queue_size = len(local_queue)
  comm.Barrier()
  global_queue_size = comm.allreduce(local_queue_size, op=MPI.SUM)

# Output our timing results. Scaling observed?
for i in range(0, nprocs):
  if i == procid:
    print("Rank: ", procid, "Time:", time.perf_counter() - elt)
    comm.barrier()