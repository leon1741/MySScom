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
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
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

BEGIN_EVENTSINK_MAP(CMySScomDlg, CDialog)
//{{AFX_EVENTSINK_MAP(CMySScomDlg)
ON_EVENT(CMySScomDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm, VTS_NONE)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


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

	GetDlgItem(IDC_STATIC_CONTROL)->MoveWindow(10, 10, 158, Main.Height() - 20);
	
	GetDlgItem(IDC_STATIC_RECEIVE)->MoveWindow(180, 10, Main.Width() - 190, Main.Height() - 110);
	GetDlgItem(IDC_EDIT_RECV)->MoveWindow(190, 28, Main.Width() - 210, Main.Height() - 136);
	
	GetDlgItem(IDC_STATIC_SEND)->MoveWindow(180, Main.Height() - 92, Main.Width() - 190, 82);
	GetDlgItem(IDC_EDIT_SEND)->MoveWindow(190, Main.Height() - 74, Main.Width() - 210, 56);
}

void CMySScomDlg::SetControlStatus(bool Enable)
{
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_REIPUT)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_RESPITE)->EnableWindow(Enable);
	
	GetDlgItem(IDC_CHECK_HEXDSPL)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(Enable);
	
	GetDlgItem(IDC_STATIC_INTERVAL)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
}

void CMySScomDlg::NeedClearWindow(void)
{
	if (s_Edit_Recv->GetLineCount() > 500) {

		CTime   NowTime  = CTime::GetCurrentTime();	                 // ��ȡ����ʱ��
		CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";
		
		CString Temp_String;                                         // ��ʱ����
		CFile   MyFile;	                                             // �����ļ���
		
		if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite)) {

			GetDlgItem(IDC_EDIT_RECV)->GetWindowText(Temp_String);   // ȡ������������

			int nLength = Temp_String.GetLength();                   // �ļ�����
			MyFile.Write(Temp_String, nLength);	                     // д���ı��ļ�
			MyFile.Close();	                                         // �ر��ļ�
			
			m_Edit_Recv = "";
			SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);              // ��ձ༭������
		}
	}
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
	CString ComNo;
    
	if (m_PortOpened == true) {                                      // ��������Ѿ��򿪣���ôִ�йرղ���

		if (m_Check_AutoSend) {
			MessageBox("������ͣ���Զ����͹����ٳ��Թرմ���    ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
			return;
		}
		
		m_ctrlComm.SetPortOpen(FALSE);

		MessageBox("������ �ɹ��رմ���! ������    ", "֪ͨ", MB_OK + MB_ICONINFORMATION);

		SetDlgItemText(IDC_BUTTON_ONOFF, "�򿪴���");

		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(TRUE);

		SetControlStatus(FALSE);

		m_PortOpened = FALSE;

		return;
	}

	int Number = m_Combo_ComNo.GetCurSel();                          // �õ����ں�
	
	if (Number == 0) {
		MessageBox("��δѡ�񴮿ں�      ", "ע��", MB_OK + MB_ICONEXCLAMATION);
        return;
    }
	
	if (m_ctrlComm.GetPortOpen()) {                                  // �ж��Ƿ��Ѿ���
        m_ctrlComm.SetPortOpen(FALSE);
	}
	
	m_Combo_ComNo.GetLBText(Number, ComNo);
	ComNo.TrimLeft("COM");                                           // ɾ��"COM"�ֶ�
	
	m_ctrlComm.SetCommPort(atoi(ComNo.Mid(0)));
	
    if (!m_ctrlComm.GetPortOpen()) {
        m_ctrlComm.SetPortOpen(TRUE);                                // ���Դ򿪴���
		
		MessageBox("������ �ɹ��򿪴���! ������    ", "֪ͨ", MB_OK + MB_ICONINFORMATION);
		
		SetDlgItemText(IDC_BUTTON_ONOFF, "�رմ���");
		
		SetControlStatus(TRUE);
		
		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);

	} else {

        MessageBox("��ָ������ʧ��!  ", "��Ǹ", MB_OK + MB_ICONERROR);
	}
	
    CString TempStr;
    int BaudRate = m_Combo_Baud.GetCurSel();                         // ��ȡ�����ʵ�ѡ����
	
	switch (BaudRate)
	{
	case 0:
		TempStr = "2400,n,8,1";
		break;
	case 1:
		TempStr = "4800,n,8,1";
		break;
	case 2:
		TempStr = "9600,n,8,1";
		break;
	case 3:
		TempStr = "19200,n,8,1";
		break;
	case 4:
		TempStr = "38400,n,8,1";
		break;
	case 5:
		TempStr = "57600,n,8,1";
		break;
	case 6:
		TempStr = "76800,n,8,1";
		break;
	case 7:
		TempStr = "115200,n,8,1";
		break;
	case 8:
		TempStr = "153600,n,8,1";
		break;
	case 9:
		TempStr = "230400,n,8,1";
		break;
	default:
		TempStr = "9600,n,8,1";
		break;
	}
	
	m_ctrlComm.SetSettings(TempStr);                                 // ������(XXXX)����У�飬8������λ��1��ֹͣλ 
	
    m_ctrlComm.SetInputMode(1);                                      // 1��ʾ�Զ����Ʒ�ʽ��ȡ����
    m_ctrlComm.SetRThreshold(1);                                     // ����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
    m_ctrlComm.SetInputLen(0);                                       // ���õ�ǰ���������ݳ���Ϊ0
    m_ctrlComm.GetInput();                                           // ��Ԥ���������������������

	m_PortOpened = TRUE;
}

