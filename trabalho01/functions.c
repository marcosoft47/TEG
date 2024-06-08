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

/*****************Funcoes de Fila********************/
// Checa se esta vazio
int isEmpty(Queue *queue)
{
    return queue->front == NULL;
}

// Funcao que adiciona na Queue
void enqueue(Queue *queue, int data)
{
    // Checagem de duplicata
    if (contains(queue, data))
    {
        return;
    }

    Node *temp = newNode(data);

    // Se a Queue tiver vazia
    if (isEmpty(queue))
    {
        queue->front = queue->rear = temp;
        return;
    }

    // Adiciona Node no fim da Queue e move o fim
    queue->rear->next = temp;
    queue->rear = temp;
}

// Funcao que remove da Queue
void dequeue(Queue *queue)
{
    // Se a Queue estiver vazia ERRO
    if (isEmpty(queue))
    {
        return; // Consider returning a special value or handling error differently
    }

    // Move a frente
    queue->front = queue->front->next;

    // Se a frente for nula é o fim da fila
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    return;
}

// Funcao que pega o Node da frente
int front(Queue *queue)
{
    if (queue->front == NULL)
        return -1;
    return queue->front->data;
}

// Funcao que cria Node
Node *newNode(int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Funcao que cria Queue
Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Funcao que checa duplicatas na Queue
int contains(Queue *queue, int data)
{
    Node *current = queue->front;
    while (current != NULL)
    {
        if (current->data == data)
        {
            return 1; // Existe
        }
        current = current->next;
    }
    return 0; // Nao existe
}

/*****************Funcoes de BFS*********************/

void bfs(int **matrixA, int **visitados, Queue *queue)
{
    int rowMatrix = 0;
    int colMatrix = 0;

    for (int i = 0; i < nLinhas; i++)
    {
        if (check(visitados, i) == 0)
        {
            enqueue(queue, i);
            int numAtual = i;

            for (;;)
            {
                if (isEmpty(queue))
                    break;

                for (int j = numAtual + 1; j < nLinhas; j++)
                {
                    if (matrixA[numAtual][j] == 1 && check(visitados, j) == 0)
                        enqueue(queue, j);
                }

                visitados[rowMatrix][colMatrix] = numAtual;
                colMatrix++;

                dequeue(queue);
                numAtual = front(queue);
            }
            rowMatrix++;
        }
    }
}

int check(int **matrix, int x)
{
    for (int i = 0; i < nLinhas; i++)
    {
        for (int j = 0; j < nLinhas; j++)
        {
            if (matrix[i][j] == x)
                return 1;
        }
    }
    return 0;
}

int **initMatrix()
{
    int **matrix = (int **)malloc(nLinhas * sizeof(int *));

    for (int i = 0; i < nLinhas; i++)
    {
        matrix[i] = (int *)malloc(nLinhas * sizeof(int));

        memset(matrix[i], -1, nLinhas * sizeof(int));
    }

    return matrix;
}