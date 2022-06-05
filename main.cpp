#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cstdlib>


class loc {
public:
    loc(int r = 0, int c = 0) : row(r), col(c) {}
    int row, col;
};
// check if two locations are equal
bool operator== (const loc& lhs, const loc& rhs) {
    return lhs.row == rhs.row && lhs.col == rhs.col;
}

// typedefs
typedef std::vector<std::vector<loc>> vvl_t;
typedef std::vector<std::vector<std::vector<loc>>> vvvl_t;
typedef std::vector<std::vector<std::string>> vvs_t;

// helper from search from loc, check if a location is already on path
bool on_path(loc position, std::vector<loc> const& path) {
    for (unsigned int i = 0; i < path.size(); ++i)
        if (position == path[i]) return true;
    return false;
}

bool search_from_loc(loc position, //  current position
    const std::vector<std::string>& board,
    const std::string& word,
    std::vector<loc>& path, 
    int direction)  //  path up to the current pos 
{
    // DOUBLE CHECKING OUR LOGIC: the letter at the current board
    // position should equal the next letter in the word
    assert(board[position.row][position.col] == word[path.size()]);

    // start by adding this location to the path
    path.push_back(position);

    // BASE CASE: if the path length matches the word length, we're done!
    if (path.size() == word.size()) return true;

    //  search all the places you can get to in one step

    if (direction ==0){

        for (int i = position.row - 1; i <= position.row + 1; i++) {
            for (int j = position.col - 1; j <= position.col + 1; j++) {
                // don't walk off the board though!
                if (i < 0 || i >= int(board.size())) continue;
                if (j < 0 || j >= int(board[0].size())) continue;
                // don't consider locations already on our path
                if (on_path(loc(i, j), path)) continue;
                if (i == position.row - 1 && j == position.col ) direction = 1;
                else if (i == position.row + 1 && j == position.col ) direction = 2;
                else if (i == position.row  && j == position.col -1 ) direction = 3;
                else if (i == position.row  && j == position.col +1 ) direction = 4;
                else continue;
                // if this letter matches, recurse!
                if (word[path.size()] == board[i][j]) {
                    // if we find the remaining substring, we're done!
                    if (search_from_loc(loc(i, j), board, word, path, direction))
                        return true;
                }
            }
        }
    }
    else if (direction == 1){
        for (int i = position.row - 1; i <= position.row + 1; i++) {
            for (int j = position.col - 1; j <= position.col + 1; j++) {
                // don't walk off the board though!
                if (i < 0 || i >= int(board.size())) continue;
                if (j < 0 || j >= int(board[0].size())) continue;
                // don't consider locations already on our path
                if (on_path(loc(i, j), path)) continue;
                if (i == position.row - 1 && j == position.col ) {direction = 1;}
                else continue;
                // if this letter matches, recurse!
                if (word[path.size()] == board[i][j]) {
                    // if we find the remaining substring, we're done!
                    if (search_from_loc(loc(i, j), board, word, path, direction))
                        return true;
                }
            }
        }
    }
    else if (direction == 2){
        for (int i = position.row - 1; i <= position.row + 1; i++) {
            for (int j = position.col - 1; j <= position.col + 1; j++) {
                // don't walk off the board though!
                if (i < 0 || i >= int(board.size())) continue;
                if (j < 0 || j >= int(board[0].size())) continue;
                // don't consider locations already on our path
                if (on_path(loc(i, j), path)) continue;
                if (i == position.row + 1 && j == position.col ) direction = 2;
                else continue;
                // if this letter matches, recurse!
                if (word[path.size()] == board[i][j]) {
                    // if we find the remaining substring, we're done!
                    if (search_from_loc(loc(i, j), board, word, path, direction))
                        return true;
                }
            }
        }
    }
    else if (direction == 3){
        for (int i = position.row - 1; i <= position.row + 1; i++) {
            for (int j = position.col - 1; j <= position.col + 1; j++) {
                // don't walk off the board though!
                if (i < 0 || i >= int(board.size())) continue;
                if (j < 0 || j >= int(board[0].size())) continue;
                // don't consider locations already on our path
                if (on_path(loc(i, j), path)) continue;
                if (i == position.row  && j == position.col -1 ) direction = 3;
                else continue;
                // if this letter matches, recurse!
                if (word[path.size()] == board[i][j]) {
                    // if we find the remaining substring, we're done!
                    if (search_from_loc(loc(i, j), board, word, path, direction))
                        return true;
                }
            }
        }
    }else if (direction == 4){
        for (int i = position.row - 1; i <= position.row + 1; i++) {
            for (int j = position.col - 1; j <= position.col + 1; j++) {
                // don't walk off the board though!
                if (i < 0 || i >= int(board.size())) continue;
                if (j < 0 || j >= int(board[0].size())) continue;
                // don't consider locations already on our path
                if (on_path(loc(i, j), path)) continue;
                if (i == position.row  && j == position.col +1 )  direction = 4;
                else continue;
                // if this letter matches, recurse!
                if (word[path.size()] == board[i][j]) {
                    // if we find the remaining substring, we're done!
                    if (search_from_loc(loc(i, j), board, word, path, direction))
                        return true;
                }
            }
        }
    }

    // At this point we know we have failed to find a path from the
    // current loc.  Remove the current loc from the path and end this
    // recursive call with a failure so that the search can move in a
    // different direction.
    path.pop_back();
    return false;
}// check if the word I have is already in the dictionary
bool c3_helper(const std::string temp_word, const std::vector<std::string> & my_dictionary ){
    for ( unsigned int i = 0; i< my_dictionary.size(); i++){
        if (my_dictionary[i] == temp_word)
            return true;
    }
    return false;
}// check if any accidental words are formed in the temp board
bool check3(const std::vector<std::string> & temp_board, const std::vector<std::string> & my_dictionary){

    // checks horizontally, loops through the vector
    for( unsigned int r = 0; r < temp_board.size(); r++){
        std::string temp_word;//makes a temp_word
        // loops through the letter
        for( unsigned int c = 0; c < temp_board[0].size(); c++){

            if(temp_board[r][c] != '#'){// push letter to tempword if it is not a #

                temp_word.push_back(temp_board[r][c]);
            }
            // if it is or reaches the end, check if this is an accidental word
            if(temp_board[r][c] == '#' or c == temp_board[0].size()-1){
                std::string temp_str = temp_word;
                std::reverse(temp_str.begin(), temp_str.end());// dont forget to check reverse word
                if(temp_word.size() >1 and !c3_helper(temp_word, my_dictionary) and !c3_helper(temp_str, my_dictionary )){
                    std::cout<< temp_word<< "hi";
                    return false;
                }
                else
                    temp_word.clear();

            }

        }

    }
        // checksvertically, loops through the vector
    for ( unsigned int c = 0; c <temp_board[0].size(); c++ ){
        std::string temp_word;//makes a temp_word
        for( unsigned int r = 0; r < temp_board.size(); r++){
              // loops through each the letter
            if(temp_board[r][c] != '#'){// push letter to tempword if it is not a #
                temp_word.push_back(temp_board[r][c]);// if it is or reaches the end, check if this is an accidental word,                                          // easter egg found, didn't think ull look this far!
            }
            if(temp_board[r][c] == '#' or r == temp_board.size()-1){
                std::string temp_str = temp_word;
                std::reverse(temp_str.begin(), temp_str.end());
                if(temp_word.size() >1 and !c3_helper(temp_word, my_dictionary) and !c3_helper(temp_str, my_dictionary )){
                    std::cout<< temp_word<< "by";
                    return false;
                }
                else
                    temp_word.clear();

            }
        }


    }

return true;
}// check if this is a constraint by if the first letter is +
bool check_convert(const std::string& unconverted) {
    if (unconverted[0] == '+') { return true; }
    else { return false; }
}// a sort by size
bool mysort(const std::string& a, const std::string& b) {
    if (a.size() < b.size())
        return true;
    else
        return false;
}// helper function of extra, checks if a word has another word stacked on top
int extra_helper(const vvl_t & total_paths, const  loc & temp_loc){
    int counter = 0;

    for (unsigned i = 0; i < total_paths.size(); i++){// check for each word in the group
        std::vector<loc> word_path = total_paths[i];
        for (unsigned j = 0; j < word_path.size(); j++){// loops each letter in the word
            loc temp_loc2 = word_path[j];
            if (temp_loc == temp_loc2 )
                counter ++;
        }
    }// return the num of stack, better be greater then 1
    return counter;
}

