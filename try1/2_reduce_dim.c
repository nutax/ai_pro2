#include <stdio.h>
#include <stdlib.h>
#include "0_layout.h"


int main();
void read_raw(const char *path, struct sdf *sdf);
void test_raw(struct sdf *sdf);

struct sdf _sdf;

int main(){
    read_raw("sdf.o", &_sdf);
    test_raw(&_sdf);
    return 0;
}

void read_raw(const char *path, struct sdf *sdf){
    FILE *file;
    file = fopen(path, "rb");    
    if(file == NULL){ printf("Can't open file!"); exit(1); }
    fread(sdf, sizeof(struct sdf), 1, file);
    fclose(file);
}
void test_raw(struct sdf *sdf){
    printf("Train: %d    Test: %d", sdf->train.size, sdf->test.size);
}
