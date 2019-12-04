#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "varr.h"
#define STRSIZE 20

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
    if (n < 0){
        ON_ERROR("Array accessed with negative index ...\n");
    }
    /* Index greater than current physical size, expand */
    if(n >= l->pz){
        /* Like malloc, but copies original data, then frees original */
        l->data =realloc(l->data, (n+1)*l->elsz);
        if(l->data == NULL){
            ON_ERROR("Resize of Array Failed\n");
        }
        l->pz = n+1;
    }
    temp = (char *) (l->data);
    temp = temp + n * l->elsz;
    memcpy((void*)temp, v, l->elsz);

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
