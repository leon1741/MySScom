// MySScomDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_)
#define AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  Timer_No_StatusBar       0x01                               // 状态栏定时更新定时器
#define  Timer_No_AutoSend        0x02                               // 自动发送数据定时器
#define  Timer_No_SendFile        0x03                               // 发送长文件时的间隔定时器

#define  SEND_SHORT_DATA          0x01                               // 处于发送短数据的状态
#define  SEND_LONG_FILE           0x02                               // 处于发送长文件的状态

#define  MAX_RECV_LINE            500                                // 最多允许接收的数据行数，大于此数则清屏
#define  MAX_RECV_CHAR            (MAX_RECV_LINE * 3 * 100)          // 最多允许接收的字符个数，大于此数则清屏

#define  MAX_SEND_BYTE            500                                // 一次最多允许发送的字节数


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
	CComboBox	m_Combo_Stop;
	CComboBox	m_Combo_Data;
	CComboBox	m_Combo_Baud;
	CComboBox	m_Combo_ComNo;
	BOOL	m_Check_AutoSave;
	BOOL	m_Check_AutoSend;
	BOOL	m_Check_HexDspl;
	BOOL	m_Check_HexSend;
	CString	m_Edit_Recv;
	CString	m_Edit_Send;
	CString	m_Edit_Timer;
	CMSComm	m_ctrlComm;
	BOOL	m_Check_AutoClear;
	//}}AFX_DATA

	CEdit*         s_Edit_Recv;                                      // 调试消息显示控件
	CEdit*         s_Edit_Send;                                      // 协议数据显示控件

	CStringArray   sPorts;                                           // 用来枚举电脑上存在的串口

	bool           m_bCanDisplay;                                    // 判断是否需要暂停显示
	bool           m_bSendPause;                                     // 判断是否需要暂停发送

	bool           m_PortOpened;                                     // 判断串口是否已经打开

	int            Send_Status;                                      // 判断处于发送长文件还是短数据的状态
	int            Send_Counter;                                     // 发送大数据时，本次发送的数据段计数单元

	CString        StrRecved;                                        // 用来保存已经接收的数据内容
	CString        StrToSend;                                        // 用来存放需要发送的数据内容

	int            RecvedData;                                       // 已经接收的字节数
	int            SendedData;                                       // 已经发送的字节数

	CStatusBarCtrl m_StatusBar;                                      // 定义状态栏控制

	BOOL EnumComm(void);
	CString TransformtoHex(CString InputStr);
	char ConvertHexChar(char ch);
	int  String2Hex(CString str, CByteArray &senddata);
	void SetControlStatus(bool Enable);
	
	void SaveEditContent(void);
	void UpdateEditDisplay(void);
	void NeedAutoSendData(void);
	void UpdateStatusBarNow(void);

	void InitiateStatusBar(void);

	void InitiateComboComs(void);
	void InitiateComboBaud(void);
	void InitiateComboData(void);
	void InitiateComboStop(void);

	void SendEditDatatoComm(void);
	void ContinueToSendFile(void);
	
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
	afx_msg void OnButtonRead();
	afx_msg void OnButtonRespite();
	afx_msg void OnButtonReiput();
	afx_msg void OnButtonSend();
	afx_msg void OnCheckHexDisplay();
	afx_msg void OnCheckAutoSave();
	afx_msg void OnCheckHexSend();
	afx_msg void OnCheckAutoSend();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOnCommMscomm();
	afx_msg void OnButtonCount();
	afx_msg void OnCheckAutoClear();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_)
