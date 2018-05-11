
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DICTIONARY   "/usr/dict/words"
#define HASHTABSIZE  0x10000   // 65536 = 2 to the 16th power
#define HASHTABMASK  0x0ffff   // 65535 = a lot of 1's in binary
#define BASE              23
#define SHIFT              2

#define K               1024

typedef struct hashtable {
  char *word;
  struct hashtable *link;
} HASHTABENTRY;

HASHTABENTRY *hashtab[HASHTABSIZE];

int hash(char s[]);
HASHTABENTRY *makenode(char s[]);
int find(char s[]);

int main(int argc, char *argv[])
{
  HASHTABENTRY *p;
  FILE *fd;
  char word[K];
  int i,j,k,hashvalue,nwords;

  memset(hashtab, 0, HASHTABSIZE * sizeof(HASHTABENTRY *));

  fd = fopen(DICTIONARY, "r");
  if(fd == NULL)
    exit(0);
  nwords = 0;
  while(fgets(word, K, fd) != NULL){
    word[strlen(word) - 1] = 0;
    hashvalue = hash(word);
    p = makenode(word);
    p->link = hashtab[hashvalue];
    hashtab[hashvalue] = p;
    nwords++;
  }
  fclose(fd);
  for(;;){
    fgets(word, K, stdin);
    word[strlen(word)-1] = 0;
    if(find(word)){
      printf("found\n");
    } else {
      printf("not found\n");
    }
  }
} 
HASHTABENTRY *makenode(char s[])
{
  HASHTABENTRY *p;

  p = malloc(sizeof(HASHTABENTRY));
  p->link = NULL;
  p->word = strdup(s);
  return p;
}
int hash(char s[])
{
  int i, hashvalue;

  hashvalue = 0;
  for(i = 0 ; s[i] != 0 ; i++)
    hashvalue = ((hashvalue * BASE) + s[i]) & HASHTABMASK;
  return hashvalue;
}
int find(char s[])
{
  int hv;
  HASHTABENTRY *p;

  hv = hash(s);
  for(p = hashtab[hv] ; p != NULL ; p = p->link)
    if(strcmp(s, p->word) == 0)
      return 1;
  return 0;
}

