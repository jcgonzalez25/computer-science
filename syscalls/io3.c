
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME 
#define BUFFERSIZE   4096

int main(int argc, char *argv[])
{
  ssize_t rv;                // integer!
  char buffer[BUFFERSIZE];
  int fd;

  fd = open(argv[1], O_RDONLY);
  if(fd < 0){
    fprintf(stderr,"unable to open %s\n", argv[1]);
    return 0;
  }
  rv = read(fd, buffer, BUFFERSIZE);
  fprintf(stderr,"%d bytes read\n", rv);
  if(rv > 0)
    write(1, buffer, rv);
  close(fd);
}
