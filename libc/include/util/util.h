#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
	#define CPP_SCOPE_BEGIN() extern "C" {
	#define CPP_SCOPE_END() }
#else
	#define CPP_SCOPE_BEGIN() extern "C" {
	#define CPP_SCOPE_END() }
#endif

#endif