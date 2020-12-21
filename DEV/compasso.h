#include <string.h>
#ifndef COMPASSO_H
    #define COMPASSO_H

    int estado;
    string EstadoCompasso;
    string VetorEstado[6] = {"2/4", "3/4", "4/4", "5/4", "6/4", "7/4"};
    string DoisQuartos[6]={"Forte", "Fraco", "Forte", "Fraco", "Forte", "Fraco"};
    string TresQuartos[6]={"Forte", "Fraco", "Fraco", "Forte", "Fraco", "Fraco"};
    string QuatroQuartos[6]={"Forte", "Fraco", "Fraco", "Fraco", "Forte", "Fraco"};
    string CincoQuartos[6]={"Forte", "Fraco", "Meio", "Fraco", "Forte", "Fraco"};
    string SeisQuartos[6]={"Forte", "Fraco", "Fraco", "Meio", "Fraco", "Forte"};
    string SeteQuartos[6]={"Forte", "Fraco", "Fraco", "Meio", "Fraco", "Fraco"};
    string VetorEstadoCompasso[6] = {DoisQuartos, TresQuartos, QuatroQuartos, CincoQuartos, SeisQuartos, SeteQuartos};


    void Compasso_Init();
    string ProximoEstado();

#endif

