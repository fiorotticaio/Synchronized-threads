#ifndef GORILA_H
#define GORILA_H

typedef struct {
  int id;
  int ladoOrigem; // 0 = esquerda, 1 = direita
  int ladoDestino; // 0 = esquerda, 1 = direita
} Gorila;

int getIdGorila(Gorila gorila);

Gorila setIdGorila(Gorila gorila, int id);

int getLadoOrigemGorila(Gorila gorila);

Gorila setLadoOrigemGorila(Gorila gorila, int ladoOrigem);

int getLadoDestinoGorila(Gorila gorila);

Gorila setLadoDestinoGorila(Gorila gorila, int ladoDestino);

int podeAtravessarGorila(int qtdGorilasNaPonte, int qtdMacacosNaPonte);

#endif // GORILA_H