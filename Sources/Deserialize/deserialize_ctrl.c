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

/*******************************************************************************
* Includes
********************************************************************************/
#include "deserialize_ctrl.h"
#include "deserialize_data.h"

/***********************************************************************************************
*
* @brief    deserialize_ctrl_init - Initalize data layer
* @param    none
* @return   none
*
************************************************************************************************/  
void Deserialize_Ctrl_Init(void)
{
    Deserialize_Data_Init();
}

#endif /* DESERIALIZE_MODULE */
