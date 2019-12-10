/**********************************************************************************************
* Code by ff19085, Yinan Yang. 
* Multi-Value Map ADT : via Array with Dynamic Double Hashing
* 1. Change in struct: 
*	delete :	struct mvmcell next pointer
*	add:		int totalblocks in struct mvm to store array lenth. 
* 2. Hash function:
*     I create two hash functions all based on Prime Algorithm, which are:
*	hash1(countmul):each letter have an unique prime number, and if multiphy them in a word,
*			the result will be unique unless anagram words.
*			For example: add=2*7*7
*
*	hash2(countpow):the prime number which belongs to each letter multiphy the lenth weight.
*			For emample: add=2*37^0+7*37^1+7*7^2
*	i: 	is for find times, which begin with 0.
*	m:	is for array total blocks.
*	the whole hash function is:
*			hash=(hash1+i*hash2)mod m
* 3. Time Complexity and efficiency:
*	O(n) insertion with a dynamic resize
*	O(1) search and multisearch
*	O(n) delete(because it with a resize)
*	
* 	The begin hashmap size is 3, and if load in Excercise11.2,the final size is more than 
*	350,000	with many times resize. With many test, this Algorithm has a search speed 
*	10%-20% faster than link list. But it has a insert speed 30% slower than link list. 
* 4. Shortness need to be improved:
*	Delete key to null will lead to a situation which search hash jump(in insert;search;
*	multisearch function) could not continue. That is the reason why I resize hashmap again
*	at the end of delete function.
*	But a better way to solve the problem is delete the data to NULL and change the key to
*	a label "DELETE" which never appear in map. And this way need change insert|search|
*	multisearch function.
*
**********************************************************************************************/

/* Error that can't be ignored */
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)

struct mvmcell {
   char* key;
   char* data;
};
typedef struct mvmcell mvmcell;

struct mvm {
   mvmcell* head;
   int numkeys;
   int totalblocks;
};
typedef struct mvm mvm;

mvm* mvm_init(void);
/* Number of key/value pairs stored */
int mvm_size(mvm* m);
/* Insert one key/value pair */
void mvm_insert(mvm* m, char* key, char* data);
/* Store list as a string "[key](value) [key](value) " etc.  */
char* mvm_print(mvm* m);
/* Remove one key/value,and resize it to avoid the NULL key cannot continue the search*/
void mvm_delete(mvm* m, char* key);
/* Return the corresponding value for a key */
char* mvm_search(mvm* m, char* key);
/* Return *argv[] list of pointers to all values stored with key, n is the number of values */
char** mvm_multisearch(mvm* m, char* key, int* n);
/* Free & set p to NULL */
void mvm_free(mvm** p);
/*if need resize the hashmap, count next more than double total size prime.*/
int getnextprime(int n);
/*count hash2*/
int countpow(char *word,int i,int m);
/*count hash*/
int hashcount(mvm *hashmap,char *word,int *prime,int i);
/*count hash1*/
unsigned long countmul(char *word,int *prime);
/*get prime[37] to represent a-z(A-Z) 0-9 and space*/
int *createprime(int *prime);
/*if the hash map is more than load factor*/
float resizeVaild(mvm *hashhead);
/*resize the hashmap*/
mvm *resize(mvm *hashmap,int *prime);
/*return the represent number*/
int uppertolower(char c);
