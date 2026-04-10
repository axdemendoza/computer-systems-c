#include <stdio.h>
#include <stdlib.h>

int odd_ones(unsigned x){
    /*
    Uses the fact that odd_ones(abcd) = a ^ b ^ c ^ d = (ab ^ cd)^((ab^cd)>>2) (LSB)
    If abcd has odd number of 1s then ab^cd(2 LSB) will also have odd number of ones
    we use this logic on half of the int until 2/2=1 and the LSB will tell us odd/even 1s
    */
    x = x ^ (x >> 16); // XOR on the right half vs the left half (we ignore left half going forward)
    x = x ^ (x >> 8); // XOR on the 8 LSB vs 9-16 LSB bits (we ignore the 16+8 MSB going forward)
    x = x ^ (x >> 4); // XOR on the 4 LSB vs 5-8 LSB (we ignore 16+8+4 MSB going forward)
    x = x ^ (x >> 2); // XOR on the 2 LSB vs 3-4 LSB (we ignore 16+8+4+2 MSB going forward)
    x = x ^ (x >> 1); // xor on the LSB vs 2nd LSB (we ignore all bits except LSB going forward)
    return x & 1 // returns 1 when odd, 0 when even 
}

int main(){
    unsigned x = 0xAAAAAAAB; // odd # 1s
    unsigned y = 0xBBBBBBBB; // even # 1s
    unsigned z = 0x00000001; // odd # 1s
    unsigned a = 0x10000001; // even # 1s
    printf("%d\n", odd_ones(x));
    printf("%d\n", odd_ones(y));
    printf("%d\n", odd_ones(z));
    printf("%d\n", odd_ones(a));
    return EXIT_SUCCESS;
}