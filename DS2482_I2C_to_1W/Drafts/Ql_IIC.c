/**
  ******************************************************************************
  * @file		Ql_IIC.c
  ******************************************************************************
  */
 
/********************/
/********///includes: 
  
	#include "Q1_IIC.h"
/********************/
/********///definitions:


/********************/
/********///Functions:  

/*****************************************************************
* Function:     Ql_IIC_Write 
* 
* Description:
*               This function  write data  to specified slave through IIC interface.
*               
* Parameters:
*               chnnlNo:
*                   [In] IIC channel No, the No is specified by Ql_IIC_Init function.
*               slaveAddr:
*                   [In] slave address.
*               pData:
*                   [In] Setting value to slave
*               len:
*                   [In] Number of bytes to write. 
*                   if IICtype=1 ,1<len<8 . because our IIC contronller at most support 8 bytes for one time transaction
* Return:        
*               if no error return, the length of the write data.
*               QL_RET_ERR_PARAM, patameter error.
*               QL_RET_ERR_CHANNEL_NOT_FOUND, can't found the IIC channel, make sure it is initialized already.
*               QL_RET_ERR_I2CHWFAILED, Maybe the hardware have something wrong.
*               QL_RET_ERR_IIC_SLAVE_NOT_FOUND, not found the specified slave.
*****************************************************************/
s32 Ql_IIC_Write(u32 chnnlNo, u8 slaveAddr, u8 *pData, u32 len);
{
	I2C_AcknowledgeNextData(I2C_Periph1, I2C_ACK);
	I2C_GenerateStartCondition(I2C_Periph1);
	Delay_msec(1);
	
	if(!send_i2c1_slave_address(slaveAddr, write))
	{
		return QL_RET_ERR_I2CHWFAILED
	}
	
	Data_add = pData;
	for(int index = 1; index <= len; index++)
	{
		if(index == len)
		{
			I2C_AcknowledgeNextData(I2C_Periph1, I2C_NACK);
		}
		write_i2c(*pData++);
	}
	
	I2C_GenerateStopCondition(I2C_Periph1);
	return len;
}

/*****************************************************************
* Function:     Ql_IIC_Read 
* 
* Description:
*               This function read data from specified slave through IIC interface.
*               
* Parameters:
*               chnnlNo:
*                   [In] IIC channel No, the No is specified by Ql_IIC_Init function.
*               slaveAddr:
*                   [In] slave address.
*               pBuffer:
*                   [Out] read buffer of reading the specified register from slave.
*               len:
*                   [In] Number of bytes to read.
*                   if IICtype=1 ,1<len<8 . because our IIC contronller at most support 8 bytes for one time transaction
* Return:        
*               if no error, return the length of the read data.
*               QL_RET_ERR_PARAM, patameter error.
*               QL_RET_ERR_CHANNEL_NOT_FOUND, can't found the IIC channel, make sure it is initialized already.
*               QL_RET_ERR_I2CHWFAILED, Maybe the hardware have something wrong.
*               QL_RET_ERR_IIC_SLAVE_NOT_FOUND, not found the specified slave.
*****************************************************************/
s32 Ql_IIC_Read(u32 chnnlNo, u8 slaveAddr, u8 *pBuffer, u32 len)
{
	I2C_AcknowledgeNextData(I2C_Periph1, I2C_ACK);
	I2C_GenerateStartCondition(I2C_Periph1);
	Delay_msec(1);
	
	if(!send_i2c1_slave_address(slaveAddr, read))
	{
		return QL_RET_ERR_I2CHWFAILED
	}
	
	Data_add = pBuffer;
	for(int index = 1; index <= len; index++)
	{
		*pBuffer++ = read_i2c((index == len) ? false : true);
	}
	
	I2C_GenerateStopCondition(I2C_Periph1);
	return len;
}