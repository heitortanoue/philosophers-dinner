#ifndef DINING_PHILOSOPHERS_H
#define DINING_PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5
#define ESQUERDA(id) (id)
#define DIREITA(id) ((id + 1) % NUM_FILOSOFOS)

typedef enum
{
    PENSANDO,
    FAMINTO,
    COMENDO
} Estado;

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond_var[NUM_FILOSOFOS];
    Estado estados[NUM_FILOSOFOS];
} Monitor;

extern Monitor monitor;

void pegarGarfos(int filosofo);
void devolverGarfos(int filosofo);
int podeComer(int filosofo);
void testar(int filosofo);
void *filosofo(void *arg);

#endif