/*
 * Utility functions
 *
 */

#include "util.h"

#include <stdio.h>


/* between: min <= num <= max? */
inline int between (int num, int min, int max) {
    return min <= num && num <= max;
}

/* print_usage: print usage information */
int print_usage (const char *name) {

    printf ("\n Usage: %s -d\n\n"\
        "\t-d [DIFFICULTY]\t\tSet game difficulty note - smaller\n"\
        "\t\t\t\tnumbers mean more challenge!\n\n"\
        " %s -h to display this help.\n\n", name, name);

    return 0;
}

