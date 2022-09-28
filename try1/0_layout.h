#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#define MAX_CAPACITY 28000
#define PIXELS 784
#define COLS (1+PIXELS)

struct df{
    int size;
    int label[MAX_CAPACITY];
    int pixel[PIXELS][MAX_CAPACITY];
};

struct sdf{
    struct df train;
    struct df test;
};

#endif