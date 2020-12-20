/********************************************************************************
 * Camada de Abstração de Hardware do Conversor Analógico Digital		*
 ********************************************************************************
 * Definição da estrutura da memória do ADC					*
 ********************************************************************************/
typedef struct
{
  __IOM uint32_t CTRL;         /* Registrador de controle				-- TALVEZ SERÁ UTILIZADO	*/
  __IOM uint32_t CMD;          /* Registrador de comando				-- SERÁ UTILIZADO		*/
  __IM uint32_t  STATUS;       /* Registrador de estado					-- TALVEZ SERÁ UTILIZADO	*/
  __IOM uint32_t SINGLECTRL;   /* Registrador de controle das leituras unitárias	-- SERÁ UTILIZADO		*/
  __IOM uint32_t SCANCTRL;     /* Registrador de controle das leituras multiplas					*/
  __IOM uint32_t IEN;          /* Registrador de ativação das interrupções						*/
  __IM uint32_t  IF;           /* Registrador de flag de interrupções							*/
  __IOM uint32_t IFS;          /* Registrador de setar a flag de interrupções						*/
  __IOM uint32_t IFC;          /* Registrador de limpar a flag de interrupções						*/
  __IM uint32_t  SINGLEDATA;   /* Dado do resultado da conversão unitária		-- SERÁ UTILIZADO		*/
  __IM uint32_t  SCANDATA;     /* Dado do resultado da conversão múltipla						*/
  __IM uint32_t  SINGLEDATAP;  /* Prévia do dado do resultado da conversão unitária					*/
  __IM uint32_t  SCANDATAP;    /* Prévia do dado do resultado da conversão múltipla					*/
  __IOM uint32_t CAL;          /* Registrador de calibração								*/

  uint32_t       RESERVED0[1]; /* Reservado para uso futuro								*/
  __IOM uint32_t BIASPROG;     /* Registrador para programação de bias							*/
} ADC_TypeDef;                 /* Fim da estrutura 									*/

/********************************************************************************
 * Máscaras e bits de configurações das coisas que serão utilizadas		*
 ********************************************************************************/

/* Campos de bit para ADC CTRL */
#define _ADC_CTRL_RESETVALUE                    0x001F0000UL                                	/* Valor padrão ADC_CTRL */
#define _ADC_CTRL_MASK                          0x0F1F7F3BUL                                	/* Máscara para ADC_CTRL */
#define _ADC_CTRL_PRESC_SHIFT                   8                                           	/* Valor shiftado para ADC_PRESC */
#define _ADC_CTRL_PRESC_MASK                    0x7F00UL                                    	/* Máscara para ADC_PRESC */
#define _ADC_CTRL_PRESC_DEFAULT                 0x00000000UL                                	/* Modo DEFAULT para ADC_CTRL */
#define _ADC_CTRL_PRESC_NODIVISION              0x00000000UL                                	/* Modo NODIVISION para ADC_CTRL */
#define _ADC_CTRL_PRESC_QUARTER                 0x00000003UL                                	/* Modo para dividir ADC_CLK por 3+1 */
#define ADC_CTRL_PRESC_DEFAULT                  (_ADC_CTRL_PRESC_DEFAULT << 8)              	/* Modo DEFAULT shiftado para ADC_CTRL */
#define ADC_CTRL_PRESC_NODIVISION               (_ADC_CTRL_PRESC_NODIVISION << 8)           	/* Modo NODIVISION shiftado para ADC_CTRL */
#define ADC_CTRL_PRESC_QUARTER                  (_ADC_CTRL_PRESC_QUARTER << 8)               	/* Modo para dividir ADC_CLK por 4 */
#define _ADC_CTRL_TIMEBASE_SHIFT                16                                          	/* Valor shiftado para ADC_TIMEBASE */
#define _ADC_CTRL_TIMEBASE_MASK                 0x1F0000UL                                  	/* Máscara para ADC_TIMEBASE */
#define _ADC_CTRL_TIMEBASE_DEFAULT              0x0000001FUL                                	/* Modo DEFAULT para ADC_CTRL */
#define _ADC_CTRL_TIMEBASE_48MHZ                0x0000002FUL                                	/* 2F+1 ciclos de HFPERCLK em 48MHz em 1us*/
#define ADC_CTRL_TIMEBASE_DEFAULT               (_ADC_CTRL_TIMEBASE_DEFAULT << 16)          	/* Modo DEFAULT shiftado para ADC_CTRL */
#define ADC_CTRL_TIMEBASE_48MHZ                 (_ADC_CTRL_TIMEBASE_48MHZ << 16)              	/* Modo DEFAULT para ADC_CTRL */

