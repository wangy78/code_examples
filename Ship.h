#ifndef __Ship_h_
#define __Ship_h_
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <algorithm>
// ship class, also can b unstoud as customer class
class Ship{
public:

// no public vars
	typedef std::list<std::string> preference_type;

	typedef std::list<std::list<std::string>> lls_t;
// initializer
	Ship(){create();}

	Ship( std::string & cus_name ){create(cus_name);}
// those changes
	void update( preference_type &new_list);
	void addnew( std::string & DVD_name);

	preference_type get_preferences();
//checkers
	bool has_max_num_movies();
	bool preference_list_empty();



	void return_oldest();
	std::string getoldest();

	void return_newest();
	std::string getnewest();
	// printers
	void print(std::ostream& ostr);
	void print2(std::ostream& ostr);
	//getters
	void receives(const std::string & DVD_name2);
	int rented_n(){return rented_num;}

	std::string getname(){return name;}

	int get_pref_len(){return cus_pref_list.size();}
	preference_type get_holding(){return holding;}




// privates

private:
	// default const
	void create(std::string & cus_name);
	void create();
	
	int rented_num;// private variables

	std::list<std::string> holding;

	std::string name;

	preference_type cus_pref_list;


};


#endif