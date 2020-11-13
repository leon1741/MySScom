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

static const CString RecordPath = "Record\\";                        // 定义存放数据文件的文件夹的路径

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

	AfxInitRichEdit();                                               // 初始化RichEdit控件
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


/* ==================================== 自定义函数区--开始 ===================================== */

/**************************************************************************************************
**  函数名称:  SPCommProc
**  功能描述:  串口线程处理函数
**  输入参数:  
**  返回参数:  
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
    
    os.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);                          /* 创建事件内核对象 */
    
    if (os.hEvent == NULL) {                                                   /* 创建失败 */
        AfxMessageBox("Can't create event object!");
        return -1;
    }
    
    while (pDlg->m_PortOpened) {
        
        ClearCommError(pDlg->m_hSPCom, &dwErrorFlags, &ComStat);               /* 探询串口缓冲区 */
        
        if (ComStat.cbInQue) {                                                 /* 如果接收队列不为空 */
            
            length = pDlg->ReadComm(buf, MAX_SEND_BYTE);                       /* 读取1024个字节的数据 */
            
            pDlg->HandleUSARTData(buf, length);                                /* 通知主进程处理串口数据 */
        }
        
        dwMask = 0;
        
        if (!WaitCommEvent(pDlg->m_hSPCom, &dwMask, &os)) {                    /* 判断串口通信事件是否已经发生 */
            
            if (GetLastError() == ERROR_IO_PENDING) {                          /* 判断是否存在数据等待操作 */
                GetOverlappedResult(pDlg->m_hSPCom, &os, &dwTrans, TRUE);
            } else {                                                           /* 关闭事件内核对象 */
                CloseHandle(os.hEvent);
                return -1;
            }
        }
    }
    
    CloseHandle(os.hEvent);                                                    /* 关闭事件内核对象 */
    
    return 0;
}

/**************************************************************************************************
**  函数名称:  EnumComm
**  功能描述:  本函数用来枚举电脑上存在可用的串口
**  输入参数:  
**  返回参数:  
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
**  函数名称:  ReadComm
**  功能描述:  从串口获取数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
DWORD CMySScomDlg::ReadComm(char *buf, DWORD dwLength)
{
    DWORD length = 0;
    COMSTAT ComStat;
    DWORD dwErrorFlags;

    ClearCommError(m_hSPCom, &dwErrorFlags, &ComStat);                         /* 首先清除错误标志 */

    length = min(dwLength, ComStat.cbInQue);

    ReadFile(m_hSPCom, buf, length, &length, &m_osRead);                       /* 读取串口数据 */

    return length;
}

/**************************************************************************************************
**  函数名称:  WriteComm
**  功能描述:  向串口发送数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
DWORD CMySScomDlg::WriteComm(char *buf, DWORD dwLength)
{
    DWORD length = dwLength;
    COMSTAT ComStat;
    DWORD dwErrorFlags;

    ClearCommError(m_hSPCom, &dwErrorFlags, &ComStat);                         /* 首先清除错误标志 */

    WriteFile(m_hSPCom, buf, length, &length, &m_osWrite);                     /* 写入串口数据 */

    if (GetLastError() == ERROR_IO_PENDING) {                                  /* 正在处理重叠的部分，获取其长度 */
        GetOverlappedResult(m_hSPCom, &m_osWrite, &length, TRUE);
    } else {                                                                   /* 否则，发送失败，返回0 */
        length = 0;
    }

    return length;
}

/**************************************************************************************************
**  函数名称:  SetControlStatus
**  功能描述:  设置控件的状态
**  输入参数:  
**  返回参数:  
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
**  函数名称:  SetSendButtonStatus
**  功能描述:  设置发送按钮的状态
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::SetSendButtonStatus(bool Enable)
{
    GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(Enable);
}

/**************************************************************************************************
**  函数名称:  SetSendingStatus
**  功能描述:  
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::SetSendingStatus(bool Enable)
{
    GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(Enable);
    GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
}

/**************************************************************************************************
**  函数名称:  SwitchSendStatus
**  功能描述:  切换发送状态
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::SwitchSendStatus(bool IsNormal)
{
    GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(IsNormal);
    GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(IsNormal);
    GetDlgItem(IDC_STATIC_MS)->EnableWindow(IsNormal);
}

/**************************************************************************************************
**  函数名称:  ConvertHexChar
**  功能描述:  若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1
**  输入参数:  
**  返回参数:  
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
**  函数名称:  String2Hex
**  功能描述:  字符串转换为16进制数据
**  输入参数:  
**  返回参数:  
**  注意事项:  由于这个转换函数的格式限制，在发送框中的十六制字符应该每两个字符之间插入一个空隔
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
**  函数名称:  TransformtoHex
**  功能描述:  字符串转换为16进制
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
CString CMySScomDlg::TransformtoHex(CString InputStr)
{
    CString TempCStr, ResultCStr;
    
    ResultCStr = "";
    
    for (int i = 0; i < InputStr.GetLength(); i++) {
        TempCStr.Format("%.2X ", InputStr[i]);
        TempCStr = TempCStr.Right(3);                                          /* 截取右边有效位 */
        ResultCStr += TempCStr;
    }
    
    return ResultCStr;
}

