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
*			For emample: add=2*37*1+7*37*21+7*37*3
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
*	 faster than link list, almost 0s. But it has a insert speed largely slower than link list.
* 4. Shortness need to be improved:
*	Delete key to null will lead to a situation which search hash jump(in insert;search;
*	multisearch function) could not continue. That is the reason why I resize hashmap again
*	at the end of delete function.
*	But a better way to solve the problem is delete the data to NULL and change the key to
*	a label "DELETE" which never appear in map. And this way need change insert|search|
*	multisearch function.
*
**********************************************************************************************/

#include "fmvm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXSIZE 46
#define BEGINARRAYSIZE 2
#define ALPHABET 37
#define LOADFACTOR 0.6
#define LENTH 3

/* Return *argv[] list of pointers to all values stored with key, n is the number of values */
int getnextprime(int n);
int countpow(char *word, int i, int m);
int hashcount(mvm *hashmap, char *word, int *prime, int i);
unsigned long countmul(char *word, int *prime);
int *createprime(int *prime);
double resizeVaild(mvm *hashhead);
mvm *resize(mvm *hashmap, int *prime);
int uppertolower(char c);

/*init the mvm*/
mvm* mvm_init(void)
{
    mvm *head = (mvm *)calloc(1, sizeof(mvm));
    head->totalblocks = getnextprime(BEGINARRAYSIZE);
    head->head = (mvmcell *)calloc(1, head->totalblocks * sizeof(mvmcell));
    head->numkeys = 0;
    return head;
}

/*if m is NULL, return 0*/
int mvm_size(mvm* m)
{
    if (m == NULL)
    {
        return 0;
    }
    return m->numkeys;
}

/*Insert elem into map*/
void mvm_insert(mvm* m, char* key, char* data)
{
    int *prime = (int *)calloc(1, ALPHABET * sizeof(int));
    int i = 0, hash;
    if (m == NULL || key == NULL || data == NULL)
    {
        free(prime);
        return;
    }
    prime = createprime(prime);
    /*if load factor is more than 0.6, resize*/
    if (resizeVaild(m) > LOADFACTOR)
    {
        m = resize(m, prime);
    }
    /*find hash until it is a block*/
    do
    {
        hash = hashcount(m, key, prime, i++);
        if (i + m->numkeys >= m->totalblocks)
        {
            m = resize(m, prime);
            i = 0;
        }
    }
    while (m->head[hash].data != NULL);
    /*cooy key and data to array*/
    m->head[hash].key = (char *)calloc(1, (strlen(key) + 1) * sizeof(char));
    m->head[hash].data = (char *)calloc(1, (strlen(data) + 1) * sizeof(char));
    memcpy(m->head[hash].key, key, strlen(key));
    memcpy(m->head[hash].data, data, strlen(data));
    m->numkeys++;

    free(prime);
}

/* Return the corresponding value for a key */
char* mvm_search(mvm* m, char* key)
{
    int i = 0;
    int hash;
    int *prime = (int *)calloc(1, ALPHABET * sizeof(int));
    prime = createprime(prime);
    /*continue find hash if hash collision is on.
     *if new hash lead to a key to NULL, the key is not in the map*/
    do
    {
        hash = hashcount(m, key, prime, i++);
        if (m->head[hash].key == NULL || i > m->totalblocks)
        {
            free(prime);
            return NULL;
        }
    }while (strcmp(m->head[hash].key, key) != 0);
    free(prime);
    return m->head[hash].data;
}

/* Store list as a string "[key](value) [key](value) " etc.  */
char* mvm_print(mvm* m)
{
    int i;
    char *str = (char *)calloc(1, 1);
    char *temp = (char *)calloc(1, (LENTH*MAXSIZE) * sizeof(char));
    for (i = 0; i < m->totalblocks; i++)
    {
        if (m->head[i].data != NULL)
        {
            sprintf(temp, "[%s](%s) ", m->head[i].key, m->head[i].data);
            str = (char *)realloc(str, (strlen(str) + strlen(temp)+1) * sizeof(char));
            strcat(str, temp);
        }
    }
    free(temp);
    return str;
}

