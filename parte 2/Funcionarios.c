#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "MonitorBanheiro.h"

#define NUM_CORINTIANOS 10
#define NUM_PALMEIRENSES 10

/* =========== Funções =========== */

void thread_corintiano(int *id) { // cada corintiano e palmeirense terá um identificador de 1 a 10
  while (true) {
    corintianoQuerEntrar();
    printf("Eu sou corintiano-%d: ... UFA! Entrei no banheiro!\n", *id);
    sleep(3);
    corintianoSai();
    printf("Eu sou corintiano-%d: ... Estou aliviado! Vou trabalhar!\n", *id);
    sleep(5);
  }
}

void thread_palmeirense(int *id) { // cada corintiano e palmeirense terá um identificador de 1 a 10
  while (true) {
    palmeirenseQuerEntrar();
    printf("Eu sou palmeirense-%d: ... UFA! Entrei no banheiro!\n", *id);
    sleep(3);
    palmeirenseSai();
    printf("Eu sou palmeirense-%d: ... Estou aliviado! Vou trabalhar!\n", *id);
    sleep(5);
  }
}

int main(int argc, char **argv) {
  pthread_t pthCorintianos[NUM_CORINTIANOS]; // Criando os corintianos (threads)
  pthread_t pthPalmeirenses[NUM_PALMEIRENSES]; // Criando os palmerenses (threads)

  initBanheiro();

  /* Cria os corintianos */
  int i = 0;
  for (i = 0; i < NUM_CORINTIANOS; i++) {
    int *id = (int *) malloc(sizeof(int));
    *id = i + 1;
    pthread_create(&pthCorintianos[i], NULL, (void *) thread_corintiano, (void *) id);
  }

  /* Cria os palmeirenses */
  for (i = 0; i < NUM_PALMEIRENSES; i++) {
    int *id = (int *) malloc(sizeof(int));
    *id = i + 1;
    pthread_create(&pthPalmeirenses[i], NULL, (void *) thread_palmeirense, (void *) id);
  }

  /* Espera os corintianos terminarem */
  for (i = 0; i < NUM_CORINTIANOS; i++) {
    pthread_join(pthCorintianos[i], NULL);
  }

  /* Espera os palmeirenses terminarem */
  for (i = 0; i < NUM_PALMEIRENSES; i++) {
    pthread_join(pthPalmeirenses[i], NULL);
  }

  destroyBanheiro();

  return 0;
}