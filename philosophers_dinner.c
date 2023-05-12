/*
    PROBLEMA DO JANTAR DOS FILÓSOFOS
    Heitor Tanoue de Mello - 12547260
*/

#include "philosophers_dinner.h"

Monitor monitor;

void pegarGarfos(int filosofo)
{
    // bloqueia mutex para entrar na região crítica
    pthread_mutex_lock(&monitor.mutex);
    monitor.estados[filosofo] = FAMINTO;
    testar(filosofo);

    // enquanto não puder comer, espera a condição
    if (monitor.estados[filosofo] != COMENDO)
    {
        pthread_cond_wait(&monitor.cond_var[filosofo], &monitor.mutex);
    }

    // desbloqueia mutex para sair da região crítica
    pthread_mutex_unlock(&monitor.mutex);
}

void devolverGarfos(int filosofo)
{
    pthread_mutex_lock(&monitor.mutex);
    monitor.estados[filosofo] = PENSANDO;

    // testa se os vizinhos podem comer
    testar(ESQUERDA(filosofo));
    testar(DIREITA(filosofo));

    pthread_mutex_unlock(&monitor.mutex);
}

int podeComer(int filosofo)
{
    // para evitar deadlock, o filósofo só pode comer se os seus vizinhos não estiverem comendo
    return monitor.estados[filosofo] == FAMINTO &&
           monitor.estados[ESQUERDA(filosofo)] != COMENDO &&
           monitor.estados[DIREITA(filosofo)] != COMENDO;
}

void testar(int filosofo)
{
    if (podeComer(filosofo))
    {
        monitor.estados[filosofo] = COMENDO;

        // sinaliza que o filósofo pode comer
        pthread_cond_signal(&monitor.cond_var[filosofo]);
    }
}

void *filosofo(void *arg)
{
    int id = *(int *)arg;
    int qntRefeicoes = 0;

    while (1)
    {
        // Filósofo pensando
        printf("Filósofo %d está pensando...\n", id);

        sleep(rand() % 3); // Tempo aleatório pensando

        // Filósofo faminto
        printf("Filósofo %d está faminto...\n", id);

        pegarGarfos(id);

        // Filósofo comendo
        printf("Filósofo %d está comendo...\n", id);

        sleep(rand() % 3); // Tempo aleatório comendo

        devolverGarfos(id);

        qntRefeicoes++;
        printf("Filósofo %d terminou de comer pela %dª vez.\n", id, qntRefeicoes);
    }
}

int main()
{
    pthread_t filosofos[NUM_FILOSOFOS];
    int ids[NUM_FILOSOFOS];

    srand(time(NULL));

    // inicializa mutex e variáveis de condição
    pthread_mutex_init(&monitor.mutex, NULL);
    for (int i = 0; i < NUM_FILOSOFOS; i++)
    {
        pthread_cond_init(&monitor.cond_var[i], NULL);
    }

    // cria as threads
    for (int i = 0; i < NUM_FILOSOFOS; i++)
    {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
    }

    // aguarda as threads terminarem
    for (int i = 0; i < NUM_FILOSOFOS; i++)
    {
        pthread_join(filosofos[i], NULL);
    }

    // destrói mutex e variáveis de condição
    pthread_mutex_destroy(&monitor.mutex);
    for (int i = 0; i < NUM_FILOSOFOS; i++)
    {
        pthread_cond_destroy(&monitor.cond_var[i]);
    }

    return 0;
}