/**************************************************************************************************
**  函数名称:  CharisValid
**  功能描述:  判断字符是否合法
**  输入参数:  
**  返回参数:  
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
**  函数名称:  InformDlgClose
**  功能描述:  处理高级发送窗口的消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::InformDlgClose(void)
{
	SetDlgItemText(IDC_BUTTON_SRSEND, "高级发送");
	
	GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
}

/**************************************************************************************************
**  函数名称:  SaveEditContent
**  功能描述:  保存编辑框的内容到文本文件
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::SaveEditContent(void)
{
    CTime   NowTime  = CTime::GetCurrentTime();                                /* 获取现在时间 */
    CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";
        
    CFile   MyFile;                                                            /* 定义文件类 */
        
    if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite)) {

        int nLength = StrRecved.GetLength();                                   /* 文件长度 */
        MyFile.Write(StrRecved, nLength);                                      /* 写入文本文件 */
        MyFile.Close();                                                        /* 关闭文件 */
    }
}

/**************************************************************************************************
**  函数名称:  UpdateEditDisplay
**  功能描述:  更新编辑框的显示
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::UpdateEditDisplay(void)
{
    CWnd *hwnd;
    
    if (m_Check_HexDspl) {                                                     /* 如果需要16进制显示，进行转换 */

        m_Edit_Recv = TransformtoHex(StrRecved);
        SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
        s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);                    /* 让编辑框内容滚动到最后一行 */

        if (m_Check_AutoClear) {                                               /* 如果需要自动清空内容 */

            if (RecvedData >= MaxRecvLines) {                                  /* 在16进制模式下，对数据内容长度进行判断 */

                RecvedLine = 0;                                                /* 首先清空变量值 */
                RecvedData = 0;
                
                if (m_Check_AutoSave) {
                    SaveEditContent();                                         /* 保存编辑框的数据 */
                }

                StrRecved   = "";
                m_Edit_Recv = "";
                SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);                    /* 清空编辑框内容 */
            }
        }

    } else {                                                                   /* 否则，直接显示数据内容 */

        m_Edit_Recv = StrRecved;
        SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
        s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);                    /* 让编辑框内容滚动到最后一行 */

        if (m_Check_AutoClear) {                                               /* 如果需要自动清空内容 */
            
            if (RecvedLine >= MaxRecvLines) {                                  /* 在字符模式下，对数据行数进行判断 */

                RecvedLine = 0;                                                /* 首先清空变量值 */
                RecvedData = 0;

                if (m_Check_AutoSave) {
                    SaveEditContent();                                         /* 保存编辑框的数据 */
                }

                StrRecved   = "";
                m_Edit_Recv = "";
                SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);                    /* 清空编辑框内容 */
            }
        }
    }

    /*************************************************************************************************\
    |                          以下语句实现对接收编辑框的闪屏现象的屏蔽作用                           |
    \*************************************************************************************************/
    
    hwnd = GetDlgItem(IDC_EDIT_RECV);                                          /* 获取接收编辑框的控件ID */

    if (GetFocus() == hwnd) {                                                  /* 将窗口焦点转移至发送编辑框 */
        GetDlgItem(IDC_EDIT_SEND)->SetFocus();
    }
}

/**************************************************************************************************
**  函数名称:  HandleUSARTData
**  功能描述:  接收串口数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::HandleUSARTData(char *ptr, DWORD len)
{
    DWORD i;
    CString TempStr, TimeStr;
    CTime NowTime;

    if (m_bRecvPause == TRUE) return;

    for (i = 0; i < len; i++) {                                                /* 将数组转换为Cstring型变量 */
        
        #if 0                                                                  /* 以下方式为普通显示模式(会造成16进制显示模式下0x00的丢失) */

        TempStr.Format("%c", ptr[i]);

        #else                                                                  /* 以下方式可以处理0字符的显示bug，但是会造成字符模式下丢失0x00字符后的全部数据 */

        if (ptr[i] == 0) {
            TempStr = CString(ptr[i]);
        } else {
            TempStr.Format("%c", ptr[i]);
        }

        #endif
        
        if (m_Check_ShowTime == TRUE) {                                        /* 只有在启用时间显示功能时才判断 */
            
            if (TempStr == "\n") {                                             /* 本次接收到了回车符，切换到下一行显示 */
                m_NeedTime = TRUE;
                RecvedLine++;

            } else {
                if (m_NeedTime == TRUE) {
                    NowTime = CTime::GetCurrentTime();                         /* 获取现在时间 */
                    TimeStr = NowTime.Format("[%H:%M:%S] ");
                    
                    StrRecved += TimeStr;                                      /* 在行头显示时间 */
                    m_NeedTime = FALSE;
                }
            }
        } else {                                                               /* 不需要在行头位置显示时间 */
            
            if (m_Check_HexDspl == FALSE) {                                    /* 当前不处于16进制显示模式 */
                
                if (TempStr == "\n") {                                         /* 本次接收到回车符 */
                    RecvedLine++;
                }
            } else {
                
                RecvedLine = 0;                                                /* 16进制模式下不进行判断 */
            }
        }
        
        StrRecved += TempStr;                                                  /* 保存数据内容 */
        RecvedData++;                                                          /* 接收字节数累加 */
    }

    m_DataRecvd = TRUE;
}

