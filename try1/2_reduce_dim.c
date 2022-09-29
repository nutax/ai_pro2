#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "0_layout.h"


int main();
void read_raw(const char *path, struct sdf *sdf);
void test_raw(struct sdf *sdf);
void stats(struct df *df);

struct sdf _sdf;

int main(){
    read_raw("sdf.o", &_sdf);
    test_raw(&_sdf);
    stats(&(_sdf.train));
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


void fr(int *data, int *buckets, int size);
int mean(int *data, int size);
int sd(int *data, int mean, int size);
int median(int *data, int size);

void stats(struct df *df){
    int i;
    int label_fr[26] = {0};
    int pixel_sd[PIXELS], pixel_mean, pixel_sd_mean, pixel_sd_sd, pixel_sd_median;
    
    fr(df->label, label_fr, df->size);

    for(i = 0; i<PIXELS; i++){
        pixel_mean = mean(df->pixel[i], df->size);
        pixel_sd[i] = sd(df->pixel[i], pixel_mean, df->size);
    }

    pixel_sd_mean = mean(pixel_sd, df->size);
    pixel_sd_sd = sd(pixel_sd, pixel_sd_mean, df->size);
    pixel_sd_median = meadian(pixel_sd, df->size);

    for(int i = 0; i<26; i++) printf("[%d]%d  ", i, label_fr[i]);
    printf("\n\n");
    printf("SD Mean: %d\n", pixel_sd_mean);
    printf("SD SD: %d\n", pixel_sd_sd);
    printf("SD Median: %d\n", pixel_sd_median);
}

void fr(int *data, int *buckets, int size){
    int i;
    for(i = 0; i < size; i++) buckets[data[i]] += 1;
}

int mean(int *data, int size){
    int sum, i;
    sum = 0;
    for(i = 0; i < size; i++) sum += data[i];
    return sum / size;
}

int sd(int *data, int mean, int size){
    int sum, i, diff;
    sum = 0;
    for(i = 0; i < size; i++){
        diff = data[i] - mean;
        sum += diff * diff;
    }
    return (int)(sqrt(sum/size));
}

int median(int *data, int size){
    int buckets[256] = {0}, i;
    for(i = 0; i < size; i++) buckets[data[i]] += 1;
    for(i = 0; i < 255; i++) buckets[i+1] += buckets[i];
    for(i = 0; i < 256; i++) if(buckets[i]>=(size/2)) break;
    return i;
}


