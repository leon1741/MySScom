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

#define  Timer_No_RecvData             0x01                          // ���մ������ݶ�ʱ��
#define  Timer_No_StatusBar            0x02                          // ״̬����ʱ���¶�ʱ��
#define  Timer_No_AutoSend             0x03                          // �Զ��������ݶ�ʱ��
#define  Timer_No_FrameDspl            0x04                          // �Զ�������ʾ��ʱ��
#define  Timer_No_SendFile             0x05                          // �����ļ����ݶ�ʱ��

#define  MAX_RECV_BYTE                 4096                          // һ�����������յ��ֽ���
#define  MAX_SEND_BYTE                 2048                          // һ����������͵��ֽ���
#define  MAX_LOOP_BYTE                 500000                        // ѭ��������ÿһ�������͵�����ֽ���

#define  EDIT_REFRESH_TIME             40                            // �༭��ˢ��ʱ���� (��λ: ����)
#define  CHNGLINE_INTERVAL             100                           // 16����ģʽ���ж�֡���е��ӳ�ʱ�� (��λ: ����)

#define  FILESEND_BYTE                 100                           // �����ļ�ʱÿ�η��͵��ֽ���

#define  PROGRESS_POS                  1000                          // ��������С���ȿ̶�

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

	CEdit          *s_Edit_Recv;                                       // ���ձ༭����ָ��
	CEdit          *s_Edit_Send;                                       // ���ͱ༭����ָ��
	CDialogSrSend  *s_PDlgSrSend;                                      // �߼����ʹ��ھ��ָ��
	CDialogExfunct *s_PDlgExfunc;                                      // ���ӹ��ܴ��ھ��ָ��

	CStringArray    s_PortNumber;                                      // ����ö�ٵ����ϴ��ڵĴ���
	CString         s_RecvString;                                      // ���������Ѿ����յ���������

	bool            s_PortOpened;                                      // �жϴ����Ƿ��Ѿ���
	bool            s_RecvPaused;                                      // �ж��Ƿ���Ҫ��ͣ����
	bool            s_NeedChgLne;                                      // ����Ƿ���Ҫ������ʾ
	bool            s_DataRecved;                                      // �Ƿ��Ѿ��յ���������

	bool            s_datahdling;                                      // ��־��ǰ���ڴ���������

	int             s_LopSendCnt;                                      // ѭ���������ݵļ�����
	int             s_RecvedLine;                                      // �Ѿ����յ�����
	int             s_RecvedByte;                                      // �Ѿ����յ��ֽ���
	int             s_SendedByte;                                      // �Ѿ����͵��ֽ���

	unsigned long   s_FileDatPos;                                      // �ļ���ǰ���͵�λ��

	int             s_SrsDlgXPos;                                      // ��¼�߼����ʹ��ڵ�Xλ��
	int             s_SrsDlgYPos;                                      // ��¼�߼����ʹ��ڵ�Yλ��

	int             s_ExfDlgXPos;                                      // ��¼���ӹ��ܴ��ڵ�Xλ��
	int             s_ExfDlgYPos;                                      // ��¼���ӹ��ܴ��ڵ�Yλ��
	
	CStatusBar      s_CStatusBar;                                      // ����״̬������

	CWinThread     *s_ThreadHdle;                                      // �����߳̾��
	volatile HANDLE s_FileHandle;                                      // �����ļ����
	OVERLAPPED      s_EventoRead;                                      // ���ڶ�ȡ�¼�����
	OVERLAPPED      s_EventWrite;                                      // ����д���¼�����


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
