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
    argc = 3;

    if (argc != 3) 
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
    start = clock();
    pNodoAVL* arvoreLexico = CriaArvoreAVL();

    while (fgets(buffer, 50, fileLexico) != NULL)
    {
        char tempNegativos[4];
        char tempPositivos[3];
        int j = 3;
        float pontuacao;
        int ehPositivo = 1;
        strlwr(buffer);

        char c = buffer[0];
        int i = 0;
        int ehMenorTres = 1;
        while (c < 48 || c > 57 )
        {
            if (i == 2)
                ehMenorTres = 0;
            if (c == 45 && !ehMenorTres)
            {
                c = buffer[i];
                j = 4;
                ehPositivo = 0;
                strncpy(tempNegativos, buffer + i, j);
                pontuacao = strtof(tempNegativos, NULL);
                break;
            }
            i++;
            c = buffer[i];
        }

        if(ehPositivo)
        {
            strncpy(tempPositivos, buffer + i, j);
            pontuacao = strtof(tempPositivos, NULL);
        }
        strtok(buffer, separador);

        //while (*teste) {
        //    if ((*teste >= '0' && *teste <= '9') || // Check for numbers
        //        (*teste >= 33 && *teste <= 47) ||   // Check for special characters in ASCII
        //        (*teste >= 58 && *teste <= 64) ||   // Check for special characters in ASCII
        //        (*teste >= 91 && *teste <= 96) ||   // Check for special characters in ASCII
        //        (*teste >= 123 && *teste <= 126)) { // Check for special characters in ASCII
        //        int bah = 1; // The string contains a number or special character
        //    }
        //    teste++;
        //}
        arvoreLexico = InsereNodoAVL(arvoreLexico, buffer, pontuacao);
    }
    fclose(fileLexico);

    FILE* fileWrite = fopen(argv[3], "w");

    while (!feof(fileSentenças))
    {
        char buffer[450];
        fgets(buffer, 450, fileSentenças);
        int j = 0;
        float pontuacaoTotalLinha = 0;
        strlwr(buffer);
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            if (buffer[i] == ' ')
            {
                char palavra[50];
                int k = 0;
                for (; j < i; j++)
                {
                    palavra[k] = buffer[j];
                    k++;
                }
                palavra[k] = '\0';
                pNodoAVL* nodo = ConsultaAVL(arvoreLexico, palavra);
                if (nodo != NULL)
                    pontuacaoTotalLinha += nodo->pontuacao;
                j++;
                LimpaArray(k, palavra);
            }
        };
        char bufferNovaLinha[450];

        int tamanhoNumero = snprintf(NULL, 0, "%.2f", pontuacaoTotalLinha);
        snprintf(bufferNovaLinha, tamanhoNumero + strlen(buffer) + 2, "%.2f %s", pontuacaoTotalLinha, buffer);     
        fwrite(bufferNovaLinha, 1, strlen(bufferNovaLinha), fileWrite);
    }

    printf("\nArquivo de saída gerado com sucesso.\n");

    end = clock(); 
    float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; 
    printf("Tempo: %.5f ms\n", miliseconds);

    fclose(fileSentenças);
    fclose(fileWrite);
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
