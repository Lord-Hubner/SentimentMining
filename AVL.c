#include "AVL.h"
#include  <string.h>
#include <math.h>
#pragma warning(disable : 4996)


pNodoAVL* CriaArvoreAVL(void)
{
    return NULL;
}

pNodoAVL* ConsultaAVL(pNodoAVL *a, char palavra[50], int* numeroComparacoes)
{
    while (a!=NULL)
    {
        (*numeroComparacoes)++;
        if (strcmp(a->info, palavra) == 0)
            return a; //achou retorna o ponteiro para o nodo
        else if (strcmp(a->info, palavra) > 0)
            a = a->esq;
        else
            a = a->dir;
    }
    return NULL; //não achou, retorna null
}

void PreFixado(pNodoAVL *a)
{
    if (a!= NULL)
    {
        printf("%s\n",a->info);
        printf("%f\n", a->pontuacao);
        PreFixado(a->esq);
        PreFixado(a->dir);
    }
}

int ContaNodosArvore(pNodoAVL *raiz)
{
    if(raiz!=NULL)
        {
            return
            ContaNodosArvore(raiz->esq) + ContaNodosArvore(raiz->dir) + 1;
        }
    else
        return 0;

}

void imprimePreFixado(pNodoAVL *raiz, int nivel)
{
    if(raiz!=NULL)
        {
            int i;
            for(i=0;i<nivel;i++)
                {
                    printf("%c", 61);
                }
    printf("%s\n", raiz->info);
    printf("%f\n", raiz->pontuacao);
    imprimePreFixado(raiz->esq, nivel+1);
    imprimePreFixado(raiz->dir, nivel+1);
        }
}

int Altura (pNodoAVL *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = Altura (a->esq);
        Alt_Dir = Altura (a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

void CalculaFatorBalanceamentoArvore(pNodoAVL* raiz, int* FB)
{
    if(raiz != NULL)
        {
            int resultado = CalculaFatorBalanceamentoNodo(raiz);
            if(abs(resultado) > *FB)
                *FB = resultado;
            CalculaFatorBalanceamentoArvore(raiz->esq, FB);
            CalculaFatorBalanceamentoArvore(raiz->dir, FB);
        }
}

int CalculaFatorBalanceamentoNodo(pNodoAVL* nodo)
{
    if (!nodo)
        return 0;

    int alturaSubEsq = Altura(nodo->esq);
    int alturaSubDir = Altura(nodo->dir);
    return alturaSubEsq - alturaSubDir;
}

pNodoAVL* RotacaoEsquerdaAVL(pNodoAVL* raiz) {
    pNodoAVL* tmp1;
    pNodoAVL* tmp2;

    tmp1 = raiz;
    tmp2 = tmp1->dir;

    tmp1->dir = tmp2->esq;
    tmp2->esq = tmp1;

    return tmp2;
}

// Rotacao simples a direita 
pNodoAVL* RotacaoDireitaAVL(pNodoAVL* raiz) {
    pNodoAVL* tmp1;
    pNodoAVL* tmp2;

    tmp1 = raiz;
    tmp2 = tmp1->esq;

    tmp1->esq = tmp2->dir;
    tmp2->dir = tmp1;

    return tmp2;
}

// Rotacao esquerda-direita
pNodoAVL* RotacaoEsquerdaDireitaAVL(pNodoAVL* raiz) {
    pNodoAVL* tmp1;
    pNodoAVL* tmp2;
    pNodoAVL* tmp3;

    tmp1 = raiz;
    tmp2 = tmp1->esq;
    tmp3 = tmp1->esq->dir;

    tmp1->esq = tmp3->dir;
    tmp2->dir = tmp3->esq;
    tmp3->dir = tmp1;
    tmp3->esq = tmp2;

    return tmp3;
}

// Rotacao direita-esquerda
pNodoAVL* RotacaoDireitaEsquerdaAVL(pNodoAVL* raiz) {
    pNodoAVL* tmp1;
    pNodoAVL* tmp2;
    pNodoAVL* tmp3;

    tmp1 = raiz;
    tmp2 = tmp1->dir;
    tmp3 = tmp1->dir->esq;

    tmp1->dir = tmp3->esq;
    tmp2->esq = tmp3->dir;
    tmp3->esq = tmp1;
    tmp3->dir = tmp2;

    return tmp3;
}

pNodoAVL* InsereNodoAVL(pNodoAVL* raiz, char palavra[50], float pontuacao) {
    if (raiz == NULL) {
        raiz = (pNodoAVL*)malloc(sizeof(pNodoAVL));
        strcpy(raiz->info, palavra);
        raiz->pontuacao = pontuacao;
        raiz->esq = NULL;
        raiz->dir = NULL;
        return raiz;
    }
    else if (strcmp(palavra, raiz->info) < 0)
        raiz->esq = InsereNodoAVL(raiz->esq, palavra, pontuacao);
    else if (strcmp(palavra, raiz->info) > 0)
        raiz->dir = InsereNodoAVL(raiz->dir, palavra, pontuacao);

    int FB = CalculaFatorBalanceamentoNodo(raiz);
    int FBEsq = CalculaFatorBalanceamentoNodo(raiz->esq);
    int FBDir = CalculaFatorBalanceamentoNodo(raiz->dir);

    if (FB == 2 && FBEsq == 1) {
        raiz = RotacaoDireitaAVL(raiz);
    }

    else if (FB == -2 && FBDir == -1) {
        raiz = RotacaoEsquerdaAVL(raiz);
    }

    else if (FB == -2 && FBDir == 1) {
        raiz = RotacaoDireitaEsquerdaAVL(raiz);
    }

    else if (FB == 2 && FBEsq == -1) {
        raiz = RotacaoEsquerdaDireitaAVL(raiz);
    }

    return raiz;
}



