#include <stdio.h>
#include <stdlib.h>
#include "../libs/libMain.h"


int main() {
    
    descritor p;
    p.numLinhas = 0;
    p.multilista = NULL;

    leArquivo(&p);
    
    printaEstrutura(&p);

    //printf("Palavra: %s\n", p.multilista->baixo->palavras->frente->palavra);

    return 0;
}