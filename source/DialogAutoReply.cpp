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
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为模块内部函数 ===================================== */

/**************************************************************************************************
**  函数名称:  SetEditControlEnble
**  功能描述:  设置各个编辑框控件的可见性
**************************************************************************************************/
void CDialogAutoReply::SetEditControlEnble(bool enable)
{
	;
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为控件消息处理 ===================================== */

/**************************************************************************************************
**  函数名称:  OnBnClickedButtonClearall
**  功能描述:  清除全部内容重填
**************************************************************************************************/
void CDialogAutoReply::OnBnClickedButtonClearall()
{
	if (MessageBox("确认要将全部内容清空重填？", "提示", MB_OKCANCEL + MB_ICONQUESTION) != IDOK) {
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
**  函数名称:  OnBnClickedButtonSavestr
**  功能描述:  保存所填内容
**************************************************************************************************/
void CDialogAutoReply::OnBnClickedButtonSavestr()
{
	CString tempstr;

	for (int i = IDC_EDIT_RECVSTR1; i <= IDC_EDIT_RECVSTR8; i++) {
		GetDlgItemText(i, tempstr);
		if (ParseCStrisLegal(tempstr) == FALSE) {
			tempstr.Format("第%d项接收字符串格式错误，请重填！", i + 1 - IDC_EDIT_RECVSTR1);
			MessageBox(tempstr, "提示", MB_OK + MB_ICONWARNING);
			return;
		} else {
			s_RecvStrList[i - IDC_EDIT_RECVSTR1] = tempstr;
		}
	}

	for (int i = IDC_EDIT_SENDSTR1; i <= IDC_EDIT_SENDSTR8; i++) {
		GetDlgItemText(i, tempstr);
		if (ParseCStrisLegal(tempstr) == FALSE) {
			tempstr.Format("第%d项应答字符串格式错误，请重填！", i + 1- IDC_EDIT_SENDSTR1);
			MessageBox(tempstr, "提示", MB_OK + MB_ICONWARNING);
			return;
		} else {
			s_SendStrList[i - IDC_EDIT_SENDSTR1] = tempstr;
		}
	}

	OnOK();
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为对外接口函数 ===================================== */

/**************************************************************************************************
**  函数名称:  ShowHideDlgWindow
**  功能描述:  显示和隐藏本窗口，包括读取和存储窗口位置参数
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
**  函数名称:  InitiateAllParas
**  功能描述:  初始化各个参数
**************************************************************************************************/
void CDialogAutoReply::InitiateAllParas(void)
{
	char TempChar[MAX_STR_LEN];
	CString tempstr;

	s_DialogPos_X = (::GetPrivateProfileInt(FLAG_AUTOREPLY, AUTOREPLY_POSTIONX,  0, CONFIGFILENAME));
	s_DialogPos_Y = (::GetPrivateProfileInt(FLAG_AUTOREPLY, AUTOREPLY_POSTIONY,  0, CONFIGFILENAME));

	for (int i = IDC_EDIT_RECVSTR1; i <= IDC_EDIT_RECVSTR8; i++) {             /* 初始化各个接收字符串的内容 */
		tempstr.Format("RX_Str%.2d", i + 1 - IDC_EDIT_RECVSTR1);
		::GetPrivateProfileString(FLAG_AUTOREPLY, tempstr, "", TempChar, MAX_STR_LEN, CONFIGFILENAME);
		tempstr.Format("%s", TempChar);
		SetDlgItemText(i, tempstr);
	}

	for (int i = IDC_EDIT_SENDSTR1; i <= IDC_EDIT_SENDSTR8; i++) {             /* 初始化各个接收字符串的内容 */
		tempstr.Format("TX_Str%.2d", i + 1 - IDC_EDIT_SENDSTR1);
		::GetPrivateProfileString(FLAG_AUTOREPLY, tempstr, "", TempChar, MAX_STR_LEN, CONFIGFILENAME);
		tempstr.Format("%s", TempChar);
		SetDlgItemText(i, tempstr);
	}

	UpdateData(FALSE);                                                         /* 更新编辑框内容 */
}

/**************************************************************************************************
**  函数名称:  RecordAllParas
**  功能描述:  保存各个参数
**************************************************************************************************/
void CDialogAutoReply::RecordAllParas(void)
{
	CString ParaStr, EditStr;

	if ((s_DialogPos_X < 0) || (s_DialogPos_X > MAX_WIN_POS)) {                /* 防止边界异常 */
		s_DialogPos_X = 0;
	}

	if ((s_DialogPos_Y < 0) || (s_DialogPos_Y > MAX_WIN_POS)) {                /* 防止边界异常 */
		s_DialogPos_Y = 0;
	}

	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString(FLAG_AUTOREPLY, AUTOREPLY_POSTIONX, ParaStr, CONFIGFILENAME);

	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString(FLAG_AUTOREPLY, AUTOREPLY_POSTIONY, ParaStr, CONFIGFILENAME);

	for (int i = IDC_EDIT_RECVSTR1; i <= IDC_EDIT_RECVSTR8; i++) {             /* 保存各个接收字符串的内容 */
		GetDlgItemText(i, ParaStr);
		EditStr.Format("RX_Str%.2d", i + 1 - IDC_EDIT_RECVSTR1);
		::WritePrivateProfileString(FLAG_AUTOREPLY, EditStr, ParaStr, CONFIGFILENAME);
	}

	for (int i = IDC_EDIT_SENDSTR1; i <= IDC_EDIT_SENDSTR8; i++) {             /* 保存各个接收字符串的内容 */
		GetDlgItemText(i, ParaStr);
		EditStr.Format("TX_Str%.2d", i + 1 - IDC_EDIT_SENDSTR1);
		::WritePrivateProfileString(FLAG_AUTOREPLY, EditStr, ParaStr, CONFIGFILENAME);
	}
}

/**************************************************************************************************
**  函数名称:  GetTotalStringNo
**  功能描述:  获取字符串总共个数
**************************************************************************************************/
int CDialogAutoReply::GetTotalStringNo(void)
{
	return MAX_STR_NUM;
}

/**************************************************************************************************
**  函数名称:  GetRecvString
**  功能描述:  获取第X个接收字符串
**  返回参数:  没填的话返回空字符串
**************************************************************************************************/
CString CDialogAutoReply::GetRecvString(int index)
{
	return s_RecvStrList[index];
}

/**************************************************************************************************
**  函数名称:  GetSendString
**  功能描述:  获取第X个发送字符串
**  返回参数:  没填的话返回空字符串
**************************************************************************************************/
CString CDialogAutoReply::GetSendString(int index)
{
	return s_SendStrList[index];
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */

/**************************************************************************************************
**  函数名称:  OnInitDialog
**  功能描述:  窗体初始化
**************************************************************************************************/
BOOL CDialogAutoReply::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

/**************************************************************************************************
**  函数名称:  OnClose
**  功能描述:  窗体关闭
**************************************************************************************************/
void CDialogAutoReply::OnClose()
{
	ShowHideDlgWindow(FALSE);

	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_ARDLGCLOSE, 0, 0);

	CDialog::OnClose();
}