/**************************************************************************************************
**  函数名称:  NeedAutoSendData
**  功能描述:  启动定时发送数据的功能
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::NeedAutoSendData(void)
{
    int Timer;
    CString TempStr;

    GetDlgItemText(IDC_EDIT_TIMER, TempStr);
    
    Timer = atoi((LPSTR)(LPCTSTR)TempStr);
    
    if ((Timer > 0) && (Timer <= 100000)) {

        SetTimer(Timer_No_AutoSend, Timer, NULL);                              /* 启动定时器 */

        GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);

        m_Edit_AutoTimer = TempStr;                                            /* 更新编辑框内容 */
        SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);

        SetSendButtonStatus(FALSE);                                            /* 禁用发送区各个按钮 */

    } else {

        MessageBox("定时时间必须在0至100秒钟之间，请确认！  ", "提示", MB_OK + MB_ICONEXCLAMATION);

        SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);                      /* 还原编辑框内容 */

        m_Check_AutoSend = FALSE;
        UpdateData(FALSE);                                                     /* 取消复选框被选中的状态 */

        return;
    }
}

/**************************************************************************************************
**  函数名称:  UpdateStatusBarNow
**  功能描述:  更新状态栏的显示
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::UpdateStatusBarNow(void)
{
    CTime   Nowtime;
    CString TempStr, DisplayStr;
    CRect   DialogMain;

    this->GetWindowRect(&DialogMain);                                          /* 获取主界面在屏幕上的位置 */

	if (DialogMain.Width() > 1260) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发一部外设组 - Designed By LEON (LEON1741@126.com) - 仅限内部交流，谢谢！";
	} else if (DialogMain.Width() > 1160) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发一部外设组 - Designed By LEON (LEON1741@126.com)";
	} else if (DialogMain.Width() > 1080) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发一部外设组 - Designed By LEON";
	} else if (DialogMain.Width() > 1000) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发一部外设组 - LEON";
	} else if (DialogMain.Width() > 950) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发一部外设组";
	} else if (DialogMain.Width() > 900) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发一部";
	} else if (DialogMain.Width() > 840) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络";
	} else {
		DisplayStr = " 欢迎使用MySScom";
	}

	m_StatusBar.SetPaneText(0, DisplayStr);
    
    Nowtime = CTime::GetCurrentTime();
    
    DisplayStr = m_PortOpened ? " 串口已打开" : " 串口未打开";  
    m_StatusBar.SetPaneText(1, DisplayStr);

    DisplayStr.Format(" Lines: %.5d", RecvedLine);
    m_StatusBar.SetPaneText(2, DisplayStr);
        
    DisplayStr.Format(" Recv: %.6d", RecvedData);
    m_StatusBar.SetPaneText(3, DisplayStr);

    DisplayStr.Format(" Send: %.6d", SendedData);
    m_StatusBar.SetPaneText(4, DisplayStr);

    DisplayStr = " 当前时间: " + Nowtime.Format("%Y-%m-%d") + " " + Nowtime.Format("%H:%M:%S");
    m_StatusBar.SetPaneText(5, DisplayStr);
}

/**************************************************************************************************
**  函数名称:  SendDatatoComm
**  功能描述:  将指定的字符串发送出去
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CMySScomDlg::SendDatatoComm(CString datastr, BOOL needhex)
{
	int i;
	unsigned char tchar;
	char temp[MAX_SEND_BYTE];
	
	if (datastr.GetLength() > MAX_SEND_BYTE) {                                 /* 数据长度过大 */
        return FALSE;
    }
	
    if (needhex) {                                                             /* 如果需要以16进制发送 */

		for (i = 0; i <= datastr.GetLength(); ) {                              /* 判断数据内容的字符是否合法 */

			tchar = datastr[i++];                                              /* 判断第1个字符是否有效 */
			
			if (!CharisValid(tchar)) {
				return FALSE;
			}
			
			tchar = datastr[i++];                                              /* 判断第2个字符是否有效 */
			
			if (!CharisValid(tchar)) {
				return FALSE;
			}
			
			if (i >= datastr.GetLength() - 1) {                                /* 如果是最后一个数据，则不需要判断其空格 */
				break;
			}
			
			tchar = datastr[i++];                                              /* 判断第3个字符是否为空格 */
			
			if (tchar != ' ') {
				return FALSE;
			}
		}
        
        CByteArray hexdata;
        int j, len;                                                            /* 此处返回的len可以用于计算发送了多少个十六进制数 */
		
        len = String2Hex(datastr, hexdata);
		
        for (j = 0; j < len; j++) {
            temp[j] = hexdata.GetAt(j);
        }
        
        WriteComm(temp, len);
		
        SendedData += len;                                                     /* 发送字节数累加 */
        
    } else {
        
        strncpy(temp, (LPCTSTR)datastr, sizeof(temp));
        
        WriteComm(temp, datastr.GetLength());
		
        SendedData += datastr.GetLength();                                     /* 发送字节数累加 */
    }
	
    if (m_Check_Return) {                                                      /* 补发回车换行符 */
		
        temp[0] = '\r';
        temp[1] = '\n';
        
        WriteComm(temp, 2);
		
        SendedData += 2;
    }
	
    UpdateStatusBarNow();                                                      /* 更新状态栏统计数据的显示 */

	return TRUE;
}

