#pragma once

#include <string>
#include "afxwin.h"
#include "afxstr.h"
#include "winbase.h"
#include "mysscom.h"

/*************************************************************************************************/
/*                                     串口设备参数定义                                          */
/*************************************************************************************************/
typedef struct {
	unsigned long    baudrate;                                                 /* 波特率 */
	unsigned char    databits;                                                 /* 数据位 */
	unsigned char    stopbits;                                                 /* 停止位 */
	unsigned char    checkbit;                                                 /* 校验位 */
} SRL_DEV_PARA_T;

/*************************************************************************************************/
/*                                     串口设备参数定义                                          */
/*************************************************************************************************/
#define  MAX_RECV_BYTE                 1024                                    /* 最大接收字节数 */
#define  MAX_SEND_BYTE                 2048                                    /* 最大发送字节数 */

/*************************************************************************************************/
/*                                     串口设备参数定义                                          */
/*************************************************************************************************/
#define  XON                           0x11
#define  XOFF                          0x13


bool OpenSerialDevice(LPCSTR dname, SRL_DEV_PARA_T *spara);
bool CloseSerialDevice(void);
bool SerialDevisOpened(void);
int  SendSerialData(unsigned char *sbuf, int slen);

bool CreateDeviceThread(void);

