// MySScomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const CString RecordPath = "Record\\";                        // �����������ļ����ļ��е�·��

static const int Combo_Baud[9] = {2400, 4800, 9600, 19200, 38400, 57600, 76800, 115200, 153600};
static const int Combo_Data[4] = {5,    6,    7,    8};
static const int Combo_Stop[4] = {0,    1,    2,    3};

/////////////////////////////////////////////////////////////////////////////
// CMySScomDlg dialog

CMySScomDlg::CMySScomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySScomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMySScomDlg)
	m_Check_AutoSave = FALSE;
	m_Check_AutoSend = FALSE;
	m_Check_HexDspl = FALSE;
	m_Check_HexSend = FALSE;
	m_Edit_Recv = _T("");
	m_Edit_Send = _T("");
	m_Edit_Timer = _T("1000");
	m_Check_AutoClear = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySScomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMySScomDlg)
	DDX_Control(pDX, IDC_COMBO_STOP, m_Combo_Stop);
	DDX_Control(pDX, IDC_COMBO_DATA, m_Combo_Data);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_Combo_Baud);
	DDX_Control(pDX, IDC_COMBO_COMNO, m_Combo_ComNo);
	DDX_Check(pDX, IDC_CHECK_AUTOSAVE, m_Check_AutoSave);
	DDX_Check(pDX, IDC_CHECK_AUTOSEND, m_Check_AutoSend);
	DDX_Check(pDX, IDC_CHECK_HEXDSPL, m_Check_HexDspl);
	DDX_Check(pDX, IDC_CHECK_HEXSEND, m_Check_HexSend);
	DDX_Text(pDX, IDC_EDIT_RECV, m_Edit_Recv);
	DDX_Text(pDX, IDC_EDIT_SEND, m_Edit_Send);
	DDX_Text(pDX, IDC_EDIT_TIMER, m_Edit_Timer);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Check(pDX, IDC_CHECK_AUTOCLEAR, m_Check_AutoClear);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMySScomDlg, CDialog)
	//{{AFX_MSG_MAP(CMySScomDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ONOFF, OnButtonONOFF)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_RESPITE, OnButtonRespite)
	ON_BN_CLICKED(IDC_BUTTON_REIPUT, OnButtonReiput)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_CHECK_HEXDSPL, OnCheckHexDisplay)
	ON_BN_CLICKED(IDC_CHECK_AUTOSAVE, OnCheckAutoSave)
	ON_BN_CLICKED(IDC_CHECK_HEXSEND, OnCheckHexSend)
	ON_BN_CLICKED(IDC_CHECK_AUTOSEND, OnCheckAutoSend)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_BUTTON_COUNT, OnButtonCount)
	ON_BN_CLICKED(IDC_CHECK_AUTOCLEAR, OnCheckAutoClear)
	ON_BN_CLICKED(IDC_BUTTON_SRSEND, OnButtonSrSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CMySScomDlg, CDialog)
	//{{AFX_EVENTSINK_MAP(CMySScomDlg)
	ON_EVENT(CMySScomDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BEGIN_EASYSIZE_MAP(CMySScomDlg)
	EASYSIZE(IDC_STATIC_CONTROL, ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,        ES_BORDER,       0)
	EASYSIZE(IDC_STATIC_RECEIVE, IDC_STATIC_CONTROL, ES_BORDER,          ES_BORDER,          ES_BORDER,       0)
	EASYSIZE(IDC_STATIC_SEND,    IDC_STATIC_CONTROL, ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,       0)
	EASYSIZE(IDC_STATIC_SRSEND,  IDC_STATIC_RECEIVE, ES_BORDER,          ES_BORDER,          ES_BORDER,       0)
	EASYSIZE(IDC_EDIT_RECV,      ES_BORDER,          ES_BORDER,          ES_BORDER,          ES_BORDER,       0)
	EASYSIZE(IDC_EDIT_SEND,      ES_BORDER,          ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,       0)
	EASYSIZE(IDC_STATIC_LABLE,   ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	// ��������չ�������İ�ť�ؼ�����������
	EASYSIZE(IDC_BUTTON_SR01,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR02,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR03,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR04,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR05,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR06,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR07,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR08,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR09,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR10,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR11,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR12,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR13,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR14,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR15,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR16,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR17,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR18,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR19,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_BUTTON_SR20,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	// ��������չ�������ı༭��ؼ�����������
	EASYSIZE(IDC_EDIT_SR01,      ES_KEEPSIZE,        IDC_BUTTON_SR01,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR02,      ES_KEEPSIZE,        IDC_BUTTON_SR02,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR03,      ES_KEEPSIZE,        IDC_BUTTON_SR03,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR04,      ES_KEEPSIZE,        IDC_BUTTON_SR04,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR05,      ES_KEEPSIZE,        IDC_BUTTON_SR05,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR06,      ES_KEEPSIZE,        IDC_BUTTON_SR06,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR07,      ES_KEEPSIZE,        IDC_BUTTON_SR07,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR08,      ES_KEEPSIZE,        IDC_BUTTON_SR08,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR09,      ES_KEEPSIZE,        IDC_BUTTON_SR09,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR10,      ES_KEEPSIZE,        IDC_BUTTON_SR10,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR11,      ES_KEEPSIZE,        IDC_BUTTON_SR11,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR12,      ES_KEEPSIZE,        IDC_BUTTON_SR12,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR13,      ES_KEEPSIZE,        IDC_BUTTON_SR13,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR14,      ES_KEEPSIZE,        IDC_BUTTON_SR14,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR15,      ES_KEEPSIZE,        IDC_BUTTON_SR15,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR16,      ES_KEEPSIZE,        IDC_BUTTON_SR16,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR17,      ES_KEEPSIZE,        IDC_BUTTON_SR17,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR18,      ES_KEEPSIZE,        IDC_BUTTON_SR18,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR19,      ES_KEEPSIZE,        IDC_BUTTON_SR19,    ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SR20,      ES_KEEPSIZE,        IDC_BUTTON_SR20,    ES_BORDER,          ES_KEEPSIZE,     0)
	// ��������չ�������ĸ�ѡ��ؼ�����������
	EASYSIZE(IDC_CHECK_SR01,     ES_KEEPSIZE,        IDC_EDIT_SR01,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR02,     ES_KEEPSIZE,        IDC_EDIT_SR02,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR03,     ES_KEEPSIZE,        IDC_EDIT_SR03,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR04,     ES_KEEPSIZE,        IDC_EDIT_SR04,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR05,     ES_KEEPSIZE,        IDC_EDIT_SR05,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR06,     ES_KEEPSIZE,        IDC_EDIT_SR06,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR07,     ES_KEEPSIZE,        IDC_EDIT_SR07,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR08,     ES_KEEPSIZE,        IDC_EDIT_SR08,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR09,     ES_KEEPSIZE,        IDC_EDIT_SR09,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR10,     ES_KEEPSIZE,        IDC_EDIT_SR10,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR11,     ES_KEEPSIZE,        IDC_EDIT_SR11,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR12,     ES_KEEPSIZE,        IDC_EDIT_SR12,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR13,     ES_KEEPSIZE,        IDC_EDIT_SR13,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR14,     ES_KEEPSIZE,        IDC_EDIT_SR14,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR15,     ES_KEEPSIZE,        IDC_EDIT_SR15,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR16,     ES_KEEPSIZE,        IDC_EDIT_SR16,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR17,     ES_KEEPSIZE,        IDC_EDIT_SR17,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR18,     ES_KEEPSIZE,        IDC_EDIT_SR18,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR19,     ES_KEEPSIZE,        IDC_EDIT_SR19,      ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SR20,     ES_KEEPSIZE,        IDC_EDIT_SR20,      ES_BORDER,          ES_KEEPSIZE,     0)
END_EASYSIZE_MAP


/* ==================================== �Զ��庯����--��ʼ ===================================== */


// ����������ö�ٵ����ϴ��ڿ��õĴ���
BOOL CMySScomDlg::EnumComm()
{
	sPorts.RemoveAll();
	
	BOOL bSuccess = FALSE;
	
	HKEY hSERIALCOMM;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_QUERY_VALUE, &hSERIALCOMM) == ERROR_SUCCESS) {
		//Get the max value name and max value lengths
		DWORD dwMaxValueNameLen;
		DWORD dwMaxValueLen;
		DWORD dwQueryInfo = RegQueryInfoKey(hSERIALCOMM, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &dwMaxValueNameLen, &dwMaxValueLen, NULL, NULL);
		if (dwQueryInfo == ERROR_SUCCESS) {
			DWORD dwMaxValueNameSizeInChars = dwMaxValueNameLen + 1; //Include space for the NULL terminator
			DWORD dwMaxValueNameSizeInBytes = dwMaxValueNameSizeInChars * sizeof(TCHAR);
			DWORD dwMaxValueDataSizeInChars = dwMaxValueLen/sizeof(TCHAR) + 1; //Include space for the NULL terminator
			DWORD dwMaxValueDataSizeInBytes = dwMaxValueDataSizeInChars * sizeof(TCHAR);
			
			//Allocate some space for the value name and value data			
			TCHAR *szValueName;
			BYTE *byValue;
			if ((szValueName = (TCHAR *)malloc(dwMaxValueNameSizeInChars)) && (byValue = (BYTE *)malloc(dwMaxValueDataSizeInBytes)))
			{
				bSuccess = TRUE;
				
				//Enumerate all the values underneath HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM
				DWORD dwIndex = 0;
				DWORD dwType;
				DWORD dwValueNameSize = dwMaxValueNameSizeInChars;
				DWORD dwDataSize = dwMaxValueDataSizeInBytes;
				memset(szValueName, 0, dwMaxValueNameSizeInBytes);
				memset(byValue, 0, dwMaxValueDataSizeInBytes);
				LONG nEnum = RegEnumValue(hSERIALCOMM, dwIndex, szValueName, &dwValueNameSize, NULL, &dwType, byValue, &dwDataSize);
				while (nEnum == ERROR_SUCCESS)
				{
					//If the value is of the correct type, then add it to the array
					if (dwType == REG_SZ)
					{
						TCHAR* szPort = (TCHAR *)(byValue);
						sPorts.Add(szPort);	
					}
					
					//Prepare for the next time around
					dwValueNameSize = dwMaxValueNameSizeInChars;
					dwDataSize = dwMaxValueDataSizeInBytes;
					memset(szValueName, 0, dwMaxValueNameSizeInBytes);
					memset(byValue, 0, dwMaxValueDataSizeInBytes);
					++dwIndex;
					nEnum = RegEnumValue(hSERIALCOMM, dwIndex, szValueName, &dwValueNameSize, NULL, &dwType, byValue, &dwDataSize);
				}
				free(szValueName);
				free(byValue);
			}
			else {
				SetLastError(ERROR_OUTOFMEMORY);
			}
		}
		
		//Close the registry key now that we are finished with it    
		RegCloseKey(hSERIALCOMM);
		
		if (dwQueryInfo != ERROR_SUCCESS)
			SetLastError(dwQueryInfo);
	}
	
	return bSuccess;
}

void CMySScomDlg::SetControlStatus(bool Enable)
{
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_RESPITE)->EnableWindow(Enable);
	
	GetDlgItem(IDC_CHECK_HEXDSPL)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_AUTOCLEAR)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(Enable);
	
	GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
}

