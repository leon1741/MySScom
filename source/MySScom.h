#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "../resource.h"
#include "mysscomtool.h"
#include "afxdialogex.h"

#include <tchar.h>
#include <windows.h>

/*************************************************************************************************/
/*                                     全局宏定义                                               */
/*************************************************************************************************/
#define MAX_WIN_POS                    3200                                    /* 窗体显示的最大边界坐标 */
#define SHAKE_DISTANCE                 10                                      /* 抖动窗体的偏移位置 */
#define REC_DIR_PATH                   "Record\\"                              /* 存放记录文件的统一目录 */

#define UPDCTRL_FILE_PATH              "https://gitee.com/leon1741/MySScom/raw/main/update/update.ini"

#define UPDCTRL_HEAD_FLAG              "<NewVerInfo>"
#define UPDCTRL_TAIL_FLAG              "<UpdateLink>"

#define README_FILE_PATH               "https://gitee.com/leon1741/MySScom/blob/main/README.md"

/*************************************************************************************************/
/*                                     版本控制开关                                              */
/*************************************************************************************************/
#define  VERSION_COMON                 0x01                                    /* 公共版本 */
#define  VERSION_YAXON                 0x02                                    /* 雅迅版本 */

#define  VERSION_CTRL                  VERSION_YAXON

/*************************************************************************************************/
/*                                     程序发行版本属性标记                                      */
/*************************************************************************************************/
#define RELEASE_VERSION                1                                       /* 是否为正式发布版本 */

/*************************************************************************************************/
/*                                     系统配置文件字段定义                                      */
/*************************************************************************************************/
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
/*                                     各字段参数名称定义                                        */
/*************************************************************************************************/
#define SYSRUNREC_RUNTIMES             "RunTimes"
#define SYSRUNREC_PROGMVER             "ProgmVer"

/*************************************************************************************************/
/*                                     RGB颜色值定义                                             */
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
/*                                     用户自定义消息值                                          */
/*************************************************************************************************/
typedef enum {
	WM_USERMSG_NOTIFYICON = WM_USER + 100,                                     // 处理托盘图标消息
	WM_USERMSG_COMDEVLIST,                                                     // 串口设备立即更新
	WM_USERMSG_COMDEVWAIT,                                                     // 串口设备稍候更新
	WM_USERMSG_DATARECVED,                                                     // 处理收到串口数据
	WM_USERMSG_DATATOSEND,                                                     // 有串口数据要发送
	WM_USERMSG_ARDLGCLOSE,                                                     // 自动回复窗口关闭
	WM_USERMSG_DFDLGCLOSE,                                                     // 显示过滤窗口关闭
	WM_USERMSG_EFDLGCLOSE,                                                     // 附加功能窗口关闭
	WM_USERMSG_SSDLGCLOSE,                                                     // 高级发送窗口关闭
	WM_USERMSG_KWDLGCLOSE,                                                     // 关键字符监听关闭
	WM_USERMSG_NOTDEFINED
} WM_USERMSG_INDEX;

#define STATIC_TEXT                    "快捷键提示：\r\nF1：查看帮助提示;\r\nF2：打开Record目录;\r\nF5：清空接收区内容;\r\nF8：开始发送文件;\r\nF12：保存接收的数据;\r\n其他：暂未定义;"

class CMySScomApp : public CWinApp
{
public:
	CMySScomApp();

	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

