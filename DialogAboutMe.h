#pragma once

class CDialogAboutMe : public CDialog
{
public:
	CDialogAboutMe(CWnd* pParent = NULL);

	CString	m_Edit_About;
	bool m_showfuncfile;

	void CDialogAboutMe::ReadandDisplayFile(bool fileshown);

	enum { IDD = IDD_DIALOG_ABOUTME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:

	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReadOK();
	afx_msg void OnButtonSwitch();
	DECLARE_MESSAGE_MAP()
};


