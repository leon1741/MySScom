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

/* ==================================== �Զ��庯����--��ʼ ===================================== */


void CDialogAbout::ReadandDisplayFile(bool fileshown)
{
    CFile myFile;
	CString FileName;
	
	if (fileshown) {						                         // �����ļ���
		FileName = "���ܼ�Ҫ˵��.txt";
	} else {
		FileName = "�޸�������¼.txt";
	}
	
	if (myFile.Open(FileName, CFile::modeRead) == 0) {
		MessageBox("��ȡ�ļ�ʧ�ܣ���ȷ��·����ȷ���ļ�δ���ڴ�״̬��    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	myFile.SeekToBegin();
	
	int nLength = myFile.GetLength();
	char * TempStr = new char[nLength];							     // ����ռ�
	CString ResultStr;
	
	myFile.Read(TempStr, nLength);								     // ��ȡ�ļ�����
	m_Edit_About.Format(_T("%s"), TempStr);
	m_Edit_About = m_Edit_About.Left(nLength);
	
	SetDlgItemText(IDC_EDIT_ABOUT, m_Edit_About);
	
	myFile.Close();												     // �ر��ļ�
	
	delete []TempStr;											     // �ͷſռ�
	
	GetDlgItem(IDC_STATIC_ABOUT)->SetFocus();
}


/* ==================================== �Զ��庯����--���� ===================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ================================== �����ؼ���Ϣ����--��ʼ =================================== */


void CDialogAbout::OnButtonSwitch() 
{
	CEdit* s_Edit_Show;
	
	s_Edit_Show = (CEdit*)GetDlgItem(IDC_EDIT_ABOUT);
	
    if (m_showfuncfile == TRUE) {
		m_showfuncfile = FALSE;
		SetDlgItemText(IDC_BUTTON_SWITCH, "���ܼ��");
		SetDlgItemText(IDC_STATIC_ABOUT,  "����������¼");
		s_Edit_Show->ShowScrollBar(1, TRUE);
		ReadandDisplayFile(m_showfuncfile);
	} else {
		m_showfuncfile = TRUE;
		SetDlgItemText(IDC_BUTTON_SWITCH, "������¼");
		SetDlgItemText(IDC_STATIC_ABOUT,  "�����ܼ��");
		s_Edit_Show->ShowScrollBar(1, FALSE);
		ReadandDisplayFile(m_showfuncfile);
	}
}

void CDialogAbout::OnButtonReadOK() 
{
	OnOK();
}


/* ================================== �����ؼ���Ϣ����--���� =================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */

BOOL CDialogAbout::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    OnButtonSwitch();
	
	return TRUE;
}