/**************************************************************************************************
**  函数名称:  CreateSettingFile
**  功能描述:  创建配置文件，并写入默认参数
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::CreateSettingFile(void)
{
    // 以下语句判断目录下是否存在INI文件，若不存在则创建该文件并写入默认值

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
**  函数名称:  InitiateAllParas
**  功能描述:  读取配置文件的各个参数内容并初始化对话框的值
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::InitiateAllParas(void)
{
    int  TempData;                                                             /* 需要注意的是：自动发送使能和循环发送使能两项无须初始化 */
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

	if (m_Check_HexDspl) {                                                     /* 根据读入的参数值初始化提示框内容 */
        SetDlgItemText(IDC_STATIC_LINES, "字符");
    } else {
        SetDlgItemText(IDC_STATIC_LINES, "行");
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
    
    UpdateData(FALSE);                                                         /* 更新编辑框内容 */
	p_DlgSrSend->UpdateData(FALSE);
}

/**************************************************************************************************
**  函数名称:  RecordAllParas
**  功能描述:  将对话框中各个参数的值记录到配置文件中
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::RecordAllParas(void)
{
    int TempData;                                                              /* 需要注意的是：自动发送使能和循环发送使能两项无须保存 */
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
**  函数名称:  InitiateStatusBar
**  功能描述:  初始化状态栏
**  输入参数:  
**  返回参数:  
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
    m_strTime = " 当前时间: " + time.Format("%Y-%m-%d") + " " + time.Format("%H:%M:%S");
    
    m_StatusBar.SetPaneInfo(0, nID, SBPS_STRETCH, 1);
    m_StatusBar.SetPaneText(0, " 欢迎使用MySScom - 雅迅网络");
    
    m_StatusBar.SetPaneInfo(1, nID, SBPS_NORMAL, 90);
    m_StatusBar.SetPaneText(1, " 串口未打开");

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
**  函数名称:  InitiateComboComs
**  功能描述:  初始化串口号组合框
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::InitiateComboComs(void)
{
    EnumComm();                                                                /* 枚举可用的串口 */

    for (int i = 0; i < sPorts.GetSize(); i++) {
        m_Combo_ComNo.AddString(sPorts.GetAt(i));
    }
}

/**************************************************************************************************
**  函数名称:  InitiateComboBaud
**  功能描述:  初始化波特率组合框
**  输入参数:  
**  返回参数:  
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
**  函数名称:  InitiateComboData
**  功能描述:  初始化数据位组合框
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::InitiateComboData(void)
{
    CString TempStr;
    
    for (int i = 0; i < (sizeof(Combo_Data) / sizeof(Combo_Data[0])); i++) {
        
        TempStr.Format("%d 位", Combo_Data[i]);
        
        m_Combo_Data.AddString(TempStr);
    }
}

/**************************************************************************************************
**  函数名称:  InitiateComboCheck
**  功能描述:  初始化校验位组合框
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::InitiateComboCheck(void)
{
    m_Combo_Check.AddString("None 校验");
    m_Combo_Check.AddString("Odd  校验");
    m_Combo_Check.AddString("Even 校验");
    m_Combo_Check.AddString("Mark 校验");
    m_Combo_Check.AddString("Space校验");
}

/**************************************************************************************************
**  函数名称:  InitiateComboStop
**  功能描述:  初始化停止位组合框
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::InitiateComboStop(void)
{
    m_Combo_Stop.AddString("1  位");
    m_Combo_Stop.AddString("1.5位");
    m_Combo_Stop.AddString("2  位");
}

/**************************************************************************************************
**  函数名称:  TaskBarAddIcon
**  功能描述:  在任务栏增加图标显示
**  输入参数:  
**  返回参数:  
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
**  函数名称:  TaskBarDeleteIcon
**  功能描述:  在任务栏删除图标显示
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
BOOL CMySScomDlg::TaskBarDeleteIcon(HWND hwnd, UINT uID)
{
    NOTIFYICONDATA d;
    
    d.cbSize = sizeof(NOTIFYICONDATA);
    d.hWnd   = hwnd;
    d.uID    = uID;
    
    return Shell_NotifyIcon(NIM_DELETE, &d);
}


/* ==================================== 自定义函数区--结束 ===================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ================================== 各个控件消息处理--开始 =================================== */