bool extra(const vvl_t & total_paths){// the extra credit for this hw, eliminate not connected solutions
    for (unsigned i = 0; i < total_paths.size(); i++){
        std::vector<loc> word_path = total_paths[i];// the path of a word
        for (unsigned j = 0; j < word_path.size(); j++){
            loc temp_loc = word_path[j];// the locaton of each letter in a word
            int appear = extra_helper(total_paths, temp_loc);// check each letter of the word how many time it appear in group path
            if (appear > 1)
                return true;// yay, it is connected
        }
    }
    return false;


}

// this is a recursion function that find all possibel combinations of size of constraint for words in dictionary
void find_combo(int spot, int combo_size, vvs_t& total_combos, const std::vector<std::string>& my_dictionary, 
                std::vector<std::string>& combo, const int realsize) {
    bool need_more = true;
// takes in a spot, current size, vector vector string all combinations, my dictionary, current combo, and the size of the constraint
    if (combo_size < 1 or int(combo.size()) == realsize) {// if found , pushback and return
        need_more = false;
        total_combos.push_back(combo);
        return;
    }
    else {// else, loop through the diction start with spot
        for (unsigned int i = spot; i < my_dictionary.size() + 1 - combo_size; i++) {
            combo.push_back(my_dictionary[i]);// pushback the word
            find_combo(i + 1, combo_size - 1, total_combos, my_dictionary, combo, realsize);// call the function eith the next spot, the spot still we need -1
            combo.pop_back();// remove the last word
        }
    }
}
// checks if the words can be found on the board in the dictionary matches the num of constaints
bool check_all_found(std::vector<std::string> my_dictionary, std::vector<std::string> temp_board, 
                    const unsigned int cl_size, const unsigned int tp_size){
    // takes in dictionary, a temp_board for one solution, the size of constaint and the size group path
    int ct = 0;
    if (cl_size != tp_size){// If the group has more path return false
        return false;
    }

    for (unsigned int j = 0; j < my_dictionary.size(); j++) {//search for all words in diictionary, should find the constraint num

        std::string temp_word = my_dictionary[j];
        bool found = false;
        std::vector<loc> path;


        for (unsigned int r = 0; r < temp_board.size() && !found; ++r) {//search for words in the map rows
            for (unsigned int c = 0; c < temp_board[r].size() && !found; ++c) {//search for words in the map cols
                // try to find the first letter, if found, call search from loc
                if (temp_board[r][c] == temp_word[0] && search_from_loc(loc(r, c), temp_board, temp_word, path, 0)) {
                    found = true;
                    ct++;
                    }
                }
            }
    }// return f if found extra
    if (ct != cl_size)
        return false;
    else
        return true;

}
// check is helper function of print and amke board, takes in vector or rows and cols, and int num of r and c
bool check(std::vector<int>& grows, std::vector<int>& gcols, int r, int c) {
    assert(grows.size()== gcols.size());
    for (int i = 0; i < grows.size(); i++) {        
        if (grows[i] == r && gcols[i] == c) return true;  // if found, there should be a letter at this location, return true      
    }
    return false;// false means #
}// try to make a board with the og board, path of a solution, empty board
void make_board( const std::vector<std::string>& board, const vvl_t&  total_paths, std::vector<std::string>& temp_board){
    std::string temp_str;
    std::vector<int> grows2;
    std::vector<int> gcols2;// makes a row and a col vector

    for (unsigned int i = 0; i < total_paths.size(); i++) {
        std::vector<loc> wordpath = total_paths[i];

            for (unsigned int k = 0; k < wordpath.size(); k++) {
                grows2.push_back(wordpath[k].row);// push back ints
                gcols2.push_back(wordpath[k].col);// push back ints
            }
        }
        for (unsigned int m = 0; m < board.size(); m++) {// loop through the entire board
            for (unsigned int p = 0; p < board[m].size(); p++) {
                if(check(grows2, gcols2, m, p))// use check, if found, pushback a letter
                    temp_str.push_back(board[m][p]);

                else
                    temp_str.push_back('#');//else pushback #
            }
            temp_board.push_back(temp_str);// push the line back to the temp board
            temp_str.clear();
        }
}
// the print function, takes in board, final path of all solutions, the modes of what to print, 
void print(const std::vector<std::string>& board, const vvvl_t& final_path, const std::string smode,const std::string omode){
    if (smode == "one_solution"&& final_path.size()!= 0)
        std::cout << "Number of solution(s): " << 1 << std::endl;
    else
        std::cout << "Number of solution(s): " << final_path.size() << std::endl;

    if (omode == "count_only")
        return;

    for (unsigned int i = 0; i < final_path.size(); i++) {
        std::cout << "Board:" << std::endl;
        vvl_t grouppath = final_path[i];

        std::vector<int> grows;// makes a row and a col vector
        std::vector<int> gcols;

        for (unsigned int j = 0; j < grouppath.size(); j++) {
            std::vector<loc> wordpath = grouppath[j];

            for (unsigned int k = 0; k < wordpath.size(); k++) {
                grows.push_back(wordpath[k].row);// push back ints
                gcols.push_back(wordpath[k].col);// push back ints
            }
        }
        for (unsigned int m = 0; m < board.size(); m++) {
            for (unsigned int p = 0; p < board[m].size(); p++) {
                if(check(grows, gcols, m, p))//check if there is word there at the spot
                    std::cout << board[m][p];
                else
                    std::cout <<"#";// if not, it is #
            }
            std::cout << std::endl;

        }
        if (smode == "one_solution"){// if only require one solution, break after the first loop
            std::cout<<std::endl;
            return;
        }


    }
    std::cout<<std::endl;


}// takes in the parameters passed from main, ehich are what the users gave
void find_data(const bool ec, const std::string smode, const std::string omode, std::istream &istr, std::istream &istr2){
    std::vector<std::string> my_dictionary;// a dictionary

    std::vector<std::string> board;// a board
    std::vector<std::string> temp_board;// a temp_board
    std::vector<std::string> found_list;// a list of stuff found
    std::vector<int>  constraints_list;// list if constraints
    vvl_t total_paths;// the overall path

    vvs_t total_combos;// all combinations
    vvs_t possible_combos;//all combinations that can be used
    vvvl_t final_path;// path after stuff are removed
    vvs_t final_combo;// combo after stuff are removed
    std::vector<std::string> group_combo;// combo of a group

    std::string token;

    while (istr >> token) {// this parts get the data out of the provided files
        my_dictionary.push_back(token);

    }

    while (istr2 >> token) {
        std::string unconverted;

        if (token[0] == '!') {// if !, we dont need it
            continue;
        }
        else {

            if (check_convert(token)) {// check if I can convert the string to an int

                std::string uncon = token.substr(1, 2);
                int constraint = std::stoi(uncon);

                constraints_list.push_back(constraint);
            }
            else {
                board.push_back(token);// push vback the board

            }
        }
    }

    std::sort(constraints_list.begin(), constraints_list.end());// sort my constaints


    std::vector<std::string> combo;
    int combo_size = constraints_list.size();
    int combo_size2 = combo_size;
    find_combo(0, combo_size, total_combos, my_dictionary, combo, combo_size2);// find all combinations of lenth of constaint list 
    //out of the dictionary


    for (unsigned int j = 0; j < total_combos.size(); j++) {
        bool judge = true;

        std::vector<std::string> temp = total_combos[j];
        sort(temp.begin(), temp.end(), mysort);// use mysort to sort string by size

        for (unsigned int i = 0; i < temp.size(); i++) {
            if (int(temp[i].size()) != constraints_list[i])// check the size of each word match the constraint
                judge = false;

        }
        if (judge) {
            possible_combos.push_back(temp);// pushback only if match
        }

    }

    for (unsigned int i = 0; i < possible_combos.size(); i++) {
        bool all_found = false;
        total_paths.clear();
        group_combo.clear();// check the combo can be found on the vector

        for (unsigned int j = 0; j < possible_combos[i].size(); j++) {
            std::string temp_word = possible_combos[i][j];// makes a temp word

            bool found = false;
            std::vector<loc> path;// check each word in each group can be found
            for (unsigned int r = 0; r < board.size() && !found; ++r) {
                for (unsigned int c = 0; c < board[r].size() && !found; ++c) {
                    if (board[r][c] == temp_word[0] && search_from_loc(loc(r, c), board, temp_word, path, 0)) {
                        found = true;// if it can be found, return true and push it back to the group path and combo
                        total_paths.push_back(path);
                        group_combo.push_back(temp_word);
                    }
                }
            }
            temp_board.clear();
            make_board(board, total_paths, temp_board);//make a board with the words found
            unsigned int tp_size = total_paths.size();
            unsigned int cl_size = constraints_list.size();

            all_found = check_all_found(my_dictionary, temp_board, cl_size, tp_size);// check function see above

            bool all_found2 = false;

            if(ec){// if there is ec, get rid of unconnected
                bool all_found3 = check3 (temp_board, my_dictionary);
                all_found2 = extra(total_paths);// call extra, if test failed, do not pushback to final answer
                if (all_found && all_found2 && all_found3){
                    final_path.push_back(total_paths);
                    final_combo.push_back(group_combo);
                }
            }
            if (all_found && !ec){// normal case, check 3 see above
                bool all_found3 = check3 (temp_board, my_dictionary);
                if (all_found3){// push them back to my final answer.
                    final_path.push_back(total_paths);
                    final_combo.push_back(group_combo);
                }
            }
        }
    }
        print(board, final_path, smode, omode);// call print with the condenced data, all filtered

}


int main(int argc, char* argv[]) {// my main function, checks the stuff given to me is good, nothing to comment about

    if (argc < 4 || argc > 6) {
      std::cerr<< "wrong arguments"<< std::endl;
      return 1;
    }
    bool ec = false;

    if ( argc == 6&& std::string(argv[5]) == "gc"){
        ec = true;
    }
    std::string smode = std::string(argv[3]);// get the arguments
    std::string omode = std::string(argv[4]);
    std::ifstream istr(argv[1]);
    std::ifstream istr2(argv[2]);
    if (!istr) {// check if they are legit
        std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
        return 1; 
    }

    if (!istr2) {
        std::cerr<< "ERROR: Could not open " << argv[2] << " for reading." << std::endl;
        return 1; 
    }
    if (smode != "all_solutions" and smode != "one_solution") {
        std::cerr<< "ERROR: Could not read third arg." << std::endl;
        return 1; 
    }
    if (omode != "print_boards" and smode != "count only") {
        std::cerr<< "ERROR: Could not read  fourth arg." << std::endl;
        return 1; 
    }

// call find_data with the stuff passed in from user
    find_data(ec, smode, omode, istr, istr2);


}
