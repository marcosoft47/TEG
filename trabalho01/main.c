#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define nLinhas 150
#define nColunas 4

char *getField(const char *line, int num);
int manhattan(float *v1, float *v2);

int main()
{
    // Ler arquivo
    FILE *fp;
    fp = fopen("IrisDataset.csv", "r");

    float iris[nLinhas][nColunas];
    float mManhattan[nLinhas][nLinhas];
    int contador = 0;
    char tmp[64], linha[nLinhas][64];

    fgets(tmp, 64, fp);
    while (fgets(tmp, 64, fp))
        strcpy(linha[contador++], tmp);

    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nColunas; j++)
        {
            iris[i][j] = atof(getField(linha[i], j + 1)); // +1 para ignorar a coluna de texto
        }
    }
    fclose(fp);

    // Matriz distância Manhattan Normalizada
    float resultado = 0;
    float maior = 0;
    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nLinhas; j++)
        {
            for (int k = 0; k < nColunas; k++)
                resultado += abs(iris[i][k] - iris[j][k]);
            if (resultado > maior)
                maior = resultado;
            mManhattan[i][j] = resultado;
            resultado = 0;
        }
    }
    for (int i = 0; i < nLinhas; i++)
    {
        for (int a = 0; a < nLinhas; a++)
            mManhattan[i][a] = mManhattan[i][a] / maior;
    }

    int mAdjacencia[nLinhas][nLinhas];
    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nLinhas; j++)
        {
            if (mManhattan[i][j] <= 0.3 && i != j)
                mAdjacencia[i][j] = 1;
            else
                mAdjacencia[i][j] = 0;
        }
    }

    FILE *ftxt;
    ftxt = fopen("grafo.txt", "w");
    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nLinhas; j++)
        {
            if (mAdjacencia[i][j] == 1)
            {
                fprintf(ftxt, "%i %i\n", i + 1, j + 1);
            }
        }
    }
    fclose(ftxt);

    FILE *fcsv;
    fcsv = fopen("grafo.csv", "w");
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
