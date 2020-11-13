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
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== ����Ϊ�ڲ����ߺ��� ===================================== */

bool CDialogExtrafunct::InputStrValid(CString incstr, int maxlen)
{
	if (incstr.GetLength() > maxlen) {
		MessageBox("����һ��������̫�������ˣ�С���������ޣ�ʵ���Ǹ㲻����~~~         ", "��Ǹ", MB_OK + MB_ICONINFORMATION);
		return FALSE;
	}

	if (ParseCStrisLegal(incstr) == FALSE) {
		MessageBox("��ע�⣺16���ƣ�16���Ƶĸ�ʽ�����ϲ����𣿱��С�ı�������^-^\r\n\r\n�ٸ����ӣ�\"12 34\"����\"12 34 \"���У�", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== ����Ϊ�ؼ���Ϣ���� ===================================== */


/**************************************************************************************************
**  ��������:  OnChangeEditHead2
**  ��������:  
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogExtrafunct::OnChangeEditHead2() 
{
	GetDlgItemText(IDC_EDIT_HEAD2, m_Edit_Head2);

	m_Edit_Key = m_Edit_Head2;
	
    SetDlgItemText(IDC_EDIT_KEY, m_Edit_Key);	
}

/**************************************************************************************************
**  ��������:  OnButtonGetChksum
**  ��������:  ����У���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogExtrafunct::OnButtonGetChksum() 
{
	int           i, len;
	unsigned char result;
	unsigned char tbuf[MAX_CHKSUM_BYTE];
	CByteArray    hexdata;
	
	UpdateData(TRUE);

	if (InputStrValid(m_Edit_Checksum, MAX_CHKSUM_BYTE) == FALSE) {            /* ����Ϊ�գ���������̫�����������ݷǷ� */
		UpdateData(FALSE);
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

/**************************************************************************************************
**  ��������:  OnRadioDispHex
**  ��������:  HEXģʽ��ʾ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogExtrafunct::OnRadioDispHex() 
{
	CString TempStr;
	
	m_Radio_Dispmode = _DISPLAY_HEX;
	
	if (m_Radio_Dispmode == s_curdispmode) return;                             /* �ж��ظ������������Ӧ */
	
    UpdateData(TRUE);
	
	m_Edit_Change = CharToHex(m_Edit_Change);
	SetDlgItemText(IDC_EDIT_CHANGE, m_Edit_Change);
	
	s_curdispmode = _DISPLAY_HEX;
}

/**************************************************************************************************
**  ��������:  OnRADIODispChar
**  ��������:  �ַ�ģʽ��ʾ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogExtrafunct::OnRADIODispChar() 
{
	CString TempStr;
	
	m_Radio_Dispmode = _DISPLAY_CHAR;
	
	if (m_Radio_Dispmode == s_curdispmode) return;                             /* �ж��ظ������������Ӧ */
	
    UpdateData(TRUE);

	if (InputStrValid(m_Edit_Change, MAX_CHKSUM_BYTE) == FALSE) {            /* ����Ϊ�գ���������̫�����������ݷǷ� */
		m_Radio_Dispmode = _DISPLAY_HEX;
		UpdateData(FALSE);
		return;
	}
	
	m_Edit_Change = HexToChar(m_Edit_Change);
	SetDlgItemText(IDC_EDIT_CHANGE, m_Edit_Change);
	
	s_curdispmode = _DISPLAY_CHAR;
}

/**************************************************************************************************
**  ��������:  OnButtonFrame
**  ��������:  ��װ����
**  �������:  
**  ���ز���:  
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
		MessageBox("������ķ�װ����ؼ��ַ���ʽ������������ȷ�ϣ�  ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return;
	}

	rules.Flags0 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head1, NULL, 16);
	rules.Middle = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head2, NULL, 16);
	rules.Flags1 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char1, NULL, 16);
	rules.Flags2 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char2, NULL, 16);
	
	memset(tmpbuf, 0, sizeof(tmpbuf));
	memset(result, 0, sizeof(result));

	if (InputStrValid(m_Edit_BFrame, MAX_FRAME_LENTH) == FALSE) {              /* ����Ϊ�գ���������̫�����������ݷǷ� */
		UpdateData(FALSE);
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

/**************************************************************************************************
**  ��������:  OnButtonUnframe
**  ��������:  �������
**  �������:  
**  ���ز���:  
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
		MessageBox("������ķ�װ����ؼ��ַ���ʽ������������ȷ�ϣ�  ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
	
	rules.Flags0 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head1, NULL, 16);
	rules.Middle = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Head2, NULL, 16);
	rules.Flags1 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char1, NULL, 16);
	rules.Flags2 = (unsigned char)strtol((LPSTR)(LPCTSTR)m_Edit_Char2, NULL, 16);
	
	memset(tmpbuf, 0, sizeof(tmpbuf));
	memset(result, 0, sizeof(result));

	if (InputStrValid(m_Edit_AFrame, MAX_FRAME_LENTH) == FALSE) {              /* ����Ϊ�գ���������̫�����������ݷǷ� */
		UpdateData(FALSE);
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

/**************************************************************************************************
**  ��������:  OnRadioAssemble
**  ��������:  �л�����װ����ģʽ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogExtrafunct::OnRadioAssemble() 
{
	m_Radio_Assmble = _MODE_ASEMBLE;
	
	GetDlgItem(IDC_BUTTON_FRAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UNFRAME)->EnableWindow(FALSE);

	m_Edit_AFrame = "";                                                        /* �ѽ������������� */
	SetDlgItemText(IDC_EDIT_AFRAME, m_Edit_AFrame);

	UpdateData(FALSE);
}

/**************************************************************************************************
**  ��������:  OnRadioDisasmble
**  ��������:  �л����������ģʽ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogExtrafunct::OnRadioDisasmble() 
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
**  ��������:  ShowHideDlgWindow
**  ��������:  ��ʾ�����ر����ڣ�������ȡ�ʹ洢����λ�ò���
**  �������:  
**  ���ز���:  
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
**  ��������:  InitiateAllParas
**  ��������:  ��ʼ����������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogExtrafunct::InitiateAllParas(void)
{
	s_DialogPos_X = (::GetPrivateProfileInt("ExtrFunc", "DialogPos_X",  0, ".\\Settings.ini"));
	s_DialogPos_Y = (::GetPrivateProfileInt("ExtrFunc", "DialogPos_Y",  0, ".\\Settings.ini"));
}

/**************************************************************************************************
**  ��������:  RecordAllParas
**  ��������:  �����������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogExtrafunct::RecordAllParas(void)
{
	CString ParaStr;
	
	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString("ExtrFunc", "DialogPos_X", ParaStr, ".\\Settings.ini");
	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString("ExtrFunc", "DialogPos_Y", ParaStr, ".\\Settings.ini");
}

/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */

/**************************************************************************************************
**  ��������:  OnInitDialog
**  ��������:  ��ʼ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
BOOL CDialogExtrafunct::OnInitDialog() 
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

/**************************************************************************************************
**  ��������:  PreTranslateMessage
**  ��������:  Ԥ������Ϣ
**  �������:  
**  ���ز���:  
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
**  ��������:  OnClose
**  ��������:  ����ر���Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogExtrafunct::OnClose() 
{
	ShowHideDlgWindow(FALSE);
	
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_EFDLGCLOSE, 0, 0);
	
	CDialog::OnClose();
}

