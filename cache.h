
#ifndef CAOSS_CACHE_H
#define CAOSS_CACHE_H

#include "types.h"

/**
 * Setup the cache
 * @param nsets Number of sets
 * @param nways Size of each set, i.e., the number of ways
 * @param blocksize size of the block
 * @return 0, if success, -1 if error
 */
unsigned setup_cache(const unsigned nsets, const unsigned nways, const unsigned blocksize);


/**
 * Add some elements to the cache
 */
void populate_cache(const unsigned line, const unsigned block);

/**
 * Check if the byte with the given address is in the cache
 * @param address The address
 * @return The line in the set where the block is, if the block was found; -1 otherwise
 */
unsigned find_in_cache(const caoss_address address);


#endif