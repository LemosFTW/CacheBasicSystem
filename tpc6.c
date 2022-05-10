#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "types.h"
#include "cache.h"

/**
 * Number of sets
 *   1 for pure associative caches.
 */
unsigned number_sets;

/**
 * Size of a set. Number of lines or number of ways.
 *      1 for direct-mapped caches; number_sets for pure associative caches.
 */
unsigned number_lines;

/**
 * Size of a block
 */
unsigned block_size;

/**
 * The type of a cache line
 */
typedef struct {
    unsigned char valid;
    unsigned int tag;
} line_t;

/**
 * Type of a set
 */
typedef line_t* set_t;

/**
 * A cache: an array of sets
 */
set_t* cache;


/**
 * Print the contents of a line
 * @param set The set
 * @param line The line
 */
void show_line(const unsigned set, const unsigned line) {
    printf ("\t\tLine %d: valid=%u, tag=%u\n", line, cache[set][line].valid, cache[set][line].tag);
}

/**
 * Get the block in memory that stores the byte with the given address
 * @param addr The address
 */
unsigned get_block(const caoss_address addr) {

    //o numero do bloco vai ser dado por endereco dividido pelo tamanho do bloco
    return addr/block_size ; // TODO
}

/**
 * Get the offset (position) of the byte in the block
 * @param addr The address of the byte
 */
unsigned get_offset(const caoss_address addr) {
    // a posicao vai ser o resto da divisao do endereco pelo tamanho do bloco
    return addr%block_size; // TODO
}

/**
 * Returns the line in the set where the block is, if the block was found; -1 otherwise
 *
 * @param block the number of the block to find
 */
unsigned find_in_set(const unsigned set, const unsigned block) {
    for (int i = 0; i < number_lines ; i++){
       if(cache[set][i].valid && cache[set][i].tag == block) {
       return i;
       }
    }

    // TODO: Find in the cache by checking if the validity bit is 1 and if the tag matches the number of the block
    return -1; // not found
}

/**
 * Check if the byte with the given address is in the cache
 * @param address The address
 * @return The line in the set where the block is, if the block was found; -1 otherwise
 */
unsigned find_in_cache(const caoss_address address){

    unsigned block = get_block(address);
    unsigned offset = get_offset(address);
    unsigned line = find_in_set(0, block);  // We are assuming a pure associative cache. There is only one set: set 0

    if (line == -1) {
        printf ("Address %u: block %u offset %u --> miss\n", address, block, offset);
    }
    else {
        printf ("Address %u: block %u offset %u --> hit, line %d\n", address, block, offset, line);
        show_line(0, line);
    }

    return line;
}


/**
 * Add one element to the cache
 */
void populate_cache(const unsigned line, const unsigned block) {
    cache[0][line].valid = 1;
    cache[0][line].tag = block;
}

/**
 * Setup the cache
 * @param nsets Number of sets
 * @param nlines Number of lines
 * @param blocksize Size of the block
 * @return
 */
unsigned setup_cache(const unsigned nsets, const unsigned nlines, const unsigned blocksize) {
    number_sets = nsets;
    number_lines = nlines;
    block_size = blocksize;

    const unsigned set_size = number_lines * sizeof(line_t);
    cache = malloc(number_sets * sizeof(set_t *));

    if (cache == NULL)
        return errno;

    for (int i = 0; i < number_sets; i++) {
        cache[i] = malloc(set_size);
        for (int j = 0; j < number_lines; j++) 
            cache[i][j].valid = 0;  // mark all entries as invalid
    }

    printf ("Cache: %u sets x %u lines x %u bytes\n", number_sets, number_lines, block_size);

    return 0;
}

