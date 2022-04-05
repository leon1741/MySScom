#pragma once

/*************************************************************************************************/
/*                                     ���ֶβ������ƶ���                                        */
/*************************************************************************************************/
#define AUTOREPLY_POSTIONX             "PostionX"
#define AUTOREPLY_POSTIONY             "PostionY"

/*************************************************************************************************/
/*                                     ģ��궨��                                                */
/*************************************************************************************************/
#define MAX_STR_NUM                    8                                       /* ���֧�ֵ��ַ������� */
#define MAX_STR_LEN                    512                                     /* ���֧�ֵ��ַ������� */


class CDialogAutoReply : public CDialog
{
	DECLARE_DYNAMIC(CDialogAutoReply)

public:
	CDialogAutoReply(CWnd* pParent = NULL);
	virtual ~CDialogAutoReply();

	void ShowHideDlgWindow(bool show);
	void InitiateAllParas(void);
	void RecordAllParas(void);

	int GetTotalStringNo(void);
	CString GetRecvString(int index);
	CString GetSendString(int index);

	int      s_DialogPos_X;                                                    /* ��¼���ڵ�Xλ�� */
	int      s_DialogPos_Y;                                                    /* ��¼���ڵ�Yλ�� */

	CString  s_RecvStrList[MAX_STR_NUM];                                       /* �����ַ����б� */
	CString  s_SendStrList[MAX_STR_NUM];                                       /* Ӧ���ַ����б� */

	enum { IDD = IDD_DIALOG_AUTOREPLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	void SetEditControlEnble(bool enable);
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonClearall();
	afx_msg void OnBnClickedButtonSavestr();
};