/**************************************************************************************************
**  函数名称:  OnButtonONOFF
**  功能描述:  串口开关
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonONOFF() 
{
    DCB  dcb;
    CString TempStr;
    COMMTIMEOUTS TimeOuts;
    
    if (m_PortOpened == TRUE) {                                                /* 如果串口已经打开，那么执行关闭操作 */

        if (m_Check_AutoSend) {
            MessageBox("请首先停用自动发送功能再尝试关闭串口...  ", "提示", MB_OK + MB_ICONEXCLAMATION);
            return;
        }
        
        SetCommMask(m_hSPCom, 0);                                              /* 设置过滤掩码 ????? */
        
        WaitForSingleObject(m_pThread->m_hThread, INFINITE);                   /* 关闭线程 ????? */
        
        m_pThread = NULL;
        
        CloseHandle(m_hSPCom);                                                 /* 关闭串口句柄 */

        SetDlgItemText(IDC_BUTTON_ONOFF, "打开串口");

        GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_DATA)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_CHECK)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_STOP)->EnableWindow(TRUE);

        SetControlStatus(FALSE);

        m_PortOpened = FALSE;

        return;
    }

    int ComNumber = m_Combo_ComNo.GetCurSel();                                 /* 得到串口号 */

    if (ComNumber == 0) {
        MessageBox("连串口号都没有选择，你叫我打开什么东东...？   ", "提示", MB_OK + MB_ICONINFORMATION);
        return;
    }
    
    m_Combo_ComNo.GetLBText(ComNumber, TempStr);
    CString ComComNo = TempStr;

    int ComBaudSel = m_Combo_Baud.GetCurSel();                                 /* 获取波特率的选择项 */
    TempStr.Format("%d", Combo_Baud[ComBaudSel]);
    ComBaudSel = atoi(TempStr);
    
    int ComDataSel = m_Combo_Data.GetCurSel();                                 /* 获取数据位的选择项 */
    TempStr.Format("%d", Combo_Data[ComDataSel]);
    ComDataSel = atoi(TempStr);
    
    int ComCheckSel = m_Combo_Check.GetCurSel();                               /* 获取校验位的选择项 */
    TempStr.Format("%c", Combo_Check[ComCheckSel]);
    ComCheckSel = atoi(TempStr);
    
    int ComStopSel = m_Combo_Stop.GetCurSel();                                 /* 获取停止位的选择项 */
    TempStr.Format("%d", Combo_Stop[ComStopSel]);
    ComStopSel = atoi(TempStr);

    m_hSPCom = CreateFile(ComComNo, GENERIC_READ | GENERIC_WRITE, 0,           /* 打开串口，获取句柄 */
                          NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    
    if (m_hSPCom == INVALID_HANDLE_VALUE) {                                    /* 串口打开失败 */
        MessageBox("打开串口失败，该串口可能正在使用中...   ", "提示", MB_OK + MB_ICONERROR);
        return;
    }
    
    SetupComm(m_hSPCom, MAXBLOCK, MAXBLOCK);                                   /* 设置缓存大小 */
    SetCommMask(m_hSPCom, EV_RXCHAR);                                          /* 设置过滤掩码??? - 所有字符全接收 */
    
    TimeOuts.ReadIntervalTimeout         = MAXDWORD;                           /* 读间隔超时 */
    TimeOuts.ReadTotalTimeoutConstant    = 0;                                  /* 读时间常量 */
    TimeOuts.ReadTotalTimeoutMultiplier  = 0;                                  /* 读时间系数 */
    TimeOuts.WriteTotalTimeoutConstant   = 2000;                               /* 写时间常量 */
    TimeOuts.WriteTotalTimeoutMultiplier = 50;                                 /* 写时间系数 */

    SetCommTimeouts(m_hSPCom, &TimeOuts);                                      /* 设置超时参数 */

    if (!GetCommState(m_hSPCom, &dcb)) {                                       /* 首先获取当前的工作参数 */
        MessageBox("串口工作参数获取失败，请确认该串口是否有效...   ", "提示", MB_OK + MB_ICONERROR);
        return;
    }
    
    dcb.fBinary      = TRUE;                                                   /* 二进制模式 */
    dcb.BaudRate     = ComBaudSel;                                             /* 设置波特率 */
    dcb.ByteSize     = ComDataSel;                                             /* 设置数据位 */
    dcb.StopBits     = ComStopSel;
    dcb.fParity      = TRUE;                                                   /* 开启校验功能 */
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
        
    if (SetCommState(m_hSPCom, &dcb)) {                                        /* 首先配置串口参数 */
        
        m_pThread = AfxBeginThread(SPCommProc, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);     /* 新开一个线程用于监听串口数据 */
        
        if (m_pThread == NULL) {                                               /* 如果线程创建失败 */

            CloseHandle(m_hSPCom);                                             /* 关闭串口句柄 */

            MessageBox("出现异常！串口监听线程创建失败...   ", "提示", MB_OK + MB_ICONERROR);
            return;

        } else {                                                               /* 开始正常工作 */

            m_pThread->ResumeThread();

            m_PortOpened = TRUE;
            
            SetControlStatus(TRUE);                                            /* 启用各个按钮控件 */
            
            SetDlgItemText(IDC_BUTTON_ONOFF, "关闭串口");
            
            GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(FALSE);
            GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(FALSE);
            GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);
            GetDlgItem(IDC_COMBO_CHECK)->EnableWindow(FALSE);
            GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);
        }

    } else {                                                                   /* 串口配置失败，关闭串口句柄 */

        CloseHandle(m_hSPCom);
        MessageBox("串口参数配置失败，请确认各个参数是否合法...   ", "提示", MB_OK + MB_ICONERROR);
        return;
    }
}

