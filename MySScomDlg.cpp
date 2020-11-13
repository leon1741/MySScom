// MySScomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const CString RecordPath = "Record\\";                        // �����������ļ����ļ��е�·��

static const int    Combo_Baud[12] = {600,  1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
static const int    Combo_Data[4]  = {5,    6,    7,    8};
static const double Combo_Stop[4]  = {1,    1.5,  2};
static const int    Combo_Check[5] = {0,    1,    2,    3,   4};

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
	m_Check_AutoClear = FALSE;
	m_Edit_Recv = _T("");
	m_Edit_Send = _T("");
	m_Edit_AutoTimer = _T("");
    m_Edit_Lines = _T("1000");
	m_Check_Return = FALSE;
	m_Check_ShowTime = FALSE;
	m_NeedTime = TRUE;
	m_DataRecvd = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	AfxInitRichEdit();                                               // ��ʼ��RichEdit�ؼ�
}

void CMySScomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMySScomDlg)
	DDX_Control(pDX, IDC_COMBO_CHECK, m_Combo_Check);
	DDX_Control(pDX, IDC_COMBO_STOP, m_Combo_Stop);
	DDX_Control(pDX, IDC_COMBO_DATA, m_Combo_Data);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_Combo_Baud);
	DDX_Control(pDX, IDC_COMBO_COMNO, m_Combo_ComNo);
	DDX_Check(pDX, IDC_CHECK_AUTOSAVE, m_Check_AutoSave);
	DDX_Check(pDX, IDC_CHECK_AUTOSEND, m_Check_AutoSend);
	DDX_Check(pDX, IDC_CHECK_HEXDSPL, m_Check_HexDspl);
	DDX_Check(pDX, IDC_CHECK_HEXSEND, m_Check_HexSend);
	DDX_Check(pDX, IDC_CHECK_AUTOCLEAR, m_Check_AutoClear);
	DDX_Text(pDX, IDC_EDIT_RECV, m_Edit_Recv);
	DDX_Text(pDX, IDC_EDIT_SEND, m_Edit_Send);
	DDX_Text(pDX, IDC_EDIT_TIMER, m_Edit_AutoTimer);
	DDX_Text(pDX, IDC_EDIT_LINES, m_Edit_Lines);
	DDX_Check(pDX, IDC_CHECK_RETURN, m_Check_Return);
	DDX_Check(pDX, IDC_CHECK_SHOWTIME, m_Check_ShowTime);
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
	ON_WM_CLOSE()
	ON_COMMAND(IDC_MENU_TRAY_EXIT, OnMenuTrayExit)
	ON_COMMAND(IDC_MENU_TRAY_HIDE, OnMenuTrayHide)
	ON_COMMAND(IDC_MENU_TRAY_SHOW, OnMenuTrayShow)
	ON_MESSAGE(MYWM_NOTIFYICON, OnMyIconNotify)
	ON_BN_CLICKED(IDC_CHECK_RETURN, OnCheckReturn)
	ON_BN_CLICKED(IDC_CHECK_SHOWTIME, OnCheckShowTime)
	ON_COMMAND(IDC_MENU_TRAY_ABOUT, OnMenuTrayAbout)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_SRSEND, OnButtonSrSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CMySScomDlg, CDialog)
	//{{AFX_EVENTSINK_MAP(CMySScomDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BEGIN_EASYSIZE_MAP(CMySScomDlg)
	EASYSIZE(IDC_STATIC_CONTROL, ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,        ES_BORDER,       0)
	EASYSIZE(IDC_STATIC_RECEIVE, IDC_STATIC_CONTROL, ES_BORDER,          ES_BORDER,          ES_BORDER,       0)
	EASYSIZE(IDC_STATIC_SEND,    IDC_STATIC_CONTROL, ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,       0)
	EASYSIZE(IDC_EDIT_RECV,      ES_BORDER,          ES_BORDER,          ES_BORDER,          ES_BORDER,       0)
	EASYSIZE(IDC_EDIT_SEND,      ES_BORDER,          ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,       0)
	EASYSIZE(IDC_BUTTON_HELP,    ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,        ES_BORDER,       0)
	EASYSIZE(IDC_BUTTON_SEND,    ES_KEEPSIZE,        ES_KEEPSIZE,        ES_BORDER,          IDC_STATIC_SEND, 0)
END_EASYSIZE_MAP


/* ==================================== �Զ��庯����--��ʼ ===================================== */

/**************************************************************************************************
**  ��������:  SPCommProc
**  ��������:  �����̴߳�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
UINT SPCommProc(LPVOID pParam)
{
    OVERLAPPED os;
    DWORD dwMask, dwTrans;
    COMSTAT ComStat;
    DWORD dwErrorFlags;
    char buf[MAXBLOCK / 4];
    DWORD length;
    CString str;
    
    CMySScomDlg *pDlg = (CMySScomDlg *)pParam;
    
    memset(&os, 0, sizeof(OVERLAPPED));
    
    os.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);                          /* �����¼��ں˶��� */
    
    if (os.hEvent == NULL) {                                                   /* ����ʧ�� */
        AfxMessageBox("Can't create event object!");
        return -1;
    }
    
    while (pDlg->m_PortOpened) {
        
        ClearCommError(pDlg->m_hSPCom, &dwErrorFlags, &ComStat);               /* ̽ѯ���ڻ����� */
        
        if (ComStat.cbInQue) {                                                 /* ������ն��в�Ϊ�� */
            
            length = pDlg->ReadComm(buf, MAX_SEND_BYTE);                       /* ��ȡ1024���ֽڵ����� */
            
            pDlg->HandleUSARTData(buf, length);                                /* ֪ͨ�����̴��������� */
        }
        
        dwMask = 0;
        
        if (!WaitCommEvent(pDlg->m_hSPCom, &dwMask, &os)) {                    /* �жϴ���ͨ���¼��Ƿ��Ѿ����� */
            
            if (GetLastError() == ERROR_IO_PENDING) {                          /* �ж��Ƿ�������ݵȴ����� */
                GetOverlappedResult(pDlg->m_hSPCom, &os, &dwTrans, TRUE);
            } else {                                                           /* �ر��¼��ں˶��� */
                CloseHandle(os.hEvent);
                return -1;
            }
        }
    }
    
    CloseHandle(os.hEvent);                                                    /* �ر��¼��ں˶��� */
    
    return 0;
}

/**************************************************************************************************
**  ��������:  EnumComm
**  ��������:  ����������ö�ٵ����ϴ��ڿ��õĴ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
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

/**************************************************************************************************
**  ��������:  ReadComm
**  ��������:  �Ӵ��ڻ�ȡ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
DWORD CMySScomDlg::ReadComm(char *buf, DWORD dwLength)
{
    DWORD length = 0;
    COMSTAT ComStat;
    DWORD dwErrorFlags;

    ClearCommError(m_hSPCom, &dwErrorFlags, &ComStat);                         /* ������������־ */

    length = min(dwLength, ComStat.cbInQue);

    ReadFile(m_hSPCom, buf, length, &length, &m_osRead);                       /* ��ȡ�������� */

    return length;
}

/**************************************************************************************************
**  ��������:  WriteComm
**  ��������:  �򴮿ڷ�������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
DWORD CMySScomDlg::WriteComm(char *buf, DWORD dwLength)
{
    DWORD length = dwLength;
    COMSTAT ComStat;
    DWORD dwErrorFlags;

    ClearCommError(m_hSPCom, &dwErrorFlags, &ComStat);                         /* ������������־ */

    WriteFile(m_hSPCom, buf, length, &length, &m_osWrite);                     /* д�봮������ */

    if (GetLastError() == ERROR_IO_PENDING) {                                  /* ���ڴ����ص��Ĳ��֣���ȡ�䳤�� */
        GetOverlappedResult(m_hSPCom, &m_osWrite, &length, TRUE);
    } else {                                                                   /* ���򣬷���ʧ�ܣ�����0 */
        length = 0;
    }

    return length;
}

