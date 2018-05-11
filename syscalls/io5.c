
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME 
#define BUFFERSIZE   64

int main(int argc, char *argv[])
{
  ssize_t rv, total;                // integer!
  char buffer[BUFFERSIZE];
  int infd, outfd;

  if(argc != 3){
    fprintf(stderr,"usage: %s oldfile newfile\n", argv[0]);
    return 0;
  }
  
  infd = open(argv[1], O_RDONLY);
  if(infd < 0){
    fprintf(stderr,"unable to open %s for reading\n", argv[1]);
    return 0;
  }
  outfd = open(argv[2], O_WRONLY | O_CREAT, 0644);
  if(outfd < 0){
    fprintf(stderr,"unable to open %s for writing\n", argv[2]);
    return 0;
  }

  total = 0;
  for(;;){
    rv = read(infd, buffer, BUFFERSIZE);
    fprintf(stderr,"read %d bytes\n", rv);
    if(rv > 0){
      write(outfd, buffer, rv);
      total += rv;
    } else
      break;
  }
  close(infd);
  close(outfd);
  fprintf(stderr,"%d bytes read\n", total);
}

