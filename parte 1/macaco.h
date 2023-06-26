#ifndef MACACO_H
#define MACACO_H

typedef struct {
  int id;
  int ladoOrigem; // 0 = esquerda, 1 = direita
  int ladoDestino; // 0 = esquerda, 1 = direita
} Macaco;

int getIdMacaco(Macaco macaco);

Macaco setIdMacaco(Macaco macaco, int id);

int getLadoOrigemMacaco(Macaco macaco);

Macaco setLadoOrigemMacaco(Macaco macaco, int LadoOrigem);

int getLadoDestinoMacaco(Macaco macaco);

Macaco setLadoDestinoMacaco(Macaco macaco, int LadoDestino);

int podeAtravessarMacaco(Macaco macaco, Macaco macacosNaPonte[], int qtdMacacosNaPonte, int qtdGorilasNaPonte, int qtdGorilasQueQueremAtravessar);

#endif // MACACO_H