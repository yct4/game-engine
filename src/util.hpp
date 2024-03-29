#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <iostream>

#define ERROR_EXIT(...) fprint(stderr, __VA_ARGS__)
#define ERROR_RETURN(R, ...) fprintf(stderr, __VA_ARGS__); return R
#define PRINT(...) cout << __VA_ARGS__ << endl 


#endif // UTIL_H
