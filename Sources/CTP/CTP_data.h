#ifdef  CTP_MODULE
#ifndef _CTP_DATA_H_
#define _CTP_DATA_H_
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

/**********************************************************************************************
* External objects
**********************************************************************************************/
#include "../../Headers/derivative.h" 

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
extern void CTP_Data_Init(void);
extern void CTP_Data_Write(void);
extern void CTP_Data_Read(void);

#endif /* _CTP_DATA_H_ */
#endif /* CTP_MODULE */