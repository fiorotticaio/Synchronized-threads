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
int qtdGorilasQueQueremAtravessar = 0;

Macaco macacos[NUM_MACACOS];
Gorila gorilas[NUM_GORILAS];

Macaco macacosNaPonte[NUM_MACACOS];
Gorila gorilasNaPonte[NUM_GORILAS];

void* macaco(void* arg) {
  Macaco macaco = *(Macaco*) arg;
  usleep(rand() % 2000000); // Atraso aleatório antes de iniciar a travessia

  sem_wait(&semMacacos); // Verifica a disponibilidade na ponte
  while (!podeAtravessarMacaco(macaco, macacosNaPonte, qtdMacacosNaPonte, qtdGorilasNaPonte, qtdGorilasQueQueremAtravessar)) {
    sem_post(&semMacacos); // Libera o semáforo
    usleep(100000); // Espera um curto período e tenta novamente
    sem_wait(&semMacacos); // Verifica o semáforo novamente
  }

  /* Pode atravessar */
  macacosNaPonte[qtdMacacosNaPonte] = macaco;
  qtdMacacosNaPonte++;
  printf("Macaco %d está atravessando a ponte. (lado %d -> lado %d) \n", getIdMacaco(macaco), getLadoOrigemMacaco(macaco), getLadoDestinoMacaco(macaco));
  usleep(rand() % 2000000); // Simula a travessia
  printf("Macaco %d atravessou a ponte. (lado %d -> lado %d) \n", getIdMacaco(macaco), getLadoOrigemMacaco(macaco), getLadoDestinoMacaco(macaco));
  qtdMacacosNaPonte--;
  sem_post(&semMacacos); // Libera o semáforo
}

void* gorila(void* arg) {
  Gorila gorila = *(Gorila*) arg;
  usleep(rand() % 2000000); // Atraso aleatório antes de iniciar a travessia

  sem_wait(&semGorilas); // Verifica a disponibilidade do gorila
  qtdGorilasQueQueremAtravessar++; // Gorilas tem prioridade
  while (!podeAtravessarGorila(qtdGorilasNaPonte, qtdMacacosNaPonte)) {
    sem_post(&semGorilas); // Libera o semáforo
    usleep(100000); // Espera um curto período e tenta novamente
    sem_wait(&semGorilas); // Verifica o semáforo novamente
  }

  /* Pode atravessar */
  gorilasNaPonte[qtdGorilasNaPonte] = gorila;
  qtdGorilasNaPonte++;
  qtdGorilasQueQueremAtravessar--;
  printf("\x1b[1;31mGorila %d está atravessando a ponte. (lado %d -> lado %d)\x1b[0m\n", getIdGorila(gorila), getLadoOrigemGorila(gorila), getLadoDestinoGorila(gorila));
  usleep(rand() % 2000000); // Simula a travessia
  printf("\x1b[1;31mGorila %d atravessou a ponte. (lado %d -> lado %d)\x1b[0m\n", getIdGorila(gorila), getLadoOrigemGorila(gorila), getLadoDestinoGorila(gorila));
  qtdGorilasNaPonte--;

  sem_post(&semGorilas); // Libera o semáforo
}

int main(int argc, char **argv) {
  srand(time(NULL)); // Para gerar números aleatórios

  pthread_t pthMacacos[NUM_MACACOS]; // Criando os macacos (threads)
  pthread_t pthGorilas[NUM_GORILAS]; // Criando os gorilas (threads)

  sem_init(&semMacacos, 0, NUM_MACACOS/2); // Inicialização do semáforo dos macacos
  /* No máximo 5 (NUM_MACACOS/2) macacos podem atravessar ao mesmo tempo, que são os macacos que vão na mesma direção */
  
  sem_init(&semGorilas, 0, 1); // Inicialização do semáforo dos gorilas
  /* Um gorila só pode atravessar a ponte sozinho */

  int i = 0;
  for (i = 0; i < NUM_MACACOS; i++) { // Inicialização dos macacos
    macacos[i] = setIdMacaco(macacos[i], i+1);
    if (i < NUM_MACACOS/2) {
      macacos[i] = setLadoOrigemMacaco(macacos[i], 0);
      macacos[i] = setLadoDestinoMacaco(macacos[i], 1);
    } else {
      macacos[i] = setLadoOrigemMacaco(macacos[i], 1);
      macacos[i] = setLadoDestinoMacaco(macacos[i], 0);
    }
    pthread_create(&pthMacacos[i], NULL, macaco, &macacos[i]);
  }

  for (i = 0; i < NUM_GORILAS; i++) { // Inicialização dos gorilas
    gorilas[i] = setIdGorila(gorilas[i], i+1);
    if (i < NUM_GORILAS/2) {
      gorilas[i] = setLadoOrigemGorila(gorilas[i], 0);
      gorilas[i] = setLadoDestinoGorila(gorilas[i], 1);
    } else {
      gorilas[i] = setLadoOrigemGorila(gorilas[i], 1);
      gorilas[i] = setLadoDestinoGorila(gorilas[i], 0);
    }    
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