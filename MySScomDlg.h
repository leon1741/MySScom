#pragma once

#include "threadserial.h"
#include "updatemanage.h"
#include "DialogDisplaylFilt.h"
#include "DialogSuperSend.h"
#include "DialogExtrafunct.h"
#include "DialogKeywords.h"
#include "DialogAutoReply.h"

/*************************************************************************************************/
/*                                     定时器值定义                                              */
/*************************************************************************************************/
#define Timer_No_UpdateDsp             0x01                                    /* 刷新显示内容定时器 */
#define Timer_No_StatusBar             0x02                                    /* 状态栏定时更新定时器 */
#define Timer_No_AutoSend              0x03                                    /* 自动发送数据定时器 */
#define Timer_No_FrameDspl             0x04                                    /* 自动换行显示定时器 */
#define Timer_No_SendFile              0x05                                    /* 发送文件数据定时器 */
#define Timer_No_SrAllSend             0x06                                    /* 全部数据自动连发的定时器 */
#define Timer_No_SrEachSend            0x07                                    /* 各条数据自动连发的定时器 */

/*************************************************************************************************/
/*                                     各字段参数名称定义                                        */
/*************************************************************************************************/
#define MAINFRAME_POSTIONX             "PostionX"
#define MAINFRAME_POSTIONY             "PostionY"
#define MAINFRAME_COMMPORT             "CommPort"
#define MAINFRAME_BAUDRATE             "BaudRate"
#define MAINFRAME_DATABITS             "DataBits"
#define MAINFRAME_CHECKBIT             "CheckBit"
#define MAINFRAME_STOPBITS             "StopBits"
#define MAINFRAME_SHOWTIME             "ShowTime"
#define MAINFRAME_HEXDISPL             "HexDispl"
#define MAINFRAME_HEXFRAME             "HexFrame"
#define MAINFRAME_PROTOACK             "ProtoAck"
#define MAINFRAME_AUTOCLER             "AutoCler"
#define MAINFRAME_AUTOSAVE             "AutoSave"
#define MAINFRAME_AUTOFILT             "AutoFilt"
#define MAINFRAME_KEYWORDS             "KeyWords"
#define MAINFRAME_HEXSSEND             "HexsSend"
#define MAINFRAME_CRLFSEND             "CRLFSend"
#define MAINFRAME_AUTOSEND             "AutoSend"
#define MAINFRAME_SENDHEXS             "SendHexs"
#define MAINFRAME_SENDSTRS             "SendStrs"
#define MAINFRAME_FILEPATH             "FilePath"
#define MAINFRAME_AUTCLRKB             "AutClrKB"
#define MAINFRAME_SENDTIME             "SendTime"

/*************************************************************************************************/
/*                                     模块宏定义                                                */
/*************************************************************************************************/
#define UPDATEEDIT_TIME                50                                      /* 编辑框刷新时间间隔 (单位: 毫秒) */
#define CHNGLINE_INTERVAL              100                                     /* 16进制模式下判断帧换行的延迟时间 (单位: 毫秒) */
#define STATUSBAR_TIME                 1000                                    /* 状态栏刷新时间间隔 (单位: 毫秒) */

#define FILESEND_BYTE                  100                                     /* 发送文件时每次发送的字节数 */

#define PROGRESS_POS                   1000                                    /* 进度条最小进度刻度 */

#define MIN_WIN_WIDTH                  860                                     /* 窗体宽度最小值 */
#define MIN_WIN_HIGHT                  540                                     /* 窗体高度最小值 */

#define STATIC_LEFT                    18                                      /* 全屏显示时，提示信息框的左上角坐标 */
#define STATIC_TOP                     480                                     /* 全屏显示时，提示信息框的左上角坐标 */
#define STATIC_WIDTH                   122                                     /* 全屏显示时，提示信息框的宽度 */
#define STATIC_HEIGHT                  85                                      /* 全屏显示时，提示信息框的高度 */

#define MAINWIN_HEIGHT                 650                                     /* 可以显示提示信息的高度 */

