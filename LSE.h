#include<stdio.h>
#include <string.h>

struct s_InfoNo{
char nome[20];
int codigo;
int preco;
};

typedef struct s_InfoNo InfoNo;

struct s_PtNo{
InfoNo info;
struct s_PtNo * prox;
};

typedef struct s_PtNo pNodoLista;


pNodoLista* inicializa(void);

void imprime(pNodoLista* ptLista);

pNodoLista* insereCrescente(pNodoLista* ptLista, InfoNo dados);

pNodoLista* InsereInicio(pNodoLista* PtLista, InfoNo info);

pNodoLista* InsereFim(pNodoLista* PtLista, InfoNo info);

pNodoLista* destroi(pNodoLista* ptLista);

pNodoLista* remover(pNodoLista* ptLista, char titulo[]);

int TamanhoLista(pNodoLista* ptLista);

void RemoveRepetidos(pNodoLista* ptLista);
