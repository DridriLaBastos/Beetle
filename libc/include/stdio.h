#ifndef BEETLE_STDIO_H
#define BEETLE_STDIO_H

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* format, ...) __attribute__((format(printf,1,2))) ;

int puts(const char* s);
int putchar(int c);

#ifdef __cplusplus
}
#endif

#endif