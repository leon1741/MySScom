#include "stdafx.h"
#include "MySScom.h"
#include "DialogKeywords.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(CDialogKeywords, CDialog)

CDialogKeywords::CDialogKeywords(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogKeywords::IDD, pParent)
{
	m_Edit_MatchRec = _T("");
}

CDialogKeywords::~CDialogKeywords()
{
	;
}

void CDialogKeywords::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MATCHREC, m_Edit_MatchRec);
}

BEGIN_MESSAGE_MAP(CDialogKeywords, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVEALL, &CDialogKeywords::OnButtonSaveall)
	ON_BN_CLICKED(IDC_BUTTON_EXITALL, &CDialogKeywords::OnButtonExitall)
	ON_BN_CLICKED(IDC_BUTTON_CLEARALL, &CDialogKeywords::OnButtonClearall)
	ON_BN_CLICKED(IDC_BUTTON_SAVEFILE, &CDialogKeywords::OnButtonSavefile)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEWIN, &CDialogKeywords::OnButtonClosewin)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== ����Ϊ�ڲ����ߺ��� ===================================== */



/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */

void CDialogKeywords::OnClose()
{
	ShowHideDlgWindow(FALSE);
	RecordAllParas();

	CDialog::OnClose();
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== ����Ϊ�ؼ���Ϣ���� ===================================== */


/**************************************************************************************************
**  ��������:  OnButtonSaveall
**  ��������:  ����ȫ���������˳�
**************************************************************************************************/
void CDialogKeywords::OnButtonSaveall()
{
	CString ParaStr, EditStr;

	for (int i = IDC_EDIT_KEYWORD1; i <= IDC_EDIT_KEYWORD8; i++) {             /* ������������ַ��������� */
		GetDlgItemText(i, ParaStr);
		EditStr.Format("Keywrd%.2d", i + 1 - IDC_EDIT_KEYWORD1);
		::WritePrivateProfileString(FLAG_KEYWDMTCH, EditStr, ParaStr, CONFIGFILENAME);
	}
}

/**************************************************************************************************
**  ��������:  OnButtonExitall
**  ��������:  ����ȫ���޸Ĳ��˳�
**************************************************************************************************/
void CDialogKeywords::OnButtonExitall()
{
	char TempChar[MAX_KEYWORD_LEN];
	CString tempstr;

	for (int i = IDC_EDIT_KEYWORD1; i <= IDC_EDIT_KEYWORD8; i++) {             /* ��ʼ�����������ַ��������� */
		tempstr.Format("Keywrd%.2d", i + 1 - IDC_EDIT_KEYWORD1);
		::GetPrivateProfileString(FLAG_KEYWDMTCH, tempstr, "", TempChar, MAX_KEYWORD_LEN, CONFIGFILENAME);
		tempstr.Format("%s", TempChar);
		SetDlgItemText(i, tempstr);
	}
}

/**************************************************************************************************
**  ��������:  OnButtonClearall
**  ��������:  ���ȫ��ƥ�����ļ�¼
**************************************************************************************************/
void CDialogKeywords::OnButtonClearall()
{
	if (MessageBox("ȷ��Ҫ�������յ���ȫ��������գ�", "��ʾ", MB_OKCANCEL + MB_ICONQUESTION) != IDOK) {
		return;
	}
	
	m_Edit_MatchRec = "";
	SetDlgItemText(IDC_EDIT_MATCHREC, m_Edit_MatchRec);
}

/**************************************************************************************************
**  ��������:  OnButtonSavefile
**  ��������:  ��ƥ�����ļ�¼���浽�ļ�
**************************************************************************************************/
void CDialogKeywords::OnButtonSavefile()
{
	CFile   MyFile;                                                            /* �����ļ��� */
	CTime   NowTime  = CTime::GetCurrentTime();                                /* ��ȡ����ʱ�� */
	CString FileName = NowTime.Format("KeyWord_Rec_%y-%m-%d_%H-%M-%S") + ".txt";

	GetDlgItemText(IDC_EDIT_MATCHREC, m_Edit_MatchRec);

	if (m_Edit_MatchRec.GetLength() == 0) {
		MessageBox("��δ���յ��κ���Ч���ݣ����豣��......", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}

	MyFile.Open(REC_DIR_PATH + FileName, CFile::modeCreate | CFile::modeReadWrite);
	MyFile.Write(m_Edit_MatchRec, m_Edit_MatchRec.GetLength());                /* д���ı��ļ� */
	MyFile.Close();                                                            /* �ر��ļ� */

	MessageBox("���������Ѿ��ɹ�������ָ���ļ�!      ", "��ϲ", MB_OK + MB_ICONINFORMATION);
}

/**************************************************************************************************
**  ��������:  OnButtonClosewin
**  ��������:  �رմ���
**************************************************************************************************/
void CDialogKeywords::OnButtonClosewin()
{
	ShowHideDlgWindow(FALSE);
	RecordAllParas();
	
	OnOK();
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊ����ӿں��� ===================================== */

/**************************************************************************************************
**  ��������:  ShowHideDlgWindow
**  ��������:  ��ʾ�����ر����ڣ�������ȡ�ʹ洢����λ�ò���
**************************************************************************************************/
void CDialogKeywords::ShowHideDlgWindow(bool show)
{
	CRect rect;

	GetWindowRect(&rect);

	if (show == TRUE) {
		SetWindowPos(NULL, s_DialogPos_X, s_DialogPos_Y, rect.Width(), rect.Height(), SWP_NOSIZE);
		UpdateData(FALSE);
		ShowWindow(SW_SHOW);
	} else {
		s_DialogPos_X = rect.left;
		s_DialogPos_Y = rect.top;
		ShowWindow(SW_HIDE);
	}
}

/**************************************************************************************************
**  ��������:  InitiateAllParas
**  ��������:  ��ʼ����������
**************************************************************************************************/
void CDialogKeywords::InitiateAllParas(void)
{
	s_DialogPos_X = (::GetPrivateProfileInt(FLAG_KEYWDMTCH, KEYWDMTCH_POSTIONX, 0, CONFIGFILENAME));
	s_DialogPos_Y = (::GetPrivateProfileInt(FLAG_KEYWDMTCH, KEYWDMTCH_POSTIONY, 0, CONFIGFILENAME));

	OnButtonExitall();                                                         /* ��ȡ�����ļ�����ʼ���ؼ� */

	UpdateData(FALSE);                                                         /* ���±༭������ */
}

/**************************************************************************************************
**  ��������:  RecordAllParas
**  ��������:  �����������
**************************************************************************************************/
void CDialogKeywords::RecordAllParas(void)
{
	CString ParaStr;

	if ((s_DialogPos_X < 0) || (s_DialogPos_X > MAX_WIN_POS)) {                /* ��ֹ�߽��쳣 */
		s_DialogPos_X = 0;
	}

	if ((s_DialogPos_Y < 0) || (s_DialogPos_Y > MAX_WIN_POS)) {                /* ��ֹ�߽��쳣 */
		s_DialogPos_Y = 0;
	}
	
	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString(FLAG_KEYWDMTCH, KEYWDMTCH_POSTIONX, ParaStr, CONFIGFILENAME);

	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString(FLAG_KEYWDMTCH, KEYWDMTCH_POSTIONY, ParaStr, CONFIGFILENAME);

	OnButtonSaveall();                                                         /* �洢�ؼ����ݵ������ļ� */
}

/**************************************************************************************************
**  ��������:  GetKeywordMax
**  ��������:  ��ȡ�ؼ��ָ������ֵ
**************************************************************************************************/
int CDialogKeywords::GetKeywordMax(void)
{
	return MAX_KEYWORD_NUM;
}

/**************************************************************************************************
**  ��������:  GetKeywordX
**  ��������:  ��ȡ�ؼ�������
**  �������:  index: 1-8
**************************************************************************************************/
CString CDialogKeywords::GetKeywordX(int index)
{
	char TempChar[MAX_KEYWORD_LEN];
	CString tempstr;

	if ((index == 0) || (index > MAX_KEYWORD_NUM)) {
		return "";
	}
	
	tempstr.Format("Keywrd%.2d", index);
	::GetPrivateProfileString(FLAG_KEYWDMTCH, tempstr, "", TempChar, MAX_KEYWORD_LEN, CONFIGFILENAME);
	tempstr.Format("%s", TempChar);

	return tempstr;
}

/**************************************************************************************************
**  ��������:  AddNewMatchRec
**  ��������:  ��ƥ��ɹ�����Ϣ׷�Ӽ�¼����
**************************************************************************************************/
void CDialogKeywords::AddNewMatchRec(int index)
{
	CTime     NowTime;
	CString   ShowStr, TimeStr;

	NowTime = CTime::GetCurrentTime();                                         /* ��ȡ��ǰϵͳʱ�� */
	TimeStr = NowTime.Format("[%H:%M:%S]");

	ShowStr = TimeStr + " Recv Keyword \"" + GetKeywordX(index) + "\"\r\n";

	m_Edit_MatchRec += ShowStr;
	SetDlgItemText(IDC_EDIT_MATCHREC, m_Edit_MatchRec);

	((CEdit *)GetDlgItem(IDC_EDIT_MATCHREC))->SetSel(-1, -1);
	((CEdit *)GetDlgItem(IDC_EDIT_MATCHREC))->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


