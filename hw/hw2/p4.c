/*
Axel De Mendoza
MPCS 52015 - Advanced Computer Systems
The University of Chicago
4/12/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned float_bits;

/*
Encode a 32-bit signed int into IEEE Standard 754 floating point representation
- This is done by using bit operations to encode the following bit patterns:
    - Bit 32 (MSB) - Sign bit (0 for positive, 1 for negative)
    - Bits 31-24 - Exponent bits in biased form (e+127 resuling in the range (-126,127
    - Bits 23-1 - Fractional bits which requires rounding for values >= 0x00FFFFFF

- Special cases for 0 and INT_MIN are handled seperately 
*/
float_bits float_i2f(int i){
    // special cases
    if (i == 0){
        // i = 0
        return 0;
    } else if (i == INT_MIN){
        // i = INT_MIN
        float_bits sign = 1 << 31;
        float_bits M = 0;
        float_bits E = (31 + 127) << 23;
        return sign | E | M;
    }

    // sign bit
    float_bits sign = i & 0x80000000; // sets the S bit to 0 or 1

    // exponent bits
    if (sign) {
        // take the 2's compliment
        i = ~i + 1;
    }
    // find the position of the highest 1 bit by bit shifting right until we hit 0
    unsigned exp = 0;
    for (int w = i; w > 0; w = w >> 1){
        exp++;
    }
    exp--; // if 1 in pos 4, we want exp=3
    

    // if exp > 23 then we have discarded bits and have to round
    float_bits M;
    if (exp > 23) {
        // if bits need to be discarded we have to round
        int num_discarded_bits = exp - 23;
        // left shift discarded bits to the 0-7 positions and zero out bits to the left
        // we will be left with discarded bits with a range of 0-255
        // 10000000 (128) is the halfway point. Anything less should round down, anything greater rounds up
        float_bits discarded_bits = (i << (8-num_discarded_bits)) & 0x000000FF; // 8 is the max # of discarded bits
        // right shift fractional bits to the 0-22 position
        M = i >> num_discarded_bits;
        M = M & 0x007FFFFF; // zeros out left 9 bits leaving M in the 0-22 positions
        if (discarded_bits > 128) {
            // round up
            M += 1; // add one to round up
        } else if (discarded_bits < 128) {
            // round down, do nothing
        } else {
            // if discarded_bits = 128 then 0.5 is right in the middle and we round to nearest even
            // if LSB is 1 number is odd and we round up; if 0 then even and we round down
            int LSB = 1 & M;
            if (LSB == 1) {
                M += 1;
            } else {
                // round down to nothing
            }
        }
        // we have to check for overflow and increase EXP if overflow
        if (M > 0x007FFFFF){
            exp += 1;
            M = M & 0x007FFFFF; // reset back to 23 bits if overflow
        }
    } else {
        // EXP <= 23 then no discarded bits and no rounding
        // fractional bits (mantissa)
        M = i << (23-exp);
        M = M & 0x007FFFFF; // zeros out left 9 bits leaving M in the 0-22 positions
    }
    
    // encode the exp bits
    float_bits E = exp + 127; // but exp needs to be encoded as e - 127
    E = E << 23; // sets the exp bits in the 2-9 positions

    return sign | E | M;
}

int main(){
    printf("0: 0x%08x - Expected: 0x00000000\n", float_i2f(0));
    printf("INT_MAX: 0x%08x - Expected: 0x4f000000\n", float_i2f(INT_MAX));
    printf("INT_MIN: 0x%08x - Expected: 0xcf000000\n", float_i2f(INT_MIN));
    printf("-10: 0x%08x - Expected: 0xc1200000\n", float_i2f(-10));
    printf("10: 0x%08x - Expected: 0x41200000\n", float_i2f(10));
    printf("0x00FFFFFF: 0x%08x - Expected: 0x4b7fffff\n", float_i2f(0x00FFFFFF));
    printf("0x01000001: 0x%08x - Expected: 0x4b800000\n", float_i2f(0x01000001));
    printf("0x7FFFFFFF: 0x%08x - Expected: 0x4f000000\n", float_i2f(0x7FFFFFFF));
    printf("0x01000005: 0x%08x - Expected: 0x4b800002\n", float_i2f(0x01000005));
    return EXIT_SUCCESS;
}