#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogDisplaylFilt.h"


IMPLEMENT_DYNAMIC(CDialogDsplFilt, CDialog)

CDialogDsplFilt::CDialogDsplFilt(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogDsplFilt::IDD, pParent)
{
	m_Radio_FilterMode = -1;
	m_Edit_Str1 = _T("");
	m_Edit_Str2 = _T("");
	m_Edit_Str3 = _T("");
	m_Edit_Str4 = _T("");
	m_Edit_Str5 = _T("");
}

CDialogDsplFilt::~CDialogDsplFilt()
{
	;
}

void CDialogDsplFilt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_OPENMODE, m_Radio_FilterMode);
	DDX_Text(pDX, IDC_EDIT_STR1, m_Edit_Str1);
	DDX_Text(pDX, IDC_EDIT_STR2, m_Edit_Str2);
	DDX_Text(pDX, IDC_EDIT_STR3, m_Edit_Str3);
	DDX_Text(pDX, IDC_EDIT_STR4, m_Edit_Str4);
	DDX_Text(pDX, IDC_EDIT_STR5, m_Edit_Str5);
}


BEGIN_MESSAGE_MAP(CDialogDsplFilt, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_OPENMODE, &CDialogDsplFilt::OnBnClickedRadioOpenmode)
	ON_BN_CLICKED(IDC_RADIO_FILTMODE, &CDialogDsplFilt::OnBnClickedRadioFiltmode)
	ON_BN_CLICKED(IDC_RADIO_DSPLMODE, &CDialogDsplFilt::OnBnClickedRadioDsplmode)
END_MESSAGE_MAP()


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊģ���ڲ����� ===================================== */


/**************************************************************************************************
**  ��������:  FilterEditValid
**  ��������:  �жϹ����ַ����༭�������Ƿ���Ч
**  �������:  
**  ���ز���:  ֻҪ��һ��������Ч���򷵻�TRUE��ȫ����Ϊ�գ��򷵻�FALSE
**************************************************************************************************/
bool CDialogDsplFilt::FilterEditValid(void)
{
	if (m_Edit_Str1.GetLength() > 0) {
		return TRUE;
	}

	if (m_Edit_Str2.GetLength() > 0) {
		return TRUE;
	}

	if (m_Edit_Str3.GetLength() > 0) {
		return TRUE;
	}

	if (m_Edit_Str4.GetLength() > 0) {
		return TRUE;
	}

	if (m_Edit_Str5.GetLength() > 0) {
		return TRUE;
	}
	
	return FALSE;
}

/**************************************************************************************************
**  ��������:  SetEditControlEnble
**  ��������:  ���ø����༭��ؼ��Ŀɼ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogDsplFilt::SetEditControlEnble(bool enable)
{
	GetDlgItem(IDC_EDIT_STR1)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_STR2)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_STR3)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_STR4)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_STR5)->EnableWindow(enable);
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊ�ؼ���Ϣ���� ===================================== */


