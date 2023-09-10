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
        printf("N�mero incorreto de par�metros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }

    FILE* fileLexico = fopen(argv[1], "r");
    if(!fileLexico)
    {
        printf("Erro: n�o foi poss�vel abrir o arquivo de l�xicos");
        return 1;
    }
    FILE* fileSenten�as = fopen(argv[2], "r");
    if (!fileSenten�as)
    {
        printf("Erro: n�o foi poss�vel abrir o arquivo de senten�as");
        return 1;
    }

    FILE* fileWrite = fopen(argv[3], "w");
    if(!fileWrite)
    {
        "Erro: n�o foi poss�vel criar o arquivo de sa�da";
        return 1;
    }
    start = clock(); //Come�a contagem do cron�metro
    pNodoAVL* arvoreLexico = CriaArvoreAVL();
     
    while (fgets(buffer, 50, fileLexico) != NULL) //Pega linhas do arquivo de l�xicos e armazena em buffer
    {
        char tempNegativos[4]; //arrays para as pontua��es: negativo � um caractere maior para armazenas sinal de negativo
        char tempPositivos[3];
        int j = 3; //Vari�vel para saber tamanho do n�mero armazenado para l�gica posterior
        float pontuacao;
        int ehPositivo = 1;
        strlwr(buffer); //Para depois armazenar a palavra com letras min�sculas

        char c = buffer[0];
        int i = 0;
        int ehMenorTres = 1; //Para evitar cortar palavras pequenas com h�fens
        while (c < 48 || c > 57 ) //Itera pela linha enquanto o caractere n�o for um n�mero:
        {
            if (i == 2) 
                ehMenorTres = 0;
            if (c == 45 && !ehMenorTres) //Se o caractere for um sinal negativo e tiver iterado mais de duas vezes, come�a l�gica para armazenar pontua��o negativa
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

        if(ehPositivo) //Se iterou por toda a linha e n�o achou um sinal de negativo, a pontua��o � positiva
        {
            strncpy(tempPositivos, buffer + i, j);
            pontuacao = strtof(tempPositivos, NULL);
        }
        strtok(buffer, separador); //Depois de armazenar a pontua��o, tokeniza o buffer para inserir s� a palavra

        arvoreLexico = InsereNodoAVL(arvoreLexico, buffer, pontuacao);
    }
    fclose(fileLexico); //Terminou de ler o arquivo de l�xicos

    while (!feof(fileSenten�as)) //Enquanto n�o chegou ao fim do arquivo de senten�as:
    {
        char buffer[450];
        fgets(buffer, 450, fileSenten�as); //Pega do arquivo e armazena em buffer
        int j = 0;
        float pontuacaoTotalLinha = 0;
        strlwr(buffer); //Garante que a palavra esteja como foi armazenada (em letras min�sculas)
        for (int i = 0; buffer[i] != '\0'; i++) //Itera pela linha at� chegar no fim da string
        {
            if (buffer[i] == ' ') //Se teve um espa�o em branco, termina a atual palavra
            {
                char palavra[50];
                int k = 0;
                for (; j < i; j++) //Armazena a palavra em um novo vetor percorrendo do in�cio (j) at� o fim (i)
                {
                    palavra[k] = buffer[j];
                    k++;
                }
                palavra[k] = '\0'; //Marca o fim da palavra logo depois de terminar, para garantir que seja igual a como foi armazenada
                pNodoAVL* nodo = ConsultaAVL(arvoreLexico, palavra, pNumeroComparacoes); //Busca pela palavra na �rvore
                if (nodo != NULL)
                    pontuacaoTotalLinha += nodo->pontuacao; //Soma pontua��o apenas se estiver na �rvore
                j++;
                LimpaArray(k, palavra); //Limpa vetor palavra para evitar vest�gios da palavra anterior
            }
        };
        char bufferNovaLinha[450]; //Ap�s iterar por toda a linha

        int tamanhoNumero = snprintf(NULL, 0, "%.2f", pontuacaoTotalLinha); //Pega quanto espa�o vai armazenar na nova linha para a pontua��o
        snprintf(bufferNovaLinha, tamanhoNumero + strlen(buffer) + 2, "%.2f %s", pontuacaoTotalLinha, buffer); //Armazena na nova linha a pontua��o seguida do texto, com seus respectivos tamanhos     
        fwrite(bufferNovaLinha, 1, strlen(bufferNovaLinha), fileWrite); //Escreve a nova linha no arquivo de sa�da
    }

    printf("\nArquivo de sa�da gerado com sucesso.\n");

    end = clock(); 
    float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; 
    printf("Tempo: %.5f ms\n", miliseconds); //Tempo de execu��o

    printf("N�mero de compara��es realizadas na consulta da �rvore: %d", *pNumeroComparacoes);

    fclose(fileSenten�as);
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
        palavra[l] = '�';
}

int CharToInt(char c)
{
    if(c > 45 && c < 58)
    {
        return c - 45;
    }
}
