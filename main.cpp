// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <algorithm>
#include "Ship.h"
// several type defs to keep things neat
// (hint, these are STL lists)
typedef std::list<std::string> inventory_type;
typedef std::list<Ship> customers_type;

typedef std::list<std::list<std::string>> lls_t;


// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name, inventory_type &inventory_out);

// The main algorithm for DVD distribution
void shipped(std::string moviename, inventory_type & inventory, inventory_type & inventory_out){
    
    inventory_type::iterator movie_it = std::find(inventory.begin(), inventory.end(), moviename);
    if (movie_it == inventory.end()){
     // std::cout<< "This shouldnt happen"<< std::endl;
    }
    else{
      // change the inventory to this is deleted.
      inventory_out.push_back(*movie_it);
      *movie_it = "this is deleted";
    }
}
// return newest alg, return the newest movie from customer holding to inventory
void rnalg(std::istream &istr,std::ostream & ostr, inventory_type & customers_loc, inventory_type & inventory, customers_type & customers){
      std::string customer_name = read_customer_name(istr);
// check if the cus name is right
      inventory_type::iterator cus_name_it = std::find(customers_loc.begin(), customers_loc.end(), customer_name);

      if(cus_name_it == customers_loc.end()){
            
            std::cout<<"WARNING: No customer named "<<customer_name <<std::endl;
      }else{// if it is correct, do the rest
      customers_type::iterator cus_typeit = customers.begin();     
// find the location
      while((*cus_typeit).getname() != customer_name){
           cus_typeit++;
        }
// check how many is he/she holding
      if((*cus_typeit).rented_n() == 0){
        std::cout<< "WARNING: "<<customer_name<<" has no DVDs to return!"<< std::endl;
      }
      // get the newest movie he/she has and put it back into inventory
      else{
       std::string temp = (*cus_typeit).getnewest();
       std::cout<< customer_name<< " returns "<< temp<< std::endl;
      inventory.push_back(temp);
// delete it from the cus holding
      (*cus_typeit).return_newest();

      }
    }
}
// print out customer
void ptcus(std::istream &istr,std::ostream & ostr, inventory_type & customers_loc, customers_type & customers){
std::string customer_name = read_customer_name(istr);
// find the location
      inventory_type::iterator cus_name_it;
      cus_name_it = std::find(customers_loc.begin(), customers_loc.end(), customer_name);
      if(cus_name_it == customers_loc.end()){
            
            std::cout<<"WARNING: No customer named "<< customer_name<<std::endl;
          }
      else{

      customers_type::iterator cus_typeit = customers.begin();
              
      while((*cus_typeit).getname() != customer_name){
        cus_typeit++;
      }

      // figure out what to print
          if ((*cus_typeit).rented_n() > 1){

            std::cout<< customer_name<< " has "<< (*cus_typeit).rented_n() <<" movies:"<< std::endl;
            (*cus_typeit).print(ostr);
          }// very basic hard words
          else if ((*cus_typeit).rented_n() == 0){
            std::cout<< customer_name<< " has no movies"<< std::endl;
          }
          else{//more printings, call the class prit function
            std::cout<< customer_name<< " has "<< (*cus_typeit).rented_n() <<" movie:"<< std::endl;
            (*cus_typeit).print(ostr);

          }
          if ((*cus_typeit).get_pref_len()> 0)
             (*cus_typeit).print2(ostr);
    }
  }
