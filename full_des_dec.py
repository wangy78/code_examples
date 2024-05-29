# -*- coding: utf-8 -*-
"""
Created on Fri Jun 17 15:00:10 2022

@author: wangy78
"""
import random
og_key = "1100011110"
key_history = []

s0 = [[1,0,3,2],
      [3,2,1,0],
      [0,2,1,3],
      [3,1,3,2] 
      ]
s1 = [[0,1,2,3],
      [2,0,1,3],
      [3,0,1,0],
      [2,1,0,3] 
      ]

fin_res = [] 
def permute(order, og_text):
    list_text = list(og_text)
    result = []
    
    for i in order:
        result.append(list_text[i-1])

    return "".join(result)
def shift_left(og_str):
    return og_str[1:len(og_str)]+og_str[0:1] 

def create_rd_key(key, rd_num):
    key = permute([3,5,2,7,4,10,1,9,8,6], key)
    key_1 = key[:int(len(key)/2)]
    key_2 = key[int(len(key)/2):]
    
    for i in range(0,rd_num):
    
        key_1 = shift_left(key_1)
        key_2 = shift_left(key_2)
        
        
    rd_key = permute([6,3,7,4,8,5,10,9], key_1+key_2);
    
   
    key_history.append(rd_key)
def x_or(a,b):
    x = []
    for i in range(0, len(a)):
        if(a[i] == b[i]):
            x.append("0")
        else:
            x.append("1")
            
    return "".join(x)

def expand(x_1, tt_size):
    while(len(x_1)<tt_size):
        x_1 = "0"+x_1
        
    return x_1
def binaryToDecimal(bi_str):
    return int(bi_str, 2) 
     
def dec_to_bi(temp):
    if(temp == 3):
        return "11"
    elif(temp==2):
        return "10"
    elif(temp == 1):
        return "01"
    else:
        return "00"
    
# look up the valin sbox
def find_table_val(curr_1, s_box):
    row1 = curr_1[0]+curr_1[3]
    col1 = curr_1[1]+curr_1[2]
    value = s_box[binaryToDecimal(row1)][binaryToDecimal(col1)]
    return dec_to_bi(value)
    
def print_table(ddt, ddtl):
    for i in range(0, 16):
        print(ddt[i])
        
    for i in range(0, 16):
        for j in range(0, 4):
            print(i," => ",j, ddtl[i*4+j])
            
            
def intersection(lst1, lst2):
    lst3 = [value for value in lst1 if value in lst2]
    return lst3

# find the candidate keys and if first time, they are the final candidates, if not, take intersection
def q3hack(key_0_0, s_table, ddtl0, key_can_final, x_1, x_2):
    key_can = []
    curr = x_or(x_1, key_0_0)
    y_1 = find_table_val(curr,s_table)
    
    curr = x_or(x_2, key_0_0)
    
    y_2 = find_table_val(curr, s_table)
    delta_x = binaryToDecimal(x_or(x_1,x_2))
    delta_y = binaryToDecimal(x_or(y_1,y_2))

    
    for i in ddtl0[delta_x*4+delta_y]:
        x_prime = expand(bin(i).replace("0b", ""),4)
        poss_key = x_or(x_prime, x_1)
        key_can.append(poss_key)
        
    if(len(key_can_final) == 0):
        key_can_final = key_can.copy()
    else:
        key_can_final = intersection(key_can_final, key_can)
    
        

    print(key_can_final)
    
    if(len(key_can_final) == 1):
        fin_res.append(key_can_final)
    return key_can_final
    
    
  # find the candidate keys and if first time, they are the final candidates, if not, take intersection  
