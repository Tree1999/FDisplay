/******************************************************************************								
*  Name: Main.c
*  Description: 
*  Project: C_demo
*  Auther:  shanghai tianma
*              R&D center
*              penghu
*  MCU: S9KEAZ128AMLH
*  Comment:
******************************************************************************/		
/**********************************************************************************************
* External objects
**********************************************************************************************/
#include <stdio.h>
/*Header file from MCU supplier*/
#include "../Headers/derivative.h" /* include peripheral declarations */
#include "../Headers/CLK.h"
#include "../Headers/GPIO.h"

/* user defined */
#include "project_cfg.h" /* this header file is must first */
#ifdef  DESERIALIZE_MODULE
#include "Deserialize/deserialize_if.h"
#endif  
#ifdef  CTP_MODULE
#include "CTP/CTP_if.h"
#endif  
#ifdef EEPROM_MODULE
#include "EEPROM/EEPROM_if.h"
#endif 
#ifdef LED_MODULE
#include "LED/LED_if.h"
#endif 
#ifdef LCD_MODULE
#include "LCD/LCD_if.h"
#endif
#ifdef ADC_MODULE
#include "ADC/ADC_if.h"
#endif

#include "KBI/KBI_if.h"

/**********************************************************************************************
* Global variables
**********************************************************************************************/

/**********************************************************************************************
* Constants and macros
**********************************************************************************************/


/**********************************************************************************************
* Local types
**********************************************************************************************/


/**********************************************************************************************
* Local function prototypes
*********************************************************************************************/

/**********************************************************************************************
* Local variables
**********************************************************************************************/


/**********************************************************************************************
* Local functions
**********************************************************************************************/


/**********************************************************************************************
* Global functions
**********************************************************************************************/



/***********************************************************************************************
*
* @brief    main() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
int main(void)
{	
    UINT32 i=1;
	
    Clk_Init();

	CONFIG_PIN_AS_GPIO(PTB,PTB0,OUTPUT);  /* LCD_RESET(PTB0):*/
    OUTPUT_SET(PTB,PTB0);
	
    CONFIG_PIN_AS_GPIO(PTB,PTB1,OUTPUT);  /* LCD_STBYB(PTB1):  request LCD into standby */
    OUTPUT_CLEAR(PTB,PTB1);
#if 0

    CONFIG_PIN_AS_GPIO(PTD,PTD4,OUTPUT); 
    while(1)
    {
        OUTPUT_SET(PTD,PTD4);
        
        for(i=0; i<1000; i++);
        
        OUTPUT_CLEAR(PTD,PTD4);
        
        for(i=0; i<1000; i++);
    }
#endif    
#ifdef  DESERIALIZE_MODULE
//    CONFIG_PIN_AS_GPIO(PTD,PTD5,OUTPUT);
//    OUTPUT_SET(PTD,PTD5);

    Deserialize_If_Init();
#endif
	

#ifdef LCD_MODULE
    LCD_If_Init();
#endif

	
#ifdef ADC_MODULE
    ADC_If_Init();
#endif

#ifdef  CTP_MODULE
    CTP_If_Init();
#endif 

#ifdef EEPROM_MODULE
    EEPROM_If_Init();
#endif 

#ifdef LED_MODULE
    LED_If_Init();
#endif


	
    KBI_If_Init();

#ifdef  CTP_MODULE
    CTP_If_Task();
#endif
	while(1)
	{
		i = GPIO_READ_INPUT(PTD,PTD3);
		if(i==1)
			OUTPUT_SET(PTD,PTD4);
		else
			OUTPUT_CLEAR(PTD,PTD4);
	}
}



void NMI_Handler(void)
{
    while(1);
}

/**********************************************************************************
Chang history:


**********************************************************************************/

