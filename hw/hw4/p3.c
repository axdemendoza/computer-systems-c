/*
Axel De Mendoza
MPCS 52015 - Advanced Computer Systems
The University of Chicago
4/19/2026
*/

/*
A. What are the offsets (in bytes) of the following fields:
- Assuming x86-64 architecture
e1.p:    0 bytes
e1.y:    8 bytes
e2.x:    0 bytes
e2.next: 8 bytes
*/

/*
B. How many total bytes does the structure require?
- Assuming x86-64 architecture
16 bytes
Union ele requires 16 bytes because both a pointer and a long are 8 bytes and
the 2 structs in the union share the same memory. Since e1 and e2 are the same
size the max memory that Union ele will require is 16 bytes. 
*/

#include <stdio.h>

union ele {
    struct {
        long *p;
        long y;
    } e1;
    struct {
        long x;
        union ele *next;
    } e2;
};

void proc (union ele * up){
    up->e2.x = *(up->e2.next->e1.p) - (up->e2.next->e1.y);
}

// main function not required for assignment but including for testing purposes
int main()
{
    // Union & struct initialization for test
    union ele mem_0000; // union ele pretending is stored in mem address 0000
    union ele mem_0016; // union ele2 pretending is stored in mem address 0016
    long mem_0032 = 2; // long pretending is stored in mem address 0032
    
    mem_0000.e2.x = 10;
    mem_0000.e2.next = &mem_0016; // next is a pointer that points to mem address 0016
    
    // union ele2 is stored is in mem address 0016
    mem_0016.e1.p = &mem_0032;      // ele2.e1.p is pointer in mem address 0016 pointing to mem address 0032
    mem_0016.e1.y = 1;              // ele2.e1.y is float with value 2 (address 0024)

    proc(&mem_0000);

    printf("%ld\n", mem_0032); // should print 2 because float is not directly modified
    printf("%ld\n", mem_0000.e2.x); // should print 1 bc we set it to 2-1
}