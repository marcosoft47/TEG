#define LIVRE 0
#define OCUPADA 1
#define FRACASSO 0
#define SUCESSO 1
#define FALSO 0
#define VERDADEIRO 1
#define NAO 0
#define SIM 1
#define MAIOR 1
#define IGUAL 0
#define MENOR -1
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
 
#define debugging  1

typedef struct{ 
	int numero;
}info;


struct noFila{
	info dados;
	struct noFila *atras;
    struct noFila *defronte;
};

struct descF{
	struct noFila *frente;
	struct noFila *cauda;
	struct noFila *refMovel;
    int tamInfo;
};

//======================APLICACAO=====================


//======================FILA=====================
struct descF * cria(int tamInfo);
int insere(info *novo,struct descF *p);
int insereMovel(info *novo, struct descF *p);
int tamanhoDaFila(struct descF *p);
int reinicia(struct descF *p);
struct descF * destroi(struct descF *p);
int buscaNaCauda(info *reg, struct descF *p);
int buscaNaFrente(info *reg, struct descF *p);
int remove_(info *reg, struct descF *p);
int testaVazia(struct descF *p);
int inverte(struct descF *p);
info *iniciaInfo();
struct noFila *iniciaNo();
int numeroPertence(int numero, struct descF *p);
int filaRemove(struct descF *p);