// print out the dvd info
void ptdvd(std::istream &istr,std::ostream & ostr,  inventory_type & inventory,  inventory_type & og_inventory){
      std::string dvd_name = read_dvd_name(istr);
      inventory_type::iterator findog;
      findog = std::find(og_inventory.begin(), og_inventory.end(), dvd_name);


      if (findog == og_inventory.end())
        std::cout<<"WARNING: No movie named "<<dvd_name<<" in the inventory"<< std::endl;
      else{
        //find the avaliable and rented out, do the math with the origional set
        int og_num = std::count(og_inventory.begin(), og_inventory.end(), dvd_name);       
        int ava_num = std::count(inventory.begin(), inventory.end(), dvd_name);
        int out_num = og_num -ava_num;

        std::cout<< dvd_name<< ":"<< std::endl;
        if (out_num >1)// very basic hard words, see is it is singular, rezero or is purial
          std::cout<<  "  "<< out_num<< " copies checked out";
        else if (out_num ==1)
          std::cout<<  "  "<< out_num<< " copy checked out" ;
        else// figure out what to print
          std::cout<<  " ";

        if (out_num >0 and ava_num != 0){
          std::cout<<" and";// printing is hard?
        }

        if (ava_num == 0)// figure out what to print
          std::cout<< std::endl;

        else if (ava_num == 1)// just printing, nothing special
          std::cout<<" "<<ava_num<< " copy available"<<std::endl;
        else
          std::cout<< " "<<ava_num<< " copies available"<<std::endl;
    }
}// next, I present the retrun Oldest alg
void r0alg(std::istream &istr,std::ostream & ostr, inventory_type & customers_loc, inventory_type & inventory, customers_type & customers){                      // interesting, you found an easter egg
        std::string customer_name = read_customer_name(istr);
          // find the customer
      inventory_type::iterator cus_name_it = std::find(customers_loc.begin(), customers_loc.end(), customer_name);

      if(cus_name_it == customers_loc.end()){
            
            std::cout<<"WARNING: No customer named "<<customer_name <<std::endl;

          }
      // if found, do the rest
      else{
        customers_type::iterator cus_typeit = customers.begin();
          while((*cus_typeit).getname() != customer_name){
          cus_typeit++;
               }
// check if he/she has anything to return
        if((*cus_typeit).rented_n() == 0){
        std::cout<< "WARNING: "<<customer_name <<" has no DVDs to return!"<< std::endl;
      }
      else{     

       std::string temp = (*cus_typeit).getoldest();
       std::cout<< customer_name<< " returns "<< temp<< std::endl;
      inventory.push_back(temp);
// remove the oldest from cus holding
      (*cus_typeit).return_oldest();
    }
    }

}
void cus_alg(std::istream &istr,std::ostream & ostr, inventory_type & customers_loc, inventory_type & inventory, customers_type & customers, lls_t & cus_pref){
std::string customer_name = read_customer_name(istr);
    // check if name already exist
          inventory_type::iterator cus_name_it;
          cus_name_it = std::find(customers_loc.begin(), customers_loc.end(), customer_name);

          if(cus_name_it != customers_loc.end()){        
            std::cout<<"WARNING: Already have a customer named "<<customer_name <<std::endl;
          }// if the name doesnt exist, add this new cus
          else{
            customers_loc.push_back(customer_name);
            Ship cust_name(customer_name);// default constructer of the class
            customers.push_back(cust_name);// push it back into customers
          }// get how many movies he/she want
          int num_movies;
          istr >> num_movies;
          inventory_type temp_customers;
          if(cus_name_it != customers_loc.end()){
            for (int i = 0; i < num_movies; i++) {//  just to read inputs
                std::string dvd_name = read_dvd_name(istr);
              }
          }else{
            //read the movies append the movie names to the list, 

            for (int i = 0; i < num_movies; i++) {

                  std::string dvd_name = read_dvd_name(istr);
                  
                  // check for duplicate                  
                  inventory_type::iterator custemp_movie_it = std::find(temp_customers.begin(), temp_customers.end(), dvd_name);

                  inventory_type::iterator cus_movie_it = std::find(inventory.begin(), inventory.end(), dvd_name);               
                               
                  if(custemp_movie_it != temp_customers.end()){// we have duplicate, wh cant we ship them the num the request?                  
                    std::cout<<"WARNING: Duplicate movie "<< dvd_name<<" on preference list!"<<std::endl;               

                  }else if(cus_movie_it == inventory.end()){// find if inv has the movie
                  
                    std::cout<<"WARNING: No movie named "<< dvd_name<< " in the inventory" << std::endl;
                    

                    }else{
                        temp_customers.push_back(dvd_name);
                       // push back the movie to his list
                      }

                }
                std::cout<< "new customer: "<< customer_name <<std::endl;
                
                cus_pref.push_back(temp_customers);// push his /her list to a bigger list
                customers_type::iterator cus_typeit = customers.begin();       

                while((*cus_typeit).getname() != customer_name){// find the cus by the name
                  cus_typeit++;
                }

                (*cus_typeit).update (temp_customers); // update his/her preference
                temp_customers.clear();

              }
    }// add preference list