void CMySScomDlg::SetSendButtonStatus(bool Enable)
{
	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_RESPITE)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_REIPUT)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(Enable);
}

void CMySScomDlg::SetSendingStatus(bool Enable)
{
	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_RESPITE)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_REIPUT)->EnableWindow(Enable);

	GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
}

// ����һ�����ַ�ת��Ϊ��Ӧ��ʮ������ֵ�ĺ������ö�C�������϶������ҵ�
// ���ܣ�������0-F֮����ַ�����ת��Ϊ��Ӧ��ʮ�������ַ������򷵻�-1
char CMySScomDlg::ConvertHexChar(char ch) 
{
	if ((ch >= '0') && (ch <= '9')) {
        return (ch - 0x30);
	} else if ((ch >= 'A') && (ch <= 'F')) {
        return (ch - 'A' + 10);
    } else if ((ch >= 'a') && (ch <= 'f')) {
        return (ch - 'a' + 10);
    } else {
		return (-1);
	}
}

// �������ת�������ĸ�ʽ���ƣ��ڷ��Ϳ��е�ʮ�����ַ�Ӧ��ÿ�����ַ�֮�����һ���ո�
// �磺A1 23 45 0B 00 29
// CByteArray��һ����̬�ֽ�����
int CMySScomDlg::String2Hex(CString str, CByteArray &senddata)
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

