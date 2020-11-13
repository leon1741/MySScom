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
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为模块内部函数 ===================================== */


/**************************************************************************************************
**  函数名称:  ReadandDisplayFile
**  功能描述:  读取并显示文件内容
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogAboutMe::ReadandDisplayFile(bool fileshown)
{
    CFile   myFile;
	CString FileName;
	
	if (fileshown) {						                                   // 设置文件名
		FileName = "功能简要说明.txt";
	} else {
		FileName = "修改升级记录.txt";
	}
	
	if (myFile.Open(FileName, CFile::modeRead) == 0) {

		SetDlgItemText(IDC_EDIT_ABOUT, "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n                      信息文件读取失败，请确认路径正确且文件未处于打开状态！");
		UpdateData(TRUE);

	} else {

		myFile.SeekToBegin();
		
		int nLength = (int)(myFile.GetLength());
		char * TempStr = new char[nLength];							           // 分配空间
		
		myFile.Read(TempStr, nLength);								           // 读取文件内容

        m_Edit_About = TempStr;
        m_Edit_About = m_Edit_About.Left(nLength);
		SetDlgItemText(IDC_EDIT_ABOUT, m_Edit_About);
		
		myFile.Close();												           // 关闭文件
		
		delete []TempStr;											           // 释放空间
	}
	
	GetDlgItem(IDC_STATIC_ABOUT)->SetFocus();
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ================================== 各个控件消息处理--开始 =================================== */


/**************************************************************************************************
**  函数名称:  OnButtonSwitch
**  功能描述:  切换显示内容
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogAboutMe::OnButtonSwitch() 
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

    UpdateData(FALSE);
}

/**************************************************************************************************
**  函数名称:  OnButtonReadOK
**  功能描述:  成功返回
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogAboutMe::OnButtonReadOK() 
{
	OnOK();
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
BOOL CDialogAboutMe::OnInitDialog() 
{
    CDialog::OnInitDialog();
	
    OnButtonSwitch();
	
	return TRUE;
}

