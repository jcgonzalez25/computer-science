
#include <stdio.h>

int cube(int n);   // function prototype
void printsomething(void);
void increment(int *p);

int main(int argc, char *argv[])
{
  int x,y;
  int retval;   // return value\

  printf("? ");
  retval = scanf("%d", &x);
  if(retval != 1){
    fprintf(stderr,"enter a number\n");
    return 0;
  }
  y = cube(x);
  printf("%d cubed is %d\n", x, y);

  printsomething();

  printf("x is now %d\n", x);
  increment(&x);
  printf("x is now %d\n", x);
}
int cube(int n)
{
  int ncubed;

  ncubed = n*n*n;
  return ncubed;
}
void printsomething(void)
{
  printf("Hello, world.\n");
}
void increment(int *p)
{
/*
  *p++ : add one to the value at address p and increment the addr p
  (*p)++; : increment what is at address p]
*/
  (*p)++;
}
