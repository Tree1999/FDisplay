#ifdef EEPROM_MODULE
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
#include "EEPROM_I2C.h"
#include "../../Headers/I2C.h"

/**********************************************************************************************
* External objects
**********************************************************************************************/


/**********************************************************************************************
* Global variables
**********************************************************************************************/

/**********************************************************************************************
* Constants and macros
**********************************************************************************************/
#define EEPROM_MASTER_WRITE_TO_SLAVE   0xA0    /* the slave is AT24C16 */
#define EEPROM_MASTER_READ_FROM_SLAVE  0xA1    /* the slave is AT24C16 */

#define EEPROM_IC   I2C1
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
* @brief    EEPROM_If_Init() - 
* @param    none
* @return   none
*
************************************************************************************************/
void EEPROM_I2C_Init(void)
{
    /*It has Initialize the I2C in CTP module ,so do nothing now */
}

/***********************************************************************************************
*
* @brief    EEPROM_If_Init() - 
* @param    none
* @return   none
*
************************************************************************************************/
UINT8 EEPROM_I2C_Master_Write(UINT16 word_addr, UINT8 *send_data, UINT32 data_size)
{
    UINT8 write_pos;
    UINT8 u8ErrorStatus;
    UINT8 byte_temp;
    
    if((NULL==send_data) || (0 == data_size))
        return 0xFF;

    I2C_IntDisable(EEPROM_IC);
	 
	/* send start signals to bus */
    u8ErrorStatus = I2C_Start(EEPROM_IC);

	/* send device address and word address to slave first */
    byte_temp = word_addr>>0x07&0x0E; /* MSB of address, device address byte */
    u8ErrorStatus = I2C_WriteOneByte(EEPROM_IC,byte_temp|EEPROM_MASTER_WRITE_TO_SLAVE);
    if(u8ErrorStatus == I2C_ERROR_NULL)
    {
        byte_temp = word_addr&0xFF; /* LSB of address, word address byte */
        u8ErrorStatus = I2C_WriteOneByte(EEPROM_IC,byte_temp);
        
        /* if no error occur, received the correct ack from slave
                continue to send data to slave*/
        if( u8ErrorStatus == I2C_ERROR_NULL )
        {
            for(write_pos=0;write_pos<data_size;write_pos++)
            {
                u8ErrorStatus = I2C_WriteOneByte(EEPROM_IC,send_data[write_pos]);
                if( u8ErrorStatus != I2C_ERROR_NULL )
                {
                    return u8ErrorStatus;
                }
            }
         }
    }
    
    /* send stop signals to bus */
    u8ErrorStatus = I2C_Stop(EEPROM_IC);
    I2C_IntEnable(EEPROM_IC);

    return u8ErrorStatus;
}

/***********************************************************************************************
*
* @brief    EEPROM_If_Init() - 
* @param    none
* @return   none
*
************************************************************************************************/
UINT8 EEPROM_I2C_Master_Read(UINT16 word_addr, UINT8 *read_data, UINT32 data_size)
{
    UINT32 read_pos;
    UINT8 u8ErrorStatus;
    UINT8 byte_temp;
    UINT8 clear_buf;

    if((NULL==read_data) || (0 == data_size))
        return 0xFF;

    I2C_IntDisable(EEPROM_IC);

    /* send start signals to bus */
    u8ErrorStatus = I2C_Start(EEPROM_IC);

    /* send device address and word address to slave first */
    byte_temp = word_addr>>0x07&0x0E; /* MSB of address, device address byte */
    u8ErrorStatus = I2C_WriteOneByte(EEPROM_IC,byte_temp|EEPROM_MASTER_WRITE_TO_SLAVE);

    if(u8ErrorStatus == I2C_ERROR_NULL)
    {
        byte_temp = word_addr&0xFF; /* LSB of address, word address byte */
        u8ErrorStatus = I2C_WriteOneByte(EEPROM_IC,byte_temp);

        /* if no error occur, received the correct ack from slave continue to send data to slave*/
        /* dummy write two bytes to switch to Rx mode */   
        u8ErrorStatus = I2C_RepeatStart(EEPROM_IC);

        if( u8ErrorStatus == I2C_ERROR_NULL )
        {
            /* read data, send device address and read sign first  */
            u8ErrorStatus = I2C_WriteOneByte(EEPROM_IC,EEPROM_MASTER_READ_FROM_SLAVE);
            /* clear register data : EEPROM_MASTER_READ_FROM_SLAVE*/
            I2C_ReadOneByte(EEPROM_IC,&clear_buf,I2C_SEND_ACK);

            if( u8ErrorStatus == I2C_ERROR_NULL )
            {
                for(read_pos=0;read_pos<data_size-1;read_pos++)
                {
                    u8ErrorStatus = I2C_ReadOneByte(EEPROM_IC,&read_data[read_pos],I2C_SEND_ACK);
                    if( u8ErrorStatus != I2C_ERROR_NULL )
                    {
                        return u8ErrorStatus;
                    }
                }
                u8ErrorStatus = I2C_ReadOneByte(EEPROM_IC,&read_data[read_pos],I2C_SEND_NACK);
            }
        }
    }
    /* send stop signals to bus */
    u8ErrorStatus = I2C_Stop(EEPROM_IC);

    I2C_IntEnable(EEPROM_IC);
    
    return u8ErrorStatus;
}
#endif /* EEPROM_MODULE */
