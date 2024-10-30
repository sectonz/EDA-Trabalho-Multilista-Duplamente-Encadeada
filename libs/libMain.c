#include "libMain.h"

char* abrirDialogoArquivo() {
    char* caminhoArquivo = NULL;

    // Implementação GTK (Linux/Unix)
    gtk_init(NULL, NULL);
    
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Abrir Arquivo",
                                                   NULL,
                                                   GTK_FILE_CHOOSER_ACTION_OPEN,
                                                   "_Cancelar", GTK_RESPONSE_CANCEL,
                                                   "_Abrir", GTK_RESPONSE_ACCEPT,
                                                   NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        caminhoArquivo = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }
    
    gtk_widget_destroy(dialog);
    while (gtk_events_pending()) gtk_main_iteration();

    return caminhoArquivo;
}

void leArquivo(descritor *p){

    char* caminho = abrirDialogoArquivo();

    if (caminho != NULL) {
        // printf("Arquivo selecionado: %s\n", caminho);
        
        FILE *arq = fopen(caminho,"r");

        char line[50];
        int l = 0;
        int c = 0;
        
        while(fgets(line, sizeof(line), arq) != NULL){

            linha linhaAux;
            linhaAux.palavras = NULL;
            linhaAux.numPalavras = 0;

            //insereLinhaNoDesc(p);

            line[strcspn(line, "\n")] = '\0'; //retira o \n do final de cada linha

            char *token = strtok(line, " ");

            printf("Linha: %d\n", l);

            do{
                palavra palavraAux;
                palavraAux.palavra = token;
                palavraAux.coord.linha = l;
                palavraAux.coord.coluna = c;

                insereNaLinha(p, l, &palavraAux);

                printf("Palavra: %s | linha: %d | coluna: %d\n", palavraAux.palavra, palavraAux.coord.linha, palavraAux.coord.coluna);

                c += strlen(token) + 1; //idxProxPalavra = tamPalavraAtual + espaço

                token = strtok(NULL, " ");
            }while(token);

            l++;
            c = 0;
            printf("\n");

            free(token);
        }

        free(caminho);
    } else {
        printf("Nenhum arquivo selecionado\n");
    }

}