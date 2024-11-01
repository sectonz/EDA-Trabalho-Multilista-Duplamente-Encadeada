#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libUtils.h"

#define tam_palavra 45

typedef struct {
    int linha;
    int coluna;
    }Coordenada;


typedef struct informacoes{ 
    char palavra[tam_palavra];
    Coordenada coord;
    struct informacoes *frente;
    struct informacoes *tras;
    }palavra;

typedef struct noMDE{
    palavra *palavras;
    struct noMDE *cima;
    struct noMDE *baixo;
    int numPalavras;
    }linha;

typedef struct multilista_duplamente_encadeada{
    int numLinhas;
    linha *multilista;
    char *caminhoArquivo;
    }descritor;

void exibirTexto(descritor *p);

Coordenada buscaPalavra(descritor *p,char s[]);

int removePalavra(descritor *p,char s[]);

int removeCoordenada(descritor *p,int l,int coluna);

void exibirTotalOcorrenciasDePalavra(descritor *p,char s[]);

void exibirTotalPalavras(descritor *p);

void editarPalavra(descritor *p,int l,int coluna, char s[]);

void exibirOcorrenciasSubstring(descritor *p,char s[]);

int insere(descritor *p,int l,int coluna, char s[]);

void procuraSubstring(descritor *p, char substr[]);

int insereNaLinha(descritor *p, int l, palavra *plvr);

int insereLinhaNoDesc(descritor *p, linha *l);

void printaEstrutura(descritor *p);