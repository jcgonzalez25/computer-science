
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define  K   1024

typedef struct node {
   int n;
   struct node *link;
} NODE;

NODE *makenode(int n);
NODE *makelist(char *filename);
void printlist(NODE *h);
void deletenode(NODE **headptr, int key);
void deletecommand(NODE **headptr, char *s);
int listlength(NODE *h);

int main(int argc, char *argv[])
{
   NODE *head;  // the head of the list
   char cmd[K];

   head = makelist(argv[1]);
   for(;;){
     printf("? ");
     fgets(cmd, K, stdin);
     switch(cmd[0]){
       case 'l':
         printf("length of list: %d\n", listlength(head));
         break;
       case 'q':
         exit(0);
       case 'p':
         printlist(head);
         break;
       case 'd':
         deletecommand(&head, cmd+1);
         break;
       default: fprintf(stderr,"invalid command: %d\n", cmd[0]);
     }
   }
}
NODE *makelist(char *filename)
{
   NODE *head;  // the head of the list
   NODE *tail;  // the head of the list
   int n;
   FILE *fd;

   fd = fopen(filename, "r");
   if(fd == NULL){
     fprintf(stderr,"unable to open 5s\n", filename);
     return NULL;
   }
   head = NULL;
   while(fscanf(fd,"%d", &n) == 1){
      if(head == NULL){
         head = tail = makenode(n);
      } else {
         tail->link = makenode(n);
         tail = tail->link;
      }
   }
   fclose(fd);
   return head;
}
NODE *makenode(int n)
{
   NODE *tmp;

   tmp = malloc(sizeof(NODE));
   tmp->n = n;
   tmp->link = NULL;
   return tmp;
}
void printlist(NODE *h)
{
  NODE *p;

  for(p = h ; p != NULL ; p = p->link)
    printf("%6d\n", p->n);
}
void deletenode(NODE **headptr, int key)
{
  NODE *p, *previousptr, *h;

  h = *headptr;   // let h be the value stored at address headptr
#ifdef DEBUG
  fprintf(stderr,"deleting %d\n", key);
#endif
  if(h == NULL)
    return;
  if(h->n == key){    // the first node is the one to delete
    p = h;
    *headptr = h->link;
    free(p);
    return;
  }
  while(h != NULL && h->n != key){   // depends on C evaluating left to right, and shortcutting
    previousptr = h;
    h = h->link;
  }
  if(h == NULL)
    return;

/* if I make it to here, previousptr has been assigned a value */

  previousptr->link = h->link;
  free(h);
}
void deletecommand(NODE **headptr, char *s)
{
  int key;

  while(*s == ' ')
    s++;
  if(!isdigit(*s)){
    fprintf(stderr,"usage: d number\n");
    return;
  }
  key = atoi(s);
#ifdef DEBUG
  fprintf(stderr,"key = %d\n", key);
#endif
  deletenode(headptr, key);
}
int listlength(NODE *h)
{
  int n;

  n = 0;
  while(h != NULL){
    n++;
    h = h->link;
  }
  return n;
}
