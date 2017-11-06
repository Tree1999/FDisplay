#include "../project_cfg.h"
#ifdef  DESERIALIZE_MODULE
/******************************************************************************								
*  Name: deserialize_data.c
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
#include "deserialize_data.h"
#include "../../Headers/GPIO.h"

/*******************************************************************************
* Constants
********************************************************************************/


/*******************************************************************************
* Macros
********************************************************************************/
/*******************************************************************************
* Types
********************************************************************************/
typedef struct
{
    //UINT8 device_address;
    UINT8 register_address;
    UINT8 register_value;
}DESERIALIZE_SET0;

typedef struct
{
    //UINT8 device_address;
    UINT8 register_address;
    UINT8 register_value;
}DESERIALIZE_SET1;

typedef struct
{
    //UINT8 device_address;
    UINT8 register_address;
    UINT8 register_value;
}DESERIALIZE_SET2;

/*******************************************************************************
* Variables
********************************************************************************/

/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* static Functions
********************************************************************************/
static void Deserialize_Data_Register_Set(void);
static void Deserialize_Data_GPIO_Init(void);

/***********************************************************************************************
*
* @brief    deserialize_data_init - driver init and Initalize deserialize register
* @param    none
* @return   none
*
************************************************************************************************/  
void Deserialize_Data_Init(void)
{
    /*GPIO init*/
    Deserialize_Data_GPIO_Init();
	/*I2C driver init */
	Deserialize_I2C_Init();
    /* initialize deserialize register */
	Deserialize_Data_Register_Set();

#if 0
    /*Des configure*/
    CONFIG_PIN_AS_GPIO(PTD,PTD1,OUTPUT); /* Configure DES_DRS(PTD1) as an output */	
    OUTPUT_CLEAR(PTD,PTD1);
    CONFIG_PIN_AS_GPIO(PTD,PTD2,INPUT);  /* Configure DES_LOCK(PTD2) as an input */
    ENABLE_INPUT(PTD,PTD2);
    CONFIG_PIN_AS_GPIO(PTD,PTD3,INPUT);  /* Configure DES_ERR(PTD3) as an input */	
    ENABLE_INPUT(PTD,PTD3);
    CONFIG_PIN_AS_GPIO(PTD,PTD4,OUTPUT); /* Configure DES_PWDN(PTD4) as an output */
    OUTPUT_SET(PTD,PTD4);
    CONFIG_PIN_AS_GPIO(PTD,PTD5,OUTPUT); /* Configure DES_CDS(PTD5) as an output */	
    OUTPUT_CLEAR(PTD,PTD5);
    CONFIG_PIN_AS_GPIO(PTD,PTD6,INPUT);  /* Configure DES_INTOUT(PTD6) as an input */
    ENABLE_INPUT(PTD,PTD6);
    CONFIG_PIN_AS_GPIO(PTD,PTD7,OUTPUT); /* Configure DES_GPI(PTD7) as an output */
    OUTPUT_SET(PTD,PTD7);
		CONFIG_PIN_AS_GPIO(PTA,PTA1,OUTPUT); /* Configure DES_HIM(PTA1) as an output */
    OUTPUT_CLEAR(PTA,PTA1);
		CONFIG_PIN_AS_GPIO(PTF,PTF0,OUTPUT); /* Configure DES_SSEN(PTF0) as an output */
    OUTPUT_CLEAR(PTF,PTF0);
		CONFIG_PIN_AS_GPIO(PTF,PTF2,OUTPUT); /* Configure DES_EQS(PTF2) as an output */
    OUTPUT_SET(PTF,PTF2);		
#endif
}

