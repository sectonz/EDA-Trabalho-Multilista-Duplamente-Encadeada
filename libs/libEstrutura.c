#include "libEstrutura.h"

void exibirTexto(descritor *p){
    linha *aux1 = p->multilista; 
    palavra *aux2 = aux1->palavras;

    if(!aux1){
        printf("Arquivo vazio!");
        return;
    }

    while(aux1){
        while(aux2){
            printaPalavra(aux2->palavra);
            printf(" ");    
            aux2 = aux2->frente;
        }
        printf("\n");
        aux1 = aux1->baixo;
        aux2 = aux1->palavras;
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

    while (aux1) {
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