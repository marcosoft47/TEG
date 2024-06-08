#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define nLinhas 150
#define nColunas 40

// Define o Node
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Define a Queue
typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;

// Funcoes misc
char *getField(const char *line, int num);
int **adjacencia(float **matrix, float x);
float **normalizedManhattan(float **matrix);

// Funcoes BFS
void bfs(int **matrixA, int **visitados, Queue *queue);
int check(int **matrix, int x);
int **initMatrix();

// Funcoes de fila

Node *newNode(int data);
Queue *createQueue();
int contains(Queue *queue, int data);
void enqueue(Queue *queue, int data);
void dequeue(Queue *queue);
int front(Queue *queue);

#endif