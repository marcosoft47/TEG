#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define nLinhas 150
#define nColunas 4

char *getField(const char *line, int num);
int **adjacencia(float **matrix, float x);
float **normalizedManhattan(float **matrix);

#endif