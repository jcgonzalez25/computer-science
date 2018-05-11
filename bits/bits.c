
#include <stdio.h>

void printbinary(char *label, unsigned char c);

int main(int argc, char *argv[])
{
  unsigned char x, y;
  char z;

  x = 34;
  y = 99;
  z = -10;
  printbinary("x = ",x);
  printbinary("y = ",y);
  printbinary("x & y = ", x & y);
  printbinary("x | y = ", x | y);
  printbinary("x ^ y = ", x ^ y);
  printbinary("~ x = ", ~x);
  printbinary("x >> 2 = ", x >> 2);
  printbinary("y << 2 = ", y << 2);
  printbinary("z = ",z);
  printbinary("z >> 2 = ", z >> 2);
}
void printbinary(char *lab, unsigned char c)
{
  unsigned char mask;

  printf("%-12s", lab);
  mask = (1 << 7);
  while( mask != 0 ){
    putchar(' ');
    if((c & mask) == 0)
      putchar('0');
    else
      putchar('1');
    mask = mask >> 1;
  }
  putchar('\n');
}
