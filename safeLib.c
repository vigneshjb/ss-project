#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <stdarg.h>

static int (*orig_printf)(const char *format, ...) = NULL;

int printf(const char *format1, ...)
{
	int numArgs = 2, i=0;
	va_list args;
	orig_printf = (int (*)(const char *format, ...))dlsym(RTLD_NEXT, "printf");

	(*orig_printf)("This is a safe string \n");

	va_start(args, numArgs);
	char *format_str = va_arg(args,char *);
	char *arg_item = va_arg(args,char *);
	va_end(args);

	(*orig_printf)(format_str, arg_item);

	(*orig_printf)("\n\n\n---\n");

	return 1;
}