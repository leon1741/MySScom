// DialogSrSend.cpp : implementation file
//

#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogSrSend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSrSend dialog


CDialogSrSend::CDialogSrSend(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSrSend::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSrSend)
	m_Check_01 = FALSE;
	m_Check_02 = FALSE;
	m_Check_03 = FALSE;
	m_Check_04 = FALSE;
	m_Check_05 = FALSE;
	m_Check_06 = FALSE;
	m_Check_07 = FALSE;
	m_Check_08 = FALSE;
	m_Check_09 = FALSE;
	m_Check_10 = FALSE;
	m_Check_11 = FALSE;
	m_Check_12 = FALSE;
	m_Check_13 = FALSE;
	m_Check_14 = FALSE;
	m_Check_15 = FALSE;
	m_Check_16 = FALSE;
	m_Check_17 = FALSE;
	m_Check_18 = FALSE;
	m_Check_19 = FALSE;
	m_Check_20 = FALSE;
	m_Check_21 = FALSE;
	m_Check_22 = FALSE;
	m_Check_23 = FALSE;
	m_Check_24 = FALSE;
	m_Check_25 = FALSE;
	m_Check_26 = FALSE;
	m_Check_27 = FALSE;
	m_Check_28 = FALSE;
	m_Check_29 = FALSE;
	m_Check_30 = FALSE;
	m_Check_31 = FALSE;
	m_Check_32 = FALSE;
	m_Check_33 = FALSE;
	m_Check_34 = FALSE;
	m_Check_35 = FALSE;
	m_Check_36 = FALSE;
	m_Check_37 = FALSE;
	m_Check_38 = FALSE;
	m_Check_39 = FALSE;
	m_Check_40 = FALSE;
	m_Edit_T01 = _T("");
	m_Edit_T02 = _T("");
	m_Edit_T03 = _T("");
	m_Edit_T04 = _T("");
	m_Edit_T05 = _T("");
	m_Edit_T06 = _T("");
	m_Edit_T07 = _T("");
	m_Edit_T08 = _T("");
	m_Edit_T09 = _T("");
	m_Edit_T10 = _T("");
	m_Edit_T11 = _T("");
	m_Edit_T12 = _T("");
	m_Edit_T13 = _T("");
	m_Edit_T14 = _T("");
	m_Edit_T15 = _T("");
	m_Edit_T16 = _T("");
	m_Edit_T17 = _T("");
	m_Edit_T18 = _T("");
	m_Edit_T19 = _T("");
	m_Edit_T20 = _T("");
	m_Edit_T21 = _T("");
	m_Edit_T22 = _T("");
	m_Edit_T23 = _T("");
	m_Edit_T24 = _T("");
	m_Edit_T25 = _T("");
	m_Edit_T26 = _T("");
	m_Edit_T27 = _T("");
	m_Edit_T28 = _T("");
	m_Edit_T29 = _T("");
	m_Edit_T30 = _T("");
	m_Edit_T31 = _T("");
	m_Edit_T32 = _T("");
	m_Edit_T33 = _T("");
	m_Edit_T34 = _T("");
	m_Edit_T35 = _T("");
	m_Edit_T36 = _T("");
	m_Edit_T37 = _T("");
	m_Edit_T38 = _T("");
	m_Edit_T39 = _T("");
	m_Edit_T40 = _T("");
	m_Radio_SendAll = -1;
	//}}AFX_DATA_INIT
}


