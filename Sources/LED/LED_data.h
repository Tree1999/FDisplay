#include "../project_cfg.h"
#ifdef  LED_MODULE
#ifndef  _LED_DATA_H_
#define _LED_DATA_H_
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
#include "../../Headers/derivative.h" 

/**********************************************************************************************
* External objects
**********************************************************************************************/


/**********************************************************************************************
* Global variables
**********************************************************************************************/

/**********************************************************************************************
* Constants and macros
**********************************************************************************************/
/* the slave device address: LP8860 */
#define LED_SLAVE_ADDRESS_WRITE 0x5A
#define LED_SLAVE_ADDRESS_READ  0x5B

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
void LED_Data_Init(void);

#endif  /* _LED_DATA_H_ */
#endif /* LED_MODULE */
