#pragma once

#include <string>
#include "afxwin.h"
#include "afxstr.h"
#include "winbase.h"
#include "mysscom.h"

/*************************************************************************************************/
/*                                     �����豸��������                                          */
/*************************************************************************************************/
typedef struct {
	unsigned long    baudrate;                                                 /* ������ */
	unsigned char    databits;                                                 /* ����λ */
	unsigned char    stopbits;                                                 /* ֹͣλ */
	unsigned char    checkbit;                                                 /* У��λ */
} SRL_DEV_PARA_T;

/*************************************************************************************************/
/*                                     �����豸��������                                          */
/*************************************************************************************************/
#define  MAX_RECV_BYTE                 1024                                    /* �������ֽ��� */
#define  MAX_SEND_BYTE                 2048                                    /* ������ֽ��� */

/*************************************************************************************************/
/*                                     �����豸��������                                          */
/*************************************************************************************************/
#define  XON                           0x11
#define  XOFF                          0x13


bool OpenSerialDevice(LPCSTR dname, SRL_DEV_PARA_T *spara);
bool CloseSerialDevice(void);
bool SerialDevisOpened(void);
int  SendSerialData(unsigned char *sbuf, int slen);

bool CreateDeviceThread(void);