void CDialogSrSend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSrSend)
	DDX_Check(pDX, IDC_CHECK_01, m_Check_01);
	DDX_Check(pDX, IDC_CHECK_02, m_Check_02);
	DDX_Check(pDX, IDC_CHECK_03, m_Check_03);
	DDX_Check(pDX, IDC_CHECK_04, m_Check_04);
	DDX_Check(pDX, IDC_CHECK_05, m_Check_05);
	DDX_Check(pDX, IDC_CHECK_06, m_Check_06);
	DDX_Check(pDX, IDC_CHECK_07, m_Check_07);
	DDX_Check(pDX, IDC_CHECK_08, m_Check_08);
	DDX_Check(pDX, IDC_CHECK_09, m_Check_09);
	DDX_Check(pDX, IDC_CHECK_10, m_Check_10);
	DDX_Check(pDX, IDC_CHECK_11, m_Check_11);
	DDX_Check(pDX, IDC_CHECK_12, m_Check_12);
	DDX_Check(pDX, IDC_CHECK_13, m_Check_13);
	DDX_Check(pDX, IDC_CHECK_14, m_Check_14);
	DDX_Check(pDX, IDC_CHECK_15, m_Check_15);
	DDX_Check(pDX, IDC_CHECK_16, m_Check_16);
	DDX_Check(pDX, IDC_CHECK_17, m_Check_17);
	DDX_Check(pDX, IDC_CHECK_18, m_Check_18);
	DDX_Check(pDX, IDC_CHECK_19, m_Check_19);
	DDX_Check(pDX, IDC_CHECK_20, m_Check_20);
	DDX_Check(pDX, IDC_CHECK_21, m_Check_21);
	DDX_Check(pDX, IDC_CHECK_22, m_Check_22);
	DDX_Check(pDX, IDC_CHECK_23, m_Check_23);
	DDX_Check(pDX, IDC_CHECK_24, m_Check_24);
	DDX_Check(pDX, IDC_CHECK_25, m_Check_25);
	DDX_Check(pDX, IDC_CHECK_26, m_Check_26);
	DDX_Check(pDX, IDC_CHECK_27, m_Check_27);
	DDX_Check(pDX, IDC_CHECK_28, m_Check_28);
	DDX_Check(pDX, IDC_CHECK_29, m_Check_29);
	DDX_Check(pDX, IDC_CHECK_30, m_Check_30);
	DDX_Check(pDX, IDC_CHECK_31, m_Check_31);
	DDX_Check(pDX, IDC_CHECK_32, m_Check_32);
	DDX_Check(pDX, IDC_CHECK_33, m_Check_33);
	DDX_Check(pDX, IDC_CHECK_34, m_Check_34);
	DDX_Check(pDX, IDC_CHECK_35, m_Check_35);
	DDX_Check(pDX, IDC_CHECK_36, m_Check_36);
	DDX_Check(pDX, IDC_CHECK_37, m_Check_37);
	DDX_Check(pDX, IDC_CHECK_38, m_Check_38);
	DDX_Check(pDX, IDC_CHECK_39, m_Check_39);
	DDX_Check(pDX, IDC_CHECK_40, m_Check_40);
	DDX_Text(pDX, IDC_EDIT_AUTOTIME, m_Edit_AutoTime);
	DDV_MaxChars(pDX, m_Edit_AutoTime, 5);
	DDX_Text(pDX, IDC_EDIT_T01, m_Edit_T01);
	DDV_MaxChars(pDX, m_Edit_T01, 5);
	DDX_Text(pDX, IDC_EDIT_T02, m_Edit_T02);
	DDV_MaxChars(pDX, m_Edit_T02, 5);
	DDX_Text(pDX, IDC_EDIT_T03, m_Edit_T03);
	DDV_MaxChars(pDX, m_Edit_T03, 5);
	DDX_Text(pDX, IDC_EDIT_T04, m_Edit_T04);
	DDV_MaxChars(pDX, m_Edit_T04, 5);
	DDX_Text(pDX, IDC_EDIT_T05, m_Edit_T05);
	DDV_MaxChars(pDX, m_Edit_T05, 5);
	DDX_Text(pDX, IDC_EDIT_T06, m_Edit_T06);
	DDV_MaxChars(pDX, m_Edit_T06, 5);
	DDX_Text(pDX, IDC_EDIT_T07, m_Edit_T07);
	DDV_MaxChars(pDX, m_Edit_T07, 5);
	DDX_Text(pDX, IDC_EDIT_T08, m_Edit_T08);
	DDV_MaxChars(pDX, m_Edit_T08, 5);
	DDX_Text(pDX, IDC_EDIT_T09, m_Edit_T09);
	DDV_MaxChars(pDX, m_Edit_T09, 5);
	DDX_Text(pDX, IDC_EDIT_T10, m_Edit_T10);
	DDV_MaxChars(pDX, m_Edit_T10, 5);
	DDX_Text(pDX, IDC_EDIT_T11, m_Edit_T11);
	DDV_MaxChars(pDX, m_Edit_T11, 5);
	DDX_Text(pDX, IDC_EDIT_T12, m_Edit_T12);
	DDV_MaxChars(pDX, m_Edit_T12, 5);
	DDX_Text(pDX, IDC_EDIT_T13, m_Edit_T13);
	DDV_MaxChars(pDX, m_Edit_T13, 5);
	DDX_Text(pDX, IDC_EDIT_T14, m_Edit_T14);
	DDV_MaxChars(pDX, m_Edit_T14, 5);
	DDX_Text(pDX, IDC_EDIT_T15, m_Edit_T15);
	DDV_MaxChars(pDX, m_Edit_T15, 5);
	DDX_Text(pDX, IDC_EDIT_T16, m_Edit_T16);
	DDV_MaxChars(pDX, m_Edit_T16, 5);
	DDX_Text(pDX, IDC_EDIT_T17, m_Edit_T17);
	DDV_MaxChars(pDX, m_Edit_T17, 5);
	DDX_Text(pDX, IDC_EDIT_T18, m_Edit_T18);
	DDV_MaxChars(pDX, m_Edit_T18, 5);
	DDX_Text(pDX, IDC_EDIT_T19, m_Edit_T19);
	DDV_MaxChars(pDX, m_Edit_T19, 5);
	DDX_Text(pDX, IDC_EDIT_T20, m_Edit_T20);
	DDV_MaxChars(pDX, m_Edit_T20, 5);
	DDX_Text(pDX, IDC_EDIT_T21, m_Edit_T21);
	DDV_MaxChars(pDX, m_Edit_T21, 5);
	DDX_Text(pDX, IDC_EDIT_T22, m_Edit_T22);
	DDV_MaxChars(pDX, m_Edit_T22, 5);
	DDX_Text(pDX, IDC_EDIT_T23, m_Edit_T23);
	DDV_MaxChars(pDX, m_Edit_T23, 5);
	DDX_Text(pDX, IDC_EDIT_T24, m_Edit_T24);
	DDV_MaxChars(pDX, m_Edit_T24, 5);
	DDX_Text(pDX, IDC_EDIT_T25, m_Edit_T25);
	DDV_MaxChars(pDX, m_Edit_T25, 5);
	DDX_Text(pDX, IDC_EDIT_T26, m_Edit_T26);
	DDV_MaxChars(pDX, m_Edit_T26, 5);
	DDX_Text(pDX, IDC_EDIT_T27, m_Edit_T27);
	DDV_MaxChars(pDX, m_Edit_T27, 5);
	DDX_Text(pDX, IDC_EDIT_T28, m_Edit_T28);
	DDV_MaxChars(pDX, m_Edit_T28, 5);
	DDX_Text(pDX, IDC_EDIT_T29, m_Edit_T29);
	DDV_MaxChars(pDX, m_Edit_T29, 5);
	DDX_Text(pDX, IDC_EDIT_T30, m_Edit_T30);
	DDV_MaxChars(pDX, m_Edit_T30, 5);
	DDX_Text(pDX, IDC_EDIT_T31, m_Edit_T31);
	DDV_MaxChars(pDX, m_Edit_T31, 5);
	DDX_Text(pDX, IDC_EDIT_T32, m_Edit_T32);
	DDV_MaxChars(pDX, m_Edit_T32, 5);
	DDX_Text(pDX, IDC_EDIT_T33, m_Edit_T33);
	DDV_MaxChars(pDX, m_Edit_T33, 5);
	DDX_Text(pDX, IDC_EDIT_T34, m_Edit_T34);
	DDV_MaxChars(pDX, m_Edit_T34, 5);
	DDX_Text(pDX, IDC_EDIT_T35, m_Edit_T35);
	DDV_MaxChars(pDX, m_Edit_T35, 5);
	DDX_Text(pDX, IDC_EDIT_T36, m_Edit_T36);
	DDV_MaxChars(pDX, m_Edit_T36, 5);
	DDX_Text(pDX, IDC_EDIT_T37, m_Edit_T37);
	DDV_MaxChars(pDX, m_Edit_T37, 5);
	DDX_Text(pDX, IDC_EDIT_T38, m_Edit_T38);
	DDV_MaxChars(pDX, m_Edit_T38, 5);
	DDX_Text(pDX, IDC_EDIT_T39, m_Edit_T39);
	DDV_MaxChars(pDX, m_Edit_T39, 5);
	DDX_Text(pDX, IDC_EDIT_T40, m_Edit_T40);
	DDV_MaxChars(pDX, m_Edit_T40, 5);
	DDX_Radio(pDX, IDC_RADIO_SENDALL, m_Radio_SendAll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSrSend, CDialog)
	//{{AFX_MSG_MAP(CDialogSrSend)
	ON_BN_CLICKED(IDC_BUTTON_EXPAND, OnButtonExpand)
	ON_BN_CLICKED(IDC_BUTTON_SEND01, OnButtonSend01)
	ON_BN_CLICKED(IDC_BUTTON_SEND02, OnButtonSend02)
	ON_BN_CLICKED(IDC_BUTTON_SEND03, OnButtonSend03)
	ON_BN_CLICKED(IDC_BUTTON_SEND04, OnButtonSend04)
	ON_BN_CLICKED(IDC_BUTTON_SEND05, OnButtonSend05)
	ON_BN_CLICKED(IDC_BUTTON_SEND06, OnButtonSend06)
	ON_BN_CLICKED(IDC_BUTTON_SEND07, OnButtonSend07)
	ON_BN_CLICKED(IDC_BUTTON_SEND08, OnButtonSend08)
	ON_BN_CLICKED(IDC_BUTTON_SEND09, OnButtonSend09)
	ON_BN_CLICKED(IDC_BUTTON_SEND10, OnButtonSend10)
	ON_BN_CLICKED(IDC_BUTTON_SEND11, OnButtonSend11)
	ON_BN_CLICKED(IDC_BUTTON_SEND12, OnButtonSend12)
	ON_BN_CLICKED(IDC_BUTTON_SEND13, OnButtonSend13)
	ON_BN_CLICKED(IDC_BUTTON_SEND14, OnButtonSend14)
	ON_BN_CLICKED(IDC_BUTTON_SEND15, OnButtonSend15)
	ON_BN_CLICKED(IDC_BUTTON_SEND16, OnButtonSend16)
	ON_BN_CLICKED(IDC_BUTTON_SEND17, OnButtonSend17)
	ON_BN_CLICKED(IDC_BUTTON_SEND18, OnButtonSend18)
	ON_BN_CLICKED(IDC_BUTTON_SEND19, OnButtonSend19)
	ON_BN_CLICKED(IDC_BUTTON_SEND20, OnButtonSend20)
	ON_BN_CLICKED(IDC_BUTTON_SEND21, OnButtonSend21)
	ON_BN_CLICKED(IDC_BUTTON_SEND22, OnButtonSend22)
	ON_BN_CLICKED(IDC_BUTTON_SEND23, OnButtonSend23)
	ON_BN_CLICKED(IDC_BUTTON_SEND24, OnButtonSend24)
	ON_BN_CLICKED(IDC_BUTTON_SEND25, OnButtonSend25)
	ON_BN_CLICKED(IDC_BUTTON_SEND26, OnButtonSend26)
	ON_BN_CLICKED(IDC_BUTTON_SEND27, OnButtonSend27)
	ON_BN_CLICKED(IDC_BUTTON_SEND28, OnButtonSend28)
	ON_BN_CLICKED(IDC_BUTTON_SEND29, OnButtonSend29)
	ON_BN_CLICKED(IDC_BUTTON_SEND30, OnButtonSend30)
	ON_BN_CLICKED(IDC_BUTTON_SEND31, OnButtonSend31)
	ON_BN_CLICKED(IDC_BUTTON_SEND32, OnButtonSend32)
	ON_BN_CLICKED(IDC_BUTTON_SEND33, OnButtonSend33)
	ON_BN_CLICKED(IDC_BUTTON_SEND34, OnButtonSend34)
	ON_BN_CLICKED(IDC_BUTTON_SEND35, OnButtonSend35)
	ON_BN_CLICKED(IDC_BUTTON_SEND36, OnButtonSend36)
	ON_BN_CLICKED(IDC_BUTTON_SEND37, OnButtonSend37)
	ON_BN_CLICKED(IDC_BUTTON_SEND38, OnButtonSend38)
	ON_BN_CLICKED(IDC_BUTTON_SEND39, OnButtonSend39)
	ON_BN_CLICKED(IDC_BUTTON_SEND40, OnButtonSend40)
	ON_BN_CLICKED(IDC_CHECK_01, OnCheck01)
	ON_BN_CLICKED(IDC_CHECK_02, OnCheck02)
	ON_BN_CLICKED(IDC_CHECK_03, OnCheck03)
	ON_BN_CLICKED(IDC_CHECK_04, OnCheck04)
	ON_BN_CLICKED(IDC_CHECK_05, OnCheck05)
	ON_BN_CLICKED(IDC_CHECK_06, OnCheck06)
	ON_BN_CLICKED(IDC_CHECK_07, OnCheck07)
	ON_BN_CLICKED(IDC_CHECK_08, OnCheck08)
	ON_BN_CLICKED(IDC_CHECK_09, OnCheck09)
	ON_BN_CLICKED(IDC_CHECK_10, OnCheck10)
	ON_BN_CLICKED(IDC_CHECK_11, OnCheck11)
	ON_BN_CLICKED(IDC_CHECK_12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK_13, OnCheck13)
	ON_BN_CLICKED(IDC_CHECK_14, OnCheck14)
	ON_BN_CLICKED(IDC_CHECK_15, OnCheck15)
	ON_BN_CLICKED(IDC_CHECK_16, OnCheck16)
	ON_BN_CLICKED(IDC_CHECK_17, OnCheck17)
	ON_BN_CLICKED(IDC_CHECK_18, OnCheck18)
	ON_BN_CLICKED(IDC_CHECK_19, OnCheck19)
	ON_BN_CLICKED(IDC_CHECK_20, OnCheck20)
	ON_BN_CLICKED(IDC_CHECK_21, OnCheck21)
	ON_BN_CLICKED(IDC_CHECK_22, OnCheck22)
	ON_BN_CLICKED(IDC_CHECK_23, OnCheck23)
	ON_BN_CLICKED(IDC_CHECK_24, OnCheck24)
	ON_BN_CLICKED(IDC_CHECK_25, OnCheck25)
	ON_BN_CLICKED(IDC_CHECK_26, OnCheck26)
	ON_BN_CLICKED(IDC_CHECK_27, OnCheck27)
	ON_BN_CLICKED(IDC_CHECK_28, OnCheck28)
	ON_BN_CLICKED(IDC_CHECK_29, OnCheck29)
	ON_BN_CLICKED(IDC_CHECK_30, OnCheck30)
	ON_BN_CLICKED(IDC_CHECK_31, OnCheck31)
	ON_BN_CLICKED(IDC_CHECK_32, OnCheck32)
	ON_BN_CLICKED(IDC_CHECK_33, OnCheck33)
	ON_BN_CLICKED(IDC_CHECK_34, OnCheck34)
	ON_BN_CLICKED(IDC_CHECK_35, OnCheck35)
	ON_BN_CLICKED(IDC_CHECK_36, OnCheck36)
	ON_BN_CLICKED(IDC_CHECK_37, OnCheck37)
	ON_BN_CLICKED(IDC_CHECK_38, OnCheck38)
	ON_BN_CLICKED(IDC_CHECK_39, OnCheck39)
	ON_BN_CLICKED(IDC_CHECK_40, OnCheck40)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_SENDALL, OnRadioSendAll)
	ON_BN_CLICKED(IDC_RADIO_SENDEACH, OnRadioSendEach)
	ON_BN_CLICKED(IDC_BUTTON_STARTSEND, OnButtonStartSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为内部工具函数 ===================================== */


/**************************************************************************************************
**  函数名称:  EditDataValid
**  功能描述:  判断edit控件内的数据是否有效
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CDialogSrSend::EditDataValid(int EditID)
{
	CString TempStr;
	
	GetDlgItemText(EditID, TempStr);
	
	if (TempStr.GetLength() > 0) {                                             // 判断编辑框内容的长度是否有效
		return TRUE;
	} else {
		return FALSE;
	}
}

/**************************************************************************************************
**  函数名称:  EditDataTimeValid
**  功能描述:  判断edit控件内的数据以及发送时间间隔是否有效
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CDialogSrSend::EditDataTimeValid(int EditID, int TimeID)
{
	int     timeint;
	CString TempStr;
	
	GetDlgItemText(EditID, TempStr);
	if (TempStr.GetLength() == 0) {                                            // 判断编辑框内容的长度是否有效
		return FALSE;
	}

	GetDlgItemText(TimeID, TempStr);
	if (TempStr.GetLength() == 0) {                                            // 判断编辑框内容的长度是否有效
		return FALSE;
	}
	
	timeint = atoi((LPSTR)(LPCTSTR)TempStr);
	if (timeint == 0) {                                                        // 时间间隔不能为0
		return FALSE;
	}

	return TRUE;
}

/**************************************************************************************************
**  函数名称:  CanSendEditData
**  功能描述:  判断是否可以发送数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CDialogSrSend::CanSendEditData(int editno, int TimeID)
{
	int     timeint;
	CString TempStr;
	
	GetDlgItemText(TimeID, TempStr);	
	timeint = atoi((LPSTR)(LPCTSTR)TempStr);

	if (++s_sendcnt[editno] >= (timeint / 10)) {                               // 时间到点
		s_sendcnt[editno] = 0;
		return TRUE;
	} else {
		return FALSE;
	}
}

/**************************************************************************************************
**  函数名称:  GetSrValidDataNo
**  功能描述:  获取高级发送区内edit控件内数据有效的控件ID
**  输入参数:  
**  返回参数:  返回内容有效的编辑框的序号，全无效则返回0
**************************************************************************************************/
int CDialogSrSend::GetSrValidDataNo(void)
{
	if (s_expandmode == FALSE) {                                               // 非扩展发送模式下，只判断左边20条
		if (EditDataValid(IDC_EDIT_01) == TRUE) {
			return IDC_EDIT_01;
		} else if (EditDataValid(IDC_EDIT_02) == TRUE) {
			return IDC_EDIT_02;
		} else if (EditDataValid(IDC_EDIT_03) == TRUE) {
			return IDC_EDIT_03;
		} else if (EditDataValid(IDC_EDIT_04) == TRUE) {
			return IDC_EDIT_04;
		} else if (EditDataValid(IDC_EDIT_05) == TRUE) {
			return IDC_EDIT_05;
		} else if (EditDataValid(IDC_EDIT_06) == TRUE) {
			return IDC_EDIT_06;
		} else if (EditDataValid(IDC_EDIT_07) == TRUE) {
			return IDC_EDIT_07;
		} else if (EditDataValid(IDC_EDIT_08) == TRUE) {
			return IDC_EDIT_08;
		} else if (EditDataValid(IDC_EDIT_09) == TRUE) {
			return IDC_EDIT_09;
		} else if (EditDataValid(IDC_EDIT_10) == TRUE) {
			return IDC_EDIT_10;
		} else if (EditDataValid(IDC_EDIT_11) == TRUE) {
			return IDC_EDIT_11;
		} else if (EditDataValid(IDC_EDIT_12) == TRUE) {
			return IDC_EDIT_12;
		} else if (EditDataValid(IDC_EDIT_13) == TRUE) {
			return IDC_EDIT_13;
		} else if (EditDataValid(IDC_EDIT_14) == TRUE) {
			return IDC_EDIT_14;
		} else if (EditDataValid(IDC_EDIT_15) == TRUE) {
			return IDC_EDIT_15;
		} else if (EditDataValid(IDC_EDIT_16) == TRUE) {
			return IDC_EDIT_16;
		} else if (EditDataValid(IDC_EDIT_17) == TRUE) {
			return IDC_EDIT_17;
		} else if (EditDataValid(IDC_EDIT_18) == TRUE) {
			return IDC_EDIT_18;
		} else if (EditDataValid(IDC_EDIT_19) == TRUE) {
			return IDC_EDIT_19;
		} else if (EditDataValid(IDC_EDIT_20) == TRUE) {
			return IDC_EDIT_20;
		} else {
			return 0;
		}
	} else {                                                                   // 扩展发送模式下，判断全部40条
		if (EditDataValid(IDC_EDIT_01) == TRUE) {
			return IDC_EDIT_01;
		} else if (EditDataValid(IDC_EDIT_02) == TRUE) {
			return IDC_EDIT_02;
		} else if (EditDataValid(IDC_EDIT_03) == TRUE) {
			return IDC_EDIT_03;
		} else if (EditDataValid(IDC_EDIT_04) == TRUE) {
			return IDC_EDIT_04;
		} else if (EditDataValid(IDC_EDIT_05) == TRUE) {
			return IDC_EDIT_05;
		} else if (EditDataValid(IDC_EDIT_06) == TRUE) {
			return IDC_EDIT_06;
		} else if (EditDataValid(IDC_EDIT_07) == TRUE) {
			return IDC_EDIT_07;
		} else if (EditDataValid(IDC_EDIT_08) == TRUE) {
			return IDC_EDIT_08;
		} else if (EditDataValid(IDC_EDIT_09) == TRUE) {
			return IDC_EDIT_09;
		} else if (EditDataValid(IDC_EDIT_10) == TRUE) {
			return IDC_EDIT_10;
		} else if (EditDataValid(IDC_EDIT_11) == TRUE) {
			return IDC_EDIT_11;
		} else if (EditDataValid(IDC_EDIT_12) == TRUE) {
			return IDC_EDIT_12;
		} else if (EditDataValid(IDC_EDIT_13) == TRUE) {
			return IDC_EDIT_13;
		} else if (EditDataValid(IDC_EDIT_14) == TRUE) {
			return IDC_EDIT_14;
		} else if (EditDataValid(IDC_EDIT_15) == TRUE) {
			return IDC_EDIT_15;
		} else if (EditDataValid(IDC_EDIT_16) == TRUE) {
			return IDC_EDIT_16;
		} else if (EditDataValid(IDC_EDIT_17) == TRUE) {
			return IDC_EDIT_17;
		} else if (EditDataValid(IDC_EDIT_18) == TRUE) {
			return IDC_EDIT_18;
		} else if (EditDataValid(IDC_EDIT_19) == TRUE) {
			return IDC_EDIT_19;
		} else if (EditDataValid(IDC_EDIT_20) == TRUE) {
			return IDC_EDIT_20;
		} else if (EditDataValid(IDC_EDIT_21) == TRUE) {
			return IDC_EDIT_21;
		} else if (EditDataValid(IDC_EDIT_22) == TRUE) {
			return IDC_EDIT_22;
		} else if (EditDataValid(IDC_EDIT_23) == TRUE) {
			return IDC_EDIT_23;
		} else if (EditDataValid(IDC_EDIT_24) == TRUE) {
			return IDC_EDIT_24;
		} else if (EditDataValid(IDC_EDIT_25) == TRUE) {
			return IDC_EDIT_25;
		} else if (EditDataValid(IDC_EDIT_26) == TRUE) {
			return IDC_EDIT_26;
		} else if (EditDataValid(IDC_EDIT_27) == TRUE) {
			return IDC_EDIT_27;
		} else if (EditDataValid(IDC_EDIT_28) == TRUE) {
			return IDC_EDIT_28;
		} else if (EditDataValid(IDC_EDIT_29) == TRUE) {
			return IDC_EDIT_29;
		} else if (EditDataValid(IDC_EDIT_30) == TRUE) {
			return IDC_EDIT_30;
		} else if (EditDataValid(IDC_EDIT_31) == TRUE) {
			return IDC_EDIT_31;
		} else if (EditDataValid(IDC_EDIT_32) == TRUE) {
			return IDC_EDIT_32;
		} else if (EditDataValid(IDC_EDIT_33) == TRUE) {
			return IDC_EDIT_33;
		} else if (EditDataValid(IDC_EDIT_34) == TRUE) {
			return IDC_EDIT_34;
		} else if (EditDataValid(IDC_EDIT_35) == TRUE) {
			return IDC_EDIT_35;
		} else if (EditDataValid(IDC_EDIT_36) == TRUE) {
			return IDC_EDIT_36;
		} else if (EditDataValid(IDC_EDIT_37) == TRUE) {
			return IDC_EDIT_37;
		} else if (EditDataValid(IDC_EDIT_38) == TRUE) {
			return IDC_EDIT_38;
		} else if (EditDataValid(IDC_EDIT_39) == TRUE) {
			return IDC_EDIT_39;
		} else if (EditDataValid(IDC_EDIT_40) == TRUE) {
			return IDC_EDIT_40;
		} else {
			return 0;
		}
	}
}

/**************************************************************************************************
**  函数名称:  TrytoSendData
**  功能描述:  尝试发送数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogSrSend::TrytoSendData(CString InputStr, BOOL NeedHex)
{	
	CMySScomDlg *pDlg;
	
	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;
	
	if (InputStr.GetLength() <= 0) {
		MessageBox("发送窗口内容为空，未发送任何数据！  ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	if ((pDlg->SendDatatoComm(InputStr, NeedHex)) == FALSE) {                  // 如果发送失败，提示

		MessageBox("您输入的数据帧内容过长，或者存在非法字符，请确认！......       ", "提醒", MB_OK + MB_ICONEXCLAMATION);

		if (s_issenddata == TRUE) {                                            // 如果处于连发模式，则停止连发
			OnButtonStartSend();
		}
	}
}

/**************************************************************************************************
**  函数名称:  TrytoContinueSend
**  功能描述:  尝试继续连发数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogSrSend::TrytoContinueSend(void)
{
	if (s_expandmode == FALSE) {                                               // 非扩展发送模式下，只判断左边20条

		if ((s_curdatacnt < IDC_EDIT_01) && (EditDataValid(IDC_EDIT_01) == TRUE)) {		
			OnButtonSend01();
			s_curdatacnt = IDC_EDIT_01;
		} else if ((s_curdatacnt < IDC_EDIT_02) && (EditDataValid(IDC_EDIT_02) == TRUE)) {
			OnButtonSend02();
			s_curdatacnt = IDC_EDIT_02;
		} else if ((s_curdatacnt < IDC_EDIT_03) && (EditDataValid(IDC_EDIT_03) == TRUE)) {
			OnButtonSend03();
			s_curdatacnt = IDC_EDIT_03;
		} else if ((s_curdatacnt < IDC_EDIT_04) && (EditDataValid(IDC_EDIT_04) == TRUE)) {
			OnButtonSend04();
			s_curdatacnt = IDC_EDIT_04;
		} else if ((s_curdatacnt < IDC_EDIT_05) && (EditDataValid(IDC_EDIT_05) == TRUE)) {
			OnButtonSend05();
			s_curdatacnt = IDC_EDIT_05;
		} else if ((s_curdatacnt < IDC_EDIT_06) && (EditDataValid(IDC_EDIT_06) == TRUE)) {
			OnButtonSend06();
			s_curdatacnt = IDC_EDIT_06;
		} else if ((s_curdatacnt < IDC_EDIT_07) && (EditDataValid(IDC_EDIT_07) == TRUE)) {
			OnButtonSend07();
			s_curdatacnt = IDC_EDIT_07;
		} else if ((s_curdatacnt < IDC_EDIT_08) && (EditDataValid(IDC_EDIT_08) == TRUE)) {
			OnButtonSend08();
			s_curdatacnt = IDC_EDIT_08;
		} else if ((s_curdatacnt < IDC_EDIT_09) && (EditDataValid(IDC_EDIT_09) == TRUE)) {
			OnButtonSend09();
			s_curdatacnt = IDC_EDIT_09;
		} else if ((s_curdatacnt < IDC_EDIT_10) && (EditDataValid(IDC_EDIT_10) == TRUE)) {
			OnButtonSend10();
			s_curdatacnt = IDC_EDIT_10;
		} else if ((s_curdatacnt < IDC_EDIT_11) && (EditDataValid(IDC_EDIT_11) == TRUE)) {
			OnButtonSend11();
			s_curdatacnt = IDC_EDIT_11;
		} else if ((s_curdatacnt < IDC_EDIT_12) && (EditDataValid(IDC_EDIT_12) == TRUE)) {
			OnButtonSend12();
			s_curdatacnt = IDC_EDIT_12;
		} else if ((s_curdatacnt < IDC_EDIT_13) && (EditDataValid(IDC_EDIT_13) == TRUE)) {
			OnButtonSend13();
			s_curdatacnt = IDC_EDIT_13;
		} else if ((s_curdatacnt < IDC_EDIT_14) && (EditDataValid(IDC_EDIT_14) == TRUE)) {
			OnButtonSend14();
			s_curdatacnt = IDC_EDIT_14;
		} else if ((s_curdatacnt < IDC_EDIT_15) && (EditDataValid(IDC_EDIT_15) == TRUE)) {
			OnButtonSend15();
			s_curdatacnt = IDC_EDIT_15;
		} else if ((s_curdatacnt < IDC_EDIT_16) && (EditDataValid(IDC_EDIT_16) == TRUE)) {
			OnButtonSend16();
			s_curdatacnt = IDC_EDIT_16;
		} else if ((s_curdatacnt < IDC_EDIT_17) && (EditDataValid(IDC_EDIT_17) == TRUE)) {
			OnButtonSend17();
			s_curdatacnt = IDC_EDIT_17;
		} else if ((s_curdatacnt < IDC_EDIT_18) && (EditDataValid(IDC_EDIT_18) == TRUE)) {
			OnButtonSend18();
			s_curdatacnt = IDC_EDIT_18;
		} else if ((s_curdatacnt < IDC_EDIT_19) && (EditDataValid(IDC_EDIT_19) == TRUE)) {
			OnButtonSend19();
			s_curdatacnt = IDC_EDIT_19;
		} else if ((s_curdatacnt < IDC_EDIT_20) && (EditDataValid(IDC_EDIT_20) == TRUE)) {
			OnButtonSend20();
			s_curdatacnt = IDC_EDIT_20;
		} else {
			s_curdatacnt = 0;
		}
	} else {                                                                   // 扩展发送模式下，判断全部40条

		if ((s_curdatacnt < IDC_EDIT_01) && (EditDataValid(IDC_EDIT_01) == TRUE)) {		
			OnButtonSend01();
			s_curdatacnt = IDC_EDIT_01;
		} else if ((s_curdatacnt < IDC_EDIT_02) && (EditDataValid(IDC_EDIT_02) == TRUE)) {
			OnButtonSend02();
			s_curdatacnt = IDC_EDIT_02;
		} else if ((s_curdatacnt < IDC_EDIT_03) && (EditDataValid(IDC_EDIT_03) == TRUE)) {
			OnButtonSend03();
			s_curdatacnt = IDC_EDIT_03;
		} else if ((s_curdatacnt < IDC_EDIT_04) && (EditDataValid(IDC_EDIT_04) == TRUE)) {
			OnButtonSend04();
			s_curdatacnt = IDC_EDIT_04;
		} else if ((s_curdatacnt < IDC_EDIT_05) && (EditDataValid(IDC_EDIT_05) == TRUE)) {
			OnButtonSend05();
			s_curdatacnt = IDC_EDIT_05;
		} else if ((s_curdatacnt < IDC_EDIT_06) && (EditDataValid(IDC_EDIT_06) == TRUE)) {
			OnButtonSend06();
			s_curdatacnt = IDC_EDIT_06;
		} else if ((s_curdatacnt < IDC_EDIT_07) && (EditDataValid(IDC_EDIT_07) == TRUE)) {
			OnButtonSend07();
			s_curdatacnt = IDC_EDIT_07;
		} else if ((s_curdatacnt < IDC_EDIT_08) && (EditDataValid(IDC_EDIT_08) == TRUE)) {
			OnButtonSend08();
			s_curdatacnt = IDC_EDIT_08;
		} else if ((s_curdatacnt < IDC_EDIT_09) && (EditDataValid(IDC_EDIT_09) == TRUE)) {
			OnButtonSend09();
			s_curdatacnt = IDC_EDIT_09;
		} else if ((s_curdatacnt < IDC_EDIT_10) && (EditDataValid(IDC_EDIT_10) == TRUE)) {
			OnButtonSend10();
			s_curdatacnt = IDC_EDIT_10;
		} else if ((s_curdatacnt < IDC_EDIT_11) && (EditDataValid(IDC_EDIT_11) == TRUE)) {
			OnButtonSend11();
			s_curdatacnt = IDC_EDIT_11;
		} else if ((s_curdatacnt < IDC_EDIT_12) && (EditDataValid(IDC_EDIT_12) == TRUE)) {
			OnButtonSend12();
			s_curdatacnt = IDC_EDIT_12;
		} else if ((s_curdatacnt < IDC_EDIT_13) && (EditDataValid(IDC_EDIT_13) == TRUE)) {
			OnButtonSend13();
			s_curdatacnt = IDC_EDIT_13;
		} else if ((s_curdatacnt < IDC_EDIT_14) && (EditDataValid(IDC_EDIT_14) == TRUE)) {
			OnButtonSend14();
			s_curdatacnt = IDC_EDIT_14;
		} else if ((s_curdatacnt < IDC_EDIT_15) && (EditDataValid(IDC_EDIT_15) == TRUE)) {
			OnButtonSend15();
			s_curdatacnt = IDC_EDIT_15;
		} else if ((s_curdatacnt < IDC_EDIT_16) && (EditDataValid(IDC_EDIT_16) == TRUE)) {
			OnButtonSend16();
			s_curdatacnt = IDC_EDIT_16;
		} else if ((s_curdatacnt < IDC_EDIT_17) && (EditDataValid(IDC_EDIT_17) == TRUE)) {
			OnButtonSend17();
			s_curdatacnt = IDC_EDIT_17;
		} else if ((s_curdatacnt < IDC_EDIT_18) && (EditDataValid(IDC_EDIT_18) == TRUE)) {
			OnButtonSend18();
			s_curdatacnt = IDC_EDIT_18;
		} else if ((s_curdatacnt < IDC_EDIT_19) && (EditDataValid(IDC_EDIT_19) == TRUE)) {
			OnButtonSend19();
			s_curdatacnt = IDC_EDIT_19;
		} else if ((s_curdatacnt < IDC_EDIT_20) && (EditDataValid(IDC_EDIT_20) == TRUE)) {
			OnButtonSend20();
			s_curdatacnt = IDC_EDIT_20;
		} else if ((s_curdatacnt < IDC_EDIT_21) && (EditDataValid(IDC_EDIT_21) == TRUE)) {		
			OnButtonSend21();
			s_curdatacnt = IDC_EDIT_21;
		} else if ((s_curdatacnt < IDC_EDIT_22) && (EditDataValid(IDC_EDIT_22) == TRUE)) {
			OnButtonSend22();
			s_curdatacnt = IDC_EDIT_22;
		} else if ((s_curdatacnt < IDC_EDIT_23) && (EditDataValid(IDC_EDIT_23) == TRUE)) {
			OnButtonSend23();
			s_curdatacnt = IDC_EDIT_23;
		} else if ((s_curdatacnt < IDC_EDIT_24) && (EditDataValid(IDC_EDIT_24) == TRUE)) {
			OnButtonSend24();
			s_curdatacnt = IDC_EDIT_24;
		} else if ((s_curdatacnt < IDC_EDIT_25) && (EditDataValid(IDC_EDIT_25) == TRUE)) {
			OnButtonSend25();
			s_curdatacnt = IDC_EDIT_25;
		} else if ((s_curdatacnt < IDC_EDIT_26) && (EditDataValid(IDC_EDIT_26) == TRUE)) {
			OnButtonSend26();
			s_curdatacnt = IDC_EDIT_26;
		} else if ((s_curdatacnt < IDC_EDIT_27) && (EditDataValid(IDC_EDIT_27) == TRUE)) {
			OnButtonSend27();
			s_curdatacnt = IDC_EDIT_27;
		} else if ((s_curdatacnt < IDC_EDIT_28) && (EditDataValid(IDC_EDIT_28) == TRUE)) {
			OnButtonSend28();
			s_curdatacnt = IDC_EDIT_28;
		} else if ((s_curdatacnt < IDC_EDIT_29) && (EditDataValid(IDC_EDIT_29) == TRUE)) {
			OnButtonSend29();
			s_curdatacnt = IDC_EDIT_29;
		} else if ((s_curdatacnt < IDC_EDIT_30) && (EditDataValid(IDC_EDIT_30) == TRUE)) {
			OnButtonSend30();
			s_curdatacnt = IDC_EDIT_30;
		} else if ((s_curdatacnt < IDC_EDIT_31) && (EditDataValid(IDC_EDIT_31) == TRUE)) {
			OnButtonSend31();
			s_curdatacnt = IDC_EDIT_31;
		} else if ((s_curdatacnt < IDC_EDIT_32) && (EditDataValid(IDC_EDIT_32) == TRUE)) {
			OnButtonSend32();
			s_curdatacnt = IDC_EDIT_32;
		} else if ((s_curdatacnt < IDC_EDIT_33) && (EditDataValid(IDC_EDIT_33) == TRUE)) {
			OnButtonSend33();
			s_curdatacnt = IDC_EDIT_33;
		} else if ((s_curdatacnt < IDC_EDIT_34) && (EditDataValid(IDC_EDIT_34) == TRUE)) {
			OnButtonSend34();
			s_curdatacnt = IDC_EDIT_34;
		} else if ((s_curdatacnt < IDC_EDIT_35) && (EditDataValid(IDC_EDIT_35) == TRUE)) {
			OnButtonSend35();
			s_curdatacnt = IDC_EDIT_35;
		} else if ((s_curdatacnt < IDC_EDIT_36) && (EditDataValid(IDC_EDIT_36) == TRUE)) {
			OnButtonSend36();
			s_curdatacnt = IDC_EDIT_36;
		} else if ((s_curdatacnt < IDC_EDIT_37) && (EditDataValid(IDC_EDIT_37) == TRUE)) {
			OnButtonSend37();
			s_curdatacnt = IDC_EDIT_37;
		} else if ((s_curdatacnt < IDC_EDIT_38) && (EditDataValid(IDC_EDIT_38) == TRUE)) {
			OnButtonSend38();
			s_curdatacnt = IDC_EDIT_38;
		} else if ((s_curdatacnt < IDC_EDIT_39) && (EditDataValid(IDC_EDIT_39) == TRUE)) {
			OnButtonSend39();
			s_curdatacnt = IDC_EDIT_39;
		} else if ((s_curdatacnt < IDC_EDIT_40) && (EditDataValid(IDC_EDIT_40) == TRUE)) {
			OnButtonSend40();
			s_curdatacnt = IDC_EDIT_40;
		} else {
			s_curdatacnt = 0;
		}
	}
}

/**************************************************************************************************
**  函数名称:  TrytoSendEachData
**  功能描述:  尝试连发单条数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogSrSend::TrytoSendEachData(void)
{
    if (s_expandmode == FALSE) {                                               // 非扩展发送模式下，只判断左边20条

		if (EditDataTimeValid(IDC_EDIT_01, IDC_EDIT_T01) == TRUE) {
			if (CanSendEditData(0, IDC_EDIT_T01) == TRUE) {
				OnButtonSend01();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_02, IDC_EDIT_T02) == TRUE) {
			if (CanSendEditData(1, IDC_EDIT_T02) == TRUE) {
				OnButtonSend02();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_03, IDC_EDIT_T03) == TRUE) {
			if (CanSendEditData(2, IDC_EDIT_T03) == TRUE) {
				OnButtonSend03();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_04, IDC_EDIT_T04) == TRUE) {
			if (CanSendEditData(3, IDC_EDIT_T04) == TRUE) {
				OnButtonSend04();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_05, IDC_EDIT_T05) == TRUE) {
			if (CanSendEditData(4, IDC_EDIT_T05) == TRUE) {
				OnButtonSend05();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_06, IDC_EDIT_T06) == TRUE) {
			if (CanSendEditData(5, IDC_EDIT_T06) == TRUE) {
				OnButtonSend06();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_07, IDC_EDIT_T07) == TRUE) {
			if (CanSendEditData(6, IDC_EDIT_T07) == TRUE) {
				OnButtonSend07();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_08, IDC_EDIT_T08) == TRUE) {
			if (CanSendEditData(7, IDC_EDIT_T08) == TRUE) {
				OnButtonSend08();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_09, IDC_EDIT_T09) == TRUE) {
			if (CanSendEditData(8, IDC_EDIT_T09) == TRUE) {
				OnButtonSend09();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_10, IDC_EDIT_T10) == TRUE) {
			if (CanSendEditData(9, IDC_EDIT_T10) == TRUE) {
				OnButtonSend10();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_11, IDC_EDIT_T11) == TRUE) {
			if (CanSendEditData(10, IDC_EDIT_T11) == TRUE) {
				OnButtonSend11();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_12, IDC_EDIT_T12) == TRUE) {
			if (CanSendEditData(11, IDC_EDIT_T12) == TRUE) {
				OnButtonSend12();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_13, IDC_EDIT_T13) == TRUE) {
			if (CanSendEditData(12, IDC_EDIT_T13) == TRUE) {
				OnButtonSend13();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_14, IDC_EDIT_T14) == TRUE) {
			if (CanSendEditData(13, IDC_EDIT_T14) == TRUE) {
				OnButtonSend14();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_15, IDC_EDIT_T15) == TRUE) {
			if (CanSendEditData(14, IDC_EDIT_T15) == TRUE) {
				OnButtonSend15();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_16, IDC_EDIT_T16) == TRUE) {
			if (CanSendEditData(15, IDC_EDIT_T16) == TRUE) {
				OnButtonSend16();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_17, IDC_EDIT_T17) == TRUE) {
			if (CanSendEditData(16, IDC_EDIT_T17) == TRUE) {
				OnButtonSend17();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_18, IDC_EDIT_T18) == TRUE) {
			if (CanSendEditData(17, IDC_EDIT_T18) == TRUE) {
				OnButtonSend18();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_19, IDC_EDIT_T19) == TRUE) {
			if (CanSendEditData(18, IDC_EDIT_T19) == TRUE) {
				OnButtonSend19();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_20, IDC_EDIT_T20) == TRUE) {
			if (CanSendEditData(19, IDC_EDIT_T20) == TRUE) {
				OnButtonSend20();
			}
		}

	} else {                                                                   // 扩展发送模式下，判断全部40条

		if (EditDataTimeValid(IDC_EDIT_01, IDC_EDIT_T01) == TRUE) {
			if (CanSendEditData(0, IDC_EDIT_T01) == TRUE) {
				OnButtonSend01();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_02, IDC_EDIT_T02) == TRUE) {
			if (CanSendEditData(1, IDC_EDIT_T02) == TRUE) {
				OnButtonSend02();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_03, IDC_EDIT_T03) == TRUE) {
			if (CanSendEditData(2, IDC_EDIT_T03) == TRUE) {
				OnButtonSend03();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_04, IDC_EDIT_T04) == TRUE) {
			if (CanSendEditData(3, IDC_EDIT_T04) == TRUE) {
				OnButtonSend04();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_05, IDC_EDIT_T05) == TRUE) {
			if (CanSendEditData(4, IDC_EDIT_T05) == TRUE) {
				OnButtonSend05();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_06, IDC_EDIT_T06) == TRUE) {
			if (CanSendEditData(5, IDC_EDIT_T06) == TRUE) {
				OnButtonSend06();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_07, IDC_EDIT_T07) == TRUE) {
			if (CanSendEditData(6, IDC_EDIT_T07) == TRUE) {
				OnButtonSend07();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_08, IDC_EDIT_T08) == TRUE) {
			if (CanSendEditData(7, IDC_EDIT_T08) == TRUE) {
				OnButtonSend08();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_09, IDC_EDIT_T09) == TRUE) {
			if (CanSendEditData(8, IDC_EDIT_T09) == TRUE) {
				OnButtonSend09();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_10, IDC_EDIT_T10) == TRUE) {
			if (CanSendEditData(9, IDC_EDIT_T10) == TRUE) {
				OnButtonSend10();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_11, IDC_EDIT_T11) == TRUE) {
			if (CanSendEditData(10, IDC_EDIT_T11) == TRUE) {
				OnButtonSend11();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_12, IDC_EDIT_T12) == TRUE) {
			if (CanSendEditData(11, IDC_EDIT_T12) == TRUE) {
				OnButtonSend12();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_13, IDC_EDIT_T13) == TRUE) {
			if (CanSendEditData(12, IDC_EDIT_T13) == TRUE) {
				OnButtonSend13();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_14, IDC_EDIT_T14) == TRUE) {
			if (CanSendEditData(13, IDC_EDIT_T14) == TRUE) {
				OnButtonSend14();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_15, IDC_EDIT_T15) == TRUE) {
			if (CanSendEditData(14, IDC_EDIT_T15) == TRUE) {
				OnButtonSend15();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_16, IDC_EDIT_T16) == TRUE) {
			if (CanSendEditData(15, IDC_EDIT_T16) == TRUE) {
				OnButtonSend16();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_17, IDC_EDIT_T17) == TRUE) {
			if (CanSendEditData(16, IDC_EDIT_T17) == TRUE) {
				OnButtonSend17();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_18, IDC_EDIT_T18) == TRUE) {
			if (CanSendEditData(17, IDC_EDIT_T18) == TRUE) {
				OnButtonSend18();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_19, IDC_EDIT_T19) == TRUE) {
			if (CanSendEditData(18, IDC_EDIT_T19) == TRUE) {
				OnButtonSend19();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_20, IDC_EDIT_T20) == TRUE) {
			if (CanSendEditData(19, IDC_EDIT_T20) == TRUE) {
				OnButtonSend20();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_21, IDC_EDIT_T21) == TRUE) {		
			if (CanSendEditData(20, IDC_EDIT_T21) == TRUE) {
				OnButtonSend21();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_22, IDC_EDIT_T22) == TRUE) {
			if (CanSendEditData(21, IDC_EDIT_T22) == TRUE) {
				OnButtonSend22();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_23, IDC_EDIT_T23) == TRUE) {
			if (CanSendEditData(22, IDC_EDIT_T23) == TRUE) {
				OnButtonSend23();
			}
		}
		
		if (EditDataTimeValid(IDC_EDIT_24, IDC_EDIT_T24) == TRUE) {
			if (CanSendEditData(23, IDC_EDIT_T24) == TRUE) {
				OnButtonSend24();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_25, IDC_EDIT_T25) == TRUE) {
			if (CanSendEditData(24, IDC_EDIT_T25) == TRUE) {
				OnButtonSend25();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_26, IDC_EDIT_T26) == TRUE) {
			if (CanSendEditData(25, IDC_EDIT_T26) == TRUE) {
				OnButtonSend26();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_27, IDC_EDIT_T27) == TRUE) {
			if (CanSendEditData(26, IDC_EDIT_T27) == TRUE) {
				OnButtonSend27();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_28, IDC_EDIT_T28) == TRUE) {
			if (CanSendEditData(27, IDC_EDIT_T28) == TRUE) {
				OnButtonSend28();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_29, IDC_EDIT_T29) == TRUE) {
			if (CanSendEditData(28, IDC_EDIT_T29) == TRUE) {
				OnButtonSend29();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_30, IDC_EDIT_T30) == TRUE) {
			if (CanSendEditData(29, IDC_EDIT_T30) == TRUE) {
				OnButtonSend30();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_31, IDC_EDIT_T31) == TRUE) {
			if (CanSendEditData(30, IDC_EDIT_T31) == TRUE) {
				OnButtonSend31();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_32, IDC_EDIT_T32) == TRUE) {
			if (CanSendEditData(31, IDC_EDIT_T32) == TRUE) {
				OnButtonSend32();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_33, IDC_EDIT_T33) == TRUE) {
			if (CanSendEditData(32, IDC_EDIT_T33) == TRUE) {
				OnButtonSend33();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_34, IDC_EDIT_T34) == TRUE) {
			if (CanSendEditData(33, IDC_EDIT_T34) == TRUE) {
				OnButtonSend34();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_35, IDC_EDIT_T35) == TRUE) {
			if (CanSendEditData(34, IDC_EDIT_T35) == TRUE) {
				OnButtonSend35();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_36, IDC_EDIT_T36) == TRUE) {
			if (CanSendEditData(35, IDC_EDIT_T36) == TRUE) {
				OnButtonSend36();
			}
		}

		if (EditDataTimeValid(IDC_EDIT_37, IDC_EDIT_T37) == TRUE) {
			if (CanSendEditData(36, IDC_EDIT_T37) == TRUE) {
				OnButtonSend37();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_38, IDC_EDIT_T38) == TRUE) {
			if (CanSendEditData(37, IDC_EDIT_T38) == TRUE) {
				OnButtonSend38();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_39, IDC_EDIT_T39) == TRUE) {
			if (CanSendEditData(38, IDC_EDIT_T39) == TRUE) {
				OnButtonSend39();
			}
		} 
		
		if (EditDataTimeValid(IDC_EDIT_40, IDC_EDIT_T40) == TRUE) {
			if (CanSendEditData(39, IDC_EDIT_T40) == TRUE) {
				OnButtonSend40();
			}
		}
	}
}

/**************************************************************************************************
**  函数名称:  ShowHideTimeEdit
**  功能描述:  显示或隐藏时间编辑框
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogSrSend::ShowHideTimeEdit(bool enanble)
{
	GetDlgItem(IDC_EDIT_T01)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T02)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T03)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T04)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T05)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T06)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T07)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T08)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T09)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T10)->EnableWindow(enanble);

	GetDlgItem(IDC_EDIT_T11)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T12)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T13)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T14)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T15)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T16)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T17)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T18)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T19)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T20)->EnableWindow(enanble);

	GetDlgItem(IDC_EDIT_T21)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T22)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T23)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T24)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T25)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T26)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T27)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T28)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T29)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T30)->EnableWindow(enanble);

	GetDlgItem(IDC_EDIT_T31)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T32)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T33)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T34)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T35)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T36)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T37)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T38)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T39)->EnableWindow(enanble);
	GetDlgItem(IDC_EDIT_T40)->EnableWindow(enanble);

	GetDlgItem(IDC_EDIT_AUTOTIME)->EnableWindow(!enanble);
}

/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为控件消息处理 ===================================== */


void CDialogSrSend::OnButtonStartSend() 
{
	int     Timer;
	CString TempStr;
	
	if (s_issenddata == FALSE) {                                               // 如果当前没有在发送数据
		s_issenddata = TRUE;
		SetDlgItemText(IDC_BUTTON_STARTSEND, "停止发送");

		if (GetSrValidDataNo() == 0) {                                         // 判断数据区是否有效
			MessageBox("貌似您尚未输入任何需要的发送的内容，叫我发送什么呢？~~~  ", "提示", MB_OK + MB_ICONINFORMATION);
			UpdateData(FALSE);                                                 // 取消复选框被选中的状态
			return;
		}

		if (s_cirsendall == TRUE) {                                            // 全部数据统一连发

			GetDlgItemText(IDC_EDIT_AUTOTIME, TempStr);
			Timer = atoi((LPSTR)(LPCTSTR)TempStr);
			
			if ((Timer > 0) && (Timer <= 10000)) {                             // 时间合法
				
				SetTimer(Timer_No_SrAllSend, Timer, NULL);                     // 启动定时器
				s_curdatacnt = 0;
				
				GetDlgItem(IDC_RADIO_SENDALL)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDIT_AUTOTIME)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_SENDEACH)->EnableWindow(FALSE);
				
			} else {
				
				MessageBox("定时时间必须在0至10秒钟之间，请确认！  ", "提示", MB_OK + MB_ICONEXCLAMATION);
				SetDlgItemText(IDC_EDIT_AUTOTIME, m_Edit_AutoTime);            // 还原编辑框内容
				UpdateData(FALSE);                                             // 取消复选框被选中的状态
				return;
			}
		} else {                                                               // 单条数据各自连发

			SetTimer(Timer_No_SrEachSend, 10, NULL);                           // 启动定时器
			memset(s_sendcnt, 0, sizeof(s_sendcnt));
			
			GetDlgItem(IDC_RADIO_SENDALL)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_AUTOTIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_SENDEACH)->EnableWindow(FALSE);
		}
		
	} else {                                                                   // 如果当前正在发送数据
		s_issenddata = FALSE;
		SetDlgItemText(IDC_BUTTON_STARTSEND, "开始发送");

		if (s_cirsendall == TRUE) {                                            // 关闭定时器，取消自动发送功能
			KillTimer(Timer_No_SrAllSend);
		} else {
			KillTimer(Timer_No_SrEachSend);
		}
		
		GetDlgItem(IDC_RADIO_SENDALL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_AUTOTIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_SENDEACH)->EnableWindow(TRUE);
	}
}

