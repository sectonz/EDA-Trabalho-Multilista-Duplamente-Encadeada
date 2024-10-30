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

        if(arq==NULL){
            printf("Erro ao abrir o arquivo!\n");
            free(caminho);
            return;
        }

        char line[50];
        int l = 0;
        int c = 0;
        
        while(fgets(line, sizeof(line), arq) != NULL){

            linha *linhaAux = (linha*)malloc(sizeof(linha));

            linhaAux->palavras = NULL;
            linhaAux->numPalavras = 0;
            linhaAux->cima = NULL;
            linhaAux->baixo = NULL;

            line[strcspn(line, "\n")] = '\0'; //retira o \n do final de cada linha
            char *token = strtok(line, " ");


            //printf("Linha: %d\n", l);

            palavra *prevPalavra = NULL;

            while (token) {
                
                // Aloca nova palavra
                palavra *palavraAux = (palavra*)malloc(sizeof(palavra));
                  
                // Copia a palavra com limite de tamanho
                strncpy(palavraAux->palavra, token, 19);
                palavraAux->palavra[19] = '\0';
                palavraAux->coord.linha = l;
                palavraAux->coord.coluna = c;
                palavraAux->frente = NULL;
                palavraAux->tras = prevPalavra; 
                // Liga a palavra na estrutura
                if (prevPalavra) {
                    prevPalavra->frente = palavraAux;
                } else {
                    linhaAux->palavras = palavraAux;
            }
            
            prevPalavra = palavraAux;
            linhaAux->numPalavras++;
            
            c += strlen(token) + 1;
            token = strtok(NULL, " ");
        }
            insereLinhaNoDesc(p, linhaAux);
            l++;
        }
        fclose(arq);
        free(caminho);
    } else {
        printf("Nenhum arquivo selecionado\n");
    }
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

            /*if(linhaAux->palavras == NULL){
                printf("Não existem palavras nessa linha\n");
            }else{
                palavraAux = linhaAux->palavras;

                while(palavraAux != NULL){
                    printf("Palavra: %s | linha: %d | coluna: %d\n", palavraAux->palavra, palavraAux->coord.linha, palavraAux->coord.coluna);
                    palavraAux = palavraAux->frente;
                }
            }*/

            l++;
            linhaAux = linhaAux->baixo;

        }
    }

}