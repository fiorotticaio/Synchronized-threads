#ifndef GORILA_H
#define GORILA_H

typedef struct {
  int id;
  int ladoAtual;
} Gorila;

int getIdGorila(Gorila gorila);

Gorila setIdGorila(Gorila gorila, int id);

int getLadoAtualGorila(Gorila gorila);

Gorila setLadoAtualGorila(Gorila gorila, int ladoAtual);

Gorila trocarLadoGorila(Gorila gorila);

int podeAtravessarGorila(int qtdGorilasNaPonte, int qtdMacacosNaPonte);

#endif // GORILA_H