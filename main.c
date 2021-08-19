#include <stdio.h>
#include <stdlib.h>
#include "sbb.h"
void main(){
    Apontador  Dicionario;
    int x;
    int  vetor[10];
    int i, j, k, n;
    n=5;
    Inicializa(&Dicionario);
    for(i=0;i<10;i++){
        vetor[i] = i+1;
    }
    for (i = 0; i < 10; i++){
        x = vetor[i];
        Insere(x, &Dicionario);
        printf("Inseriu chave: %d\n", x);
    }
    Retira(5,&Dicionario);


}