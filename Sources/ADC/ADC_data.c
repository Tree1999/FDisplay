#ifdef ADC_MODULE
/******************************************************************************								
*  Name: .c
*  Description: 
*  Project: C_demo
*  Auther:  shanghai tianma
*              R&D center
*              penghu
*  MCU: S9KEAZ128AMLH
*  Comment:
******************************************************************************/		
#include "ADC_data.h"
#include "../../Headers/adc.h"

/**********************************************************************************************
* External objects
**********************************************************************************************/


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
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
void ADC_Data_Init(void)
{
    ADC_ConfigType  ADC_Config={{0}};

    ADC_Config.u8ClockSource = CLOCK_SOURCE_BUS_CLOCK;
    ADC_Config.u8ClockDiv = ADC_ADIV_DIVIDE_4;
    ADC_Config.u8Mode = ADC_MODE_12BIT;
    ADC_Config.sSetting.bContinuousEn = 1;
    ADC_Config.u16PinControl = 0x7000;  /* disable I/0 control on ADC channel 12,13,14 */

    ADC_Init(ADC, &ADC_Config);
}

/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
UINT32 ADC_Data_Get_LED_NTC(void)
{
    return 0;
}

/***********************************************************************************************
*
* @brief    CTP_If_Init() - input power voltage
* @param    none
* @return   none
*
************************************************************************************************/
UINT32 ADC_Data_Get_Input_Vol(void)
{
    return ADC_PollRead(ADC,ADC_CHANNEL_AD14);
}

/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
UINT32 ADC_Data_PCB_Detect_Vol_High(void)
{
    return ADC_PollRead(ADC,ADC_CHANNEL_AD12);
}

/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
UINT32 ADC_Data_PCB_Detect_Vol_Low(void)
{
    return ADC_PollRead(ADC,ADC_CHANNEL_AD13);
}

#endif /* ADC_MODULE */