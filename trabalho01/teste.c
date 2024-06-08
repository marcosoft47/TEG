#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nLinhas 3

int main()
{
    int **visitados = (int **)malloc(nLinhas * sizeof(int *));

    for (int i = 0; i < nLinhas; i++)
    {
        visitados[i] = (int *)malloc(nLinhas * sizeof(int));

        memset(visitados[i], -1, nLinhas * sizeof(int));
    }

    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nLinhas; j++)
        {
            printf("%d ", visitados[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