void CDialogSrSend::OnButtonExpand() 
{
	CRect rect;
	
	GetWindowRect(&rect);

	if (s_expandmode == TRUE) {
		SetWindowPos(NULL, 0, 0, rect.Width() / 2, rect.Height(), SWP_NOMOVE);
		SetDlgItemText(IDC_BUTTON_EXPAND, ">> 扩展至40条数据 >>");
		s_expandmode = FALSE;
	} else {
		SetWindowPos(NULL, 0, 0, rect.Width() * 2, rect.Height(), SWP_NOMOVE);
		SetDlgItemText(IDC_BUTTON_EXPAND, "<< 精简至20条数据 <<");
		s_expandmode = TRUE;
	}
}

void CDialogSrSend::OnRadioSendAll() 
{
	s_cirsendall = TRUE;
	ShowHideTimeEdit(!s_cirsendall);
}

void CDialogSrSend::OnRadioSendEach() 
{
	s_cirsendall = FALSE;
	ShowHideTimeEdit(!s_cirsendall);
}

/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为发送按钮处理 ===================================== */


void CDialogSrSend::OnButtonSend01() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_01, TempStr);
	
	TrytoSendData(TempStr, m_Check_01);
}

void CDialogSrSend::OnButtonSend02() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_02, TempStr);
	
	TrytoSendData(TempStr, m_Check_02);
}

