// DialogExfunct.cpp : implementation file
//

#include "stdafx.h"
#include "MySScom.h"
#include "DialogExfunct.h"
#include "MySScomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogExfunct dialog


CDialogExfunct::CDialogExfunct(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogExfunct::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogExfunct)
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
	//}}AFX_DATA_INIT
}


void CDialogExfunct::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogExfunct)
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogExfunct, CDialog)
	//{{AFX_MSG_MAP(CDialogExfunct)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_DispChar, OnRADIODispChar)
	ON_BN_CLICKED(IDC_BUTTON_GETCHKSUM, OnButtonGetChksum)
	ON_BN_CLICKED(IDC_BUTTON_FRAME, OnButtonFrame)
	ON_BN_CLICKED(IDC_BUTTON_UNFRAME, OnButtonUnframe)
	ON_BN_CLICKED(IDC_RADIO_DISPMODE, OnRadioDispHex)
	ON_EN_CHANGE(IDC_EDIT_HEAD2, OnChangeEditHead2)
	ON_BN_CLICKED(IDC_RADIO_ASSEMBLE, OnRadioAssemble)
	ON_BN_CLICKED(IDC_RADIO_DISASMBLE, OnRadioDisasmble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为模块内部函数 ===================================== */


/**************************************************************************************************
**  函数名称:  GetChkSum_O
**  功能描述:  计算数据的原码的单字节累加校验和
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
unsigned char CDialogExfunct::GetChkSum_O(unsigned char *ptr, long len)
{
	int i;
    unsigned char result;
	
	result = 0;
    
    for (i = 0; i < len; i++) {
        result += *ptr++;
    }
	
    return result;
}

/**************************************************************************************************
**  函数名称:  GetChkSum_N
**  功能描述:  计算数据的反码的单字节累加校验和
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
unsigned char CDialogExfunct::GetChkSum_N(unsigned char *ptr, long len)
{
	int i;
    unsigned char result;
	
	result = 0;
    
    for (i = 0; i < len; i++) {
        result += ~(*ptr++);
    }
	
    return result;
}

/**************************************************************************************************
**  函数名称:  GetChkSum_Xor
**  功能描述:  计算异或校验和
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
unsigned char CDialogExfunct::GetChkSum_Xor(unsigned char *ptr, long len)
{
	unsigned char sum;
	
	sum = *ptr++;

	while (--len) {
		sum ^= *ptr++;
	}

	return sum;
}

/**************************************************************************************************
**  函数名称:  AssembleByRules
**  功能描述:  按格式封装数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
unsigned int CDialogExfunct::AssembleByRules(unsigned char *dptr, unsigned char *sptr, int len, int maxlen, ASMRULE_T *rule)
{
    unsigned char temp;
    int  rlen;
    
    if (rule == 0) return 0;

    *dptr++ = rule->Flags0;
    rlen = 1;

    for (; len > 0; len--) {
        temp = *sptr++;
        if (temp == rule->Flags0) {
            if (rlen > (maxlen + 2)) return 0;
            *dptr++ = rule->Middle;
            *dptr++ = rule->Flags1;
            rlen += 2;
        } else if (temp == rule->Middle) {
            if (rlen > (maxlen + 2)) return 0;
            *dptr++ = rule->Middle;
            *dptr++ = rule->Flags2;
            rlen += 2;
        } else {
            if (rlen >= maxlen) return 0;
            *dptr++ = temp;
            rlen++;
        }
    }

    if (rlen >= maxlen) return 0;

    *dptr = rule->Flags0;
    rlen++;

    return rlen;
}

/**************************************************************************************************
**  函数名称:  DeassembleByRules
**  功能描述:  按格式解封数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
unsigned int CDialogExfunct::DeassembleByRules(unsigned char *dptr, unsigned char *sptr, int len, int maxlen, ASMRULE_T *rule)
{
    int  rlen;
    unsigned char prechar, curchar, midchar;

    if (rule == 0) return 0;

    midchar = rule->Middle;
    rlen = 0;

    prechar = (~midchar);

    for (; len > 0; len--) {
        curchar = *sptr++;
        if (len >= maxlen) return 0;
        if (prechar == midchar) {
            if (curchar == rule->Flags1) {
                prechar = (~midchar);
                *dptr++ = rule->Flags0;
                rlen++;
            } else if (curchar == rule->Flags2) {
                prechar = (~midchar);
                *dptr++ = midchar;
                rlen++;
            } else {
                return 0;
            }
        } else {
            if ((prechar = curchar) != midchar) {
                *dptr++ = curchar;
                rlen++;
            }
        }
    }
    return rlen;
}

/**************************************************************************************************
**  函数名称:  ConvertHexChar
**  功能描述:  将16进制数据转换为字符
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
unsigned char CDialogExfunct::ConvertHexChar(unsigned char ch) 
{
	if ((ch >= '0') && (ch <= '9')) {
        return (ch - 0x30);
    } else if ((ch >= 'A') && (ch <= 'F')) {
        return (ch - 'A' + 10);
    } else if ((ch >= 'a') && (ch <= 'f')) {
        return (ch - 'a' + 10);
    } else {
        return (0);
    }
}

/**************************************************************************************************
**  函数名称:  CharToHex
**  功能描述:  将字符转换为16进制数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
CString CDialogExfunct::CharToHex(CString InStr)
{
    CString TempStr;
	CString ResultStr = "";
    int len = InStr.GetLength();

    for (int i = 0; i < len; i++) {

		TempStr.Format(_T("%.2X"), InStr[i]);

		if (TempStr.GetLength() > 2) {
			TempStr = TempStr.Right(2);
		}		

		ResultStr = ResultStr + TempStr + " ";
    }

	return ResultStr;
}

/**************************************************************************************************
**  函数名称:  HexToChar
**  功能描述:  将16进制数组转换为字符串
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
CString CDialogExfunct::HexToChar(CString InStr)
{
	CString TempStr;
	CString ResultStr = "";
	int len = InStr.GetLength();

	for (int i = 0; i < len; i++) {
		
		char TempSW = InStr[i++];
		char TempGW = InStr[i++];

		TempSW = ConvertHexChar(TempSW);
		TempGW = ConvertHexChar(TempGW);

		char TempChar = TempSW % 0x10 * 0x10 + TempGW % 0x10;

		ResultStr = ResultStr + TempChar;
    }

	return ResultStr;
}

/**************************************************************************************************
**  函数名称:  String2Hex
**  功能描述:  字符串转换为16进制数据
**  输入参数:  
**  返回参数:  
**  注意事项:  由于这个转换函数的格式限制，在发送框中的十六制字符应该每两个字符之间插入一个空隔
**************************************************************************************************/
int CDialogExfunct::String2Hex(CString str, CByteArray &senddata)
{
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = str.GetLength();

    senddata.SetSize(len / 2);
    
    for (int i = 0; i < len; ) {

        char lstr, hstr = str[i];
        
        if (hstr == ' ') {
            i++;
            continue;
        }
        
        i++;
        
        if (i >= len) {
            break;
        }
        
        lstr       = str[i];
        hexdata    = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        
        if ((hexdata == 16) || (lowhexdata == 16)) {
            break;
        } else {
            hexdata = hexdata * 16 + lowhexdata;
        }
        
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }

    senddata.SetSize(hexdatalen);
    
    return hexdatalen;
}

/**************************************************************************************************
**  函数名称:  ParseCharIsLegal
**  功能描述:  判断字符是否合法
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CDialogExfunct::ParseCharIsLegal(unsigned char inchar)
{
    if ((inchar >= '0') && (inchar <= '9')) {
		return TRUE;
	} else if ((inchar >= 'a') && (inchar <= 'f')) {
		return TRUE;
	} else if ((inchar >= 'A') && (inchar <= 'F')) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/**************************************************************************************************
**  函数名称:  ParseCStrisLegal
**  功能描述:  判断字符串是否合法
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CDialogExfunct::ParseCStrisLegal(CString str, long len)
{
    int           i;
	unsigned char tchar;
	
	for (i = 0; i <= str.GetLength(); ) {                                      /* 本循环体用于判断数据内容是否合法 */
		
		if (str.GetLength() > len) {                                           /* 数据长度过大 */
			return FALSE;
		}

		if ((str.GetLength() % 3) == 1) {                                      /* 数据长度非法 */
			return FALSE;
		}
		
		tchar = str[i++];                                                      /* 判断第1个字符是否有效 */
		
		if (!ParseCharIsLegal(tchar)) {
			return FALSE;
		}
		
		tchar = str[i++];                                                      /* 判断第2个字符是否有效 */
		
		if (!ParseCharIsLegal(tchar)) {
			return FALSE;
		}
		
		if (i >= str.GetLength() - 1) {                                        /* 如果是最后一个数据，则不需要判断其空格 */
			return TRUE;
		}
		
		tchar = str[i++];                                                      /* 判断第3个字符是否为空格 */
		
		if (tchar != ' ') {
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


/* ==================================== 以下为控件消息处理 ===================================== */



void CDialogExfunct::OnChangeEditHead2() 
{
	GetDlgItemText(IDC_EDIT_HEAD2, m_Edit_Head2);

	m_Edit_Key = m_Edit_Head2;
	
    SetDlgItemText(IDC_EDIT_KEY, m_Edit_Key);	
}

void CDialogExfunct::OnButtonGetChksum() 
{
	int           i, len;
	unsigned char result;
	unsigned char tbuf[MAX_CHKSUM_BYTE];
	CByteArray    hexdata;
	
	UpdateData(TRUE);

	if (m_Edit_Checksum.GetLength() == 0) {
		MessageBox("您老啥都没输，难道叫我计算空气的校验和吗......？         ", "抱歉", MB_OK + MB_ICONEXCLAMATION);
		return;
	}

	if (m_Edit_Checksum.GetLength() % 3 == 1) {
		MessageBox("您输入的字符串长度有误，必须严格按照\"12 34 56\"的格式!  ", "注意", MB_OK + MB_ICONINFORMATION);
		m_Radio_Dispmode = _DISPLAY_HEX;
		UpdateData(FALSE);
		return;
	}

	if (ParseCStrisLegal(m_Edit_Checksum, MAX_CHKSUM_BYTE) == FALSE) {
		MessageBox("您输入的字符串格式错误或者长度过长！  ", "抱歉", MB_OK + MB_ICONEXCLAMATION);
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

void CDialogExfunct::OnRadioDispHex() 
{
	CString TempStr;
	
	m_Radio_Dispmode = _DISPLAY_HEX;
	
	if (m_Radio_Dispmode == s_curdispmode) return;                             /* 判断重复点击，则不予响应 */
	
    UpdateData(TRUE);
	
	m_Edit_Change = CharToHex(m_Edit_Change);
	SetDlgItemText(IDC_EDIT_CHANGE, m_Edit_Change);
	
	s_curdispmode = _DISPLAY_HEX;
}

void CDialogExfunct::OnRADIODispChar() 
{
	CString TempStr;
	
	m_Radio_Dispmode = _DISPLAY_CHAR;
	
	if (m_Radio_Dispmode == s_curdispmode) return;                             /* 判断重复点击，则不予响应 */
	
    UpdateData(TRUE);
	
	int length = m_Edit_Change.GetLength();                                    /* 此处需要检验输入的字符串是否符合要求 */
	
	if (length % 3 == 1) {
		MessageBox("您输入的字符串长度有误，必须严格按照\"12 34 56\"的格式!  ", "注意", MB_OK + MB_ICONINFORMATION);
		m_Radio_Dispmode = _DISPLAY_HEX;
		UpdateData(FALSE);
		return;
	}
	
	if (length % 3 == 2) {                                                     /* 防止用户忘记输入最后的空格，此处补上 */
		m_Edit_Change = m_Edit_Change + " ";
        SetDlgItemText(IDC_EDIT_CHANGE, m_Edit_Change);
	}
	
	for (int i = 0; i < length; i++) {                                         /* 每次判断三个字符 */
		
        if ((!ParseCharIsLegal(m_Edit_Change[i++])) || (!ParseCharIsLegal(m_Edit_Change[i++])) ||
            (m_Edit_Change[i] != ' ')) {
            MessageBox("您输入的字符串内容或格式有误，请确认!  ", "注意", MB_OK + MB_ICONINFORMATION);
            m_Radio_Dispmode = _DISPLAY_HEX;
            UpdateData(FALSE);                                                 /* 重新切回选择钮，并更新显示 */
			return;
        }
	}
	
	m_Edit_Change = HexToChar(m_Edit_Change);
	SetDlgItemText(IDC_EDIT_CHANGE, m_Edit_Change);
	
	s_curdispmode = _DISPLAY_CHAR;
}

void CDialogExfunct::OnButtonFrame() 
{
	int           i, ttllen;
	CString       tmpstr;
	unsigned char tmpbuf[MAX_FRAME_LENTH], result[MAX_FRAME_LENTH * 2];
	ASMRULE_T     rules;
	CByteArray    hexdata;

	if (m_Radio_Assmble != _MODE_ASEMBLE) return;

	UpdateData(TRUE);

	if (m_Edit_BFrame.GetLength() == 0) {
		MessageBox("您老啥都没输，封装出来的数据恐怕也不能用吧？     ", "抱歉", MB_OK + MB_ICONEXCLAMATION);
		return;
	}

	if (m_Edit_BFrame.GetLength() % 3 == 1) {
		MessageBox("您输入的字符串长度有误，必须严格按照\"12 34 56\"的格式!  ", "注意", MB_OK + MB_ICONINFORMATION);
		UpdateData(FALSE);
		return;
	}

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

	if (ParseCStrisLegal(m_Edit_BFrame, MAX_FRAME_LENTH) == FALSE) {
		MessageBox("您输入的字符串格式错误或者长度过长！  ", "抱歉", MB_OK + MB_ICONEXCLAMATION);
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

void CDialogExfunct::OnButtonUnframe() 
{
	int           i, ttllen;
	CString       tmpstr;
	unsigned char tmpbuf[MAX_FRAME_LENTH], result[MAX_FRAME_LENTH];
	ASMRULE_T     rules;
	CByteArray    hexdata;
	
	if (m_Radio_Assmble != _MODE_DSAMBLE) return;
	
	UpdateData(TRUE);

	if (m_Edit_AFrame.GetLength() == 0) {
		MessageBox("您老啥都没输，俺就算是神仙也解不出任何东西来啊！     ", "抱歉", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
	
	if ((m_Edit_Head1.GetLength() < 2) || (m_Edit_Head2.GetLength() < 2) || (m_Edit_Char1.GetLength() < 2) || (m_Edit_Char2.GetLength() < 2)) {
		MessageBox("您输入的封装规则关键字符格式或内容有误，请确认！  ", "抱歉", MB_OK + MB_ICONEXCLAMATION);
		return;
	}

	if (m_Edit_AFrame.GetLength() % 3 == 1) {
		MessageBox("您输入的字符串长度有误，必须严格按照\"12 34 56\"的格式!  ", "注意", MB_OK + MB_ICONINFORMATION);
		UpdateData(FALSE);
		return;
	}
	
	rules.Flags0 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head1, NULL, 16);
	rules.Middle = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head2, NULL, 16);
	rules.Flags1 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char1, NULL, 16);
	rules.Flags2 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char2, NULL, 16);
	
	memset(tmpbuf, 0, sizeof(tmpbuf));
	memset(result, 0, sizeof(result));
	
	if (ParseCStrisLegal(m_Edit_AFrame, MAX_FRAME_LENTH) == FALSE) {
		MessageBox("您输入的字符串格式错误或者长度过长！  ", "抱歉", MB_OK + MB_ICONEXCLAMATION);
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

void CDialogExfunct::OnRadioAssemble() 
{
	m_Radio_Assmble = _MODE_ASEMBLE;
	
	GetDlgItem(IDC_BUTTON_FRAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UNFRAME)->EnableWindow(FALSE);

	m_Edit_AFrame = "";                                                        /* 把结果区的内容清空 */
	SetDlgItemText(IDC_EDIT_AFRAME, m_Edit_AFrame);

	UpdateData(FALSE);
}

void CDialogExfunct::OnRadioDisasmble() 
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
**  函数名称:  ShowHideExDlgWindow
**  功能描述:  显示和隐藏本窗口，包括读取和存储窗口位置参数
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogExfunct::ShowHideExDlgWindow(bool show)
{
	CRect rect;
	CMySScomDlg *pDlg;

	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;
	
	GetWindowRect(&rect);

	if (show == TRUE) {
		SetWindowPos(NULL, pDlg->s_ExfDlgXPos, pDlg->s_ExfDlgYPos, rect.Width(), rect.Height(), SWP_NOSIZE);	
		ShowWindow(SW_SHOW);
	} else {
		pDlg->s_ExfDlgXPos = rect.left;
		pDlg->s_ExfDlgYPos = rect.top;
		ShowWindow(SW_HIDE);
	}
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */


BOOL CDialogExfunct::OnInitDialog() 
{
	CDialog::OnInitDialog();

	s_curdispmode = -1;

	GetDlgItem(IDC_BUTTON_UNFRAME)->EnableWindow(FALSE);
	
	// CG: The following block was added by the ToolTips component.
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

BOOL CDialogExfunct::PreTranslateMessage(MSG* pMsg) 
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

void CDialogExfunct::OnClose() 
{
	CMySScomDlg *pDlg;
	
	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;
	
	pDlg->InformExDlgClose();                                                  /* 通知主界面窗口已被关闭 */
	
	ShowHideExDlgWindow(FALSE);
	
	CDialog::OnClose();
}

