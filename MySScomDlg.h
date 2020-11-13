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

#define  Timer_No_StatusBar            0x01                          // 状态栏定时更新定时器
#define  Timer_No_AutoSend             0x02                          // 自动发送数据定时器
#define  Timer_No_LoopSend             0x03                          // 高级发送功能的循环定时器

#define  MAX_RECV_CHAR(n)              (n * 3 * 100)                 // 最多允许接收的字符个数，根据行数来计算

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
	BOOL	m_Check_LoopSend;
	BOOL	m_Check_HexDspl;
	BOOL	m_Check_HexSend;
	BOOL	m_Check_AutoClear;
	CString	m_Edit_Recv;
	CString	m_Edit_Send;
	CString	m_Edit_AutoTimer;
	CString	m_Edit_LoopTimer;
	CMSComm	m_ctrlComm;	
	BOOL	m_Check_SrSend_01;
	BOOL	m_Check_SrSend_02;
	BOOL	m_Check_SrSend_03;
	BOOL	m_Check_SrSend_04;
	BOOL	m_Check_SrSend_05;
	BOOL	m_Check_SrSend_06;
	BOOL	m_Check_SrSend_07;
	BOOL	m_Check_SrSend_08;
	BOOL	m_Check_SrSend_09;
	BOOL	m_Check_SrSend_10;
	BOOL	m_Check_SrSend_11;
	BOOL	m_Check_SrSend_12;
	BOOL	m_Check_SrSend_13;
	BOOL	m_Check_SrSend_14;
	BOOL	m_Check_SrSend_15;
	BOOL	m_Check_SrSend_16;
	BOOL	m_Check_SrSend_17;
	BOOL	m_Check_SrSend_18;
	BOOL	m_Check_SrSend_19;
	BOOL	m_Check_SrSend_20;
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
	bool           m_SrSendEnable;                                   // 判断是否启用高级发送功能
	bool           m_NeedTime;                                       // 判断是否需要显示时间标志

	int            Loop_Counter;                                     // 循环发送数据的计数器
	int            RecvedData;                                       // 已经接收的字节数
	int            SendedData;                                       // 已经发送的字节数
    int            MaxRecvLines;                                     // 最多允许接收的行数

	int            s_top_offset;                                     // 切换显示模式时的上部偏移量
	int            s_left_offset;                                    // 切换显示模式时的左部偏移量

	CStatusBar     m_StatusBar;                                      // 定义状态栏控制

	BOOL EnumComm(void);
	CString TransformtoHex(CString InputStr);
	char ConvertHexChar(char ch);
	int  String2Hex(CString str, CByteArray &senddata);

	void SetControlStatus(bool Enable);
	void SetSendButtonStatus(bool Enable);
	void SetSrSendCtrlStatus(bool Enable);
	void SetSendingStatus(bool Enable);
	void SwitchSendStatus(bool IsNormal);
	
	void SaveEditContent(void);
	void UpdateEditDisplay(void);
	void NeedAutoSendData(void);
	void NeedLoopSendData(void);
	void UpdateStatusBarNow(void);

	void CreateSettingFile(void);
	void InitiateAllParas(void);
	void RecordAllParas(void);

	void InitiateStatusBar(void);

	void InitiateComboComs(void);
	void InitiateComboBaud(void);
	void InitiateComboData(void);
	void InitiateComboCheck(void);
	void InitiateComboStop(void);

	void InitiateMainFrame(void);
	void InitiateSrSendArea(void);

	void SendEditDatatoComm(void);
	void ContinueToSendFile(void);

	void ShowSrSendCheck(bool Enable);	
	void ShowSrSendEdit(bool Enable);
	void ShowSrSendButton(bool Enable);
	void ShowSrSendOthers(bool Enable);

	void HideSrSendArea(void);
	void ShowSrSendArea(void);

	bool SrEditDataValid(int EditID);
	int  GetSrValidDataNo(void);
	void TrytoSrSendData(CString InputStr, BOOL NeedHex);
	void ContinueLoopSrSend(void);

	BOOL TaskBarDeleteIcon(HWND hwnd, UINT uID);
	BOOL TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip);
	
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
	afx_msg void OnButtonSrSend();
	afx_msg void OnCheckSrAuto();
	afx_msg void OnButtonSrSend01();
	afx_msg void OnButtonSrSend02();
	afx_msg void OnButtonSrSend03();
	afx_msg void OnButtonSrSend04();
	afx_msg void OnButtonSrSend05();
	afx_msg void OnButtonSrSend06();
	afx_msg void OnButtonSrSend07();
	afx_msg void OnButtonSrSend08();
	afx_msg void OnButtonSrSend09();
	afx_msg void OnButtonSrSend10();
	afx_msg void OnButtonSrSend11();
	afx_msg void OnButtonSrSend12();
	afx_msg void OnButtonSrSend13();
	afx_msg void OnButtonSrSend14();
	afx_msg void OnButtonSrSend15();
	afx_msg void OnButtonSrSend16();
	afx_msg void OnButtonSrSend17();
	afx_msg void OnButtonSrSend18();
	afx_msg void OnButtonSrSend19();
	afx_msg void OnButtonSrSend20();
	afx_msg void OnCheckSrSend01();
	afx_msg void OnCheckSrSend02();
	afx_msg void OnCheckSrSend03();
	afx_msg void OnCheckSrSend04();
	afx_msg void OnCheckSrSend05();
	afx_msg void OnCheckSrSend06();
	afx_msg void OnCheckSrSend07();
	afx_msg void OnCheckSrSend08();
	afx_msg void OnCheckSrSend09();
	afx_msg void OnCheckSrSend10();
	afx_msg void OnCheckSrSend11();
	afx_msg void OnCheckSrSend12();
	afx_msg void OnCheckSrSend13();
	afx_msg void OnCheckSrSend14();
	afx_msg void OnCheckSrSend15();
	afx_msg void OnCheckSrSend16();
	afx_msg void OnCheckSrSend17();
	afx_msg void OnCheckSrSend18();
	afx_msg void OnCheckSrSend19();
	afx_msg void OnCheckSrSend20();
	afx_msg void OnClose();
	afx_msg void OnMenuTrayExit();
	afx_msg void OnMenuTrayHide();
	afx_msg void OnMenuTrayShow();
	afx_msg void OnMyIconNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCheckReturn();
	afx_msg void OnCheckShowTime();
	afx_msg void OnMenuTrayAbout();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_)
