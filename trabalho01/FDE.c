#include "FDE.h"

/*************** CRIA ***************/
struct descF *cria(int tamInfo)
{
    struct descF *desc = (struct descF *)malloc(sizeof(struct descF));
    if (desc != NULL)
    {
        desc->cauda = NULL;
        desc->frente = NULL;
        desc->tamInfo = tamInfo;
        desc->refMovel = NULL;
    }
    return desc;
}
// Inicia info
info *iniciaInfo()
{
    info *i = NULL;
    i = (info *)malloc(sizeof(info));
    if (i)
    {
        i->numero = 0;
    }
    return i;
}

// Inicia Nó
struct noFila *iniciaNo()
{
    struct noFila *n = NULL;
    info *i = iniciaInfo();
    n = (struct noFila *)malloc(sizeof(struct noFila));
    if (n)
    {
        n->atras = NULL;
        n->defronte = NULL;
        n->dados = *i;
    }
    return n;
}
/*************** INSERE A PARTIR DA FRENTE ***************/
int insere(info *pInfo, struct descF *p)
{
    struct noFila *novoNoFila = NULL, *visitado = NULL;
    if ((novoNoFila = (struct noFila *)malloc(sizeof(struct noFila))) != NULL)
    {
        memcpy(&(novoNoFila->dados), pInfo, p->tamInfo);

        if (p->frente == NULL && p->cauda == NULL)
        { /*fila vazia*/
            novoNoFila->atras = novoNoFila->defronte = NULL;
            p->frente = p->cauda = novoNoFila;
        }
        else
        {
            printf("novo no %d\n",novoNoFila->dados.numero);
            // printf("endereco %p", p->cauda);
            printf("cauda %d\n", p->cauda->dados.numero);
            if (novoNoFila->dados.numero < p->cauda->dados.numero)
            { /*novo elemento é o de menor prioridade */

                novoNoFila->atras = NULL;
                novoNoFila->defronte = p->cauda;
                p->cauda->atras = novoNoFila;
                p->cauda = novoNoFila;
            }

            else
            {
                visitado = p->frente; /*maior prioridade na frente */

                while (visitado->atras != NULL && (visitado->dados.numero >= novoNoFila->dados.numero))
                {
                    visitado = visitado->atras; /* A(idade) <= B(idade) */
                }

                if (visitado->dados.numero < novoNoFila->dados.numero)
                { /* novo item fica a frente do visitado */
                    novoNoFila->atras = visitado;

                    if (visitado->defronte != NULL)
                    {
                        novoNoFila->defronte = visitado->defronte;
                        visitado->defronte->atras = novoNoFila;
                    }
                    else
                    { // novo item é o de maior prioridade de todos na fila, sendo a nova frente
                        novoNoFila->defronte = NULL;
                        p->frente = novoNoFila;
                    }
                    visitado->defronte = novoNoFila;
                }
            }
        }
        return SUCESSO;
    }
    return FRACASSO;
}

