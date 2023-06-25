#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "macaco.h"
#include "gorila.h"

#define NUM_MACACOS 10
#define NUM_GORILAS 2


/*======= Variáveis globais =======*/
sem_t semMacacos; // Semáforo dos macacos
sem_t semGorilas; // Semáforo dos gorilas

int qtdMacacosNaPonte = 0;
int qtdGorilasNaPonte = 0;

Macaco macacos[NUM_MACACOS];
Gorila gorilas[NUM_GORILAS];

Macaco macacosNaPonte[NUM_MACACOS];
Gorila gorilasNaPonte[NUM_GORILAS];

void* macaco(void* arg) {
  Macaco macaco = *(Macaco*) arg;
  usleep(rand() % 2000000); // Atraso aleatório antes de iniciar a travessia

  sem_wait(&semMacacos); // Verifica a disponibilidade na ponte
  while (!podeAtravessarMacaco(macaco, macacosNaPonte, qtdMacacosNaPonte, qtdGorilasNaPonte)) {
    sem_post(&semMacacos); // Libera o semáforo
    usleep(100000); // Espera um curto período e tenta novamente
    sem_wait(&semMacacos); // Verifica o semáforo novamente
  }

  macacosNaPonte[qtdMacacosNaPonte] = macaco;
  qtdMacacosNaPonte++;
  printf("Macaco %d está atravessando a ponte.\n", getIdMacaco(macaco));
  usleep(rand() % 2000000); // Simula a travessia
  printf("Macaco %d atravessou a ponte.\n", getIdMacaco(macaco));
  qtdMacacosNaPonte--;

  sem_post(&semMacacos); // Libera o semáforo
}

void* gorila(void* arg) {
  Gorila gorila = *(Gorila*) arg;
  usleep(rand() % 2000000); // Atraso aleatório antes de iniciar a travessia

  sem_wait(&semGorilas); // Verifica a disponibilidade do gorila
  while (!podeAtravessarGorila(qtdGorilasNaPonte, qtdMacacosNaPonte)) {
    sem_post(&semGorilas); // Libera o semáforo
    usleep(100000); // Espera um curto período e tenta novamente
    sem_wait(&semGorilas); // Verifica o semáforo novamente
  }

  gorilasNaPonte[qtdGorilasNaPonte] = gorila;
  qtdGorilasNaPonte++;
  printf("Gorila %d está atravessando a ponte.\n", getIdGorila(gorila));
  usleep(rand() % 2000000); // Simula a travessia
  printf("Gorila %d atravessou a ponte.\n", getIdGorila(gorila));
  qtdGorilasNaPonte--;

  sem_post(&semGorilas); // Libera o semáforo
}

int main(int argc, char **argv) {
  srand(time(NULL)); // Para gerar números aleatórios

  pthread_t pthMacacos[NUM_MACACOS]; // Criando os macacos (threads)
  pthread_t pthGorilas[NUM_GORILAS]; // Criando os gorilas (threads)

  sem_init(&semMacacos, 0, 1); // Inicialização do semáforo dos macacos
  sem_init(&semGorilas, 0, 1); // Inicialização do semáforo dos gorilas

  int i = 0;
  for (i = 0; i < NUM_MACACOS; i++) { // Inicialização dos macacos
    macacos[i] = setIdMacaco(macacos[i], i+1);
    if (i % 2 == 0) setLadoAtual(macacos[i], 0);
    else            setLadoAtual(macacos[i], 1);
    pthread_create(&pthMacacos[i], NULL, macaco, &macacos[i]);
  }

  for (i = 0; i < NUM_GORILAS; i++) { // Inicialização dos gorilas
    gorilas[i] = setIdGorila(gorilas[i], i+1);
    if (i % 2 == 0) setLadoAtualGorila(gorilas[i], 0);
    else            setLadoAtualGorila(gorilas[i], 1);
    pthread_create(&pthGorilas[i], NULL, gorila, &gorilas[i]);
  }

  for (i = 0; i < NUM_MACACOS; i++) { // Espera os macacos terminarem
    pthread_join(pthMacacos[i], NULL);
  }

  for (i = 0; i < NUM_GORILAS; i++) { // Espera os gorilas terminarem
    pthread_join(pthGorilas[i], NULL);
  }

  sem_destroy(&semMacacos); // Destruição do semáforo dos macacos
  sem_destroy(&semGorilas); // Destruição do semáforo dos gorilas

  return 0;
}