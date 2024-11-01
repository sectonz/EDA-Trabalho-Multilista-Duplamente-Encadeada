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
            printf("%s ",aux2->palavra);
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
                if(aux1->palavras == aux2){
                    aux1->palavras = aux2->frente;
                }
                aux2->frente = NULL;
                aux2->tras = NULL;

                aux1->numPalavras--;

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
                if(aux1->palavras == aux2){
                    aux1->palavras = aux2->frente;
                }
                aux2->frente = NULL;
                aux2->tras = NULL;

                aux1->numPalavras--;

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

void editarPalavra(descritor *p, int l, int coluna, char s[]){    
    linha *aux1 = p->multilista;

    //procura a linha
    int i = 0;
    while(i != l && aux1 != NULL){
        aux1 = aux1->baixo;
        i++;
    }

    palavra *aux2 = aux1->palavras;

    //procura a coluna
    while(coluna != aux2->coord.coluna && aux2 != NULL){
        aux2 = aux2->frente;
    }

    //atualiza a palavra
    strncpy(aux2->palavra, s, 19);
    aux2->palavra[19] = '\0';

    //Atualiza a coluna das proximas palavras
    int c = coluna;
    while(aux2 != NULL){
        aux2->coord.coluna = c;
        c += strlen(aux2->palavra) + 1;
        aux2 = aux2->frente;
    }
}

int insere(descritor *p,int l,int coluna, char s[]){
    
    if (!p || !p->multilista || l < 0 || coluna < 0 || !s) {
        printf("Parâmetros inválidos\n");
        return 0;
    }
    
    linha *aux1 = p->multilista;

    //procura a linha
    int i = 0;
    while(i != l && aux1 != NULL){
        aux1 = aux1->baixo;
        i++;
    }

    if (!aux1) {
        printf("Linha %d não encontrada\n", l);
        return 0;
    }

    // se não tem palavras na linha ainda
    if (aux1->palavras == NULL) {
        palavra *palavraAux = (palavra*) malloc(sizeof(palavra));
        if (!palavraAux) return 0;
        
        strncpy(palavraAux->palavra, s, 19);
        palavraAux->palavra[19] = '\0';
        palavraAux->coord.linha = l;
        palavraAux->coord.coluna = coluna;
        palavraAux->frente = NULL;
        palavraAux->tras = NULL;
        
        aux1->palavras = palavraAux;
        aux1->numPalavras++;
        return 1;
    }

    palavra *aux2 = aux1->palavras;
    palavra *anterior = NULL;

    // Encontra a posição correta para inserir
    while (aux2 != NULL && aux2->coord.coluna < coluna) {
        anterior = aux2;
        aux2 = aux2->frente;
    }

    // Aloca nova palavra
    palavra *palavraAux = (palavra*) malloc(sizeof(palavra));
    strncpy(palavraAux->palavra, s, 19);
    palavraAux->palavra[19] = '\0';
    palavraAux->coord.linha = l;
    palavraAux->coord.coluna = coluna;
    
    // Insere no início da linha
    if (anterior == NULL) {
        palavraAux->frente = aux1->palavras;
        palavraAux->tras = NULL;
        aux1->palavras->tras = palavraAux;
        aux1->palavras = palavraAux;
    }
    // Insere no final da linha
    else if (aux2 == NULL) {
        palavraAux->frente = NULL;
        palavraAux->tras = anterior;
        anterior->frente = palavraAux;
    }
    // Insere no meio da linha
    else {
        palavraAux->frente = aux2;
        palavraAux->tras = anterior;
        anterior->frente = palavraAux;
        aux2->tras = palavraAux;
    }

    // Atualiza a coluna das próximas palavras
    aux2 = palavraAux->frente;
    int c = coluna + strlen(palavraAux->palavra) + 1;
    while (aux2 != NULL) {
        aux2->coord.coluna = c;
        c += strlen(aux2->palavra) + 1;
        aux2 = aux2->frente;
    }

    aux1->numPalavras++;
    return 1;
}

void procuraSubstring(descritor *p, char substr[]){
    int *listaAparicoes = NULL;
    int qtdLinhas = 0;

    linha *aux1 = p->multilista;
    palavra *aux2 = NULL;
    int i = 0;

    while(aux1 != NULL){
        aux2 = aux1->palavras;
        while(aux2 != NULL){
            if(strstr(aux2->palavra, substr) != NULL){
                if(listaAparicoes == NULL){
                    listaAparicoes = malloc(sizeof(int));
                }else{
                    listaAparicoes = realloc(listaAparicoes, sizeof(int) * (qtdLinhas+1));
                }
                listaAparicoes[qtdLinhas] = i;
                qtdLinhas++;
                break;
            }
            aux2 = aux2->frente;
        }
        aux1 = aux1->baixo;
        i++;
    }

    if(listaAparicoes == NULL){
        printf("Essa substring nao se encontra no texto\n");
    }else{
        printf("A substring aparece nas linhas: ");
        for(i = 0; i < qtdLinhas; i++){
            printf("%d",listaAparicoes[i]);
            if(i != qtdLinhas-1){
                printf(", ");
            }
        }
        printf("\n");
    }

    free(listaAparicoes);
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

void printaEstrutura(descritor *p){
    if(p->numLinhas == 0){
        printf("Nao existem linhas no arquivo!\n");
    }else{

        linha *linhaAux = p->multilista;
        palavra *palavraAux = NULL;

        printf("Numero de linhas: %d\n", p->numLinhas);

        int l = 0;

        while(linhaAux != NULL){
            printf("Linha: %d | NumPalavras: %d\n", l, linhaAux->numPalavras);

            if(linhaAux->palavras == NULL){
                printf("Não existem palavras nessa linha\n");
            }else{
                palavraAux = linhaAux->palavras;

                while(palavraAux != NULL){
                    printf("Palavra: %s | linha: %d | coluna: %d\n", palavraAux->palavra, palavraAux->coord.linha, palavraAux->coord.coluna);
                    palavraAux = palavraAux->frente;
                }
            }

            printf("----------------------------------\n");
            l++;
            linhaAux = linhaAux->baixo;

        }
    }
}

void reiniciaDesc(descritor *p){
    if(p->multilista != NULL){
        linha *aux = p->multilista;

        if(aux->baixo != NULL){
            reiniciaLinha(aux);
            aux = aux->baixo;
            free(aux->cima);
        }

        reiniciaLinha(aux);
        free(aux);

        p->multilista = NULL;
    }
}

void reiniciaLinha(linha *l){
    if(l->palavras != NULL){
        palavra *aux = l->palavras;

        if(aux->frente != NULL){  
            aux = aux->frente;
            free(aux->tras);
        }

        free(aux);

        l->palavras = NULL;
    }
}