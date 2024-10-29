#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libs/libMain.h"


int main() {
    char* caminho = abrirDialogoArquivo();

    if (caminho != NULL) {
        printf("Arquivo selecionado: %s\n", caminho);
        free(caminho);
    } else {
        printf("Nenhum arquivo selecionado\n");
    }
    
    return 0;
}