/**************************************************************************************************
**  ��������:  SetControlStatus
**  ��������:  ���ÿؼ���״̬
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::SetControlStatus(bool Enable)
{
    GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(Enable);
    GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(Enable);
    
    GetDlgItem(IDC_CHECK_HEXDSPL)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_AUTOCLEAR)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(Enable);

    if ((!m_Check_AutoClear) || (!Enable)) {
        GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(FALSE);
    } else {
        GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(TRUE);
    }

    GetDlgItem(IDC_CHECK_SHOWTIME)->EnableWindow(Enable);

    GetDlgItem(IDC_STATIC_OVER)->EnableWindow(Enable);
    GetDlgItem(IDC_STATIC_LINES)->EnableWindow(Enable);
    GetDlgItem(IDC_EDIT_LINES)->EnableWindow(Enable);
    
    GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(Enable);
    GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_RETURN)->EnableWindow(Enable);

	GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(Enable);
}

/**************************************************************************************************
**  ��������:  SetSendButtonStatus
**  ��������:  ���÷��Ͱ�ť��״̬
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::SetSendButtonStatus(bool Enable)
{
    GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(Enable);
}

/**************************************************************************************************
**  ��������:  SetSendingStatus
**  ��������:  
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::SetSendingStatus(bool Enable)
{
    GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(Enable);
    GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
}

/**************************************************************************************************
**  ��������:  SwitchSendStatus
**  ��������:  �л�����״̬
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::SwitchSendStatus(bool IsNormal)
{
    GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(IsNormal);
    GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(IsNormal);
    GetDlgItem(IDC_STATIC_MS)->EnableWindow(IsNormal);
}

/**************************************************************************************************
**  ��������:  ConvertHexChar
**  ��������:  ������0-F֮����ַ�����ת��Ϊ��Ӧ��ʮ�������ַ������򷵻�-1
**  �������:  
**  ���ز���:  
**************************************************************************************************/
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

/**************************************************************************************************
**  ��������:  String2Hex
**  ��������:  �ַ���ת��Ϊ16��������
**  �������:  
**  ���ز���:  
**  ע������:  �������ת�������ĸ�ʽ���ƣ��ڷ��Ϳ��е�ʮ�����ַ�Ӧ��ÿ�����ַ�֮�����һ���ո�
**************************************************************************************************/
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

/**************************************************************************************************
**  ��������:  TransformtoHex
**  ��������:  �ַ���ת��Ϊ16����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
CString CMySScomDlg::TransformtoHex(CString InputStr)
{
    CString TempCStr, ResultCStr;
    
    ResultCStr = "";
    
    for (int i = 0; i < InputStr.GetLength(); i++) {
        TempCStr.Format("%.2X ", InputStr[i]);
        TempCStr = TempCStr.Right(3);                                          /* ��ȡ�ұ���Чλ */
        ResultCStr += TempCStr;
    }
    
    return ResultCStr;
}

/**************************************************************************************************
**  ��������:  CharisValid
**  ��������:  �ж��ַ��Ƿ�Ϸ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CMySScomDlg::CharisValid(unsigned char inchar)
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
**  ��������:  InformDlgClose
**  ��������:  ����߼����ʹ��ڵ���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InformDlgClose(void)
{
	SetDlgItemText(IDC_BUTTON_SRSEND, "�߼�����");
	
	GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
}

/**************************************************************************************************
**  ��������:  SaveEditContent
**  ��������:  ����༭������ݵ��ı��ļ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::SaveEditContent(void)
{
    CTime   NowTime  = CTime::GetCurrentTime();                                /* ��ȡ����ʱ�� */
    CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";
        
    CFile   MyFile;                                                            /* �����ļ��� */
        
    if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite)) {

        int nLength = StrRecved.GetLength();                                   /* �ļ����� */
        MyFile.Write(StrRecved, nLength);                                      /* д���ı��ļ� */
        MyFile.Close();                                                        /* �ر��ļ� */
    }
}

/**************************************************************************************************
**  ��������:  UpdateEditDisplay
**  ��������:  ���±༭�����ʾ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::UpdateEditDisplay(void)
{
    CWnd *hwnd;
    
    if (m_Check_HexDspl) {                                                     /* �����Ҫ16������ʾ������ת�� */

        m_Edit_Recv = TransformtoHex(StrRecved);
        SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
        s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);                    /* �ñ༭�����ݹ��������һ�� */

        if (m_Check_AutoClear) {                                               /* �����Ҫ�Զ�������� */

            if (RecvedData >= MaxRecvLines) {                                  /* ��16����ģʽ�£����������ݳ��Ƚ����ж� */

                RecvedLine = 0;                                                /* ������ձ���ֵ */
                RecvedData = 0;
                
                if (m_Check_AutoSave) {
                    SaveEditContent();                                         /* ����༭������� */
                }

                StrRecved   = "";
                m_Edit_Recv = "";
                SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);                    /* ��ձ༭������ */
            }
        }

    } else {                                                                   /* ����ֱ����ʾ�������� */

        m_Edit_Recv = StrRecved;
        SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
        s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);                    /* �ñ༭�����ݹ��������һ�� */

        if (m_Check_AutoClear) {                                               /* �����Ҫ�Զ�������� */
            
            if (RecvedLine >= MaxRecvLines) {                                  /* ���ַ�ģʽ�£����������������ж� */

                RecvedLine = 0;                                                /* ������ձ���ֵ */
                RecvedData = 0;

                if (m_Check_AutoSave) {
                    SaveEditContent();                                         /* ����༭������� */
                }

                StrRecved   = "";
                m_Edit_Recv = "";
                SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);                    /* ��ձ༭������ */
            }
        }
    }

    /*************************************************************************************************\
    |                          �������ʵ�ֶԽ��ձ༭��������������������                           |
    \*************************************************************************************************/
    
    hwnd = GetDlgItem(IDC_EDIT_RECV);                                          /* ��ȡ���ձ༭��Ŀؼ�ID */

    if (GetFocus() == hwnd) {                                                  /* �����ڽ���ת�������ͱ༭�� */
        GetDlgItem(IDC_EDIT_SEND)->SetFocus();
    }
}

/**************************************************************************************************
**  ��������:  HandleUSARTData
**  ��������:  ���մ�������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::HandleUSARTData(char *ptr, DWORD len)
{
    DWORD i;
    CString TempStr, TimeStr;
    CTime NowTime;

    if (m_bRecvPause == TRUE) return;

    for (i = 0; i < len; i++) {                                                /* ������ת��ΪCstring�ͱ��� */
        
        #if 0                                                                  /* ���·�ʽΪ��ͨ��ʾģʽ(�����16������ʾģʽ��0x00�Ķ�ʧ) */

        TempStr.Format("%c", ptr[i]);

        #else                                                                  /* ���·�ʽ���Դ���0�ַ�����ʾbug�����ǻ�����ַ�ģʽ�¶�ʧ0x00�ַ����ȫ������ */

        if (ptr[i] == 0) {
            TempStr = CString(ptr[i]);
        } else {
            TempStr.Format("%c", ptr[i]);
        }

        #endif
        
        if (m_Check_ShowTime == TRUE) {                                        /* ֻ��������ʱ����ʾ����ʱ���ж� */
            
            if (TempStr == "\n") {                                             /* ���ν��յ��˻س������л�����һ����ʾ */
                m_NeedTime = TRUE;
                RecvedLine++;

            } else {
                if (m_NeedTime == TRUE) {
                    NowTime = CTime::GetCurrentTime();                         /* ��ȡ����ʱ�� */
                    TimeStr = NowTime.Format("[%H:%M:%S] ");
                    
                    StrRecved += TimeStr;                                      /* ����ͷ��ʾʱ�� */
                    m_NeedTime = FALSE;
                }
            }
        } else {                                                               /* ����Ҫ����ͷλ����ʾʱ�� */
            
            if (m_Check_HexDspl == FALSE) {                                    /* ��ǰ������16������ʾģʽ */
                
                if (TempStr == "\n") {                                         /* ���ν��յ��س��� */
                    RecvedLine++;
                }
            } else {
                
                RecvedLine = 0;                                                /* 16����ģʽ�²������ж� */
            }
        }
        
        StrRecved += TempStr;                                                  /* ������������ */
        RecvedData++;                                                          /* �����ֽ����ۼ� */
    }

    m_DataRecvd = TRUE;
}

/**************************************************************************************************
**  ��������:  NeedAutoSendData
**  ��������:  ������ʱ�������ݵĹ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::NeedAutoSendData(void)
{
    int Timer;
    CString TempStr;

    GetDlgItemText(IDC_EDIT_TIMER, TempStr);
    
    Timer = atoi((LPSTR)(LPCTSTR)TempStr);
    
    if ((Timer > 0) && (Timer <= 100000)) {

        SetTimer(Timer_No_AutoSend, Timer, NULL);                              /* ������ʱ�� */

        GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);

        m_Edit_AutoTimer = TempStr;                                            /* ���±༭������ */
        SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);

        SetSendButtonStatus(FALSE);                                            /* ���÷�����������ť */

    } else {

        MessageBox("��ʱʱ�������0��100����֮�䣬��ȷ�ϣ�  ", "��ʾ", MB_OK + MB_ICONEXCLAMATION);

        SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);                      /* ��ԭ�༭������ */

        m_Check_AutoSend = FALSE;
        UpdateData(FALSE);                                                     /* ȡ����ѡ��ѡ�е�״̬ */

        return;
    }
}

