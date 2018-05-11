
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct node {
   int n;
   struct node *link;
} NODE;

NODE *makenode(int n);

int main(int argc, char *argv[])
{
   NODE *head;  // the head of the list
   NODE *tail;  // the head of the list
   NODE *p;     // a pointer to use to modify the list
   int n;

   head = NULL;
   while(scanf("%d", &n) == 1){
      if(head == NULL){
         head = tail = makenode(n);
      } else {
         p = makenode(n);
         tail->link = p;
         tail = tail->link;
      }
   }
   for(p = head ; p != NULL ; p = p->link)
      printf("%d\n", p->n);
}
NODE *makenode(int n)
{
   NODE *tmp;

   tmp = malloc(sizeof(NODE));
   tmp->n = n;
   tmp->link = NULL;
   return tmp;
}