void add_pre_alg(std::istream &istr,std::ostream & ostr, inventory_type & customers_loc, customers_type & customers, lls_t & cus_pref, inventory_type & og_inventory){

      std::string customer_name = read_customer_name(istr);// read inputs

      std::string dvd_name = read_dvd_name(istr);
      inventory_type::iterator cus_name_it;
      cus_name_it = std::find(customers_loc.begin(), customers_loc.end(), customer_name);// try to find the cus

      if(cus_name_it == customers_loc.end()){
            
            std::cout<<"WARNING: No customer named "<<customer_name<<std::endl;
          }

      else{
          // reset iterator
          inventory_type::iterator cus_movie_it = std::find(og_inventory.begin(), og_inventory.end(), dvd_name);
          cus_name_it = customers_loc.begin();
          int counter_name = 0;
          // locate the location of the name
          while(counter_name < int(customers_loc.size())){
            if (*cus_name_it == customer_name)
              break;
            else{
              cus_name_it ++;// update the count
              counter_name++;
            }
          }
          // find the iterator of pref of the name
          lls_t::iterator cus_pref_it = cus_pref.begin();
          for(int i = 0; i < counter_name; i++){
            cus_pref_it ++;
          }
          customers_type::iterator cus_typeit = customers.begin();
// find location again
           while((*cus_typeit).getname() != customer_name){
                cus_typeit++;
              }
          inventory_type temp_cust_pref = (*cus_typeit).get_preferences();
          // get his /her preference
          inventory_type::iterator cus_movie_pref_it = std::find(temp_cust_pref.begin(), temp_cust_pref.end(), dvd_name);
          inventory_type temp_holding = (*cus_typeit).get_holding();
          // get his/ her rented items
          inventory_type::iterator cus_movieh_it = std::find(temp_holding.begin(), temp_holding.end(), dvd_name);

// checking for errors as warnings
          if(cus_movie_it == og_inventory.end()){// we dont have the movie at all
              std::cout<<"WARNING: No movie named "<<dvd_name <<" in the inventory"<<std::endl;
          }
           else if (cus_movie_pref_it != temp_cust_pref.end()){// the cus has the move in preference list
              std::cout<<"WARNING: "<< customer_name <<" already has "<<dvd_name<<" on his/her preference list!"<<std::endl;
          }else if (cus_movieh_it !=temp_holding.end() ){// does the cus already have the movie at home
            std::cout<<"WARNING: "<< customer_name <<" currently has "<<dvd_name<< "!"<<std::endl;
          }
          else{// if the above didnt occor, pushback the dvd to preferencelist             
              (*cus_pref_it).push_back(dvd_name);
// find the customer again
              customers_type::iterator cus_typeit = customers.begin();
              while((*cus_typeit).getname() != customer_name){
                cus_typeit++;
              }
              // add tis to his/her class
              (*cus_typeit).addnew(dvd_name);
    
            }


        }
}
// ==================================================================

//
// A basic algorithm for determining which movies to ship to each customer
//


// ==================================================================

void shipping_algorithm(inventory_type &inventory, std::ostream &ostr, lls_t & cus_pref, inventory_type & inventory_out, customers_type &customers) {

  std::cout<< "Ship DVDs" << std::endl;
  int counter_n = 0;


  // Loop over the customers in priority order
  //
  // Note that we edit the customers list as we go, to add customers
  // to the back of the list if they receive a DVD.  This allows a
  // customer to receive multiple DVDs in one shipment cycle, but only
  // after all other customers have had a chance to receive DVDs.
  //
  customers_type::iterator customer_itr = customers.begin();

  lls_t::iterator cus_pref_it2 = cus_pref.begin();

  for (int i = 0; i < counter_n; i++) cus_pref_it2 ++;

  while (customer_itr != customers.end()) {

    // skip this customer if they already have 3 movies or if their
    // preference list is empty (no outstanding requests)
    if ((*customer_itr).has_max_num_movies() || customer_itr->preference_list_empty()) {
      // move on to the next customer
      customer_itr++;
      counter_n++;
      continue;
    }

    // a helper flag variable
    bool sent_dvd = false;
 
    // loop over the customer's preferences
    const inventory_type &preferences = customer_itr->get_preferences();

    for (inventory_type::const_iterator preferences_itr = preferences.begin(); 
         preferences_itr != preferences.end(); preferences_itr++) {

      // locate this DVD in the inventory
      inventory_type::iterator inventory_itr = std::find(inventory.begin(), inventory.end(), *preferences_itr);
      if (inventory_itr != inventory.end()) { 

        // if the DVD is available, ship it to the customer!


        std::cout<< "  " << customer_itr->getname() << " receives " << *preferences_itr << std::endl;
        shipped(*preferences_itr, inventory, inventory_out);
        customer_itr->receives(*preferences_itr);
        
        // move this customer to the back of the priority queue
        // they will get a chance to receive another DVD, but only
        // after everyone else gets a chance
        customers.push_back(*customer_itr);
        customer_itr = customers.erase(customer_itr);

        cus_pref.push_back(*cus_pref_it2);
        cus_pref_it2 =cus_pref.erase(cus_pref_it2);

        // after setting the flag to true, leave the iteration over preferences
        sent_dvd = true;        
        break;
      }
    }


    // if no DVD was sent to this customer, then we move on to the next customer 
    // (do not change this customer's priority for tomorrow's shipment)
    if (!sent_dvd) {
      customer_itr++;
       counter_n++;
    }
  }

}

