#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float calcula_fit(int a[],float *mat,int items,int n){
    float soma = 0.00,custo;
    int i,j;

    for(i=0;i<items;i++){
        for(j=i+1;j<items;j++){
            soma += *(mat + (a[i])*n + a[j] );
        }
    }
    custo = soma/items;
    return custo;
}
