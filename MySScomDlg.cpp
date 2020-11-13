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

static const CString RecordPath = "Record\\";                        // 定义存放数据文件的文件夹的路径

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
		TempCStr = TempCStr.Right(3);                                // 截取右边有效位
		ResultCStr += TempCStr;
	}
	
	return ResultCStr;
}

void CMySScomDlg::SaveEditContent(void)
{
	CTime   NowTime  = CTime::GetCurrentTime();	                     // 获取现在时间
	CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";
		
	CFile   MyFile;	                                                 // 定义文件类
		
	if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite)) {

		int nLength = StrRecved.GetLength();                         // 文件长度
		MyFile.Write(StrRecved, nLength);                            // 写入文本文件
		MyFile.Close();	                                             // 关闭文件
	}
}

void CMySScomDlg::UpdateEditDisplay(void)
{
	if (m_Check_HexDspl) {                                           // 如果需要16进制显示，进行转换

		m_Edit_Recv = TransformtoHex(StrRecved);
		SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);

		if (m_Check_AutoClear) {                                     // 如果需要自动清空内容

			if (m_Edit_Recv.GetLength() >= MAX_RECV_CHAR) {          // 在16进制模式下，对数据内容长度进行判断
				
				if (m_Check_AutoSave) {

					SaveEditContent();                               // 首先保存编辑框的数据
				}

				StrRecved   = "";
				m_Edit_Recv = "";
				SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);          // 清空编辑框内容
			}
		}

	} else {                                                         // 否则，直接显示数据内容

		m_Edit_Recv = StrRecved;
		SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);

		if (m_Check_AutoClear) {                                     // 如果需要自动清空内容
			
			if (s_Edit_Recv->GetLineCount() >= MAX_RECV_LINE) {      // 在字符模式下，对数据行数进行判断
				
				if (m_Check_AutoSave) {
					
					SaveEditContent();                               // 首先保存编辑框的数据
				}

				StrRecved   = "";
				m_Edit_Recv = "";
				SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);          // 清空编辑框内容
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
		SetTimer(Timer_No_AutoSend, Timer, NULL);                    // 启动定时器
		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(false);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(false);
		m_Edit_Timer = TempStr;                                      // 更新编辑框内容
		SetDlgItemText(IDC_EDIT_TIMER, m_Edit_Timer);
	} else {
		MessageBox("定时时间必须在0至10秒钟之间，请确认！     ", "提示", MB_OK + MB_ICONEXCLAMATION);
		SetDlgItemText(IDC_EDIT_TIMER, m_Edit_Timer);                // 还原编辑框内容
		m_Check_AutoSend = false;
		UpdateData(false);                                           // 取消复选框被选中的状态
		return;
	}
}

void CMySScomDlg::UpdateStatusBarNow(void)
{
	CTime   Nowtime;
	CString TempStr, DisplayStr;	
	
	Nowtime = CTime::GetCurrentTime();
	
	DisplayStr = m_PortOpened ? " 串口已打开" : " 串口未打开";	
	m_StatusBar.SetText(DisplayStr, 1, 0 );

	DisplayStr.Format(" Recv: %.4d", RecvedData);
	m_StatusBar.SetText(DisplayStr, 2, 0 );

	DisplayStr.Format(" Send: %.4d", SendedData);
	m_StatusBar.SetText(DisplayStr, 3, 0 );

	DisplayStr = " 当前时间: " + Nowtime.Format("%Y-%m-%d") + " " + Nowtime.Format("%H:%M:%S");
	m_StatusBar.SetText(DisplayStr, 4, 0);
}