/**************************************************************************************************
**  ��������:  OnBnClickedRadioOpenmode
**  ��������:  �л�Ϊȫ��ģʽ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogDsplFilt::OnBnClickedRadioOpenmode()
{
	m_Radio_FilterMode = _OPEN_MODE;
	SetEditControlEnble(FALSE);
	UpdateData(TRUE);
}

/**************************************************************************************************
**  ��������:  OnBnClickedRadioFiltmode
**  ��������:  �л�Ϊ����ģʽ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogDsplFilt::OnBnClickedRadioFiltmode()
{
	m_Radio_FilterMode = _FILT_MODE;
	SetEditControlEnble(TRUE);
	UpdateData(TRUE);
}

/**************************************************************************************************
**  ��������:  OnBnClickedRadioDsplmode
**  ��������:  �л�Ϊƥ��ģʽ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogDsplFilt::OnBnClickedRadioDsplmode()
{
	m_Radio_FilterMode = _MATH_MODE;
	SetEditControlEnble(TRUE);
	UpdateData(TRUE);
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
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogDsplFilt::ShowHideDlgWindow(bool show)
{
	CRect rect;

	GetWindowRect(&rect);

	if (show == TRUE) {
		SetWindowPos(NULL, s_DialogPos_X, s_DialogPos_Y, rect.Width(), rect.Height(), SWP_NOSIZE);
		if (m_Radio_FilterMode == _OPEN_MODE) {
			SetEditControlEnble(FALSE);
		} else {
			SetEditControlEnble(TRUE);
		}
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
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogDsplFilt::InitiateAllParas(void)
{
	char TempChar[MAX_SEND_BYTE];
	
	s_DialogPos_X = (::GetPrivateProfileInt("DsplFilt", "DialogPos_X",  0, ".\\Settings.ini"));
	s_DialogPos_Y = (::GetPrivateProfileInt("DsplFilt", "DialogPos_Y",  0, ".\\Settings.ini"));

	m_Radio_FilterMode = (::GetPrivateProfileInt("DsplFilt", "FilterMode",  0, ".\\Settings.ini"));

	::GetPrivateProfileString("DsplFilt", "FilterStr1", "", TempChar, MAX_SEND_BYTE, ".\\Settings.ini");
	m_Edit_Str1.Format("%s", TempChar);
	SetDlgItemText(IDC_EDIT_STR1, m_Edit_Str1);

	::GetPrivateProfileString("DsplFilt", "FilterStr2", "", TempChar, MAX_SEND_BYTE, ".\\Settings.ini");
	m_Edit_Str2.Format("%s", TempChar);
	SetDlgItemText(IDC_EDIT_STR2, m_Edit_Str2);

	::GetPrivateProfileString("DsplFilt", "FilterStr3", "", TempChar, MAX_SEND_BYTE, ".\\Settings.ini");
	m_Edit_Str3.Format("%s", TempChar);
	SetDlgItemText(IDC_EDIT_STR3, m_Edit_Str3);

	::GetPrivateProfileString("DsplFilt", "FilterStr4", "", TempChar, MAX_SEND_BYTE, ".\\Settings.ini");
	m_Edit_Str4.Format("%s", TempChar);
	SetDlgItemText(IDC_EDIT_STR4, m_Edit_Str4);

	::GetPrivateProfileString("DsplFilt", "FilterStr5", "", TempChar, MAX_SEND_BYTE, ".\\Settings.ini");
	m_Edit_Str5.Format("%s", TempChar);
	SetDlgItemText(IDC_EDIT_STR5, m_Edit_Str5);

	UpdateData(FALSE);                                                         /* ���±༭������ */
}

