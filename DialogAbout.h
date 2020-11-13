#if !defined(AFX_DIALOGABOUT_H__6597D98B_6FC3_4AB9_8943_D2F04B4B2CD6__INCLUDED_)
#define AFX_DIALOGABOUT_H__6597D98B_6FC3_4AB9_8943_D2F04B4B2CD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAbout.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogAbout dialog

class CDialogAbout : public CDialog
{
// Construction
public:
	CDialogAbout(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogAbout)
	enum { IDD = IDD_DIALOG_ABOUT };
	CString	m_Edit_About;
	//}}AFX_DATA

	bool m_showfuncfile;
    
	void CDialogAbout::ReadandDisplayFile(bool fileshown);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogAbout)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReadOK();
	afx_msg void OnButtonSwitch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGABOUT_H__6597D98B_6FC3_4AB9_8943_D2F04B4B2CD6__INCLUDED_)
