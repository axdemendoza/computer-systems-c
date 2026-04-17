#ifndef FIND_RANGE_H
#define FIND_RANGE_H

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x);

#endif