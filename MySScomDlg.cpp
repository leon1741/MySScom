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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/* ==================================== 自定义函数区--开始 ===================================== */


// 本函数用来枚举电脑上存在可用的串口
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

// 这是一个将字符转换为相应的十六进制值的函数，好多C语言书上都可以找到
// 功能：若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1
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

// 由于这个转换函数的格式限制，在发送框中的十六制字符应该每两个字符之间插入一个空隔
// 如：A1 23 45 0B 00 29
// CByteArray是一个动态字节数组
int CMySScomDlg::String2Hex(CString str, CByteArray &senddata)
{
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = str.GetLength();
    senddata.SetSize(len / 2);
	
    for (int i = 0; i < len; )
    {
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

void CMySScomDlg::RePaintWindows(void)
{
	CRect Main;
	GetClientRect(&Main);

	//if ((Main.Width()) < 800) {
	//	MoveWindow(0, 0, 800, 500);
	//	return;
	//}

	//if ((Main.Height()) < 500) {
	//	MoveWindow(0, 0, 800, 500);
	//	return;
	//}
	
	GetDlgItem(IDC_STATIC_RECEIVE)->MoveWindow(190, 10, Main.Width() - 200, Main.Height() - 110);
	GetDlgItem(IDC_EDIT_RECV)->MoveWindow(198, 28, Main.Width() - 216, Main.Height() - 136);
	
	GetDlgItem(IDC_STATIC_SEND)->MoveWindow(190, Main.Height() - 92, Main.Width() - 200, 82);
	GetDlgItem(IDC_EDIT_SEND)->MoveWindow(198, Main.Height() - 74, Main.Width() - 216, 56);
}


/* ==================================== 自定义函数区--结束 ===================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ================================== 各个控件消息处理--开始 =================================== */


void CMySScomDlg::OnButtonONOFF() 
{
	
}

void CMySScomDlg::OnButtonPause() 
{
	
}

void CMySScomDlg::OnButtonClear() 
{
	
}

void CMySScomDlg::OnButtonSave() 
{
	
}

void CMySScomDlg::OnButtonRead() 
{
	
}

void CMySScomDlg::OnButtonRespite() 
{
	
}

void CMySScomDlg::OnButtonReiput() 
{
	
}

void CMySScomDlg::OnButtonSend() 
{
	
}

void CMySScomDlg::OnCheckHexDisplay() 
{
	
}

void CMySScomDlg::OnCheckAutoSave() 
{
	
}

void CMySScomDlg::OnCheckHexSend() 
{
	
}

void CMySScomDlg::OnCheckAutoSend() 
{
	
}


/* ================================== 各个控件消息处理--结束 =================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */


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
	
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");
	}

	return TRUE;
}

void CMySScomDlg::OnTimer(UINT nIDEvent) 
{
	
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CMySScomDlg::PreTranslateMessage(MSG* pMsg) 
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMySScomDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CWnd *pWnd = GetDlgItem(IDC_EDIT_RECV);
	
	if (pWnd) {
		RePaintWindows();                                            // 重绘窗口
	}
}
