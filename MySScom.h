#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "mysscomtool.h"
#include "afxdialogex.h"

#include <tchar.h>
#include <windows.h>

/*************************************************************************************************/
/*                                     ȫ�ֺ궨��                                               */
/*************************************************************************************************/
#define MAX_WIN_POS                    3200                                    /* ������ʾ�����߽����� */
#define SHAKE_DISTANCE                 10                                      /* ���������ƫ��λ�� */
#define REC_DIR_PATH                   "Record\\"                              /* ��ż�¼�ļ���ͳһĿ¼ */

/*************************************************************************************************/
/*                                     �汾���ƿ���                                              */
/*************************************************************************************************/
#define  VERSION_COMON                 0x01                                    /* �����汾 */
#define  VERSION_YAXON                 0x02                                    /* ��Ѹ�汾 */

#define  VERSION_CTRL                  VERSION_YAXON

/*************************************************************************************************/
/*                                     �����汾���                                              */
/*************************************************************************************************/
#define RELEASE_VERSION                0                                       /* �Ƿ�Ϊ��ʽ�����汾 */

#define CONFIGFILENAME                 ".\\Settings.ini"
#define CONFIGBACKNAME                 ".\\Settings_old.ini"

#define FLAG_SYSRUNREC                 "Config_BasicInfo"
#define FLAG_MAINFRAME                 "Config_MainFrame"
#define FLAG_AUTOREPLY                 "Config_AutoReply"
#define FLAG_DISPLYFLT                 "Config_DisplyFlt"
#define FLAG_EXTRAFUNT                 "Config_ExtraFunt"
#define FLAG_KEYWDMTCH                 "Config_KeywdMtch"
#define FLAG_SUPERSEND                 "Config_SuperSend"

/*************************************************************************************************/
/*                                     ���ֶβ������ƶ���                                        */
/*************************************************************************************************/
#define SYSRUNREC_RUNTIMES             "RunTimes"
#define SYSRUNREC_PROGMVER             "ProgmVer"

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
typedef enum {
	WM_USERMSG_NOTIFYICON = WM_USER + 100,                                     // ��������ͼ����Ϣ
	WM_USERMSG_COMDEVLIST,                                                     // �����豸��������
	WM_USERMSG_COMDEVWAIT,                                                     // �����豸�Ժ����
	WM_USERMSG_DATARECVED,                                                     // �����յ���������
	WM_USERMSG_DATATOSEND,                                                     // �д�������Ҫ����
	WM_USERMSG_ARDLGCLOSE,                                                     // �Զ��ظ����ڹر�
	WM_USERMSG_DFDLGCLOSE,                                                     // ��ʾ���˴��ڹر�
	WM_USERMSG_EFDLGCLOSE,                                                     // ���ӹ��ܴ��ڹر�
	WM_USERMSG_SSDLGCLOSE,                                                     // �߼����ʹ��ڹر�
	WM_USERMSG_KWDLGCLOSE,                                                     // �ؼ��ַ������ر�
	WM_USERMSG_NOTDEFINED
} WM_USERMSG_INDEX;

#define STATIC_TEXT                    "��ݼ���ʾ��\r\nF1���鿴������ʾ;\r\nF2����RecordĿ¼;\r\nF5����ս���������;\r\nF8����ʼ�����ļ�;\r\nF12��������յ�����;\r\n��������δ����;"

class CMySScomApp : public CWinApp
{
public:
	CMySScomApp();

	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

