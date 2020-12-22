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
//#include "gpio.h"

#include "em_device.h"
#include "em_emu.h"
#include "em_chip.h"
//#include "gpio.h"

#include "adc.h"
//#include "touch.h"
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

int tempo = 1000;

//#include "uart2.h"
//#include "tt_tasks.h"

// #define CH4 ADC_SINGLECTRL_INPUTSEL_CH4
// #define CH5 ADC_SINGLECTRL_INPUTSEL_CH5



/*************************************************************************//**
 * @brief  Sys Tick Handler
 */
const int TickDivisor = 1000; // milliseconds

volatile uint64_t tick = 0;

// void SysTick_Handler (void) {
// static int counter = 0;

//     tick++;

//     if( counter == 0 ) {
//         counter = TickDivisor;
//         // Process every second
//         LED_Toggle(LED1);
//     }
//     counter--;
// }

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


/**************************************************************************//**
 * @brief  Input/output functions for ministdio functions
 */

///@{
// int putchar(int c) { UART_SendChar(c); return 0; }
// int getchar(int c) { return UART_GetChar(); }
///@}

static int potenciometro;
int passo;

int task_ID;

void Estado_Compasso(void) {
    printf("\n%s\n",ProximoEstadoCompasso());
    set_dutyCyclePercent(GetEstadoCompassoIntensidade());
    Delay(60000/(passo*3));
    set_dutyCyclePercent(0);
}

void Task_Compasso(void){
    if(task_ID != 0){
            Task_Delete(task_ID);
    }
    task_ID = Task_Add(Estado_Compasso,1000*60/passo,1);
}
int cont = 0;
void Potenciometro_Listening(void) {
    static int8_t state = 0;
    static int potenciometro_new = 0;
    int passo_new = 20;
    potenciometro = 0;
    
    switch(state) {
		case 0:
		    ADC_StartReading(CH4);
		    state = 1;
		break;
		case 1:
		    potenciometro_new = ADC_GetReading(CH4);
			state = 0;
            if(potenciometro_new != potenciometro){
                potenciometro = potenciometro_new;

                passo_new = convert_potenciometro(potenciometro);
                if(passo_new != passo){
                    cont++;
                }
                else
                {
                    cont = 0;
                }
                
                if(cont == 10){
                    passo = passo_new;
                    Task_Compasso();
                    printf("Potenciometro: %d => %d\n",potenciometro, passo);
                    cont = 0;
                }
            }
			
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
        Task_Compasso();
    }
    if( b&BUTTON2 ) {
        str = AnteriorEstado();
        LCD_WriteString(str);
        printf("\n---  %s  ---\n",str);
        Task_Compasso();
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
    task_ID = 0;
    passo = 20;


    //PWM
    CHIP_Init();
    initGpio();
    initTimer();
    


//char line[100];
//int v;
//uint32_t v;
    /* Configure LEDs */
    LED_Init(LED1|LED2);

    // Set clock source to external crystal: 48 MHz
    (void) SystemCoreClockSet(CLOCK_HFXO,1,1);

    /* Configure buttons */
    Button_Init(BUTTON1|BUTTON2);

    
    

    /* Turn on LEDs */
    //LED_Write(0,LED1|LED2);

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


        /* Configure Pins in GPIOE */
    //GPIO_Init(GPIOD,CH4,0);       // LED pins configured as output
    //GPIO_ConfigPins(GPIOD,CH4,GPIO_MODE_INPUT);

    //ADC_Init(500000);
    //ADC_ConfigChannel(ADC_CH4,0);
    //GetCalibrationValues();

    //Touch_Init();

    // /* Configure UART */
    // UART_Init();
    // __enable_irq();

    printf("\r\n\n\n\rHello\n\r");
    printf("\nOi 0\n");
    //int i = 0;
    while (1) {
        Task_Dispatch();
        EMU_EnterEM1();

         //Delay(500);
        // printf("\nOi 0\n");
        //printf("\nOi %d\n",i);
        //i++;
        // //Delay(2000);
        
        // //v = Touch_ReadChannel(ADC_CH4);
        // //ADC_StartReading(ADC_CH4);

        //Delay(500);
        // //v = ADC_GetReading(ADC_CH4);
        // v = ADC_Read(ADC_CH4);
        //v = GPIO_ReadPins(GPIOD);
        //v = ~(v)&CH4;
        

        //printf("\nValue: %d\n", (int)v);


        // // printf("\r\n\n\n\rWhat is your name?\n");
        // // fgets(line,99,stdin);
        // // printf("Hello %s\n",line);
        
        
        // //Task_Dispatch();
        // //Delay(1000);
        // i++;
    }

}
