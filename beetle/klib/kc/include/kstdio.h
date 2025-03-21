#ifndef KERNEL_STDIO_H
#define KERNEL_STDIO_H

#ifdef __cplusplus
	extern "C" {
#endif

int kprintf (const char* format, ...);
int kputs (const char* s);
int kputchar (const int c);

#ifdef __cplusplus
	}
#endif

#endif