/* Return the corresponding value for a key */
void mvm_delete(mvm* m, char* key)
{
    int flag = 1;
    int i = 0;
    int hash;
    int *prime = (int *)calloc(1, ALPHABET * sizeof(int));
    if (m == NULL || key == NULL || key[0] == '\0')
    {
        free(prime);
        return;
    }
    prime = createprime(prime);
    do
    {
        hash = hashcount(m, key, prime, i++);
        if (i > m->totalblocks)
        {
            free(prime);
            return;
        }
        if (m->head[hash].key != NULL)
        {
            flag = strcmp(m->head[hash].key, key);
        }
    }
    while (m->head[hash].key == NULL && flag);

    free(m->head[hash].key);
    free(m->head[hash].data);
    m->head[hash].key = NULL;
    m->head[hash].data = NULL;
    m->numkeys--;

    /*	Delete key to null will lead to a situation which search hash jump(in insert;search;
    *	multisearch function) could not continue. That is the reason why I resize hashmap
    *	again at the end of delete function.
    */
    m=resize(m, prime);
    free(prime);
}

/* Return *argv[] list of pointers to all values stored with key, n is the number of values */
char** mvm_multisearch(mvm* m, char* key, int* n)
{
    int *prime = (int *)calloc(1, ALPHABET * sizeof(int));
    char *str = mvm_search(m, key);
    char **res = (char **)calloc(1, sizeof(char*));
    int i = 0, hash;
    prime = createprime(prime);
    *res = (char *)calloc(1, (strlen(str)+1) * sizeof(char));
    if (str == NULL)
    {
        free(res);
        return NULL;
    }

    memcpy(*res, str, strlen(str));
    (*n)++;
    /*if str is not NULL,find the first key hash*/
    do
    {
        hash = hashcount(m, key, prime, i++);
    }while (strcmp(m->head[hash].key, key) != 0);
    /*continue to find hash until the key is NULL*/
    while (m->head[hash].key != NULL)
    {
        hash = hashcount(m, key, prime, i++);
        if (m->head[hash].key == NULL)
        {
            free(prime);
            return res;
        }
        if (!strcmp(m->head[hash].key, key))
        {
            res = (char**)realloc(res, (++*n) * sizeof(char*));
            *(res + *n - 1) = (char*)calloc(1, (strlen(m->head[hash].data)+1) * sizeof(char));
            memcpy(*(res + *n - 1), m->head[hash].data, strlen(m->head[hash].data));
        }
    }
    free(prime);
    return res;
}

/* Free & set p to NULL */
void mvm_free(mvm** p)
{
    mvm **a;
    int i;
    if (p == NULL)
    {
        return;
    }
    a = p;
    for (i = 0; i < (*p)->totalblocks; i++)
    {
        if ((*a)->head[i].key!=NULL)
        {
            free((*a)->head[i].key);
        }
        if ((*a)->head[i].data!=NULL)
        {
            free((*a)->head[i].data);
        }
    }
    if ((*a)->head)
    {
        free((*a)->head);
    }
    free((*a));
    *p = NULL;
}

int getnextprime(int n)
{
    int temp = n + 1, sqt, flag = 0;
    while (1)
    {
        for (sqt = 2; ((sqt < temp) && (flag == 0)); sqt++)
        {
            if (temp%sqt == 0)
            {
                flag = 1;
            }
        }
        if ((sqt == temp) && (flag == 0))
        {
            return temp;
        }
        else
        {
            temp++;
            flag = 0;
        }
    }
}
/*hash1 function*/
unsigned long countmul(char *word, int *prime)
{
    int i;
    unsigned long mul = 1;
    for (i = 0; i < (int)strlen(word); i++)
    {
        mul *= prime[uppertolower(word[i])];
    }
    return mul;
}
/*hash function*/
int hashcount(mvm *hashmap, char *word, int *prime, int i)
{
    unsigned long hash1 = countmul(word, prime);
    unsigned long hash2 = countpow(word, i, hashmap->totalblocks);
    unsigned long res = (hash1 + hash2) % hashmap->totalblocks;
    return (int)res;
}

/*hash2 function*/
int countpow(char *word, int i, int m)
{
    int j, k;
    unsigned long temp;
    unsigned long res = 0;
    for (j = 0; j < (int)strlen(word); j++)
    {
        temp = 1;
        for (k = 0; k < j; k++)
        {
            temp += ALPHABET;
        }
        res += temp*(uppertolower(word[j]));
    }
    res %= m;
    return i*res;
}

