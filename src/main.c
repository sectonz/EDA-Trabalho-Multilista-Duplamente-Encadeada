#include <stdio.h>
#include <stdlib.h>
#include "../libs/libMain.h"


int main() {
    

    descritor p;
    p.numLinhas = 0;
    p.multilista = NULL;
    // p.caminhoArquivo[0] = '\0';

    leArquivo(&p);
    

    //exibirTexto(&p);
    /*Coordenada c = buscaPalavra(&p, "amigo");
    printf("linha: %d| coluna: %d\n", c.linha, c.coluna);*/

    printaEstrutura(&p);

    insere(&p, 1, 14, "o");

    printaEstrutura(&p);

    //printf("Palavra: %s\n", p.multilista->baixo->palavras->frente->palavra);

    procuraSubstring(&p, "ing");

    return 0;
}