#include "andamento.h"
#include "compasso.h"

#include <stdio.h>

int main()
{

    int convert = convert_potenciometro(13);
    //Compasso_Init();

    printf("%d\n",convert);
   
    printf("%s\n",ProximoEstado());
    printf("%s\n",ProximoEstado());
    printf("%s\n",ProximoEstado());

    printf("%s\n",ProximoEstado());
    printf("%s\n",ProximoEstadoCompasso());
    printf("%s\n",ProximoEstadoCompasso());
    printf("%s\n",ProximoEstadoCompasso());
    printf("%s\n",ProximoEstadoCompasso());

    printf("%s\n",ProximoEstado());
    printf("%s\n",ProximoEstado());
    printf("%s\n",ProximoEstado());
    printf("%s\n",ProximoEstado());
    printf("%s\n",ProximoEstado());
    
    //printf("%s\n",VetorEstadoCompasso[3][1]);
}