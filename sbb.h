#include <sys/time.h>
#include<stdlib.h>
#include<stdio.h>
#define TRUE  1
#define FALSE 0
typedef enum {
  Vertical, Horizontal
} Inclinacao;
typedef struct No* Apontador;
typedef struct No {
  int registro;
  Apontador Esq, Dir;
  Inclinacao BitE, BitD;
} No;

//Transformações de Bayer
void EE(Apontador *Aux);
void ED(Apontador *Aux);
void DD(Apontador *Aux);
void DE(Apontador *Aux);

//Funções de inserção
void IInsere(int registro, Apontador *Aux, Inclinacao *IAp, short *Fim);
void Insere(int registro, Apontador *Aux);

//Função de inicialização
void Inicializa(Apontador *Dicionario);

//Funções de Remoção
void EsqCurto(Apontador *Aux, short *Fim);
void DirCurto(Apontador *Aux, short *Fim);
void Antecessor(Apontador q, Apontador *r, short *Fim);
void IRetira(int registro, Apontador *Aux, short *Fim);
void Retira(int registro, Apontador *Aux);

//Funções de pesquisa
void Pesquisa(int *registro, Apontador *Aux);
void Testa1(Apontador p, int nivel, int *NivelFolhas, short *PrimeiraFolha);
void Testa2(Apontador p, int *NivelFolhas, short *PrimeiraFolha);
void Testa(Apontador Arvore);