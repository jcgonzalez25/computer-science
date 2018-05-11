
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define K   1024

typedef struct node {
   char *word;
   struct node *link;
} NODE;

NODE *makenode(char b[]);

int main(int argc, char *argv[])
{
   NODE *head;  // the head of the list
   NODE *tail;  // the head of the list
   NODE *p;     // a pointer to use to modify the list
   char buffer[K];

   printf("buffer in makenode: %p\n", buffer);
   head = NULL;
   while(fgets(buffer,K,stdin) != NULL){
      if(head == NULL){
         head = tail = makenode(buffer);
      } else {
         p = makenode(buffer);
         tail->link = p;
         tail = tail->link;
      }
   }
   for(p = head ; p != NULL ; p = p->link)
      printf("%s", p->word);
}
NODE *makenode(char b[K])
{
   NODE *tmp;
   int len;

   printf("address of len in makenode: %p\n", &len);
   tmp = malloc(sizeof(NODE));
   printf("tmp in makenode: %p\n", tmp);
   len = strlen(b);  
   tmp->word = malloc((len+1)*sizeof(char));
   printf("tmp->word in makenode: %p\n", tmp->word);
   strcpy(tmp->word, b);
   return tmp;
}

