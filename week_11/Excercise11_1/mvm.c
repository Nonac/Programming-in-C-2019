#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mvm.h"


mvm *mvm_init(void)
{
    mvm *m = (mvm *)calloc(1,sizeof(mvm));
    m->head = NULL; /*important!*/
    m->numkeys = 0;
    return m;
}

int mvm_size(mvm* m)
{
    if(m == NULL){
        return 0;
    }
    return m->numkeys;
}

/* Insert one key/value pair */
void mvm_insert(mvm* m, char* key, char* data)
{
    mvmcell *cell = (mvmcell *)calloc(1,sizeof(mvmcell));
    if(m==NULL||key == NULL||data ==NULL)
    {
        free(cell);
        return;
    }
    cell->key = (char *)calloc(1,sizeof(char)*(strlen(key)+1));
    cell->data = (char *)calloc(1,sizeof(char)*(strlen(data)+1));

    strcpy(cell->key,key);
    strcpy(cell->data,data);
    cell->next = m->head;
    m->head = cell;
    m->numkeys++;
}

/* Store list as a string "[key](value) [key](value) " etc.  */
char* mvm_print(mvm* m)
{
    if(m != NULL){
        mvmcell *temp = m->head;
        char *str = (char *)calloc(1,sizeof(char));
        int offset = 0;
        
        while(temp != NULL){
            str = (char *)realloc(str,(strlen(str)+strlen(temp->key)+strlen(temp->data)\
            +strlen("[]() "))*sizeof(char)+sizeof(char));
            offset += sprintf(str+offset,"[%s](%s) ",temp->key,temp->data);

            temp = temp->next;
        }
        return str;
    }
    return  NULL;
}

/* Remove one key/value */
void mvm_delete(mvm* m, char* key)
{
    if(m!=NULL&& key != NULL){
        mvmcell *temp = m->head;
        mvmcell *swap;
        if(strcmp(temp->key,key)==0){

            m->head = m->head->next;
            m->numkeys--;
            free(temp->data);
            free(temp->key);
            free(temp);
            return;
        }
        while(temp->next != NULL && strcmp(temp->next->key,key)!=0){ /*cannot exchange*/
            temp = temp->next;
        }
        if(temp->next == NULL){
            return;
        }
        swap = temp->next;
        temp->next = temp->next->next;
        free(swap->data);
        free(swap->key);
        free(swap);
        m->numkeys--;
    }
}

/* Return the corresponding value for a key */
char* mvm_search(mvm* m, char* key)
{
    if(m!=NULL&&key!=NULL){
        mvmcell *temp = m->head;

        while(temp != NULL && strcmp(temp->key,key)!=0 ){/*why???*/
            temp = temp ->next;
        }

        if(temp == NULL){
            return NULL;
        }
        return temp->data;
    }
    return NULL;
}

/* Return *argv[] list of pointers to all values stored with key, n is the number of values */
char** mvm_multisearch(mvm* m, char* key, int* n)
{
    if(m !=NULL&& key!=NULL&& n != NULL){
        char **a;
        int index = 0;
        mvmcell *temp = m->head;
        *n = 0;
        a = (char **)malloc(sizeof(char *));
    
        while(temp!=NULL){
            if(strcmp(temp->key,key)==0){
                (*n)++;
                a = (char **)realloc(a,(*n)* sizeof(char *));
                a[index] = temp->data;
                index ++;      
            }
            temp = temp ->next;
        }
        return  a;
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

/* Free & set p to NULL */
void mvm_free(mvm** p)
{
    mvm *a;
    if( p ==NULL || *p == NULL){
        return;
    }
    a = *p;
    free_linked_list(&(a->head));
    free(a);
    *p =NULL;
}

