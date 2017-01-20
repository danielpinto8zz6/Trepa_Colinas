#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include "algoritmo.h"
#include "funcao.h"
#include "TamMat.h"

#define runs 30
#define items 7
#define num_iter 10000

int main(int argc, char *argv[])
{
    char nome_fich[100];
    float custo, best_custo;
    float *mat,mbf=0.0;
    int *sol;
    int *best;
    int n = 20,i,pos;

    //if(argc == )
    printf("Nome do ficheiro: ");
    scanf("%s[^\n]", nome_fich);

    init_rand();

    mat = init_data(nome_fich,TamMat);
    sol = malloc(sizeof(int) * items);
    best = malloc(sizeof(int)* items);

    if(sol == NULL || best == NULL){
        printf("ERRO na alocacao de memoria!\n");
        exit(1);
    }

        for(i = 0; i < runs; i++){
            gera_sol_inicial(sol,items,TamMat);
            escreve_sol(sol,items);

            custo = trepa_colinas(sol,mat,items,num_iter,TamMat);
            //custo = Recristalizacao(sol,mat,items,TamMat);

            printf("Repeticao %d\n",i);
            escreve_sol(sol,items);
            printf("Custo final: %.2f\n\n", custo);
            mbf += custo;
            if(i==0 || best_custo < custo)
                {
                    best_custo = custo;
                    pos = i;
                    substitui(best, sol,items);
                }

        }

    printf("\n\nMBF: %.2f\n", mbf/i);
    printf("\nMelhor solucao encontrada\n");
    escreve_sol(best,items);
	printf("Custo final: %.2f\nPos: %d\n", best_custo,pos);
    free(mat);
    free(sol);
	free(best);
    return 0;
}
