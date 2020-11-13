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
	ON_BN_CLICKED(IDC_BUTTON_COUNT, OnButtonCount)
	ON_BN_CLICKED(IDC_CHECK_AUTOCLEAR, OnCheckAutoClear)
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

	GetDlgItem(IDC_STATIC_CONTROL)->MoveWindow(10, 10, 158, Main.Height() - 40);
	
	GetDlgItem(IDC_STATIC_RECEIVE)->MoveWindow(180, 10, Main.Width() - 190, Main.Height() - 130);
	GetDlgItem(IDC_EDIT_RECV)->MoveWindow(190, 28, Main.Width() - 210, Main.Height() - 156);
	
	GetDlgItem(IDC_STATIC_SEND)->MoveWindow(180, Main.Height() - 112, Main.Width() - 190, 82);
	GetDlgItem(IDC_EDIT_SEND)->MoveWindow(190, Main.Height() - 94, Main.Width() - 210, 56);
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
	m_StatusBar.SetText(DisplayStr, 1, 0 );

	DisplayStr.Format(" Recv: %.4d", RecvedData);
	m_StatusBar.SetText(DisplayStr, 2, 0 );

	DisplayStr.Format(" Send: %.4d", SendedData);
	m_StatusBar.SetText(DisplayStr, 3, 0 );

	DisplayStr = " ��ǰʱ��: " + Nowtime.Format("%Y-%m-%d") + " " + Nowtime.Format("%H:%M:%S");
	m_StatusBar.SetText(DisplayStr, 4, 0);
}

