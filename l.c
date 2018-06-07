#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 6000

typedef struct palavra {
  char txt[MAX_WORD_LENGTH];
  int distancia;
} palavra;

int **criaMatrizDistancia (const int tam_palavra1, const int tam_palavra2) {
  int **M = (int**)malloc((tam_palavra1 + 1) * sizeof(int*));
  int i;
  for(i = 0; i <= tam_palavra1; i++){
    M[i] = (int*) malloc((tam_palavra2 + 1) * sizeof(int));
    M[i][0] = i;
  };
  for (i = 0; i <= tam_palavra2; i++) {
      M[0][i] = i;
  };
  return M;
}

int distanciaLevenshtein (const char *palavra1, const char *palavra2){ //https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
    const int tam_palavra1 = strlen(palavra1);
    const int tam_palavra2 = strlen(palavra2);
    int **dMatriz = criaMatrizDistancia(tam_palavra1, tam_palavra2);
    if(!dMatriz){
      printf("Erro ao alocar a matriz");
      return -1;
    }
    int i, j;
    for (i = 1; i <= tam_palavra1; i++) {
        char c1 = palavra1[i-1];
        for (j = 1; j <= tam_palavra2; j++) {
            char c2 = palavra2[j-1];
            if (c1 == c2) {
                dMatriz[i][j] = dMatriz[i-1][j-1];
            }
            else {
                int remocao = dMatriz[i-1][j] + 1;
                int insercao = dMatriz[i][j-1] + 1;
                int substituicao = dMatriz[i-1][j-1] + 1;
                int custo_min = remocao;
                if (insercao < custo_min) {
                    custo_min = insercao;
                }
                if (substituicao < custo_min) {
                    custo_min = substituicao;
                }
                dMatriz[i][j] = custo_min;
            }
        }
    }
    return dMatriz[tam_palavra1][tam_palavra2];
}

int compare (const void * a, const void * b)
{
  palavra **orderA = (palavra **)a;
  palavra **orderB = (palavra **)b;
  if((*orderA)->distancia < (*orderB)->distancia)
    return -1;
  else if((*orderA)->distancia == (*orderB)->distancia)
    return strcmp((*orderA)->txt, (*orderB)->txt);
  else
    return 1;
  // return ( (*orderA)->distancia - (*orderB)->distancia );
}

int main (void) {
    int D, n;
    int i;
    char q[MAX_WORD_LENGTH];

    scanf("%d", &D);
    scanf("%d", &n);
    scanf("%s", q);

    palavra **dicionario = (palavra**) malloc(D * sizeof(palavra*));

    for(i = 0; i < D; i++){
      dicionario[i] = (palavra *) malloc(MAX_WORD_LENGTH * sizeof(palavra));
      scanf("%s", dicionario[i]->txt);
      dicionario[i]->distancia = 0;
    }

    for(i = 0; i < D; i++){
      dicionario[i]->distancia = distanciaLevenshtein (q, dicionario[i]->txt);
    }
    // printf("antes do sort\n");
    // for(i = 0; i < D; i++){
    //   printf("%d\n", dicionario[i]->distancia);
    // }
    qsort(dicionario, D, sizeof(palavra*), compare);
    // printf("depois do sort\n");
    // for(i = 0; i < D; i++){
    //   printf("%d\n", dicionario[i]->distancia);
    // }
    for(i = 0; i < D; i++){
      if(dicionario[i]->distancia <= n)
        printf("%s\n", dicionario[i]->txt);
    }
    return 0;
}
