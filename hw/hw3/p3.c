/*
Axel De Mendoza
MPCS 52015 - Advanced Computer Systems
The University of Chicago
4/12/2026
*/


#include <stdio.h>
#include <stdlib.h>

typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

long switch3(long *p1, long *p2, mode_t action)
{
    // p1 in %rdi
    // p2 in %rsi
    // action in %rdx
    long result = 0;
    switch(action){
        case MODE_A:
            result = *p2; // movq (%rsi), %rax
            *p2 = *p1; // memory to memory move so movq (%rdi), %rdx then movq %rdx, (%rsi)
            break;
        case MODE_B:
            result = *p1; // movq (%rdi), %rax
            result += *p2; // addq (%rsi), %rax
            *p1 = result; // movq %rax, (%rdi)
            break;
        case MODE_C:
            *p1 = 59; // movq $59, (%rdi)
            result = *p2; // movq (%rsi), %rax
            break;
        case MODE_D:
            result = *p2; // movq (%rsi), %rax
            *p1 = result; // movq %rax, (%rdi)
        case MODE_E:
            result = 27; // movl $27, %eax
            break;
        default:
            result = 12; // movl $12, %eax
            break;
    }
    return result;
}

int main(){
    long a = 0x00FF00CC00AA00DD;
    long b = 0x00AA00DD00BB00FF;
    printf("%ld\n", switch3(&a, &b, MODE_A));
}