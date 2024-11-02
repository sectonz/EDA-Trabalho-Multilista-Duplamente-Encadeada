#include "../libs/libMain.h"

int main() {
    descritor p;
    p.multilista = NULL;
    p.numLinhas = 0;
    p.caminhoArquivo = NULL;

    int opcao;
    char palavra[tam_palavra];
    int linha, coluna;
    Coordenada coord;

    do {
        limpaTela();    
        printf("\n=== EDITOR DE TEXTO ===\n\n");
        printf("1) Abrir arquivo\n");
        printf("2) Exibir texto\n");
        printf("3) Buscar palavra\n");
        printf("4) Remover palavra\n");
        printf("5) Remover por coordenada\n");
        printf("6) Contar ocorrências de palavra\n");
        printf("7) Contar total de palavras\n");
        printf("8) Editar palavra\n");
        printf("9) Inserir palavra\n");
        printf("10) Buscar substring\n");
        printf("11) Exibir estrutura detalhada\n");
        printf("0) Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                limpaTela();
                if(p.multilista != NULL){
                    reiniciaDesc(&p);
                }
                printf("Selecione o arquivo de texto...\n");
                leArquivo(&p);
                if(p.caminhoArquivo) {
                    printf("Arquivo carregado com sucesso!\n");
                }
                pressEnter();
                break;

            case 2:
                limpaTela();
                printf("\n=== TEXTO ATUAL ===\n\n");
                exibirTexto(&p);
                printf("\n");
                pressEnter();
                break;

            case 3:
                limpaTela();
                printf("Digite a palavra a ser buscada: ");
                scanf("%s", palavra);
                coord = buscaPalavra(&p, palavra);
                if(coord.linha != 0 || coord.coluna != 0) {
                    printf("Palavra encontrada na linha %d, coluna %d\n", 
                           coord.linha, coord.coluna);
                } else {
                    printf("Palavra não encontrada\n");
                }
                pressEnter();
                break;

            case 4:
                limpaTela();
                printf("Digite a palavra a ser removida: ");
                scanf("%s", palavra);
                if(removePalavra(&p, palavra)) {
                    salvaAlteracoes(&p);
                    printf("Palavra removida com sucesso!\n");
                } else {
                    printf("Palavra não encontrada\n");
                }
                pressEnter();
                break;

            case 5:
                limpaTela();
                printf("Digite a linha: ");
                scanf("%d", &linha);
                printf("Digite a coluna: ");
                scanf("%d", &coluna);
                if(removeCoordenada(&p, linha, coluna)) {
                    salvaAlteracoes(&p);
                    printf("Palavra removida com sucesso!\n");
                } else {
                    printf("Coordenada não encontrada\n");
                }
                pressEnter();
                break;

            case 6:
                limpaTela();
                printf("Digite a palavra: ");
                scanf("%s", palavra);
                exibirTotalOcorrenciasDePalavra(&p, palavra);
                printf("\n");
                pressEnter();
                break;

            case 7:
                limpaTela();
                exibirTotalPalavras(&p);
                printf("\n");
                pressEnter();
                break;

            case 8:
                limpaTela();
                printf("Digite a linha: ");
                scanf("%d", &linha);
                printf("Digite a coluna: ");
                scanf("%d", &coluna);
                printf("Digite a nova palavra: ");
                scanf("%s", palavra);
                editarPalavra(&p, linha, coluna, palavra);
                printf("Palavra editada com sucesso!\n");
                salvaAlteracoes(&p);
                pressEnter();
                break;

            case 9:
                limpaTela();
                printf("Digite a linha: ");
                scanf("%d", &linha);
                printf("Digite a coluna: ");
                scanf("%d", &coluna);
                printf("Digite a palavra a ser inserida: ");
                scanf("%s", palavra);
                if(insere(&p, linha, coluna, palavra)) {
                    printf("Palavra inserida com sucesso!\n");
                    salvaAlteracoes(&p);
                } else {
                    printf("Erro ao inserir palavra\n");
                }
                pressEnter();
                break;

            case 10:
                limpaTela();
                printf("Digite a substring a ser buscada: ");
                scanf("%s", palavra);
                procuraSubstring(&p, palavra);
                pressEnter();
                break;

            case 11:
                limpaTela();
                printf("=== ESTRUTURA DETALHADA ===\n\n");
                printaEstrutura(&p);
                pressEnter();
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
                pressEnter();
        }

    } while(opcao != 0);

    // Liberar memória alocada
    if(p.multilista) {
    struct noMDE *linhaAtual = p.multilista;
    struct noMDE *proximaLinha;
    
    while(linhaAtual) {
        struct informacoes *palavraAtual = linhaAtual->palavras;
        struct informacoes *proximaPalavra;
        
        while(palavraAtual) {
            proximaPalavra = palavraAtual->frente;
            free(palavraAtual);
            palavraAtual = proximaPalavra;
        }
        
        proximaLinha = linhaAtual->baixo;
        free(linhaAtual);
        linhaAtual = proximaLinha;
    }
}

    return 0;
}