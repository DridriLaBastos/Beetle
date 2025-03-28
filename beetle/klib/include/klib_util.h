#ifndef KLIB_UTIL_H
#define KLIB_UTIL_H

#ifdef __cplusplus
	#define CPP_SCOPE_ENTER() extern "C" {
	#define CPP_SCOPE_EXIT() }
#else
	#define CPP_SCOPE_ENTER()
	#define CPP_SCOPE_EXIT()
#endif

#endif