#include "macaco.h"

int getIdMacaco(Macaco macaco) { 
  return macaco.id;
}

Macaco setIdMacaco(Macaco macaco, int id) {
  macaco.id = id;
  return macaco;
}

int getLadoAtual(Macaco macaco) {
  return macaco.ladoAtual;
}

Macaco setLadoAtual(Macaco macaco, int ladoAtual) {
  macaco.ladoAtual = ladoAtual;
  return macaco;
}

Macaco trocarLado(Macaco macaco) {
  if (macaco.ladoAtual == 0) macaco.ladoAtual = 1;
  else                        macaco.ladoAtual = 0;
  return macaco;
}

static int temMacacoNaMesmaDirecao(Macaco macaco, Macaco macacosNaPonte[], int qtdMacacosNaPonte) {
  int i = 0;
  for (i = 0; i < qtdMacacosNaPonte; i++) {
    if (macaco.id != macacosNaPonte[i].id && 
        macaco.ladoAtual == macacosNaPonte[i].ladoAtual) 
    {
      return 1;
    }
  }
  return 0;
}

int podeAtravessarMacaco(Macaco macaco, 
                        Macaco macacosNaPonte[], 
                        int qtdMacacosNaPonte, 
                        int qtdGorilasNaPonte)  
{
  if (qtdGorilasNaPonte > 0)                                                    return 0;
  else if (qtdMacacosNaPonte == 0)                                              return 1;
  else if (!temMacacoNaMesmaDirecao(macaco, macacosNaPonte, qtdMacacosNaPonte)) return 1;
  else                                                                          return 0;
}
