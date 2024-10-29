#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

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