/**************************************************************************************************
**  函数名称:  OnButtonPause
**  功能描述:  暂停接收/恢复接收
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonPause() 
{
    if (m_bRecvPause == FALSE) {
        m_bRecvPause = TRUE;
        SetDlgItemText(IDC_BUTTON_PAUSE, "恢复接收");
        GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(FALSE);
    } else {
        m_bRecvPause = FALSE;
        SetDlgItemText(IDC_BUTTON_PAUSE, "暂停接收");
        GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(TRUE);
    }
}

/**************************************************************************************************
**  函数名称:  OnButtonClear
**  功能描述:  清除窗口内已经接收的数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonClear()
{
    StrRecved = "";
    
    m_Edit_Recv = "";
    SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);

    if (m_Check_ShowTime == TRUE) {
        m_NeedTime = TRUE;                                                     /* 下一次收到数据时显示时间 */
    }

    RecvedLine = 0;
    RecvedData = 0;
    UpdateStatusBarNow();                                                      /* 更新状态栏的统计数据显示 */
}

/**************************************************************************************************
**  函数名称:  OnButtonSave
**  功能描述:  将接收到的数据保存到文件中
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSave()
{
    CFile   MyFile;                                                            /* 定义文件类 */
    int     nLength;
    CString Temp_String;
    
    CTime   NowTime  = CTime::GetCurrentTime();                                /* 获取现在时间 */
    CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";           /* 指定文件名 */
    
    GetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
    
    nLength = m_Edit_Recv.GetLength();                                         /* 获取长度 */
    
    if (nLength <= 0) {
        MessageBox("尚未接收到任何内容，无须保存！   ", "提示", MB_OK + MB_ICONINFORMATION);
        return;
    }
    
    if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite) == 0) {
        Temp_String = "文件 " + FileName + " 创建失败！  ";
        MessageBox(Temp_String, "抱歉", MB_OK + MB_ICONWARNING);
        return;
    } else {
        Temp_String = "文件 " + FileName + " 创建成功！  ";
        MessageBox(Temp_String, "恭喜", MB_OK + MB_ICONINFORMATION);
    }
    
    MyFile.Write(m_Edit_Recv, nLength);                                        /* 写入文本文件 */
    MyFile.Close();                                                            /* 关闭文件 */
}

