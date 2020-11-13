#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "mysscomtool.h"
#include "afxdialogex.h"

/*************************************************************************************************/
/*                                     RGB��ɫֵ����                                             */
/*************************************************************************************************/
#define RGB_BLACK                      (RGB(000, 000, 000))
#define RGB_RED                        (RGB(255, 000, 000))
#define RGB_GREEN                      (RGB(000, 255, 000))
#define RGB_BLUE                       (RGB(000, 000, 255))
#define RGB_WHITE                      (RGB(255, 255, 255))
#define RGB_BROWN                      (RGB(128, 128, 128))
#define RGB_GRAY                       (RGB(192, 192, 192))
#define RGB_CYAN                       (RGB(000, 255, 255))
#define RGB_PINK                       (RGB(255, 000, 255))
#define RGB_YELLOW                     (RGB(255, 255, 000))

#define RGB_LIGHT_GREEN                (RGB(189, 252, 201))
#define RGB_LIGHT_BLUE                 (RGB(176, 224, 230))
#define RGB_LIGHT_YELLOW               (RGB(245, 222, 179))
#define RGB_LIGHT_PINK                 (RGB(255, 192, 203))
#define RGB_LIGHT_PURPLE               (RGB(221, 160, 221))

/*************************************************************************************************/
/*                                     �û��Զ�����Ϣֵ                                          */
/*************************************************************************************************/
#define WM_USERMSG_NOTIFYICON          WM_USER + 100                           // ��������ͼ����Ϣ
#define WM_USERMSG_COMDEVLIST          WM_USER + 101                           // �������豸����
#define WM_USERMSG_DATARECVED          WM_USER + 102                           // �����յ���������
#define WM_USERMSG_DATATOSEND          WM_USER + 110                           // �д�������Ҫ����
#define WM_USERMSG_ARDLGCLOSE          WM_USER + 111                           // �Զ��ظ����ڹر�
#define WM_USERMSG_DFDLGCLOSE          WM_USER + 112                           // ��ʾ���˴��ڹر�
#define WM_USERMSG_EFDLGCLOSE          WM_USER + 113                           // ���ӹ��ܴ��ڹر�
#define WM_USERMSG_SSDLGCLOSE          WM_USER + 114                           // �߼����ʹ��ڹر�

class CMySScomApp : public CWinApp
{
public:
	CMySScomApp();

	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

