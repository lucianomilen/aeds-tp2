#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 6000 //Não ficou claro o tamanho máximo das palavras, então assumi N

typedef struct palavra { //A estrutura contém 2 atributos: a palavra em si e o valor da distância de edição da string de consulta
  char txt[MAX_WORD_LENGTH];
  int distancia;
} palavra;

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
                int custo_min = remocao; //o custo minimo é o menor entre remoção, inserção e substituição
                if (insercao < custo_min) {
                    custo_min = insercao;
                }
                if (substituicao < custo_min) { 
                    custo_min = substituicao;
                }
                dMatriz[i][j] = custo_min; //atribui o custo mínimo na matriz de distâncias para a posição atual de i e j
            }
        }
    }
    return dMatriz[tam_palavra1][tam_palavra2]; //retorna o ÚLTIMO custo calculado, que é de fato o custo de edição
}

int compare (const void * a, const void * b){ //função auxiliar para o qsort()
  palavra **orderA = (palavra **)a;
  palavra **orderB = (palavra **)b;
  if((*orderA)->distancia < (*orderB)->distancia) //se o custo da palavra A for menor que a palavra B
    return -1;
  else if((*orderA)->distancia == (*orderB)->distancia) //se for igual, ordena por ordem alfabética
    return strcmp((*orderA)->txt, (*orderB)->txt);
  else //se custo de B for maior que de A
    return 1;
}

int main (void) {
    int D, n;
    int i;
    char q[MAX_WORD_LENGTH];
    //leitura inicial da entrada
    scanf("%d", &D);
    scanf("%d", &n);
    scanf("%s", q);

    palavra **dicionario = (palavra**) malloc(D * sizeof(palavra*)); //alocação do dicionário
    if(!dicionario)
      return -1; //não foi possível alocar a memória para o dicionário

    for(i = 0; i < D; i++){ //alocação de cada linha do dicionário e inicialização do valor de distância
      dicionario[i] = (palavra *) malloc(MAX_WORD_LENGTH * sizeof(palavra));
      scanf("%s", dicionario[i]->txt);
      dicionario[i]->distancia = 0;
    }

    for(i = 0; i < D; i++){//cálculo da distância de edição utilizando o algoritmo de Wagner-Fischer
      dicionario[i]->distancia = distanciaLevenshtein (q, dicionario[i]->txt);
    } //cada posição do dicionário é uma palavra, e cada palavra tem sua distância de edição da palavra de consulta
    
    qsort(dicionario, D, sizeof(palavra*), compare); //ordenação do dicionário por ordem crescente de distância e alfabética
    
    for(i = 0; i < D; i++){
      if(dicionario[i]->distancia <= n) //n é o valor de distância máximo que uma palavra deve ter para ser exibida
        printf("%s\n", dicionario[i]->txt);
    }
    return 0;
}
