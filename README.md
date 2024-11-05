<h1 align="center" >Trabalho de Multilista Duplamente Encadeada</h1>
<p align="center">Estrutura de Dados I</p>

<p align="center">
  <a href="#descrição">Descrição</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#estrutura-do-projeto">Estrutura</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#funcionalidades">Funcionalidades</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#compilação">Compilação</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#biblioteca-usadas">Bibliotecas</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#autores">Autores</a>
</p>

</br>

**Professor:** Gilmário Barbosa
</br>
**Alunos:** André Luiz Correia Filho e João Victor Zachêo

## Descrição

Trabalho desenvolvido no curso Bacharelado em Ciência da Computação da [UDESC - CCT](https://www.udesc.br/cct).

O sistema consiste na representação e manipulação de um arquivo de texto em memória através de uma ***Multilista Duplamente Encadeada (multiLDE)***

![representação da multilista duplamente encadeada utilizada no trabalho](https://imgur.com/nI4cQbk.png)

</br>

## Estrutura do Projeto
O projeto foi estruturado separando as funções em bibliotecas para melhor organização. Assim, cada biblioteca ficou responsável por funções específicas utilizadas no decorrer do projeto.

### libEstrutura.h
>Contém as funções responsáveis por manipular a multilista duplamente encadeada.

### libMain.h
>Contém as funções utilizadas na interface, leitura e escrita dos arquivos texto.

Além disso, foram utilizadas 4 *structs* para a construção da multilista que manipula os arquivos. Sendo elas:

**Coordenada**
```C
typedef struct {
    int linha;
    int coluna;
}Coordenada;
```

**Palavra**
```C
typedef struct informacoes{ 
    char palavra[tam_palavra];
    Coordenada coord;
    struct informacoes *frente;
    struct informacoes *tras;
}palavra;
```

**Linha**
```C
typedef struct noMDE{
    palavra *palavras;
    struct noMDE *cima;
    struct noMDE *baixo;
    int numPalavras;
}linha;
```

**Descritor**
```C
typedef struct multilista_duplamente_encadeada{
    int numLinhas;
    linha *multilista;
    char *caminhoArquivo;
}descritor;
```
</br>

## Funcionalidades

### Lê Arquivo
A função carrega um arquivo da memória que o usuário seleciona a partir de uma caixa de diálogo. Ela pega o texto do arquivo e transforma em uma multiLDE separada em linhas e palavras. Além disso, a função vincula a estrutura ao ponteiro do descritor passado como parâmetro.
```C
void leArquivo(descritor *p);
```
</br>

### Criar Backup
Quando chamada, a função cria um arquivo de backup antes das novas alterações serem salvas. O arquivo de backup é nomeado adicionando "OLD" ao final do nome do arquivo original.
```C
void criaBackup(descritor *p);
```
</br>

### Salva Alterações
Salva as alterações feitas no arquivo passando as informações da multiLDE para um arquivo de texto.
```C
void salvaAlteracoes(descritor *p);
```
</br>

### Exibir Texto
Apresenta  ao usuário o texto estruturado na multiLDE.
```C
void exibirTexto(descritor *p);
```
</br>

### Busca Palavra
Procura todas as aparições de uma palavra no texto. A função retorna um vetor de coordenadas em forma de ponteiro contendo as coordenadas de todas as aparições da palavra inserida.
```C
Coordenada* buscaPalavra(descritor *p,char s[],int *numCoords);
```
**Parametros**
>- p - Descritor da multiLDE
>- s[] - Palavra que o usuário deseja procurar
>- numCoords - Quantidade de aparições encontradas

</br>

### Remove Palavra
Remove todas as aparições de uma palavra no texto. Retorna 1 em caso de sucesso e 0 em caso de falha.
```C
int removePalavra(descritor *p,char s[]);
```
</br>

### Remove Coordenada
Remove a palavra localizada nas coordenadas passadas como parâmetro. Retorna 1 em caso de sucesso e 0 em caso de falha.
```C
int removeCoordenada(descritor *p,int l,int coluna);
```
</br>

### Exibir Total de Ocorrências de Palavra
Apresenta a quantidade de aparições de uma palavra no texto.
```C
void exibirTotalOcorrenciasDePalavra(descritor *p,char s[]);
```
</br>

### Exibir Total de Palavras
Apresenta a quantidade de palavras contidas no texto.
```C
void exibirTotalPalavras(descritor *p);
```
</br>

### Editar Palavra
Edita a palavra na coordenada passada como parâmetro.
```C
void editarPalavra(descritor *p,int l,int coluna, char s[]);
```
</br>

### Insere
Insere uma palavra na posição passada como parâmetro.
```C
int insere(descritor *p,int l,int coluna, char s[]);
```
</br>

### Procura Substring
Dada uma substring, a função apresenta as linhas que tenham palavras que contém a substring.
```C
void procuraSubstring(descritor *p, char substr[]);
```
</br>

### Printa Estrutura
Apresenta o texto indicando a quantidade de linhas no texto, a quantidade de palavras em cada linha e as coordenadas das palavras.
```C
void printaEstrutura(descritor *p);
```
</br>

### Reinicia Descritor
Reinicia o descritor, excluindo todas as linhas vinculadas ao ponteiro da *struct*.
```C
void reiniciaDesc(descritor *p);
```
</br>

### Reinicia Linha
Reinicia uma linha, excluindo todas as palavras vinculadas ao ponteiro da *struct*.
```C
void reiniciaLinha(linha *l);
```
</br>

## Compilação
O seguinte comando funciona apenas para a *main*, nao esta incluindo as *libs*. Sendo assim, serve apenas como exemplo de como compilar com as *flags* do *GTK*.

```bash
gcc arquivo.c `pkg-config --cflags --libs gtk+-3.0` && ./a.out
```

Para rodar a aplicação completa, usar sempre o ***make file***!

### Tutorial:

### Compilação normal
```bash
make
```

### Limpar arquivos compilados
```bash
make clean
```

### Recompilar tudo
```bash
make rebuild
```

### Ver informações de debug
```bash
make debug
```

### Apos o make: 
```bash
./programa
```
</br>

## Biblioteca Usadas
Além daquelas criadas para o projeto, algumas bibliotecas foram utilizadas a fim de facilitar a implementação do código. São elas:

- <stdio.h>
- <stdlib.h>
- <string.h>
- <gtk/gtk.h>

</br>

## Autores
| [<img src="https://avatars.githubusercontent.com/u/95360206?v=4" width=120 height=120 style="border-radius:50%"><br><sub>João Zachêo</sub>](https://github.com/joaozacheo) |  [<img src="https://github.com/user-attachments/assets/4912b4cc-623d-4596-a202-4a21bde586cb" height=120 style="border-radius:50%"><br><sub>André Correia</sub>](https://github.com/sectonz) | 
| :---: | :---: |
