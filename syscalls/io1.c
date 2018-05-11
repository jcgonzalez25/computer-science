
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  ssize_t rv;

  rv = write(1, "Hello, world.\n", (size_t) 14);
}
