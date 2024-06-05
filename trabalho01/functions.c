#include <stdio.h>
#include "functions.h"

// Pega o campo indicado na linha
char *getField(const char *line, int num)
{
    num++;
    const char *p = line;
    size_t len;
    char *res;
    for (;;)
    {
        len = strcspn(p, ",\n");
        if (--num <= 0)
            break;
        p += len;
        if (*p == ',')
            p++;
    }
    res = malloc(len + 1);
    if (res)
    {
        memcpy(res, p, len);
        res[len] = '\0';
    }
    return res;
}

// Calcula as adjacencias com um limiar
int **adjacencia(float **matrix, float x)
{
    int **matrixout = (int **)malloc(nLinhas * sizeof(int *));
    for (int i = 0; i < nLinhas; i++)
    {
        matrixout[i] = (int *)malloc(nLinhas * sizeof(int));
    }

    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = i + 1; j < nLinhas; j++)
        {
            if (matrix[i][j] <= x)
            {
                matrixout[i][j] = 1;
                matrixout[j][i] = 1;
            }
            else
            {
                matrixout[i][j] = 0;
                matrixout[j][i] = 0;
            }
        }
    }
    return matrixout;
}

// Matriz distância Manhattan Normalizada
float **normalizedManhattan(float **matrix)
{
    float **matrixout = (float **)malloc(nLinhas * sizeof(float *));
    for (int i = 0; i < nLinhas; i++)
    {
        matrixout[i] = (float *)malloc(nLinhas * sizeof(float));
    }

    float resultado = 0;
    float maior = 0;
    float menor = 10e5;
    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = i; j < nLinhas; j++)
        {
            if (j == i)
                matrixout[i][j] = 0;
            else
            {
                for (int k = 0; k < nColunas; k++)
                    resultado += fabs(matrix[i][k] - matrix[j][k]);

                if (resultado > maior)
                    maior = resultado;

                if (resultado < menor)
                    menor = resultado;

                matrixout[i][j] = resultado;
                matrixout[j][i] = resultado;

                resultado = 0;
            }
        }
    }
    for (int i = 0; i < nLinhas; i++)
    {
        for (int a = i + 1; a < nLinhas; a++)
        {
            resultado = (matrixout[i][a] - menor) / (maior - menor);
            matrixout[i][a] = resultado;
            matrixout[a][i] = resultado;
        }
    }
    return matrixout;
}