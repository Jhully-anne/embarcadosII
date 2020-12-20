/** ***************************************************************************
 * @file    main.c
 * @brief   Simple UART Demo for EFM32GG_STK3700
 * @version 1.0
******************************************************************************/

#include <stdint.h>
/*
 * Including this file, it is possible to define which processor using command line
 * E.g. -DEFM32GG995F1024
 * The alternative is to include the processor specific file directly
 * #include "efm32gg995f1024.h"
 */
#include "em_device.h"
#include "adc.h"
//#include "touch.h"
#include "clock_efm32gg2.h"


#include "ministdio.h"
#include "led.h"
//#include "uart2.h"
//#include "tt_tasks.h"

// #define CH4 ADC_SINGLECTRL_INPUTSEL_CH4
// #define CH5 ADC_SINGLECTRL_INPUTSEL_CH5


/*************************************************************************//**
 * @brief  Sys Tick Handler
 */
const int TickDivisor = 1000; // milliseconds

volatile uint64_t tick = 0;

void SysTick_Handler (void) {
static int counter = 0;

    tick++;

    if( counter == 0 ) {
        counter = TickDivisor;
        // Process every second
        LED_Toggle(LED1);
    }
    counter--;
}


void Delay(int delay) {
uint64_t l = tick+delay;

    while(tick<l) {}

}


/**************************************************************************//**
 * @brief  Input/output functions for ministdio functions
 */

///@{
// int putchar(int c) { UART_SendChar(c); return 0; }
// int getchar(int c) { return UART_GetChar(); }
///@}

// void Sensor_Listening(void) {
//     static int8_t state = 0;
//     static int potenciometro = 0;
    
//     switch(state) {
// 		case 0:
// 		    ADC_SingleRequest(CH4);
// 		    state = 1;
// 		break;
// 		case 1:
// 		    potenciometro = ADC_SingleRead();
// 			state = 0;
// 			printf("%d\n",potenciometro);
// 		break;
// 	}
	
// }

/**************************************************************************//**
 * @brief  Main function
 *
 * @note   Using external crystal oscillator
 *         HFCLK = HFXO
 *         HFCORECLK = HFCLK
 *         HFPERCLK  = HFCLK
 */

int main(void) {
//char line[100];
//int v;
uint32_t v;
    /* Configure LEDs */
    LED_Init(LED1|LED2);

    // Set clock source to external crystal: 48 MHz
    (void) SystemCoreClockSet(CLOCK_HFXO,1,1);

    /* Turn on LEDs */
    LED_Write(0,LED1|LED2);


    // /* Inicia as tarefas */
    // Task_Init();
    // Task_Add(Sensor_Listening,100,1);//Chamado a cada 10*(0.5)ms (200Hz) e fica 1*(0.5)ms fazendo a função. Se tiver printf tem que ser alto



    /* Configure SysTick */
    SysTick_Config(SystemCoreClock/TickDivisor);


    ADC_Init(500000);
    //GetCalibrationValues();

    //Touch_Init();

    // /* Configure UART */
    // UART_Init();
    // __enable_irq();

    printf("\r\n\n\n\rHello\n\r");
    printf("\nOi 1\n");
    while (1) {

        Delay(1000);
        printf("\nOi 2\n");
        Delay(2000);
        
        //v = Touch_ReadChannel(ADC_CH4);
        v = ADC_Read(ADC_CH4);
        

        printf("\nOi: %d\n", (int)v);


        // printf("\r\n\n\n\rWhat is your name?\n");
        // fgets(line,99,stdin);
        // printf("Hello %s\n",line);
        
        
        //Task_Dispatch();
        Delay(1000);
    }

}
