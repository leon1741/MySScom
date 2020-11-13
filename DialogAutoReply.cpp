#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogAutoReply.h"


IMPLEMENT_DYNAMIC(CDialogAutoReply, CDialog)

CDialogAutoReply::CDialogAutoReply(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAutoReply::IDD, pParent)
{

}

CDialogAutoReply::~CDialogAutoReply()
{
}

void CDialogAutoReply::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDialogAutoReply, CWnd)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CLEARALL, &CDialogAutoReply::OnBnClickedButtonClearall)
	ON_BN_CLICKED(IDC_BUTTON_SAVESTR, &CDialogAutoReply::OnBnClickedButtonSavestr)
END_MESSAGE_MAP()


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊģ���ڲ����� ===================================== */

/**************************************************************************************************
**  ��������:  SetEditControlEnble
**  ��������:  ���ø����༭��ؼ��Ŀɼ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogAutoReply::SetEditControlEnble(bool enable)
{
	;
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊ�ؼ���Ϣ���� ===================================== */

/**************************************************************************************************
**  ��������:  OnBnClickedButtonClearall
**  ��������:  ���ȫ����������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogAutoReply::OnBnClickedButtonClearall()
{
	if (MessageBox("ȷ��Ҫ��ȫ������������", "��ʾ", MB_OKCANCEL + MB_ICONQUESTION) != IDOK) {
		return;
	}

	for (int i = IDC_EDIT_RECVSTR1; i <= IDC_EDIT_RECVSTR8; i++) {
		SetDlgItemText(i, "");
	}

	for (int i = IDC_EDIT_SENDSTR1; i <= IDC_EDIT_SENDSTR8; i++) {
		SetDlgItemText(i, "");
	}

	UpdateData(TRUE);
}

/**************************************************************************************************
**  ��������:  OnBnClickedButtonSavestr
**  ��������:  ������������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogAutoReply::OnBnClickedButtonSavestr()
{
	CString tempstr;

	for (int i = IDC_EDIT_RECVSTR1; i <= IDC_EDIT_RECVSTR8; i++) {
		GetDlgItemText(i, tempstr);
		if (ParseCStrisLegal(tempstr) == FALSE) {
			tempstr.Format("��%d������ַ�����ʽ���������", i + 1 - IDC_EDIT_RECVSTR1);
			MessageBox(tempstr, "��ʾ", MB_OK + MB_ICONWARNING);
			return;
		} else {
			s_RecvStrList[i - IDC_EDIT_RECVSTR1] = tempstr;
		}
	}

	for (int i = IDC_EDIT_SENDSTR1; i <= IDC_EDIT_SENDSTR8; i++) {
		GetDlgItemText(i, tempstr);
		if (ParseCStrisLegal(tempstr) == FALSE) {
			tempstr.Format("��%d��Ӧ���ַ�����ʽ���������", i + 1- IDC_EDIT_SENDSTR1);
			MessageBox(tempstr, "��ʾ", MB_OK + MB_ICONWARNING);
			return;
		} else {
			s_SendStrList[i - IDC_EDIT_SENDSTR1] = tempstr;
		}
	}

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
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogAutoReply::ShowHideDlgWindow(bool show)
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
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogAutoReply::InitiateAllParas(void)
{
	char TempChar[MAX_STR_LEN];
	CString tempstr;

	s_DialogPos_X = (::GetPrivateProfileInt("AutoRply", "DialogPos_X",  0, ".\\Settings.ini"));
	s_DialogPos_Y = (::GetPrivateProfileInt("AutoRply", "DialogPos_Y",  0, ".\\Settings.ini"));

	for (int i = IDC_EDIT_RECVSTR1; i <= IDC_EDIT_RECVSTR8; i++) {             /* ��ʼ��8�������ַ��������� */
		tempstr.Format("RecvStr%.2d", i + 1 - IDC_EDIT_RECVSTR1);
		::GetPrivateProfileString("AutoRply", tempstr, "", TempChar, MAX_STR_LEN, ".\\Settings.ini");
		tempstr.Format("%s", TempChar);
		SetDlgItemText(i, tempstr);
	}

	for (int i = IDC_EDIT_SENDSTR1; i <= IDC_EDIT_SENDSTR8; i++) {             /* ��ʼ��8�������ַ��������� */
		tempstr.Format("SendStr%.2d", i + 1 - IDC_EDIT_SENDSTR1);
		::GetPrivateProfileString("AutoRply", tempstr, "", TempChar, MAX_STR_LEN, ".\\Settings.ini");
		tempstr.Format("%s", TempChar);
		SetDlgItemText(i, tempstr);
	}

	UpdateData(FALSE);                                                         /* ���±༭������ */
}

/**************************************************************************************************
**  ��������:  RecordAllParas
**  ��������:  �����������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogAutoReply::RecordAllParas(void)
{
	CString ParaStr, EditStr;

	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString("AutoRply", "DialogPos_X", ParaStr, ".\\Settings.ini");

	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString("AutoRply", "DialogPos_Y", ParaStr, ".\\Settings.ini");

	for (int i = IDC_EDIT_RECVSTR1; i <= IDC_EDIT_RECVSTR8; i++) {             /* ����8�������ַ��������� */
		GetDlgItemText(i, ParaStr);
		EditStr.Format("RecvStr%.2d", i + 1 - IDC_EDIT_RECVSTR1);
		::WritePrivateProfileString("AutoRply", EditStr, ParaStr, ".\\Settings.ini");
	}

	for (int i = IDC_EDIT_SENDSTR1; i <= IDC_EDIT_SENDSTR8; i++) {             /* ����8�������ַ��������� */
		GetDlgItemText(i, ParaStr);
		EditStr.Format("SendStr%.2d", i + 1 - IDC_EDIT_SENDSTR1);
		::WritePrivateProfileString("AutoRply", EditStr, ParaStr, ".\\Settings.ini");
	}
}

/**************************************************************************************************
**  ��������:  GetTotalStringNo
**  ��������:  ��ȡ�ַ����ܹ�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
int CDialogAutoReply::GetTotalStringNo(void)
{
	return MAX_STR_NUM;
}

/**************************************************************************************************
**  ��������:  GetRecvString
**  ��������:  ��ȡ��X�������ַ���
**  �������:  
**  ���ز���:  û��Ļ����ؿ��ַ���
**************************************************************************************************/
CString CDialogAutoReply::GetRecvString(int index)
{
	return s_RecvStrList[index];
}

/**************************************************************************************************
**  ��������:  GetSendString
**  ��������:  ��ȡ��X�������ַ���
**  �������:  
**  ���ز���:  û��Ļ����ؿ��ַ���
**************************************************************************************************/
CString CDialogAutoReply::GetSendString(int index)
{
	return s_SendStrList[index];
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */

/**************************************************************************************************
**  ��������:  OnInitDialog
**  ��������:  �����ʼ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
BOOL CDialogAutoReply::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

/**************************************************************************************************
**  ��������:  OnClose
**  ��������:  ����ر�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogAutoReply::OnClose()
{
	ShowHideDlgWindow(FALSE);

	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_ARDLGCLOSE, 0, 0);

	CDialog::OnClose();
}


