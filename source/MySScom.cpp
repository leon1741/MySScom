
#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CMySScomApp, CWinApp)
	//{{AFX_MSG_MAP(CMySScomApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


CMySScomApp::CMySScomApp()
{
	;
}

CMySScomApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMySScomApp initialization

BOOL CMySScomApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	CMySScomDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	if (nResponse == IDOK) {
		;
	} else if (nResponse == IDCANCEL)	{
		;
	}

	return FALSE;
}
