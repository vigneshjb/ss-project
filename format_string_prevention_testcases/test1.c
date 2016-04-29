#include <stdio.h>

int main(int argc, char** argv)
{
   if (argc != 2)
   {
	  fprintf(stderr, "Usage: %s <name>\n", argv[0]);
	  return -1;
   }
   printf("hello ");
   printf(argv[1]);
   printf("\n");
   return 0;
}
