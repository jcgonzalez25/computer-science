

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILENAME "data"

typedef struct dnode {
  int x;
  struct dnode *forward, *reverse;
} DNODE;

DNODE *makenode(int n);
void deletenode(DNODE **hptr, DNODE **tptr, int key);

int main(int argc, char *argv[])
{
  DNODE *head, *tail, *p;
  FILE *fd;
  int n;

  fd = fopen(FILENAME, "r");
  if(fd == NULL){
    fprintf(stderr,"unable to open %s\n", FILENAME);
    exit(0);
  }
  fscanf(fd, "%d", &n);
  head = tail = makenode(n);
  while(fscanf(fd, "%d", &n) == 1){
    p = makenode(n);
    tail->forward = p;
    p->reverse = tail;
    tail = p;
  }

  for(;;){

// print list if forward order

    for(p = head ; p != NULL ; p = p->forward)
      printf("%4d", p->x);
    printf("\n");

// print list if reverse order

    for(p = tail ; p != NULL ; p = p->reverse)
      printf("%4d", p->x);
    printf("\n");

    printf("? ");
    if(scanf("%d", &n) != 1)
      break;
    deletenode(&head, &tail, n);
  }
}
DNODE *makenode(int n)
{
  DNODE *p;

  p = malloc(sizeof(DNODE));
  p->x = n;
  p->forward = p->reverse = NULL;
  return p;
}
void deletenode(DNODE **hptr, DNODE **tptr, int key)
{
  DNODE *h, *t;  // copies of head and tail (from mail)
  DNODE *p;

  h = *hptr;   // h = the content of address hptr
  t = *tptr;   // t = the content of address tptr
  printf("hptr = %p\n", hptr);  // 0x400000 stack value
  printf("tptr = %p\n", tptr);
  printf("h = %p\n", h);        // 0x600000 heap variable
  printf("t = %p\n", t);
  printf("content h = %d\n", (int *)h);        // 0x600000 heap variable
  printf("content t = %d\n", (int *)t);
}
