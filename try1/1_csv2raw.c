#include <stdio.h>
#include <stdlib.h>
#include "0_layout.h"

int main();
void read_csv(const char *path, struct df *df);
void write_raw(const char *path, struct sdf *sdf);


struct sdf _sdf;

int main(){
    read_csv("../input/train.csv", &(_sdf.train));
    read_csv("../input/test.csv", &(_sdf.test));
    write_raw("sdf.o", &_sdf);
    return 0;
}


void read_csv(const char *path, struct df *df){
    int i, j, result;
    FILE *file;
    char c, str[4];

    file = fopen(path, "r");    
    if(file == NULL){ printf("Can't open file!"); exit(1); }

    i = j = 0;
    while ((c = getc(file)) != '\n');

     do {
        result = fscanf(file, "%3[^,\n]", str);

        if(result == 0)
        {
            c = getc(file);
            if(c == '\n'){
                i += 1; j = 0;
            }else if(c == '\n'){
                j += 1;
            }
        }
        else
        {
            if(j == 0) df->label[i] = atoi(str);
            else df->pixel[i][j-1] = atoi(str);
        }

    } while(result != EOF);
    df->size = i;
    fclose(file);
}

void write_raw(const char *path, struct sdf *sdf){
    FILE *file;
    file = fopen(path, "wb");    
    if(file == NULL){ printf("Can't open file!"); exit(1); }
    fwrite(sdf, sizeof(struct sdf), 1, file);
    fclose(file);
}