/* Campos de bit para ADC CMD */
#define _ADC_CMD_RESETVALUE                     0x00000000UL                        		/* Valor padrão para ADC_CMD */
#define _ADC_CMD_MASK                           0x0000000FUL                        		/* Máscara para ADC_CMD */
#define ADC_CMD_SINGLESTART                     (0x1UL << 0)                        		/* Single Conversion Start */
#define _ADC_CMD_SINGLESTART_SHIFT              0                                   		/* Valor shiftado para ADC_SINGLESTART */
#define _ADC_CMD_SINGLESTART_MASK               0x1UL                               		/* Máscara para ADC_SINGLESTART */
#define _ADC_CMD_SINGLESTART_DEFAULT            0x00000000UL                        		/* Modo DEFAULT para ADC_CMD */
#define ADC_CMD_SINGLESTART_DEFAULT             (_ADC_CMD_SINGLESTART_DEFAULT << 0) 		/* Modo DEFAULT shiftado para ADC_CMD */
#define ADC_CMD_SINGLESTOP                      (0x1UL << 1)                        		/* Single Conversion Stop */
#define _ADC_CMD_SINGLESTOP_SHIFT               1                                   		/* Valor shiftado para ADC_SINGLESTOP */
#define _ADC_CMD_SINGLESTOP_MASK                0x2UL                               		/* Máscara para ADC_SINGLESTOP */
#define _ADC_CMD_SINGLESTOP_DEFAULT             0x00000000UL                        		/* Modo DEFAULT para ADC_CMD */
#define ADC_CMD_SINGLESTOP_DEFAULT              (_ADC_CMD_SINGLESTOP_DEFAULT << 1)  		/* Modo DEFAULT shiftado para ADC_CMD */

/* Campos de bit para ADC STATUS */
#define _ADC_STATUS_RESETVALUE                  0x00000000UL                             	/* Valor padrão para ADC_STATUS */
#define _ADC_STATUS_MASK                        0x07031303UL                             	/* Máscara para ADC_STATUS */
#define ADC_STATUS_SINGLEDV                     (0x1UL << 16)                            	/* Single Sample Data Valid */
#define _ADC_STATUS_SINGLEDV_SHIFT              16                                       	/* Valor shiftado para ADC_SINGLEDV */
#define _ADC_STATUS_SINGLEDV_MASK               0x10000UL                                	/* Máscara para ADC_SINGLEDV */
#define _ADC_STATUS_SINGLEDV_DEFAULT            0x00000000UL                             	/* Modo DEFAULT para ADC_STATUS */
#define ADC_STATUS_SINGLEDV_DEFAULT             (_ADC_STATUS_SINGLEDV_DEFAULT << 16)     	/* Modo DEFAULT shiftado para ADC_STATUS */