/**************************************************************************************************
**  函数名称:  OnButtonSend
**  功能描述:  发送窗口内输入的数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSend()
{
    GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
    
    if (m_Edit_Send.GetLength() <= 0) {
        MessageBox("发送窗口内容为空，未发送任何数据！ ", "提示", MB_OK + MB_ICONINFORMATION);
        return;
    }
	
	if (SendDatatoComm(m_Edit_Send, m_Check_HexSend) == FALSE) {
		MessageBox("您输入的CAN数据帧内容过长，或者存在非法字符，请确认！......       ", "提醒", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonCount
**  功能描述:  清除计数器
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonCount() 
{
    RecvedLine = 0;
    RecvedData = 0;
    SendedData = 0;

    UpdateStatusBarNow();                                                      /* 更新状态栏的统计数据显示 */
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend
**  功能描述:  显示高级发送窗口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend() 
{
	if (p_DlgSrSend->IsWindowVisible()) {                                      /* 高级发送窗口已经打开，尝试关闭 */

		if (p_DlgSrSend->DataisSending()) {
			MessageBox("请先停止自动循环发送功能，再尝试关闭高级发送窗口......   ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			p_DlgSrSend->ShowWindow(SW_HIDE);
			SetDlgItemText(IDC_BUTTON_SRSEND, "高级发送");
			
			GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
		}
		
	} else {                                                                   /* 高级发送窗口尚未打开，尝试打开 */

		if (m_Check_AutoSend) {
			MessageBox("请先停止单条数据的自动发送功能，再尝试打开高级发送窗口......   ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			p_DlgSrSend->ShowWindow(SW_SHOW);
			SetDlgItemText(IDC_BUTTON_SRSEND, "正常发送");

			GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonHelp
**  功能描述:  显示帮助窗口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonHelp() 
{
    CDialogAbout Dlgabout;
    
    Dlgabout.DoModal();
}

/**************************************************************************************************
**  函数名称:  OnCheckHexDisplay
**  功能描述:  是否显示为16进制字符
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckHexDisplay()
{
    if (m_Check_ShowTime == TRUE) {
        MessageBox("请先取消显示时间功能，然后再尝试切换到16进制的显示模式......   ", "提示", MB_OK + MB_ICONINFORMATION);
        m_Check_HexDspl = FALSE;        
        UpdateData(FALSE);
    } else {
        m_Check_HexDspl = !m_Check_HexDspl;

        if (m_Check_HexDspl) {
            SetDlgItemText(IDC_STATIC_LINES, "字符");
        } else {
            SetDlgItemText(IDC_STATIC_LINES, "行");
        }

        UpdateEditDisplay();                                                   /* 更新显示 */
    }
}

/**************************************************************************************************
**  函数名称:  OnCheckAutoClear
**  功能描述:  是否开启自动清除功能
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoClear() 
{
    int     TempData;
    CString TempStr;
    
    m_Check_AutoClear = !m_Check_AutoClear;
    
    GetDlgItemText(IDC_EDIT_LINES, TempStr);

    TempData = atoi((LPSTR)(LPCTSTR)TempStr);
    
    if ((TempData < 1) || (TempData > 10000)) {        
        MessageBox("您设置的行数值超出系统允许范围，请设置在1-10000行之间  ", "提示", MB_OK + MB_ICONINFORMATION);
        SetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                          /* 还原编辑框内容 */
        m_Check_AutoClear = FALSE;        
        UpdateData(FALSE);
        return;
    }

    GetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                              /* 读取数据并保存 */
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
**  函数名称:  OnCheckAutoSave
**  功能描述:  是否开启自动保存功能
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoSave()
{
    m_Check_AutoSave = !m_Check_AutoSave;
}

/**************************************************************************************************
**  函数名称:  OnCheckHexSend
**  功能描述:  是否发送16进制数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckHexSend()
{   
    m_Check_HexSend = !m_Check_HexSend;
}

/**************************************************************************************************
**  函数名称:  OnCheckAutoSend
**  功能描述:  是否开启自动发送功能
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoSend()
{   
    m_Check_AutoSend = !m_Check_AutoSend;

    GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);

    if (m_Edit_Send.GetLength() <= 0) {
        MessageBox("貌似发送区为空吧，请问您老想让我发送什么东东？ ", "提示", MB_OK + MB_ICONINFORMATION);
        m_Check_AutoSend = FALSE;
        UpdateData(FALSE);
        return;
    }

    if (m_Check_AutoSend) {

        if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {                        /* 确保输入的数据不会过长 */

            MessageBox("您输入的数据过长，提交发送请求失败......   ", "提示", MB_OK + MB_ICONINFORMATION);
            m_Check_AutoSend = FALSE;
            UpdateData(FALSE);
            return;
        }

        NeedAutoSendData();                                                    /* 开始尝试自动发送数据 */

    } else {

        KillTimer(Timer_No_AutoSend);                                          /* 否则，用户取消了自动发送的功能 */
        GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);

        SetSendButtonStatus(TRUE);                                             /* 重新启用发送区各个按钮 */
    }
}

/**************************************************************************************************
**  函数名称:  OnCheckReturn
**  功能描述:  发送时是否补加回车符
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckReturn()
{
    m_Check_Return = !m_Check_Return;
}

/**************************************************************************************************
**  函数名称:  OnCheckShowTime
**  功能描述:  行头位置是否显示时间
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckShowTime()
{
    if (m_Check_HexDspl == TRUE) {
        MessageBox("16进制显示模式下不支持显示接收时间功能......    ", "提示", MB_OK + MB_ICONINFORMATION);
        m_Check_ShowTime = FALSE;        
        UpdateData(FALSE);  
    } else {
        m_Check_ShowTime = !m_Check_ShowTime;
    }
}

/**************************************************************************************************
**  函数名称:  OnMenuTrayAbout
**  功能描述:  托盘菜单 - 关于程序
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayAbout()
{
    CDialogAbout Dlgabout;
    
    Dlgabout.DoModal();
}

/**************************************************************************************************
**  函数名称:  OnMenuTrayShow
**  功能描述:  托盘菜单 - 显示界面
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayShow()
{
    ShowWindow(SW_SHOW);
}

/**************************************************************************************************
**  函数名称:  OnMenuTrayHide
**  功能描述:  托盘菜单 - 隐藏界面
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayHide()
{
    ShowWindow(SW_HIDE);
}

/**************************************************************************************************
**  函数名称:  OnMenuTrayExit
**  功能描述:  托盘菜单 - 退出程序
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayExit()
{
    RecordAllParas();                                                          /* 保存各个参数数据 */
    
    TaskBarDeleteIcon(GetSafeHwnd(), 120);                                     /* 删除任务栏的图标 */
    
    ::PostQuitMessage(0);                                                      /* 程序退出的唯一方式 */
}


/* ================================== 各个控件消息处理--结束 =================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */


