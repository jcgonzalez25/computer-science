
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFERSIZE   1024

int main(int argc, char *argv[])
{
  ssize_t rv;
  char line[BUFFERSIZE];

  rv = read(0, line, BUFFERSIZE);
  fprintf(stderr,"%d bytes read\n", rv);
  if(rv > 0)
    write(1, line, rv);
}
