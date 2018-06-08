//LUCIANO OTONI MILEN [2012079754]
#include "levenshtein.h"

int main (void) {
    int D, n;
    int i;
    char q[MAX_WORD_LENGTH];
    //leitura inicial da entrada
    scanf("%d", &D);
    scanf("%d", &n);
    scanf("%s", q);

    palavra **dicionario = (palavra**) malloc(D * sizeof(palavra*)); //alocação do dicionário
    if(!dicionario){
      return -1; //não foi possível alocar a memória para o dicionário
    }
    for(i = 0; i < D; i++){ //alocação de cada linha do dicionário e inicialização do valor de distância
      dicionario[i] = (palavra *) malloc(MAX_WORD_LENGTH * sizeof(palavra));
      scanf("%s", dicionario[i]->txt);
      dicionario[i]->distancia = 0;
    }

    for(i = 0; i < D; i++){//cálculo da distância de edição utilizando o algoritmo de Wagner-Fischer
      dicionario[i]->distancia = distanciaLevenshtein (q, dicionario[i]->txt);
    } //cada posição do dicionário é uma palavra, e cada palavra tem sua distância de edição da palavra de consulta

    qsort(dicionario, D, sizeof(palavra*), compara); //ordenação do dicionário por ordem crescente de distância e alfabética

    for(i = 0; i < D; i++){
      if(dicionario[i]->distancia <= n) //n é o valor de distância máximo que uma palavra deve ter para ser exibida
        printf("%s\n", dicionario[i]->txt);
    }
    liberaDicionario(dicionario, D);
    return 0;
}