void CMySScomDlg::InitiateStatusBar(void)
{
	m_StatusBar.Create(WS_CHILD | WS_VISIBLE | CCS_BOTTOM, CRect(0, 0, 0, 0), this, 102);
	
	int strPartDim[5] = {300, 400, 500, 600,  -1};                   // 将状态栏划分为若干个区域
	m_StatusBar.SetParts(5, strPartDim);
	
	CTime time;
	CString m_strTime;
	
	time = CTime::GetCurrentTime();
	m_strTime = " 当前时间: " + time.Format("%Y-%m-%d") + " " + time.Format("%H:%M:%S");
	
	m_StatusBar.SetText(" 欢迎使用MySScom - 雅迅网络研发一部测试组", 0, 0 );
	m_StatusBar.SetText(" 串口未打开", 1, 0 );
	m_StatusBar.SetText(" Recv: 0000", 2, 0 );
	m_StatusBar.SetText(" Send: 0000", 3, 0 );
	m_StatusBar.SetText(m_strTime, 4, 0);
}

void CMySScomDlg::InitiateComboComs(void)
{
	EnumComm();                                                      // 枚举可用的串口

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
		
		TempStr.Format("%d 位", Combo_Data[i]);
		
		m_Combo_Data.AddString(TempStr);
	}
}

void CMySScomDlg::InitiateComboStop(void)
{
	CString TempStr;
	
	for (int i = 0; i < (sizeof(Combo_Stop) / sizeof(Combo_Stop[0])); i++) {
		
		TempStr.Format("%d 位", Combo_Stop[i]);
		
		m_Combo_Stop.AddString(TempStr);
	}
}

void CMySScomDlg::SendEditDatatoComm(void)
{
	if (m_bSendPause == FALSE) {                                     // 确认是否允许发送数据

		GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);                  // 获取编辑框的内容

		if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {

			MessageBox("文件内容较大，发送将持续一段时间，请耐心等待......      ", "提示", MB_OK + MB_ICONINFORMATION);
			
			Send_Status  = SEND_LONG_FILE;                           // 如果数据长度过大，则切换到大数据发送模式
			Send_Counter = 0;

			SetTimer(Timer_No_SendFile, MAX_SEND_BYTE, NULL);        // 启动定时器，获取前N个字符发送

			StrToSend = m_Edit_Send.Left(MAX_SEND_BYTE);
			Send_Counter++;

			m_ctrlComm.SetOutput(COleVariant(StrToSend));            // 发送ASCII字符数据
			SendedData += StrToSend.GetLength();                     // 发送字节数累加

		} else {

			Send_Status  = SEND_SHORT_DATA;                          // 否则，切换到小数据模式，并停止定时器
			KillTimer(Timer_No_SendFile);

			if (m_Check_HexSend) {                                   // 如果需要以16进制发送
				
				CByteArray hexdata;
				int len;                                             // 此处返回的len可以用于计算发送了多少个十六进制数
				
				len = String2Hex(m_Edit_Send, hexdata);
				
				m_ctrlComm.SetOutput(COleVariant(hexdata));          // 发送十六进制数据
				
				SendedData += len;                                   // 发送字节数累加
				
			} else {
				
				m_ctrlComm.SetOutput(COleVariant(m_Edit_Send));      // 发送ASCII字符数据
				
				SendedData += m_Edit_Send.GetLength();               // 发送字节数累加
			}
		}

		UpdateStatusBarNow();                                        // 更新状态栏统计数据的显示
	}
}