CString CMySScomDlg::TransformtoHex(CString InputStr)
{
	CString TempCStr, ResultCStr;
	
	ResultCStr = "";
	
	for (int i = 0; i < InputStr.GetLength(); i++) {
		TempCStr.Format("%.2X ", InputStr[i]);
		TempCStr = TempCStr.Right(3);                                // ��ȡ�ұ���Чλ
		ResultCStr += TempCStr;
	}
	
	return ResultCStr;
}

void CMySScomDlg::SaveEditContent(void)
{
	CTime   NowTime  = CTime::GetCurrentTime();	                     // ��ȡ����ʱ��
	CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";
		
	CFile   MyFile;	                                                 // �����ļ���
		
	if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite)) {

		int nLength = StrRecved.GetLength();                         // �ļ�����
		MyFile.Write(StrRecved, nLength);                            // д���ı��ļ�
		MyFile.Close();	                                             // �ر��ļ�
	}
}

void CMySScomDlg::UpdateEditDisplay(void)
{
	if (m_Check_HexDspl) {                                           // �����Ҫ16������ʾ������ת��

		m_Edit_Recv = TransformtoHex(StrRecved);
		SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);          // �ñ༭�����ݹ��������һ��

		if (m_Check_AutoClear) {                                     // �����Ҫ�Զ��������

			if (m_Edit_Recv.GetLength() >= MAX_RECV_CHAR) {          // ��16����ģʽ�£����������ݳ��Ƚ����ж�
				
				if (m_Check_AutoSave) {

					SaveEditContent();                               // ���ȱ���༭�������
				}

				StrRecved   = "";
				m_Edit_Recv = "";
				SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);          // ��ձ༭������
			}
		}

	} else {                                                         // ����ֱ����ʾ��������

		m_Edit_Recv = StrRecved;
		SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);          // �ñ༭�����ݹ��������һ��

		if (m_Check_AutoClear) {                                     // �����Ҫ�Զ��������
			
			if (s_Edit_Recv->GetLineCount() >= MAX_RECV_LINE) {      // ���ַ�ģʽ�£����������������ж�
				
				if (m_Check_AutoSave) {
					
					SaveEditContent();                               // ���ȱ���༭�������
				}

				StrRecved   = "";
				m_Edit_Recv = "";
				SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);          // ��ձ༭������
			}
		}
	}
}

void CMySScomDlg::NeedAutoSendData(void)
{
	int Timer;
	CString TempStr;

	GetDlgItemText(IDC_EDIT_TIMER, TempStr);
	
	Timer = atoi((LPSTR)(LPCTSTR)TempStr);
	
	if ((Timer > 0) && (Timer <= 10000)) {

		SetTimer(Timer_No_AutoSend, Timer, NULL);                    // ������ʱ��

		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(false);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(false);

		m_Edit_Timer = TempStr;                                      // ���±༭������
		SetDlgItemText(IDC_EDIT_TIMER, m_Edit_Timer);

		SetSendButtonStatus(FALSE);                                  // ���÷�����������ť

	} else {

		MessageBox("��ʱʱ�������0��10����֮�䣬��ȷ�ϣ�     ", "��ʾ", MB_OK + MB_ICONEXCLAMATION);

		SetDlgItemText(IDC_EDIT_TIMER, m_Edit_Timer);                // ��ԭ�༭������

		m_Check_AutoSend = false;
		UpdateData(false);                                           // ȡ����ѡ��ѡ�е�״̬

		return;
	}
}

void CMySScomDlg::UpdateStatusBarNow(void)
{
	CTime   Nowtime;
	CString TempStr, DisplayStr;	
	
	Nowtime = CTime::GetCurrentTime();
	
	DisplayStr = m_PortOpened ? " �����Ѵ�" : " ����δ��";	
	m_StatusBar.SetPaneText(1, DisplayStr);

	DisplayStr.Format(" Recv: %.4d", RecvedData);
	m_StatusBar.SetPaneText(2, DisplayStr);

	DisplayStr.Format(" Send: %.4d", SendedData);
	m_StatusBar.SetPaneText(3, DisplayStr);

	DisplayStr = " ��ǰʱ��: " + Nowtime.Format("%Y-%m-%d") + " " + Nowtime.Format("%H:%M:%S");
	m_StatusBar.SetPaneText(4, DisplayStr);
}

