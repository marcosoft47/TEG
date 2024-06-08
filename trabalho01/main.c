#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.c"

int main()
{
    // Ler arquivo
    FILE *fp = fopen("IrisDataset.csv", "r");
    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo IrisDataset.csv");
        return 1;
    }

    // Aloca a matriz iris
    float **iris = (float **)malloc(nLinhas * sizeof(float *));
    for (int i = 0; i < nLinhas; i++)
    {
        iris[i] = (float *)malloc(nColunas * sizeof(float));
    }

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

    // Calcula matriz manhattan normalizada
    mManhattan = normalizedManhattan(iris);

    // Free matriz iris
    free(iris);

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

        // Inicia a matriz visitados
        int **visitados = initMatrix();

        // Inicializa a fila
        Queue *fila = createQueue();

        // Calcula os componentes conexos por BFS
        bfs(mAdjacencia, visitados, fila);

        for (int i = 0; i < nLinhas; i++){
            for (int j = 0; j < nLinhas; j++){
                printf("%d  ", visitados[i][j]);
            }
            printf("\n");
        }
        
        // Free a matriz Adjacencias
        free(mAdjacencia);
        free(visitados);

        x++;
    }

    // Free a matriz Manhattan
    free(mManhattan);

    return 0;
}