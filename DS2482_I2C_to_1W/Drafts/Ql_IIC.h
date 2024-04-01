 /**
  ******************************************************************************
  * @file		Ql_IIC.h
  ******************************************************************************
  */
 
/********************/
/********///includes: 
  
	#include "i2c.h"
	#include "stm32f1xx_ll_utils.h"
/********************/
/********///definitions:

#define Delay_msec(x)	LL_mDelay(x);

/* Q1 functions return value */

typedef uint32_t s32;

#define		QL_RET_ERR_PARAM 					-1 // patameter error.
#define		QL_RET_ERR_CHANNEL_NOT_FOUND		-2 // can't found the IIC channel, make sure it is initialized already.
#define		QL_RET_ERR_I2CHWFAILED				-3 // Maybe the hardware have something wrong.
#define		QL_RET_ERR_IIC_SLAVE_NOT_FOUND		-4 // not found the specified slave.

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
s32 Ql_IIC_Read(u32 chnnlNo, u8 slaveAddr, u8 *pBuffer, u32 len);


/********************************* END OF FILE ********************************/
/******************************************************************************/ 