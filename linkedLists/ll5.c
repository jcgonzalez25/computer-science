
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
void deletelist(NODE *h);
int findlongest(NODE *h);

int main(int argc, char *argv[])
{
   NODE *head;  // the head of the list
   NODE *tail;  // the head of the list
   NODE *p;     // a pointer to use to modify the list
   char buffer[K];
   int maxlen;

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
   maxlen = findlongest(head);
   printf("%d\n", maxlen);
   deletelist(head);
   head = NULL;
}
NODE *makenode(char b[K])
{
   NODE *tmp;
   int len;

   tmp = malloc(sizeof(NODE));
#ifdef NOSTRDUP
   len = strlen(b);  
   tmp->word = malloc((len+1)*sizeof(char));
   strcpy(tmp->word, b);
#else
   tmp->word = strdup(b);
#endif
   return tmp;
}
void deletelist(NODE *h)
{
   if(h != NULL){
     free(h->word);        // free the string at this node
     deletelist(h->link);  // free the rest of the list
     free(h);              // free this node
   }
}
int findlongest(NODE *h)
{
   int lenrestoflist;
   int thislen;

   if(h == NULL)
      return 0;
   lenrestoflist = findlongest(h->link);
   thislen = (h->word == NULL) ? 0 : strlen(h->word);
   return (thislen > lenrestoflist) ? thislen : lenrestoflist;
}
