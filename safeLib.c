#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>

static int (*orig_printf)(const char *format, ...) = NULL;

int printf(const char *format1, ...)
{

	orig_printf = (int (*)(const char *format, ...))dlsym(RTLD_NEXT, "printf");
	int a =1;
	return (*orig_printf)("%s\n", format1);
}