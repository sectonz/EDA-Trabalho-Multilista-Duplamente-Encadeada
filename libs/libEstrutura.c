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
    } 
}