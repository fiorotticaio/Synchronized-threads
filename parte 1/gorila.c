#include "gorila.h"

int getIdGorila(Gorila gorila) { 
  return gorila.id;
}

Gorila setIdGorila(Gorila gorila, int id) {
  gorila.id = id;
  return gorila;
}

int getLadoAtualGorila(Gorila gorila) {
  return gorila.ladoAtual;
}

Gorila setLadoAtualGorila(Gorila gorila, int ladoAtual) {
  gorila.ladoAtual = ladoAtual;
  return gorila;
}

Gorila atravessaGorila(Gorila gorila) {
  if (gorila.ladoAtual == 0) gorila.ladoAtual = 1;
  else                       gorila.ladoAtual = 0;
  return gorila;
}

// TODO: Esquema de prioridade dos gorilas perante os macacos
int podeAtravessarGorila(int qtdGorilasNaPonte, int qtdMacacosNaPonte) {
  if (qtdGorilasNaPonte == 0 && qtdMacacosNaPonte == 0) return 1;
  else                                                  return 0;
}