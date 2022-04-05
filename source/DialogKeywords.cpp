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
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== 以下为内部工具函数 ===================================== */



/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== 以下为系统消息函数 ===================================== */

void CDialogKeywords::OnClose()
{
	ShowHideDlgWindow(FALSE);
	RecordAllParas();

	CDialog::OnClose();
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== 以下为控件消息处理 ===================================== */


/**************************************************************************************************
**  函数名称:  OnButtonSaveall
**  功能描述:  保存全部参数并退出
**************************************************************************************************/
void CDialogKeywords::OnButtonSaveall()
{
	CString ParaStr, EditStr;

	for (int i = IDC_EDIT_KEYWORD1; i <= IDC_EDIT_KEYWORD8; i++) {             /* 保存各个接收字符串的内容 */
		GetDlgItemText(i, ParaStr);
		EditStr.Format("Keywrd%.2d", i + 1 - IDC_EDIT_KEYWORD1);
		::WritePrivateProfileString(FLAG_KEYWDMTCH, EditStr, ParaStr, CONFIGFILENAME);
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonExitall
**  功能描述:  放弃全部修改并退出
**************************************************************************************************/
void CDialogKeywords::OnButtonExitall()
{
	char TempChar[MAX_KEYWORD_LEN];
	CString tempstr;

	for (int i = IDC_EDIT_KEYWORD1; i <= IDC_EDIT_KEYWORD8; i++) {             /* 初始化各个接收字符串的内容 */
		tempstr.Format("Keywrd%.2d", i + 1 - IDC_EDIT_KEYWORD1);
		::GetPrivateProfileString(FLAG_KEYWDMTCH, tempstr, "", TempChar, MAX_KEYWORD_LEN, CONFIGFILENAME);
		tempstr.Format("%s", TempChar);
		SetDlgItemText(i, tempstr);
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonClearall
**  功能描述:  清除全部匹配结果的记录
**************************************************************************************************/
void CDialogKeywords::OnButtonClearall()
{
	if (MessageBox("确认要将所接收到的全部内容清空？", "提示", MB_OKCANCEL + MB_ICONQUESTION) != IDOK) {
		return;
	}
	
	m_Edit_MatchRec = "";
	SetDlgItemText(IDC_EDIT_MATCHREC, m_Edit_MatchRec);
}

/**************************************************************************************************
**  函数名称:  OnButtonSavefile
**  功能描述:  将匹配结果的记录保存到文件
**************************************************************************************************/
void CDialogKeywords::OnButtonSavefile()
{
	CFile   MyFile;                                                            /* 定义文件类 */
	CTime   NowTime  = CTime::GetCurrentTime();                                /* 获取现在时间 */
	CString FileName = NowTime.Format("KeyWord_Rec_%y-%m-%d_%H-%M-%S") + ".txt";

	GetDlgItemText(IDC_EDIT_MATCHREC, m_Edit_MatchRec);

	if (m_Edit_MatchRec.GetLength() == 0) {
		MessageBox("尚未接收到任何有效内容，无需保存......", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}

	MyFile.Open(REC_DIR_PATH + FileName, CFile::modeCreate | CFile::modeReadWrite);
	MyFile.Write(m_Edit_MatchRec, m_Edit_MatchRec.GetLength());                /* 写入文本文件 */
	MyFile.Close();                                                            /* 关闭文件 */

	MessageBox("窗口数据已经成功保存至指定文件!      ", "恭喜", MB_OK + MB_ICONINFORMATION);
}

/**************************************************************************************************
**  函数名称:  OnButtonClosewin
**  功能描述:  关闭窗体
**************************************************************************************************/
void CDialogKeywords::OnButtonClosewin()
{
	ShowHideDlgWindow(FALSE);
	RecordAllParas();
	
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
**  函数名称:  InitiateAllParas
**  功能描述:  初始化各个参数
**************************************************************************************************/
void CDialogKeywords::InitiateAllParas(void)
{
	s_DialogPos_X = (::GetPrivateProfileInt(FLAG_KEYWDMTCH, KEYWDMTCH_POSTIONX, 0, CONFIGFILENAME));
	s_DialogPos_Y = (::GetPrivateProfileInt(FLAG_KEYWDMTCH, KEYWDMTCH_POSTIONY, 0, CONFIGFILENAME));

	OnButtonExitall();                                                         /* 读取配置文件并初始化控件 */

	UpdateData(FALSE);                                                         /* 更新编辑框内容 */
}

/**************************************************************************************************
**  函数名称:  RecordAllParas
**  功能描述:  保存各个参数
**************************************************************************************************/
void CDialogKeywords::RecordAllParas(void)
{
	CString ParaStr;

	if ((s_DialogPos_X < 0) || (s_DialogPos_X > MAX_WIN_POS)) {                /* 防止边界异常 */
		s_DialogPos_X = 0;
	}

	if ((s_DialogPos_Y < 0) || (s_DialogPos_Y > MAX_WIN_POS)) {                /* 防止边界异常 */
		s_DialogPos_Y = 0;
	}
	
	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString(FLAG_KEYWDMTCH, KEYWDMTCH_POSTIONX, ParaStr, CONFIGFILENAME);

	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString(FLAG_KEYWDMTCH, KEYWDMTCH_POSTIONY, ParaStr, CONFIGFILENAME);

	OnButtonSaveall();                                                         /* 存储控件内容到配置文件 */
}

/**************************************************************************************************
**  函数名称:  GetKeywordMax
**  功能描述:  获取关键字个数最大值
**************************************************************************************************/
int CDialogKeywords::GetKeywordMax(void)
{
	return MAX_KEYWORD_NUM;
}

/**************************************************************************************************
**  函数名称:  GetKeywordX
**  功能描述:  获取关键字内容
**  输入参数:  index: 1-8
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
**  函数名称:  AddNewMatchRec
**  功能描述:  将匹配成功的信息追加记录下来
**************************************************************************************************/
void CDialogKeywords::AddNewMatchRec(int index)
{
	CTime     NowTime;
	CString   ShowStr, TimeStr;

	NowTime = CTime::GetCurrentTime();                                         /* 获取当前系统时间 */
	TimeStr = NowTime.Format("[%H:%M:%S]");

	ShowStr = TimeStr + " Recv Keyword \"" + GetKeywordX(index) + "\"\r\n";

	m_Edit_MatchRec += ShowStr;
	SetDlgItemText(IDC_EDIT_MATCHREC, m_Edit_MatchRec);

	((CEdit *)GetDlgItem(IDC_EDIT_MATCHREC))->SetSel(-1, -1);
	((CEdit *)GetDlgItem(IDC_EDIT_MATCHREC))->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


