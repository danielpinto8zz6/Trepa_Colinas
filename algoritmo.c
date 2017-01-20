#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcao.h"
#include "utils.h"

void gera_vizinho(int sol[],int nova_sol[],int items,int n){
    int i,p1,p2,val1,val2;

    for(i=0; i<items; i++)
        nova_sol[i]=sol[i];

    p1 = rand_l_h(0,items-1);
    do
        p2 = rand_l_h(0,items-1);
    while(p2 == p1);

    do
        val1 = rand_l_h(0,n-1);
    while(verificacao(nova_sol,items,val1)==0);

    do
        val2 = rand_l_h(0,n-1);
    while(val2 == val1 || verificacao(nova_sol,items,val2)==0);

    nova_sol[p1] = val1;
    nova_sol[p2] = val2;
}

void gera_vizinho2(int sol[],int nova_sol[],int items,int n){
    int i,p1,p2,p3,p4,val1,val2,val3,val4;

    for(i=0; i<items; i++)
        nova_sol[i]=sol[i];

    p1 = rand_l_h(0,items-1);
    do
        p2 = rand_l_h(0,items-1);
    while(p2 == p1);

    do
        p3 = rand_l_h(0,items-1);
    while(p3 == p1 || p3 == p2);

    do
        p4 = rand_l_h(0,items-1);
    while(p4 == p1|| p4 == p2 || p4 == p3);

    do
        val1 = rand_l_h(0,n-1);
    while(verificacao(nova_sol,items,val1)==0);

    do
        val2 = rand_l_h(0,n-1);
    while(val2 == val1 || verificacao(nova_sol,items,val2)==0);

    do
        val3 = rand_l_h(0,n-1);
    while(val3 == val1 || val3 == val2 ||verificacao(nova_sol,items,val3)==0);

    do
        val4 = rand_l_h(0,n-1);
    while(val4 == val1 || val4 == val2 || val4 == val3 ||verificacao(nova_sol,items,val4)==0);

    nova_sol[p1] = val1;
    nova_sol[p2] = val2;
    nova_sol[p3] = val3;
    nova_sol[p4] = val4;
}

float trepa_colinas(int sol[], float *mat,int items,int num_iter,int n){
    int i;
    int *nova_sol;
    float custo,custo_viz;


    nova_sol = malloc(sizeof(int)*items);
    if(nova_sol == NULL){
        printf("ERRO na alocacao de memoria!\n");
        exit(1);
    }
    custo = calcula_fit(sol,mat,items,n);
    for(i=0;i<num_iter;i++){
        gera_vizinho2(sol,nova_sol,items,n);
        custo_viz = calcula_fit(nova_sol,mat,items,n);

        if(custo_viz >= custo){
            substitui(sol,nova_sol,items);
            custo = custo_viz;
        }

    }
    free(nova_sol);
    return custo;
}


int Recristalizacao(int sol[],float *mat,int items,int n){

    int t,i=0,k=10,custo_viz,custo,iter=0;
    int Tmax = 100, Tmin = 0.01, Fator = 0.99;
    int *nova_sol;

    nova_sol = malloc(sizeof(int)*items);
    if(nova_sol == NULL){
        printf("ERRO na alocacao de memoria!\n");
        exit(1);
    }
    custo = calcula_fit(nova_sol,mat,items,n);
     while(t < Tmax){
            for(i = 0; i< k; i++){
                gera_vizinho(sol,nova_sol,items,n);
                custo_viz = calcula_fit(nova_sol,mat,items,n);

                 if(custo_viz >= custo){
                    substitui(sol,nova_sol,items);
                    custo = custo_viz;
                 }
                   else if(rand_01() <= (exp(custo-custo_viz)/t)){
                        substitui(sol,nova_sol,items);
                        custo = custo_viz;
                    }
                }
                //iter++;
                t = t*Fator;
    }


        free(nova_sol);
        return custo;
}