def hacking(key_0_0, s_table, ddtl0, key_can_final):
    
    print(key_0_0)
    key_can = []

    x_1 = bin(random.randint(0, 15)).replace("0b", "")
    x_1 = expand(x_1, 4)
    
        
    
    x_2 = bin(random.randint(0, 15)).replace("0b", "")
    x_2 = expand(x_2, 4)
    
    curr = x_or(x_1, key_0_0)
    y_1 = find_table_val(curr,s_table)
    
    curr = x_or(x_2, key_0_0)
    
    y_2 = find_table_val(curr, s_table)
    delta_x = binaryToDecimal(x_or(x_1,x_2))
    delta_y = binaryToDecimal(x_or(y_1,y_2))
    
    
    for i in ddtl0[delta_x*4+delta_y]:
        x_prime = expand(bin(i).replace("0b", ""),4)
        poss_key = x_or(x_prime, x_1)
        key_can.append(poss_key)
        
    if(len(key_can_final) == 0):
        key_can_final = key_can.copy()
    else:
        key_can_final = intersection(key_can_final, key_can)

    print("cadidates=> ", key_can_final)
    return key_can_final
def f_fun(curr, key):
    
    
    curr = permute([4,1,2,3,2,3,4,1], curr)

    curr = x_or(curr, key)


    curr_1 = curr[:int(len(curr)/2)]
    curr_2 = curr[int(len(curr)/2):]
    

    row1 = curr_1[0]+curr_1[3]
    row2 = curr_2[0]+curr_2[3]
    
    col1 = curr_1[1]+curr_1[2]
    col2 = curr_2[1]+curr_2[2]
    
  
    value = s0[binaryToDecimal(row1)][binaryToDecimal(col1)]
    
    left_2 = dec_to_bi(value)
    
    value2 = s1[binaryToDecimal(row2)][binaryToDecimal(col2)]
    right_2 =  dec_to_bi(value2)

    return permute([2,4,3,1], left_2+right_2)

def des_round(curr_1, curr_2, key):
    
    temp = curr_2[:]
    
    curr_2 = f_fun(curr_2, key)
    
    curr_2= x_or(curr_1, curr_2)
    

    
    return curr_2, temp

def decrypt_des(cryptotext):
    

    
    current_text = permute([2,6,3,1,4,8,5,7], cryptotext)
    
    
    curr_1 = current_text[:int(len(current_text)/2)]
    curr_2 = current_text[int(len(current_text)/2):]
    curr_2, curr_1 = des_round(curr_1, curr_2, key_history[1])
    

    curr_1, curr_2 = des_round(curr_1, curr_2, key_history[0])    
    

    curr = curr_1+ curr_2
    print(curr, "left")

    curr = permute([4,1,3,5,7,2,8,6], curr)
    print("plain text = "+ curr)

    return curr


def encrypt_des(plaintext):
    
    current_text = permute([2,6,3,1,4,8,5,7], plaintext)
    
    
    curr_1 = current_text[:int(len(current_text)/2)]
    curr_2 = current_text[int(len(current_text)/2):]
    
    curr_2, curr_1 = des_round(curr_1, curr_2, key_history[0])
    
    curr_1, curr_2 = des_round(curr_1, curr_2, key_history[1])    
    
    curr = curr_1+ curr_2
    
    curr = permute([4,1,3,5,7,2,8,6], curr)
    print("encrypted text = " + curr)
    
    return curr
    
        
create_rd_key(og_key, 1)# create key with 1 left shifts
create_rd_key(og_key, 3)# create key with3 left shifts
print("keys=",key_history)


# part 1 build tables
ddt0 = []
ddt1 = []
ddtl0 = []
ddtl1 = []

for i in range(0, 16):
    ddt0.append([0,0,0,0])
    ddt1.append([0,0,0,0])
    for j in range(0, 4):
        ddtl0.append(set())
        ddtl1.append(set())
        
        
    

for i in range(0, 16):
    for j in range(0, 16):
        
        x_1 = bin(i).replace("0b", "")
        x_1 = expand(x_1, 4)
        x_2 = bin(j).replace("0b", "")
        x_2 = expand(x_2, 4)
        
        delta_x = binaryToDecimal(x_or(x_1, x_2))

        y_1 = find_table_val(x_1, s0)
        y_2 = find_table_val(x_2, s0)
        delta_y = binaryToDecimal(x_or(y_1, y_2))
        
        
        ddt0[delta_x][delta_y] +=1
        ddtl0[delta_x*4+delta_y].add(binaryToDecimal(x_1))
        ddtl0[delta_x*4+delta_y].add(binaryToDecimal(x_2))
        
        
        y_1_s1 = find_table_val(x_1, s1)
        y_2_s1 = find_table_val(x_2, s1)
        
        delta_y_s1 = binaryToDecimal(x_or(y_1_s1, y_2_s1))
        ddt1[delta_x][delta_y_s1] +=1
        
        ddtl1[delta_x*4+delta_y_s1].add(binaryToDecimal(x_1))
        ddtl1[delta_x*4+delta_y_s1].add(binaryToDecimal(x_2))
        
        
        
