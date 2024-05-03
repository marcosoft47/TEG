#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nLinhas 150
#define nColunas 4

char *getField(const char* line, int num);
int manhattan(float *v1, float *v2);
void salvarCsv(FILE *fp, float matriz[nLinhas][nColunas]);

int main(){
    // Ler arquivo
    FILE *fp;
    fp = fopen("IrisDataset.csv", "r");
    
    float iris[nLinhas][nColunas];
        int contador = 0;
    char tmp[64], linha[nLinhas][64];

    fgets(tmp, 64, fp);
    while(fgets(tmp,64,fp))
        strcpy(linha[contador++], tmp);
    
    for (int i = 0; i < nLinhas; i++){
        for (int j = 0; j < nColunas; j++){
            iris[i][j] = atof(getField(linha[i], j+1)); // +1 para ignorar a coluna de texto
        }
    }
    fclose(fp);


    // Matriz distância Manhattan Normalizada
    for (int i = 0; i < nLinhas; i++){
        for (int j = 0; j < nColunas; j++){
            printf("%f ", iris[i][j]);
        }
        printf("\n");
    }

    // Matriz adjacencia (manhattan <= 0.3)
    float mAdjacencia[nLinhas][nLinhas];

    // Salvar em .csv

    // Ver git caloio
}

// Pega o campo 
char *getField(const char* line, int num) {
    num++;
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

int manhattan(float *v1, float *v2){
    // float resultado = 0;
    // for(int i = 0; i <nColunas; i++)
    //     resultado += sqrt(pow(v1[i], 2)) - sqrt(pow(v2[i], 2));
    // return resultado;
}

void salvarCsv(FILE *fp, float matriz[nLinhas][nColunas]){
    int contador = 0;
    char tmp[64], linha[nLinhas][64];

    fgets(tmp, 10, fp);
        while(fgets(tmp,64,fp))
        strcpy(linha[contador++], tmp);
    
    for (int i = 0; i < nLinhas; i++){
        for (int j = 0; j < nColunas; j++){
            matriz[i][j] = atof(getField(linha, j+1)); // +1 para ignorar a coluna de texto
        }
    }
}