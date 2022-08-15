/**********************************************************************************************************
** Company     : JNE WuHan Co.,Ltd.
** Project     :
** --------------------------------------------------------------------------------------------------------
** File name   : bsp_MB85RS2.h
** Author      : Huang Cheng
** Date        : 2021-11-09
** Description : bsp_MB85RS2 head file
**********************************************************************************************************/

#ifndef _BSP_MB85RS2_H_
#define _BSP_MB85RS2_H_

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************************************************
**                                          ͷ�ļ�������
**********************************************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include "hc32_ddl.h"

/**********************************************************************************************************
**                                            �궨����
**********************************************************************************************************/
//#define MB85RS2_TEST    

#define MB85RS2_CMD_WREN 		   0x06      //дʹ��
#define MB85RS2_CMD_WRDI		   0x04      //д��ֹ
#define MB85RS2_CMD_RDSR		   0x05      //��״̬�Ĵ���
#define MB85RS2_CMD_WRSR		   0x01      //д״̬�Ĵ���
#define MB85RS2_CMD_READ		   0x03      //24λ��ַģʽ������ 
#define MB85RS2_CMD_WRITE		   0x02      //д����
#define MB85RS2_CMD_FSTRD          0x0B      //32λ��ַģʽ����λ���룬��λ��0��������
#define MB85RS2_CMD_RDID		   0x9f      //��ID��32λID
#define MB85RS2_CMD_SLEEP		   0xB9      //�͹���ģʽ

#define StartADD_WorkStatus	       0          // ��һ�ζϵ繤��״̬��¼��������ʼ��ַ��8�ֽڣ�
#define StartADD_MB85RS2DeviceSN   8          // �豸SN�����ţ�3�ֽڣ�
#define MB85RS2_Size               0x40000    //256K Byte


/*FRAM�����ַ����*/
#define APP_Copy_Flag_ADD       MB85RS2_Size-1   //�������һ����ַ��ΪAPP������־��ַ
/**********************************************************************************************************
**                                           ���Ͷ�����
**********************************************************************************************************/


/**********************************************************************************************************
**                                         �ⲿ���ñ�����
**********************************************************************************************************/	

	
/**********************************************************************************************************
**                                         �ⲿ���ú�����
**********************************************************************************************************/	
void MB85Ctrl_Read(uint32_t addr, uint8_t *buf, uint16_t len);
void MB85Ctrl_Write(uint32_t addr, uint8_t *buf, uint16_t len);
void MB85Ctrl_ReadID(uint32_t *buf);
uint8_t MB85Ctrl_CheckWrite(uint32_t addr, uint8_t *buf, uint16_t len);

#ifdef __cplusplus
}
#endif	
	
#endif

/**********************************************************************************************************
**                                          End Of File
**********************************************************************************************************/