void CMySScomDlg::InitiateStatusBar(void)
{
	static UINT indicators[] =
	{
		ID_SEPARATOR,
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
		ID_INDICATOR_OVR,
	};

	CTime   time;
	CString m_strTime;
	UINT    nID = 0;
	
	if (!m_StatusBar.Create(this) || !m_StatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT))) {
		TRACE0("Failed to create status barn");
		return;
	}

	time = CTime::GetCurrentTime();
	m_strTime = " ��ǰʱ��: " + time.Format("%Y-%m-%d") + " " + time.Format("%H:%M:%S");
	
	m_StatusBar.SetPaneInfo(0, nID, SBPS_STRETCH, 200);
	m_StatusBar.SetPaneText(0, " ��ӭʹ��MySScom - ��Ѹ�����з�һ��������");
	
	m_StatusBar.SetPaneInfo(1, nID, SBPS_NORMAL, 100);
	m_StatusBar.SetPaneText(1, " ����δ��");

	m_StatusBar.SetPaneInfo(2, nID, SBPS_NORMAL, 100);
	m_StatusBar.SetPaneText(2, " Recv: 0000");
	
	m_StatusBar.SetPaneInfo(3, nID, SBPS_NORMAL, 100);
	m_StatusBar.SetPaneText(3, " Send: 0000");

	m_StatusBar.SetPaneInfo(4, nID, SBPS_NORMAL, 200);
	m_StatusBar.SetPaneText(4, m_strTime);
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}

void CMySScomDlg::InitiateComboComs(void)
{
	EnumComm();                                                      // ö�ٿ��õĴ���

	for (int i = 0; i < sPorts.GetSize(); i++) {
		m_Combo_ComNo.AddString(sPorts.GetAt(i));
	}
}

void CMySScomDlg::InitiateComboBaud(void)
{
	CString TempStr;
	
	for (int i = 0; i < (sizeof(Combo_Baud) / sizeof(Combo_Baud[0])); i++) {

		TempStr.Format("%d bps", Combo_Baud[i]);

		m_Combo_Baud.AddString(TempStr);
	}
}

void CMySScomDlg::InitiateComboData(void)
{
	CString TempStr;
	
	for (int i = 0; i < (sizeof(Combo_Data) / sizeof(Combo_Data[0])); i++) {
		
		TempStr.Format("%d λ", Combo_Data[i]);
		
		m_Combo_Data.AddString(TempStr);
	}
}

void CMySScomDlg::InitiateComboStop(void)
{
	CString TempStr;
	
	for (int i = 0; i < (sizeof(Combo_Stop) / sizeof(Combo_Stop[0])); i++) {
		
		TempStr.Format("%d λ", Combo_Stop[i]);
		
		m_Combo_Stop.AddString(TempStr);
	}
}

void CMySScomDlg::InitiateMainFrame(void)
{
	CRect DialogMain;

	this->GetWindowRect(&DialogMain);                                // ��ȡ����������Ļ�ϵ�λ��

	this->MoveWindow((DialogMain.left), (DialogMain.top), (DialogMain.Width()), (DialogMain.Height()));
}

void CMySScomDlg::InitiateSrSendArea(void)
{
	m_SrSendEnable = FALSE;

	HideSrSendArea();                                                // Ĭ��״̬�²���ʾ�߼����͹���
}

void CMySScomDlg::SendEditDatatoComm(void)
{
	if (m_bSendPause == FALSE) {                                     // ȷ���Ƿ�����������

		GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);                  // ��ȡ�༭�������

		if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {              // ������ݳ��ȹ������л��������ݷ���ģʽ

			MessageBox("�ļ����ݽϴ󣬷��ͽ�����һ��ʱ�䣬�����ĵȴ�......      ", "��ʾ", MB_OK + MB_ICONINFORMATION);
						
			SetDlgItemText(IDC_BUTTON_SEND, "ȡ������");

			SetSendingStatus(FALSE);
			
			Send_Status  = SEND_LONG_FILE;
			Send_Counter = 0;

			SetTimer(Timer_No_SendFile, MAX_SEND_BYTE, NULL);        // ������ʱ������ȡǰN���ַ�����

			StrToSend = m_Edit_Send.Left(MAX_SEND_BYTE);
			Send_Counter++;

			m_ctrlComm.SetOutput(COleVariant(StrToSend));            // ����ASCII�ַ�����
			SendedData += StrToSend.GetLength();                     // �����ֽ����ۼ�

		} else {                                                     // �����л���С����ģʽ����ֹͣ��ʱ��
			
			Send_Status  = SEND_SHORT_DATA;
			KillTimer(Timer_No_SendFile);

			if (m_Check_HexSend) {                                   // �����Ҫ��16���Ʒ���
				
				CByteArray hexdata;
				int len;                                             // �˴����ص�len�������ڼ��㷢���˶��ٸ�ʮ��������
				
				len = String2Hex(m_Edit_Send, hexdata);
				
				m_ctrlComm.SetOutput(COleVariant(hexdata));          // ����ʮ����������
				
				SendedData += len;                                   // �����ֽ����ۼ�
				
			} else {
				
				m_ctrlComm.SetOutput(COleVariant(m_Edit_Send));      // ����ASCII�ַ�����
				
				SendedData += m_Edit_Send.GetLength();               // �����ֽ����ۼ�
			}
		}

		UpdateStatusBarNow();                                        // ����״̬��ͳ�����ݵ���ʾ
	}
}

