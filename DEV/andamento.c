#include "andamento.h"

int convert_potenciometro(int value){

    int passo = (value-POT_MIN)*180/(POT_MAX-POT_MIN)+20;
    //pot_max=2500 -> 200 bpm
    //pot_min=1500 -> 20 bpm
    int frequencia = passo/60;
    return frequencia;
}