void CDialogSrSend::OnButtonSend03() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_03, TempStr);
	
	TrytoSendData(TempStr, m_Check_03);
}

void CDialogSrSend::OnButtonSend04() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_04, TempStr);
	
	TrytoSendData(TempStr, m_Check_04);
}

void CDialogSrSend::OnButtonSend05() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_05, TempStr);
	
	TrytoSendData(TempStr, m_Check_05);
}

void CDialogSrSend::OnButtonSend06() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_06, TempStr);
	
	TrytoSendData(TempStr, m_Check_06);
}

void CDialogSrSend::OnButtonSend07() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_07, TempStr);
	
	TrytoSendData(TempStr, m_Check_07);
}

void CDialogSrSend::OnButtonSend08() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_08, TempStr);
	
	TrytoSendData(TempStr, m_Check_08);
}

void CDialogSrSend::OnButtonSend09() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_09, TempStr);
	
	TrytoSendData(TempStr, m_Check_09);
}

void CDialogSrSend::OnButtonSend10() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_10, TempStr);
	
	TrytoSendData(TempStr, m_Check_10);
}

void CDialogSrSend::OnButtonSend11() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_11, TempStr);
	
	TrytoSendData(TempStr, m_Check_11);
}

void CDialogSrSend::OnButtonSend12() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_12, TempStr);
	
	TrytoSendData(TempStr, m_Check_12);
}