/***********************************************************************************************
*
* @brief    deserialize_data_register_set - set the register of deserialize
* @param    none
* @return   none
*
************************************************************************************************/  
static void Deserialize_Data_Register_Set(void)
{
	#define	DES_REG_SIZE0	0x02
	#define	DES_REG_SIZE1	0x02
	#define	DES_REG_SIZE2	0x02
    /*DESERIALIZE_SET des_set[DES_REG_SIZE]={{0x58,0x02,0x80},
    							 			{0x58,0x1E,0x50},
								 			{0x58,0x1F,0x05}};*/
	DESERIALIZE_SET0 des_set0[DES_REG_SIZE0]={0x02,0x80};
	DESERIALIZE_SET1 des_set1[DES_REG_SIZE1]={0x1E,0x50};
	DESERIALIZE_SET2 des_set2[DES_REG_SIZE2]={0x1F,0x05};
	UINT8			number0;
	UINT8			number1;
	UINT8			number2;

	for(number0=0; number0<DES_REG_SIZE0; number0++)
	{
	    /* send data to deserialize */
//    Deserialize_UART_Send_Data((UINT8*)&des_set, sizeof(DESERIALIZE_SET));
		Deserialize_I2C_Master_Send((UINT8*)&des_set0, sizeof(DESERIALIZE_SET0));
		
	}
	
	for(number1=0; number1<DES_REG_SIZE1; number1++)
	{
	    /* send data to deserialize */
//    Deserialize_UART_Send_Data((UINT8*)&des_set, sizeof(DESERIALIZE_SET));
		Deserialize_I2C_Master_Send((UINT8*)&des_set1, sizeof(DESERIALIZE_SET1));
		
	}

	for(number2=0; number2<DES_REG_SIZE2; number2++)
	{
	    /* send data to deserialize */
//    Deserialize_UART_Send_Data((UINT8*)&des_set, sizeof(DESERIALIZE_SET));
		Deserialize_I2C_Master_Send((UINT8*)&des_set2, sizeof(DESERIALIZE_SET2));
		
	}
	
}

/***********************************************************************************************
*
* @brief    Deserialize_Data_GPIO_INIT - set the GPIO of deserialize
* @param    none
* @return   none
*
************************************************************************************************/  
static void Deserialize_Data_GPIO_Init(void)
{
    //CONFIG_PIN_AS_GPIO(PTD, PTD5, OUTPUT);  /* Configure deserialize as master */
    //OUTPUT_SET(PTD,PTD5);
    CONFIG_PIN_AS_GPIO(PTD,PTD2,INPUT);  /* Configure DES_LOCK(PTD2) as an input */
    	ENABLE_INPUT(PTD,PTD2);
    CONFIG_PIN_AS_GPIO(PTD,PTD4,OUTPUT); /* Configure DES_PWDN(PTD4) as an output */
    	OUTPUT_CLEAR(PTD,PTD4);
    CONFIG_PIN_AS_GPIO(PTD,PTD5,OUTPUT); /* Configure DES_CDS(PTD5) as an output */	
    	OUTPUT_CLEAR(PTD,PTD5);
    CONFIG_PIN_AS_GPIO(PTD,PTD6,INPUT);  /* Configure DES_INTOUT(PTD6) as an input */
    	ENABLE_INPUT(PTD,PTD6);
    CONFIG_PIN_AS_GPIO(PTD,PTD7,OUTPUT); /* Configure DES_GPI(PTD7) as an output */
    	OUTPUT_SET(PTD,PTD7);		
	CONFIG_PIN_AS_GPIO(PTA,PTA1,OUTPUT); /* Configure DES_HIM(PTA1) as an output */
    	OUTPUT_CLEAR(PTA,PTA1);
	CONFIG_PIN_AS_GPIO(PTF,PTF0,OUTPUT); /* Configure DES_SSEN(PTF0) as an output */
    	OUTPUT_CLEAR(PTF,PTF0);
	CONFIG_PIN_AS_GPIO(PTF,PTF2,OUTPUT); /* Configure DES_EQS(PTF2) as an output */
    	OUTPUT_SET(PTF,PTF2);		
			
	  CONFIG_PIN_AS_GPIO(PTH,PTH6,OUTPUT); 
    OUTPUT_SET(PTH,PTH6);
		//OUTPUT_CLEAR(PTH,PTH6);
		CONFIG_PIN_AS_GPIO(PTH,PTH1,OUTPUT); 
    OUTPUT_SET(PTH,PTH1); 
		
		CONFIG_PIN_AS_GPIO(PTH,PTH0,OUTPUT); 
    OUTPUT_SET(PTH,PTH0);
		
		CONFIG_PIN_AS_GPIO(PTH,PTH7,INPUT);  /* Configure DES_INTOUT(PTD6) as an input */
    ENABLE_INPUT(PTH,PTH7);
		
	CONFIG_PIN_AS_GPIO(PTE,PTE6,OUTPUT); /* Configure LED_EN as an output */
    OUTPUT_SET(PTE,PTE6); 

}
#endif /* DESERIALIZE_MODULE */

