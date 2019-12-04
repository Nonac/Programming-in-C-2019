#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "varr.h"

#define STRSIZE 20

int main(void)
{

   arr *aint;
   arr *astr;
   char str1[STRSIZE];
   char str2[STRSIZE];
   int i, *j;

   printf("Basic Array Tests ... Start\n");

   /* Int test */
   /* Set up empty array */
   aint = arr_init(sizeof(i));
   assert(aint != NULL);
   /* Simple gets & sets */
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

   aint = arr_init(sizeof(i));
   for(i=1; i<10000; i+=100){
      arr_set(aint, i, &i);
      j = arr_get(aint, i);
      assert((*j)==i);
      /* Check getting an unset valie is OK, though
         no particular value can be expected */
      assert(arr_get(aint, i-1) != NULL);
   }
   arr_free(&aint);
   assert(aint==NULL);

   /* String test */
   /* Set up empty array */
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