/* Campos de bit para ADC SINGLECTRL */
#define _ADC_SINGLECTRL_RESETVALUE              0x00000000UL                             /* Valor padrão para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_MASK                    0xF1F70F37UL                             /* Máscara para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_INPUTSEL_SHIFT          8                                        /* Valor shiftado para ADC_INPUTSEL */
#define _ADC_SINGLECTRL_INPUTSEL_MASK           0x00000F00UL                             /* Máscara para ADC_INPUTSEL */
#define _ADC_SINGLECTRL_INPUTSEL_DEFAULT        0x00000000UL                             /* Modo DEFAULT para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_INPUTSEL_CH0            0x00000000UL                             /* Modo CH0 para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_INPUTSEL_CH1            0x00000001UL                             /* Modo CH1 para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_INPUTSEL_CH2            0x00000002UL                             /* Modo CH2 para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_INPUTSEL_CH3            0x00000003UL                             /* Modo CH3 para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_INPUTSEL_CH4            0x00000004UL                             /* Modo CH4 para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_INPUTSEL_CH5            0x00000005UL                             /* Modo CH5 para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_INPUTSEL_CH6            0x00000006UL                             /* Modo CH6 para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_INPUTSEL_CH7            0x00000007UL                             /* Modo CH7 para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_INPUTSEL_DEFAULT         (_ADC_SINGLECTRL_INPUTSEL_DEFAULT << 8)  /* Modo DEFAULT shiftado para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_INPUTSEL_CH0             (_ADC_SINGLECTRL_INPUTSEL_CH0 << 8)      /* Modo shiftado CH0 para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_INPUTSEL_CH1             (_ADC_SINGLECTRL_INPUTSEL_CH1 << 8)      /* Modo shiftado CH1 para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_INPUTSEL_CH2             (_ADC_SINGLECTRL_INPUTSEL_CH2 << 8)      /* Modo shiftado CH2 para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_INPUTSEL_CH3             (_ADC_SINGLECTRL_INPUTSEL_CH3 << 8)      /* Modo shiftado CH3 para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_INPUTSEL_CH4             (_ADC_SINGLECTRL_INPUTSEL_CH4 << 8)      /* Modo shiftado CH4 para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_INPUTSEL_CH5             (_ADC_SINGLECTRL_INPUTSEL_CH5 << 8)      /* Modo shiftado CH5 para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_INPUTSEL_CH6             (_ADC_SINGLECTRL_INPUTSEL_CH6 << 8)      /* Modo shiftado CH6 para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_INPUTSEL_CH7             (_ADC_SINGLECTRL_INPUTSEL_CH7 << 8)      /* Modo shiftado CH7 para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_REF_SHIFT               16                                       /* Valor shiftado para ADC_REF */
#define _ADC_SINGLECTRL_REF_MASK                0x70000UL                                /* Máscara para ADC_REF */
#define _ADC_SINGLECTRL_REF_DEFAULT             0x00000000UL                             /* Modo DEFAULT para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_REF_VDD                 0x00000002UL                             /* Modo VDD para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_REF_DEFAULT              (_ADC_SINGLECTRL_REF_DEFAULT << 16)      /* Modo DEFAULT shiftado para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_REF_VDD                  (_ADC_SINGLECTRL_REF_VDD << 16)          /* Modo shiftado VDD para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_AT_SHIFT                20                                       /* Valor shiftado para ADC_AT */
#define _ADC_SINGLECTRL_AT_MASK                 0xF00000UL                               /* Máscara para ADC_AT */
#define _ADC_SINGLECTRL_AT_DEFAULT              0x00000000UL                             /* Modo DEFAULT para ADC_SINGLECTRL */
#define _ADC_SINGLECTRL_AT_16CYCLES             0x00000004UL                             /* Modo 16CYCLES para ADC_SINGLECTRL */
#define ADC_SINGLECTRL_AT_DEFAULT               (_ADC_SINGLECTRL_AT_DEFAULT << 20)       /* Modo shiftado DEFAULT for ADC_SINGLECTRL */
#define ADC_SINGLECTRL_AT_16CYCLES              (_ADC_SINGLECTRL_AT_16CYCLES << 20)      /* Modo shiftado 16CYCLES for ADC_SINGLECTRL */

/* Campos de bit para ADC SINGLEDATA */
#define _ADC_SINGLEDATA_RESETVALUE              0x00000000UL                        	/* Valor padrão para ADC_SINGLEDATA */
#define _ADC_SINGLEDATA_MASK                    0xFFFFFFFFUL                        	/* Máscara para ADC_SINGLEDATA */
#define _ADC_SINGLEDATA_DATA_SHIFT              0                                   	/* Valor shiftado para ADC_DATA */
#define _ADC_SINGLEDATA_DATA_MASK               0xFFFFFFFFUL                        	/* Máscara para ADC_DATA */
#define _ADC_SINGLEDATA_DATA_DEFAULT            0x00000000UL                        	/* Modo DEFAULT para ADC_SINGLEDATA */
#define ADC_SINGLEDATA_DATA_DEFAULT             (_ADC_SINGLEDATA_DATA_DEFAULT << 0) 	/* Modo DEFAULT shiftado para ADC_SINGLEDATA*/

/* Campos de bit para ADC SINGLEDATAP */
#define _ADC_SINGLEDATAP_RESETVALUE             0x00000000UL                          	/* Valor padrão para ADC_SINGLEDATAP */
#define _ADC_SINGLEDATAP_MASK                   0xFFFFFFFFUL                          	/* Máscara para ADC_SINGLEDATAP */
#define _ADC_SINGLEDATAP_DATAP_SHIFT            0                                     	/* Valor shiftado para ADC_DATAP */
#define _ADC_SINGLEDATAP_DATAP_MASK             0xFFFFFFFFUL                          	/* Máscara para ADC_DATAP */
#define _ADC_SINGLEDATAP_DATAP_DEFAULT          0x00000000UL                          	/* Modo DEFAULT para ADC_SINGLEDATAP */
#define ADC_SINGLEDATAP_DATAP_DEFAULT           (_ADC_SINGLEDATAP_DATAP_DEFAULT << 0) 	/* Modo DEFAULT shiftado para ADC_SINGLEDATAP*/

/** Fim da HAL do ADC */

