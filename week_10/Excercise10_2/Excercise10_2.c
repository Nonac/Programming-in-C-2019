#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define EMPTY 0
#define ARRDEFSZ 32
#include "set.h"

set* set_init(void)
{
    set* l;
    l = calloc(1,sizeof(set));
    if(l==NULL){
        ON_ERROR("Creation of Set Failed.\n");
    }
    l->ua=arr_init();
    l->sz=EMPTY;
    return l;
}

set* set_copy(set* s)
{
    set* l;
    int i;
    l=set_init();
    if(s!=NULL){
        l->sz=s->sz;
        for(i=0;i<(s->sz);++i){
            l->ua->data[i]=s->ua->data[i];
        }
    }
    return l;
}

set* set_fromarray(arrtype* a, int n)
{
    set* l;
    int i;
    l=set_init();
    if(a!=NULL){
        for(i=0;i<n;++i){
            if(!set_contains(l,a[i])){
                set_insert(l,a[i]);
            }
        }
    }
    return l;
}


void set_insert(set* s, arrtype l)
{

    if(s==NULL){
        return;
    }
    if(set_contains(s,l)){
        return;
    }
    arr_set(s->ua, s->sz, l);
    s->sz=s->sz+1;
}

int set_size(set* s)
{
    int n;
    if(s==NULL){
        n=EMPTY;
    }
    else{
        n=s->sz;
    }
    return n;
}

int set_contains(set* s, arrtype l)
{
    int i;
    if(s==NULL){
        return 0;
    }
    for(i=0;i<(s->sz);++i){
        if(memcmp((s->ua->data)+i,&l,sizeof(arrtype))==0){
            return 1;
        }
    }
    return 0;
}

void set_remove(set* s, arrtype l)
{
    int j,k;
    if(s==NULL){
        return;
    }
    if(!set_contains(s,l)){
        ON_ERROR("not in set\n");
    }
    for(j=k=0;j<(s->sz);++j){
        if(memcmp((s->ua->data+j),&l,sizeof(arrtype))!=0){
            s->ua->data[k]=s->ua->data[j];
            k++;
        }
    }
    s->sz=k;
}


arrtype set_removeone(set* s)
{
    arrtype first;
    if(s==NULL){
        ON_ERROR("EMPTY SET\n");
    }
    first=arr_get(s->ua,0);
    set_remove(s,first);
    return first;
}


set* set_union(set* s1, set* s2)
{
    set* l;
    int n;
    if(s1==NULL){
        l=set_copy(s2);
        return l;
    }
    if(s2==NULL){
        l=set_copy(s1);
        return l;
    }
    l=set_copy(s1);
    for(n=0;n<s2->sz;++n){
        set_insert(l,s2->ua->data[n]);
    }
    return l;
}

set* set_intersection(set* s1, set* s2)
{
    int i;
    set* n;
    n=set_init();
    if((s1==NULL)||(s2==NULL)){
        return n;
    }
    for(i=0;i<s2->sz;++i){
        if(set_contains(s1,s2->ua->data[i])){
            set_insert(n,s2->ua->data[i]);
        }
    }
    return n;

}


void set_free(set** s)
{
    if(s==NULL){
        return;
    }
    if((*s)->ua==NULL){
        free(*s);
        *s=NULL;
        return;
    }
    arr_free(&((*s)->ua));
    free(*s);
    *s=NULL;
}

