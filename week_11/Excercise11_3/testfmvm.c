#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "fmvm.h"

int main(void)
{

   int i,j;
   mvm *m;
   char* str;
   char** av;
   char animals[5][10] = {"cat",  "dog",  "bird",  "horse", "frog"};
   char  noises[5][10] = {"meow", "bark", "tweet", "neigh", "croak"};

   printf("Basic MVM Tests ... Start\n");

   m = mvm_init();
   assert(m != NULL);
   assert(mvm_size(m)==0);


   for(j=0; j<5; j++){
      mvm_insert(m, animals[j], noises[j]);
      assert(mvm_size(m)==j+1);
      i = strcmp(mvm_search(m, animals[j]), noises[j]);
      assert(i==0);
   }


   str = mvm_print(m);
   i = strcmp(str, "[dog](bark) [bird](tweet) [frog](croak) [cat](meow) [horse](neigh) ");
   assert(i==0);
   free(str);


   assert(mvm_search(m, "fox") == NULL);


   mvm_delete(m, "dog");
   assert(mvm_size(m)==4);
   str = mvm_print(m);
   i = strcmp(str, "[cat](meow) [horse](neigh) [bird](tweet) [frog](croak) ");
   assert(i==0);
   free(str);
   mvm_delete(m, "frog");
   assert(mvm_size(m)==3);
   str = mvm_print(m);
   i = strcmp(str, "[horse](neigh) [bird](tweet) [cat](meow) ");
   assert(i==0);
   free(str);


   mvm_insert(m, "frog", "croak");
   mvm_insert(m, "frog", "ribbit");
   assert(mvm_size(m)==5);
   str = mvm_print(m);
   i = strcmp(str, "[frog](croak) [frog](ribbit) [horse](neigh) [bird](tweet) [cat](meow) ");
   free(str);
   assert(i==0);


   str = mvm_search(m, "frog");
   i = strcmp(str, "croak");
   assert(i==0);

   av = mvm_multisearch(m, "cat", &i);
   assert(i==1);
   i = strcmp(av[0], "meow");
   assert(i==0);
   free(av[0]);
   free(av);
   av = mvm_multisearch(m, "horse", &i);
   assert(i==1);
   i = strcmp(av[0], "neigh");
   assert(i==0);
   free(av[0]);
   free(av);
   av = mvm_multisearch(m, "frog", &i);
   assert(i==2);
   j = strcmp(av[0], "croak");
   i = strcmp(av[1], "ribbit");
   assert((i==0)&&(j==0));
   free(av[0]);
   free(av[1]);
   free(av);


   mvm_delete(m, "frog");
   assert(mvm_size(m)==4);
   mvm_delete(m, "frog");
   assert(mvm_size(m)==3);
   str = mvm_print(m);
   i = strcmp(str, "[bird](tweet) [cat](meow) [horse](neigh) ");
   assert(i==0);
   free(str);


   mvm_insert(m, NULL, "quack");
   assert(mvm_size(m)==3);
   mvm_insert(NULL, "duck", "quack");
   assert(mvm_size(m)==3);
   mvm_insert(m, "duck", NULL);
   assert(mvm_size(m)==3);

   mvm_delete(m, "");
   assert(mvm_size(m)==3);
   mvm_delete(m, NULL);
   assert(mvm_size(m)==3);
   mvm_delete(NULL, "frog");
   assert(mvm_size(m)==3);
   mvm_delete(m, "bird");
   assert(mvm_size(m)==2);
   str = mvm_print(m);
   i = strcmp(str, "[cat](meow) [horse](neigh) ");
   assert(i==0);
   free(str);


   mvm_free(&m);
   assert(m==NULL);
   assert(mvm_size(m)==0);

   printf("Basic MVM Tests ... Stop\n");
   return 0;
}
