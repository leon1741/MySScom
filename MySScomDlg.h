// MySScomDlg.h : header file
//
//{{AFX_INCLUDES()
//}}AFX_INCLUDES

#include "DialogSrSend.h"
#include "DialogExfunct.h"

#if !defined(AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_)
#define AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  XON                           0x11
#define  XOFF                          0x13

#define  Timer_No_RecvData             0x01                          // 接收串口数据定时器
#define  Timer_No_StatusBar            0x02                          // 状态栏定时更新定时器
#define  Timer_No_AutoSend             0x03                          // 自动发送数据定时器
#define  Timer_No_FrameDspl            0x04                          // 自动换行显示定时器
#define  Timer_No_SendFile             0x05                          // 发送文件数据定时器

#define  MAX_RECV_BYTE                 4096                          // 一次最多允许接收的字节数
#define  MAX_SEND_BYTE                 2048                          // 一次最多允许发送的字节数
#define  MAX_LOOP_BYTE                 500000                        // 循环发送区每一次允许发送的最大字节数

#define  EDIT_REFRESH_TIME             40                            // 编辑框刷新时间间隔 (单位: 毫秒)
#define  CHNGLINE_INTERVAL             100                           // 16进制模式下判断帧换行的延迟时间 (单位: 毫秒)

#define  FILESEND_BYTE                 100                           // 发送文件时每次发送的字节数

#define  PROGRESS_POS                  1000                          // 进度条最小进度刻度

#define  MYWM_NOTIFYICON               (WM_USER + 1001)

/////////////////////////////////////////////////////////////////////////////
// CMySScomDlg dialog

class CMySScomDlg : public CDialog
{
DECLARE_EASYSIZE
// Construction
public:
	CMySScomDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMySScomDlg)
	enum { IDD = IDD_MYSSCOM_DIALOG };
	CProgressCtrl	m_Progress_SendFile;
	CComboBox	m_Combo_Check;
	CComboBox	m_Combo_Stop;
	CComboBox	m_Combo_Data;
	CComboBox	m_Combo_Baud;
	CComboBox	m_Combo_ComNo;
	BOOL		m_Check_AutoSave;
	BOOL		m_Check_AutoSend;
	BOOL		m_Check_HexDspl;
	BOOL		m_Check_HexSend;
	BOOL		m_Check_AutoClear;
	CString		m_Edit_Recv;
	CString		m_Edit_Send;
	CString		m_Edit_AutoTimer;
	CString		m_Edit_Lines;
	BOOL		m_Check_Return;
	BOOL		m_Check_ShowTime;
	BOOL		m_Check_FrameDspl;
	BOOL		m_Check_ShowDirect;
	BOOL		m_Check_ShowSData;
	CString	m_Edit_FilePath;
	//}}AFX_DATA

	CEdit          *s_Edit_Recv;                                       // 接收编辑框句柄指针
	CEdit          *s_Edit_Send;                                       // 发送编辑框句柄指针
	CDialogSrSend  *s_PDlgSrSend;                                      // 高级发送窗口句柄指针
	CDialogExfunct *s_PDlgExfunc;                                      // 附加功能窗口句柄指针

	CStringArray    s_PortNumber;                                      // 用来枚举电脑上存在的串口
	CString         s_RecvString;                                      // 用来保存已经接收的数据内容

	bool            s_PortOpened;                                      // 判断串口是否已经打开
	bool            s_RecvPaused;                                      // 判断是否需要暂停接收
	bool            s_NeedChgLne;                                      // 标记是否需要换行显示
	bool            s_DataRecved;                                      // 是否已经收到串口数据

	bool            s_datahdling;                                      // 标志当前正在处理串口数据

	int             s_LopSendCnt;                                      // 循环发送数据的计数器
	int             s_RecvedLine;                                      // 已经接收的行数
	int             s_RecvedByte;                                      // 已经接收的字节数
	int             s_SendedByte;                                      // 已经发送的字节数

	unsigned long   s_FileDatPos;                                      // 文件当前发送的位置

	int             s_SrsDlgXPos;                                      // 记录高级发送窗口的X位置
	int             s_SrsDlgYPos;                                      // 记录高级发送窗口的Y位置

	int             s_ExfDlgXPos;                                      // 记录附加功能窗口的X位置
	int             s_ExfDlgYPos;                                      // 记录附加功能窗口的Y位置
	
	CStatusBar      s_CStatusBar;                                      // 定义状态栏控制

	CWinThread     *s_ThreadHdle;                                      // 串口线程句柄
	volatile HANDLE s_FileHandle;                                      // 串口文件句柄
	OVERLAPPED      s_EventoRead;                                      // 串口读取事件对象
	OVERLAPPED      s_EventWrite;                                      // 串口写入事件对象


	BOOL  EnumComm();
	DWORD ReadComm(char *buf, DWORD dwLength);
	DWORD WriteComm(char *buf, DWORD dwLength);
	
	char    ConvertHexChar(char ch);
	int     String2Hex(CString str, CByteArray &senddata);
	CString TransformtoHex(CString InputStr);
	bool    CharisValid(unsigned char inchar);

	void SetControlStatus(bool Enable);
	void SetSendCtrlArea(bool Enable);
	void InformSrDlgClose(void);
	void InformExDlgClose(void);
	bool SaveEditContent(void);
	void UpdateEditStr(CString showstr);
	void UpdateEditDisplay(void);
	void ShowSendData(CString sstr);
	void HandleUSARTData(char *ptr, DWORD len);
	void NeedAutoSendData(void);
	void UpdateStatusBarNow(void);
	bool SendDatatoComm(CString datastr, BOOL needhex);
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

	BOOL TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip);
	BOOL TaskBarDeleteIcon(HWND hwnd, UINT uID);
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySScomDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMySScomDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonONOFF();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonSend();
	afx_msg void OnCheckHexDisplay();
	afx_msg void OnCheckAutoSave();
	afx_msg void OnCheckHexSend();
	afx_msg void OnCheckAutoSend();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnOnCommMscomm();
	afx_msg void OnButtonCount();
	afx_msg void OnCheckAutoClear();
	afx_msg void OnClose();
	afx_msg void OnMenuTrayExit();
	afx_msg void OnMenuTrayHide();
	afx_msg void OnMenuTrayShow();
	afx_msg void OnMyIconNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCheckReturn();
	afx_msg void OnCheckShowTime();
	afx_msg void OnMenuTrayAbout();
	afx_msg void OnButtonSrSend();
	afx_msg void OnCheckFrameDspl();
	afx_msg void OnCheckShowDirec();
	afx_msg void OnCheckShowSData();
	afx_msg void OnButtonExfunct();
	afx_msg void OnButtonAboutMe();
	afx_msg void OnButtonOpenFile();
	afx_msg void OnButtonSendFile();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_)
