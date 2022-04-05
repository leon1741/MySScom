#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogExtrafunct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDialogExtrafunct::CDialogExtrafunct(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogExtrafunct::IDD, pParent)
{
	m_Radio_Assmble  = _MODE_ASEMBLE;
	m_Radio_Checksum = _CHKSUM_ADO;
	m_Radio_Dispmode = _DISPLAY_CHAR;
	m_Edit_AFrame = _T("");
	m_Edit_BFrame = _T("");
	m_Edit_Checksum = _T("");
	m_Edit_Chksum10 = _T("");
	m_Edit_Chksum16 = _T("");
	m_Edit_Change = _T("");
	m_Edit_Char1 = _T("02");
	m_Edit_Char2 = _T("01");
	m_Edit_Head1 = _T("7E");
	m_Edit_Head2 = _T("7D");
	m_Edit_Key = _T("7D");
}


void CDialogExtrafunct::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_ASSEMBLE, m_Radio_Assmble);
	DDX_Radio(pDX, IDC_RADIO_CHECKSUM, m_Radio_Checksum);
	DDX_Radio(pDX, IDC_RADIO_DISPMODE, m_Radio_Dispmode);
	DDX_Text(pDX, IDC_EDIT_AFRAME, m_Edit_AFrame);
	DDX_Text(pDX, IDC_EDIT_BFRAME, m_Edit_BFrame);
	DDX_Text(pDX, IDC_EDIT_CHECKSUM, m_Edit_Checksum);
	DDX_Text(pDX, IDC_EDIT_CHKSUM10, m_Edit_Chksum10);
	DDX_Text(pDX, IDC_EDIT_CHKSUM16, m_Edit_Chksum16);
	DDX_Text(pDX, IDC_EDIT_CHANGE, m_Edit_Change);
	DDX_Text(pDX, IDC_EDIT_CHAR1, m_Edit_Char1);
	DDV_MaxChars(pDX, m_Edit_Char1, 2);
	DDX_Text(pDX, IDC_EDIT_CHAR2, m_Edit_Char2);
	DDV_MaxChars(pDX, m_Edit_Char2, 2);
	DDX_Text(pDX, IDC_EDIT_HEAD1, m_Edit_Head1);
	DDV_MaxChars(pDX, m_Edit_Head1, 2);
	DDX_Text(pDX, IDC_EDIT_HEAD2, m_Edit_Head2);
	DDV_MaxChars(pDX, m_Edit_Head2, 2);
	DDX_Text(pDX, IDC_EDIT_KEY, m_Edit_Key);
	DDV_MaxChars(pDX, m_Edit_Key, 2);
}


BEGIN_MESSAGE_MAP(CDialogExtrafunct, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_DispChar, OnRADIODispChar)
	ON_BN_CLICKED(IDC_BUTTON_GETCHKSUM, OnButtonGetChksum)
	ON_BN_CLICKED(IDC_BUTTON_FRAME, OnButtonFrame)
	ON_BN_CLICKED(IDC_BUTTON_UNFRAME, OnButtonUnframe)
	ON_BN_CLICKED(IDC_RADIO_DISPMODE, OnRadioDispHex)
	ON_EN_CHANGE(IDC_EDIT_HEAD2, OnChangeEditHead2)
	ON_BN_CLICKED(IDC_RADIO_ASSEMBLE, OnRadioAssemble)
	ON_BN_CLICKED(IDC_RADIO_DISASMBLE, OnRadioDisasmble)
END_MESSAGE_MAP()



/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== 以下为内部工具函数 ===================================== */