/*************** INSERE POR REF MOVEL ***************/
int insereMovel(info *pInfo, struct descF *p)
{
    struct noFila *novoNoFila = NULL, *visitado = NULL;
    if ((novoNoFila = (struct noFila *)malloc(sizeof(struct noFila))) != NULL)
    {
        memcpy(&(novoNoFila->dados), pInfo, p->tamInfo);

        if (p->frente == NULL && p->cauda == NULL)
        { /*fila vazia*/
            novoNoFila->atras = novoNoFila->defronte = NULL;
            p->refMovel = p->frente = p->cauda = novoNoFila;
        }
        else
        {
            if (novoNoFila->dados.numero <= p->cauda->dados.numero)
            { /*novo elemento é o de menor prioridade */
                novoNoFila->atras = NULL;
                novoNoFila->defronte = p->cauda;
                p->cauda->atras = novoNoFila;
                p->cauda = novoNoFila;
            }
            else if (novoNoFila->dados.numero > p->frente->dados.numero)
            {
                novoNoFila->atras = p->frente;
                novoNoFila->defronte = NULL;
                p->frente->defronte = novoNoFila;
                p->frente = novoNoFila;
            }
            else if (p->cauda->dados.numero < novoNoFila->dados.numero && novoNoFila->dados.numero < p->refMovel->dados.numero)
            {
                if (abs(p->cauda->dados.numero - novoNoFila->dados.numero) < abs(p->refMovel->dados.numero - novoNoFila->dados.numero))
                {
                    // Vai pela cauda
                    visitado = p->cauda;

                    while (visitado->defronte != NULL && visitado->dados.numero < novoNoFila->dados.numero)
                    {
                        visitado = visitado->defronte;
                    }
                    novoNoFila->defronte = visitado;
                    novoNoFila->atras = visitado->atras;
                    if (visitado->atras != NULL)
                        visitado->atras->defronte = novoNoFila;
                    visitado->atras = novoNoFila;
                }
                else
                {
                    // Vai pelo ref até a cauda
                    visitado = p->refMovel;

                    while (visitado->atras != NULL && visitado->dados.numero >= novoNoFila->dados.numero)
                    {
                        visitado = visitado->atras;
                    }
                    novoNoFila->atras = visitado;
                    novoNoFila->defronte = visitado->defronte;
                    if (visitado->defronte != NULL)
                        visitado->defronte->atras = novoNoFila;
                    visitado->defronte = novoNoFila;
                }
            }
            else if (p->refMovel->dados.numero <= novoNoFila->dados.numero && novoNoFila->dados.numero <= p->frente->dados.numero)
            {
                if (abs(p->frente->dados.numero - novoNoFila->dados.numero) < abs(p->refMovel->dados.numero - novoNoFila->dados.numero))
                {
                    // Vai pela frente
                    visitado = p->frente;

                    while (visitado->atras != NULL && visitado->dados.numero >= novoNoFila->dados.numero)
                    {
                        visitado = visitado->atras;
                    }
                    novoNoFila->atras = visitado;
                    novoNoFila->defronte = visitado->defronte;
                    if (visitado->defronte != NULL)
                        visitado->defronte->atras = novoNoFila;
                    visitado->defronte = novoNoFila;
                }
                else
                {
                    // Vai pelo ref até a frente
                    visitado = p->refMovel;

                    while (visitado->defronte != NULL && visitado->dados.numero < novoNoFila->dados.numero)
                    {
                        visitado = visitado->defronte;
                    }
                    novoNoFila->defronte = visitado;
                    novoNoFila->atras = visitado->atras;
                    if (visitado->atras != NULL)
                        visitado->atras->defronte = novoNoFila;
                    visitado->atras = novoNoFila;
                }
            }
        }
        p->refMovel = novoNoFila;
        return SUCESSO;
    }
    return FRACASSO;
}
/*************** REMOVE DA FRENTE ***************/
int remove_(info *reg, struct descF *p)
{
    int ret = FRACASSO;
    struct noFila *aux = p->cauda;

    if (p->cauda != NULL && p->frente != NULL)
    {
        memcpy(reg, &(p->frente->dados), p->tamInfo);

        if (aux == p->frente)
        { // caso tenha 1 elemento apenas
            free(p->frente);
            p->frente = p->cauda = NULL;
        }
        else
        {
            p->frente = p->frente->atras;
            free(p->frente->defronte);
            p->frente->defronte = NULL;
        }
        ret = SUCESSO;
    }

    return ret;
}

/*************** BUSCA NA FRENTE ***************/
int buscaNaFrente(info *reg, struct descF *p)
{
    int ret = FRACASSO;

    if (p->frente != NULL && p->cauda != NULL)
    {
        memcpy(reg, &(p->frente->dados), p->tamInfo);
        ret = SUCESSO;
    }

    return ret;
}

/*************** BUSCA NA CAUDA ***************/
int buscaNaCauda(info *reg, struct descF *p)
{
    int ret = FRACASSO;

    if (p->cauda != NULL && p->frente != NULL)
    {
        memcpy(reg, &(p->cauda->dados), p->tamInfo);
        ret = SUCESSO;
    }

    return ret;
}

/*************** VAZIA? ***************/
int testaVazia(struct descF *p)
{
    if (p->frente == NULL && p->cauda == NULL)
    {
        return SIM;
    }

    return NAO;
}

/*************** TAMANHO ***************/
int tamanhoDaFila(struct descF *p)
{
    int tam = 0;
    struct noFila *aux = p->cauda;

    while (aux != NULL)
    {
        tam++;
        aux = aux->defronte;
    }

    return tam;
}

/*************** PURGA ***************/
int reinicia(struct descF *p)
{
    int ret = FRACASSO;
    struct noFila *aux = NULL;

    if (p->frente != NULL && p->cauda != NULL)
    {
        aux = p->cauda->defronte;
        while (aux != NULL)
        {
            free(p->cauda);
            p->cauda = aux;
            aux = aux->defronte;
        }

        free(p->cauda);
        p->frente = NULL;
        p->cauda = NULL;
        ret = SUCESSO;
    }
    return ret;
}

/*************** DESTROI ***************/
struct descF *destroi(struct descF *p)
{
    reinicia(p);
    free(p);
    return NULL; // aterra o ponteiro externo, declarado na aplica��o
}

// Verifica se um numero pertence na fila
int numeroPertence(int numero, struct descF *p)
{
    struct noFila *aux = p->cauda;
    while (aux != NULL)
    {
        if (numero == aux->dados.numero)
            return VERDADEIRO;
        aux = aux->defronte;
    }
    return FALSO;
}

int filaRemove(struct descF *p)
{
    if (p->cauda == NULL)
        return -1;
    struct noFila *aux = p->cauda->defronte;
    free(p->cauda);
    p->cauda = aux;
    if (aux != NULL)
        return aux->dados.numero;
    return -1;
}