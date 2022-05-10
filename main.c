#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "cache.h"

int main(int argc , char* argv[]) {

    if (argc < 2) {
        printf ("usage: %s sequence of address to check\n", argv[0]);
        printf ("\t example: %s 10 12 45 23\n", argv[0]);
    }
    
    unsigned number_sets = 1; // associative cache
    unsigned number_lines_per_set = 32;
    unsigned blocksize = 16;

    if (setup_cache(number_sets, number_lines_per_set, blocksize) == -1) {
        perror(CAOSS_ERROR);
        return errno;
    }

    populate_cache(0, 0);
    populate_cache(1, 1);
    populate_cache(2, 2);
    populate_cache(3, 11);
    populate_cache(4, 19);
    populate_cache(5, 26);

    for (int i = 1; i < argc; i++) 
        find_in_cache(atoi(argv[i]));

    return 0;
}



