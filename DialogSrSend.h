#if !defined(AFX_DIALOGSRSEND_H__D5EE9170_8155_4446_8A5A_E16C5C494469__INCLUDED_)
#define AFX_DIALOGSRSEND_H__D5EE9170_8155_4446_8A5A_E16C5C494469__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSrSend.h : header file
//

#define  Timer_No_SrAllSend            0x81                          // 全部数据自动连发的定时器
#define  Timer_No_SrEachSend           0x82                          // 各条数据自动连发的定时器

/////////////////////////////////////////////////////////////////////////////
// CDialogSrSend dialog

class CDialogSrSend : public CDialog
{
// Construction
public:
	CDialogSrSend(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogSrSend)
	enum { IDD = IDD_DIALOG_SRSEND };
	BOOL	m_Check_01;
	BOOL	m_Check_02;
	BOOL	m_Check_03;
	BOOL	m_Check_04;
	BOOL	m_Check_05;
	BOOL	m_Check_06;
	BOOL	m_Check_07;
	BOOL	m_Check_08;
	BOOL	m_Check_09;
	BOOL	m_Check_10;
	BOOL	m_Check_11;
	BOOL	m_Check_12;
	BOOL	m_Check_13;
	BOOL	m_Check_14;
	BOOL	m_Check_15;
	BOOL	m_Check_16;
	BOOL	m_Check_17;
	BOOL	m_Check_18;
	BOOL	m_Check_19;
	BOOL	m_Check_20;
	BOOL	m_Check_21;
	BOOL	m_Check_22;
	BOOL	m_Check_23;
	BOOL	m_Check_24;
	BOOL	m_Check_25;
	BOOL	m_Check_26;
	BOOL	m_Check_27;
	BOOL	m_Check_28;
	BOOL	m_Check_29;
	BOOL	m_Check_30;
	BOOL	m_Check_31;
	BOOL	m_Check_32;
	BOOL	m_Check_33;
	BOOL	m_Check_34;
	BOOL	m_Check_35;
	BOOL	m_Check_36;
	BOOL	m_Check_37;
	BOOL	m_Check_38;
	BOOL	m_Check_39;
	BOOL	m_Check_40;
	CString	m_Edit_AutoTime;
	CString	m_Edit_T01;
	CString	m_Edit_T02;
	CString	m_Edit_T03;
	CString	m_Edit_T04;
	CString	m_Edit_T05;
	CString	m_Edit_T06;
	CString	m_Edit_T07;
	CString	m_Edit_T08;
	CString	m_Edit_T09;
	CString	m_Edit_T10;
	CString	m_Edit_T11;
	CString	m_Edit_T12;
	CString	m_Edit_T13;
	CString	m_Edit_T14;
	CString	m_Edit_T15;
	CString	m_Edit_T16;
	CString	m_Edit_T17;
	CString	m_Edit_T18;
	CString	m_Edit_T19;
	CString	m_Edit_T20;
	CString	m_Edit_T21;
	CString	m_Edit_T22;
	CString	m_Edit_T23;
	CString	m_Edit_T24;
	CString	m_Edit_T25;
	CString	m_Edit_T26;
	CString	m_Edit_T27;
	CString	m_Edit_T28;
	CString	m_Edit_T29;
	CString	m_Edit_T30;
	CString	m_Edit_T31;
	CString	m_Edit_T32;
	CString	m_Edit_T33;
	CString	m_Edit_T34;
	CString	m_Edit_T35;
	CString	m_Edit_T36;
	CString	m_Edit_T37;
	CString	m_Edit_T38;
	CString	m_Edit_T39;
	CString	m_Edit_T40;
	int		m_Radio_SendAll;
	//}}AFX_DATA

	bool           s_expandmode;                                               // 是否处于扩展发送模式
	unsigned int   s_curdatacnt;                                               // 当前发送到第几个数据
	bool           s_cirsendall;                                               // 是否需要轮回发送全部数据
	bool           s_issenddata;                                               // 是否正处于发送数据中