void CDialogSrSend::OnButtonSend13() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_13, TempStr);
	
	TrytoSendData(TempStr, m_Check_13);
}

void CDialogSrSend::OnButtonSend14() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_14, TempStr);
	
	TrytoSendData(TempStr, m_Check_14);
}

void CDialogSrSend::OnButtonSend15() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_15, TempStr);
	
	TrytoSendData(TempStr, m_Check_15);
}

void CDialogSrSend::OnButtonSend16() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_16, TempStr);
	
	TrytoSendData(TempStr, m_Check_16);
}

void CDialogSrSend::OnButtonSend17() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_17, TempStr);
	
	TrytoSendData(TempStr, m_Check_17);
}

void CDialogSrSend::OnButtonSend18() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_18, TempStr);
	
	TrytoSendData(TempStr, m_Check_18);
}

void CDialogSrSend::OnButtonSend19() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_19, TempStr);
	
	TrytoSendData(TempStr, m_Check_19);
}

void CDialogSrSend::OnButtonSend20() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_20, TempStr);
	
	TrytoSendData(TempStr, m_Check_20);
}

void CDialogSrSend::OnButtonSend21() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_21, TempStr);
	
	TrytoSendData(TempStr, m_Check_21);
}

void CDialogSrSend::OnButtonSend22() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_22, TempStr);
	
	TrytoSendData(TempStr, m_Check_22);
}

