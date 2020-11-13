#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogAboutMe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDialogAboutMe::CDialogAboutMe(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAboutMe::IDD, pParent)
{
	m_Edit_About = _T("");
	m_showfuncfile = FALSE;
}


void CDialogAboutMe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ABOUT, m_Edit_About);
}


BEGIN_MESSAGE_MAP(CDialogAboutMe, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_READOK, OnButtonReadOK)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, OnButtonSwitch)
END_MESSAGE_MAP()


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊģ���ڲ����� ===================================== */


/**************************************************************************************************
**  ��������:  ReadandDisplayFile
**  ��������:  ��ȡ����ʾ�ļ�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogAboutMe::ReadandDisplayFile(bool fileshown)
{
    CFile   myFile;
	CString FileName;
	
	if (fileshown) {						                                   // �����ļ���
		FileName = "���ܼ�Ҫ˵��.txt";
	} else {
		FileName = "�޸�������¼.txt";
	}
	
	if (myFile.Open(FileName, CFile::modeRead) == 0) {

		SetDlgItemText(IDC_EDIT_ABOUT, "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n                      ��Ϣ�ļ���ȡʧ�ܣ���ȷ��·����ȷ���ļ�δ���ڴ�״̬��");
		UpdateData(TRUE);

	} else {

		myFile.SeekToBegin();
		
		int nLength = (int)(myFile.GetLength());
		char * TempStr = new char[nLength];							           // ����ռ�
		
		myFile.Read(TempStr, nLength);								           // ��ȡ�ļ�����

        m_Edit_About = TempStr;
        m_Edit_About = m_Edit_About.Left(nLength);
		SetDlgItemText(IDC_EDIT_ABOUT, m_Edit_About);
		
		myFile.Close();												           // �ر��ļ�
		
		delete []TempStr;											           // �ͷſռ�
	}
	
	GetDlgItem(IDC_STATIC_ABOUT)->SetFocus();
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ================================== �����ؼ���Ϣ����--��ʼ =================================== */


/**************************************************************************************************
**  ��������:  OnButtonSwitch
**  ��������:  �л���ʾ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogAboutMe::OnButtonSwitch() 
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

    UpdateData(FALSE);
}

/**************************************************************************************************
**  ��������:  OnButtonReadOK
**  ��������:  �ɹ�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogAboutMe::OnButtonReadOK() 
{
	OnOK();
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */


/**************************************************************************************************
**  ��������:  OnInitDialog
**  ��������:  ��ʼ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
BOOL CDialogAboutMe::OnInitDialog() 
{
    CDialog::OnInitDialog();
	
    OnButtonSwitch();
	
	return TRUE;
}