/**************************************************************************************************
**  函数名称:  InputStrValid
**  功能描述:  判断输入的字符串内容是否合法
**************************************************************************************************/
bool CDialogExtrafunct::InputStrValid(CString incstr, int maxlen)
{
	if (incstr.GetLength() > maxlen) {
		MessageBox("您老一下子输入太多内容了，小的能力有限，实在是搞不定啊~~~         ", "抱歉", MB_OK + MB_ICONINFORMATION);
		return FALSE;
	}

	if (ParseCStrisLegal(incstr) == FALSE) {
		MessageBox("请注意：16进制！16进制的格式，您老不懂吗？别逼小的鄙视您！^_^\r\n\r\n举个例子：\"12 34\"或者\"12 34 \"都行！数字中间必须有空格！", "抱歉", MB_OK + MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== 以下为控件消息处理 ===================================== */


/**************************************************************************************************
**  函数名称:  OnChangeEditHead2
**  功能描述:  更新HEAD字符串内容
**************************************************************************************************/
void CDialogExtrafunct::OnChangeEditHead2() 
{
	GetDlgItemText(IDC_EDIT_HEAD2, m_Edit_Head2);

	m_Edit_Key = m_Edit_Head2;
	
    SetDlgItemText(IDC_EDIT_KEY, m_Edit_Key);	
}

/**************************************************************************************************
**  函数名称:  OnButtonGetChksum
**  功能描述:  计算校验和
**************************************************************************************************/
void CDialogExtrafunct::OnButtonGetChksum() 
{
	int           i, len;
	unsigned char result;
	unsigned char tbuf[MAX_CHKSUM_BYTE];
	CByteArray    hexdata;
	
	UpdateData(TRUE);

	if (InputStrValid(m_Edit_Checksum, MAX_CHKSUM_BYTE) == FALSE) {            /* 输入为空，或者数据太长，或者内容非法 */
		UpdateData(FALSE);
		return;
	}

	len = String2Hex(m_Edit_Checksum, hexdata);                                /* 将字符串转换为实际对应的数据 */
	
	for (i = 0; i < len; i++) {                                                /* 将实际数据保存至数组 */
		tbuf[i] = hexdata.GetAt(i);
	}
	
	switch (m_Radio_Checksum)
	{
		case _CHKSUM_ADO:
			result = GetChkSum_O(tbuf, len);
			break;

		case _CHKSUM_ADN:
			result = GetChkSum_N(tbuf, len);
			break;
			
		case _CHKSUM_XOR:
			result = GetChkSum_Xor(tbuf, len);
			break;
			
		default:
			break;
	}

	m_Edit_Chksum10.Format("%d", result);                                      /* 显示最终的结果 */
	SetDlgItemText(IDC_EDIT_CHKSUM10, m_Edit_Chksum10);

	m_Edit_Chksum16.Format("%X", result);
	SetDlgItemText(IDC_EDIT_CHKSUM16, m_Edit_Chksum16);
}

/**************************************************************************************************
**  函数名称:  OnRadioDispHex
**  功能描述:  HEX模式显示
**************************************************************************************************/
void CDialogExtrafunct::OnRadioDispHex() 
{
	CString TempStr;
	
	m_Radio_Dispmode = _DISPLAY_HEX;
	
	if (m_Radio_Dispmode == s_curdispmode) return;                             /* 判断重复点击，则不予响应 */
	
    UpdateData(TRUE);
	
	m_Edit_Change = CharToHex(m_Edit_Change);
	SetDlgItemText(IDC_EDIT_CHANGE, m_Edit_Change);
	
	s_curdispmode = _DISPLAY_HEX;
}

/**************************************************************************************************
**  函数名称:  OnRADIODispChar
**  功能描述:  字符模式显示
**************************************************************************************************/
void CDialogExtrafunct::OnRADIODispChar() 
{
	CString TempStr;
	
	m_Radio_Dispmode = _DISPLAY_CHAR;
	
	if (m_Radio_Dispmode == s_curdispmode) return;                             /* 判断重复点击，则不予响应 */
	
    UpdateData(TRUE);

	if (InputStrValid(m_Edit_Change, MAX_CHKSUM_BYTE) == FALSE) {              /* 输入为空，或者数据太长，或者内容非法 */
		m_Radio_Dispmode = _DISPLAY_HEX;
		UpdateData(FALSE);
		return;
	}
	
	m_Edit_Change = HexToChar(m_Edit_Change);
	SetDlgItemText(IDC_EDIT_CHANGE, m_Edit_Change);
	
	s_curdispmode = _DISPLAY_CHAR;
}

/**************************************************************************************************
**  函数名称:  OnButtonFrame
**  功能描述:  封装数据
**************************************************************************************************/
void CDialogExtrafunct::OnButtonFrame() 
{
	int           i, ttllen;
	CString       tmpstr;
	unsigned char tmpbuf[MAX_FRAME_LENTH], result[MAX_FRAME_LENTH * 2];
	ASMRULE_T     rules;
	CByteArray    hexdata;

	if (m_Radio_Assmble != _MODE_ASEMBLE) return;

	UpdateData(TRUE);

	if ((m_Edit_Head1.GetLength() < 2) || (m_Edit_Head2.GetLength() < 2) || (m_Edit_Char1.GetLength() < 2) || (m_Edit_Char2.GetLength() < 2)) {
		MessageBox("您输入的封装规则关键字符格式或内容有误，请确认！  ", "抱歉", MB_OK + MB_ICONEXCLAMATION);
		return;
	}

	rules.Flags0 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head1, NULL, 16);
	rules.Middle = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head2, NULL, 16);
	rules.Flags1 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char1, NULL, 16);
	rules.Flags2 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char2, NULL, 16);
	
	memset(tmpbuf, 0, sizeof(tmpbuf));
	memset(result, 0, sizeof(result));

	if (InputStrValid(m_Edit_BFrame, MAX_FRAME_LENTH) == FALSE) {              /* 输入为空，或者数据太长，或者内容非法 */
		UpdateData(FALSE);
		return;
	}
	
	ttllen = String2Hex(m_Edit_BFrame, hexdata);                               /* 将字符串转换为实际对应的数据 */

	for (i = 0; i < ttllen; i++) {                                             /* 将实际数据保存至数组 */
		tmpbuf[i] = hexdata.GetAt(i);
	}
	
    ttllen = AssembleByRules(result, tmpbuf, ttllen, sizeof(result), &rules);
		
	tmpstr = (LPSTR)(LPCTSTR)result;                                           /* 将字符数组转化为CString类型 */
		
    m_Edit_AFrame = CharToHex(tmpstr);                                         /* 将数值内容重新格式化 */
    SetDlgItemText(IDC_EDIT_AFRAME, m_Edit_AFrame);                            /* 更新编辑框内容 */
}