/**************************************************************************************************
**  ��������:  UpdateStatusBarNow
**  ��������:  ����״̬������ʾ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::UpdateStatusBarNow(void)
{
    CTime   Nowtime;
    CString TempStr, DisplayStr;
    CRect   DialogMain;

    this->GetWindowRect(&DialogMain);                                          /* ��ȡ����������Ļ�ϵ�λ�� */

	if (DialogMain.Width() > 1260) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з�һ�������� - Designed By LEON (LEON1741@126.com) - �����ڲ�������лл��";
	} else if (DialogMain.Width() > 1160) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з�һ�������� - Designed By LEON (LEON1741@126.com)";
	} else if (DialogMain.Width() > 1080) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з�һ�������� - Designed By LEON";
	} else if (DialogMain.Width() > 1000) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з�һ�������� - LEON";
	} else if (DialogMain.Width() > 950) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з�һ��������";
	} else if (DialogMain.Width() > 900) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з�һ��";
	} else if (DialogMain.Width() > 840) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ����";
	} else {
		DisplayStr = " ��ӭʹ��MySScom";
	}

	m_StatusBar.SetPaneText(0, DisplayStr);
    
    Nowtime = CTime::GetCurrentTime();
    
    DisplayStr = m_PortOpened ? " �����Ѵ�" : " ����δ��";  
    m_StatusBar.SetPaneText(1, DisplayStr);

    DisplayStr.Format(" Lines: %.5d", RecvedLine);
    m_StatusBar.SetPaneText(2, DisplayStr);
        
    DisplayStr.Format(" Recv: %.6d", RecvedData);
    m_StatusBar.SetPaneText(3, DisplayStr);

    DisplayStr.Format(" Send: %.6d", SendedData);
    m_StatusBar.SetPaneText(4, DisplayStr);

    DisplayStr = " ��ǰʱ��: " + Nowtime.Format("%Y-%m-%d") + " " + Nowtime.Format("%H:%M:%S");
    m_StatusBar.SetPaneText(5, DisplayStr);
}

/**************************************************************************************************
**  ��������:  SendDatatoComm
**  ��������:  ��ָ�����ַ������ͳ�ȥ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CMySScomDlg::SendDatatoComm(CString datastr, BOOL needhex)
{
	int i;
	unsigned char tchar;
	char temp[MAX_SEND_BYTE];
	
	if (datastr.GetLength() > MAX_SEND_BYTE) {                                 /* ���ݳ��ȹ��� */
        return FALSE;
    }
	
    if (needhex) {                                                             /* �����Ҫ��16���Ʒ��� */

		for (i = 0; i <= datastr.GetLength(); ) {                              /* �ж��������ݵ��ַ��Ƿ�Ϸ� */

			tchar = datastr[i++];                                              /* �жϵ�1���ַ��Ƿ���Ч */
			
			if (!CharisValid(tchar)) {
				return FALSE;
			}
			
			tchar = datastr[i++];                                              /* �жϵ�2���ַ��Ƿ���Ч */
			
			if (!CharisValid(tchar)) {
				return FALSE;
			}
			
			if (i >= datastr.GetLength() - 1) {                                /* ��������һ�����ݣ�����Ҫ�ж���ո� */
				break;
			}
			
			tchar = datastr[i++];                                              /* �жϵ�3���ַ��Ƿ�Ϊ�ո� */
			
			if (tchar != ' ') {
				return FALSE;
			}
		}
        
        CByteArray hexdata;
        int j, len;                                                            /* �˴����ص�len�������ڼ��㷢���˶��ٸ�ʮ�������� */
		
        len = String2Hex(datastr, hexdata);
		
        for (j = 0; j < len; j++) {
            temp[j] = hexdata.GetAt(j);
        }
        
        WriteComm(temp, len);
		
        SendedData += len;                                                     /* �����ֽ����ۼ� */
        
    } else {
        
        strncpy(temp, (LPCTSTR)datastr, sizeof(temp));
        
        WriteComm(temp, datastr.GetLength());
		
        SendedData += datastr.GetLength();                                     /* �����ֽ����ۼ� */
    }
	
    if (m_Check_Return) {                                                      /* �����س����з� */
		
        temp[0] = '\r';
        temp[1] = '\n';
        
        WriteComm(temp, 2);
		
        SendedData += 2;
    }
	
    UpdateStatusBarNow();                                                      /* ����״̬��ͳ�����ݵ���ʾ */

	return TRUE;
}