void CDialogSrSend::OnButtonSend23() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_23, TempStr);
	
	TrytoSendData(TempStr, m_Check_23);
}

void CDialogSrSend::OnButtonSend24() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_24, TempStr);
	
	TrytoSendData(TempStr, m_Check_24);
}

void CDialogSrSend::OnButtonSend25() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_25, TempStr);
	
	TrytoSendData(TempStr, m_Check_25);
}

void CDialogSrSend::OnButtonSend26() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_26, TempStr);
	
	TrytoSendData(TempStr, m_Check_26);
}

void CDialogSrSend::OnButtonSend27() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_27, TempStr);
	
	TrytoSendData(TempStr, m_Check_27);
}

void CDialogSrSend::OnButtonSend28() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_28, TempStr);
	
	TrytoSendData(TempStr, m_Check_28);
}

void CDialogSrSend::OnButtonSend29() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_29, TempStr);
	
	TrytoSendData(TempStr, m_Check_29);
}

void CDialogSrSend::OnButtonSend30() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_30, TempStr);
	
	TrytoSendData(TempStr, m_Check_30);
}

void CDialogSrSend::OnButtonSend31() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_31, TempStr);
	
	TrytoSendData(TempStr, m_Check_31);
}

void CDialogSrSend::OnButtonSend32() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_32, TempStr);
	
	TrytoSendData(TempStr, m_Check_32);
}

