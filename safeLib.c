#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static int (*orig_printf)(const char *format, ...) = NULL;

int nonNformat(char a){
	int res = 1;
	switch(a){
		case 'd': break;
		case 'i': break;
		case 'o': break;
		case 'u': break;
		case 'x': break;
		case 'X': break;
		case 'e': break;
		case 'E': break;
		case 'f': break;
		case 'F': break;
		case 'g': break;
		case 'a': break;
		case 'A': break;
		case 'c': break;
		case 's': break;
		case 'p': break;
		case 'm': break; 
		default: res=0; break;
	}
	return res;
}

int printf(const char *format_str, ...)
{
	int numArgs, i=0, testflg=0;

	char *our_format_str;
	our_format_str = malloc(strlen(format_str));
	strcpy(our_format_str, format_str);

	va_list args;
	
	orig_printf = (int (*)(const char *format, ...))dlsym(RTLD_NEXT, "vprintf");

	// (*orig_printf)("\n---\n");
	puts(format_str);
	while(1){
		if (format_str[i]=='\0'|| i>strlen(format_str))
			break;
		else if(format_str[i]=='%' && format_str[i+1]=='%')
			i++;
		else if (format_str[i]=='%'){
			testflg=1;
		}
		if (testflg==1 && nonNformat(format_str[i])==1){
			testflg=0;
		}
		else if(testflg==1 && format_str[i]=='n'){
			testflg=0; 
			*(our_format_str+i)='p';
		}
		i++;
	}
	puts(our_format_str);

	va_start(args, format_str);
		(*orig_printf)(our_format_str, args);
	va_end(args);
	// (*orig_printf)("\n---\n");
	

	return 1;

}