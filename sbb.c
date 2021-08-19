#include "sbb.h"

//Transformações de Bayer
void EE(Apontador *Aux){
  Apontador Ap1;
  Ap1 = (*Aux)->Esq; 
  (*Aux)->Esq = Ap1->Dir; 
  Ap1->Dir = *Aux;
  Ap1->BitE = Vertical; 
  (*Aux)->BitE = Vertical;
  *Aux = Ap1;
}
void ED(Apontador *Aux){
    Apontador Ap1, Ap2;
    Ap1 = (*Aux)->Esq; 
    Ap2 = Ap1->Dir; 
    Ap1->BitD = Vertical;
    (*Aux)->BitE = Vertical; 
    Ap1->Dir = Ap2->Esq; 
    Ap2->Esq = Ap1;
    (*Aux)->Esq = Ap2->Dir; 
    Ap2->Dir = *Aux; 
    *Aux = Ap2;
}
void DD(Apontador *Aux){
    Apontador Ap1;
    Ap1 = (*Aux)->Dir; 
    (*Aux)->Dir = Ap1->Esq; 
    Ap1->Esq = *Aux;
    Ap1->BitD = Vertical; 
    (*Aux)->BitD = Vertical;
    *Aux = Ap1;
}
void DE(Apontador *Aux){
    Apontador Ap1, Ap2;
    Ap1 = (*Aux)->Dir;
    Ap2 = Ap1->Esq; 
    Ap1->BitE = Vertical;
    (*Aux)->BitD = Vertical; 
    Ap1->Esq = Ap2->Dir;
    Ap2->Dir = Ap1;
    (*Aux)->Dir = Ap2->Esq; 
    Ap2->Esq = *Aux;
    *Aux = Ap2;
}

//Inserção
void Insere(int registro, Apontador *Aux){
    short Fim;
    Inclinacao IAp;
    IInsere(registro, Aux, &IAp, &Fim);
}
void IInsere(int registro, Apontador *Aux, Inclinacao *IAp, short *Fim){
    if (*Aux == NULL) { 
        *Aux = (Apontador)malloc(sizeof(No));
        *IAp = Horizontal;  
        (*Aux)->registro = registro;
        (*Aux)->BitE = Vertical;
        (*Aux)->BitD = Vertical;
        (*Aux)->Esq = NULL;
        (*Aux)->Dir = NULL;
        *Fim = FALSE;
        return;
    }
    if (registro < (*Aux)->registro) { 
        IInsere(registro, &(*Aux)->Esq, &(*Aux)->BitE, Fim);
        if (*Fim) return;
        if ((*Aux)->BitE != Horizontal){ 
            *Fim = TRUE;
            return; 
        }
        if ((*Aux)->Esq->BitE == Horizontal) {
            EE(Aux);
            *IAp = Horizontal;
            return;
        }
        if ((*Aux)->Esq->BitD == Horizontal){
            ED(Aux);
            *IAp = Horizontal;
        }
        return;
    }
    if (registro <= (*Aux)->registro) { 
        printf("Erro: Chave ja esta na arvore\n");
        *Fim = TRUE;
        return;
    }
    IInsere(registro, &(*Aux)->Dir, &(*Aux)->BitD, Fim);
    if (*Fim) return;
    if ((*Aux)->BitD != Horizontal){ 
        *Fim = TRUE;
        return;
    }
    if ((*Aux)->Dir->BitD == Horizontal){
        DD(Aux);
        *IAp = Horizontal;
        return;
    }
    if ((*Aux)->Dir->BitE == Horizontal){
      DE(Aux);
      *IAp = Horizontal;
    }
}

//Inicializando
void Inicializa(Apontador *Dicionario){
    *Dicionario = NULL;
}

