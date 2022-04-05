#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogAutoReply.h"


IMPLEMENT_DYNAMIC(CDialogAutoReply, CDialog)

CDialogAutoReply::CDialogAutoReply(CWnd* pParent /* =NULL */)
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
**************************************************************************************************/
void CDialogAutoReply::InitiateAllParas(void)
{
	char TempChar[MAX_STR_LEN];
	CString tempstr;

	s_DialogPos_X = (::GetPrivateProfileInt(FLAG_AUTOREPLY, AUTOREPLY_POSTIONX,  0, CONFIGFILENAME));
	s_DialogPos_Y = (::GetPrivateProfileInt(FLAG_AUTOREPLY, AUTOREPLY_POSTIONY,  0, CONFIGFILENAME));

	for (int i = IDC_EDIT_RECVSTR1; i <= IDC_EDIT_RECVSTR8; i++) {             /* ��ʼ�����������ַ��������� */
		tempstr.Format("RX_Str%.2d", i + 1 - IDC_EDIT_RECVSTR1);
		::GetPrivateProfileString(FLAG_AUTOREPLY, tempstr, "", TempChar, MAX_STR_LEN, CONFIGFILENAME);
		tempstr.Format("%s", TempChar);
		SetDlgItemText(i, tempstr);
	}

	for (int i = IDC_EDIT_SENDSTR1; i <= IDC_EDIT_SENDSTR8; i++) {             /* ��ʼ�����������ַ��������� */
		tempstr.Format("TX_Str%.2d", i + 1 - IDC_EDIT_SENDSTR1);
		::GetPrivateProfileString(FLAG_AUTOREPLY, tempstr, "", TempChar, MAX_STR_LEN, CONFIGFILENAME);
		tempstr.Format("%s", TempChar);
		SetDlgItemText(i, tempstr);
	}

	UpdateData(FALSE);                                                         /* ���±༭������ */
}

/**************************************************************************************************
**  ��������:  RecordAllParas
**  ��������:  �����������
**************************************************************************************************/
void CDialogAutoReply::RecordAllParas(void)
{
	CString ParaStr, EditStr;

	if ((s_DialogPos_X < 0) || (s_DialogPos_X > MAX_WIN_POS)) {                /* ��ֹ�߽��쳣 */
		s_DialogPos_X = 0;
	}

	if ((s_DialogPos_Y < 0) || (s_DialogPos_Y > MAX_WIN_POS)) {                /* ��ֹ�߽��쳣 */
		s_DialogPos_Y = 0;
	}

	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString(FLAG_AUTOREPLY, AUTOREPLY_POSTIONX, ParaStr, CONFIGFILENAME);

	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString(FLAG_AUTOREPLY, AUTOREPLY_POSTIONY, ParaStr, CONFIGFILENAME);

	for (int i = IDC_EDIT_RECVSTR1; i <= IDC_EDIT_RECVSTR8; i++) {             /* ������������ַ��������� */
		GetDlgItemText(i, ParaStr);
		EditStr.Format("RX_Str%.2d", i + 1 - IDC_EDIT_RECVSTR1);
		::WritePrivateProfileString(FLAG_AUTOREPLY, EditStr, ParaStr, CONFIGFILENAME);
	}

	for (int i = IDC_EDIT_SENDSTR1; i <= IDC_EDIT_SENDSTR8; i++) {             /* ������������ַ��������� */
		GetDlgItemText(i, ParaStr);
		EditStr.Format("TX_Str%.2d", i + 1 - IDC_EDIT_SENDSTR1);
		::WritePrivateProfileString(FLAG_AUTOREPLY, EditStr, ParaStr, CONFIGFILENAME);
	}
}

/**************************************************************************************************
**  ��������:  GetTotalStringNo
**  ��������:  ��ȡ�ַ����ܹ�����
**************************************************************************************************/
int CDialogAutoReply::GetTotalStringNo(void)
{
	return MAX_STR_NUM;
}

/**************************************************************************************************
**  ��������:  GetRecvString
**  ��������:  ��ȡ��X�������ַ���
**  ���ز���:  û��Ļ����ؿ��ַ���
**************************************************************************************************/
CString CDialogAutoReply::GetRecvString(int index)
{
	return s_RecvStrList[index];
}

/**************************************************************************************************
**  ��������:  GetSendString
**  ��������:  ��ȡ��X�������ַ���
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
**************************************************************************************************/
BOOL CDialogAutoReply::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

/**************************************************************************************************
**  ��������:  OnClose
**  ��������:  ����ر�
**************************************************************************************************/
void CDialogAutoReply::OnClose()
{
	ShowHideDlgWindow(FALSE);

	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_ARDLGCLOSE, 0, 0);

	CDialog::OnClose();
}


