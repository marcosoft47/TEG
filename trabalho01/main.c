#include <stdio.h>
#include <stdlib.h>

int manhattan(){
}


int main(){
    // Ler arquivo
    FILE *fpntr;
    fpntr = fopen("IrisDataset.csv", "r");
    
    // Adicionar em matriz
    int iris[150][4];
    char linha[10];
    fgets(linha, 10, fpntr);

    // Matriz distância Manhattan Normalizada


    // Matriz adjacencia (manhattan <= 0.3)

    // Salvar em .csv

    // Ver git caloio
}

char *getField(const char* line, int num) {
    const char *p = line;
    size_t len;
    char *res;
    for (;;) {
        len = strcspn(p, ",\n");
        if (--num <= 0)
            break;
        p += len;
        if (*p == ',')
            p++;
    }
    res = malloc(len + 1);
    if (res) {
        memcpy(res, p, len);
        res[len] = '\0';
    }
    return res;
}