//Remoção
void EsqCurto(Apontador *Aux, short *Fim){
    /* Folha esquerda retirada => arvore curta na altura esquerda */
    Apontador Ap1;
    if ((*Aux)->BitE == Horizontal){
        (*Aux)->BitE = Vertical;
        *Fim = TRUE;
        return;
    }
    if ((*Aux)->BitD == Horizontal){
        Ap1 = (*Aux)->Dir;
        (*Aux)->Dir = Ap1->Esq;
        Ap1->Esq = *Aux;
        *Aux = Ap1;
        if ((*Aux)->Esq->Dir->BitE == Horizontal){
            DE(&(*Aux)->Esq);
            (*Aux)->BitE = Horizontal;
        }
        else if ((*Aux)->Esq->Dir->BitD == Horizontal){
            DD(&(*Aux)->Esq);
            (*Aux)->BitE = Horizontal;
        }
        *Fim = TRUE;
        return;
    }
    (*Aux)->BitD = Horizontal;
    if ((*Aux)->Dir->BitE == Horizontal){
        DE(Aux);
        *Fim = TRUE;
        return;
    }
    if ((*Aux)->Dir->BitD == Horizontal){
        DD(Aux);*Fim = TRUE;
    }
}
void DirCurto(Apontador *Aux, short *Fim){
    /* Folha direita retirada => arvore curta na altura direita */
    Apontador Ap1;
    if ((*Aux)->BitD == Horizontal){
        (*Aux)->BitD = Vertical;
        *Fim = TRUE;
        return;
    }
    if ((*Aux)->BitE == Horizontal){
        Ap1 = (*Aux)->Esq;
        (*Aux)->Esq = Ap1->Dir;
        Ap1->Dir = *Aux;
        *Aux = Ap1;
        if ((*Aux)->Dir->Esq->BitD == Horizontal){
            ED(&(*Aux)->Dir);
            (*Aux)->BitD = Horizontal;
        } 
        else if ((*Aux)->Dir->Esq->BitE == Horizontal){
            EE(&(*Aux)->Dir);
            (*Aux)->BitD = Horizontal;
        }
        *Fim = TRUE;
        return;
    }
    (*Aux)->BitE = Horizontal;
    if ((*Aux)->Esq->BitD == Horizontal){
        ED(Aux);
        *Fim = TRUE;
        return;
    }
    if ((*Aux)->Esq->BitE == Horizontal){
        EE(Aux); *Fim = TRUE;
    }
}
void Antecessor(Apontador q, Apontador *r, short *Fim){
    if ((*r)->Dir != NULL){
        Antecessor(q, &(*r)->Dir, Fim);
        if (!*Fim) DirCurto(r, Fim);
        return;
    }
    q->registro = (*r)->registro;
    q = *r;
    *r = (*r)->Esq;
    free(q);
    if (*r != NULL) *Fim = TRUE; 
}
void IRetira(int registro, Apontador *Aux, short *Fim){
    No *Aux2;
    if (*Aux == NULL){
        printf("Chave nao esta na arvore\n");
        *Fim = TRUE;
        return;
    }
    if (registro < (*Aux)->registro){
        IRetira(registro,&(*Aux)->Esq, Fim);
        if (!*Fim) EsqCurto(Aux, Fim);
        return;
    }
    if (registro > (*Aux)->registro){
        IRetira(registro, &(*Aux)->Dir, Fim);
        if (!*Fim) DirCurto(Aux, Fim);
        return;
    }
    *Fim = FALSE; Aux2 = *Aux;
    if (Aux2->Dir == NULL){
        *Aux = Aux2->Esq;
        free(Aux2);
        if (*Aux != NULL) *Fim = TRUE;
        return;
    }
    if (Aux2->Esq == NULL){
        *Aux = Aux2->Dir;
        free(Aux2);
        if (*Aux != NULL) *Fim = TRUE;
        return;
    }
    Antecessor(Aux2, &Aux2->Esq, Fim);
    if (!*Fim) EsqCurto(Aux, Fim); /* Encontrou chave */
}
void Retira(int registro, Apontador *Aux){
    short Fim;
    IRetira(registro, Aux, &Fim);
}
void Pesquisa(int *registro, Apontador *Aux){
    if (*Aux == NULL){
        printf("Erro: Registro nao esta presente na arvore\n");
        return;
    }
    if (*registro < (*Aux)->registro){
        Pesquisa(registro, &(*Aux)->Esq);
        return;
    }
    if (*registro > (*Aux)->registro) Pesquisa(registro, &(*Aux)->Dir);
    else *registro = (*Aux)->registro;
}
