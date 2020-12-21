#include "compasso.h"

void Compasso_Init() {
    estado = 0;
}
string ProximoEstado() {
    if estado<6{
        estado = estado+1;
    }
    else{
        estado = 0;
    }       
    EstadoCompasso = VetorEstadoCompasso[estado];
    return VetorEstado[estado], EstadoCompasso;
}
