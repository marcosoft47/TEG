#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern int nLinhas = 150;
extern int nColunas = 4;

char *getField(const char *line, int num);
int **adjacencia(float **matrix, float x);
float **normalizedManhattan(float **matrix);

#endif