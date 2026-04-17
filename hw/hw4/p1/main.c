#include <stdio.h>
#include "find_range.h"
#include <math.h>

int main()
{
    float my_float = NAN;
    range_t rng = find_range(my_float);
    printf("%d\n", rng);
    return 1;
}