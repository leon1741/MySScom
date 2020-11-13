#pragma once

#include "threadserial.h"
#include "DialogDisplaylFilt.h"
#include "DialogSuperSend.h"
#include "DialogExtrafunct.h"
#include "DialogAutoReply.h"
#include "DialogAboutMe.h"

/*************************************************************************************************/
/*                                     版本控制开关                                              */
/*************************************************************************************************/
#define  VERSION_LEON                  0x01                                    /* 对外版本 */
#define  VERSION_YAXON                 0x02                                    /* 雅迅版本 */

#define  VERSION_CTRL                  VERSION_YAXON

/*************************************************************************************************/
/*                                     定时器值定义                                              */
/*************************************************************************************************/
#define  Timer_No_UpdateDsp            0x01                                    /* 刷新显示内容定时器 */
#define  Timer_No_StatusBar            0x02                                    /* 状态栏定时更新定时器 */
#define  Timer_No_AutoSend             0x03                                    /* 自动发送数据定时器 */
#define  Timer_No_FrameDspl            0x04                                    /* 自动换行显示定时器 */
#define  Timer_No_SendFile             0x05                                    /* 发送文件数据定时器 */
#define  Timer_No_SrAllSend            0x06                                    /* 全部数据自动连发的定时器 */
#define  Timer_No_SrEachSend           0x07                                    /* 各条数据自动连发的定时器 */

/*************************************************************************************************/
/*                                     模块宏定义                                                */
/*************************************************************************************************/
#define  MAX_DISP_BYTE                 1000000                                 /* 显示区最多显示的内容（超过后自动清空） */

#define  UPDATEEDIT_TIME               50                                      /* 编辑框刷新时间间隔 (单位: 毫秒) */
#define  CHNGLINE_INTERVAL             100                                     /* 16进制模式下判断帧换行的延迟时间 (单位: 毫秒) */
#define  STATUSBAR_TIME                1000                                    /* 状态栏刷新时间间隔 (单位: 毫秒) */

#define  FILESEND_BYTE                 100                                     /* 发送文件时每次发送的字节数 */

#define  PROGRESS_POS                  1000                                    /* 进度条最小进度刻度 */

#define  MIN_WIN_WIDTH                 860                                     /* 窗体宽度最小值 */
#define  MIN_WIN_HIGHT                 510                                     /* 窗体高度最小值 */

class CMySScomDlg : public CDialog
{
DECLARE_EASYSIZE

public:
	CMySScomDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_MYSSCOM_DIALOG };
	CProgressCtrl	m_Progress_SendFile;
	CComboBox		m_Combo_Check;
	CComboBox		m_Combo_Stop;
	CComboBox		m_Combo_Data;
	CComboBox		m_Combo_Baud;
	CComboBox		m_Combo_ComNo;
	BOOL			m_Check_AutoSave;
	BOOL			m_Check_AutoSend;
	BOOL			m_Check_HexDspl;
	BOOL			m_Check_HexSend;
	BOOL			m_Check_AutoClear;
	CString			m_Edit_Recv;
	CString			m_Edit_Send;
	CString			m_Edit_AutoTimer;
	CString			m_Edit_Lines;
	BOOL			m_Check_Return;
	BOOL			m_Check_ShowTime;
	BOOL			m_Check_FrameDspl;
	BOOL			m_Check_AutoReply;
	BOOL			m_Check_Filter;
	CString			m_Edit_FilePath;
	CRichEditCtrl   m_RichEdit_Recv;

	int                 s_DialogPos_X;                                         /* 记录窗口的X位置 */
	int                 s_DialogPos_Y;                                         /* 记录窗口的Y位置 */

	CEdit              *s_Edit_Recv;                                           /* 接收编辑框句柄指针 */
	CEdit              *s_Edit_Send;                                           /* 发送编辑框句柄指针 */

	CDialogDsplFilt    *s_PDlgDsplFilt;                                        /* 过滤设置窗口句柄指针 */
	CDialogSuperSend   *s_PDlgSuprSend;                                        /* 高级发送窗口句柄指针 */
	CDialogExtrafunct  *s_PDlgExtrfunc;                                        /* 附加功能窗口句柄指针 */
	CDialogAutoReply   *s_PDlgAutoRply;                                        /* 自动回复窗口句柄指针 */

	CStringArray        s_PortNumber;                                          /* 用来枚举电脑上存在的串口 */
	CString             s_RecvString;                                          /* 用来保存已经接收的数据内容 */

	CString             s_SendStr_Chr;                                         /* 发送区所输入的字符串 */
	CString             s_SendStr_Hex;                                         /* 发送区所输入的16进制 */
	
	bool                s_RecvPaused;                                          /* 判断是否需要暂停接收 */
	bool                s_NeedChgLne;                                          /* 标记是否需要换行显示 */
	bool                s_DataRecved;                                          /* 是否已经收到串口数据 */

	int                 s_LopSendCnt;                                          /* 循环发送数据的计数器 */
	int                 s_RecvedLine;                                          /* 已经接收的行数 */
	int                 s_RecvedByte;                                          /* 已经接收的字节数 */
	int                 s_SendedByte;                                          /* 已经发送的字节数 */

	unsigned long       s_FileDatPos;                                          /* 文件当前发送的位置 */
	
	CStatusBar          s_CStatusBar;                                          /* 定义状态栏控制 */

	BOOL  EnumCommPortList();

	void SetControlStatus(bool Enable);
	void SetSendCtrlArea(bool Enable);

    void CloseAllChildWin(void);

	void InformAutoReplyDlgClose(void);
	void InformDsplFiltDlgClose(void);
	void InformExtrFuncDlgClose(void);
	void InformSuprSendDlgClose(void);

	bool SaveEditContent(void);
	void UpdateEditStr(CString showstr);
	void UpdateEditDisplay(void);
	void HandleUSARTData(unsigned char *sbuf, DWORD len);
    void ReadHandleUartData(void);
	void NeedAutoSendData(void);
	void UpdateStatusBarNow(void);
	bool SendDatatoComm(unsigned char *sbuf, int slen, BOOL needhex);
	bool SendFileDatatoComm(void);

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
	void UpdateComboComs(void);

	BOOL TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip);
	BOOL TaskBarDeleteIcon(HWND hwnd, UINT uID);

protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

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
	afx_msg LRESULT OnUsrMsgHdlDataRecved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDatatoSend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlARDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDFDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlEFDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlSSDlgClose(WPARAM wParam, LPARAM lParam);

	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()
};




