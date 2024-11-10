#include "libMain.h"

// Abre uma janela de diálogo para selecionar um arquivo
// Usa a biblioteca GTK para criar interface gráfica
// Retorna o caminho do arquivo selecionado ou NULL se nenhum arquivo for escolhido
char* abrirDialogoArquivo() {
   char* caminhoArquivo = NULL;

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

// Lê um arquivo texto e carrega seu conteúdo na estrutura de dados
// Cria linhas e palavras dinamicamente conforme lê o arquivo
// Mantém controle de coordenadas (linha e coluna) para cada palavra
void leArquivo(descritor *p){
   p->caminhoArquivo = abrirDialogoArquivo();
   
   char *caminho = p->caminhoArquivo;

   if (caminho != NULL) {
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

           insereLinhaNoDesc(p, linhaAux);

           line[strcspn(line, "\n")] = '\0';
           char *token = strtok(line, " ");

           while(token){
               palavra *palavraAux = (palavra*) malloc(sizeof(palavra));
                 
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
   }else {
       printf("Nenhum arquivo selecionado\n");
   }
}

// Cria uma cópia de backup do arquivo original antes de salvar alterações
// O arquivo de backup tem o mesmo nome do original com "OLD" no final
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

// Salva as alterações feitas na estrutura de dados de volta no arquivo
// Cria um backup do arquivo original antes de salvar
// Mantém a formatação original com palavras separadas por espaço e linhas por \n
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

// Limpa a tela do terminal usando códigos ANSI
void limpaTela(){
   printf("\033[H\033[J"); 
}

// Pausa a execução até que o usuário pressione Enter
// Útil para controle de fluxo do programa
void pressEnter(){
   printf("\nAperte enter para continuar...\n");
   getchar();
   getchar();  
   limpaTela();
}