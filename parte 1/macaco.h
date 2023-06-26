#ifndef MACACO_H
#define MACACO_H

typedef struct {
  int id;
  int ladoAtual; // 0 = esquerda, 1 = direita
} Macaco;

int getIdMacaco(Macaco macaco);

Macaco setIdMacaco(Macaco macaco, int id);

int getLadoAtual(Macaco macaco);

Macaco setLadoAtual(Macaco macaco, int ladoAtual);

Macaco atravessaMacaco(Macaco macaco);

int podeAtravessarMacaco(Macaco macaco, 
                        Macaco macacosNaPonte[], 
                        int qtdMacacosNaPonte, 
                        int qtdGorilasNaPonte);

#endif // MACACO_H