#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static int (*orig_stream_print)(FILE *stream, const char *format, ...) = NULL;
static int (*orig_string_print)(char *string, const char *format, ...) = NULL;

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

void sanitized_stream_print(FILE *stream, const char* format_str, ...){
	int numArgs, i=0, testflg=0;
	char *our_format_str;
	va_list args;

	our_format_str = malloc(strlen(format_str));
	strcpy(our_format_str, format_str);
	
	orig_stream_print = (int (*)(FILE *stream, const char *format, ...))dlsym(RTLD_NEXT, "vfprintf");

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

	va_start(args, format_str);
		(*orig_stream_print)(stream, our_format_str, args);
	va_end(args);
}

void sanitized_string_print(char *string, const char* format_str, ...){
	int numArgs, i=0, testflg=0;
	char *our_format_str;
	va_list args;

	our_format_str = malloc(strlen(format_str));
	strcpy(our_format_str, format_str);
	
	orig_string_print = (int (*)(char *string, const char *format, ...))dlsym(RTLD_NEXT, "vsprintf");

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

	va_start(args, format_str);
		(*orig_string_print)(string, our_format_str, args);
	va_end(args);
}

int printf(const char *format, ...){
	va_list args;
	va_start(args, format);
		sanitized_stream_print(stdout, format, args);
	va_end(args);
	return 1;
}

int fprintf(FILE *stream, const char *format, ...){
	va_list args;
	va_start(args, format);
		sanitized_stream_print(stream, format, args);
	va_end(args);
	return 1;
}

int vprintf(const char *format, va_list ap){
	sanitized_stream_print(stdout, format, ap);
	return 1;
}

int vfprintf(FILE *stream, const char *format, va_list ap){
	sanitized_stream_print(stream, format, ap);
	return 1;
}

int sprintf(char *str, const char *format, ...){
	va_list args;
	va_start(args, format);
		sanitized_string_print(str, format, args);
	va_end(args);
	return 1;
}

int vsprintf(char *str, const char *format, va_list ap){
	sanitized_string_print(str, format, ap);
	return 1;
}