/**************************************************************************************************
**  ��������:  RecordAllParas
**  ��������:  �����������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogDsplFilt::RecordAllParas(void)
{
	CString ParaStr;
	
	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString("DsplFilt", "DialogPos_X", ParaStr, ".\\Settings.ini");
	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString("DsplFilt", "DialogPos_Y", ParaStr, ".\\Settings.ini");

	ParaStr.Format("%d", m_Radio_FilterMode);
	::WritePrivateProfileString("DsplFilt", "FilterMode", ParaStr, ".\\Settings.ini");

	GetDlgItemText(IDC_EDIT_STR1, m_Edit_Str1);
	::WritePrivateProfileString("DsplFilt", "FilterStr1", m_Edit_Str1, ".\\Settings.ini");

	GetDlgItemText(IDC_EDIT_STR2, m_Edit_Str2);
	::WritePrivateProfileString("DsplFilt", "FilterStr2", m_Edit_Str2, ".\\Settings.ini");

	GetDlgItemText(IDC_EDIT_STR3, m_Edit_Str3);
	::WritePrivateProfileString("DsplFilt", "FilterStr3", m_Edit_Str3, ".\\Settings.ini");

	GetDlgItemText(IDC_EDIT_STR4, m_Edit_Str4);
	::WritePrivateProfileString("DsplFilt", "FilterStr4", m_Edit_Str4, ".\\Settings.ini");

	GetDlgItemText(IDC_EDIT_STR5, m_Edit_Str5);
	::WritePrivateProfileString("DsplFilt", "FilterStr5", m_Edit_Str5, ".\\Settings.ini");
}

/**************************************************************************************************
**  ��������:  StringCanDisplay
**  ��������:  �Թ����ַ�������ƥ�䣬������ƥ����
**  �������:  
**  ���ز���:  ��Ҫ��ʾ������TRUE������Ҫ��ʾ������FALSE
**************************************************************************************************/
bool CDialogDsplFilt::StringCanDisplay(CString inputstr)
{
	if (m_Radio_FilterMode == _OPEN_MODE) {                                    /* û�п������˹���ʱ��ȫ��������ʾ */
		return TRUE;
	}

	GetDlgItemText(IDC_EDIT_STR1, m_Edit_Str1);
	GetDlgItemText(IDC_EDIT_STR2, m_Edit_Str2);
	GetDlgItemText(IDC_EDIT_STR3, m_Edit_Str3);
	GetDlgItemText(IDC_EDIT_STR4, m_Edit_Str4);
	GetDlgItemText(IDC_EDIT_STR5, m_Edit_Str5);

	if (m_Radio_FilterMode == _FILT_MODE) {                                    /* ����ģʽ�£����˵������������ַ��� */

		if (FilterEditValid() == FALSE) {                                      /* û�������κι��˴�����ζ��ȫ������ʾ */
			return TRUE;
		}

		if ((m_Edit_Str1.GetLength() > 0) &&(inputstr.Find(m_Edit_Str1, 0) != -1)) {               /* �ַ���1ƥ��ɹ� */
			return FALSE;
		} else if ((m_Edit_Str2.GetLength() > 0) &&(inputstr.Find(m_Edit_Str2, 0) != -1)) {        /* �ַ���2ƥ��ɹ� */
			return FALSE;
		} else if ((m_Edit_Str3.GetLength() > 0) &&(inputstr.Find(m_Edit_Str3, 0) != -1)) {        /* �ַ���3ƥ��ɹ� */
			return FALSE;
		} else if ((m_Edit_Str4.GetLength() > 0) &&(inputstr.Find(m_Edit_Str4, 0) != -1)) {        /* �ַ���4ƥ��ɹ� */
			return FALSE;
		} else if ((m_Edit_Str5.GetLength() > 0) &&(inputstr.Find(m_Edit_Str5, 0) != -1)) {        /* �ַ���5ƥ��ɹ� */
			return FALSE;
		} else {
			return TRUE;
		}
	}

	if (m_Radio_FilterMode == _MATH_MODE) {                                    /* ƥ��ģʽ�£�ֻ�з����������ַ�����ͨ�� */
		
		if (FilterEditValid() == FALSE) {                                      /* û�������κ�ƥ�䴮����ζ��ȫ������ʾ */
			return FALSE;
		}

		if ((m_Edit_Str1.GetLength() > 0) &&(inputstr.Find(m_Edit_Str1, 0) != -1)) {               /* �ַ���1ƥ��ɹ� */
			return TRUE;
		} else if ((m_Edit_Str2.GetLength() > 0) &&(inputstr.Find(m_Edit_Str2, 0) != -1)) {        /* �ַ���2ƥ��ɹ� */
			return TRUE;
		} else if ((m_Edit_Str3.GetLength() > 0) &&(inputstr.Find(m_Edit_Str3, 0) != -1)) {        /* �ַ���3ƥ��ɹ� */
			return TRUE;
		} else if ((m_Edit_Str4.GetLength() > 0) &&(inputstr.Find(m_Edit_Str4, 0) != -1)) {        /* �ַ���4ƥ��ɹ� */
			return TRUE;
		} else if ((m_Edit_Str5.GetLength() > 0) &&(inputstr.Find(m_Edit_Str5, 0) != -1)) {        /* �ַ���5ƥ��ɹ� */
			return TRUE;
		} else {
			return FALSE;
		}
	}

	return TRUE;
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
BOOL CDialogDsplFilt::OnInitDialog()
{	
	CDialog::OnInitDialog();

	return TRUE;
}

/**************************************************************************************************
**  ��������:  OnClose
**  ��������:  ����ر���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogDsplFilt::OnClose()
{
	ShowHideDlgWindow(FALSE);

	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_DFDLGCLOSE, 0, 0);

	CDialog::OnClose();
}

/**************************************************************************************************
**  ��������:  PreTranslateMessage
**  ��������:  Ԥ������Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
BOOL CDialogDsplFilt::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg -> message == WM_KEYDOWN) {

		if (pMsg -> wParam == VK_ESCAPE)
			return true;
		if (pMsg -> wParam == VK_RETURN)
			return true;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