// ==================================================================


void usage(const char* program_name) {
  std::cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
  exit(1);
}


int main(int argc, char* argv[]) {

  if (argc < 3 || argc > 5) {
    usage(argv[0]);
  }

  // open input and output file streams
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    usage(argv[0]); 
  }
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cout<< "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
    usage(argv[0]); 
  }

  // optional parameters for extra credit
  bool use_improved_algorithm = false;
  bool print_analysis = false;
  for (int i = 3; i < argc; i++) {
    if (std::string(argv[i]) == "--improved") {
      use_improved_algorithm = true;
    } else if (std::string(argv[i]) == "--analysis") {
      print_analysis = true;
    } else {
      usage(argv[0]);
    }
  }


  // stores information about the DVDs
  inventory_type inventory;

  inventory_type inventory_out;
  // stores list of list of movie preference
  lls_t cus_pref;
  // stores information about the customers
  customers_type customers;
// orgional set of customer stored as a list of string
  inventory_type customers_loc;
// what we have origionally
  inventory_type og_inventory;

  // read in and handle each of the 8 keyword tokens
  std::string token;
  while (istr >> token) {
    if (token == "dvd") {// main , add dvd into inventory, its short, I dont need a function
      std::string dvd_name = read_dvd_name(istr);
      int copies;
      istr >> copies;

      for(int i = 0; i < copies; i++){
          inventory.push_back(dvd_name);// add to both og and the one we updates
          og_inventory.push_back(dvd_name);

      }
      if(copies > 1)
        std::cout<< copies << " copies of "<< dvd_name<< " added"<<std::endl;
      else if (copies == 1)
        std::cout<< copies << " copy of "<< dvd_name<< " added"<<std::endl;


    } else if (token == "customer") {// call this function
      cus_alg(istr, ostr, customers_loc, inventory, customers,cus_pref);          

    } else if (token == "ship") {// call this function

      shipping_algorithm(inventory,  ostr, cus_pref, inventory_out, customers);
      
    } else if (token == "return_oldest") {// call this function
        r0alg(istr, ostr, customers_loc, inventory, customers);

    } else if (token == "return_newest") {// call this function
      rnalg(istr, ostr, customers_loc, inventory, customers);

    } else if (token == "print_customer") {// call this function
      ptcus(istr, ostr, customers_loc,  customers);
      
    } else if (token == "print_dvd") {// call this function
      ptdvd(istr, ostr, inventory, og_inventory);


    } else if (token == "add_preference") {// call this function
      add_pre_alg(istr, ostr, customers_loc,  customers,cus_pref, og_inventory);

    } else {
      std::cout<< "ERROR: Unknown token " << token << std::endl;
      exit(1);
  }
}
  // for (lls_t::iterator testit = cus_pref.begin(); testit != cus_pref.end(); testit++){
  //   std::cout<<  std::endl;
  //   for(customers_type::iterator tt = (*testit).begin(); tt!= (*testit).end() ; tt++  )
  //     std::cout<< *tt<< std::endl;
  // }
          

}


// ==================================================================


// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr) {
  std::string first, last;
  istr >> first >> last;
  return first + " " + last;
}


// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr) {
  std::string token;
  istr >> token;
  assert (token[0] == '"');
  std::string answer = token;
  while (answer[answer.size()-1] != '"') {
    istr >> token;
    answer += " " + token;
  }
  return answer;
}
