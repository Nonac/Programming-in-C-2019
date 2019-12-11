#include "mvm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<assert.h>
#define MAXSIZE 100

/*Init structure, and assert the head.*/
mvm* mvm_init(void)
{
    mvm *head=(mvm *)calloc(1, sizeof(mvm));
    assert(head!=NULL);
    head->head=NULL;
    return head;
}

/* Number of key/value pairs stored 
 * If m is null, return 0.*/
int mvm_size(mvm* m)
{
    if(m==NULL)
    {
        return 0;
    }
    return m->numkeys;
}

/* Insert one key/value pair 
 * Because insertion must have an O(1) time, 
 * I make a head insert to the list.*/
void mvm_insert(mvm* m, char* key, char* data)
{
    mvmcell *p=(mvmcell *)calloc(1, sizeof(mvmcell));
    if (m == NULL || key == NULL || data == NULL) {
        free(p);
        return;
    }
    p->key=(char *)calloc(1, (strlen(key)+1)* sizeof(char));
    p->data=(char *)calloc(1, (strlen(data)+1)* sizeof(char));
    assert(key!=NULL);
    assert(data!=NULL);
    strcpy(p->key,key);
    strcpy(p->data,data);
    p->next=m->head;
    m->head=p;
    m->numkeys++;
}


/* Return the corresponding value for a key 
 * There is an O(n) time in search function.
 * So I have to search list from begin to end.*/
char* mvm_search(mvm* m, char* key)
{
    mvmcell *p=m->head;
    while(p!=NULL)/* Remove one key/value */
    {
        if(!strcmp(p->key,key))
        {
            return p->data;
        }
        p=p->next;
    }
    free(p);
    return NULL;
}

/* Store list as a string "[key](value) [key](value) " etc.  
 * An O(n) time also in print function.
*/

char* mvm_print(mvm* m)
{
    char *str=(char *)calloc(1,1);
    char *temp=(char *)calloc(1,MAXSIZE* sizeof(char));
    mvmcell *p=m->head;
    while (p!=NULL)
    {
        sprintf(temp,"[%s](%s) ",p->key,p->data);
        str=(char *)realloc(str,(strlen(str)+strlen(temp)+1)* sizeof(char));
        strcat(str,temp);
        p=p->next;
    }
    free(temp);
    return str;
}

/* Remove one key/value 
 * There are two steps in the function:
 * 1. If the first mvmcell is the key we are finding ?
 * 2. If not the first, let us go next.
 * In the way, it gets an O(n) time*/
void mvm_delete(mvm* m, char* key)
{
    mvmcell *p,*cur;
    if (m == NULL || key == NULL || key[0] == '\0' || mvm_search(m, key) == NULL)
    {
        return;
    }
    p=m->head;
    cur=m->head;
    if(!strcmp(cur->key,key))
    {
        m->head=m->head->next;
        m->numkeys--;
        free(cur->key);
        free(cur->data);
        free(cur);
        return;
    }
    p=p->next;
    while (p!=NULL)
    {
        if(!strcmp(p->key,key))
        {
            cur->next=p->next;
            m->numkeys--;
            free(p->data);
            free(p->key);
            free(p);
            return;
        }
        cur=cur->next;
        p=p->next;
    }
}

/* Return *argv[] list of pointers to all values stored with key, 
 * n is the number of values. 
 * In order to speed up multisearch to find a vaild key from link list,
 * I use search(). If search function find nothing, then return NULL.
 * If search function find one, then let us find others from begin to end.
*/

char** mvm_multisearch(mvm* m, char* key, int* n)
{
    char **res;
    int index = 0;
    mvmcell *temp = m->head;
    if(m !=NULL&& key!=NULL&& n != NULL)
    {
        *n = 0;
        res = (char **)malloc(sizeof(char *));
    
        while(temp!=NULL){
            if(strcmp(temp->key,key)==0){
                res = (char **)realloc(res,(++(*n))* sizeof(char *));
                res[index++] = temp->data;     
            }
            temp = temp ->next;
        }
        return  res;
    }
    return NULL;
}

void free_linked_list(mvmcell **head)
{
    if(head !=NULL){
        mvmcell *current = *head;
        mvmcell *next;
        while(current != NULL){
            next = current->next;
            free(current->data);
            free(current->key);
            free(current);
            current = next;
        }
        *head = NULL;
    }
}

/* Free & set p to NULL from head*/
void mvm_free(mvm** p)
{
    mvm *a;
   if( p ==NULL || *p == NULL) {
        return;
    }
    a=*p;
    
    free_linked_list(&(a->head));
    free(a);
    *p=NULL;
}