void CMySScomDlg::ContinueToSendFile(void)
{
	if (m_bSendPause == FALSE) {                                     // ȷ���Ƿ�����������

		if (Send_Status == SEND_LONG_FILE) {
			
			Send_Counter++;
			
			if (m_Edit_Send.GetLength() >= (Send_Counter * MAX_SEND_BYTE)) {
				
				StrToSend = m_Edit_Send.Left(Send_Counter * MAX_SEND_BYTE);
				StrToSend = StrToSend.Right(MAX_SEND_BYTE);
				
			} else {                                                 // ��ȡ���һ�����ַ�����
				
				StrToSend = m_Edit_Send.Left(Send_Counter * MAX_SEND_BYTE);
				StrToSend = StrToSend.Right(MAX_SEND_BYTE - (Send_Counter * MAX_SEND_BYTE - m_Edit_Send.GetLength()));
				
				Send_Status = SEND_SHORT_DATA;                       // ������ϣ������л���С����ģʽ
				KillTimer(Timer_No_SendFile);                        // ֹͣ��ʱ��
			}
		} else {

			KillTimer(Timer_No_SendFile);                            // ֹͣ��ʱ��
		}
		
		m_ctrlComm.SetOutput(COleVariant(StrToSend));                // ����ASCII�ַ�����
		
		SendedData += StrToSend.GetLength();                         // �����ֽ����ۼ�
		
		UpdateStatusBarNow();                                        // ����״̬��ͳ�����ݵ���ʾ
	}
}

void CMySScomDlg::ShowSrSendCheck(bool Enable)
{
	GetDlgItem(IDC_CHECK_SR01)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR02)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR03)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR04)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR05)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR06)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR07)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR08)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR09)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR10)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR11)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR12)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR13)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR14)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR15)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR16)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR17)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR18)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR19)->ShowWindow(Enable);
	GetDlgItem(IDC_CHECK_SR20)->ShowWindow(Enable);
}

void CMySScomDlg::ShowSrSendEdit(bool Enable)
{
	GetDlgItem(IDC_EDIT_SR01)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR02)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR03)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR04)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR05)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR06)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR07)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR08)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR09)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR10)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR11)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR12)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR13)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR14)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR15)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR16)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR17)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR18)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR19)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SR20)->ShowWindow(Enable);
}

void CMySScomDlg::ShowSrSendButton(bool Enable)
{
	GetDlgItem(IDC_BUTTON_SR01)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR02)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR03)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR04)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR05)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR06)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR07)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR08)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR09)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR10)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR11)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR12)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR13)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR14)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR15)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR16)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR17)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR18)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR19)->ShowWindow(Enable);
	GetDlgItem(IDC_BUTTON_SR20)->ShowWindow(Enable);
}

void CMySScomDlg::HideSrSendArea(void)
{
	CRect DialogMain, RecvEdit, SendEdit;
	CRect RecvStatic, SendStatic, SrSdStatic;
	
	GetDlgItem(IDC_STATIC_RECEIVE)->GetWindowRect(&RecvStatic);
	GetDlgItem(IDC_STATIC_SEND)->GetWindowRect(&SendStatic);
	GetDlgItem(IDC_STATIC_SRSEND)->GetWindowRect(&SrSdStatic);
	
	GetDlgItem(IDC_EDIT_RECV)->GetWindowRect(&RecvEdit);
	GetDlgItem(IDC_EDIT_SEND)->GetWindowRect(&SendEdit);
	
	this->GetWindowRect(&DialogMain);                                // ��ȡ����������Ļ�ϵ�λ��
	
	GetDlgItem(IDC_STATIC_SRSEND)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_LABLE)->ShowWindow(FALSE);

	ShowSrSendCheck(FALSE);
	ShowSrSendEdit(FALSE);
	ShowSrSendButton(FALSE);
	
	GetDlgItem(IDC_STATIC_RECEIVE)->MoveWindow((RecvStatic.left - DialogMain.left - 4), 
											   (RecvStatic.top - DialogMain.top - 23), 
		                                       (RecvStatic.Width() + SrSdStatic.Width() + 10), 
											   (RecvStatic.Height()));
	
	GetDlgItem(IDC_EDIT_RECV)->MoveWindow((RecvEdit.left - DialogMain.left - 4), 
		                                  (RecvEdit.top - DialogMain.top - 23), 
		                                  (RecvEdit.Width() + SrSdStatic.Width() + 10), 
										  (RecvEdit.Height()));

	GetDlgItem(IDC_STATIC_SEND)->MoveWindow((SendStatic.left - DialogMain.left - 4), 
	                                        (SendStatic.top - DialogMain.top - 23), 
	                                        (SendStatic.Width() + SrSdStatic.Width() + 10), 
											(SendStatic.Height()));

	GetDlgItem(IDC_EDIT_SEND)->MoveWindow((SendEdit.left - DialogMain.left - 4), 
	                                      (SendEdit.top - DialogMain.top - 23), 
		                                  (SendEdit.Width() + SrSdStatic.Width() + 10), 
										  (SendEdit.Height()));
}

void CMySScomDlg::ShowSrSendArea(void)
{
	CRect DialogMain, RecvEdit, SendEdit;
	CRect RecvStatic, SendStatic, SrSdStatic;
	
	GetDlgItem(IDC_STATIC_RECEIVE)->GetWindowRect(&RecvStatic);
	GetDlgItem(IDC_STATIC_SEND)->GetWindowRect(&SendStatic);
	GetDlgItem(IDC_STATIC_SRSEND)->GetWindowRect(&SrSdStatic);
	
	GetDlgItem(IDC_EDIT_RECV)->GetWindowRect(&RecvEdit);
	GetDlgItem(IDC_EDIT_SEND)->GetWindowRect(&SendEdit);
	
	this->GetWindowRect(&DialogMain);                                // ��ȡ����������Ļ�ϵ�λ��
	
	GetDlgItem(IDC_STATIC_SRSEND)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_LABLE)->ShowWindow(TRUE);
	
	ShowSrSendCheck(TRUE);
	ShowSrSendEdit(TRUE);
	ShowSrSendButton(TRUE);
	
	GetDlgItem(IDC_STATIC_RECEIVE)->MoveWindow((RecvStatic.left - DialogMain.left - 4), 
											   (RecvStatic.top - DialogMain.top - 23), 
		                                       (RecvStatic.Width() - SrSdStatic.Width() - 10), 
											   (RecvStatic.Height()));
	
	GetDlgItem(IDC_EDIT_RECV)->MoveWindow((RecvEdit.left - DialogMain.left - 4), 
		                                  (RecvEdit.top - DialogMain.top - 23), 
		                                  (RecvEdit.Width() - SrSdStatic.Width() - 10), 
										  (RecvEdit.Height()));

	GetDlgItem(IDC_STATIC_SEND)->MoveWindow((SendStatic.left - DialogMain.left - 4), 
	                                        (SendStatic.top - DialogMain.top - 23), 
	                                        (SendStatic.Width() - SrSdStatic.Width() - 10), 
											(SendStatic.Height()));

	GetDlgItem(IDC_EDIT_SEND)->MoveWindow((SendEdit.left - DialogMain.left - 4), 
	                                      (SendEdit.top - DialogMain.top - 23), 
		                                  (SendEdit.Width() - SrSdStatic.Width() - 10), 
										  (SendEdit.Height()));
}


