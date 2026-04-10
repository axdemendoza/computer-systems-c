#include <stdio.h>
#include <stdlib.h>

int int_shifts_are_arithmetic(){
    int neg_one = -1; // initialize int with all 1 bits
    int shifted = neg_one >> 4; // shift 4 bits to the right
    return shifted == -1; // returns 1 if shifts are arithmetic (retains signed bit); 0 otherwise 
}

int main(){
    int is_arithmetic = int_shifts_are_arithmetic();
    printf("%d\n", is_arithmetic);
    return is_arithmetic;
}