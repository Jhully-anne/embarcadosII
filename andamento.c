#include "andamento.h"

// Propriedades
static int potenciometro;
int passo;
int task_ID;


int convert_potenciometro(){

    int passo = (potenciometro-POT_MIN)*180/(POT_MAX-POT_MIN)+20;
    return (passo < 20 ? 20 : (passo > 200 ? 200 : passo));
}

void Andamento_Init(void){
    potenciometro = 0;
    passo = 20;
    task_ID = 0;
}

// Get
int getTaskID(){return task_ID;}
int getPasso(){return passo;}
int getPotenciometro(){return potenciometro;}

//Set
void setTaskID(int value){task_ID = value;}
void setPasso(int value){passo = value;}
void setPotenciometro(int value){potenciometro = value;}