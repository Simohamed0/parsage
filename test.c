#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(){

    int *a = (int *)malloc(1000000000*sizeof(int ));
    
    
    for(int j = 0; j < 1000000000; j++){
        a[j] = j;
    }

    for(int j = 0; j < 1000000000; j++){
        printf("%d ", a[j]);
    }
    

    
    free(a);

}