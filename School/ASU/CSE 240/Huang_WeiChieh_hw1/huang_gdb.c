#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float frand();

int main(int argc, char** argv)
{
  int i;
  for(i = 0; i < 10000; i++)
    {
      int value = (int)(frand() * 10000); //here is missing a parenthesis
      printf("%d\n",value);
    }

  return 0;
}

float frand()
{
  return ((float)rand())/RAND_MAX;
}
