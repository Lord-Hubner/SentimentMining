#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct TNodoAVL{
char info[50];
float pontuacao;
struct TNodoAVL *esq;
struct TNodoAVL *dir;
};

typedef struct TNodoAVL pNodoAVL;

pNodoAVL* CriaArvoreAVL(void);

void PreFixado(pNodoAVL *a);

pNodoAVL* ConsultaAVL(pNodoAVL* a, char palavra[50]);

int ContaNodosArvore(pNodoAVL *raiz);

void ContaNodosAux(pNodoAVL *nodo, int *pCounter);

void imprimePreFixado(pNodoAVL *raiz, int nivel);

int Altura(pNodoAVL* a);

void CalculaFatorBalanceamentoArvore(pNodoAVL* raiz, int* FB);

int CalculaFatorBalanceamentoNodo(pNodoAVL* nodo);

pNodoAVL* RotacaoDireitaAVL(pNodoAVL* raiz);

pNodoAVL* RotacaoEsquerdaAVL(pNodoAVL* raiz);

pNodoAVL* RotacaoDireitaEsquerdaAVL(pNodoAVL* raiz);

pNodoAVL* RotacaoEsquerdaDireitaAVL(pNodoAVL* raiz);

pNodoAVL* InsereNodoAVL(pNodoAVL* raiz, char infoBuffer[50], float pontuacao);


