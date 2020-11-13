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
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为模块内部函数 ===================================== */


/**************************************************************************************************
**  函数名称:  FilterEditValid
**  功能描述:  判断过滤字符串编辑框内容是否有效
**  输入参数:  
**  返回参数:  只要有一个内容有效，则返回TRUE。全部都为空，则返回FALSE
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
**  函数名称:  SetEditControlEnble
**  功能描述:  设置各个编辑框控件的可见性
**  输入参数:  
**  返回参数:  
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
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为控件消息处理 ===================================== */


/**************************************************************************************************
**  函数名称:  OnBnClickedRadioOpenmode
**  功能描述:  切换为全开模式
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogDsplFilt::OnBnClickedRadioOpenmode()
{
	m_Radio_FilterMode = _OPEN_MODE;
	SetEditControlEnble(FALSE);
	UpdateData(TRUE);
}

/**************************************************************************************************
**  函数名称:  OnBnClickedRadioFiltmode
**  功能描述:  切换为过滤模式
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogDsplFilt::OnBnClickedRadioFiltmode()
{
	m_Radio_FilterMode = _FILT_MODE;
	SetEditControlEnble(TRUE);
	UpdateData(TRUE);
}

/**************************************************************************************************
**  函数名称:  OnBnClickedRadioDsplmode
**  功能描述:  切换为匹配模式
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogDsplFilt::OnBnClickedRadioDsplmode()
{
	m_Radio_FilterMode = _MATH_MODE;
	SetEditControlEnble(TRUE);
	UpdateData(TRUE);
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
**  输入参数:  
**  返回参数:  
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
**  函数名称:  InitiateAllParas
**  功能描述:  初始化各个参数
**  输入参数:  
**  返回参数:  
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

	UpdateData(FALSE);                                                         /* 更新编辑框内容 */
}

/**************************************************************************************************
**  函数名称:  RecordAllParas
**  功能描述:  保存各个参数
**  输入参数:  
**  返回参数:  
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
**  函数名称:  StringCanDisplay
**  功能描述:  对过滤字符串进行匹配，并返回匹配结果
**  输入参数:  
**  返回参数:  需要显示，返回TRUE；不需要显示，返回FALSE
**************************************************************************************************/
bool CDialogDsplFilt::StringCanDisplay(CString inputstr)
{
	if (m_Radio_FilterMode == _OPEN_MODE) {                                    /* 没有开启过滤功能时，全部可以显示 */
		return TRUE;
	}

	GetDlgItemText(IDC_EDIT_STR1, m_Edit_Str1);
	GetDlgItemText(IDC_EDIT_STR2, m_Edit_Str2);
	GetDlgItemText(IDC_EDIT_STR3, m_Edit_Str3);
	GetDlgItemText(IDC_EDIT_STR4, m_Edit_Str4);
	GetDlgItemText(IDC_EDIT_STR5, m_Edit_Str5);

	if (m_Radio_FilterMode == _FILT_MODE) {                                    /* 过滤模式下，过滤掉符合条件的字符串 */

		if (FilterEditValid() == FALSE) {                                      /* 没有输入任何过滤串，意味着全部都显示 */
			return TRUE;
		}

		if ((m_Edit_Str1.GetLength() > 0) &&(inputstr.Find(m_Edit_Str1, 0) != -1)) {               /* 字符串1匹配成功 */
			return FALSE;
		} else if ((m_Edit_Str2.GetLength() > 0) &&(inputstr.Find(m_Edit_Str2, 0) != -1)) {        /* 字符串2匹配成功 */
			return FALSE;
		} else if ((m_Edit_Str3.GetLength() > 0) &&(inputstr.Find(m_Edit_Str3, 0) != -1)) {        /* 字符串3匹配成功 */
			return FALSE;
		} else if ((m_Edit_Str4.GetLength() > 0) &&(inputstr.Find(m_Edit_Str4, 0) != -1)) {        /* 字符串4匹配成功 */
			return FALSE;
		} else if ((m_Edit_Str5.GetLength() > 0) &&(inputstr.Find(m_Edit_Str5, 0) != -1)) {        /* 字符串5匹配成功 */
			return FALSE;
		} else {
			return TRUE;
		}
	}

	if (m_Radio_FilterMode == _MATH_MODE) {                                    /* 匹配模式下，只有符合条件的字符串才通过 */
		
		if (FilterEditValid() == FALSE) {                                      /* 没有输入任何匹配串，意味着全部不显示 */
			return FALSE;
		}

		if ((m_Edit_Str1.GetLength() > 0) &&(inputstr.Find(m_Edit_Str1, 0) != -1)) {               /* 字符串1匹配成功 */
			return TRUE;
		} else if ((m_Edit_Str2.GetLength() > 0) &&(inputstr.Find(m_Edit_Str2, 0) != -1)) {        /* 字符串2匹配成功 */
			return TRUE;
		} else if ((m_Edit_Str3.GetLength() > 0) &&(inputstr.Find(m_Edit_Str3, 0) != -1)) {        /* 字符串3匹配成功 */
			return TRUE;
		} else if ((m_Edit_Str4.GetLength() > 0) &&(inputstr.Find(m_Edit_Str4, 0) != -1)) {        /* 字符串4匹配成功 */
			return TRUE;
		} else if ((m_Edit_Str5.GetLength() > 0) &&(inputstr.Find(m_Edit_Str5, 0) != -1)) {        /* 字符串5匹配成功 */
			return TRUE;
		} else {
			return FALSE;
		}
	}

	return TRUE;
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */

/**************************************************************************************************
**  函数名称:  OnInitDialog
**  功能描述:  初始化
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
BOOL CDialogDsplFilt::OnInitDialog()
{	
	CDialog::OnInitDialog();

	return TRUE;
}

/**************************************************************************************************
**  函数名称:  OnClose
**  功能描述:  窗体关闭消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogDsplFilt::OnClose()
{
	ShowHideDlgWindow(FALSE);

	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_DFDLGCLOSE, 0, 0);

	CDialog::OnClose();
}

/**************************************************************************************************
**  函数名称:  PreTranslateMessage
**  功能描述:  预处理消息
**  输入参数:  
**  返回参数:  
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


