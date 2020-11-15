#pragma once

/*************************************************************************************************/
/*                                     ���ֶβ������ƶ���                                        */
/*************************************************************************************************/
#define KEYWDMTCH_POSTIONX             "PostionX"
#define KEYWDMTCH_POSTIONY             "PostionY"

/*************************************************************************************************/
/*                                     ģ��궨��                                                */
/*************************************************************************************************/
#define MAX_KEYWORD_NUM                8                                       /* ���֧�ֵ��ַ������� */
#define MAX_KEYWORD_LEN                512                                     /* ���֧�ֵ��ַ������� */

class CDialogKeywords : public CDialog
{
	DECLARE_DYNAMIC(CDialogKeywords)

public:
	CDialogKeywords(CWnd* pParent = NULL);
	virtual ~CDialogKeywords();

	void ShowHideDlgWindow(bool show);
	void InitiateAllParas(void);
	void RecordAllParas(void);
	int GetKeywordMax(void);
	CString GetKeywordX(int index);
	void AddNewMatchRec(int index);

	int      s_DialogPos_X;                                                    /* ��¼���ڵ�Xλ�� */
	int      s_DialogPos_Y;                                                    /* ��¼���ڵ�Yλ�� */

	enum { IDD = IDD_DIALOG_KEYWORDS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:

	CString m_Edit_MatchRec;

	afx_msg void OnButtonSaveall();
	afx_msg void OnButtonExitall();
	afx_msg void OnButtonClearall();
	afx_msg void OnButtonSavefile();
	afx_msg void OnButtonClosewin();
	afx_msg void OnClose();
};
