// MySScomDlg.h : header file
//
//{{AFX_INCLUDES()
//}}AFX_INCLUDES

#include "DialogSrSend.h"

#if !defined(AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_)
#define AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  MAXBLOCK                      2048
#define  XON                           0x11
#define  XOFF                          0x13

#define  Timer_No_RecvData             0x01                          // 接收串口数据定时器
#define  Timer_No_StatusBar            0x02                          // 状态栏定时更新定时器
#define  Timer_No_AutoSend             0x03                          // 自动发送数据定时器

#define  MAX_SEND_BYTE                 1024                          // 一次最多允许发送的字节数
#define  MAX_LOOP_BYTE                 500000                        // 循环发送区每一次允许发送的最大字节数

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
	CComboBox	m_Combo_Check;
	CComboBox	m_Combo_Stop;
	CComboBox	m_Combo_Data;
	CComboBox	m_Combo_Baud;
	CComboBox	m_Combo_ComNo;
	BOOL	m_Check_AutoSave;
	BOOL	m_Check_AutoSend;
	BOOL	m_Check_HexDspl;
	BOOL	m_Check_HexSend;
	BOOL	m_Check_AutoClear;
	CString	m_Edit_Recv;
	CString	m_Edit_Send;
	CString	m_Edit_AutoTimer;
	CString	m_Edit_Lines;
	BOOL	m_Check_Return;
	BOOL	m_Check_ShowTime;
	//}}AFX_DATA

	CEdit*         s_Edit_Recv;                                      // 接收编辑框
	CEdit*         s_Edit_Send;                                      // 发送编辑框

	CStringArray   sPorts;                                           // 用来枚举电脑上存在的串口
	CString        StrRecved;                                        // 用来保存已经接收的数据内容

	bool           m_PortOpened;                                     // 判断串口是否已经打开
	bool           m_bRecvPause;                                     // 判断是否需要暂停接收
	bool           m_NeedTime;                                       // 判断是否需要显示时间标志
	bool           m_DataRecvd;                                      // 是否已经收到串口数据

	int            Loop_Counter;                                     // 循环发送数据的计数器
	int            RecvedLine;                                       // 已经接收的行数
	int            RecvedData;                                       // 已经接收的字节数
	int            SendedData;                                       // 已经发送的字节数
    int            MaxRecvLines;                                     // 最多允许接收的行数

	int            s_top_offset;                                     // 切换显示模式时的上部偏移量
	int            s_left_offset;                                    // 切换显示模式时的左部偏移量

	int            s_displaycnt;

	CStatusBar     m_StatusBar;                                      // 定义状态栏控制

	CWinThread    *m_pThread;
	volatile BOOL  m_bConnected;
	volatile HANDLE m_hSPCom;
	OVERLAPPED     m_osRead, m_osWrite;

	CDialogSrSend *p_DlgSrSend;

	BOOL EnumComm();
	DWORD ReadComm(char *buf, DWORD dwLength);
	DWORD WriteComm(char *buf, DWORD dwLength);
	
	void SetControlStatus(bool Enable);
	void SetSendButtonStatus(bool Enable);
	void SetSendingStatus(bool Enable);
	void SwitchSendStatus(bool IsNormal);
	
	char ConvertHexChar(char ch);
	int String2Hex(CString str, CByteArray &senddata);
	CString TransformtoHex(CString InputStr);
	bool CharisValid(unsigned char inchar);

	void InformDlgClose(void);
	void SaveEditContent(void);
	void UpdateEditDisplay(void);
	void HandleUSARTData(char *ptr, DWORD len);
	void NeedAutoSendData(void);
	void UpdateStatusBarNow(void);
	bool SendDatatoComm(CString datastr, BOOL needhex);
	
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
	afx_msg void OnButtonHelp();
	afx_msg void OnButtonSrSend();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_)
