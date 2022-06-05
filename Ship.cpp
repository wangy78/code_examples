#include "Ship.h"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <algorithm>

typedef std::list<std::string> preference_type;

typedef std::list<std::list<std::string>> lls_t;
void  Ship::create(){
	name = "the one";
	rented_num = 666;
}

void  Ship::create(std::string & cus_name){// constructor, very basic, sets the name and size
	name = cus_name;
	rented_num = 0;
}
void Ship::update(preference_type &newlist){
	cus_pref_list = newlist;

}
void Ship::addnew(std::string & DVD_name){
	cus_pref_list.push_back(DVD_name);
}
// recieves means to erase from pref list and add to holding
void Ship::receives(const std::string & DVD_name2){
	rented_num++;
	holding.push_back(DVD_name2);
// fin the loaction to remove
	preference_type::iterator movie_it = std::find(cus_pref_list.begin(), cus_pref_list.end(), DVD_name2);

    if (movie_it == cus_pref_list.end())
      std::cout<< "This shouldnt happen"<< std::endl;
    else{

    	cus_pref_list.erase(movie_it);
      
    }
}
// check if the size is right
bool Ship::has_max_num_movies(){
	if( rented_num < 3)

  		return false;
  	else
  		return true;


}
// check if the customer just subscribe and dont watch moives
bool Ship::preference_list_empty(){
  if (cus_pref_list.size() <1 )
    return true;
  else
    return false;

}
preference_type Ship::get_preferences(){
  return cus_pref_list;
}

void Ship::return_newest(){// delete and reduce size
	holding.pop_back();
	rented_num --;


}
void Ship::return_oldest(){// delete and reduce size
	holding.pop_front();
	rented_num --;
	
}
std::string Ship::getnewest(){// return the newest movie name
	preference_type::iterator go =  holding.end();
	go--;
	return *go;

}
std::string Ship::getoldest(){// return the oldest movie name
	preference_type::iterator gn =  holding.begin();
	return *gn;

}
// print out holdings
void Ship::print(std::ostream& ostr){
	preference_type::iterator gn =  holding.begin();// use a loop to print

	for (int i = 0; i < rented_num; i++){
		ostr << "    "<< (*gn)<< std::endl;
		gn++;
	}
}
// print out preference list
void Ship::print2(std::ostream& ostr){
	ostr<< "  preference list:"<< std::endl;
	preference_type::iterator gn =  cus_pref_list.begin();// use a loop to print
	for (unsigned int i = 0; i < cus_pref_list.size(); i++){
		ostr << "    "<< (*gn)<< std::endl;
		gn++;
	}
}