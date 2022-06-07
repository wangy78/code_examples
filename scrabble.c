#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int pair_list_size = 26;

struct my_pair {
    char first;
    int second;
}my_pair;
/*scrabble.c*/

/*
	argument: word - the word to be scored; blank tiles are represented as the space character, ' '
	requires: global map of tile set in scrabble to their associated scores is not null; word is not null
	returns: integer equal to the score of the word argument; 0 if word empty string, contains invalid characters
			 (ex: '8', '!'), or contains an impossible number of a certain character (ex: 5 'c' characters even
			 though there are only 2 'c's in scrabble)
	effects: none
	modifies: none
	throws: none
*/
int points(char* word, struct my_pair pair_list[]){
	int score = 0;
	for(int i = 0; i< strlen(word);i++){// add up the point for each letter 
		for(int j = 0; j< pair_list_size; j++){
			if((pair_list[j]).first == word[i]){
				score+= pair_list[j].second;
			}

		}
	}
	return score;

}

/*
	argument: results - the list of words to be found (or not found) in the dictionary;
					 blank tiles are represented as the space character, ' '
			  playable_results - playable words will be filled in here

			  res_ct - number of possible playable words
			  dict - the dictionary to loop up words in
			  dict_len - length of dictionary



	requires: dictionary is not null; each word in results is not null, playable_results is empty, res_ct and dict_len
				matches the size of results and dictionary
	returns: the number of playable words
	effects: none
	modifies: playable_results, fills in the playable words
	throws: none
*/


int playable(char** results,  char playable_results[1000][60], int res_ct, char ** dict, int dict_len){

	int play_ct = 0;

	for(int i = 0; i< res_ct; i++){// for each word in results
		for(int j = 0; j< dict_len; j++){// for each word in dictionary
			
			if(strcmp(results[i], dict[j]) == 0){
				strcpy(playable_results[play_ct], dict[j]);
				play_ct++;
			}
		}

	}

	return play_ct;


}
// prevent abuse of duplicate letters
// if my letters are "aab"
// make sure at most 2 a can appear in my word

int check(char *j, char* k, char* letters){

	int ct = 0;
	int ct2 = 0;

	char ch1 = j[0];
	for(int i = 0; i< strlen(letters); i++){
		if(letters[i] == ch1){
			ct++;
		}
	}
	
	while (*k!= '\0'){
		if(*k == ch1){
		
			ct2++;
			
			
		}
		k++;
	}
	if(ct2>ct-1){
		return 1;
	}
	return 0;


}

/*
	argument: letters - an array of letters that will be used to generate anagrams;
						blank tiles are represented as the space character, ' '
			  results - where results will be stored

	requires: letters is not null
	returns: the length of results
	effects: none
	modifies: results, fill in the possible playable words aka valid letter combinations into results
	throws: none
*/
int anagrams(char* letters, char** results){




	int res_ct = 0;


	int max_len = strlen(letters);

	char str_letters [1000][2];// base 1 letter words
	char str_letters2 [100000][max_len+1];// z-1 length words, z is used later


	char l2[strlen(letters)+1];
	for(int i =0; i< strlen(letters)+1;i++){
		l2[i] = tolower(letters[i]);

	}

		





	for(int i = 0; i< max_len; i++){
		
		char temp[2];
		temp[0] = tolower(letters[i]);
		temp[1] = '\0';
		strcpy(str_letters[i], temp);
		strcpy(str_letters2[i], temp);


	}
	int ct2 = max_len;



	
	for(int i = 0; i< max_len; i++){// add in the len 1 letters

		results[res_ct] = malloc(1+strlen(str_letters[i])*sizeof(char));

		strcpy(results[res_ct], str_letters[i]);
		res_ct++;

		//printf("%s==>%d\n", str_letters[i], res_ct-1);
	}




	int ct = 0;// counter for temp results
		
	for(int z = 0; z< max_len-1; z++){// add 2 letter words, 3 letters...
		

		char temp_results [100000][max_len+1];// a temp list of string that store z length letter combos

		for(int j = 0; j< max_len; j++){

			for(int k = 0; k< ct2; k++){// ct 2 is str_letters2 length

				if(check(str_letters[j],str_letters2[k], l2)==0){


					strcpy(temp_results[ct], "");						

					strcat(temp_results[ct], str_letters2[k]);
					strcat(temp_results[ct], str_letters[j]);


					ct++;
								


					
				}

			}

			
		}


		for(int j = 0; j< ct; j++){
			

			int stat = 0;// does not allow duplicates
			for(int k = 0; k< res_ct; k++){
				if(strcmp(results[k], temp_results[j]) == 0){
					stat = stat+1;
				}

			}
			if(stat==0){

				results[res_ct] = malloc(1+strlen(temp_results[j])* sizeof(char));
				strcpy(results[res_ct], temp_results[j]);
				
				res_ct++;

			}

			
			strcpy(str_letters2[j], temp_results[j]);


		}

		ct2 = ct;
		ct = 0;


	}
	for(int i = 0; i< res_ct; i++){
		//printf("%s\n", results[i]);
	}
	return res_ct;

}

