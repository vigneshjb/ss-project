#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
   int output;
   
   if (argc != 1)
   {
	  fprintf(stderr, "Usage: %s\n", argv[0]);
	  return -1;
   }

   printf("hello world%n %s\n", &output, "CSE 545!");
   printf("%d\n", output);

   return 0;
}
