#include "LSE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 136)
#pragma warning(disable : 138)

pNodoLista* inicializa(void)
{
    return NULL;
}

pNodoLista* InsereInicio(pNodoLista* PtLista, InfoNo info)
{
    pNodoLista* novo = (pNodoLista*)malloc(sizeof(pNodoLista));
    novo->info = info;
    novo->prox = PtLista;
    PtLista = novo;
    return novo;
}

pNodoLista* InsereFim(pNodoLista* PtLista, InfoNo info)
{
    pNodoLista* novo = (pNodoLista*)malloc(sizeof(pNodoLista));
    pNodoLista* aux = PtLista;
    novo->info = info;
    novo->prox = NULL;
    
    if (aux != NULL)
    {
        for (aux = PtLista; aux->prox != NULL; aux = aux->prox);
        
        aux->prox = novo;
    }

    return PtLista;
}

pNodoLista* remover(pNodoLista* ptLista, char titulo[])
{
    pNodoLista* ant = NULL; //ponteiro auxiliar para a posição anterior
    pNodoLista* ptaux = ptLista; //ponteiro auxiliar para percorrer a lista
    /*procura o elemento na lista*/
    while (ptaux != NULL && (strcmp(ptaux->info.nome, titulo)))
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }
    if (ptaux == NULL) /*verifica se achou*/
        return ptLista; /*retorna a lista original*/
    if (ant == NULL) /*vai remover o primeiro elemento*/
        ptLista = ptLista->prox ;
    else /*vai remover do meio ou do final*/
        ant->prox = ptLista->prox;
    free(ptaux); /*libera a memória alocada*/
    return ptLista;
}

pNodoLista* destroi(pNodoLista* ptLista)
{
    pNodoLista* ptaux; //ponteiro auxiliar para percorrer a lista
    while (ptLista != NULL)
    {
        ptaux = ptLista;
        ptLista = ptLista->prox;
        free(ptaux);
    }
    free(ptLista);
    return NULL;
}


void imprime(pNodoLista* ptLista)
{
    pNodoLista* ptaux;
    if (ptLista == NULL)
        return;
    else
        {
        for (ptaux=ptLista; ptaux!=NULL; ptaux=ptaux->prox)
            printf("Codigo = %d, Nome = %s, Preco = %d\n",
                   ptaux->info.codigo,
                   ptaux->info.nome,
                   ptaux->info.preco);
        }
}

pNodoLista* insereCrescente(pNodoLista* ptLista, InfoNo dados)
{
    pNodoLista* novo = (pNodoLista*)malloc(sizeof(pNodoLista));
    novo->info = dados;
    novo->prox = NULL;

    if (ptLista == NULL || dados.codigo <= ptLista->info.codigo) {
        novo->prox = ptLista;
        ptLista = novo;
        return ptLista;
    }

    pNodoLista* ptAux = ptLista;

    while (ptAux->prox != NULL && dados.codigo > ptAux->prox->info.codigo) {
        ptAux = ptAux->prox;
    }

    novo->prox = ptAux->prox;
    ptAux->prox = novo;

    return ptLista;
}

int TamanhoLista(pNodoLista* ptLista)
{
    pNodoLista* aux = ptLista;
    if (!aux)
        return 0;
    int counter = 0;
    for(aux=ptLista;aux;aux=aux->prox)
    {
        counter++;
    }
    return counter;
}

void RemoveRepetidos(pNodoLista* ptLista)
{
    pNodoLista* aux = ptLista;
    if (!aux)
        return 0;
    pNodoLista* aux2 = NULL;
    pNodoLista* ant1= NULL;
    pNodoLista* ant2 = NULL;
    int removeu = 0;

    char infoAtual[20];
    for(aux=ptLista;aux!=NULL;aux=aux->prox)
    {
        strcpy_s(infoAtual, sizeof infoAtual, aux->info.nome);
        ant2 = aux;
        for(aux2=aux->prox;aux2!=NULL;aux2=aux2->prox)
        {
            removeu = 0;

            if(!strcmp(infoAtual, aux2->info.nome))
            {
                if (aux2->prox)
                    ant2->prox = aux2->prox;
                else
                    ant2->prox = NULL;
                free(aux2);
                aux2 = ant2; 
                removeu = 1;
            }

            if (removeu == 0)
                ant2 = aux2;
        }
        ant1 = aux;
        ant2 = aux;
    }
}