/**************************************************************************************************
**  函数名称:  OnPaint
**  功能描述:  处理窗体重绘消息
**  输入参数:  
**  返回参数:  
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
**  函数名称:  OnQueryDragIcon
**  功能描述:  获取窗体图标
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
HCURSOR CMySScomDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

/**************************************************************************************************
**  函数名称:  OnInitDialog
**  功能描述:  窗口初始化
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
BOOL CMySScomDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	p_DlgSrSend = new CDialogSrSend();                                         /* 以下语句创建高级发送窗体，并隐藏待用 */
	
	if (p_DlgSrSend != NULL){
		
		int Result = p_DlgSrSend->Create(IDD_DIALOG_SRSEND, this);
		
		if (!Result) {
			MessageBox("系统资源不足，创建对话框失败......   ", "抱歉", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		p_DlgSrSend->ShowWindow(SW_HIDE);
	}

    s_top_offset  = 0;                                                         /* 该语句不能移动位置 */
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

    InitiateStatusBar();                                                       /* 初始化状态栏各个区域位置 */
    InitiateComboComs();                                                       /* 初始化选择串口号的列表框 */
    InitiateComboBaud();                                                       /* 初始化选择波特率的列表框 */
    InitiateComboData();                                                       /* 初始化选择数据位的列表框 */
    InitiateComboCheck();                                                      /* 初始化选择校验位的列表框 */
    InitiateComboStop();                                                       /* 初始化选择停止位的列表框 */

    SetControlStatus(FALSE);                                                   /* 首先禁用各个按钮控件 */

    CreateDirectory(RecordPath, NULL);                                         /* 创建Record文件夹，用于保存数据 */

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

    INIT_EASYSIZE;                                                             /* 初始化各个控件的位置 */

    CreateSettingFile();                                                       /* 创建程序配置参数文件并初始化各个参数 */
    InitiateAllParas();

    TaskBarAddIcon(GetSafeHwnd(), 120, AfxGetApp()->LoadIcon(IDR_MAINFRAME), "MySScom");

    return TRUE;
}

/**************************************************************************************************
**  函数名称:  OnTimer
**  功能描述:  定时器消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnTimer(UINT nIDEvent) 
{
    switch (nIDEvent)
    {
        case Timer_No_RecvData:                                                /* 接收到串口数据 */
            if (m_DataRecvd == TRUE) {
                SetTimer(Timer_No_RecvData, 10, NULL);
                UpdateEditDisplay();                                           /* 更新编辑框内容显示 */
                UpdateStatusBarNow();                                          /* 更新状态栏统计数据的显示 */
                m_DataRecvd = FALSE;
            }
            break;
        
        case Timer_No_StatusBar:                                               /* 状态栏定时更新 */
            UpdateStatusBarNow();
            break;
            
        case Timer_No_AutoSend:                                                /* 自动发送数据 */
            GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
			if (SendDatatoComm(m_Edit_Send, m_Check_HexSend) == FALSE) {       /* 数据非法，则停止定时器 */
				OnCheckAutoSend();
				UpdateData(FALSE);
				MessageBox("您输入的CAN数据帧内容过长，或者存在非法字符，请确认！......       ", "提醒", MB_OK + MB_ICONEXCLAMATION);
			}
            break;
            
        default:
            return;
    }
        
    CDialog::OnTimer(nIDEvent);
}

/**************************************************************************************************
**  函数名称:  PreTranslateMessage
**  功能描述:  系统消息预处理函数
**  输入参数:  
**  返回参数:  
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
**  函数名称:  OnClose
**  功能描述:  处理窗口关闭消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnClose() 
{
    ShowWindow(SW_HIDE);                                                       /* 隐藏主窗口但是不退出 */
}

/**************************************************************************************************
**  函数名称:  OnSize
**  功能描述:  处理窗口大小缩放消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);

    UPDATE_EASYSIZE;

    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);      /* 同步状态栏的位置 */
}

/**************************************************************************************************
**  函数名称:  OnSizing
**  功能描述:  处理窗口大小缩放消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
    CDialog::OnSizing(fwSide, pRect);

    EASYSIZE_MINSIZE(800, 482, fwSide, pRect);                                 /* 限制窗体的最小尺寸 */
}

/**************************************************************************************************
**  函数名称:  OnMyIconNotify
**  功能描述:  处理托盘图标消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMyIconNotify(WPARAM wParam, LPARAM lParam)
{
    UINT uMouseMsg = LOWORD(lParam);
    CMenu oMenu;
    CPoint oPoint;
    
    switch (uMouseMsg)
    {
        case WM_LBUTTONDBLCLK:                                                 /* 如果是左键双击 */
            ShowWindow(IsWindowVisible()? SW_HIDE:SW_SHOWNORMAL);
            break;
        
        case WM_RBUTTONDOWN:                                                   /* 如果是右键 */
            if (oMenu.LoadMenu(IDR_MENU_TRAY)) {
                CMenu* pPopup = oMenu.GetSubMenu(0);
                ASSERT(pPopup != NULL);
                
                GetCursorPos(&oPoint);                                         /* 确定鼠标位置以便在该位置附近显示菜单 */
                SetForegroundWindow();
                pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, oPoint.x, oPoint.y, this); 
            }
            break;
    }
}


