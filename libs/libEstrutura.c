#include "libEstrutura.h"

void exibirTexto(descritor *p){
    linha *aux1 = p->multilista; 
    palavra *aux2;

    if(!aux1 || !p){
        printf("Arquivo vazio!");
        return;
    }

    while(aux1){
        aux2 = aux1->palavras;
        while(aux2){
            printf("%s",aux2->palavra);
            aux2 = aux2->frente;
        }
        printf("\n");
        aux1 = aux1->baixo;
    } 
}
// TODO
//RETORNAR TODAS AS APARICOES DE UMA PALAVRA
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
    
    int retorna=0;

    if(!aux1){
        printf("Arquivo vazio!");
        return retorna;
    }

    while(aux1) {
        aux2 = aux1->palavras;
        while(aux2){    
            if(strcmp(aux2->palavra, s) == 0){
                if(aux2->tras != NULL){
                    aux2->tras->frente = aux2->frente;
                }
                if(aux2->frente != NULL){
                    aux2->frente->tras = aux2->tras;
                }
                aux2->frente = NULL;
                aux2->tras = NULL;

                retorna = 1;
            }
            aux2 = aux2->frente;
        }
        aux1 = aux1->baixo;
    }

    return retorna;
}

int removeCoordenada(descritor *p,int l,int coluna){

    linha *aux1 = p->multilista;
    palavra *aux2;
    
    if(!aux1){
        printf("Arquivo vazio!");
        return 0;
    }

    while(aux1) {
        aux2 = aux1->palavras;
        while(aux2){    
            if(aux2->coord.linha == l && aux2->coord.coluna == coluna){
                if(aux2->tras != NULL){
                    aux2->tras->frente = aux2->frente;
                }
                if(aux2->frente != NULL){
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

void exibirTotalOcorrenciasDePalavra(descritor *p,char s[]){

    linha *aux1 = p->multilista;
    palavra *aux2;
    int ocorrencias=0;

    if(!aux1){
        printf("Arquivo vazio!");
        return;
    }

    while(aux1) {
        aux2 = aux1->palavras;
        while(aux2){    
            if(strcmp(aux2->palavra, s) == 0){
                
                ocorrencias++;

            }
            aux2 = aux2->frente;
        }
        aux1 = aux1->baixo;
    }

    printf("Palavra %s aparece %d vezes!",s,ocorrencias);
}

void exibirTotalPalavras(descritor *p){
        
    linha *aux = p->multilista;
    int total=0;
    while(aux){
        
        total += aux->numPalavras;
        
        aux=aux->baixo;
    }

    printf("Total de palavras do texto: %d",total);

}

int insereNaLinha(descritor *p, int l, palavra *plvr){
    if(l >= p->numLinhas) return 0; //linha inexistente

    linha *aux = p->multilista;

    int i = 0;
    while(i != l){
        aux = aux->baixo;
        i++;
    }

    if(aux->palavras == NULL){
        aux->palavras = plvr;
        aux->numPalavras += 1;
        return 1;
    }

    palavra *aux2 = aux->palavras;

    while(aux2->frente != NULL){
        aux2 = aux2->frente;
    }

    aux2->frente = plvr;
    plvr->tras = aux2;

    aux->numPalavras += 1;

    return 1;
}

int insereLinhaNoDesc(descritor *p, linha *l){
    if(p->multilista == NULL){
        p->multilista = l;
        p->numLinhas += 1;
        return 1;
    }

    linha *aux = p->multilista;

    while(aux->baixo != NULL){
        aux = aux->baixo;
    }

    aux->baixo = l;
    l->cima = aux;

    p->numLinhas += 1;

    return 1;
}
