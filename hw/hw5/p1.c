#include <stdio.h>
#include <stdlib.h>


typedef long data_t;

/* Create abstract data type for vector */
typedef struct {
    long len;
    data_t *data;
} vec_rec;

typedef vec_rec *vec_ptr;

data_t *get_vec_start(vec_ptr v)
{
    return v->data;
}

long vec_length(vec_ptr v)
{
    return v->len;
}

void inner4(vec_ptr u, vec_ptr v, data_t * dest)
{
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;

    for (i = 0; i < length; i++) {
        sum = sum + udata[i] * vdata[i];
    }
    *dest = sum;
}


/*
Let's assume we don't know the length of our vectors at compile time. 

This is a 6x6 unrolled version of the inner4 function. The first 6 means we
process 6 elements per loop iteration and the 2nd 6 means we have 6 accumulators.

Our loop does the following:
    A. multiply two long ints from memory
    B. sum the result of A with our total sum in register
    C. Do A-B 6x 
    D. increment i by 6 and compare it with limit
    E. If i is < limit, continue with next 6 values in the array. 

As we can see operation B depends on operation A being completed, and 
operation E depends on operation D being completed. 
So even though we are reducing the number of times we do steps D-E and branch
by a factor of 6, we are still limited by the fact that operation B depends on operation A. 
The factor that limits performance to a CPE of 1.0 is that a multiplication
has an issue value of 1 and a capacity of 1. Issue indicates the minimum number
of clock cycles between two independent operations. The capacity indicates how
many of these operations can be done simultaniously. So even though one iteration
of our loop can line up 6 multiplication instructions, the CPU can
only output 1 at a time. 

The benefit of loop unrolling here is that we don't have to wait for D and E to finish
running before loading the next set of instructions and increasing the throughput of 
our loop.
*/
void inner6(vec_ptr u, vec_ptr v, data_t * dest)
{
    long i;
    long length = vec_length(u);
    long limit = length - 5;
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum1 = (data_t) 0;
    data_t sum2 = (data_t) 0;
    data_t sum3 = (data_t) 0;
    data_t sum4 = (data_t) 0;
    data_t sum5 = (data_t) 0;
    data_t sum6 = (data_t) 0;
    data_t sum = (data_t) 0;

    /* limit makes sure we don't go out of bounds. but doesn't always finish all elements
    len = 4 -> limit = -1 -> 0 elements computed
    len = 7 -> limit = 2 -> 6 elements computed
    len = 12 -> limit = 7 -> 12 elements computed
    */
    for (i = 0; i < limit; i+=6) {
        sum1 = sum1 + udata[i] * vdata[i];
        sum2 = sum2 + udata[i+1] * vdata[i+1];
        sum3 = sum3 + udata[i+2] * vdata[i+2];
        sum4 = sum4 + udata[i+3] * vdata[i+3];
        sum5 = sum5 + udata[i+4] * vdata[i+4];
        sum6 = sum6 + udata[i+5] * vdata[i+5];
    }

    /* run from last computed value to the end of the array */
    for (; i < length; i++) {
        sum = sum + udata[i] * vdata[i];
    }

    *dest = sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum;
}

int main()
{
    data_t my_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vec_ptr my_vector = malloc(sizeof(vec_rec));
    my_vector->data = my_data;
    my_vector->len = 10;
    
    data_t your_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vec_ptr your_vector = malloc(sizeof(vec_rec));
    your_vector->data = your_data;
    your_vector->len = 10;

    data_t result_4 = 0;
    inner4(my_vector, your_vector, &result_4);

    data_t result_6 = 0;
    inner4(my_vector, your_vector, &result_6);

    printf("Inner4 result: %ld\n", result_4);
    printf("Inner6 result: %ld\n", result_6);

    return 1;
}