/*
	argument: playable_results, an array of strings; playable_ct, number of playable words;  pair_list, the lists that holds letter values

	requires:playable_results, an array of strings that are playable, playable_ct matches length of playable_words, pair_list is not null
	returns: none
	effects: prints out the best playable words
	modifies: none
	throws: none
*/


void best_playable_words(char playable_results[1000][60], int playable_ct,struct my_pair pair_list[]){


	int records[playable_ct];


	for (int i = 0; i< playable_ct; i++){// find score for each playable words
		int score = points(playable_results[i], pair_list);
		records[i] = score;

		//printf("best = %s, with points %d\n", playable_results[i], score);


	}
	for(int i = 0; i< playable_ct; i++){// print words by score
		int max_val  = -1;
		int max_loc = -1;
		for(int j = 0; j< playable_ct; j++){
			if(records[j]> max_val){
				max_val = records[j];
				max_loc = j;

			}


		}
		records[max_loc] = -1;

		printf("\"%s\"==>with points %d\n", playable_results[max_loc], max_val);

	}
	




}
int my_read(char **dict){// reads the dictionary

	FILE *ptr;
	ptr = fopen("collins-words-2019.txt","r");



	int bufferLength = 60;
	char buffer[bufferLength]; 
	
	int dict_len = 0;

	fgets(buffer, bufferLength, ptr);// skip first 2 lines
	fgets(buffer, bufferLength, ptr);


	while(fgets(buffer, bufferLength, ptr)) {
		dict[dict_len] = malloc(1+strlen(buffer) * sizeof(char));

		buffer[strcspn(buffer, "\n\r")] = '\0';
			
		for(int j = 0; j< strlen(buffer); j++){
			
			buffer[j] = tolower(buffer[j]);
			
		}

		strcpy(dict[dict_len], buffer);
		dict_len++;

	}
	fclose(ptr);

	return dict_len;

}
void my_test(char* words, char **dict, int dict_len ){

	char* my_alpha = "abcdefghijklmnopqrstuvwxyz";

	struct my_pair pair_list[pair_list_size+1];

	for(int i = 0; i< pair_list_size; i++){

		struct my_pair a = {my_alpha[i], i};
		pair_list[i] = a;

	}


	char ** results = malloc(1000000*sizeof(char*));

	char playable_results[1000][60];


	int res_ct = anagrams(words, results);

	//printf("rc = %d\n", res_ct);// the total order of letters count

	int playable_ct = playable(results, playable_results, res_ct, dict, dict_len);

	//printf("pc = %d\n", playable_ct);// the playable words count

	best_playable_words(playable_results, playable_ct, pair_list);

	for(int i = 0; i< res_ct; i++){
		free(results[i]);

	}
	free(results);
}

int main(){// requires there is a dictionary collins-words-2019.txt





	char **dict;
	dict = malloc(279999*sizeof(char*));


	int dict_len = my_read(dict);


	my_test("abcd", dict, dict_len);// the test is just slow, not infinite looped
	printf("next: \n");

	my_test("aabs", dict, dict_len);
	printf("next: \n");

	my_test("aaaaaa", dict, dict_len);
	printf("next: \n");
	my_test("zzzzzz", dict, dict_len);
	printf("next: \n");
	my_test("hiiamjoe", dict, dict_len);
	printf("next: \n");
	my_test("cat,dog", dict, dict_len);
	printf("next: \n");
	my_test(" ", dict, dict_len);
	printf("next: \n");
	my_test("", dict, dict_len);
	printf("next: \n");

	my_test("iatheJOE", dict, dict_len);




	

	for(int j = 0; j< dict_len; j++){
		free(dict[j]);
	}
	free(dict);
	

}
/*

 (a) aspects of the specs that you disagreed with 

 	I disagree that playable is a bool so I asked her to chnage the return type to an int
 	I disagree with making global variables like dictionary, I asked her to make most globals local
 	I disagree with char** returns, because I dont need to return anything if i modify char**, 
 	I disagree that not enough argument are given in all functions, to make my life easier, I asked her to add parameters that reflects length
 	I dont know if char** for words is a good idea, but I asked her to use square brackets with appropriate sizes

 	I asked her to change the above

 	I disagree that anything should be global, 
 	I disagree that any function will ever return, I will use pointers
 	I disagree that chars like 8 or ! is 0 points, I believe that they will get the points in the scoreboard


 	b) approaches you would have taken instead. Keep this to about one page (or screen).

 	I would have all local variables
 	I would use add arguments as parameters to functions instead of return
 	I would use ints as bools, I dont think c has bools
 	I would even add more parameters sto make my code easier
 	I would add more conor cases like upper/lower letter
 	She did not mention memory at all, I would like that


 	Otherwise, I appreciate her specs, she did a great job and it was detailed.
 	She has some corner cases and I would like to add more


*/


