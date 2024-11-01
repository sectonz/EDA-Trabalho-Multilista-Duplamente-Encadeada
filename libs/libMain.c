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

    //salva o caminho do arquivo no descritor
    p->caminhoArquivo = abrirDialogoArquivo();
    
    char *caminho = p->caminhoArquivo;

    if (caminho != NULL) {
        // printf("Arquivo selecionado: %s\n", caminho);
        
        FILE *arq = fopen(caminho,"r");

        if(arq==NULL){
            printf("Erro ao abrir o arquivo!\n");
            free(caminho);
            return;
        }

        char line[254];
        int l = 0;
        int c = 0;
        
        while(fgets(line, sizeof(line), arq) != NULL){

            linha *linhaAux = (linha*)malloc(sizeof(linha));

            linhaAux->palavras = NULL;
            linhaAux->numPalavras = 0;
            linhaAux->cima = NULL;
            linhaAux->baixo = NULL;

            //Insere nova linha no descritor
            insereLinhaNoDesc(p, linhaAux);

            line[strcspn(line, "\n")] = '\0'; //retira o \n do final de cada linha
            char *token = strtok(line, " ");

            //printf("Linha: %d\n", l);

            while(token){
                
                // Aloca nova palavra
                palavra *palavraAux = (palavra*) malloc(sizeof(palavra));
                  
                // Copia a palavra com limite de tamanho
                strncpy(palavraAux->palavra, token, 19);
                palavraAux->palavra[19] = '\0';
                palavraAux->coord.linha = l;
                palavraAux->coord.coluna = c;
                palavraAux->frente = NULL;
                palavraAux->tras = NULL;
            
                insereNaLinha(p, l, palavraAux);
                
                c += strlen(token) + 1;
                token = strtok(NULL, " ");
            }

            l++;
            c = 0;
        }

        fclose(arq);
        free(caminho);
    }else {
        printf("Nenhum arquivo selecionado\n");
    }
}

void criaBackup(descritor *p) {
    
    char *arquivo = p->caminhoArquivo;

    if (strlen(arquivo) == 0) {
        printf("Caminho do arquivo não definido!\n");
        return;
    }
    
    char arquivoBackup[256];
    snprintf(arquivoBackup, sizeof(arquivoBackup), "%sOLD.txt", arquivo);
    
    FILE *arquivoOriginal = fopen(arquivo, "r");
    if (!arquivoOriginal) {
        printf("Erro ao abrir arquivo original para backup!\n");
        return;
    }
    
    FILE *novoBackup = fopen(arquivoBackup, "w");
    if (!novoBackup) {
        printf("Erro ao criar arquivo de backup!\n");
        fclose(arquivoOriginal);
        return;
    }
    
    char buffer[1024];
    size_t bytesLidos;
    
    while ((bytesLidos = fread(buffer, 1, sizeof(buffer), arquivoOriginal)) > 0) {
        fwrite(buffer, 1, bytesLidos, novoBackup);
    }
    
    fclose(arquivoOriginal);
    fclose(novoBackup);
}

void salvaAlteracoes(descritor *p) {
    
    char *arquivo = p->caminhoArquivo; 

    if (!p || !p->multilista) {
        printf("Estrutura vazia, nada para salvar!\n");
        return;
    }
    
    if (strlen(arquivo) == 0) {
        printf("Caminho do arquivo não definido!\n");
        return;
    }

    criaBackup(p);
    
    FILE *novoArquivo = fopen(arquivo, "w");
    if (!novoArquivo) {
        printf("Erro ao abrir arquivo para salvar alterações!\n");
        return;
    }
    
    linha *linhaAtual = p->multilista;
    while (linhaAtual) {
        palavra *palavraAtual = linhaAtual->palavras;
        int ehPrimeira = 1;
        
        while (palavraAtual) {
            if (!ehPrimeira) {
                fprintf(novoArquivo, " ");
            }
            fprintf(novoArquivo, "%s", palavraAtual->palavra);
            ehPrimeira = 0;
            palavraAtual = palavraAtual->frente;
        }
        
        if (linhaAtual->baixo) {
            fprintf(novoArquivo, "\n");
        }
        
        linhaAtual = linhaAtual->baixo;
    }
    
    fclose(novoArquivo);
    printf("Alterações salvas com sucesso!\n");
}

void limpaTela(){
    printf("\033[H\033[J"); 
}

void pressEnter(){
    printf("\nAperte enter para continuar...\n");
    getchar();
    getchar();  
    limpaTela();
}