/*create enough primes to represent all letter*/
int *createprime(int *prime)
{
    int temp, cnt = 0, flag = 0, sqt;
    for (temp = 2; cnt < ALPHABET; temp++)
    {
        for (sqt = 2; ((sqt < temp) && (flag == 0)); sqt++)
        {
            if (temp%sqt == 0) flag = 1;
        }
        if ((sqt >= temp) && (flag == 0))
        {
            *(prime + cnt) = temp;
            cnt++;
        }
        flag = 0;
    }
    return prime;
}

/*return current loat factor*/
double resizeVaild(mvm *hashhead)
{
    double f = (double)hashhead->numkeys / hashhead->totalblocks;
    return f;
}


/*resize function*/
mvm *resize(mvm *hashmap, int *prime)
{
    mvm *hashmapnew = (mvm *)calloc(1, sizeof(mvm));
    int i, j;
    int hash;
    /*find the next double total blocks prime to init new hashmap*/
    hashmapnew->totalblocks = getnextprime(2 * hashmap->totalblocks);
    hashmapnew->head = (mvmcell *)calloc(1, hashmapnew->totalblocks * sizeof(mvmcell));

    /*put elem from old hashmap to new hashmap in a new order*/
    for (i = 0; i < hashmap->totalblocks; i++)
    {
        if (hashmap->head[i].key != NULL)
        {
            j = 0;
            do
            {
                hash = hashcount(hashmapnew, hashmap->head[i].key, prime, j++);
                if (j + hashmapnew->numkeys >= hashmapnew->totalblocks)
                {
                    hashmapnew = resize(hashmapnew, prime);
                    /*i = 0;*/
                }
            }
            while (hashmapnew->head[hash].key != NULL);
            hashmapnew->head[hash].key = (char *)calloc(1, ((int)strlen(hashmap->head[i].key) + 1) * sizeof(char));
            hashmapnew->head[hash].data = (char *)calloc(1, ((int)strlen(hashmap->head[i].data) + 1) * sizeof(char));

            memcpy(hashmapnew->head[hash].key, hashmap->head[i].key, strlen(hashmap->head[i].key));
            memcpy(hashmapnew->head[hash].data, hashmap->head[i].data, strlen(hashmap->head[i].data));

            if (hashmap->head[i].key)
            {
                free(hashmap->head[i].key);
            }
            if (hashmap->head[i].data)
            {
                free(hashmap->head[i].data);
            }

            hashmapnew->numkeys++;
        }
    }

    /*I have to relloc old hashmap pointer ,copy elems from new to old to return pointer.
     * Because I have no access to change function prototypes*/
    /* hashmap = (mvm *)realloc(hashmap, sizeof(mvm));*/
    hashmap->numkeys = 0;
    if (hashmap->head)
    {
        free(hashmap->head);
    }
    hashmap->head = (mvmcell *)calloc(1, hashmapnew->totalblocks * sizeof(mvmcell));
    hashmap->totalblocks = hashmapnew->totalblocks;
    for (i = 0; i < hashmap->totalblocks; i++)
    {
        if (hashmap->head[i].key)
        {
            free(hashmap->head[i].key);
        }
        if (hashmap->head[i].data)
        {
            free(hashmap->head[i].data);
        }
        if (hashmapnew->head[i].key != NULL)
        {
            hashmap->head[i].key = (char *)calloc(1, ((int)strlen(hashmapnew->head[i].key) + 1) * sizeof(char));
            hashmap->head[i].data = (char *)calloc(1, ((int)strlen(hashmapnew->head[i].data) + 1) * sizeof(char));
            memcpy(hashmap->head[i].key, hashmapnew->head[i].key, strlen(hashmapnew->head[i].key));
            memcpy(hashmap->head[i].data, hashmapnew->head[i].data, strlen(hashmapnew->head[i].data));
            hashmap->numkeys++;
        }
    }
    mvm_free(&hashmapnew);
    return hashmap;
}

/*return the number repersent each letter*/
int uppertolower(char c)
{
    if (c >= 'a'&&c <= 'z')
    {
        return c - 'a';
    }
    else if (c == ' ')
    {
        return 'z' + 1 - 'a';
    }
    else if (c >= '0'&&c <= '9')
    {
        return 'z' + 2 - 'a' + c - '0';
    }
    else if (c >= 'A'&&c <= 'Z')
    {
        return c - 'A';
    }
    return 0;
}
