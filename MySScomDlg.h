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

#define  Timer_No_Main       0x01                                    // 定义定时器序号

/////////////////////////////////////////////////////////////////////////////
// CMySScomDlg dialog

class CMySScomDlg : public CDialog
{
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
	//}}AFX_DATA

	CEdit*         s_Edit_Recv;                                      // 调试消息显示控件
	CEdit*         s_Edit_Send;                                      // 协议数据显示控件

	CStringArray   sPorts;                                           // 用来枚举电脑上存在的串口
	bool           m_bCanDisplay;                                    // 判断是否需要暂停显示
	bool           m_PortOpened;                                     // 判断串口是否已经打开

	CString        ReceiveStr;                                       // 用来保存所接收的数据内容

	BOOL EnumComm(void);
	CString TransformtoHex(CString InputStr);
	char ConvertHexChar(char ch);
	int  String2Hex(CString str, CByteArray &senddata);
	void RePaintWindows(void);
	void SetControlStatus(bool Enable);
	void NeedClearWindow(void);
	void UpdateEditDisplay(void);
	void NeedAutoSendData(void);

	void InitiateComboComs(void);
	void InitiateComboBaud(void);
	void InitiateComboData(void);
	void InitiateComboStop(void);

	void SendEditDatatoComm(void);
	
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
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSSCOMDLG_H__F4B9224E_CA46_4200_BF89_E729A2094F99__INCLUDED_)
