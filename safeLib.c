#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static int (*orig_printf)(const char *format, ...) = NULL;

int countChars( const char* s, char c )
{
	int count = 0, index = 0;
	while(1){
		if (s[index] == '\0')
			break;
		if (s[index] == c)
			count++;
		index++;
	}
	return count;
}

int printf(const char *format_str, ...)
{
	int numArgs, i=0;
	char** p;
	va_list args;
	
	orig_printf = (int (*)(const char *format, ...))dlsym(RTLD_NEXT, "printf");
	numArgs = countChars(format_str, '%');
	p = malloc(numArgs * sizeof(char *));

	(*orig_printf)("\n---\n");

	va_start(args, format_str);
	for (i=0; i<numArgs; i++){
		char *temp = va_arg(args,char *);
		p[i] = malloc(strlen(temp));
		strncpy(p[i], temp, strlen(temp));
	}
	va_end(args);

	(*orig_printf)(format_str, NULL);
	(*orig_printf)("\n");
	for (i=0; i<numArgs; i++){
		(*orig_printf)(p[i]);
		free(p[i]);
	}

	(*orig_printf)("\n---\n");

	free(p);
	(*orig_printf)(" total number of arguments are : %d\n", numArgs);

	return 1;
}