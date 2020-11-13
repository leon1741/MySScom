// DialogAbout.cpp : implementation file
//

#include "stdafx.h"
#include "MySScom.h"
#include "DialogAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogAbout dialog


CDialogAbout::CDialogAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogAbout)
	m_Edit_About = _T("");
	m_showfuncfile = FALSE;
	//}}AFX_DATA_INIT
}


void CDialogAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAbout)
	DDX_Text(pDX, IDC_EDIT_ABOUT, m_Edit_About);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAbout, CDialog)
	//{{AFX_MSG_MAP(CDialogAbout)
	ON_BN_CLICKED(IDC_BUTTON_READOK, OnButtonReadOK)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, OnButtonSwitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/* ==================================== 自定义函数区--开始 ===================================== */


void CDialogAbout::ReadandDisplayFile(bool fileshown)
{
    CFile myFile;
	CString FileName;
	
	if (fileshown) {						                         // 设置文件名
		FileName = "功能简要说明.txt";
	} else {
		FileName = "修改升级记录.txt";
	}
	
	if (myFile.Open(FileName, CFile::modeRead) == 0) {
		MessageBox("读取文件失败，请确认路径正确且文件未处于打开状态！    ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	myFile.SeekToBegin();
	
	int nLength = myFile.GetLength();
	char * TempStr = new char[nLength];							     // 分配空间
	CString ResultStr;
	
	myFile.Read(TempStr, nLength);								     // 读取文件内容
	m_Edit_About.Format(_T("%s"), TempStr);
	m_Edit_About = m_Edit_About.Left(nLength);
	
	SetDlgItemText(IDC_EDIT_ABOUT, m_Edit_About);
	
	myFile.Close();												     // 关闭文件
	
	delete []TempStr;											     // 释放空间
	
	GetDlgItem(IDC_STATIC_ABOUT)->SetFocus();
}


/* ==================================== 自定义函数区--结束 ===================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ================================== 各个控件消息处理--开始 =================================== */


void CDialogAbout::OnButtonSwitch() 
{
	CEdit* s_Edit_Show;
	
	s_Edit_Show = (CEdit*)GetDlgItem(IDC_EDIT_ABOUT);
	
    if (m_showfuncfile == TRUE) {
		m_showfuncfile = FALSE;
		SetDlgItemText(IDC_BUTTON_SWITCH, "功能简介");
		SetDlgItemText(IDC_STATIC_ABOUT,  "程序升级记录");
		s_Edit_Show->ShowScrollBar(1, TRUE);
		ReadandDisplayFile(m_showfuncfile);
	} else {
		m_showfuncfile = TRUE;
		SetDlgItemText(IDC_BUTTON_SWITCH, "升级记录");
		SetDlgItemText(IDC_STATIC_ABOUT,  "程序功能简介");
		s_Edit_Show->ShowScrollBar(1, FALSE);
		ReadandDisplayFile(m_showfuncfile);
	}
}

void CDialogAbout::OnButtonReadOK() 
{
	OnOK();
}


/* ================================== 各个控件消息处理--结束 =================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */

BOOL CDialogAbout::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    OnButtonSwitch();
	
	return TRUE;
}


