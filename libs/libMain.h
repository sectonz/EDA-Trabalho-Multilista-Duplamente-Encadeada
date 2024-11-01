#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <gtk/gtk.h>
#include "libEstrutura.h"

char* abrirDialogoArquivo();

void leArquivo(descritor *p);

void criaBackup(descritor *p);

void salvaAlteracoes(descritor *p);

void limpaTela();

void pressEnter();
