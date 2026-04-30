#include <stddef.h>
#include <stdint.h>

/* Basic implementation of memset */
void *basic_memset(void *s, int c, size_t n)
{
    size_t cnt = 0;
    unsigned char *schar = s;
    while (cnt < n) {
        *schar++ = (unsigned char) c;
        cnt++;
    }
    return s;
}

/* more efficient version */
void *memset(void *s, int c, size_t n)
{  
    size_t K = sizeof(unsigned long);

    unsigned char *schar = s;
    // check if memory address is aligned on 8 bytes. 
    // write single bytes until the address is aligned
    while (((uintptr_t)schar % K != 0) && (n > 0)) { 
        *schar++ = (unsigned char) c;
        n--;
    }

    // once aligned, begin to write K bytes at a time
    // we can use 4x4 loop unrolling to write 32 bytes per loop
    unsigned long lowest_byte = (unsigned long)(unsigned char)c;
    unsigned clong 0;
    // makes K copies of lowest byte into the clong variable
    for (size_t i = 0; i < K; i++) {
        clong = clong | (lowest_byte << (i * 8));
    }

    // keep 4 counters of the pointer so we can do 4x4 unrolling
    unsigned long *slong_1 = (unsigned long *)schar;
    unsigned long *slong_2 = (unsigned long *)schar+1;
    unsigned long *slong_3 = (unsigned long *)schar+2;
    unsigned long *slong_4 = (unsigned long *)schar+3;

    // write 32 bytes at a time with 4x4 loop unrolling
    while (n >= 4*K) {
        *slong_1++ = clong; // 8 bytes
        *slong_2++ = clong; // 8 bytes
        *slong_3++ = clong; // 8 bytes
        *slong_4++ = clong; // 8 bytes
        n -= 4*K;
    }

    // finish by writing 1 byte at a time until we reach the end of n
    schar = (unsigned char*)slong_1;
    while (n > 0) {
        *schar++ = (unsigned char) c;
        n--;
    }
    return s;
}