/**************************************************************************************************
**  函数名称:  OnButtonUnframe
**  功能描述:  解封数据
**************************************************************************************************/
void CDialogExtrafunct::OnButtonUnframe() 
{
	int           i, ttllen;
	CString       tmpstr;
	unsigned char tmpbuf[MAX_FRAME_LENTH], result[MAX_FRAME_LENTH];
	ASMRULE_T     rules;
	CByteArray    hexdata;
	
	if (m_Radio_Assmble != _MODE_DSAMBLE) return;
	
	UpdateData(TRUE);
	
	if ((m_Edit_Head1.GetLength() < 2) || (m_Edit_Head2.GetLength() < 2) || (m_Edit_Char1.GetLength() < 2) || (m_Edit_Char2.GetLength() < 2)) {
		MessageBox("您输入的封装规则关键字符格式或内容有误，请确认！  ", "抱歉", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
	
	rules.Flags0 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head1, NULL, 16);
	rules.Middle = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head2, NULL, 16);
	rules.Flags1 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char1, NULL, 16);
	rules.Flags2 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char2, NULL, 16);
	
	memset(tmpbuf, 0, sizeof(tmpbuf));
	memset(result, 0, sizeof(result));

	if (InputStrValid(m_Edit_AFrame, MAX_FRAME_LENTH) == FALSE) {              /* 输入为空，或者数据太长，或者内容非法 */
		UpdateData(FALSE);
		return;
	}
	
	ttllen = String2Hex(m_Edit_AFrame, hexdata);                               /* 将字符串转换为实际对应的数据 */
	
	for (i = 0; i < ttllen; i++) {                                             /* 将实际数据保存至数组 */
		tmpbuf[i] = hexdata.GetAt(i);
	}
	
    ttllen = DeassembleByRules(result, &tmpbuf[1], ttllen - 2, sizeof(result), &rules);
	
	tmpstr = (LPSTR)(LPCTSTR)result;                                           /* 将字符数组转化为CString类型 */
	
    m_Edit_BFrame = CharToHex(tmpstr);                                         /* 将数值内容重新格式化 */
    SetDlgItemText(IDC_EDIT_BFRAME, m_Edit_BFrame);                            /* 更新编辑框内容 */
}

