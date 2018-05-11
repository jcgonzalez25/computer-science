
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

int hash(char s[]);

int main(int argc, char *argv[])
{
  unsigned short hits[HASHTABSIZE];
  FILE *fd;
  char word[K];
  int i,j,k,hashvalue,nwords,maxhits;

  memset(hits, 0, HASHTABSIZE * sizeof(unsigned short));
  fd = fopen(DICTIONARY, "r");
  if(fd == NULL)
    exit(0);
  nwords = 0;
  while(fgets(word, K, fd) != NULL){
    word[strlen(word) - 1] = 0;
    hashvalue = hash(word);
    hits[hashvalue]++;
    nwords++;
  }
  fclose(fd);
  k = 0; maxhits = 0;
  for(i=0;i<HASHTABSIZE;i++)
    if(hits[i] > 0){
      k++;
      if(hits[i] > maxhits)
        maxhits = hits[i];
    }
  printf("%d/%d %6d   %lf\n", k, nwords, maxhits, (double) k/(double) nwords);
} 
int hash(char s[])
{
  int i, hashvalue;

  hashvalue = 0;
  for(i = 0 ; s[i] != 0 ; i++)
    hashvalue = ((hashvalue * BASE) + s[i]) & HASHTABMASK;
  return hashvalue;
}
