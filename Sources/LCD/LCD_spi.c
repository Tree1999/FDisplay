#include "../project_cfg.h"
#ifdef LCD_MODULE

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
#include "../../Headers/GPIO.h"
#include "LCD_spi.h"

/**********************************************************************************************
* External objects
**********************************************************************************************/


/**********************************************************************************************
* Global variables
**********************************************************************************************/

/**********************************************************************************************
* Constants and macros
**********************************************************************************************/
#define LCD_CS_LOW      OUTPUT_CLEAR(PTD,PTD3)
#define LCD_CS_HIGH     OUTPUT_SET(PTD,PTD3)
#define LCD_SCL_LOW     OUTPUT_CLEAR(PTD,PTD0)
#define LCD_SCL_HIGH    OUTPUT_SET(PTD,PTD0)
#define LCD_SDI_LOW     OUTPUT_CLEAR(PTD,PTD1)
#define LCD_SDI_HIGH    OUTPUT_SET(PTD,PTD1)
#define LCD_SDO_LOW     OUTPUT_CLEAR(PTB,PTB4)
#define LCD_SDO_HIGH    OUTPUT_SET(PTB,PTB4)

#define LCD_READ_MODE   1
#define LCD_WRITE_MODE  0

/* time */
#define TIME_ZERO_UNIT      0x00000000  
#define TIME_ONE_UNIT       0x00000001  /*the core clock is 40MHz, 0x01 need 208.33ns to count */
#define TIME_TWO_UNIT       0x00000002
#define TIME_THREE_UNIT     0x00000003
#define TIME_FOUR_UNIT      0x00000004
#define TIME_FIVE_UNIT      0x00000005
#define TIME_SIX_UNIT       0x00000006
#define TIME_SEVEN_UNIT     0x00000007
#define TIME_EIGHT_UNIT     0x00000008
#define TIME_NINE_UNIT      0x00000009
#define TIME_TEN_UNIT       0x0000000A
#define TIME_ELEVEN_UNIT    0x0000000B
#define TIME_FOURTEEN_UNIT  0x0000000E

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
static void LCD_Spi_GPIO_Init(void);
static void LCD_Spi_Enable_Input(GPIO_Type *port, UINT32 port_pin);
//static void LCD_Spi_Unable_Input(GPIO_Type *port, UINT32 port_pin);
static UINT8 LCD_Spi_Read_Input(GPIO_Type *port, UINT32 port_pin);
static void LCD_I2C_Delay(UINT32  timer);

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
void LCD_Spi_Init(void)
{
    LCD_Spi_GPIO_Init();
}
/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/

void LCD_Spi_Write_Page(LCD_IC_SID IC_SID, UINT8 page_data)
{
    UINT16 send_data=0;
    UINT8 send_bit_number=16;
    
    /* set write mode */
    send_data += (LCD_WRITE_MODE&0x01)<<15;
    /* set sid */
    //send_data += (IC_SID&0x03)<<13;
		send_data += (IC_SID&0x7F)<<14;
    send_data += (LCD_IC_PAGE_REG&0x1F)<<8;

    send_data += page_data;
    
    /* send data */
    OUTPUT_CLEAR(PTB,PTB1); // standby low level
    LCD_CS_LOW;
    while(send_bit_number--)
    {
        LCD_I2C_Delay(TIME_ONE_UNIT);
        LCD_SCL_LOW;
        if(send_data&0x8000)
            LCD_SDI_HIGH;
        else
            LCD_SDI_LOW;
        LCD_SCL_HIGH;
        send_data <<= 1;
    }
    LCD_I2C_Delay(TIME_ONE_UNIT);

    OUTPUT_SET(PTB,PTB1); // standby high level
    LCD_SDI_HIGH;
    LCD_CS_HIGH;
}

/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/

void LCD_Spi_Write_Register( UINT8 reg, UINT8 register_data)
{
    UINT16 send_data=0;
    UINT8 send_bit_number=16;
    
    /* set sid */
    send_data += (reg&0x7F)<<8;

    send_data += register_data;
    
    /* send data */
   // OUTPUT_CLEAR(PTB,PTB1); // standby low level
    LCD_CS_LOW;
    while(send_bit_number--)
    {
        LCD_I2C_Delay(TIME_ONE_UNIT);
        LCD_SCL_LOW;
        if(send_data&0x8000)
            LCD_SDI_HIGH;
        else
            LCD_SDI_LOW;
        LCD_SCL_HIGH;
        send_data <<= 1;
    }
    LCD_I2C_Delay(TIME_ONE_UNIT);

   // OUTPUT_SET(PTB,PTB1); // standby high level
    LCD_SDI_HIGH;
    LCD_CS_HIGH;
}