/* ==================================== �Զ��庯����--���� ===================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ================================== �����ؼ���Ϣ����--��ʼ =================================== */


void CMySScomDlg::OnButtonONOFF() 
{
	CString TempStr, SettingStr;
    
	if (m_PortOpened == true) {                                      // ��������Ѿ��򿪣���ôִ�йرղ���

		if (m_Check_AutoSend) {
			MessageBox("������ͣ���Զ����͹����ٳ��Թرմ���    ", "��ʾ", MB_OK + MB_ICONEXCLAMATION);
			return;
		}
		
		m_ctrlComm.SetPortOpen(FALSE);

		MessageBox("������   �ɹ��رմ���!   ������    ", "��ʾ", MB_OK + MB_ICONINFORMATION);

		SetDlgItemText(IDC_BUTTON_ONOFF, "�򿪴���");

		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DATA)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_STOP)->EnableWindow(TRUE);

		SetControlStatus(FALSE);

		RecvedData = 0;                                              // �ۼƵ�Ԫ����
		SendedData = 0;

		m_PortOpened = FALSE;

		return;
	}

	int Number = m_Combo_ComNo.GetCurSel();                          // �õ����ں�
	
	if (Number == 0) {
		MessageBox("���ںŶ�û��ѡ������Ҵ�ʲô����...��      ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        return;
    }
	
	if (m_ctrlComm.GetPortOpen()) {                                  // �ж��Ƿ��Ѿ���
        m_ctrlComm.SetPortOpen(FALSE);
	}
	
	m_Combo_ComNo.GetLBText(Number, TempStr);
	TempStr.TrimLeft("COM");                                         // ɾ��"COM"�ֶ�
	
	m_ctrlComm.SetCommPort(atoi(TempStr.Mid(0)));
	
    if (!m_ctrlComm.GetPortOpen()) {

        m_ctrlComm.SetPortOpen(TRUE);                                // ���Դ򿪴���

		MessageBox("������   �ɹ��򿪴���!   ������    ", "��ϲ", MB_OK + MB_ICONINFORMATION);

		SettingStr = "";
		
		int ComBaudSel = m_Combo_Baud.GetCurSel();                   // ��ȡ�����ʵ�ѡ����
		TempStr.Format("%d", Combo_Baud[ComBaudSel]);
		SettingStr += TempStr;
		
		SettingStr += ",n,";
		
		int ComDataSel = m_Combo_Data.GetCurSel();                   // ��ȡ����λ��ѡ����
		TempStr.Format("%d", Combo_Data[ComDataSel]);
		SettingStr += TempStr;
		
		SettingStr += ",";
		
		int ComStopSel = m_Combo_Stop.GetCurSel();                   // ��ȡֹͣλ��ѡ����
		TempStr.Format("%d", Combo_Stop[ComStopSel]);
		SettingStr += TempStr;
		
		m_ctrlComm.SetSettings(SettingStr);                          // ������(XXXX)����У�飬8������λ��1��ֹͣλ 
		
		m_ctrlComm.SetInputMode(1);                                  // 1��ʾ�Զ����Ʒ�ʽ��ȡ����
		m_ctrlComm.SetRThreshold(1);                                 // ����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
		m_ctrlComm.SetInputLen(0);                                   // ���õ�ǰ���������ݳ���Ϊ0
		m_ctrlComm.GetInput();                                       // ��Ԥ���������������������
		
		m_PortOpened = TRUE;
		
		SetControlStatus(TRUE);                                      // ���ø�����ť�ؼ�
		
		SetDlgItemText(IDC_BUTTON_ONOFF, "�رմ���");

		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);		

	} else {

        MessageBox("�򿪴���ʧ�ܣ��ô��ڿ�������ʹ����...    ", "��ʾ", MB_OK + MB_ICONERROR);
	}
}

void CMySScomDlg::OnButtonPause() 
{
	if (m_bRecvPause == FALSE) {
		m_bRecvPause = TRUE;
		SetDlgItemText(IDC_BUTTON_PAUSE, "��ͣ����");
		GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(TRUE);
	} else {
		m_bRecvPause = FALSE;
		SetDlgItemText(IDC_BUTTON_PAUSE, "�ָ�����");
		GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(FALSE);
	}
}

void CMySScomDlg::OnButtonClear() 
{
	StrRecved = "";
	
	m_Edit_Recv = "";
	SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);

	RecvedData = 0;
	UpdateStatusBarNow();                                            // ����״̬����ͳ��������ʾ
}

