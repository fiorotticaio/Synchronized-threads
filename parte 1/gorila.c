#include "gorila.h"

int getIdGorila(Gorila gorila) { 
  return gorila.id;
}

Gorila setIdGorila(Gorila gorila, int id) {
  gorila.id = id;
  return gorila;
}

int getLadoOrigemGorila(Gorila gorila) {
  return gorila.ladoOrigem;
}

Gorila setLadoOrigemGorila(Gorila gorila, int ladoOrigem) {
  gorila.ladoOrigem = ladoOrigem;
  return gorila;
}

int getLadoDestinoGorila(Gorila gorila) {
  return gorila.ladoDestino;
}

Gorila setLadoDestinoGorila(Gorila gorila, int ladoDestino) {
  gorila.ladoDestino = ladoDestino;
  return gorila;
}

int podeAtravessarGorila(int qtdGorilasNaPonte, int qtdMacacosNaPonte) {
  if (qtdGorilasNaPonte == 0 && qtdMacacosNaPonte == 0) return 1;
  else                                                  return 0;
}