/**************************************************************************************************
**  ��������:  CreateSettingFile
**  ��������:  ���������ļ�����д��Ĭ�ϲ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::CreateSettingFile(void)
{
    // ��������ж�Ŀ¼���Ƿ����INI�ļ������������򴴽����ļ���д��Ĭ��ֵ

    if (!(::GetPrivateProfileInt("SystemInfo", "Created", 0, ".\\Settings.ini"))) {

        ::WritePrivateProfileString("SystemInfo", "Created",  "1",     ".\\Settings.ini");
        
        ::WritePrivateProfileString("PortConfig", "CommPort",  "0",     ".\\Settings.ini");
        ::WritePrivateProfileString("PortConfig", "BaudRate",  "4",     ".\\Settings.ini");
        ::WritePrivateProfileString("PortConfig", "DataBits",  "3",     ".\\Settings.ini");
        ::WritePrivateProfileString("PortConfig", "CheckBits", "0",     ".\\Settings.ini");
        ::WritePrivateProfileString("PortConfig", "StopBits",  "1",     ".\\Settings.ini");

        ::WritePrivateProfileString("RecvConfig", "HexDispl", "0",     ".\\Settings.ini");
        ::WritePrivateProfileString("RecvConfig", "AutoClar", "0",     ".\\Settings.ini");
        ::WritePrivateProfileString("RecvConfig", "AutoSave", "0",     ".\\Settings.ini");

        ::WritePrivateProfileString("RecvConfig", "ShowTime", "1",     ".\\Settings.ini");

        ::WritePrivateProfileString("SendConfig", "HexaSend", "0",     ".\\Settings.ini");
        ::WritePrivateProfileString("SendConfig", "AutoTime", "1000",  ".\\Settings.ini");
 
        ::WritePrivateProfileString("SendConfig", "AddReturn", "0",    ".\\Settings.ini");

        ::WritePrivateProfileString("SendConfig", "SendData",  "",     ".\\Settings.ini");

		::WritePrivateProfileString("SrSendArea", "SrHexa01",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa02",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa03",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa04",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa05",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa06",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa07",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa08",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa09",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa10",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa11",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa12",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa13",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa14",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa15",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa16",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa17",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa18",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa19",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa20",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa21",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa22",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa23",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa24",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa25",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa26",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa27",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa28",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa29",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa30",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa31",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa32",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa33",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa34",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa35",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa36",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa37",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa38",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa39",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrHexa40",  "",     ".\\Settings.ini");
		
		::WritePrivateProfileString("SrSendArea", "SrData01",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData02",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData03",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData04",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData05",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData06",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData07",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData08",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData09",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData10",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData11",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData12",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData13",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData14",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData15",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData16",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData17",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData18",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData19",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData20",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData21",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData22",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData23",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData24",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData25",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData26",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData27",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData28",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData29",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData30",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData31",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData32",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData33",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData34",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData35",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData36",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData37",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData38",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData39",  "",     ".\\Settings.ini");
		::WritePrivateProfileString("SrSendArea", "SrData40",  "",     ".\\Settings.ini");
		
		::WritePrivateProfileString("SrSendArea", "LoopTime",  "1000", ".\\Settings.ini");
	}
}

/**************************************************************************************************
**  ��������:  InitiateAllParas
**  ��������:  ��ȡ�����ļ��ĸ����������ݲ���ʼ���Ի����ֵ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateAllParas(void)
{
    int  TempData;                                                             /* ��Ҫע����ǣ��Զ�����ʹ�ܺ�ѭ������ʹ�����������ʼ�� */
    char TempStr[MAX_LOOP_BYTE];
    CString TempPara;

    TempData = (::GetPrivateProfileInt("PortConfig", "CommPort",  0, ".\\Settings.ini"));
    m_Combo_ComNo.SetCurSel(TempData);
    TempData = (::GetPrivateProfileInt("PortConfig", "BaudRate",  4, ".\\Settings.ini"));
    m_Combo_Baud.SetCurSel(TempData);
    TempData = (::GetPrivateProfileInt("PortConfig", "DataBits",  3, ".\\Settings.ini"));
    m_Combo_Data.SetCurSel(TempData);
    TempData = (::GetPrivateProfileInt("PortConfig", "CheckBits", 0, ".\\Settings.ini"));
    m_Combo_Check.SetCurSel(TempData);
    TempData = (::GetPrivateProfileInt("PortConfig", "StopBits",  1, ".\\Settings.ini"));
    m_Combo_Stop.SetCurSel(TempData);

    m_Check_HexDspl  = (::GetPrivateProfileInt("RecvConfig", "HexDispl", 0, ".\\Settings.ini")) ? TRUE : FALSE;
    m_Check_ShowTime = (::GetPrivateProfileInt("RecvConfig", "ShowTime", 1, ".\\Settings.ini")) ? TRUE : FALSE;

    ::GetPrivateProfileString("SendConfig", "AutoLines", "1000", TempStr, 5, ".\\Settings.ini");
    m_Edit_Lines.Format("%s", TempStr);
    SetDlgItemText(IDC_EDIT_LINES, TempStr);

    m_Check_HexSend   = (::GetPrivateProfileInt("SendConfig", "HexaSend", 0, ".\\Settings.ini")) ? TRUE : FALSE;
    ::GetPrivateProfileString("SendConfig", "AutoTime", "1000", TempStr, 5, ".\\Settings.ini");
    m_Edit_AutoTimer.Format("%s", TempStr);

    m_Check_Return    = (::GetPrivateProfileInt("SendConfig", "AddReturn", 0, ".\\Settings.ini")) ? TRUE : FALSE;

    ::GetPrivateProfileString("SendConfig", "SendData", "", TempStr, MAX_SEND_BYTE, ".\\Settings.ini");
    m_Edit_Send.Format("%s", TempStr);
    SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);

	if (m_Check_HexDspl) {                                                     /* ���ݶ���Ĳ���ֵ��ʼ����ʾ������ */
        SetDlgItemText(IDC_STATIC_LINES, "�ַ�");
    } else {
        SetDlgItemText(IDC_STATIC_LINES, "��");
    }
    
	p_DlgSrSend->m_Check_01 = (::GetPrivateProfileInt("SrSendArea", "SrHexa01", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_02 = (::GetPrivateProfileInt("SrSendArea", "SrHexa02", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_03 = (::GetPrivateProfileInt("SrSendArea", "SrHexa03", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_04 = (::GetPrivateProfileInt("SrSendArea", "SrHexa04", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_05 = (::GetPrivateProfileInt("SrSendArea", "SrHexa05", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_06 = (::GetPrivateProfileInt("SrSendArea", "SrHexa06", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_07 = (::GetPrivateProfileInt("SrSendArea", "SrHexa07", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_08 = (::GetPrivateProfileInt("SrSendArea", "SrHexa08", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_09 = (::GetPrivateProfileInt("SrSendArea", "SrHexa09", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_10 = (::GetPrivateProfileInt("SrSendArea", "SrHexa10", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_11 = (::GetPrivateProfileInt("SrSendArea", "SrHexa11", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_12 = (::GetPrivateProfileInt("SrSendArea", "SrHexa12", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_13 = (::GetPrivateProfileInt("SrSendArea", "SrHexa13", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_14 = (::GetPrivateProfileInt("SrSendArea", "SrHexa14", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_15 = (::GetPrivateProfileInt("SrSendArea", "SrHexa15", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_16 = (::GetPrivateProfileInt("SrSendArea", "SrHexa16", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_17 = (::GetPrivateProfileInt("SrSendArea", "SrHexa17", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_18 = (::GetPrivateProfileInt("SrSendArea", "SrHexa18", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_19 = (::GetPrivateProfileInt("SrSendArea", "SrHexa19", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_20 = (::GetPrivateProfileInt("SrSendArea", "SrHexa20", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_21 = (::GetPrivateProfileInt("SrSendArea", "SrHexa21", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_22 = (::GetPrivateProfileInt("SrSendArea", "SrHexa22", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_23 = (::GetPrivateProfileInt("SrSendArea", "SrHexa23", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_24 = (::GetPrivateProfileInt("SrSendArea", "SrHexa24", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_25 = (::GetPrivateProfileInt("SrSendArea", "SrHexa25", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_26 = (::GetPrivateProfileInt("SrSendArea", "SrHexa26", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_27 = (::GetPrivateProfileInt("SrSendArea", "SrHexa27", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_28 = (::GetPrivateProfileInt("SrSendArea", "SrHexa28", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_29 = (::GetPrivateProfileInt("SrSendArea", "SrHexa29", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_30 = (::GetPrivateProfileInt("SrSendArea", "SrHexa30", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_31 = (::GetPrivateProfileInt("SrSendArea", "SrHexa31", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_32 = (::GetPrivateProfileInt("SrSendArea", "SrHexa32", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_33 = (::GetPrivateProfileInt("SrSendArea", "SrHexa33", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_34 = (::GetPrivateProfileInt("SrSendArea", "SrHexa34", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_35 = (::GetPrivateProfileInt("SrSendArea", "SrHexa35", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_36 = (::GetPrivateProfileInt("SrSendArea", "SrHexa36", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_37 = (::GetPrivateProfileInt("SrSendArea", "SrHexa37", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_38 = (::GetPrivateProfileInt("SrSendArea", "SrHexa38", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_39 = (::GetPrivateProfileInt("SrSendArea", "SrHexa39", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	p_DlgSrSend->m_Check_40 = (::GetPrivateProfileInt("SrSendArea", "SrHexa40", 0, ".\\Settings.ini")) ? TRUE : FALSE;

	::GetPrivateProfileString("SrSendArea", "SrData01", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_01, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData02", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_02, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData03", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_03, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData04", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_04, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData05", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_05, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData06", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_06, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData07", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_07, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData08", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_08, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData09", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_09, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData10", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_10, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData11", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_11, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData12", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_12, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData13", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_13, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData14", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_14, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData15", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_15, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData16", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_16, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData17", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_17, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData18", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_18, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData19", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_19, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData20", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_20, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData21", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_21, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData22", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_22, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData23", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_23, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData24", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_24, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData25", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_25, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData26", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_26, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData27", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_27, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData28", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_28, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData29", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_29, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData30", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_30, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData31", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_31, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData32", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_32, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData33", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_33, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData34", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_34, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData35", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_35, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData36", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_36, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData37", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_37, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData38", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_38, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData39", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_39, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData40", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_40, TempPara);

	::GetPrivateProfileString("SrSendArea", "LoopTime", "", TempStr, 5, ".\\Settings.ini");
	p_DlgSrSend->m_Edit_AutoTime.Format("%s", TempStr);
	p_DlgSrSend->SetDlgItemText(IDC_EDIT_AUTOTIME, p_DlgSrSend->m_Edit_AutoTime);
    
    UpdateData(FALSE);                                                         /* ���±༭������ */
	p_DlgSrSend->UpdateData(FALSE);
}

/**************************************************************************************************
**  ��������:  RecordAllParas
**  ��������:  ���Ի����и���������ֵ��¼�������ļ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::RecordAllParas(void)
{
    int TempData;                                                              /* ��Ҫע����ǣ��Զ�����ʹ�ܺ�ѭ������ʹ���������뱣�� */
    CString ParaStr;
    
    TempData = m_Combo_ComNo.GetCurSel();
    ParaStr.Format("%d", TempData);
    ::WritePrivateProfileString("PortConfig", "CommPort",  ParaStr, ".\\Settings.ini");
    TempData = m_Combo_Baud.GetCurSel();
    ParaStr.Format("%d", TempData);
    ::WritePrivateProfileString("PortConfig", "BaudRate",  ParaStr, ".\\Settings.ini");
    TempData = m_Combo_Data.GetCurSel();
    ParaStr.Format("%d", TempData);
    ::WritePrivateProfileString("PortConfig", "DataBits",  ParaStr, ".\\Settings.ini");
    TempData = m_Combo_Check.GetCurSel();
    ParaStr.Format("%d", TempData);
    ::WritePrivateProfileString("PortConfig", "CheckBits", ParaStr, ".\\Settings.ini");
    TempData = m_Combo_Stop.GetCurSel();
    ParaStr.Format("%d", TempData);
    ::WritePrivateProfileString("PortConfig", "StopBits",  ParaStr, ".\\Settings.ini");

    ::WritePrivateProfileString("RecvConfig", "HexDispl",  m_Check_HexDspl   ? "1" : "0", ".\\Settings.ini");
    ::WritePrivateProfileString("RecvConfig", "ShowTime",  m_Check_ShowTime  ? "1" : "0", ".\\Settings.ini");

    GetDlgItemText(IDC_EDIT_LINES, ParaStr);
    ::WritePrivateProfileString("SendConfig", "AutoLines", ParaStr, ".\\Settings.ini");

    ::WritePrivateProfileString("SendConfig", "HexaSend",  m_Check_HexSend   ? "1" : "0", ".\\Settings.ini");
    GetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);
    ::WritePrivateProfileString("SendConfig", "AutoTime",  m_Edit_AutoTimer, ".\\Settings.ini");

    ::WritePrivateProfileString("SendConfig", "AddReturn", m_Check_Return    ? "1" : "0", ".\\Settings.ini");

    GetDlgItemText(IDC_EDIT_SEND, ParaStr);
    ::WritePrivateProfileString("SendConfig", "SendData",  ParaStr, ".\\Settings.ini");

	::WritePrivateProfileString("SrSendArea", "SrHexa01",  p_DlgSrSend->m_Check_01 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa02",  p_DlgSrSend->m_Check_02 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa03",  p_DlgSrSend->m_Check_03 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa04",  p_DlgSrSend->m_Check_04 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa05",  p_DlgSrSend->m_Check_05 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa06",  p_DlgSrSend->m_Check_06 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa07",  p_DlgSrSend->m_Check_07 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa08",  p_DlgSrSend->m_Check_08 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa09",  p_DlgSrSend->m_Check_09 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa10",  p_DlgSrSend->m_Check_10 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa11",  p_DlgSrSend->m_Check_11 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa12",  p_DlgSrSend->m_Check_12 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa13",  p_DlgSrSend->m_Check_13 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa14",  p_DlgSrSend->m_Check_14 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa15",  p_DlgSrSend->m_Check_15 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa16",  p_DlgSrSend->m_Check_16 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa17",  p_DlgSrSend->m_Check_17 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa18",  p_DlgSrSend->m_Check_18 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa19",  p_DlgSrSend->m_Check_19 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa20",  p_DlgSrSend->m_Check_20 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa21",  p_DlgSrSend->m_Check_21 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa22",  p_DlgSrSend->m_Check_22 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa23",  p_DlgSrSend->m_Check_23 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa24",  p_DlgSrSend->m_Check_24 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa25",  p_DlgSrSend->m_Check_25 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa26",  p_DlgSrSend->m_Check_26 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa27",  p_DlgSrSend->m_Check_27 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa28",  p_DlgSrSend->m_Check_28 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa29",  p_DlgSrSend->m_Check_29 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa30",  p_DlgSrSend->m_Check_30 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa31",  p_DlgSrSend->m_Check_31 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa32",  p_DlgSrSend->m_Check_32 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa33",  p_DlgSrSend->m_Check_33 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa34",  p_DlgSrSend->m_Check_34 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa35",  p_DlgSrSend->m_Check_35 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa36",  p_DlgSrSend->m_Check_36 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa37",  p_DlgSrSend->m_Check_37 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa38",  p_DlgSrSend->m_Check_38 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa39",  p_DlgSrSend->m_Check_39 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa40",  p_DlgSrSend->m_Check_40 ? "1" : "0", ".\\Settings.ini");

	p_DlgSrSend->GetDlgItemText(IDC_EDIT_01, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData01", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_02, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData02", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_03, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData03", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_04, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData04", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_05, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData05", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_06, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData06", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_07, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData07", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_08, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData08", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_09, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData09", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_10, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData10", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_11, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData11", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_12, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData12", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_13, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData13", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_14, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData14", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_15, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData15", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_16, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData16", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_17, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData17", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_18, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData18", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_19, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData19", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_20, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData20", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_21, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData21", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_22, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData22", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_23, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData23", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_24, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData24", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_25, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData25", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_26, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData26", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_27, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData27", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_28, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData28", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_29, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData29", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_30, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData30", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_31, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData31", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_32, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData32", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_33, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData33", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_34, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData34", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_35, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData35", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_36, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData36", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_37, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData37", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_38, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData38", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_39, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData39", ParaStr, ".\\Settings.ini");
	p_DlgSrSend->GetDlgItemText(IDC_EDIT_40, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData40", ParaStr, ".\\Settings.ini");

	p_DlgSrSend->GetDlgItemText(IDC_EDIT_AUTOTIME, ParaStr);
	::WritePrivateProfileString("SrSendArea", "LoopTime", ParaStr, ".\\Settings.ini");
}

/**************************************************************************************************
**  ��������:  InitiateStatusBar
**  ��������:  ��ʼ��״̬��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateStatusBar(void)
{
    static UINT indicators[] =
    {
        ID_SEPARATOR,
        ID_INDICATOR_CAPS,
        ID_INDICATOR_NUM,
        ID_INDICATOR_SCRL,
        ID_INDICATOR_OVR,
        ID_INDICATOR_REC,
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
    
    m_StatusBar.SetPaneInfo(0, nID, SBPS_STRETCH, 1);
    m_StatusBar.SetPaneText(0, " ��ӭʹ��MySScom - ��Ѹ����");
    
    m_StatusBar.SetPaneInfo(1, nID, SBPS_NORMAL, 90);
    m_StatusBar.SetPaneText(1, " ����δ��");

    m_StatusBar.SetPaneInfo(2, nID, SBPS_NORMAL, 90);
    m_StatusBar.SetPaneText(2, " Lines: 00000");
    
    m_StatusBar.SetPaneInfo(3, nID, SBPS_NORMAL, 100);
    m_StatusBar.SetPaneText(3, " Recv: 000000");
    
    m_StatusBar.SetPaneInfo(4, nID, SBPS_NORMAL, 100);
    m_StatusBar.SetPaneText(4, " Send: 000000");

    m_StatusBar.SetPaneInfo(5, nID, SBPS_NORMAL, 200);
    m_StatusBar.SetPaneText(5, m_strTime);
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}

/**************************************************************************************************
**  ��������:  InitiateComboComs
**  ��������:  ��ʼ�����ں���Ͽ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateComboComs(void)
{
    EnumComm();                                                                /* ö�ٿ��õĴ��� */

    for (int i = 0; i < sPorts.GetSize(); i++) {
        m_Combo_ComNo.AddString(sPorts.GetAt(i));
    }
}

/**************************************************************************************************
**  ��������:  InitiateComboBaud
**  ��������:  ��ʼ����������Ͽ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateComboBaud(void)
{
    CString TempStr;
    
    for (int i = 0; i < (sizeof(Combo_Baud) / sizeof(Combo_Baud[0])); i++) {

        TempStr.Format("%d bps", Combo_Baud[i]);

        m_Combo_Baud.AddString(TempStr);
    }
}

/**************************************************************************************************
**  ��������:  InitiateComboData
**  ��������:  ��ʼ������λ��Ͽ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateComboData(void)
{
    CString TempStr;
    
    for (int i = 0; i < (sizeof(Combo_Data) / sizeof(Combo_Data[0])); i++) {
        
        TempStr.Format("%d λ", Combo_Data[i]);
        
        m_Combo_Data.AddString(TempStr);
    }
}

/**************************************************************************************************
**  ��������:  InitiateComboCheck
**  ��������:  ��ʼ��У��λ��Ͽ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateComboCheck(void)
{
    m_Combo_Check.AddString("None У��");
    m_Combo_Check.AddString("Odd  У��");
    m_Combo_Check.AddString("Even У��");
    m_Combo_Check.AddString("Mark У��");
    m_Combo_Check.AddString("SpaceУ��");
}

/**************************************************************************************************
**  ��������:  InitiateComboStop
**  ��������:  ��ʼ��ֹͣλ��Ͽ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateComboStop(void)
{
    m_Combo_Stop.AddString("1  λ");
    m_Combo_Stop.AddString("1.5λ");
    m_Combo_Stop.AddString("2  λ");
}

/**************************************************************************************************
**  ��������:  TaskBarAddIcon
**  ��������:  ������������ͼ����ʾ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
BOOL CMySScomDlg::TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip)
{
    NOTIFYICONDATA d;
    
    d.cbSize = sizeof(NOTIFYICONDATA);
    d.hWnd   = hwnd;
    d.uID    = uID;
    d.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    d.hIcon  = hicon;
    d.uCallbackMessage = MYWM_NOTIFYICON;
    
    if (lpszTip) {
        lstrcpy(d.szTip, lpszTip);
    } else {
        d.szTip[0] = '\0';
    }
    
    return Shell_NotifyIcon(NIM_ADD, &d);
}

/**************************************************************************************************
**  ��������:  TaskBarDeleteIcon
**  ��������:  ��������ɾ��ͼ����ʾ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
BOOL CMySScomDlg::TaskBarDeleteIcon(HWND hwnd, UINT uID)
{
    NOTIFYICONDATA d;
    
    d.cbSize = sizeof(NOTIFYICONDATA);
    d.hWnd   = hwnd;
    d.uID    = uID;
    
    return Shell_NotifyIcon(NIM_DELETE, &d);
}


/* ==================================== �Զ��庯����--���� ===================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ================================== �����ؼ���Ϣ����--��ʼ =================================== */


/**************************************************************************************************
**  ��������:  OnButtonONOFF
**  ��������:  ���ڿ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonONOFF() 
{
    DCB  dcb;
    CString TempStr;
    COMMTIMEOUTS TimeOuts;
    
    if (m_PortOpened == TRUE) {                                                /* ��������Ѿ��򿪣���ôִ�йرղ��� */

        if (m_Check_AutoSend) {
            MessageBox("������ͣ���Զ����͹����ٳ��Թرմ���...  ", "��ʾ", MB_OK + MB_ICONEXCLAMATION);
            return;
        }
        
        SetCommMask(m_hSPCom, 0);                                              /* ���ù������� ????? */
        
        WaitForSingleObject(m_pThread->m_hThread, INFINITE);                   /* �ر��߳� ????? */
        
        m_pThread = NULL;
        
        CloseHandle(m_hSPCom);                                                 /* �رմ��ھ�� */

        SetDlgItemText(IDC_BUTTON_ONOFF, "�򿪴���");

        GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_DATA)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_CHECK)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_STOP)->EnableWindow(TRUE);

        SetControlStatus(FALSE);

        m_PortOpened = FALSE;

        return;
    }

    int ComNumber = m_Combo_ComNo.GetCurSel();                                 /* �õ����ں� */

    if (ComNumber == 0) {
        MessageBox("�����ںŶ�û��ѡ������Ҵ�ʲô����...��   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        return;
    }
    
    m_Combo_ComNo.GetLBText(ComNumber, TempStr);
    CString ComComNo = TempStr;

    int ComBaudSel = m_Combo_Baud.GetCurSel();                                 /* ��ȡ�����ʵ�ѡ���� */
    TempStr.Format("%d", Combo_Baud[ComBaudSel]);
    ComBaudSel = atoi(TempStr);
    
    int ComDataSel = m_Combo_Data.GetCurSel();                                 /* ��ȡ����λ��ѡ���� */
    TempStr.Format("%d", Combo_Data[ComDataSel]);
    ComDataSel = atoi(TempStr);
    
    int ComCheckSel = m_Combo_Check.GetCurSel();                               /* ��ȡУ��λ��ѡ���� */
    TempStr.Format("%c", Combo_Check[ComCheckSel]);
    ComCheckSel = atoi(TempStr);
    
    int ComStopSel = m_Combo_Stop.GetCurSel();                                 /* ��ȡֹͣλ��ѡ���� */
    TempStr.Format("%d", Combo_Stop[ComStopSel]);
    ComStopSel = atoi(TempStr);

    m_hSPCom = CreateFile(ComComNo, GENERIC_READ | GENERIC_WRITE, 0,           /* �򿪴��ڣ���ȡ��� */
                          NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    
    if (m_hSPCom == INVALID_HANDLE_VALUE) {                                    /* ���ڴ�ʧ�� */
        MessageBox("�򿪴���ʧ�ܣ��ô��ڿ�������ʹ����...   ", "��ʾ", MB_OK + MB_ICONERROR);
        return;
    }
    
    SetupComm(m_hSPCom, MAXBLOCK, MAXBLOCK);                                   /* ���û����С */
    SetCommMask(m_hSPCom, EV_RXCHAR);                                          /* ���ù�������??? - �����ַ�ȫ���� */
    
    TimeOuts.ReadIntervalTimeout         = MAXDWORD;                           /* �������ʱ */
    TimeOuts.ReadTotalTimeoutConstant    = 0;                                  /* ��ʱ�䳣�� */
    TimeOuts.ReadTotalTimeoutMultiplier  = 0;                                  /* ��ʱ��ϵ�� */
    TimeOuts.WriteTotalTimeoutConstant   = 2000;                               /* дʱ�䳣�� */
    TimeOuts.WriteTotalTimeoutMultiplier = 50;                                 /* дʱ��ϵ�� */

    SetCommTimeouts(m_hSPCom, &TimeOuts);                                      /* ���ó�ʱ���� */

    if (!GetCommState(m_hSPCom, &dcb)) {                                       /* ���Ȼ�ȡ��ǰ�Ĺ������� */
        MessageBox("���ڹ���������ȡʧ�ܣ���ȷ�ϸô����Ƿ���Ч...   ", "��ʾ", MB_OK + MB_ICONERROR);
        return;
    }
    
    dcb.fBinary      = TRUE;                                                   /* ������ģʽ */
    dcb.BaudRate     = ComBaudSel;                                             /* ���ò����� */
    dcb.ByteSize     = ComDataSel;                                             /* ��������λ */
    dcb.StopBits     = ComStopSel;
    dcb.fParity      = TRUE;                                                   /* ����У�鹦�� */
    dcb.Parity       = ComCheckSel;
    dcb.XonChar      = XON;
    dcb.XoffChar     = XOFF;
    dcb.fOutxCtsFlow = 0;
    dcb.fRtsControl  = 0;
    dcb.fInX         = 0;
    dcb.fOutX        = 0;
    
    if (dcb.XoffLim = 50) {
        dcb.XonLim = 1;
    } else {
        dcb.XonLim = 0;
    }
        
    if (SetCommState(m_hSPCom, &dcb)) {                                        /* �������ô��ڲ��� */
        
        m_pThread = AfxBeginThread(SPCommProc, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);     /* �¿�һ���߳����ڼ����������� */
        
        if (m_pThread == NULL) {                                               /* ����̴߳���ʧ�� */

            CloseHandle(m_hSPCom);                                             /* �رմ��ھ�� */

            MessageBox("�����쳣�����ڼ����̴߳���ʧ��...   ", "��ʾ", MB_OK + MB_ICONERROR);
            return;

        } else {                                                               /* ��ʼ�������� */

            m_pThread->ResumeThread();

            m_PortOpened = TRUE;
            
            SetControlStatus(TRUE);                                            /* ���ø�����ť�ؼ� */
            
            SetDlgItemText(IDC_BUTTON_ONOFF, "�رմ���");
            
            GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(FALSE);
            GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(FALSE);
            GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);
            GetDlgItem(IDC_COMBO_CHECK)->EnableWindow(FALSE);
            GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);
        }

    } else {                                                                   /* ��������ʧ�ܣ��رմ��ھ�� */

        CloseHandle(m_hSPCom);
        MessageBox("���ڲ�������ʧ�ܣ���ȷ�ϸ��������Ƿ�Ϸ�...   ", "��ʾ", MB_OK + MB_ICONERROR);
        return;
    }
}

/**************************************************************************************************
**  ��������:  OnButtonPause
**  ��������:  ��ͣ����/�ָ�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonPause() 
{
    if (m_bRecvPause == FALSE) {
        m_bRecvPause = TRUE;
        SetDlgItemText(IDC_BUTTON_PAUSE, "�ָ�����");
        GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(FALSE);
    } else {
        m_bRecvPause = FALSE;
        SetDlgItemText(IDC_BUTTON_PAUSE, "��ͣ����");
        GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(TRUE);
    }
}

/**************************************************************************************************
**  ��������:  OnButtonClear
**  ��������:  ����������Ѿ����յ�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonClear()
{
    StrRecved = "";
    
    m_Edit_Recv = "";
    SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);

    if (m_Check_ShowTime == TRUE) {
        m_NeedTime = TRUE;                                                     /* ��һ���յ�����ʱ��ʾʱ�� */
    }

    RecvedLine = 0;
    RecvedData = 0;
    UpdateStatusBarNow();                                                      /* ����״̬����ͳ��������ʾ */
}

/**************************************************************************************************
**  ��������:  OnButtonSave
**  ��������:  �����յ������ݱ��浽�ļ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSave()
{
    CFile   MyFile;                                                            /* �����ļ��� */
    int     nLength;
    CString Temp_String;
    
    CTime   NowTime  = CTime::GetCurrentTime();                                /* ��ȡ����ʱ�� */
    CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";           /* ָ���ļ��� */
    
    GetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
    
    nLength = m_Edit_Recv.GetLength();                                         /* ��ȡ���� */
    
    if (nLength <= 0) {
        MessageBox("��δ���յ��κ����ݣ����뱣�棡   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        return;
    }
    
    if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite) == 0) {
        Temp_String = "�ļ� " + FileName + " ����ʧ�ܣ�  ";
        MessageBox(Temp_String, "��Ǹ", MB_OK + MB_ICONWARNING);
        return;
    } else {
        Temp_String = "�ļ� " + FileName + " �����ɹ���  ";
        MessageBox(Temp_String, "��ϲ", MB_OK + MB_ICONINFORMATION);
    }
    
    MyFile.Write(m_Edit_Recv, nLength);                                        /* д���ı��ļ� */
    MyFile.Close();                                                            /* �ر��ļ� */
}

/**************************************************************************************************
**  ��������:  OnButtonSend
**  ��������:  ���ʹ��������������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSend()
{
    GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
    
    if (m_Edit_Send.GetLength() <= 0) {
        MessageBox("���ʹ�������Ϊ�գ�δ�����κ����ݣ� ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        return;
    }
	
	if (SendDatatoComm(m_Edit_Send, m_Check_HexSend) == FALSE) {
		MessageBox("�������CAN����֡���ݹ��������ߴ��ڷǷ��ַ�����ȷ�ϣ�......       ", "����", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
}

/**************************************************************************************************
**  ��������:  OnButtonCount
**  ��������:  ���������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonCount() 
{
    RecvedLine = 0;
    RecvedData = 0;
    SendedData = 0;

    UpdateStatusBarNow();                                                      /* ����״̬����ͳ��������ʾ */
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend
**  ��������:  ��ʾ�߼����ʹ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend() 
{
	if (p_DlgSrSend->IsWindowVisible()) {                                      /* �߼����ʹ����Ѿ��򿪣����Թر� */

		if (p_DlgSrSend->DataisSending()) {
			MessageBox("����ֹͣ�Զ�ѭ�����͹��ܣ��ٳ��Թرո߼����ʹ���......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			p_DlgSrSend->ShowWindow(SW_HIDE);
			SetDlgItemText(IDC_BUTTON_SRSEND, "�߼�����");
			
			GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
		}
		
	} else {                                                                   /* �߼����ʹ�����δ�򿪣����Դ� */

		if (m_Check_AutoSend) {
			MessageBox("����ֹͣ�������ݵ��Զ����͹��ܣ��ٳ��Դ򿪸߼����ʹ���......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			p_DlgSrSend->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_BUTTON_SRSEND, "��������");

			GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  ��������:  OnButtonHelp
**  ��������:  ��ʾ��������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonHelp() 
{
    CDialogAbout Dlgabout;
    
    Dlgabout.DoModal();
}

/**************************************************************************************************
**  ��������:  OnCheckHexDisplay
**  ��������:  �Ƿ���ʾΪ16�����ַ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckHexDisplay()
{
    if (m_Check_ShowTime == TRUE) {
        MessageBox("����ȡ����ʾʱ�书�ܣ�Ȼ���ٳ����л���16���Ƶ���ʾģʽ......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        m_Check_HexDspl = FALSE;        
        UpdateData(FALSE);
    } else {
        m_Check_HexDspl = !m_Check_HexDspl;

        if (m_Check_HexDspl) {
            SetDlgItemText(IDC_STATIC_LINES, "�ַ�");
        } else {
            SetDlgItemText(IDC_STATIC_LINES, "��");
        }

        UpdateEditDisplay();                                                   /* ������ʾ */
    }
}

/**************************************************************************************************
**  ��������:  OnCheckAutoClear
**  ��������:  �Ƿ����Զ��������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoClear() 
{
    int     TempData;
    CString TempStr;
    
    m_Check_AutoClear = !m_Check_AutoClear;
    
    GetDlgItemText(IDC_EDIT_LINES, TempStr);

    TempData = atoi((LPSTR)(LPCTSTR)TempStr);
    
    if ((TempData < 1) || (TempData > 10000)) {        
        MessageBox("�����õ�����ֵ����ϵͳ����Χ����������1-10000��֮��  ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        SetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                          /* ��ԭ�༭������ */
        m_Check_AutoClear = FALSE;        
        UpdateData(FALSE);
        return;
    }

    GetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                              /* ��ȡ���ݲ����� */
    MaxRecvLines = atoi((LPSTR)(LPCTSTR)m_Edit_Lines);

    if (m_Check_AutoClear) {
        GetDlgItem(IDC_STATIC_OVER)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_LINES)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_LINES)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(TRUE);
    } else {
        GetDlgItem(IDC_STATIC_OVER)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_LINES)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_LINES)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(FALSE);
    }
}

/**************************************************************************************************
**  ��������:  OnCheckAutoSave
**  ��������:  �Ƿ����Զ����湦��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoSave()
{
    m_Check_AutoSave = !m_Check_AutoSave;
}

/**************************************************************************************************
**  ��������:  OnCheckHexSend
**  ��������:  �Ƿ���16��������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckHexSend()
{   
    m_Check_HexSend = !m_Check_HexSend;
}

/**************************************************************************************************
**  ��������:  OnCheckAutoSend
**  ��������:  �Ƿ����Զ����͹���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoSend()
{   
    m_Check_AutoSend = !m_Check_AutoSend;

    GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);

    if (m_Edit_Send.GetLength() <= 0) {
        MessageBox("ò�Ʒ�����Ϊ�հɣ��������������ҷ���ʲô������ ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        m_Check_AutoSend = FALSE;
        UpdateData(FALSE);
        return;
    }

    if (m_Check_AutoSend) {

        if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {                        /* ȷ����������ݲ������ */

            MessageBox("����������ݹ������ύ��������ʧ��......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
            m_Check_AutoSend = FALSE;
            UpdateData(FALSE);
            return;
        }

        NeedAutoSendData();                                                    /* ��ʼ�����Զ��������� */

    } else {

        KillTimer(Timer_No_AutoSend);                                          /* �����û�ȡ�����Զ����͵Ĺ��� */
        GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);

        SetSendButtonStatus(TRUE);                                             /* �������÷�����������ť */
    }
}

/**************************************************************************************************
**  ��������:  OnCheckReturn
**  ��������:  ����ʱ�Ƿ񲹼ӻس���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckReturn()
{
    m_Check_Return = !m_Check_Return;
}

/**************************************************************************************************
**  ��������:  OnCheckShowTime
**  ��������:  ��ͷλ���Ƿ���ʾʱ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckShowTime()
{
    if (m_Check_HexDspl == TRUE) {
        MessageBox("16������ʾģʽ�²�֧����ʾ����ʱ�书��......    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        m_Check_ShowTime = FALSE;        
        UpdateData(FALSE);  
    } else {
        m_Check_ShowTime = !m_Check_ShowTime;
    }
}

/**************************************************************************************************
**  ��������:  OnMenuTrayAbout
**  ��������:  ���̲˵� - ���ڳ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayAbout()
{
    CDialogAbout Dlgabout;
    
    Dlgabout.DoModal();
}

/**************************************************************************************************
**  ��������:  OnMenuTrayShow
**  ��������:  ���̲˵� - ��ʾ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayShow()
{
    ShowWindow(SW_SHOW);
}

/**************************************************************************************************
**  ��������:  OnMenuTrayHide
**  ��������:  ���̲˵� - ���ؽ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayHide()
{
    ShowWindow(SW_HIDE);
}

/**************************************************************************************************
**  ��������:  OnMenuTrayExit
**  ��������:  ���̲˵� - �˳�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayExit()
{
    RecordAllParas();                                                          /* ��������������� */
    
    TaskBarDeleteIcon(GetSafeHwnd(), 120);                                     /* ɾ����������ͼ�� */
    
    ::PostQuitMessage(0);                                                      /* �����˳���Ψһ��ʽ */
}


/* ================================== �����ؼ���Ϣ����--���� =================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */


/**************************************************************************************************
**  ��������:  OnPaint
**  ��������:  �������ػ���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnPaint() 
{
    if (IsIconic()) {

        CPaintDC dc(this);
        
        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
        
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);

        CRect rect;

        GetClientRect(&rect);

        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        
        dc.DrawIcon(x, y, m_hIcon);

    } else {

        CDialog::OnPaint();
    }
}

/**************************************************************************************************
**  ��������:  OnQueryDragIcon
**  ��������:  ��ȡ����ͼ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
HCURSOR CMySScomDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

/**************************************************************************************************
**  ��������:  OnInitDialog
**  ��������:  ���ڳ�ʼ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
BOOL CMySScomDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	p_DlgSrSend = new CDialogSrSend();                                         /* ������䴴���߼����ʹ��壬�����ش��� */
	
	if (p_DlgSrSend != NULL){
		
		int Result = p_DlgSrSend->Create(IDD_DIALOG_SRSEND, this);
		
		if (!Result) {
			MessageBox("ϵͳ��Դ���㣬�����Ի���ʧ��......   ", "��Ǹ", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		p_DlgSrSend->ShowWindow(SW_HIDE);
	}

    s_top_offset  = 0;                                                         /* ����䲻���ƶ�λ�� */
    s_left_offset = 0;

    m_pThread    = NULL;
    m_bRecvPause = FALSE;
    m_PortOpened = FALSE;
    
    StrRecved = "";
    
    Loop_Counter = 0;
    MaxRecvLines = 0;
    
    RecvedLine = 0;
    RecvedData = 0;
    SendedData = 0;

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    memset(&m_osRead,  0, sizeof(OVERLAPPED));
    memset(&m_osWrite, 0, sizeof(OVERLAPPED));
    
    if (!(m_osRead.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL))) {
        return FALSE;
    }
    
    if (!(m_osWrite.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL))) {
        return FALSE;
    }

    s_Edit_Recv = (CEdit*)GetDlgItem(IDC_EDIT_RECV);
    s_Edit_Send = (CEdit*)GetDlgItem(IDC_EDIT_SEND);

    InitiateStatusBar();                                                       /* ��ʼ��״̬����������λ�� */
    InitiateComboComs();                                                       /* ��ʼ��ѡ�񴮿ںŵ��б�� */
    InitiateComboBaud();                                                       /* ��ʼ��ѡ�����ʵ��б�� */
    InitiateComboData();                                                       /* ��ʼ��ѡ������λ���б�� */
    InitiateComboCheck();                                                      /* ��ʼ��ѡ��У��λ���б�� */
    InitiateComboStop();                                                       /* ��ʼ��ѡ��ֹͣλ���б�� */

    SetControlStatus(FALSE);                                                   /* ���Ƚ��ø�����ť�ؼ� */

    CreateDirectory(RecordPath, NULL);                                         /* ����Record�ļ��У����ڱ������� */

    SetTimer(Timer_No_RecvData,  10,   NULL);
    SetTimer(Timer_No_StatusBar, 1000, NULL);
    
    // CG: The following block was added by the ToolTips component. 
    {       
        m_tooltip.Create(this);
        m_tooltip.Activate(TRUE);

        m_tooltip.AddTool(GetDlgItem(IDC_COMBO_COMNO),     IDS_STRING_001);
        m_tooltip.AddTool(GetDlgItem(IDC_COMBO_BAUD),      IDS_STRING_002);
        m_tooltip.AddTool(GetDlgItem(IDC_COMBO_DATA),      IDS_STRING_003);
        m_tooltip.AddTool(GetDlgItem(IDC_COMBO_CHECK),     IDS_STRING_021);
        m_tooltip.AddTool(GetDlgItem(IDC_COMBO_STOP),      IDS_STRING_004);
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_ONOFF),    IDS_STRING_005);
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_PAUSE),    IDS_STRING_006);
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_CLEAR),    IDS_STRING_007);
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SAVE),     IDS_STRING_008);
        m_tooltip.AddTool(GetDlgItem(IDC_CHECK_HEXDSPL),   IDS_STRING_009);
        m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOCLEAR), IDS_STRING_010);
        m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOSAVE),  IDS_STRING_011);
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SEND),     IDS_STRING_015);
        m_tooltip.AddTool(GetDlgItem(IDC_CHECK_HEXSEND),   IDS_STRING_016);
        m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOSEND),  IDS_STRING_017);
        m_tooltip.AddTool(GetDlgItem(IDC_EDIT_TIMER),      IDS_STRING_018);
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_COUNT),    IDS_STRING_019);
        m_tooltip.AddTool(GetDlgItem(IDC_CHECK_RETURN),    IDS_STRING_020);
    }

    INIT_EASYSIZE;                                                             /* ��ʼ�������ؼ���λ�� */

    CreateSettingFile();                                                       /* �����������ò����ļ�����ʼ���������� */
    InitiateAllParas();

    TaskBarAddIcon(GetSafeHwnd(), 120, AfxGetApp()->LoadIcon(IDR_MAINFRAME), "MySScom");

    return TRUE;
}

/**************************************************************************************************
**  ��������:  OnTimer
**  ��������:  ��ʱ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnTimer(UINT nIDEvent) 
{
    switch (nIDEvent)
    {
        case Timer_No_RecvData:                                                /* ���յ��������� */
            if (m_DataRecvd == TRUE) {
                SetTimer(Timer_No_RecvData, 10, NULL);
                UpdateEditDisplay();                                           /* ���±༭��������ʾ */
                UpdateStatusBarNow();                                          /* ����״̬��ͳ�����ݵ���ʾ */
                m_DataRecvd = FALSE;
            }
            break;
        
        case Timer_No_StatusBar:                                               /* ״̬����ʱ���� */
            UpdateStatusBarNow();
            break;
            
        case Timer_No_AutoSend:                                                /* �Զ��������� */
            GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
			if (SendDatatoComm(m_Edit_Send, m_Check_HexSend) == FALSE) {       /* ���ݷǷ�����ֹͣ��ʱ�� */
				OnCheckAutoSend();
				UpdateData(FALSE);
				MessageBox("�������CAN����֡���ݹ��������ߴ��ڷǷ��ַ�����ȷ�ϣ�......       ", "����", MB_OK + MB_ICONEXCLAMATION);
			}
            break;
            
        default:
            return;
    }
        
    CDialog::OnTimer(nIDEvent);
}

/**************************************************************************************************
**  ��������:  PreTranslateMessage
**  ��������:  ϵͳ��ϢԤ������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
BOOL CMySScomDlg::PreTranslateMessage(MSG* pMsg) 
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
**  ��������:  �����ڹر���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnClose() 
{
    ShowWindow(SW_HIDE);                                                       /* ���������ڵ��ǲ��˳� */
}

/**************************************************************************************************
**  ��������:  OnSize
**  ��������:  �����ڴ�С������Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);

    UPDATE_EASYSIZE;

    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);      /* ͬ��״̬����λ�� */
}

/**************************************************************************************************
**  ��������:  OnSizing
**  ��������:  �����ڴ�С������Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
    CDialog::OnSizing(fwSide, pRect);

    EASYSIZE_MINSIZE(800, 482, fwSide, pRect);                                 /* ���ƴ������С�ߴ� */
}

/**************************************************************************************************
**  ��������:  OnMyIconNotify
**  ��������:  ��������ͼ����Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMyIconNotify(WPARAM wParam, LPARAM lParam)
{
    UINT uMouseMsg = LOWORD(lParam);
    CMenu oMenu;
    CPoint oPoint;
    
    switch (uMouseMsg)
    {
        case WM_LBUTTONDBLCLK:                                                 /* ��������˫�� */
            ShowWindow(IsWindowVisible()? SW_HIDE:SW_SHOWNORMAL);
            break;
        
        case WM_RBUTTONDOWN:                                                   /* ������Ҽ� */
            if (oMenu.LoadMenu(IDR_MENU_TRAY)) {
                CMenu* pPopup = oMenu.GetSubMenu(0);
                ASSERT(pPopup != NULL);
                
                GetCursorPos(&oPoint);                                         /* ȷ�����λ���Ա��ڸ�λ�ø�����ʾ�˵� */
                SetForegroundWindow();
                pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, oPoint.x, oPoint.y, this); 
            }
            break;
    }
}