/**************************************************************************************************
**  函数名称:  OnRadioAssemble
**  功能描述:  切换到封装数据模式
**************************************************************************************************/
void CDialogExtrafunct::OnRadioAssemble() 
{
	m_Radio_Assmble = _MODE_ASEMBLE;
	
	GetDlgItem(IDC_BUTTON_FRAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UNFRAME)->EnableWindow(FALSE);

	m_Edit_AFrame = "";                                                        /* 把结果区的内容清空 */
	SetDlgItemText(IDC_EDIT_AFRAME, m_Edit_AFrame);

	UpdateData(FALSE);
}

/**************************************************************************************************
**  函数名称:  OnRadioDisasmble
**  功能描述:  切换到解封数据模式
**************************************************************************************************/
void CDialogExtrafunct::OnRadioDisasmble() 
{
	m_Radio_Assmble = _MODE_DSAMBLE;
	
	GetDlgItem(IDC_BUTTON_FRAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_UNFRAME)->EnableWindow(TRUE);

	m_Edit_BFrame = "";                                                        /* 把结果区的内容清空 */
	SetDlgItemText(IDC_EDIT_BFRAME, m_Edit_BFrame);

	UpdateData(FALSE);
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
void CDialogExtrafunct::ShowHideDlgWindow(bool show)
{
	CRect rect;
	
	GetWindowRect(&rect);

	if (show == TRUE) {
		SetWindowPos(NULL, s_DialogPos_X, s_DialogPos_Y, rect.Width(), rect.Height(), SWP_NOSIZE);	
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
void CDialogExtrafunct::InitiateAllParas(void)
{
	s_DialogPos_X = (::GetPrivateProfileInt(FLAG_EXTRAFUNT, EXTRAFUNT_POSTIONX,  0, CONFIGFILENAME));
	s_DialogPos_Y = (::GetPrivateProfileInt(FLAG_EXTRAFUNT, EXTRAFUNT_POSTIONY,  0, CONFIGFILENAME));
}

/**************************************************************************************************
**  函数名称:  RecordAllParas
**  功能描述:  保存各个参数
**************************************************************************************************/
void CDialogExtrafunct::RecordAllParas(void)
{
	CString ParaStr;
	
	if ((s_DialogPos_X < 0) || (s_DialogPos_X > MAX_WIN_POS)) {                /* 防止边界异常 */
		s_DialogPos_X = 0;
	}

	if ((s_DialogPos_Y < 0) || (s_DialogPos_Y > MAX_WIN_POS)) {                /* 防止边界异常 */
		s_DialogPos_Y = 0;
	}
	
	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString(FLAG_EXTRAFUNT, EXTRAFUNT_POSTIONX, ParaStr, CONFIGFILENAME);
	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString(FLAG_EXTRAFUNT, EXTRAFUNT_POSTIONY, ParaStr, CONFIGFILENAME);
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
**************************************************************************************************/
BOOL CDialogExtrafunct::OnInitDialog() 
{
	CDialog::OnInitDialog();

	s_curdispmode = -1;

	GetDlgItem(IDC_BUTTON_UNFRAME)->EnableWindow(FALSE);

	{
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		m_tooltip.AddTool(GetDlgItem(IDC_EDIT_CHECKSUM),  IDS_STRING_101);
		m_tooltip.AddTool(GetDlgItem(IDC_EDIT_CHANGE),    IDS_STRING_102);
		m_tooltip.AddTool(GetDlgItem(IDC_EDIT_BFRAME),    IDS_STRING_103);
		m_tooltip.AddTool(GetDlgItem(IDC_EDIT_AFRAME),    IDS_STRING_104);
	}

	return TRUE;
}

/**************************************************************************************************
**  函数名称:  PreTranslateMessage
**  功能描述:  预处理消息
**************************************************************************************************/
BOOL CDialogExtrafunct::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);

	if (pMsg -> message == WM_KEYDOWN) {
		
        if (pMsg -> wParam == VK_ESCAPE)
            return true;
        if (pMsg -> wParam == VK_RETURN)
            return true;
    }
	
	return CDialog::PreTranslateMessage(pMsg);
}

/**************************************************************************************************
**  函数名称:  OnClose
**  功能描述:  窗体关闭消息处理
**************************************************************************************************/
void CDialogExtrafunct::OnClose() 
{
	ShowHideDlgWindow(FALSE);
	
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_EFDLGCLOSE, 0, 0);
	
	CDialog::OnClose();
}

