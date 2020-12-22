#ifndef ANDAMENTO_H
#define ANDAMENTO_H

#define POT_MIN 20
#define POT_MAX 3500

int     convert_potenciometro();
void    Andamento_Init(void);

// Get
int getTaskID();
int getPasso();
int getPotenciometro();

//Set
void setTaskID(int value);
void setPasso(int value);
void setPotenciometro(int value);

#endif
