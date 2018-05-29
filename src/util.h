
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define dlog(...)   ({  printf ("Log: "); printf (__VA_ARGS__); })
#define error(...)  ({  fprintf (stderr, "Error: %s - ", __func__); fprintf (stderr, __VA_ARGS__);  })
#define fatal(...)  ({  error (__VA_ARGS__); exit (EXIT_FAILURE);   })


int between (int num, int min, int max);

int print_usage (const char *name);


#endif

