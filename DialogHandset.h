#pragma once

#define  Timer_No_HstLink            0xA1                          // 手柄心跳数据的定时器

// CDialogHandset 对话框

class CDialogHandset : public CDialog
{
	DECLARE_DYNAMIC(CDialogHandset)

public:
	CDialogHandset(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogHandset();

	bool s_recv_head;
	char s_recv_buff[64];
	int  s_recv_dlen;

	void SendHstData(char ch);
	void ShowHideHstWindow(bool show);
	void HandleHstProtcol(void);
	void HandleUSARTData(char *ptr, DWORD len);


// 对话框数据
	enum { IDD = IDD_DIALOG_HANDSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonc();
	afx_msg void OnBnClickedButtonok();
	afx_msg void OnBnClickedButtonup();
	afx_msg void OnBnClickedButtondown();
	afx_msg void OnBnClickedButtonset();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtonX();
	afx_msg void OnBnClickedButtonJ();
	CRichEditCtrl m_RichEdit;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtono();
	afx_msg void OnBnClickedStaticFrame();
	CStatic m_Picture_Line1;
	CStatic m_Picture_Line2;
	CStatic m_Picture_BAT;
	CStatic m_Picture_GPS;
	CStatic m_Picture_Phone;
	CStatic m_Picture_SMS;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	CStatic m_Picture_GSM0;
	CStatic m_Picture_GSM1;
	CStatic m_Picture_GSM2;
	CStatic m_Picture_GSM3;
	CStatic m_Picture_GSM4;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
