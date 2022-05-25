#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(){

    int **a = (int **)malloc(10000*sizeof(int *));
    for( int i = 0; i < 10000; i++ ){
        a[i] = (int *)malloc(10000*sizeof(int));
    }

    for(int i = 0; i < 10000; i++){
        for(int j = 0; j < 10000; j++){
            a[i][j] = i*j;
        }
    }

    for(int i = 0; i < 10000; i++){
        for(int j = 0; j < 10000; j++){
            printf("%d ", a[i][j]);
        }
    }

    for( int i = 0; i < 10000; i++ ){
        free(a[i]);
    }
    free(a);

}