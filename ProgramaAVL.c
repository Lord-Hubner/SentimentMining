#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "AVL.h"
#include "Origem.h"

#pragma warning(disable : 4996)

void main(int argc, char*argv[])
{
    clock_t start, end;
    char buffer[50];
    char separador[] = { " ,.&*%\?!;/-'@\"$#=><()][}{:\n\t" };
    int numeroComparacoes = 0;
    int* pNumeroComparacoes = &numeroComparacoes;

    if (argc != 4) 
    {
        printf("Número incorreto de parâmetros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }

    FILE* fileLexico = fopen(argv[1], "r");
    if(!fileLexico)
    {
        printf("Erro: não foi possível abrir o arquivo de léxicos");
        return 1;
    }
    FILE* fileSentenças = fopen(argv[2], "r");
    if (!fileSentenças)
    {
        printf("Erro: não foi possível abrir o arquivo de sentenças");
        return 1;
    }

    FILE* fileWrite = fopen(argv[3], "w");
    if(!fileWrite)
    {
        "Erro: não foi possível criar o arquivo de saída";
        return 1;
    }
    start = clock(); //Começa contagem do cronômetro
    pNodoAVL* arvoreLexico = CriaArvoreAVL();
     
    while (fgets(buffer, 50, fileLexico) != NULL) //Pega linhas do arquivo de léxicos e armazena em buffer
    {
        char tempNegativos[4]; //arrays para as pontuações: negativo é um caractere maior para armazenas sinal de negativo
        char tempPositivos[3];
        int j = 3; //Variável para saber tamanho do número armazenado para lógica posterior
        float pontuacao;
        int ehPositivo = 1;
        strlwr(buffer); //Para depois armazenar a palavra com letras minúsculas

        char c = buffer[0];
        int i = 0;
        int ehMenorTres = 1; //Para evitar cortar palavras pequenas com hífens
        while (c < 48 || c > 57 ) //Itera pela linha enquanto o caractere não for um número:
        {
            if (i == 2) 
                ehMenorTres = 0;
            if (c == 45 && !ehMenorTres) //Se o caractere for um sinal negativo e tiver iterado mais de duas vezes, começa lógica para armazenar pontuação negativa
            {
                c = buffer[i];
                j = 4;
                ehPositivo = 0;
                strncpy(tempNegativos, buffer + i, j);
                pontuacao = strtof(tempNegativos, NULL); //strtof converte de string para float
                break;
            }
            i++;
            c = buffer[i];
        }

        if(ehPositivo) //Se iterou por toda a linha e não achou um sinal de negativo, a pontuação é positiva
        {
            strncpy(tempPositivos, buffer + i, j);
            pontuacao = strtof(tempPositivos, NULL);
        }
        strtok(buffer, separador); //Depois de armazenar a pontuação, tokeniza o buffer para inserir só a palavra

        arvoreLexico = InsereNodoAVL(arvoreLexico, buffer, pontuacao);
    }
    fclose(fileLexico); //Terminou de ler o arquivo de léxicos

    while (!feof(fileSentenças)) //Enquanto não chegou ao fim do arquivo de sentenças:
    {
        char buffer[450];
        fgets(buffer, 450, fileSentenças); //Pega do arquivo e armazena em buffer
        int j = 0;
        float pontuacaoTotalLinha = 0;
        strlwr(buffer); //Garante que a palavra esteja como foi armazenada (em letras minúsculas)
        for (int i = 0; buffer[i] != '\0'; i++) //Itera pela linha até chegar no fim da string
        {
            if (buffer[i] == ' ') //Se teve um espaço em branco, termina a atual palavra
            {
                char palavra[50];
                int k = 0;
                for (; j < i; j++) //Armazena a palavra em um novo vetor percorrendo do início (j) até o fim (i)
                {
                    palavra[k] = buffer[j];
                    k++;
                }
                palavra[k] = '\0'; //Marca o fim da palavra logo depois de terminar, para garantir que seja igual a como foi armazenada
                pNodoAVL* nodo = ConsultaAVL(arvoreLexico, palavra, pNumeroComparacoes); //Busca pela palavra na árvore
                if (nodo != NULL)
                    pontuacaoTotalLinha += nodo->pontuacao; //Soma pontuação apenas se estiver na árvore
                j++;
                LimpaArray(k, palavra); //Limpa vetor palavra para evitar vestígios da palavra anterior
            }
        };
        char bufferNovaLinha[450]; //Após iterar por toda a linha

        int tamanhoNumero = snprintf(NULL, 0, "%.2f", pontuacaoTotalLinha); //Pega quanto espaço vai armazenar na nova linha para a pontuação
        snprintf(bufferNovaLinha, tamanhoNumero + strlen(buffer) + 2, "%.2f %s", pontuacaoTotalLinha, buffer); //Armazena na nova linha a pontuação seguida do texto, com seus respectivos tamanhos     
        fwrite(bufferNovaLinha, 1, strlen(bufferNovaLinha), fileWrite); //Escreve a nova linha no arquivo de saída
    }

    printf("\nArquivo de saída gerado com sucesso.\n");

    end = clock(); 
    float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; 
    printf("Tempo: %.5f ms\n", miliseconds); //Tempo de execução

    printf("Número de comparações realizadas na consulta da Árvore: %d", *pNumeroComparacoes);

    fclose(fileSentenças);
    fclose(fileWrite);
    return 0;
}

void AtribuiQuebraLinha(char  palavra[50], int k)
{
    palavra[k + 1] = '/';
    palavra[k + 2] = 't';
    palavra[k + 3] = '/';
    palavra[k + 4] = '/n';
}

void LimpaArray(int k, char  palavra[50])
{
    for (int l = 0; l < k; l++)
        palavra[l] = 'Ì';
}

int CharToInt(char c)
{
    if(c > 45 && c < 58)
    {
        return c - 45;
    }
}
