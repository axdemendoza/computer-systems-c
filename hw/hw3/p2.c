#include <stdlib.h>
#include <stdio.h>

long cread_alt(long *xp){
    long zero = 0;
    long *p = xp ? xp : &zero;
    
    return *p;
}

int main(){
    long my_long = 6111994;
    printf("%ld\n", cread_alt(&my_long));
    return EXIT_SUCCESS;
}