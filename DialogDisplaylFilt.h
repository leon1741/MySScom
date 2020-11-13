#pragma once

#define  _OPEN_MODE                   0x00                                     // ȫ��ģʽ
#define  _FILT_MODE                   0x01                                     // ����ģʽ
#define  _MATH_MODE                   0x02                                     // ƥ��ģʽ

class CDialogDsplFilt : public CDialog
{
	DECLARE_DYNAMIC(CDialogDsplFilt)

public:
	CDialogDsplFilt(CWnd* pParent = NULL);
	virtual ~CDialogDsplFilt();

	int     m_Radio_FilterMode;
	CString m_Edit_Str1;
	CString m_Edit_Str2;
	CString m_Edit_Str3;
	CString m_Edit_Str4;
	CString m_Edit_Str5;

	int     s_DialogPos_X;                                                     /* ��¼���ڵ�Xλ�� */
	int     s_DialogPos_Y;                                                     /* ��¼���ڵ�Yλ�� */

	void ShowHideDlgWindow(bool show);
	void InitiateAllParas(void);
	void RecordAllParas(void);
	bool StringCanDisplay(CString inputstr);

	enum { IDD = IDD_DIALOG_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	bool FilterEditValid(void);
	void SetEditControlEnble(bool enable);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioOpenmode();
	afx_msg void OnBnClickedRadioFiltmode();
	afx_msg void OnBnClickedRadioDsplmode();
};
