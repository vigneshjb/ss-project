#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
   char* str;
   int limit = 100;
   
   if (argc != 2)
   {
	  fprintf(stderr, "Usage: %s <name>\n", argv[0]);
	  return -1;
   }
   str = malloc(limit);
   strncat(str, "Hello ", limit-1);
   strncat(str, argv[1], limit-1);

   printf(str);
   printf("\n");
   return 0;
}