void CDialogSrSend::OnButtonSend33() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_33, TempStr);
	
	TrytoSendData(TempStr, m_Check_33);
}

void CDialogSrSend::OnButtonSend34() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_34, TempStr);
	
	TrytoSendData(TempStr, m_Check_34);
}

void CDialogSrSend::OnButtonSend35() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_35, TempStr);
	
	TrytoSendData(TempStr, m_Check_35);
}

void CDialogSrSend::OnButtonSend36() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_36, TempStr);
	
	TrytoSendData(TempStr, m_Check_36);
}

void CDialogSrSend::OnButtonSend37() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_37, TempStr);
	
	TrytoSendData(TempStr, m_Check_37);
}

void CDialogSrSend::OnButtonSend38() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_38, TempStr);
	
	TrytoSendData(TempStr, m_Check_38);
}

void CDialogSrSend::OnButtonSend39() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_39, TempStr);
	
	TrytoSendData(TempStr, m_Check_39);
}

void CDialogSrSend::OnButtonSend40() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_40, TempStr);
	
	TrytoSendData(TempStr, m_Check_40);
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */


void CDialogSrSend::OnCheck01() 
{
	m_Check_01 = !m_Check_01;
}

void CDialogSrSend::OnCheck02() 
{
	m_Check_02 = !m_Check_02;
}

