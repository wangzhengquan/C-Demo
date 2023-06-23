/* See COPYRIGHT for copyright information. */

#ifndef COMMON_LOG_H
#define COMMON_LOG_H

#include "usg_common.h"

void _warn(const char*, int, const char*, ...);
void _panic(const char*, int, const char*, ...) __attribute__((noreturn));

#define warn(...) _warn(__FILE__, __LINE__, __VA_ARGS__)
#define panic(...) _panic(__FILE__, __LINE__, __VA_ARGS__)

#define myassert(x)		\
	do { if (!(x)) panic("assertion failed: %s", #x); } while (0)

// static_assert(x) will generate a compile-time error if 'x' is false.
#define mystatic_assert(x)	switch (x) case 0: case (x):

#endif 