print("t0")
print_table(ddt0, ddtl0)    

print("t1")
print_table(ddt1, ddtl1)      


print(key_history)
#part 2, hack the s box
key_can_final = []
# retrieve all 4 parts
while(len(key_can_final)!=1 ):
    key_can_final = hacking(key_history[0][:int(len(key_history[0])/2)], s0, ddtl0, key_can_final)


key_can_final = []

while(len(key_can_final)!=1 ):
    key_can_final = hacking(key_history[0][int(len(key_history[0])/2):],  s1, ddtl1, key_can_final)


key_can_final = []

while(len(key_can_final)!=1 ):
    key_can_final = hacking(key_history[1][:int(len(key_history[1])/2)],  s0, ddtl0, key_can_final)


key_can_final = []

while(len(key_can_final)!=1 ):
    key_can_final = hacking(key_history[1][int(len(key_history[1])/2):],  s1, ddtl1, key_can_final)






test_str = "("
print("The original string is : " + str(test_str))
res = ' '.join(format(ord(i), '08b') for i in test_str)


res = str(res)
bi_list = res.split(" ")
print("The string after binary conversion : " , bi_list)



print("keys=",key_history)




for i in bi_list:
    crypto_text = encrypt_des(i)
    og_text = decrypt_des(crypto_text)
    print ("The ASCII value of given character is", chr (int(og_text, 2) ))
    
# part 3 is below attact from start
key_can_final = []

print("rd 1 key 1st part below")
while(len(key_can_final)!=1 ):
#if(1 == 1):
    plain_text = bin(random.randint(0, 255)).replace("0b", "")
    plain_text = expand(plain_text, 8)
    
    plain_text2 = bin(random.randint(0, 255)).replace("0b", "")
    plain_text2 = expand(plain_text2, 8)
    
    current_text = permute([2,6,3,1,4,8,5,7], plain_text)
    current_text2 = permute([2,6,3,1,4,8,5,7], plain_text2)
    
    
    curr_1 = current_text[:int(len(current_text)/2)]
    curr_2 = current_text[int(len(current_text)/2):]
     
    
    
    curr_1_1 = current_text[:int(len(current_text2)/2)]
    curr_2_2 = current_text2[int(len(current_text2)/2):]
    
    curr_2 = permute([4,1,2,3,2,3,4,1], curr_2)
    curr_2 = x_or(curr_2, key_history[0])
    
    curr_2_2 = permute([4,1,2,3,2,3,4,1], curr_2_2)
    curr_2_2 = x_or(curr_2_2, key_history[0])
    
    
    c = curr_2[:int(len(curr_2)/2)]
    c_2 = curr_2_2[:int(len(curr_2_2)/2)]
    
  
    
    
    

    
    key_can_final = q3hack(key_history[0][:int(len(key_history[0])/2)],  s0, ddtl0, key_can_final, c,c_2)



    
    
print("rd 1 key 2nd part below")
key_can_final = []



