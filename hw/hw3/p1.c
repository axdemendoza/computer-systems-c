#include <stdio.h>
#include <stdlib.h>

long decode2(long x, long y, long z){
    y = y - z; // subq %rdx, %rsi
    x = y * x; // imulq %rsi, %rdi
    long a = y; // movq %rsi, %rax
    a = a << 63; // salq $63, %rax
    a = a >> 63; // sarq $63, %rax
    a = x ^ a; // xorq %rdi, %rax
    return a; // ret (returns %rax)
}

int main(){
    long x = 0x0000000080000001;
    long y = 0x0000000080000002;
    long z = 0x0000000080000003;
    printf("%ld\n", decode2(x, y, z));
    return EXIT_SUCCESS;
}