class CMySScomDlg : public CDialog
{
DECLARE_EASYSIZE

public:
	CMySScomDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_MYSSCOM_DIALOG };

	CProgressCtrl	    m_Progs_SendFile;                                      /* 发送文件的进度条 */

	CComboBox		    m_Combo_CommPort;                                      /* 串口号 */
	CComboBox		    m_Combo_BaudRate;                                      /* 波特率 */
	CComboBox		    m_Combo_DataBits;                                      /* 数据位 */
	CComboBox		    m_Combo_CheckBit;                                      /* 校验位 */
	CComboBox		    m_Combo_StopBits;                                      /* 结束位 */

	BOOL			    m_Check_ShowTime;                                      /* 是否显示时间 */
	BOOL			    m_Check_HexDispl;                                      /* 是否16进制显示 */
	BOOL			    m_Check_HexFrame;                                      /* 是否以帧格式显示 */
	BOOL			    m_Check_ProtoACK;                                      /* 是否自动应答协议 */
	BOOL			    m_Check_AutoCler;                                      /* 是否自动清空 */
	BOOL			    m_Check_AutoSave;                                      /* 是否自动保存 */
	BOOL			    m_Check_AutoFilt;                                      /* 是否自动过滤 */
	BOOL			    m_Check_Keywords;                                      /* 是否关键词匹配 */
	BOOL			    m_Check_HexsSend;                                      /* 是否16进制格式发送 */
	BOOL			    m_Check_CRLFSend;                                      /* 是否发送回车换行符 */
	BOOL			    m_Check_AutoSend;	                                   /* 是否自动发送 */

	CString			    m_Edit_RecvCstr;                                       /* 接收编辑框 */
	CString			    m_Edit_SendCstr;                                       /* 发送编辑框 */

	CString			    m_Edit_SendTime;                                       /* 自动发送的时间 */
	CString			    m_Edit_AutClrKB;                                       /* 自动清空的字节数（单位KB） */
	CString			    m_Edit_FilePath;                                       /* 发送文件的路径 */

	CRichEditCtrl       m_RichEdit_Recv;                                       /* 接收编辑框的ctrl控件 */

	int                 s_DialogPos_X;                                         /* 记录窗口的X位置 */
	int                 s_DialogPos_Y;                                         /* 记录窗口的Y位置 */

	CEdit              *s_Edit_Recv;                                           /* 接收编辑框句柄指针 */
	CEdit              *s_Edit_Send;                                           /* 发送编辑框句柄指针 */

	CDialogDsplFilt    *s_PDlgDsplFilt;                                        /* 显示内容过滤  窗口句柄指针 */
	CDialogSuperSend   *s_PDlgSuprSend;                                        /* 高级发送功能  窗口句柄指针 */
	CDialogExtrafunct  *s_PDlgExtrfunc;                                        /* 附加计算功能  窗口句柄指针 */
	CDialogAutoReply   *s_PDlgAutoRply;                                        /* 自动回复功能  窗口句柄指针 */
	CDialogKeywords    *s_PDlgKeyWords;                                        /* 关键字符监听  窗口句柄指针 */

	CStringArray        s_PortNumber;                                          /* 用来枚举电脑上存在的串口 */
	CString             s_RecvString;                                          /* 用来保存已经接收的数据内容 */

	CString             s_SendStr_Chr;                                         /* 发送区所输入的字符串 */
	CString             s_SendStr_Hex;                                         /* 发送区所输入的16进制 */
	
	bool                s_RecvPaused;                                          /* 判断是否需要暂停接收 */
	bool                s_NeedChgLne;                                          /* 标记是否需要换行显示 */
	bool                s_DataRecved;                                          /* 是否已经收到串口数据 */
	bool                s_DevNeedUpd;                                          /* 串口设备是否需要更新 */
	bool                s_ChkingUpdt;                                          /* 是否正在检测程序更新 */

	int                 s_LopSendCnt;                                          /* 循环发送数据的计数器 */
	int                 s_RecvedByte;                                          /* 已经接收的字节数 */
	int                 s_SendedByte;                                          /* 已经发送的字节数 */

	unsigned long       s_FileDatPos;                                          /* 文件当前发送的位置 */
	
	CStatusBar          s_CStatusBar;                                          /* 定义状态栏控制 */

	LONGLONG            s_StartdTcik;

	CStatic            *s_MainStatic;                                          /* 放置于主窗口的静态控件 */

	BOOL  EnumCommPortList(void);

	void SetControlStatus(bool Enable);
	void SetSendCtrlArea(bool Enable);

	void ShowAboutMeDialog(void);
	bool KeyWordMatchOK(CString showstr);
	void ShakeMainWindow(void);
	void AttractAttention(void);
	void CloseAllChildWin(void);
	bool UserFnKeyHdl(WPARAM key);
	void ExcuteAutoReply(CString instr);

	CString GetHighExactTime(void);
	bool SaveEditContent(void);
	void UpdateEditStr(CString showstr);
	void HandleUSARTData(unsigned char *sbuf, DWORD len);
	void NeedAutoSendData(void);
	void UpdateStatusBarNow(void);
	bool SendDatatoComm(unsigned char *sbuf, int slen, BOOL needhex);
	bool SendFileDatatoComm(void);

	bool ConfigFileCanUse(CString target);
	void CreateSettingFile(void);
	void InitiateAllParas(void);
	void RecordAllParas(void);
	
	void InitiateStatusBar(void);
	void InitiateComboComs(void);
	void InitiateComboBaud(void);
	void InitiateComboData(void);
	void InitiateComboCheck(void);
	void InitiateComboStop(void);
	bool InitiateChildWins(void);
	void InitiateToolsTip(void);
	void InitiateMainStatic(void);
	void UpdateMainStatic(void);
	void UpdateComboComs(void);

	BOOL TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip);
	BOOL TaskBarDeleteIcon(HWND hwnd, UINT uID);

protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnClose();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	afx_msg void OnButtonPortCtrl();
	afx_msg void OnButtonRecvPause();
	afx_msg void OnButtonClearAll();
	afx_msg void OnButtonSaveFile();
	afx_msg void OnButtonSendData();
	afx_msg void OnButtonSuperSend();
	afx_msg void OnButtonExtrafunc();
	afx_msg void OnButtonConfigKeywords();
	afx_msg void OnButtonOpenFile();
	afx_msg void OnButtonSendFile();
	afx_msg void OnButtonConfigDsplFilt();
	afx_msg void OnButtonConfigAutoReply();

	afx_msg void OnCheckHexDisplay();
	afx_msg void OnCheckAutoSave();
	afx_msg void OnCheckHexSend();
	afx_msg void OnCheckAutoSend();
	afx_msg void OnCheckAutoClear();
	afx_msg void OnCheckAddReturn();
	afx_msg void OnCheckShowTime();
	afx_msg void OnCheckFrameDspl();
	afx_msg void OnCheckDsplFilt();
	afx_msg void OnCheckAutoReply();
	afx_msg void OnCheckKeyword();

	afx_msg void OnChangeEditSendcstr();

	afx_msg void OnMenuTrayAbout();
	afx_msg void OnMenuTrayHide();
	afx_msg void OnMenuTrayShow();
	afx_msg void OnMenuTrayExit();

	afx_msg void OnMenuEditCopy();
	afx_msg void OnMenuEditClear();
	afx_msg void OnMenuEditFont();
	afx_msg void OnMenuEditAbout();
	afx_msg void OnMenuEditColorWhite();
	afx_msg void OnMenuEditColorGray();
	afx_msg void OnMenuEditColorGreen();
	afx_msg void OnMenuEditColorBlue();
	afx_msg void OnMenuEditColorPink();
	afx_msg void OnMenuEditColorPurple();

	afx_msg LRESULT OnUsrMsgHdlIconNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlComDevList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlComDevWait(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDataRecved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDatatoSend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlARDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDFDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlEFDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlSSDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlKWDlgClose(WPARAM wParam, LPARAM lParam);

	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()
};