	int            s_sendcnt[40];                                              // 记录每一条数据的发送计数

	bool EditDataValid(int EditID);
	bool EditDataTimeValid(int EditID, int TimeID);
	bool CanSendEditData(int editno, int TimeID);
	int  GetSrValidDataNo(void);
	void TrytoSendData(CString InputStr, BOOL NeedHex);
	void TrytoContinueSend(void);
	void TrytoSendEachData(void);
	void ShowHideTimeEdit(bool enanble);
	void InitateSrDlgPos(void);
	void ShowHideSrDlgWindow(bool show);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSrSend)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogSrSend)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonExpand();
	afx_msg void OnButtonSend01();
	afx_msg void OnButtonSend02();
	afx_msg void OnButtonSend03();
	afx_msg void OnButtonSend04();
	afx_msg void OnButtonSend05();
	afx_msg void OnButtonSend06();
	afx_msg void OnButtonSend07();
	afx_msg void OnButtonSend08();
	afx_msg void OnButtonSend09();
	afx_msg void OnButtonSend10();
	afx_msg void OnButtonSend11();
	afx_msg void OnButtonSend12();
	afx_msg void OnButtonSend13();
	afx_msg void OnButtonSend14();
	afx_msg void OnButtonSend15();
	afx_msg void OnButtonSend16();
	afx_msg void OnButtonSend17();
	afx_msg void OnButtonSend18();
	afx_msg void OnButtonSend19();
	afx_msg void OnButtonSend20();
	afx_msg void OnButtonSend21();
	afx_msg void OnButtonSend22();
	afx_msg void OnButtonSend23();
	afx_msg void OnButtonSend24();
	afx_msg void OnButtonSend25();
	afx_msg void OnButtonSend26();
	afx_msg void OnButtonSend27();
	afx_msg void OnButtonSend28();
	afx_msg void OnButtonSend29();
	afx_msg void OnButtonSend30();
	afx_msg void OnButtonSend31();
	afx_msg void OnButtonSend32();
	afx_msg void OnButtonSend33();
	afx_msg void OnButtonSend34();
	afx_msg void OnButtonSend35();
	afx_msg void OnButtonSend36();
	afx_msg void OnButtonSend37();
	afx_msg void OnButtonSend38();
	afx_msg void OnButtonSend39();
	afx_msg void OnButtonSend40();
	afx_msg void OnCheck01();
	afx_msg void OnCheck02();
	afx_msg void OnCheck03();
	afx_msg void OnCheck04();
	afx_msg void OnCheck05();
	afx_msg void OnCheck06();
	afx_msg void OnCheck07();
	afx_msg void OnCheck08();
	afx_msg void OnCheck09();
	afx_msg void OnCheck10();
	afx_msg void OnCheck11();
	afx_msg void OnCheck12();
	afx_msg void OnCheck13();
	afx_msg void OnCheck14();
	afx_msg void OnCheck15();
	afx_msg void OnCheck16();
	afx_msg void OnCheck17();
	afx_msg void OnCheck18();
	afx_msg void OnCheck19();
	afx_msg void OnCheck20();
	afx_msg void OnCheck21();
	afx_msg void OnCheck22();
	afx_msg void OnCheck23();
	afx_msg void OnCheck24();
	afx_msg void OnCheck25();
	afx_msg void OnCheck26();
	afx_msg void OnCheck27();
	afx_msg void OnCheck28();
	afx_msg void OnCheck29();
	afx_msg void OnCheck30();
	afx_msg void OnCheck31();
	afx_msg void OnCheck32();
	afx_msg void OnCheck33();
	afx_msg void OnCheck34();
	afx_msg void OnCheck35();
	afx_msg void OnCheck36();
	afx_msg void OnCheck37();
	afx_msg void OnCheck38();
	afx_msg void OnCheck39();
	afx_msg void OnCheck40();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnRadioSendAll();
	afx_msg void OnRadioSendEach();
	afx_msg void OnButtonStartSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSRSEND_H__D5EE9170_8155_4446_8A5A_E16C5C494469__INCLUDED_)