void CDialogSrSend::OnCheck03() 
{
	m_Check_03 = !m_Check_03;
}

void CDialogSrSend::OnCheck04() 
{
	m_Check_04 = !m_Check_04;
}

void CDialogSrSend::OnCheck05() 
{
	m_Check_05 = !m_Check_05;
}

void CDialogSrSend::OnCheck06() 
{
	m_Check_06 = !m_Check_06;
}

void CDialogSrSend::OnCheck07() 
{
	m_Check_07 = !m_Check_07;
}

void CDialogSrSend::OnCheck08() 
{
	m_Check_08 = !m_Check_08;
}

void CDialogSrSend::OnCheck09() 
{
	m_Check_09 = !m_Check_09;
}

void CDialogSrSend::OnCheck10() 
{
	m_Check_10 = !m_Check_10;
}

void CDialogSrSend::OnCheck11() 
{
	m_Check_11 = !m_Check_11;
}

void CDialogSrSend::OnCheck12() 
{
	m_Check_12 = !m_Check_12;
}

void CDialogSrSend::OnCheck13() 
{
	m_Check_13 = !m_Check_13;
}

void CDialogSrSend::OnCheck14() 
{
	m_Check_14 = !m_Check_14;
}

void CDialogSrSend::OnCheck15() 
{
	m_Check_15 = !m_Check_15;
}

void CDialogSrSend::OnCheck16() 
{
	m_Check_16 = !m_Check_16;
}

void CDialogSrSend::OnCheck17() 
{
	m_Check_17 = !m_Check_17;
}

void CDialogSrSend::OnCheck18() 
{
	m_Check_18 = !m_Check_18;
}

void CDialogSrSend::OnCheck19() 
{
	m_Check_19 = !m_Check_19;
}

void CDialogSrSend::OnCheck20() 
{
	m_Check_20 = !m_Check_20;
}

void CDialogSrSend::OnCheck21() 
{
	m_Check_21 = !m_Check_21;
}

void CDialogSrSend::OnCheck22() 
{
	m_Check_22 = !m_Check_22;
}

void CDialogSrSend::OnCheck23() 
{
	m_Check_23 = !m_Check_23;
}

void CDialogSrSend::OnCheck24() 
{
	m_Check_24 = !m_Check_24;
}

void CDialogSrSend::OnCheck25() 
{
	m_Check_25 = !m_Check_25;
}

void CDialogSrSend::OnCheck26() 
{
	m_Check_26 = !m_Check_26;
}

void CDialogSrSend::OnCheck27() 
{
	m_Check_27 = !m_Check_27;
}

void CDialogSrSend::OnCheck28() 
{
	m_Check_28 = !m_Check_28;
}

void CDialogSrSend::OnCheck29() 
{
	m_Check_29 = !m_Check_29;
}

void CDialogSrSend::OnCheck30() 
{
	m_Check_30 = !m_Check_30;
}

void CDialogSrSend::OnCheck31() 
{
	m_Check_31 = !m_Check_31;
}

void CDialogSrSend::OnCheck32() 
{
	m_Check_32 = !m_Check_32;
}

void CDialogSrSend::OnCheck33() 
{
	m_Check_33 = !m_Check_33;
}

void CDialogSrSend::OnCheck34() 
{
	m_Check_34 = !m_Check_34;
}

void CDialogSrSend::OnCheck35() 
{
	m_Check_35 = !m_Check_35;
}

void CDialogSrSend::OnCheck36() 
{
	m_Check_36 = !m_Check_36;
}

void CDialogSrSend::OnCheck37() 
{
	m_Check_37 = !m_Check_37;
}

void CDialogSrSend::OnCheck38() 
{
	m_Check_38 = !m_Check_38;
}

void CDialogSrSend::OnCheck39() 
{
	m_Check_39 = !m_Check_39;
}

void CDialogSrSend::OnCheck40() 
{
	m_Check_40 = !m_Check_40;
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为对外接口函数 ===================================== */


/**************************************************************************************************
**  函数名称:  InitateSrDlgPos
**  功能描述:  初始化本窗口的位置和显示尺寸
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogSrSend::InitateSrDlgPos(void)
{
	CRect rect;
	CMySScomDlg *pDlg;
	
	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;
	
	GetWindowRect(&rect);
	
	SetWindowPos(NULL, pDlg->s_SrsDlgXPos, pDlg->s_SrsDlgYPos, rect.Width() / 2, rect.Height(), SWP_NOZORDER);	
	ShowWindow(SW_HIDE);
}

/**************************************************************************************************
**  函数名称:  ShowHideSrDlgWindow
**  功能描述:  显示和隐藏本窗口，包括读取和存储窗口位置参数
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogSrSend::ShowHideSrDlgWindow(bool show)
{
	CRect rect;
	CMySScomDlg *pDlg;

	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;
	
	GetWindowRect(&rect);

	if (show == TRUE) {
		SetWindowPos(NULL, pDlg->s_SrsDlgXPos, pDlg->s_SrsDlgYPos, rect.Width(), rect.Height(), SWP_NOSIZE);	
		ShowWindow(SW_SHOW);
	} else {
		pDlg->s_SrsDlgXPos = rect.left;
		pDlg->s_SrsDlgYPos = rect.top;
		ShowWindow(SW_HIDE);
	}
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */


BOOL CDialogSrSend::OnInitDialog() 
{
	CDialog::OnInitDialog();

	s_expandmode = FALSE;
	s_issenddata = FALSE;

	s_cirsendall = TRUE;
	m_Radio_SendAll = 0;
	ShowHideTimeEdit(!s_cirsendall);
	
	return TRUE;
}

void CDialogSrSend::OnTimer(UINT nIDEvent) 
{
	switch (nIDEvent)
	{
		case Timer_No_SrAllSend:                                               // 开始统一轮发全部数据
			TrytoContinueSend();
			break;
			
		case Timer_No_SrEachSend:                                              // 开始分别逐条轮发数据
			TrytoSendEachData();
			break;
		
		default:
			return;
	}
	
	CDialog::OnTimer(nIDEvent);
}


void CDialogSrSend::OnClose() 
{
	CMySScomDlg *pDlg;
	
	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;

	if (s_issenddata == TRUE) {
		MessageBox("请先停止自动循环发送功能，再尝试关闭高级发送窗口......   ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}

	pDlg->InformDlgClose();                                                    // 通知主界面窗口已被关闭

	ShowHideSrDlgWindow(FALSE);
	
	CDialog::OnClose();
}


