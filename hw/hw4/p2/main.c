/*
Axel De Mendoza
MPCS 52015 - Advanced Computer Systems
The University of Chicago
4/19/2026
*/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "find_range.h"

int main()
{
    float my_float;
    range_t expected;
    for (unsigned long bits=0; bits <= 0xFFFFFFFF; bits++){
        memcpy(&my_float, &bits, 4); // copy 4 bytes from mem address of bits, copy into float for float representation of bits
        
        unsigned exp_bits = (bits >> 23) & 0x000000FF;
        unsigned frac_bits = (bits & 0x007FFFFF);
        unsigned sign_bit = (bits >> 31) & 1;
        // get expected return values
        if ((exp_bits == 0x000000FF) && (frac_bits != 0x00000000)){ // if Nan
            expected = OTHER;
        } else if ((exp_bits == 0) && (frac_bits == 0)){ // if zero
            expected = ZERO;
        } else if (sign_bit == 0){
            expected = POS;
        } else if (sign_bit == 1){
            expected = NEG;
        } else {
            expected = OTHER;
        }

        range_t actual = find_range(my_float);
        if (actual != expected){
            printf("Failed on %ld", bits);
            assert(actual == expected);
        }
    }

    
    printf("All tests passed!\n");
    return 1;
}