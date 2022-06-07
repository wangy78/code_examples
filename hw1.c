#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

// requires the main cache operation, token is each valid string, cache_var is my cache structure, cache_size

void my_cache(char * token, char** cache_var, int cache_size){

	char * token_ct = token;// find the hash
	int asc_total = 0;
	while(* token_ct != '\0'){
		asc_total = asc_total+ (int)*token_ct;
		token_ct++;

	}
	asc_total = asc_total % cache_size;


	char** cache_var_ct = cache_var;
	for(int i = 0; i< asc_total; i++){
		cache_var_ct++;
	}// chech for calloc, realloc or nop
	if(*cache_var_ct == NULL){// no value before, calloc needed
		*cache_var_ct = calloc(strlen(token)+1, sizeof(char));
		strcpy(*cache_var_ct, token);
		printf("Word \"%s\" ==> %d (calloc)\n", token, asc_total);


	}else{
		if(strlen(*cache_var_ct) == strlen(token)){// different size value here, realloc needed
			strcpy(*cache_var_ct, token);
			printf("Word \"%s\" ==> %d (nop)\n", token, asc_total);



		}else{// nop

			*cache_var_ct = realloc(*cache_var_ct,(int)strlen(token)+1);

			strcpy(*cache_var_ct, token);
			printf("Word \"%s\" ==> %d (realloc)\n", token, asc_total);


		}

	}


}

// clean each line of input and store the result in cache
// requires buf: a line of words, cache_var: the cache structure, cache_var_len the length of cache, cache size
// find all valid words
//return current cache size
int my_parse(char * buf, char ** cache_var, int cache_var_len, int cache_size){

	char* buf_ct0 = buf;

	while(*buf_ct0!= '\0'){// clean the data, get rid of bad characters
		if(*buf_ct0== '\n' || *buf_ct0== '\r'){
			*buf_ct0= '\0';
		}
		if(!isalnum(*buf_ct0)){
			*buf_ct0 = ' ';
		}
		buf_ct0++;

	}

	char* token = strtok(buf, " ");

	char* buf_ct = buf;

	while (token != NULL) {// read each token or word


		if(strlen(token)>=2){// check if i can cache it


			my_cache(token, cache_var, cache_size);


       	 	cache_var_len++;
        	buf_ct++;
		}
		token = strtok(NULL, " ");
  
    }
    return cache_var_len;




}
// requires size of cache, buffer string and file
// read form inputfile FILE *ptr into buffer, int n is allowed cache size

void my_read(int n, char * buffer, FILE *ptr){// reading in a file


	char *buf = (char *)calloc(128, sizeof(char));

	char **cache_var;
	cache_var = calloc(n, sizeof(char*));
	int cache_var_len = 0;




	while(fgets(buf, 128, ptr)){// parse each line and store data in my parse

		cache_var_len = my_parse(buf, cache_var, cache_var_len, n);


	}

	char ** cache_var_ct = cache_var;// print the updated cache

	for(int i=0; i< n; i++){

		
		if(*cache_var_ct!=NULL){
			printf("Cache index %d ==> \"%s\"\n",i,*cache_var_ct);
			free(*cache_var_ct);
		}

		cache_var_ct++;
	}
	free (cache_var);
	free(buf);


	fclose(ptr);




}


int main(int argc, char **argv){

	if ( argc != 3 )// check for correct argument counts
  {
    fprintf( stderr, "ERROR: wrong arguments number, arg1 should be cache size, arg2 should be file, \n" );
    return EXIT_FAILURE;
  }


	char** pt = argv;// read in the arguments
	pt++;


    char *	arg1 = *pt;



	int n = atoi(arg1);

	pt++;

	char *buffer = *pt;


	FILE *ptr;
	ptr = fopen(buffer,"r");
	if(n<1){

		fprintf( stderr, "invalid cache size, it has to be >0\n");// check for valid size 

	}

	if(ptr == NULL){
		fprintf( stderr, "can't open file\"%s\"\n", buffer );// check for correct file
		return EXIT_FAILURE;

	}

	my_read(n, buffer, ptr);
	return EXIT_SUCCESS;




}
