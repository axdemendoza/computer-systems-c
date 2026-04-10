#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned float_bits;

float_bits float_i2f(int i){
    // sign bit
    float_bits sign = i & 0x80000000; // sets the S bit to 0 or 1
    printf("%d\n", sign >> 31);
    // exponent bits
    // find the position of the highest 1 bit by bit shifting right until we hit 0
    unsigned exp = 0;
    for (int w = i; w > 0; w = w >> 1){
        exp++;
    }
    exp--; // if 1 in pos 4, we want exp=3
    float_bits E = exp + 127; // but exp needs to be encoded as e - 127
    E = E << 23; // sets the exp bits in the 2-9 positions
    printf("%d\n", exp);

    // fractional bits (mantissa)
    float_bits M = i << (23-exp);
    M = M & 0x007FFFFF; // zeros out left 9 bits leaving M in the 10-32 positions
    printf("%d\n", M);
    
    return sign | E | M;
}

int main(){
    float_bits a = float_i2f(INT_MAX);
    printf("0x%08x\n", a);
    return EXIT_SUCCESS;
}