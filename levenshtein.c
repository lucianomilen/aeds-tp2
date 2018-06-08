//LUCIANO OTONI MILEN [2012079754]
#include "levenshtein.h"

int custo_minimo(int remocao, int insercao, int substituicao){
    int min = remocao;
    if(insercao < min){
      min = insercao;
    }
    if(substituicao < min){
      min = substituicao;
    }
    return min;
}

int compara (const void * a, const void * b){ //função auxiliar para o qsort()
    palavra **orderA = (palavra **)a;
    palavra **orderB = (palavra **)b;
    if((*orderA)->distancia < (*orderB)->distancia) //se o custo da palavra A for menor que a palavra B
      return -1;
    else if((*orderA)->distancia == (*orderB)->distancia) //se for igual, ordena por ordem alfabética
      return strcmp((*orderA)->txt, (*orderB)->txt);
    else //se custo de B for maior que de A
      return 1;
}

int **criaMatrizDistancia (const int tam_palavra1, const int tam_palavra2) {
    int **M = (int**)malloc((tam_palavra1 + 1) * sizeof(int*));
    int i;
    for(i = 0; i <= tam_palavra1; i++){
      M[i] = (int*) malloc((tam_palavra2 + 1) * sizeof(int));
      M[i][0] = i; //parte do algoritmo de Wagner-Fischer envolve zerar as colunas de cada linha e...
    };
    for (i = 0; i <= tam_palavra2; i++) {
        M[0][i] = i; //...as colunas de cada linha
    };
    return M; //retorna um ponteiro para a matriz já alocada dinamicamente
}

void liberaMatriz(int **M, const int nItens){ //autoexplicativa
    for(int i = 0; i <= nItens; i++){
      free(M[i]);
    }
    free(M);
}

void liberaDicionario(palavra **D, const int nItens){ //autoexplicativa
    for(int i = 0; i < nItens; i++){
      free(D[i]);
    }
    free(D);
}

int distanciaLevenshtein (const char *palavra1, const char *palavra2){ //esta função utiliza o algoritmo de Wagner-Fischer para retornar o valor da distância de edição
    const int tam_palavra1 = strlen(palavra1);
    const int tam_palavra2 = strlen(palavra2);
    int **dMatriz = criaMatrizDistancia(tam_palavra1, tam_palavra2);
    if(!dMatriz){
      printf("Erro ao alocar a matriz");
      return -1;
    }
    int i, j;
    for (i = 1; i <= tam_palavra1; i++) {
        char c1 = palavra1[i-1]; //para cada caractere da palavra1 e...
        for (j = 1; j <= tam_palavra2; j++) {
            char c2 = palavra2[j-1]; //...cada char da palavra 2...
            if (c1 == c2) {
                dMatriz[i][j] = dMatriz[i-1][j-1]; //se os chars forem iguais, o custo vai ser relativo ao da diagonal esquerda superior
            }
            else { //se os chars forem diferentes
                int remocao = dMatriz[i-1][j] + 1;//de acordo com o algoritmo, o custo de cada operação é calculado desta forma
                int insercao = dMatriz[i][j-1] + 1;
                int substituicao = dMatriz[i-1][j-1] + 1;
                dMatriz[i][j] = custo_minimo(remocao, insercao, substituicao); //atribui o custo mínimo na matriz de distâncias para a posição atual de i e j
            }
        }
    }
    int dist = dMatriz[tam_palavra1][tam_palavra2];
    liberaMatriz(dMatriz, tam_palavra1);
    return dist; //retorna o ÚLTIMO custo calculado, que é de fato o custo de edição
}
