//LUCIANO OTONI MILEN [2012079754]
#ifndef LEVENSHTEIN
#define LEVENSHTEIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 6000 //Não ficou claro o tamanho máximo das palavras, então assumi 6000

typedef struct palavra { //A estrutura contém 2 atributos: a palavra em si e o valor da distância de edição da string de consulta
    char txt[MAX_WORD_LENGTH];
    int distancia;
} palavra;

int **criaMatrizDistancia (const int tam_palavra1, const int tam_palavra2);

void liberaMatriz(int **M, const int nItens);

void liberaDicionario(palavra **D, const int nItens);

int distanciaLevenshtein (const char *palavra1, const char *palavra2);

int compara (const void * a, const void * b);

int custo_minimo(int remocao, int insercao, int substituicao);

#endif
