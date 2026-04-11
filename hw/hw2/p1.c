/*
Axel De Mendoza
MPCS 52015 - Advanced Computer Systems
The University of Chicago
4/12/2026
*/

#include <stdio.h>
#include <stdlib.h>

int is_little_endian(){
    /*
    Initializes a small integer (255)
    255 is stored in memory as FF000... in little endian; 00...FF in big endian
    Get the memory address of the int and cast to a char. This points to the first byte of the int
    If the first byte of the int is non-zero, then our machine is little endian
    */
    int a = 0x00FF; // small 2 byte int that's stored differently in little/big endian
    char * mem = (char*) &a; // cast memory address of "a" as char to just point to the first byte
    return !!(*mem); // *mem is 0 for big endian so !!(*mem) returns 0 for big, 1 for little
}

int main(){
    int little = is_little_endian();
    printf("%d\n", little);
    return little;
}