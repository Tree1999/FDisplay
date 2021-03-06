#include "../project_cfg.h"
#ifdef LCD_MODULE
/**********************************************************************************************
* External objects
**********************************************************************************************/
#include "LCD_ctrl.h"
#include "LCD_data.h"

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
void LCD_Ctrl_Init(void)
{
    LCD_Data_Init();
}


#endif /* LCD_MODULE */
