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
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊģ���ڲ����� ===================================== */


/**************************************************************************************************
**  ��������:  GetChkSum_O
**  ��������:  �������ݵ�ԭ��ĵ��ֽ��ۼ�У���
**  �������:  
**  ���ز���:  
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
**  ��������:  GetChkSum_N
**  ��������:  �������ݵķ���ĵ��ֽ��ۼ�У���
**  �������:  
**  ���ز���:  
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
**  ��������:  GetChkSum_Xor
**  ��������:  �������У���
**  �������:  
**  ���ز���:  
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
**  ��������:  AssembleByRules
**  ��������:  ����ʽ��װ����
**  �������:  
**  ���ز���:  
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
**  ��������:  DeassembleByRules
**  ��������:  ����ʽ�������
**  �������:  
**  ���ز���:  
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
**  ��������:  ConvertHexChar
**  ��������:  ��16��������ת��Ϊ�ַ�
**  �������:  
**  ���ز���:  
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
**  ��������:  CharToHex
**  ��������:  ���ַ�ת��Ϊ16��������
**  �������:  
**  ���ز���:  
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
**  ��������:  HexToChar
**  ��������:  ��16��������ת��Ϊ�ַ���
**  �������:  
**  ���ز���:  
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
**  ��������:  String2Hex
**  ��������:  �ַ���ת��Ϊ16��������
**  �������:  
**  ���ز���:  
**  ע������:  �������ת�������ĸ�ʽ���ƣ��ڷ��Ϳ��е�ʮ�����ַ�Ӧ��ÿ�����ַ�֮�����һ���ո�
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
**  ��������:  ParseCharIsLegal
**  ��������:  �ж��ַ��Ƿ�Ϸ�
**  �������:  
**  ���ز���:  
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
**  ��������:  ParseCStrisLegal
**  ��������:  �ж��ַ����Ƿ�Ϸ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CDialogExfunct::ParseCStrisLegal(CString str, long len)
{
    int           i;
	unsigned char tchar;
	
	for (i = 0; i <= str.GetLength(); ) {                                      /* ��ѭ���������ж����������Ƿ�Ϸ� */
		
		if (str.GetLength() > len) {                                           /* ���ݳ��ȹ��� */
			return FALSE;
		}

		if ((str.GetLength() % 3) == 1) {                                      /* ���ݳ��ȷǷ� */
			return FALSE;
		}
		
		tchar = str[i++];                                                      /* �жϵ�1���ַ��Ƿ���Ч */
		
		if (!ParseCharIsLegal(tchar)) {
			return FALSE;
		}
		
		tchar = str[i++];                                                      /* �жϵ�2���ַ��Ƿ���Ч */
		
		if (!ParseCharIsLegal(tchar)) {
			return FALSE;
		}
		
		if (i >= str.GetLength() - 1) {                                        /* ��������һ�����ݣ�����Ҫ�ж���ո� */
			return TRUE;
		}
		
		tchar = str[i++];                                                      /* �жϵ�3���ַ��Ƿ�Ϊ�ո� */
		
		if (tchar != ' ') {
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


/* ==================================== ����Ϊ�ؼ���Ϣ���� ===================================== */



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
		MessageBox("����ɶ��û�䣬�ѵ����Ҽ��������У�����......��         ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return;
	}

	if (m_Edit_Checksum.GetLength() % 3 == 1) {
		MessageBox("��������ַ����������󣬱����ϸ���\"12 34 56\"�ĸ�ʽ!  ", "ע��", MB_OK + MB_ICONINFORMATION);
		m_Radio_Dispmode = _DISPLAY_HEX;
		UpdateData(FALSE);
		return;
	}

	if (ParseCStrisLegal(m_Edit_Checksum, MAX_CHKSUM_BYTE) == FALSE) {
		MessageBox("��������ַ�����ʽ������߳��ȹ�����  ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return;
	}

	len = String2Hex(m_Edit_Checksum, hexdata);                                /* ���ַ���ת��Ϊʵ�ʶ�Ӧ������ */
	
	for (i = 0; i < len; i++) {                                                /* ��ʵ�����ݱ��������� */
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

	m_Edit_Chksum10.Format("%d", result);                                      /* ��ʾ���յĽ�� */
	SetDlgItemText(IDC_EDIT_CHKSUM10, m_Edit_Chksum10);

	m_Edit_Chksum16.Format("%X", result);
	SetDlgItemText(IDC_EDIT_CHKSUM16, m_Edit_Chksum16);
}

void CDialogExfunct::OnRadioDispHex() 
{
	CString TempStr;
	
	m_Radio_Dispmode = _DISPLAY_HEX;
	
	if (m_Radio_Dispmode == s_curdispmode) return;                             /* �ж��ظ������������Ӧ */
	
    UpdateData(TRUE);
	
	m_Edit_Change = CharToHex(m_Edit_Change);
	SetDlgItemText(IDC_EDIT_CHANGE, m_Edit_Change);
	
	s_curdispmode = _DISPLAY_HEX;
}

void CDialogExfunct::OnRADIODispChar() 
{
	CString TempStr;
	
	m_Radio_Dispmode = _DISPLAY_CHAR;
	
	if (m_Radio_Dispmode == s_curdispmode) return;                             /* �ж��ظ������������Ӧ */
	
    UpdateData(TRUE);
	
	int length = m_Edit_Change.GetLength();                                    /* �˴���Ҫ����������ַ����Ƿ����Ҫ�� */
	
	if (length % 3 == 1) {
		MessageBox("��������ַ����������󣬱����ϸ���\"12 34 56\"�ĸ�ʽ!  ", "ע��", MB_OK + MB_ICONINFORMATION);
		m_Radio_Dispmode = _DISPLAY_HEX;
		UpdateData(FALSE);
		return;
	}
	
	if (length % 3 == 2) {                                                     /* ��ֹ�û������������Ŀո񣬴˴����� */
		m_Edit_Change = m_Edit_Change + " ";
        SetDlgItemText(IDC_EDIT_CHANGE, m_Edit_Change);
	}
	
	for (int i = 0; i < length; i++) {                                         /* ÿ���ж������ַ� */
		
        if ((!ParseCharIsLegal(m_Edit_Change[i++])) || (!ParseCharIsLegal(m_Edit_Change[i++])) ||
            (m_Edit_Change[i] != ' ')) {
            MessageBox("��������ַ������ݻ��ʽ������ȷ��!  ", "ע��", MB_OK + MB_ICONINFORMATION);
            m_Radio_Dispmode = _DISPLAY_HEX;
            UpdateData(FALSE);                                                 /* �����л�ѡ��ť����������ʾ */
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
		MessageBox("����ɶ��û�䣬��װ���������ݿ���Ҳ�����ðɣ�     ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return;
	}

	if (m_Edit_BFrame.GetLength() % 3 == 1) {
		MessageBox("��������ַ����������󣬱����ϸ���\"12 34 56\"�ĸ�ʽ!  ", "ע��", MB_OK + MB_ICONINFORMATION);
		UpdateData(FALSE);
		return;
	}

	if ((m_Edit_Head1.GetLength() < 2) || (m_Edit_Head2.GetLength() < 2) || (m_Edit_Char1.GetLength() < 2) || (m_Edit_Char2.GetLength() < 2)) {
		MessageBox("������ķ�װ����ؼ��ַ���ʽ������������ȷ�ϣ�  ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return;
	}

	rules.Flags0 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head1, NULL, 16);
	rules.Middle = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head2, NULL, 16);
	rules.Flags1 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char1, NULL, 16);
	rules.Flags2 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char2, NULL, 16);
	
	memset(tmpbuf, 0, sizeof(tmpbuf));
	memset(result, 0, sizeof(result));

	if (ParseCStrisLegal(m_Edit_BFrame, MAX_FRAME_LENTH) == FALSE) {
		MessageBox("��������ַ�����ʽ������߳��ȹ�����  ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
	
	ttllen = String2Hex(m_Edit_BFrame, hexdata);                               /* ���ַ���ת��Ϊʵ�ʶ�Ӧ������ */

	for (i = 0; i < ttllen; i++) {                                             /* ��ʵ�����ݱ��������� */
		tmpbuf[i] = hexdata.GetAt(i);
	}
	
    ttllen = AssembleByRules(result, tmpbuf, ttllen, sizeof(result), &rules);
		
	tmpstr = (LPSTR)(LPCTSTR)result;                                           /* ���ַ�����ת��ΪCString���� */
		
    m_Edit_AFrame = CharToHex(tmpstr);                                         /* ����ֵ�������¸�ʽ�� */
    SetDlgItemText(IDC_EDIT_AFRAME, m_Edit_AFrame);                            /* ���±༭������ */
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
		MessageBox("����ɶ��û�䣬������������Ҳ�ⲻ���κζ���������     ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
	
	if ((m_Edit_Head1.GetLength() < 2) || (m_Edit_Head2.GetLength() < 2) || (m_Edit_Char1.GetLength() < 2) || (m_Edit_Char2.GetLength() < 2)) {
		MessageBox("������ķ�װ����ؼ��ַ���ʽ������������ȷ�ϣ�  ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return;
	}

	if (m_Edit_AFrame.GetLength() % 3 == 1) {
		MessageBox("��������ַ����������󣬱����ϸ���\"12 34 56\"�ĸ�ʽ!  ", "ע��", MB_OK + MB_ICONINFORMATION);
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
		MessageBox("��������ַ�����ʽ������߳��ȹ�����  ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
	
	ttllen = String2Hex(m_Edit_AFrame, hexdata);                               /* ���ַ���ת��Ϊʵ�ʶ�Ӧ������ */
	
	for (i = 0; i < ttllen; i++) {                                             /* ��ʵ�����ݱ��������� */
		tmpbuf[i] = hexdata.GetAt(i);
	}
	
    ttllen = DeassembleByRules(result, &tmpbuf[1], ttllen - 2, sizeof(result), &rules);
	
	tmpstr = (LPSTR)(LPCTSTR)result;                                           /* ���ַ�����ת��ΪCString���� */
	
    m_Edit_BFrame = CharToHex(tmpstr);                                         /* ����ֵ�������¸�ʽ�� */
    SetDlgItemText(IDC_EDIT_BFRAME, m_Edit_BFrame);                            /* ���±༭������ */
}

void CDialogExfunct::OnRadioAssemble() 
{
	m_Radio_Assmble = _MODE_ASEMBLE;
	
	GetDlgItem(IDC_BUTTON_FRAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UNFRAME)->EnableWindow(FALSE);

	m_Edit_AFrame = "";                                                        /* �ѽ������������� */
	SetDlgItemText(IDC_EDIT_AFRAME, m_Edit_AFrame);

	UpdateData(FALSE);
}

void CDialogExfunct::OnRadioDisasmble() 
{
	m_Radio_Assmble = _MODE_DSAMBLE;
	
	GetDlgItem(IDC_BUTTON_FRAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_UNFRAME)->EnableWindow(TRUE);

	m_Edit_BFrame = "";                                                        /* �ѽ������������� */
	SetDlgItemText(IDC_EDIT_BFRAME, m_Edit_BFrame);

	UpdateData(FALSE);
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊ����ӿں��� ===================================== */


/**************************************************************************************************
**  ��������:  ShowHideExDlgWindow
**  ��������:  ��ʾ�����ر����ڣ�������ȡ�ʹ洢����λ�ò���
**  �������:  
**  ���ز���:  
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
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */


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
	
	pDlg->InformExDlgClose();                                                  /* ֪ͨ�����洰���ѱ��ر� */
	
	ShowHideExDlgWindow(FALSE);
	
	CDialog::OnClose();
}