/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
#if 0
void LCD_Spi_Read_Register( LCD_IC_SID IC_SID, UINT8 reg, UINT8 *register_data)
{
    UINT8 bit_number=0;
    UINT8 reg_data=0;

    *register_data = 0;
    /* set write mode */
    reg_data += (LCD_READ_MODE&0x01)<<7;
    /* set sid */
    reg_data += (IC_SID&0x03)<<5;
    reg_data += reg&0x1F;

    
    /* send data */
    bit_number = 8;
    OUTPUT_CLEAR(PTB,PTB1); // standby low level
    LCD_CS_LOW;
    while(bit_number--)
    {
        LCD_I2C_Delay(TIME_ONE_UNIT);
        LCD_SCL_LOW;
        if(reg_data&0x80)
            LCD_SDI_HIGH;
        else
            LCD_SDI_LOW;
        LCD_SCL_HIGH;
        reg_data <<= 1;
    }
     LCD_I2C_Delay(TIME_ZERO_UNIT);

    /* receive data */
    bit_number = 8;
    while(bit_number--)
    {
        LCD_SCL_LOW;
        *register_data <<= 1;
        LCD_I2C_Delay(TIME_TWO_UNIT);
        LCD_SCL_HIGH;
        *register_data += LCD_Spi_Read_Input(PTB,PTB4);
    }

    OUTPUT_SET(PTB,PTB1); // standby high level
    LCD_SDI_HIGH;
    LCD_CS_HIGH;
}
#endif
void LCD_Spi_Read_Register( LCD_IC_SID IC_SID, UINT8 reg, UINT8 *register_data)
{
    UINT8 bit_number=0;
    UINT8 reg_data=0;

    *register_data = 0;
    /* set write mode */
    reg_data += (LCD_READ_MODE&0x01)<<7;
    /* set sid */
    reg_data += (IC_SID&0x03)<<5;
    reg_data += reg&0x1F;

	 reg_data += reg&0x1F;

    
    /* send data */
    bit_number = 8;
    OUTPUT_CLEAR(PTB,PTB1); // standby low level
    LCD_CS_LOW;
    while(bit_number--)
    {
        LCD_I2C_Delay(TIME_ONE_UNIT);
        LCD_SCL_LOW;
        if(reg_data&0x80)
            LCD_SDI_HIGH;
        else
            LCD_SDI_LOW;
        LCD_SCL_HIGH;
        reg_data <<= 1;
    }
     LCD_I2C_Delay(TIME_ZERO_UNIT);

    /* receive data */
    bit_number = 8;
    while(bit_number--)
    {
        LCD_SCL_LOW;
        *register_data <<= 1;
        LCD_I2C_Delay(TIME_TWO_UNIT);
        LCD_SCL_HIGH;
        *register_data += LCD_Spi_Read_Input(PTB,PTB4);
    }

    OUTPUT_SET(PTB,PTB1); // standby high level
    LCD_SDI_HIGH;
    LCD_CS_HIGH;
}

/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
static void LCD_Spi_GPIO_Init(void)
{

    /* SPI */
	CONFIG_PIN_AS_GPIO(PTD,PTD3,OUTPUT);  /* LCD_CSB(PTD3) */
    OUTPUT_SET(PTD,PTD3);
	CONFIG_PIN_AS_GPIO(PTD,PTD0,OUTPUT);  /* LCD_SCL(PTD0) */
    OUTPUT_SET(PTD,PTD0);
    CONFIG_PIN_AS_GPIO(PTD,PTD1,OUTPUT);  /* LCD_SDI(PTD1) */
	OUTPUT_SET(PTD,PTD1);
	
    //SIM_SOPT0 &=~(SIM_SOPT0_NMIE_MASK);   /* set PTB4 as GPIO */
    CONFIG_PIN_AS_GPIO(PTB,PTB4,INPUT);  /* Configure LCD_SDO(PTB4) as an input */ /*Hi-Z in schematic*/
    LCD_Spi_Enable_Input(PTB,PTB4);
	
	
	//Control signal
    CONFIG_PIN_AS_GPIO(PTB,PTB0,OUTPUT);  /* LCD_RESET(PTB0):*/
    OUTPUT_SET(PTB,PTB0);
	
    CONFIG_PIN_AS_GPIO(PTB,PTB1,OUTPUT);  /* LCD_STBYB(PTB1):  request LCD into standby */
    OUTPUT_CLEAR(PTB,PTB1);
	
    CONFIG_PIN_AS_GPIO(PTC,PTC2,OUTPUT); /* Configure LCD_UPDN(PTC2) as an output */
	OUTPUT_SET(PTC,PTC2);
    CONFIG_PIN_AS_GPIO(PTC,PTC3,OUTPUT); /* Configure LCD_SHLR(PTC3) as an output */
    OUTPUT_SET(PTC,PTC3);
	CONFIG_PIN_AS_GPIO(PTC,PTC0,INPUT);   /* LCD_FAIL_T(PTC0): fail feedback */
    LCD_Spi_Enable_Input(PTC,PTC0);
	
}

/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
void LCD_Spi_GPIO_Init_Standby(void)
{
//    CONFIG_PIN_AS_GPIO(PTB,PTB1,OUTPUT);  /* LCD_STBYB(PTB1):  request LCD into standby */
    OUTPUT_SET(PTB,PTB1);
}

/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
static void LCD_Spi_Enable_Input(GPIO_Type *port, UINT32 port_pin)
{
    port->PIDR &= ~(0x00000001 << port_pin);
}
/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
#if 0
static void LCD_Spi_Unable_Input(GPIO_Type *port, UINT32 port_pin)
{
    port->PIDR |= 0x00000001 << port_pin;
}
#endif

/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
static UINT8 LCD_Spi_Read_Input(GPIO_Type *port, UINT32 port_pin)
{
    return ((port->PDIR)>>port_pin)&0x00000001;
}
/***********************************************************************************************
*
* @brief    CTP_If_Init() - Program entry function
* @param    none
* @return   none
*
************************************************************************************************/
static void LCD_I2C_Delay(UINT32  timer)
{
    while(timer--);
}

#endif /* LCD_MODULE */
