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
#include "KBI_if.h"
#include "../../Headers/kbi.h"
#ifdef  CTP_MODULE
#include "../CTP/CTP_if.h"
#endif  

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
typedef void (*SKBI_FUNCTION)(void);

static SKBI_FUNCTION sKBI1_Function_Table[KBI_MAX_PINS_PER_PORT]=
{
    NULL,   /* KBI1_P0 */
    NULL,   /* KBI1_P1 */
    NULL,   /* KBI1_P2 */
    NULL,   /* KBI1_P3 */
    NULL,   /* KBI1_P4 */
    NULL,   /* KBI1_P5 */
    NULL,   /* KBI1_P6 */
    NULL,   /* KBI1_P7 */
    NULL,   /* KBI1_P8 */
    NULL,   /* KBI1_P9 */
    NULL,   /* KBI1_P10 */
    NULL,   /* KBI1_P11 */
    NULL,   /* KBI1_P12 */
    NULL,   /* KBI1_P13 */
    NULL,   /* KBI1_P14 */
    NULL,   /* KBI1_P15 */
#ifdef  CTP_MODULE
    CTP_If_Touch_Interrupt_Notice,   /* KBI1_P16 */
#else
    NULL,   /* KBI1_P16 */
#endif
    NULL,   /* KBI1_P17 */
    NULL,   /* KBI1_P18 */
    NULL,   /* KBI1_P19 */
    NULL,   /* KBI1_P20 */
    NULL,   /* KBI1_P21 */
    NULL,   /* KBI1_P22 */
    NULL,   /* KBI1_P23 */
    NULL,   /* KBI1_P24 */
    NULL,   /* KBI1_P25 */
    NULL,   /* KBI1_P26 */
    NULL,   /* KBI1_P27 */
    NULL,   /* KBI1_P28 */
    NULL,   /* KBI1_P29 */
    NULL,   /* KBI1_P30 */
    NULL    /* KBI1_P31 */
};
/**********************************************************************************************
* Local function prototypes
*********************************************************************************************/

/**********************************************************************************************
* Local variables
**********************************************************************************************/


/**********************************************************************************************
* Local functions
**********************************************************************************************/
static void KBI1_Handler(void);


/**********************************************************************************************
* Global functions
**********************************************************************************************/
/***********************************************************************************************
*
* @brief    KBI_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
void KBI_If_Init(void)
{
    UINT32          i;
    KBI_ConfigType  KBIConfig={{0}};

    /* Disable all the KBI pins */
    for (i = 0; i < KBI_MAX_PINS_PER_PORT; i++)
    {
        KBIConfig.sPin[i].bEn	 = 0;
    }

    KBIConfig.sBits.bRstKbsp   = 1;			/* Writing a 1 to RSTKBSP is to clear the KBIxSP Register*/
    KBIConfig.sBits.bKbspEn   	= 1;		/* The latched value in KBxSP register while interrupt flag occur to be read.*/
    KBIConfig.sBits.bMode   	= KBI_MODE_EDGE_ONLY;
    KBIConfig.sBits.bIntEn  	= 1;

    /*Falling edge/low level select; KBI1_P16 channel enable */
    KBIConfig.sPin[16].bEdge    = KBI_FALLING_EDGE_LOW_LEVEL;
    KBIConfig.sPin[16].bEn      = 1;

    KBI_SetCallback(pKBI1, &KBI1_Handler);
    KBI_Init(pKBI1, &KBIConfig);
    
}

/***********************************************************************************************
*
* @brief    KBI1_Handler() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
static void KBI1_Handler(void)
{
    UINT32  i=0;
    UINT32 sKBI1_SP=0;

    sKBI1_SP = KBI_GetSP(pKBI1);    

    for(i=0; i< KBI_MAX_PINS_PER_PORT; i++)
    {
        if((sKBI1_SP&(0x01<<i)) && sKBI1_Function_Table[i])
        {
            sKBI1_Function_Table[i]();
        }
    }
}


