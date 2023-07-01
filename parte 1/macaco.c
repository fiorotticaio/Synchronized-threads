#include "macaco.h"

int getIdMacaco(Macaco macaco) { 
  return macaco.id;
}

Macaco setIdMacaco(Macaco macaco, int id) {
  macaco.id = id;
  return macaco;
}

int getLadoOrigemMacaco(Macaco macaco) {
  return macaco.ladoOrigem;
}

Macaco setLadoOrigemMacaco(Macaco macaco, int LadoOrigem) {
  macaco.ladoOrigem = LadoOrigem;
  return macaco;
}

int getLadoDestinoMacaco(Macaco macaco) {
  return macaco.ladoDestino;
}

Macaco setLadoDestinoMacaco(Macaco macaco, int LadoDestino) {
  macaco.ladoDestino = LadoDestino;
  return macaco;
}

static int temMacacoNaDirecaoOposta(Macaco macaco, Macaco macacosNaPonte[], int qtdMacacosNaPonte) {
  int i = 0;
  for (i = 0; i < qtdMacacosNaPonte; i++) {
    if (macaco.id != macacosNaPonte[i].id &&
      macaco.ladoOrigem == macacosNaPonte[i].ladoDestino) // Tem macaco na ponte que está indo para a direção oposta
    {
      return 1;
    }
  }
  return 0;
}

int podeAtravessarMacaco(Macaco macaco, 
                        Macaco macacosNaPonte[], 
                        int qtdMacacosNaPonte, 
                        int qtdGorilasNaPonte,
                        int qtdGorilasQueQueremAtravessar)  
{
  if (qtdGorilasNaPonte > 0)                                                     return 0;
  else if (qtdGorilasQueQueremAtravessar > 0)                                    return 0; // Gorilas tem prioridade
  else if (qtdMacacosNaPonte == 0)                                               return 1; // TODO: acho que não precisa disso
  else if (!temMacacoNaDirecaoOposta(macaco, macacosNaPonte, qtdMacacosNaPonte)) return 1;
  else                                                                           return 0;
}
