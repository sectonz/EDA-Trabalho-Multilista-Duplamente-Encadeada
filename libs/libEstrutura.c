#include "libEstrutura.h"

void exibirTexto(descritor *p){
    linha *aux1 = p->multilista; 
    palavra *aux2;

    if(!aux1){
        printf("Arquivo vazio!");
        return;
    }

    while(aux1){
        aux2 = aux1->palavras;
        while(aux2){
            printaPalavra(aux2->palavra);
            printf(" ");    
            aux2 = aux2->frente;
        }
        printf("\n");
        aux1 = aux1->baixo;
    } 
}

Coordenada buscaPalavra(descritor *p, char s[]) {
    linha *aux1 = p->multilista;
    palavra *aux2;
    Coordenada res = {0, 0};
    
    if(!aux1){
        printf("Arquivo vazio!");
        return res;
    }

    while(aux1) {
        aux2 = aux1->palavras;
        while(aux2){    
            if(strcmp(aux2->palavra, s) == 0){
                res.linha = aux2->coord.linha;
                res.coluna = aux2->coord.coluna;
                return res;
            }
            aux2 = aux2->frente;
        }
        aux1 = aux1->baixo;
    }

    return res;
}

int removePalavra(descritor *p,char s[]){

    linha *aux1 = p->multilista;
    palavra *aux2;
    
    if(!aux1){
        printf("Arquivo vazio!");
        return 0;
    }

    while(aux1) {
        aux2 = aux1->palavras;
        while(aux2){    
            if(strcmp(aux2->palavra, s) == 0){
                if(aux->tras != NULL){
                    aux2->tras->frente = aux2->frente;
                }
                if(aux->frente != NULL){
                    aux2->frente->tras = aux2->tras;
                }
                aux2->frente = NULL;
                aux2->tras = NULL;

                return 1;
            }
            aux2 = aux2->frente;
        }
        aux1 = aux1->baixo;
    }

    return 0;
}