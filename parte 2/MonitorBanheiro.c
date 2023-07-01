#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "MonitorBanheiro.h"

#define LIMITE_BANHEIRO 3

int qtdCorNoBanheiro=0;
int qtdPalNoBanheiro=0;
pthread_mutex_t mutexBanheiro;
pthread_cond_t condBanheiro;

void corintianoQuerEntrar() {
  pthread_mutex_lock(&mutexBanheiro);
  while (qtdCorNoBanheiro+qtdPalNoBanheiro >= LIMITE_BANHEIRO || qtdPalNoBanheiro>0) {
    pthread_cond_wait(&condBanheiro, &mutexBanheiro);
  }
  
  qtdCorNoBanheiro++;
  pthread_mutex_unlock(&mutexBanheiro);
  printf("\x1b[1;37m[PESSOAS NO BANHEIRO]: \x1b[1;31m%d Corintianos e \x1b[1;32m%d Palmeirenses\x1b[0;37m\n", qtdCorNoBanheiro, qtdPalNoBanheiro);
}

void corintianoSai() {
  pthread_mutex_lock(&mutexBanheiro);
  qtdCorNoBanheiro--;
  pthread_mutex_unlock(&mutexBanheiro);
  pthread_cond_signal(&condBanheiro);

}

void palmeirenseQuerEntrar() {
  pthread_mutex_lock(&mutexBanheiro);
  while (qtdCorNoBanheiro+qtdPalNoBanheiro >= LIMITE_BANHEIRO || qtdCorNoBanheiro>0) {
    pthread_cond_wait(&condBanheiro, &mutexBanheiro);
  }

  qtdPalNoBanheiro++;
  pthread_mutex_unlock(&mutexBanheiro);
  printf("\x1b[1;37m[PESSOAS NO BANHEIRO]: \x1b[1;31m%d Corintianos e \x1b[1;32m%d Palmeirenses\x1b[0;37m\n", qtdCorNoBanheiro, qtdPalNoBanheiro);
}

void palmeirenseSai() {
  pthread_mutex_lock(&mutexBanheiro);
  qtdPalNoBanheiro--;
  pthread_mutex_unlock(&mutexBanheiro);
  pthread_cond_signal(&condBanheiro);

}

void initBanheiro() {
  pthread_mutex_init(&mutexBanheiro, NULL);
  pthread_cond_init(&condBanheiro, NULL);
}

void destroyBanheiro() {
  pthread_mutex_destroy(&mutexBanheiro);
  pthread_cond_destroy(&condBanheiro);
}