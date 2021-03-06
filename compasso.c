#include "compasso.h"

int estado;
int estadoCompasso;

static char VetorEstado[6][5] = {"2/4", "3/4", "4/4", "4/4", "5/4", "6/4"};
static int VetorPasso[6] = {1, 2, 3, 3, 4, 5};

static char* VetorEstadoCompasso[6][6] = {
    {"Forte", "Fraco", "Forte", "Fraco", "Forte", "Fraco"},
    {"Forte", "Fraco", "Fraco", "Forte", "Fraco", "Fraco"},
    {"Forte", "Fraco", "Fraco", "Fraco", "Forte", "Fraco"},
    {"Forte", "Fraco", "Meio", "Fraco", "Forte", "Fraco"},
    {"Forte", "Fraco", "Fraco", "Meio", "Fraco", "Forte"},
    {"Forte", "Fraco", "Fraco", "Meio", "Fraco", "Fraco"}
};
static int VetorEstadoCompassoIntencidade[6][6] = {
    {100, 5, 100, 5, 100, 5},
    {100, 5, 5, 100, 5, 5},
    {100, 5, 5, 5, 100, 5},
    {100, 5, 30, 5, 100, 5},
    {100, 5, 5, 30, 5, 100},
    {100, 5, 5, 30, 5, 5}
};

void Compasso_Init() {
    estado = 0;
    EstadoCompasso_Reset();
}

char* ProximoEstado() {
    if (estado < 5){
        estado = estado+1;
    }
    else{
        estado = 0;
    }       
    EstadoCompasso_Reset();
    return VetorEstado[estado];
}

char* AnteriorEstado() {
    if (estado > 0)
        estado--;
    else
        estado = 5;    
    EstadoCompasso_Reset();
    return VetorEstado[estado];
}

    // ------------Estado do Compaso----------------------
    void EstadoCompasso_Reset() {
        estadoCompasso = 0;
    }

    char* ProximoEstadoCompasso() {
        if (estadoCompasso < VetorPasso[estado]){
            estadoCompasso = estadoCompasso+1;
        }
        else{
            estadoCompasso = 0;
        }       
        return VetorEstadoCompasso[estado][estadoCompasso];
    }

    int GetEstadoCompassoIntensidade(){
        return VetorEstadoCompassoIntencidade[estado][estadoCompasso];
    }