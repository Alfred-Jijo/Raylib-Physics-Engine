#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>

/**
 * Function: array_size
 * 
 * Description: Calculates and returns the size of an array in bytes.
 * 
 * Params:
 *  - arr (any array type): The array whose size needs to be determined.
 * 
 * Returns:
 *  - size_t: The size of the array in bytes.
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#endif // MACROS_H