while(len(key_can_final)!=1 ):
#if(1 == 1):
    plain_text = bin(random.randint(0, 255)).replace("0b", "")
    plain_text = expand(plain_text, 8)
    
    plain_text2 = bin(random.randint(0, 255)).replace("0b", "")
    plain_text2 = expand(plain_text2, 8)
    
    current_text = permute([2,6,3,1,4,8,5,7], plain_text)
    current_text2 = permute([2,6,3,1,4,8,5,7], plain_text2)
    
    
    curr_1 = current_text[:int(len(current_text)/2)]
    curr_2 = current_text[int(len(current_text)/2):]
     
    
    
    curr_1_1 = current_text[:int(len(current_text2)/2)]
    curr_2_2 = current_text2[int(len(current_text2)/2):]
    
    curr_2 = permute([4,1,2,3,2,3,4,1], curr_2)
    curr_2 = x_or(curr_2, key_history[0])
    
    curr_2_2 = permute([4,1,2,3,2,3,4,1], curr_2_2)
    curr_2_2 = x_or(curr_2_2, key_history[0])
    
    
    c = curr_2[:int(len(curr_2)/2)]
    c_2 = curr_2_2[:int(len(curr_2_2)/2)]
    
  
    
    key_can_final = q3hack(key_history[0][int(len(key_history[0])/2):],  s1, ddtl1, key_can_final, c,c_2)



print("rd2 key part 1 below")

key_can_final = []  
while(len(key_can_final)!=1 ):
#if(1 == 1):
    plain_text = bin(random.randint(0, 255)).replace("0b", "")
    plain_text = expand(plain_text, 8)
    
    plain_text2 = bin(random.randint(0, 255)).replace("0b", "")
    plain_text2 = expand(plain_text2, 8)
    
    current_text = permute([2,6,3,1,4,8,5,7], plain_text)
    current_text2 = permute([2,6,3,1,4,8,5,7], plain_text2)
    
    
    curr_1 = current_text[:int(len(current_text)/2)]
    curr_2 = current_text[int(len(current_text)/2):]
     
    
    
    curr_1_1 = current_text[:int(len(current_text2)/2)]
    curr_2_2 = current_text2[int(len(current_text2)/2):]
    
    curr_2, curr_1 = des_round(curr_1, curr_2, key_history[0])
    curr_2_2, curr_1_1 = des_round(curr_1_1, curr_2_2, key_history[0])
    
    curr_2 = permute([4,1,2,3,2,3,4,1], curr_2)
    curr_2 = x_or(curr_2, key_history[1])
    
    curr_2_2 = permute([4,1,2,3,2,3,4,1], curr_2_2)
    curr_2_2 = x_or(curr_2_2, key_history[1])
    
    
    c = curr_2[:int(len(curr_2)/2)]
    c_2 = curr_2_2[:int(len(curr_2_2)/2)]
    
  
    
    key_can_final = q3hack(key_history[1][:int(len(key_history[1])/2)],  s0, ddtl0, key_can_final, c,c_2)


print("rd2 key part 2 below")
key_can_final = []  
while(len(key_can_final)!=1 ):
#if(1 == 1):
    plain_text = bin(random.randint(0, 255)).replace("0b", "")
    plain_text = expand(plain_text, 8)
    
    plain_text2 = bin(random.randint(0, 255)).replace("0b", "")
    plain_text2 = expand(plain_text2, 8)
    
    current_text = permute([2,6,3,1,4,8,5,7], plain_text)
    current_text2 = permute([2,6,3,1,4,8,5,7], plain_text2)
    
    
    curr_1 = current_text[:int(len(current_text)/2)]
    curr_2 = current_text[int(len(current_text)/2):]
     
    
    
    curr_1_1 = current_text[:int(len(current_text2)/2)]
    curr_2_2 = current_text2[int(len(current_text2)/2):]
    
    curr_2, curr_1 = des_round(curr_1, curr_2, key_history[0])
    curr_2_2, curr_1_1 = des_round(curr_1_1, curr_2_2, key_history[0])
    
    curr_2 = permute([4,1,2,3,2,3,4,1], curr_2)
    curr_2 = x_or(curr_2, key_history[1])
    
    curr_2_2 = permute([4,1,2,3,2,3,4,1], curr_2_2)
    curr_2_2 = x_or(curr_2_2, key_history[1])
    
    
    c = curr_2[int(len(curr_2)/2):]
    c_2 = curr_2_2[:int(len(curr_2_2)/2):]
    
  
    
    key_can_final = q3hack(key_history[1][int(len(key_history[1])/2):],  s1, ddtl1, key_can_final, c,c_2)
print("")
print("   k1p1      k1 p2      k2p1      k2p2  ")
print(fin_res)
