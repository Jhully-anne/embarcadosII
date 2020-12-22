#ifndef PWM_H
#define PWM_H

void TIMER1_IRQHandler(void);
void initGpio(void);
void initTimer(void);
void set_dutyCyclePercent(int value);

#endif