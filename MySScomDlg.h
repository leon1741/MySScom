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

#define  Timer_No_StatusBar       0x01                               // ״̬����ʱ���¶�ʱ��
#define  Timer_No_AutoSend        0x02                               // �Զ��������ݶ�ʱ��
#define  Timer_No_SendFile        0x03                               // ���ͳ��ļ�ʱ�ļ����ʱ��

#define  SEND_SHORT_DATA          0x01                               // ���ڷ��Ͷ����ݵ�״̬
#define  SEND_LONG_FILE           0x02                               // ���ڷ��ͳ��ļ���״̬

#define  MAX_RECV_LINE            500                                // ���������յ��������������ڴ���������
#define  MAX_RECV_CHAR            (MAX_RECV_LINE * 3 * 100)          // ���������յ��ַ����������ڴ���������

#define  MAX_SEND_BYTE            500                                // һ����������͵��ֽ���


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

	CEdit*         s_Edit_Recv;                                      // ������Ϣ��ʾ�ؼ�
	CEdit*         s_Edit_Send;                                      // Э��������ʾ�ؼ�

	CStringArray   sPorts;                                           // ����ö�ٵ����ϴ��ڵĴ���

	bool           m_bCanDisplay;                                    // �ж��Ƿ���Ҫ��ͣ��ʾ
	bool           m_bSendPause;                                     // �ж��Ƿ���Ҫ��ͣ����

	bool           m_PortOpened;                                     // �жϴ����Ƿ��Ѿ���

	int            Send_Status;                                      // �жϴ��ڷ��ͳ��ļ����Ƕ����ݵ�״̬
	int            Send_Counter;                                     // ���ʹ�����ʱ�����η��͵����ݶμ�����Ԫ

	CString        StrRecved;                                        // ���������Ѿ����յ���������
	CString        StrToSend;                                        // ���������Ҫ���͵���������

	int            RecvedData;                                       // �Ѿ����յ��ֽ���
	int            SendedData;                                       // �Ѿ����͵��ֽ���

	CStatusBarCtrl m_StatusBar;                                      // ����״̬������

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