void CMySScomDlg::OnButtonSave() 
{
	CFile   MyFile;	                                                 // �����ļ���
	int     nLength;
	CString Temp_String;
	
	CTime   NowTime  = CTime::GetCurrentTime();	                     // ��ȡ����ʱ��
	CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt"; // ָ���ļ���
	
	GetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
	
	nLength = m_Edit_Recv.GetLength();                               // ��ȡ����
	
	if (nLength <= 0) {
		MessageBox("��δ���յ��κ����ݣ����뱣�棡          ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite) == 0) {
		Temp_String = "�ļ� " + FileName + " ����ʧ�ܣ�         ";
		MessageBox(Temp_String, "��Ǹ", MB_OK + MB_ICONWARNING);
		return;
	} else {
		Temp_String = "�ļ� " + FileName + " �����ɹ���         ";
		MessageBox(Temp_String, "��ϲ", MB_OK + MB_ICONINFORMATION);
	}
	
	MyFile.Write(m_Edit_Recv, nLength);	                             // д���ı��ļ�
	MyFile.Close();	                                                 // �ر��ļ�
}

void CMySScomDlg::OnButtonRead() 
{
	CFile myFile;

	if (m_Check_AutoSend) {
		MessageBox("�Զ����͹����ѿ���������ͣ��֮��    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	CFileDialog dlg(TRUE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		            "�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*|");
	
	if (dlg.DoModal() != IDOK) {
		return;
	}
	
	CString FilePath = dlg.GetPathName();						     // �����ļ���·��
		
	if (myFile.Open(FilePath, CFile::modeRead) == 0) {
		MessageBox("��ȡ�ļ�ʧ�ܣ���ȷ��·����ȷ���ļ�δ���ڴ�״̬��    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	myFile.SeekToBegin();
	
	int nLength = myFile.GetLength();
	char * TempStr = new char[nLength];							     // ����ռ�
	CString ResultStr;
	
	myFile.Read(TempStr, nLength);								     // ��ȡ�ļ�����
	myFile.Close();												     // �ر��ļ�
	
	ResultStr.Format(_T("%s"), TempStr);
	ResultStr = ResultStr.Left(nLength);
	
	nLength = s_Edit_Send->GetWindowTextLength();                    // ������ʾ
	s_Edit_Send->SetSel(nLength, nLength);
	s_Edit_Send->ReplaceSel(ResultStr);
	nLength += ResultStr.GetLength();
    m_Edit_Send = ResultStr;                                         // ��ʾ����
	SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
	
	delete []TempStr;											     // �ͷſռ�
}

void CMySScomDlg::OnButtonRespite() 
{
	if (m_bSendPause == TRUE) {
		m_bSendPause = FALSE;
		SetDlgItemText(IDC_BUTTON_RESPITE, "��ͣ����");
		GetDlgItem(IDC_BUTTON_READ)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	} else {
		m_bSendPause = TRUE;
		SetDlgItemText(IDC_BUTTON_RESPITE, "�ָ�����");
		GetDlgItem(IDC_BUTTON_READ)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	}
}

void CMySScomDlg::OnButtonReiput() 
{
	m_Edit_Send = "";
	SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);

	SendedData = 0;
	UpdateStatusBarNow();                                            // ����״̬����ͳ��������ʾ
}

void CMySScomDlg::OnButtonSend() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
	
	if (m_Edit_Send.GetLength() <= 0) {
		MessageBox("���ʹ�������Ϊ�գ�δ�����κ����ݣ�    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	GetDlgItemText(IDC_BUTTON_SEND, TempStr);

	if (TempStr == "��������") {
		SendEditDatatoComm();
	}
	
	if (TempStr == "ȡ������") {
		Send_Status  = SEND_SHORT_DATA;
		KillTimer(Timer_No_SendFile);
		Send_Counter = 0;

		SetSendingStatus(TRUE);

		SetDlgItemText(IDC_BUTTON_SEND, "��������");
	}
}

void CMySScomDlg::OnButtonCount() 
{
	RecvedData = 0;
	SendedData = 0;

	UpdateStatusBarNow();                                            // ����״̬����ͳ��������ʾ
}

void CMySScomDlg::OnButtonSrSend() 
{
	if (m_SrSendEnable == TRUE) {                                    // ����Ѿ����ø߼����͹��ܣ������֮
		HideSrSendArea();
		m_SrSendEnable = FALSE;
		SetDlgItemText(IDC_BUTTON_SRSEND, "�߼�����");
	} else {                                                         // ���û�����ø߼����͹��ܣ�������֮
		ShowSrSendArea();
		m_SrSendEnable = TRUE;
		SetDlgItemText(IDC_BUTTON_SRSEND, "��ͨ����");
	}
	
	INIT_EASYSIZE;                                                   // ���³�ʼ�������ؼ���λ��
}

void CMySScomDlg::OnCheckHexDisplay() 
{
	m_Check_HexDspl = !m_Check_HexDspl;

	UpdateEditDisplay();                                             // ������ʾ
}

void CMySScomDlg::OnCheckAutoClear() 
{
	m_Check_AutoClear = !m_Check_AutoClear;

	if (m_Check_AutoClear) {
		GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(TRUE);
	} else {
		GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(FALSE);
	}
}

void CMySScomDlg::OnCheckAutoSave() 
{
	m_Check_AutoSave = !m_Check_AutoSave;
}

void CMySScomDlg::OnCheckHexSend() 
{
	m_Check_HexSend = !m_Check_HexSend;
}

void CMySScomDlg::OnCheckAutoSend() 
{
	m_Check_AutoSend = !m_Check_AutoSend;

	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);

	if (m_Edit_Send.GetLength() <= 0) {
		MessageBox("ò�Ʒ�����Ϊ�հɣ��������������ҷ���ʲô������    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		m_Check_AutoSend = FALSE;
		UpdateData(FALSE);
		return;
	}

	if (m_Check_AutoSend) {

		if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {              // ȷ����������ݲ������

			MessageBox("����������ݹ������޷�һ�η�����ɡ����������������ļ���ʽ����......       ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			m_Check_AutoSend = FALSE;
			UpdateData(FALSE);
			return;
		}

		NeedAutoSendData();                                          // ��ʼ�����Զ���������

	} else {

		KillTimer(Timer_No_AutoSend);                                // �����û�ȡ�����Զ����͵Ĺ���
		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(true);

		SetSendButtonStatus(TRUE);                                   // �������÷�����������ť
	}
}


/* ================================== �����ؼ���Ϣ����--���� =================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */


void CMySScomDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMySScomDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CMySScomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	s_Edit_Recv = (CEdit*)GetDlgItem(IDC_EDIT_RECV);
	s_Edit_Send = (CEdit*)GetDlgItem(IDC_EDIT_SEND);

	InitiateStatusBar();

	InitiateComboComs();                                             // ��ʼ��ѡ�񴮿ںŵ��б��
	InitiateComboBaud();                                             // ��ʼ��ѡ�����ʵ��б��
	InitiateComboData();                                             // ��ʼ��ѡ������λ���б��
	InitiateComboStop();                                             // ��ʼ��ѡ��ֹͣλ���б��
	InitiateSrSendArea();                                            // ��ʼ������ʾ�߼�����������

	m_Combo_ComNo.SetCurSel(0);
	m_Combo_Baud.SetCurSel(2);
	m_Combo_Data.SetCurSel(3);
	m_Combo_Stop.SetCurSel(1);

	GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(FALSE);

	SetControlStatus(false);                                         // ���Ƚ��ø�����ť�ؼ�

	m_bRecvPause = TRUE;
	m_bSendPause  = FALSE;
	m_PortOpened  = FALSE;

	StrRecved = "";
	StrToSend = "";

	Send_Status  = SEND_SHORT_DATA;
	Send_Counter = 0;

	RecvedData = 0;
	SendedData = 0;

	CreateDirectory(RecordPath, NULL);                               // ����Record�ļ��У����ڱ�������

	SetTimer(Timer_No_StatusBar, 1000, NULL);
	
	// CG: The following block was added by the ToolTips component.
	{
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		m_tooltip.AddTool(GetDlgItem(IDC_COMBO_COMNO),     IDS_STRING_001);
		m_tooltip.AddTool(GetDlgItem(IDC_COMBO_BAUD),      IDS_STRING_002);
		m_tooltip.AddTool(GetDlgItem(IDC_COMBO_DATA),      IDS_STRING_003);
		m_tooltip.AddTool(GetDlgItem(IDC_COMBO_STOP),      IDS_STRING_004);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_ONOFF),    IDS_STRING_005);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_PAUSE),    IDS_STRING_006);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_CLEAR),    IDS_STRING_007);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SAVE),     IDS_STRING_008);
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK_HEXDSPL),   IDS_STRING_009);
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOCLEAR), IDS_STRING_010);
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOSAVE),  IDS_STRING_011);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_READ),     IDS_STRING_012);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_RESPITE),  IDS_STRING_013);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_REIPUT),   IDS_STRING_014);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SEND),     IDS_STRING_015);
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK_HEXSEND),   IDS_STRING_016);
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOSEND),  IDS_STRING_017);
		m_tooltip.AddTool(GetDlgItem(IDC_EDIT_TIMER),      IDS_STRING_018);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_COUNT),    IDS_STRING_019);
		m_tooltip.AddTool(GetDlgItem(IDC_EDIT_RECV),       IDS_STRING_020);
		m_tooltip.AddTool(GetDlgItem(IDC_EDIT_SEND),       IDS_STRING_021);
	}

	INIT_EASYSIZE;

	InitiateMainFrame();

	return TRUE;
}

void CMySScomDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == Timer_No_StatusBar) {                            // ״̬����ʱ����
		UpdateStatusBarNow();
	} else if (nIDEvent == Timer_No_AutoSend) {                      // �Զ����Ͷ�����
		SendEditDatatoComm();
	} else if (nIDEvent == Timer_No_SendFile) {                      // ���ڷ����ļ�״̬
		ContinueToSendFile();
	} else {
		return;
	}
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CMySScomDlg::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CMySScomDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	UPDATE_EASYSIZE;

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);      // ͬ��״̬����λ��
}

void CMySScomDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);

	EASYSIZE_MINSIZE(850, 522, fwSide, pRect);                       // ���ƴ������С�ߴ�
}

void CMySScomDlg::OnOnCommMscomm() 
{
	VARIANT       Input_Vrt;
    COleSafeArray Input_Ary;
    LONG RecvLen, i;
    BYTE RecvData[2048];                                             // ����BYTE����
    CString TempStr;

	if (m_PortOpened == FALSE) {
		return;
	}
	
    if (m_ctrlComm.GetCommEvent() == 2) {                            // �¼�ֵΪ2��ʾ���ջ����������ַ�

        Input_Vrt = m_ctrlComm.GetInput();                           // ��������
        Input_Ary = Input_Vrt;                                       // VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
        RecvLen   = Input_Ary.GetOneDimSize();                       // �õ���Ч���ݳ���
        
		for (i = 0; i < RecvLen; i++) {
            Input_Ary.GetElement(&i, RecvData + i);                  // ת��ΪBYTE�������ŵ�RecvData����
		}

		if (m_bRecvPause == FALSE) {                                 // �����ͣ�����ˣ��򲻴洢���ݣ�ֱ�ӷ���
			return;
		}
		
        for (i = 0; i < RecvLen; i++) {                              // ������ת��ΪCstring�ͱ���

            BYTE bt = *(char *)(RecvData + i);                       // ת��Ϊ�ַ���

			TempStr.Format("%c", bt);
			StrRecved += TempStr;                                    // ������������
			
			RecvedData++;                                            // �����ֽ����ۼ�
        }

		StrRecved.Left(RecvLen);
		
		UpdateEditDisplay();                                         // ���±༭��������ʾ

		UpdateStatusBarNow();                                        // ����״̬��ͳ�����ݵ���ʾ
    }
}


