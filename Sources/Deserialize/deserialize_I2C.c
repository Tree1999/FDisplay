#include "../project_cfg.h"
#ifdef  DESERIALIZE_MODULE
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
#include <stdio.h>
#include "../../Headers/derivative.h"
#include "../../Headers/I2C.h"
#include "../../Headers/GPIO.h"
#include "deserialize_I2C.h"

/**********************************************************************************************
* External objects
**********************************************************************************************/

/**********************************************************************************************
* Global variables
**********************************************************************************************/

/**********************************************************************************************
* Constants and macros
**********************************************************************************************/
#define DES_MASTER_SEND_TO_SLAVE   0x58    /* the slave is DS90UB948*/
#define DES_MASTER_READ_FROM_SLAVE  0x59    /* the slave is DS90UB948*/

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
static void Deserialize_I2C_Enable_IC_INT(void);

/**********************************************************************************************
* Global functions
**********************************************************************************************/



/***********************************************************************************************
*
* @brief    deserialize_if_init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
void Deserialize_I2C_Init(void)
{
    I2C_ConfigType  I2C_Config = {{0}};

    /* Initialize I2C module with interrupt mode */
    I2C_Config.u16Slt = 0x0000;
    I2C_Config.u16F = 0x0090; /* Baud rate at 100Kbps, MULT=4,  SCL divider=48, 20M/(MULT*divider) */
    I2C_Config.sSetting.bMSTEn = 1;
    I2C_Config.sSetting.bIntEn = 1;
    I2C_Config.sSetting.bI2CEn = 1;

//    I2C1_SetCallBack(Deserialize_I2C_ISR_CallBack);

    I2C_Init(DESERIALIZE_I2C, &I2C_Config);
//    I2C_ClearStatus(CTP_IC,I2C_S_IICIF_MASK);
    Deserialize_I2C_Enable_IC_INT();
}

/***********************************************************************************************
*
* @brief    deserialize_if_init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
void Deserialize_I2C_Master_Send(UINT8 *send_data, UINT32 data_size)
{
    if((NULL==send_data) || (0 == data_size))
        return;

    /* send data */
//    I2C_IntDisable(CTP_IC);
    I2C_MasterSendWait(DESERIALIZE_I2C,DES_MASTER_SEND_TO_SLAVE,&send_data[0],data_size);
//    I2C_IntEnable(CTP_IC);
}
/***********************************************************************************************
*
* @brief    deserialize_if_init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
void Deserialize_I2C_Master_Read(UINT8 *read_data, UINT32 data_size)
{
    if((NULL==read_data) || (0 == data_size))
        return;
    /* read data */
//    I2C_IntDisable(CTP_IC);
    I2C_MasterReadWait(DESERIALIZE_I2C,DES_MASTER_READ_FROM_SLAVE,read_data,data_size);
//    I2C_IntEnable(CTP_IC);
}
/***********************************************************************************************
*
* @brief    deserialize_if_init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
void Deserialize_I2C_ISR_CallBack(void)
{
    
}

/***********************************************************************************************
*
* @brief    deserialize_if_init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
UINT32 Deserialize_I2C_Read_INT_Pin(void)
{
    return READ_INPUT(PTG,PTG0);
}

/***********************************************************************************************
*
* @brief    deserialize_if_init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
static void Deserialize_I2C_Enable_IC_INT(void)
{
    CONFIG_PIN_AS_GPIO(PTG,PTG0,INPUT);
    ENABLE_INPUT(PTG,PTG0);
}
#endif /* DESERIALIZE_MODULE */
