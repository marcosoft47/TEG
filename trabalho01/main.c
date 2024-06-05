#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define nLinhas 150
#define nColunas 4

char *getField(const char *line, int num);
int **adjacencia(float **matrix, float x);

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

    // Aloca a matriz Manhattan
    float **mManhattan = (float **)malloc(nLinhas * sizeof(float *));
    for (int i = 0; i < nLinhas; i++)
    {
        mManhattan[i] = (float *)malloc(nLinhas * sizeof(float));
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

    // Faz o calculo do limiar e arquivos .txt e .csv "n" vezes ate o usuario digitar -1
    char nArquivo[12];
    int x = 1;
    float limiar;

    for (;;)
    {
        printf("insira o limiar(-1 parada): ");
        scanf("%f", &limiar);

        if (limiar == -1)
            break;

        // Aloca a matriz Adjacencia
        int **mAdjacencia = (int **)malloc(nLinhas * sizeof(int *));
        for (int i = 0; i < nLinhas; i++)
        {
            mAdjacencia[i] = (int *)malloc(nLinhas * sizeof(int));
        }

        mAdjacencia = adjacencia(mManhattan, limiar);

        sprintf(nArquivo, "grafo%d.txt", x);

        FILE *ftxt = fopen(nArquivo, "w");
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

        sprintf(nArquivo, "grafo%d.csv", x);

        FILE *fcsv = fopen(nArquivo, "w");
        for (int i = 0; i < nLinhas; i++)
        {
            for (int j = 0; j < nLinhas; j++)
            {
                if (j == nLinhas - 1)
                {
                    fprintf(fcsv, "%d\n", mAdjacencia[i][j]);
                }
                else
                {
                    fprintf(fcsv, "%d,", mAdjacencia[i][j]);
                }
            }
        }
        fclose(fcsv);

        // Calcula os componentes conexos por BFS
        int mTeste[6][6] = {{0, 1, 0, 0, 0, 0},
                        {1, 0, 1, 1, 0, 0},
                        {0, 1, 0, 1, 0, 0},
                        {0, 1, 1, 0, 0, 0},
                        {0, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 1, 0}};
        int visitados = BFS(mTeste);

        // Free a matriz Adjacencias
        free(mAdjacencia);

        x++;
    }

    // Free a matriz Manhattan
    for (int i = 0; i < nLinhas; i++)
    {
        free(mManhattan[i]);
    }
    free(mManhattan);

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

int **BFS(float **matrix)
{
    int **visitados = (int **)malloc(nLinhas * sizeof(int *));
    int fila[nLinhas];

    // Inicializa matriz visitados e fila
    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nLinhas; j++)
            visitados[i][j] = NULL;
        fila[i] = NULL;
    }

    // Indices para matriz visitados
    int iV = 0;
    int jV = 0;
    for (int i = 0; i < nLinhas;)
    {
        visitados[iV][jV] = i;
        for (int j = i + 1; j < nLinhas; j++)
        {
            if (matrix[i][j] == 1)
            {
                if (!elementoPertence(j, fila))
                {
                    filaAdiciona(fila, j);
                }
            }
        }
        jV++;
        i = filaRemove(fila);
    }

    return visitados;
}

void printVisitados(int **visitados)
{
    for (int i = 0; i < sizeof(visitados) / sizeof(visitados[0]); i++)
    {
        for (int j = 0; j!=-1; j++)
        {
            if (visitados[i][j] != NULL)
                printf("%i ", &visitados[i][j]);
            else
                j = -2;
        }
    }
}

int elementoPertence(int elemento, int *vetor)
{
    for (int i = 0; i < sizeof(vetor) / sizeof(vetor[0]); i++)
    {
        if (vetor[i] == elemento)
            return 1;
    }
    return 0;
}
int filaAdiciona(int *vetor, int elemento){
    for (int i = 0; i < sizeof(vetor) / sizeof(vetor[0]); i++){
        if (vetor[i] == NULL){
            vetor[i] = elemento;
            return 1;
        }
    }
    return 0;
}
void filaReinicia(int *vetor){
    for (int i = 0; i < sizeof(vetor) / sizeof(vetor[0]); i++)
        vetor[i] = NULL;
}
int filaRemove(int *vetor){
    for (int i = -1; i < sizeof(vetor) / sizeof(vetor[0]) - 1; i++){
        if (vetor[i+1] == NULL && i != -1){
            int valor = vetor[i];
            vetor[i] = NULL;
            return valor;
        }
    }
    return NULL;
}