void CMySScomDlg::ContinueToSendFile(void)
{
	if (m_bSendPause == FALSE) {                                     // 确认是否允许发送数据

		if (Send_Status == SEND_LONG_FILE) {
			
			Send_Counter++;
			
			if (m_Edit_Send.GetLength() >= (Send_Counter * MAX_SEND_BYTE)) {
				
				StrToSend = m_Edit_Send.Left(Send_Counter * MAX_SEND_BYTE);
				StrToSend = StrToSend.Right(MAX_SEND_BYTE);
				
			} else {                                                 // 截取最后一部分字符发送
				
				StrToSend = m_Edit_Send.Left(Send_Counter * MAX_SEND_BYTE);
				StrToSend = StrToSend.Right(MAX_SEND_BYTE - (Send_Counter * MAX_SEND_BYTE - m_Edit_Send.GetLength()));
				
				Send_Status = SEND_SHORT_DATA;                       // 发送完毕，重新切换到小数据模式
				KillTimer(Timer_No_SendFile);                        // 停止定时器
			}
		}
		
		m_ctrlComm.SetOutput(COleVariant(StrToSend));                // 发送ASCII字符数据
		
		SendedData += StrToSend.GetLength();                         // 发送字节数累加
		
		UpdateStatusBarNow();                                        // 更新状态栏统计数据的显示
	}
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
	CString TempStr, SettingStr;
    
	if (m_PortOpened == true) {                                      // 如果串口已经打开，那么执行关闭操作

		if (m_Check_AutoSend) {
			MessageBox("请首先停用自动发送功能再尝试关闭串口    ", "抱歉", MB_OK + MB_ICONEXCLAMATION);
			return;
		}
		
		m_ctrlComm.SetPortOpen(FALSE);

		MessageBox("◆◆◆   成功关闭串口!   ◆◆◆    ", "提示", MB_OK + MB_ICONINFORMATION);

		SetDlgItemText(IDC_BUTTON_ONOFF, "打开串口");

		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(TRUE);

		SetControlStatus(FALSE);

		RecvedData = 0;                                              // 累计单元清零
		SendedData = 0;

		m_PortOpened = FALSE;

		return;
	}

	int Number = m_Combo_ComNo.GetCurSel();                          // 得到串口号
	
	if (Number == 0) {
		MessageBox("串口号都没有选择，你叫我打开什么东东...？      ", "提示", MB_OK + MB_ICONINFORMATION);
        return;
    }
	
	if (m_ctrlComm.GetPortOpen()) {                                  // 判断是否已经打开
        m_ctrlComm.SetPortOpen(FALSE);
	}
	
	m_Combo_ComNo.GetLBText(Number, TempStr);
	TempStr.TrimLeft("COM");                                         // 删除"COM"字段
	
	m_ctrlComm.SetCommPort(atoi(TempStr.Mid(0)));
	
    if (!m_ctrlComm.GetPortOpen()) {

        m_ctrlComm.SetPortOpen(TRUE);                                // 尝试打开串口

		SettingStr = "";
		
		int ComBaudSel = m_Combo_Baud.GetCurSel();                   // 获取波特率的选择项
		TempStr.Format("%d", Combo_Baud[ComBaudSel]);
		SettingStr += TempStr;
		
		SettingStr += ",n,";
		
		int ComDataSel = m_Combo_Data.GetCurSel();                   // 获取数据位的选择项
		TempStr.Format("%d", Combo_Data[ComDataSel]);
		SettingStr += TempStr;
		
		SettingStr += ",";
		
		int ComStopSel = m_Combo_Stop.GetCurSel();                   // 获取停止位的选择项
		TempStr.Format("%d", Combo_Stop[ComStopSel]);
		SettingStr += TempStr;
		
		m_ctrlComm.SetSettings(SettingStr);                          // 波特率(XXXX)，无校验，8个数据位，1个停止位 
		
		m_ctrlComm.SetInputMode(1);                                  // 1表示以二进制方式检取数据
		m_ctrlComm.SetRThreshold(1);                                 // 参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
		m_ctrlComm.SetInputLen(0);                                   // 设置当前接收区数据长度为0
		m_ctrlComm.GetInput();                                       // 先预读缓冲区以清除残留数据
		
		m_PortOpened = TRUE;
		
		MessageBox("※※※   成功打开串口!   ※※※    ", "恭喜", MB_OK + MB_ICONINFORMATION);
		
		SetDlgItemText(IDC_BUTTON_ONOFF, "关闭串口");
		
		SetControlStatus(TRUE);                                      // 启用各个按钮控件
		
		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);

	} else {

        MessageBox("打开串口失败，该串口可能正在使用中...  ", "提示", MB_OK + MB_ICONERROR);
	}
}

void CMySScomDlg::OnButtonPause() 
{
	if (m_bCanDisplay == false) {
		m_bCanDisplay = TRUE;
		SetDlgItemText(IDC_BUTTON_PAUSE, "暂停接收");
		GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(TRUE);
	} else {
		m_bCanDisplay = false;
		SetDlgItemText(IDC_BUTTON_PAUSE, "恢复接收");
		GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(FALSE);
	}
}

