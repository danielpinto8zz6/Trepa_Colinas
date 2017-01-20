#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "utils.h"
#include "TamMat.h"


float *init_data(char *file,int n){
    FILE *f;
    float *p;
    int linha,coluna,i,j;
    float valor;
    int x=20;



    f=fopen(file,"r");
    if(!f){
        printf("Erro no acesso ao ficheiro dos dados!\n");
        exit(1);
    }

    p = malloc(sizeof(int)*n*n);
    if(!p){
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }

    for(i = 0; i<TamMat;i++){
        *(p+(TamMat*i)+i) = 0;

    }
    while(fscanf(f,"%d %d %f",&linha,&coluna,&valor)>0){
        *(p+(linha-1)*TamMat + (coluna - 1)) = valor;
        *(p+(coluna-1)*TamMat + (linha - 1)) = valor;
    }

    /*for(i=0;i<n*n;i++){
            if(i == x){
                putchar('\n');
                x += n;
            }
            printf("%.2f ", *(p+i));

    }
    putchar('\n'); putchar('\n');*/
    return p;

}

int verificacao(int sol[], int items,int x){
    int i;

    for(i=0;i<items;i++){
        if(sol[i] == x)
            return 0;
    }
    return 1;
}

void gera_sol_inicial(int *sol,int items,int n){
    int i,x;

    for(i=0;i<items;i++){
        do{
           x = rand_l_h(0,n-1);
        }while(verificacao(sol,items,x) == 0);
        sol[i] = x;
    }

}

void escreve_sol(int *sol, int items){
    int i;
        for(i=0;i<items;i++)
            printf("%d ",sol[i]);

        putchar('\n');
}

void substitui(int sol[], int nova_sol[],int items){
    int i;

    for(i = 0;i < items;i++)
        sol[i] = nova_sol[i];
}

void init_rand(){
	srand((unsigned)time(NULL));
}

int rand_l_h(int min, int max){
    return min + rand() % (max-min+1);
}

float rand_01(){
	return ((float)rand())/RAND_MAX;
}