void CMySScomDlg::InitiateStatusBar(void)
{
	m_StatusBar.Create(WS_CHILD | WS_VISIBLE | CCS_BOTTOM, CRect(0, 0, 0, 0), this, 102);
	
	int strPartDim[5] = {300, 400, 500, 600,  -1};                   // ��״̬������Ϊ���ɸ�����
	m_StatusBar.SetParts(5, strPartDim);
	
	CTime time;
	CString m_strTime;
	
	time = CTime::GetCurrentTime();
	m_strTime = " ��ǰʱ��: " + time.Format("%Y-%m-%d") + " " + time.Format("%H:%M:%S");
	
	m_StatusBar.SetText(" ��ӭʹ��MySScom - ��Ѹ�����з�һ��������", 0, 0 );
	m_StatusBar.SetText(" ����δ��", 1, 0 );
	m_StatusBar.SetText(" Recv: 0000", 2, 0 );
	m_StatusBar.SetText(" Send: 0000", 3, 0 );
	m_StatusBar.SetText(m_strTime, 4, 0);
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

void CMySScomDlg::SendEditDatatoComm(void)
{
	if (m_bSendPause == FALSE) {                                     // ȷ���Ƿ�����������

		GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);                  // ��ȡ�༭�������

		if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {

			MessageBox("�ļ����ݽϴ󣬷��ͽ�����һ��ʱ�䣬�����ĵȴ�......      ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			
			Send_Status  = SEND_LONG_FILE;                           // ������ݳ��ȹ������л��������ݷ���ģʽ
			Send_Counter = 0;

			SetTimer(Timer_No_SendFile, MAX_SEND_BYTE, NULL);        // ������ʱ������ȡǰN���ַ�����

			StrToSend = m_Edit_Send.Left(MAX_SEND_BYTE);
			Send_Counter++;

			m_ctrlComm.SetOutput(COleVariant(StrToSend));            // ����ASCII�ַ�����
			SendedData += StrToSend.GetLength();                     // �����ֽ����ۼ�

		} else {

			Send_Status  = SEND_SHORT_DATA;                          // �����л���С����ģʽ����ֹͣ��ʱ��
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
		}
		
		m_ctrlComm.SetOutput(COleVariant(StrToSend));                // ����ASCII�ַ�����
		
		SendedData += StrToSend.GetLength();                         // �����ֽ����ۼ�
		
		UpdateStatusBarNow();                                        // ����״̬��ͳ�����ݵ���ʾ
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
	CString TempStr, SettingStr;
    
	if (m_PortOpened == true) {                                      // ��������Ѿ��򿪣���ôִ�йرղ���

		if (m_Check_AutoSend) {
			MessageBox("������ͣ���Զ����͹����ٳ��Թرմ���    ", "��Ǹ", MB_OK + MB_ICONEXCLAMATION);
			return;
		}
		
		m_ctrlComm.SetPortOpen(FALSE);

		MessageBox("������   �ɹ��رմ���!   ������    ", "��ʾ", MB_OK + MB_ICONINFORMATION);

		SetDlgItemText(IDC_BUTTON_ONOFF, "�򿪴���");

		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(TRUE);

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
		
		MessageBox("������   �ɹ��򿪴���!   ������    ", "��ϲ", MB_OK + MB_ICONINFORMATION);
		
		SetDlgItemText(IDC_BUTTON_ONOFF, "�رմ���");
		
		SetControlStatus(TRUE);                                      // ���ø�����ť�ؼ�
		
		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);

	} else {

        MessageBox("�򿪴���ʧ�ܣ��ô��ڿ�������ʹ����...  ", "��ʾ", MB_OK + MB_ICONERROR);
	}
}

void CMySScomDlg::OnButtonPause() 
{
	if (m_bCanDisplay == false) {
		m_bCanDisplay = TRUE;
		SetDlgItemText(IDC_BUTTON_PAUSE, "��ͣ����");
		GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(TRUE);
	} else {
		m_bCanDisplay = false;
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
	CTime   NowTime  = CTime::GetCurrentTime();	                     // ��ȡ����ʱ��
	CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt"; // ָ���ļ���
	
    CString Temp_String;                                             // ��ʱ����
	CFile   MyFile;	                                                 // �����ļ���
	int     nLength = Temp_String.GetLength();                       // �ļ�����

	if (nLength <= 0) {
		MessageBox("��δ���յ��κ����ݣ����뱣�棡          ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite) == 0) {
		Temp_String = "�ļ� " + FileName + " ����ʧ��!         ";
		MessageBox(Temp_String, "��Ǹ", MB_OK + MB_ICONHAND);
		return;
	} else {
		Temp_String = "�ļ� " + FileName + " �����ɹ�!         ";
		MessageBox(Temp_String, "��ϲ", MB_OK + MB_ICONINFORMATION);
	}
	
	GetDlgItem(IDC_EDIT_RECV)->GetWindowText(Temp_String);           // ȡ������������
	
	MyFile.Write(Temp_String, nLength);	                             // д���ı��ļ�
	MyFile.Close();	                                                 // �ر��ļ�
}

void CMySScomDlg::OnButtonRead() 
{
	if (m_Check_AutoSend) {
		MessageBox("�Զ����͹����ѿ���������ͣ��֮��    ", "��Ǹ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	CFile myFile;

	CFileDialog dlg(TRUE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		            "�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*|");
	
	if (dlg.DoModal() != IDOK) {
		return;
	}
	
	CString FilePath = dlg.GetPathName();						     // �����ļ���·��
		
	if (myFile.Open(FilePath, CFile::modeRead) == 0) {
		MessageBox("��ȡ�ļ�ʧ�ܣ���ȷ��·����ȷ���ļ�δ���ڴ�״̬��    ", "��Ǹ", MB_OK + MB_ICONINFORMATION);
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
	if (m_Edit_Send.GetLength() <= 0) {
		MessageBox("���ʹ�������Ϊ�գ�δ�����κ����ݣ�    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	SendEditDatatoComm();
}

void CMySScomDlg::OnButtonCount() 
{
	RecvedData = 0;
	SendedData = 0;

	UpdateStatusBarNow();                                            // ����״̬����ͳ��������ʾ
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

	if (m_Check_AutoSend) {

		if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {              // ȷ����������ݲ������

			MessageBox("����������ݹ������޷�һ�η�����ɡ����������������ļ���ʽ����......       ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			m_Check_AutoSend = FALSE;
			UpdateData(FALSE);
			return;
		}

		NeedAutoSendData();                                          // ��ʼ�Զ���������

	} else {

		KillTimer(Timer_No_AutoSend);                                // �����û�ȡ�����Զ����͵Ĺ���
		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(true);
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

	m_Combo_ComNo.SetCurSel(0);
	m_Combo_Baud.SetCurSel(2);
	m_Combo_Data.SetCurSel(3);
	m_Combo_Stop.SetCurSel(1);

	GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);                 // �ݲ��ṩ����λ��ֹͣλ��ѡ��
	GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);

	GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(FALSE);

	SetControlStatus(false);                                         // ���Ƚ��ø�����ť�ؼ�

	m_bCanDisplay = TRUE;
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
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");
	}

	RePaintWindows();                                                // �ػ洰��

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
	
	CWnd *pWnd = GetDlgItem(IDC_EDIT_RECV);
	
	if (pWnd) {
		RePaintWindows();                                            // �ػ洰��
	}
}

void CMySScomDlg::OnOnCommMscomm() 
{
	VARIANT       Input_Vrt;
    COleSafeArray Input_Ary;
    LONG RecvLen, i;
    BYTE RecvData[2048];                                               // ����BYTE����
    CString TempStr;

	if ((m_PortOpened == false) || (!m_bCanDisplay)) {
		return;
	}
	
    if (m_ctrlComm.GetCommEvent() == 2) {                            // �¼�ֵΪ2��ʾ���ջ����������ַ�

        Input_Vrt = m_ctrlComm.GetInput();                           // ��������
        Input_Ary = Input_Vrt;                                       // VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
        RecvLen   = Input_Ary.GetOneDimSize();                       // �õ���Ч���ݳ���
        
		for (i = 0; i < RecvLen; i++) {
            Input_Ary.GetElement(&i, RecvData + i);                  // ת��ΪBYTE�������ŵ�RecvData����
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

