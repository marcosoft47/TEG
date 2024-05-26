#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define nLinhas 150
#define nColunas 4

char *getField(const char *line, int num);

int main()
{
    // Ler arquivo
    FILE *fp = fopen("IrisDataset.csv", "r");
    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo IrisDataset.csv");
        return 1;
    }

    float iris[nLinhas][nColunas];
    float mManhattan[nLinhas][nLinhas];
    int contador = 0;
    char tmp[64], linha[nLinhas][64];

    fgets(tmp, sizeof(tmp), fp);
    while (fgets(tmp, sizeof(tmp), fp))
    {
        strcpy(linha[contador++], tmp);
    }
    fclose(fp);

    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nColunas; j++)
        {
            char *field = getField(linha[i], j + 1);
            iris[i][j] = atof(field);
            free(field);
        }
    }

    // Matriz distância Manhattan Normalizada
    float resultado = 0;
    float maior = 0;
    float menor = 10e5;
    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = i; j < nLinhas; j++)
        {
            if (j == i)
                mManhattan[i][j] = 0;
            else
            {
                for (int k = 0; k < nColunas; k++)
                    resultado += fabs(iris[i][k] - iris[j][k]);

                if (resultado > maior)
                    maior = resultado;

                if (resultado < menor)
                    menor = resultado;

                mManhattan[i][j] = resultado;
                mManhattan[j][i] = resultado;

                resultado = 0;
            }
        }
    }
    for (int i = 0; i < nLinhas; i++)
    {
        for (int a = i + 1; a < nLinhas; a++)
        {
            resultado = (mManhattan[i][a] - menor) / (maior - menor);
            mManhattan[i][a] = resultado;
            mManhattan[a][i] = resultado;
        }
    }

    int mAdjacencia[nLinhas][nLinhas] = {0};
    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = i + 1; j < nLinhas; j++)
        {
            if (mManhattan[i][j] <= 0.3)
            {
                mAdjacencia[i][j] = 1;
                mAdjacencia[j][i] = 1;
            }
        }
    }

    FILE *ftxt = fopen("grafo.txt", "w");
    int first = 1;
    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = i + 1; j < nLinhas; j++)
        {
            if (mAdjacencia[i][j] == 1)
            {
                if (!first)
                    fprintf(ftxt, "\n");
                fprintf(ftxt, "%i %i", i + 1, j + 1);
                first = 0;
            }
        }
    }
    fclose(ftxt);

    FILE *fcsv = fopen("grafo.csv", "w");
    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nLinhas; j++)
        {
            if (j == nLinhas - 1)
            {
                fprintf(fcsv, "%i\n", mAdjacencia[i][j]);
            }
            else
            {
                fprintf(fcsv, "%i,", mAdjacencia[i][j]);
            }
        }
    }
    fclose(fcsv);

    return 0;
}

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
