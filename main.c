/** ***************************************************************************
 * @file    main.c
 * @brief   Simple UART Demo for EFM32GG_STK3700
 * @version 1.0
******************************************************************************/

#include <stdint.h>
#include "tt_tasks.h"
/*
 * Including this file, it is possible to define which processor using command line
 * E.g. -DEFM32GG995F1024
 * The alternative is to include the processor specific file directly
 * #include "efm32gg995f1024.h"
 */

#include "em_device.h"
#include "em_emu.h"
#include "em_chip.h"
#include "adc.h"
#include "clock_efm32gg2.h"


#include "ministdio.h"
#include "led.h"
#include "button.h"
#include "lcd.h"
#include "compasso.h"
#include "andamento.h"
#include "pwm.h"


#define CH4 0x00000004UL << 8

#define DELAYVAL 2


/*************************************************************************//**
 * @brief  Sys Tick Handler
 */
const int TickDivisor = 1000; // milliseconds

volatile uint64_t tick = 0;

/** ***************************************************************************
 * @brief  SysTick interrupt handler
 *
 * @note   Just calls Task_Update
 * @note   Called every 1 ms
 */

void SysTick_Handler(void) {
    Task_Update();

    static int counter = 0;             // must be static

    tick++;
    
    if( counter != 0 ) {
        counter--;
    } else {
        counter = TickDivisor;
        LED_Toggle(LED1);
    }
}


void Delay(int delay) {
uint64_t l = tick+delay;

    while(tick<l) {}

}

void Estado_Compasso(void) {
    //Vai para o próximo estado do compasso (Forte, Fraco ou Meio)
    printf("\n%s\n",ProximoEstadoCompasso());

    //PWM -> Atualiza itencidade do LED/Buzzer
    set_dutyCyclePercent(GetEstadoCompassoIntensidade());

    //Tempo em que o som/luz fica ativo 
    Delay(60000/(getPasso()*3));

    //Zera Som/Luz
    set_dutyCyclePercent(0);
}

void Create_Task_Compasso(void){
    int task_ID = getTaskID();

    if(task_ID != 0){
            Task_Delete(task_ID);
    }
    task_ID = Task_Add(Estado_Compasso,60000/getPasso(),1);

    setTaskID(task_ID);
}
int cont = 0;
void Potenciometro_Listening(void) {
    static int8_t state = 0;
    static int potenciometro_new = 0;
    int passo_new = 20;
    
    switch(state) {
		case 0://Indica que vai ler potenciômetro
		    ADC_StartReading(CH4);

            //Vai pro estado de leitura
		    state = 1;
		break;
		case 1://Lê o potenciômetro
		    potenciometro_new = ADC_GetReading(CH4);

            //Verifica se é direferente do valor anterior
            if(potenciometro_new != getPotenciometro()){
                setPotenciometro(potenciometro_new);
                passo_new = convert_potenciometro();

                //Debounce do passo
                if(passo_new != getPasso())
                    cont++;
                else
                    cont = 0;
                //Se o passo for diferente em 10 leituras seguidas -> Ativa
                if(cont == 10){
                    //Atualiza o passo
                    setPasso(passo_new);

                    //Cria task com novo passo
                    Create_Task_Compasso();

                    //DEBUG
                    printf("Potenciometro: %d => %d\n",getPotenciometro(), getPasso());
                    cont = 0;
                }
            }

            //Volta pro estado Zero
			state = 0;
		break;
	}
	
}





void Button_Listening(void) {
    char *str;
    uint32_t b = Button_ReadReleased();
    if( b&BUTTON1 ) {
        str = ProximoEstado();
        LCD_WriteString(str);
        printf("\n---  %s  ---\n",str);
        Create_Task_Compasso();
    }
    if( b&BUTTON2 ) {
        str = AnteriorEstado();
        LCD_WriteString(str);
        printf("\n---  %s  ---\n",str);
        Create_Task_Compasso();
    }
}


/**************************************************************************//**
 * @brief  Main function
 *
 * @note   Using external crystal oscillator
 *         HFCLK = HFXO
 *         HFCORECLK = HFCLK
 *         HFPERCLK  = HFCLK
 */

int main(void) {
    Compasso_Init();
    Andamento_Init();


    //PWM
    CHIP_Init();
    initGpio();
    initTimer();
    
    /* Configure LEDs */
    LED_Init(LED1|LED2);

    // Set clock source to external crystal: 48 MHz
    (void) SystemCoreClockSet(CLOCK_HFXO,1,1);

    /* Configure buttons */
    Button_Init(BUTTON1|BUTTON2);

    /*  Configura o ADC */
    ADC_Init(500000);
    ADC_ConfigChannel(CH4,0);

    // /* Inicia as tarefas */
    Task_Init();
    Task_Add(Button_Listening,100,1);//Chamado a cada 10*(0.5)ms (200Hz) e fica 1*(0.5)ms fazendo a função. Se tiver printf tem que ser alto
    Task_Add(Potenciometro_Listening,100,1);




    /* Configure SysTick */
    SysTick_Config(SystemCoreClock/TickDivisor);

    /* Configure LCD */
    LCD_Init();

    LCD_SetAll();
    Delay(DELAYVAL);

    LCD_ClearAll();
    Delay(DELAYVAL);

    printf("\r\n\n\n\rHello\n\r");
    while (1) {
        Task_Dispatch();
        EMU_EnterEM1();
    }

}
