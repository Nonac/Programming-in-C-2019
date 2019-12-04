#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "/Users/nickyang/CLionProjects/Clion_practise/varr.h"

#define STRSIZE 20

int main(void)
{

    arr *aint;
    arr *astr;
    char str1[STRSIZE];
    char str2[STRSIZE];
    int i, *j;

    printf("Basic Array Tests ... Start\n");
/*
    aint = arr_init(sizeof(i));
    assert(aint != NULL);
    i = 1;
    arr_set(aint, 0, &i);
    i = 2;
    arr_set(aint, 4, &i);
    j = arr_get(aint, 0);
    assert((*j)==1);
    j = arr_get(aint, 4);
    assert((*j)==2);
    arr_free(&aint);
    assert(aint==NULL);
*/
    aint = arr_init(sizeof(i));
    for(i=1; i<10000; i+=100){
        arr_set(aint, i, &i);
        j = arr_get(aint, i);
        assert((*j)==i);

        assert(arr_get(aint, i-1) != NULL);
    }
    arr_free(&aint);
    assert(aint==NULL);


    astr = arr_init(STRSIZE);
    assert(astr != NULL);
    for(i=1; i<10000; i+=100){
        sprintf(str1, "%05d", i);
        arr_set(astr, i, str1);
        strcpy(str2, arr_get(astr,i));
        assert(strcmp(str1, str2)==0);
        assert(arr_get(astr, i-1) != NULL);
    }
    arr_free(&astr);
    assert(astr==NULL);

    printf("Basic Array Tests ... Stop\n");
    return 0;
}

arr* arr_init(int elementsize)
{
    arr* l;
    l = (arr*) calloc(1,sizeof(arr));
    if(l == NULL){
        ON_ERROR("Creation of Array Failed\n");
    }
    l->data =calloc(1, elementsize);
    if(l->data == NULL){
        ON_ERROR("Creation of Array Failed\n");
    }
    l->pz = 1;
    l->elsz=elementsize;
    return l;
}

void arr_set(arr *l, int n, void* v)
{
    char *temp;
    int i;
    if (n < 0){
        ON_ERROR("Array accessed with negative index ...\n");
    }
    /* Index greater than current physical size, expand */
    if(n >= l->pz){
        /* Like malloc, but copies original data, then frees original */
        l->data =realloc(l->data, n*l->elsz);
        if(l->data == NULL){
            ON_ERROR("Resize of Array Failed\n");
        }
        l->pz = n+1;
    }
    temp = (char *) (l->data);
    temp = temp + n * l->elsz;
    memcpy((void*) temp, v, l->elsz);

}

void* arr_get(arr *l, int n)
{
    char *temp;
    if(n >= l->pz || (n < 0)){
        ON_ERROR("Array read out of bounds\n");
    }
    temp = (char*) (l->data);
    temp = temp + n * l->elsz;
    return (void*) temp;
}

void arr_free(arr **l)
{
    arr* a = *l;
    free(a->data);
    free(a);
    /* Helps to assert that the job has been done.*/
    *l = NULL;
}