void CMySScomDlg::OnButtonPause() 
{
	if (m_bCanDisplay == false) {
		m_bCanDisplay = TRUE;
		SetDlgItemText(IDC_BUTTON_PAUSE, "��ͣ��ʾ");
	} else {
		m_bCanDisplay = false;
		SetDlgItemText(IDC_BUTTON_PAUSE, "�ָ���ʾ");
	}
}

void CMySScomDlg::OnButtonClear() 
{
	m_Edit_Recv = "";
	SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
}

void CMySScomDlg::OnButtonSave() 
{
	CTime   NowTime  = CTime::GetCurrentTime();	                     // ��ȡ����ʱ��
	CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt"; // ָ���ļ���
	
    CString Temp_String;                                             // ��ʱ����
	CFile   MyFile;	                                                 // �����ļ���
	
	if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite) == 0) {
		Temp_String = "�ļ� " + FileName + " ����ʧ��!         ";
		MessageBox(Temp_String, "��Ǹ", MB_OK + MB_ICONHAND);
		return;
	} else {
		Temp_String = "�ļ� " + FileName + " �����ɹ�!         ";
		MessageBox(Temp_String, "��ϲ", MB_OK + MB_ICONINFORMATION);
	}
	
	GetDlgItem(IDC_EDIT_RECV)->GetWindowText(Temp_String);           // ȡ������������
	
	int nLength = Temp_String.GetLength();                           // �ļ�����
	MyFile.Write(Temp_String, nLength);	                             // д���ı��ļ�
	MyFile.Close();	                                                 // �ر��ļ�
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
	m_Check_HexDspl = !m_Check_HexDspl;
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

	EnumComm();                                                      // ö�ٿ��õĴ���
	for (int i = 0; i < sPorts.GetSize(); i++) {
		m_Combo_ComNo.AddString(sPorts.GetAt(i));
	}

	m_Combo_ComNo.SetCurSel(0);
	m_Combo_Baud.SetCurSel(2);
	m_Combo_Data.SetCurSel(3);
	m_Combo_Stop.SetCurSel(2);

	GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);

	SetControlStatus(false);

	m_bCanDisplay = TRUE;                                            // Ĭ��������ʾ����

	m_PortOpened  = false;

	CreateDirectory(RecordPath, NULL);                               // ����Record�ļ��У����ڱ�������
	
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");
	}

	CWnd *pWnd = GetDlgItem(IDC_EDIT_RECV);
	
	if (pWnd) {
		RePaintWindows();                                            // �ػ洰��
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
		RePaintWindows();                                            // �ػ洰��
	}
}

void CMySScomDlg::OnOnCommMscomm() 
{
	VARIANT variant_inp;
    COleSafeArray safearray_inp;
    LONG len, k;
    BYTE rxdata[2048];                                               // ����BYTE���� An 8-bit integerthat is not signed.
    CString strtemp;

	if (m_PortOpened == false) {
		return;
	}

	if (!m_bCanDisplay) {
		return;
	}
	
    if (m_ctrlComm.GetCommEvent() == 2)                              // �¼�ֵΪ2��ʾ���ջ����������ַ�
    {                                                                // ��������Ը����Լ���ͨ��Э����봦�����
        variant_inp   = m_ctrlComm.GetInput();                       // ��������
        safearray_inp = variant_inp;                                 // VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
        len = safearray_inp.GetOneDimSize();                         // �õ���Ч���ݳ���
        
		for (k = 0; k < len; k++) {
            safearray_inp.GetElement(&k, rxdata + k);                // ת��ΪBYTE������
		}
		
        for (k = 0; k < len; k++)                                    // ������ת��ΪCstring�ͱ���
        {
            BYTE bt = *(char *)(rxdata + k);                         // �ַ���
			
			if(m_Check_HexDspl) {
                strtemp.Format("%02X ",bt);                          // ���ַ���ʮ�����Ʒ�ʽ������ʱ����strtemp��ţ�ע���������һ���ո�
            } else {
                strtemp.Format("%c",bt);                             // ���ַ�������ʱ����strtemp���
            }
			
			CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_RECV);
			int nLen = pEdit->GetWindowTextLength();                 // ��ȡ֮ǰ���ݶε��ܳ���
			//pEdit->SetSel(nLen, nLen);                               // ��ȫ����������ѡ��
			//pEdit->ReplaceSel(strtemp);                              // ���ȫ������
			m_Edit_Recv += strtemp;                                  // �����ݸ�����ʾ
        }
    }
	
    UpdateData(FALSE);                                               // ���±༭������

	if (m_Check_AutoSave == TRUE) {
		NeedClearWindow();                                           // �ж��Ƿ���Ҫ����
	}
}