void CMySScomDlg::OnButtonClear() 
{
	StrRecved = "";
	
	m_Edit_Recv = "";
	SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);

	RecvedData = 0;
	UpdateStatusBarNow();                                            // 更新状态栏的统计数据显示
}

void CMySScomDlg::OnButtonSave() 
{
	CTime   NowTime  = CTime::GetCurrentTime();	                     // 获取现在时间
	CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt"; // 指定文件名
	
    CString Temp_String;                                             // 临时变量
	CFile   MyFile;	                                                 // 定义文件类
	int     nLength = Temp_String.GetLength();                       // 文件长度

	if (nLength <= 0) {
		MessageBox("尚未接收到任何内容，无须保存！          ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite) == 0) {
		Temp_String = "文件 " + FileName + " 创建失败!         ";
		MessageBox(Temp_String, "抱歉", MB_OK + MB_ICONHAND);
		return;
	} else {
		Temp_String = "文件 " + FileName + " 创建成功!         ";
		MessageBox(Temp_String, "恭喜", MB_OK + MB_ICONINFORMATION);
	}
	
	GetDlgItem(IDC_EDIT_RECV)->GetWindowText(Temp_String);           // 取得输入框的数据
	
	MyFile.Write(Temp_String, nLength);	                             // 写入文本文件
	MyFile.Close();	                                                 // 关闭文件
}

void CMySScomDlg::OnButtonRead() 
{
	if (m_Check_AutoSend) {
		MessageBox("自动发送功能已开启，请先停用之！    ", "抱歉", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	CFile myFile;

	CFileDialog dlg(TRUE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		            "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*|");
	
	if (dlg.DoModal() != IDOK) {
		return;
	}
	
	CString FilePath = dlg.GetPathName();						     // 保存文件的路径
		
	if (myFile.Open(FilePath, CFile::modeRead) == 0) {
		MessageBox("读取文件失败，请确认路径正确且文件未处于打开状态！    ", "抱歉", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	myFile.SeekToBegin();
	
	int nLength = myFile.GetLength();
	char * TempStr = new char[nLength];							     // 分配空间
	CString ResultStr;
	
	myFile.Read(TempStr, nLength);								     // 读取文件内容
	myFile.Close();												     // 关闭文件
	
	ResultStr.Format(_T("%s"), TempStr);
	ResultStr = ResultStr.Left(nLength);
	
	nLength = s_Edit_Send->GetWindowTextLength();                    // 数据显示
	s_Edit_Send->SetSel(nLength, nLength);
	s_Edit_Send->ReplaceSel(ResultStr);
	nLength += ResultStr.GetLength();
    m_Edit_Send = ResultStr;                                         // 显示内容
	SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
	
	delete []TempStr;											     // 释放空间
}

void CMySScomDlg::OnButtonRespite() 
{
	if (m_bSendPause == TRUE) {
		m_bSendPause = FALSE;
		SetDlgItemText(IDC_BUTTON_RESPITE, "暂停发送");
		GetDlgItem(IDC_BUTTON_READ)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	} else {
		m_bSendPause = TRUE;
		SetDlgItemText(IDC_BUTTON_RESPITE, "恢复发送");
		GetDlgItem(IDC_BUTTON_READ)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	}
}

void CMySScomDlg::OnButtonReiput() 
{
	m_Edit_Send = "";
	SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);

	SendedData = 0;
	UpdateStatusBarNow();                                            // 更新状态栏的统计数据显示
}

void CMySScomDlg::OnButtonSend() 
{
	if (m_Edit_Send.GetLength() <= 0) {
		MessageBox("发送窗口内容为空，未发送任何数据！    ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	SendEditDatatoComm();
}

void CMySScomDlg::OnButtonCount() 
{
	RecvedData = 0;
	SendedData = 0;

	UpdateStatusBarNow();                                            // 更新状态栏的统计数据显示
}

void CMySScomDlg::OnCheckHexDisplay() 
{
	m_Check_HexDspl = !m_Check_HexDspl;

	UpdateEditDisplay();                                             // 更新显示
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

		if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {              // 确保输入的数据不会过长

			MessageBox("您输入的数据过长，无法一次发送完成。请分批输入或者以文件形式发送......       ", "提示", MB_OK + MB_ICONINFORMATION);
			m_Check_AutoSend = FALSE;
			UpdateData(FALSE);
			return;
		}

		NeedAutoSendData();                                          // 开始自动发送数据

	} else {

		KillTimer(Timer_No_AutoSend);                                // 否则，用户取消了自动发送的功能
		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(true);
	}
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

	s_Edit_Recv = (CEdit*)GetDlgItem(IDC_EDIT_RECV);
	s_Edit_Send = (CEdit*)GetDlgItem(IDC_EDIT_SEND);

	InitiateStatusBar();

	InitiateComboComs();                                             // 初始化选择串口号的列表框
	InitiateComboBaud();                                             // 初始化选择波特率的列表框
	InitiateComboData();                                             // 初始化选择数据位的列表框
	InitiateComboStop();                                             // 初始化选择停止位的列表框

	m_Combo_ComNo.SetCurSel(0);
	m_Combo_Baud.SetCurSel(2);
	m_Combo_Data.SetCurSel(3);
	m_Combo_Stop.SetCurSel(1);

	GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);                 // 暂不提供数据位和停止位的选择
	GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);

	GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(FALSE);

	SetControlStatus(false);                                         // 首先禁用各个按钮控件

	m_bCanDisplay = TRUE;
	m_bSendPause  = FALSE;
	m_PortOpened  = FALSE;

	StrRecved = "";
	StrToSend = "";

	Send_Status  = SEND_SHORT_DATA;
	Send_Counter = 0;

	RecvedData = 0;
	SendedData = 0;

	CreateDirectory(RecordPath, NULL);                               // 创建Record文件夹，用于保存数据

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

	RePaintWindows();                                                // 重绘窗口

	return TRUE;
}

void CMySScomDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == Timer_No_StatusBar) {                            // 状态栏定时更新
		UpdateStatusBarNow();
	} else if (nIDEvent == Timer_No_AutoSend) {                      // 自动发送短数据
		SendEditDatatoComm();
	} else if (nIDEvent == Timer_No_SendFile) {                      // 处于发送文件状态
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
		RePaintWindows();                                            // 重绘窗口
	}
}

void CMySScomDlg::OnOnCommMscomm() 
{
	VARIANT       Input_Vrt;
    COleSafeArray Input_Ary;
    LONG RecvLen, i;
    BYTE RecvData[2048];                                               // 设置BYTE数组
    CString TempStr;

	if ((m_PortOpened == false) || (!m_bCanDisplay)) {
		return;
	}
	
    if (m_ctrlComm.GetCommEvent() == 2) {                            // 事件值为2表示接收缓冲区内有字符

        Input_Vrt = m_ctrlComm.GetInput();                           // 读缓冲区
        Input_Ary = Input_Vrt;                                       // VARIANT型变量转换为ColeSafeArray型变量
        RecvLen   = Input_Ary.GetOneDimSize();                       // 得到有效数据长度
        
		for (i = 0; i < RecvLen; i++) {
            Input_Ary.GetElement(&i, RecvData + i);                  // 转换为BYTE型数组存放到RecvData数组
		}
		
        for (i = 0; i < RecvLen; i++) {                              // 将数组转换为Cstring型变量

            BYTE bt = *(char *)(RecvData + i);                       // 转换为字符型

			TempStr.Format("%c", bt);
			StrRecved += TempStr;                                    // 保存数据内容
			
			RecvedData++;                                            // 接收字节数累加
        }

		StrRecved.Left(RecvLen);
		
		UpdateEditDisplay();                                         // 更新编辑框内容显示

		UpdateStatusBarNow();                                        // 更新状态栏统计数据的显示
    }
}

