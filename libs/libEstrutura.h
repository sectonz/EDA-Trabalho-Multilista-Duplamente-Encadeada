#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "libUtils.h"

#define tam_palavra 20

typedef struct {
    int linha;
    int coluna;
    }Coordenada;


typedef struct informacoes{ 
    char *palavra;
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
    }descritor;

void exibirTexto(descritor *p);

Coordenada buscaPalavra(descritor *p,char s[]);

int removePalavra(descritor *p,char s[]);

int removeCoordenada(descritor *p,int linha,int coluna);

void exibirTotalOcorrenciasDePalavra(descritor *p,char s[]);

void exibirTotalPalavras(descritor *p);

void editaPalavra(descritor *p,int linha,int coluna);

int insere(descritor *p);

void exibirOcorrenciasSubstring(descritor *p,char s[]);

int insereNaLinha(descritor *p, int linha, palavra *palavra);
