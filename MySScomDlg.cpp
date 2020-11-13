#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const CString RecordPath = "Record\\";                                  /* 定义存放数据文件的文件夹的路径 */

static const int    Combo_Baud[12] = {600,  1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
static const int    Combo_Data[4]  = {5,    6,    7,    8};
static const double Combo_Stop[4]  = {1,    1.5,  2};
static const int    Combo_Check[5] = {0,    1,    2,    3,   4};


CMySScomDlg::CMySScomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySScomDlg::IDD, pParent)
{
	m_Check_AutoSave = FALSE;
	m_Check_AutoSend = FALSE;
	m_Check_HexDspl = FALSE;
	m_Check_HexSend = FALSE;
	m_Check_AutoClear = FALSE;
	m_Check_Filter = FALSE;
	m_Edit_Recv = _T("");
	m_Edit_Send = _T("");
	m_Edit_AutoTimer = _T("");
    m_Edit_Lines = _T("1000");
	m_Check_Return = FALSE;
	m_Check_ShowTime = FALSE;
	m_Check_FrameDspl = FALSE;
	s_NeedChgLne = TRUE;
	s_DataRecved = FALSE;
	m_Edit_FilePath = _T("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	AfxInitRichEdit();                                                         /* 初始化RichEdit控件 */
}

void CMySScomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_SENDFILE, m_Progress_SendFile);
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
	DDV_MaxChars(pDX, m_Edit_AutoTimer, 5);
	DDX_Text(pDX, IDC_EDIT_LINES, m_Edit_Lines);
	DDV_MaxChars(pDX, m_Edit_Lines, 5);
	DDX_Check(pDX, IDC_CHECK_RETURN, m_Check_Return);
	DDX_Check(pDX, IDC_CHECK_SHOWTIME, m_Check_ShowTime);
	DDX_Check(pDX, IDC_CHECK_FRAMEDSPL, m_Check_FrameDspl);
	DDX_Check(pDX, IDC_CHECK_AUTOREPLY, m_Check_AutoReply);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_Edit_FilePath);
	DDX_Check(pDX, IDC_CHECK_FILTER, m_Check_Filter);
	DDX_Control(pDX, IDC_EDIT_RECV, m_RichEdit_Recv);
}

BEGIN_MESSAGE_MAP(CMySScomDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_CLOSE()

	ON_COMMAND(IDC_MENU_TRAY_ABOUT, OnMenuTrayAbout)
	ON_COMMAND(IDC_MENU_TRAY_EXIT, OnMenuTrayExit)
	ON_COMMAND(IDC_MENU_TRAY_HIDE, OnMenuTrayHide)
	ON_COMMAND(IDC_MENU_TRAY_SHOW, OnMenuTrayShow)

	ON_COMMAND(IDC_MENU_EDIT_COPY, OnMenuEditCopy)
	ON_COMMAND(IDC_MENU_EDIT_CLEAR, OnMenuEditClear)
	ON_COMMAND(IDC_MENU_EDIT_FONT, OnMenuEditFont)
	ON_COMMAND(IDC_MENU_EDIT_ABOUT, OnMenuEditAbout)
	ON_COMMAND(IDC_MENU_EDIT_COLOR_WHITE, OnMenuEditColorWhite)
	ON_COMMAND(IDC_MENU_EDIT_COLOR_GRAY, OnMenuEditColorGray)
	ON_COMMAND(IDC_MENU_EDIT_COLOR_GREEN, OnMenuEditColorGreen)
	ON_COMMAND(IDC_MENU_EDIT_COLOR_BLUE, OnMenuEditColorBlue)
	ON_COMMAND(IDC_MENU_EDIT_COLOR_PINK, OnMenuEditColorPink)
	ON_COMMAND(IDC_MENU_EDIT_COLOR_PURPLE, OnMenuEditColorPurple)

	ON_BN_CLICKED(IDC_BUTTON_ONOFF, OnButtonPortCtrl)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonRecvPause)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClearAll)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSaveFile)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSendData)
	ON_BN_CLICKED(IDC_BUTTON_SRSEND, OnButtonSuperSend)
	ON_BN_CLICKED(IDC_BUTTON_EXFUNCT, OnButtonExtrafunc)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, OnButtonOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_SENDFILE, OnButtonSendFile)
	ON_BN_CLICKED(IDC_BUTTON_SETFILTER, OnButtonConfigDsplFilt)
	ON_BN_CLICKED(IDC_BUTTON_SETREPLY, OnButtonConfigAutoReply)

	ON_BN_CLICKED(IDC_CHECK_HEXDSPL, OnCheckHexDisplay)
	ON_BN_CLICKED(IDC_CHECK_AUTOSAVE, OnCheckAutoSave)
	ON_BN_CLICKED(IDC_CHECK_HEXSEND, OnCheckHexSend)
	ON_BN_CLICKED(IDC_CHECK_AUTOSEND, OnCheckAutoSend)
	ON_BN_CLICKED(IDC_CHECK_RETURN, OnCheckAddReturn)
	ON_BN_CLICKED(IDC_CHECK_SHOWTIME, OnCheckShowTime)
	ON_BN_CLICKED(IDC_CHECK_AUTOCLEAR, OnCheckAutoClear)
	ON_BN_CLICKED(IDC_CHECK_FRAMEDSPL, OnCheckFrameDspl)
	ON_BN_CLICKED(IDC_CHECK_FILTER, OnCheckDsplFilt)
	ON_BN_CLICKED(IDC_CHECK_AUTOREPLY, OnCheckAutoReply)
	
	ON_MESSAGE(WM_USERMSG_NOTIFYICON, OnUsrMsgHdlIconNotify)
	ON_MESSAGE(WM_USERMSG_COMDEVLIST, OnUsrMsgHdlComDevList)
	ON_MESSAGE(WM_USERMSG_DATARECVED, OnUsrMsgHdlDataRecved)
	ON_MESSAGE(WM_USERMSG_DATATOSEND, OnUsrMsgHdlDatatoSend)
	ON_MESSAGE(WM_USERMSG_ARDLGCLOSE, OnUsrMsgHdlARDlgClose)
	ON_MESSAGE(WM_USERMSG_DFDLGCLOSE, OnUsrMsgHdlDFDlgClose)
	ON_MESSAGE(WM_USERMSG_EFDLGCLOSE, OnUsrMsgHdlEFDlgClose)
	ON_MESSAGE(WM_USERMSG_SSDLGCLOSE, OnUsrMsgHdlSSDlgClose)
	ON_WM_SYSCOMMAND()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CMySScomDlg, CDialog)
	//{{AFX_EVENTSINK_MAP(CMySScomDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BEGIN_EASYSIZE_MAP(CMySScomDlg)
	EASYSIZE(IDC_STATIC_CONTROL,    ES_BORDER,           ES_BORDER,          ES_KEEPSIZE,        ES_BORDER,        0)
	EASYSIZE(IDC_STATIC_RECEIVE,    IDC_STATIC_CONTROL,  ES_BORDER,          ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_STATIC_SEND,       IDC_STATIC_CONTROL,  ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_STATIC_FILE,       IDC_STATIC_CONTROL,  ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_EDIT_RECV,         ES_BORDER,           ES_BORDER,          ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_EDIT_SEND,         ES_BORDER,           ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_PROGRESS_SENDFILE, ES_BORDER,           ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_BUTTON_SEND,       ES_KEEPSIZE,         ES_KEEPSIZE,        ES_BORDER,          IDC_STATIC_SEND,  0)
	EASYSIZE(IDC_EDIT_FILEPATH,     ES_BORDER,           ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_BUTTON_OPENFILE,   ES_KEEPSIZE,         ES_KEEPSIZE,        ES_BORDER,          IDC_STATIC_SEND,  0)
	EASYSIZE(IDC_BUTTON_SENDFILE,   ES_KEEPSIZE,         ES_KEEPSIZE,        ES_BORDER,          IDC_STATIC_SEND,  0)
END_EASYSIZE_MAP


/**************************************************************************************************
**  函数名称:  EnumCommPortList
**  功能描述:  本函数用来枚举电脑上存在可用的串口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
BOOL CMySScomDlg::EnumCommPortList()
{
	HKEY hSERIALCOMM;
	BOOL bSuccess = FALSE;
	
	s_PortNumber.RemoveAll();
	
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_QUERY_VALUE, &hSERIALCOMM) == ERROR_SUCCESS) {

		DWORD dwMaxValueNameLen;
		DWORD dwMaxValueLen;
		DWORD dwQueryInfo = RegQueryInfoKey(hSERIALCOMM, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &dwMaxValueNameLen, &dwMaxValueLen, NULL, NULL);
		
		if (dwQueryInfo == ERROR_SUCCESS) {

			DWORD dwMaxValueNameSizeInChars = dwMaxValueNameLen + 1;
			DWORD dwMaxValueNameSizeInBytes = dwMaxValueNameSizeInChars * sizeof(TCHAR);
			DWORD dwMaxValueDataSizeInChars = dwMaxValueLen / sizeof(TCHAR) + 1;
			DWORD dwMaxValueDataSizeInBytes = dwMaxValueDataSizeInChars * sizeof(TCHAR);
				
			TCHAR *szValueName;
			BYTE  *byValue;

			if ((szValueName = (TCHAR *)malloc(dwMaxValueNameSizeInChars)) && (byValue = (BYTE *)malloc(dwMaxValueDataSizeInBytes))) {
				
				bSuccess = TRUE;
				
				DWORD dwIndex = 0;
				DWORD dwType;
				DWORD dwValueNameSize = dwMaxValueNameSizeInChars;
				DWORD dwDataSize = dwMaxValueDataSizeInBytes;

				memset(szValueName, 0, dwMaxValueNameSizeInBytes);
				memset(byValue, 0, dwMaxValueDataSizeInBytes);

				LONG nEnum = RegEnumValue(hSERIALCOMM, dwIndex, szValueName, &dwValueNameSize, NULL, &dwType, byValue, &dwDataSize);
				
				while (nEnum == ERROR_SUCCESS) {

					if (dwType == REG_SZ) {
						TCHAR* szPort = (TCHAR *)(byValue);
						s_PortNumber.Add(szPort);	
					}
					
					dwValueNameSize = dwMaxValueNameSizeInChars;
					dwDataSize = dwMaxValueDataSizeInBytes;
					memset(szValueName, 0, dwMaxValueNameSizeInBytes);
					memset(byValue, 0, dwMaxValueDataSizeInBytes);
					++dwIndex;
					nEnum = RegEnumValue(hSERIALCOMM, dwIndex, szValueName, &dwValueNameSize, NULL, &dwType, byValue, &dwDataSize);
				}

				free(szValueName);
				free(byValue);
			} else {
				SetLastError(ERROR_OUTOFMEMORY);
			}
		}
		
		RegCloseKey(hSERIALCOMM);
		
		if (dwQueryInfo != ERROR_SUCCESS) {
			SetLastError(dwQueryInfo);
		}
	}
	
	return bSuccess;
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== 以下为控件状态设置 ===================================== */

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
	GetDlgItem(IDC_BUTTON_OPENFILE)->EnableWindow(Enable);
    GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_HEXDSPL)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_AUTOCLEAR)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_SHOWTIME)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_FILTER)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_OVER)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_LINES)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_LINES)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_RETURN)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(Enable);

    if ((IsDlgButtonChecked(IDC_CHECK_AUTOCLEAR) == FALSE) || (Enable == FALSE)) {
        GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FRAMEDSPL)->EnableWindow(FALSE);
    } else {
        GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_FRAMEDSPL)->EnableWindow(TRUE);
    }

	if (IsDlgButtonChecked(IDC_CHECK_HEXDSPL) == FALSE) {
		GetDlgItem(IDC_CHECK_FRAMEDSPL)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_AUTOREPLY)->EnableWindow(FALSE);
	} else {
		GetDlgItem(IDC_CHECK_FRAMEDSPL)->EnableWindow(Enable);
		GetDlgItem(IDC_CHECK_AUTOREPLY)->EnableWindow(Enable);
	}

	if (Enable == TRUE) {
		if (IsDlgButtonChecked(IDC_CHECK_AUTOREPLY) == TRUE) {
			GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(TRUE);
		} else {
			GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(FALSE);
		}

		if (IsDlgButtonChecked(IDC_CHECK_FILTER) == TRUE) {
			GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(TRUE);
		} else {
			GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  函数名称:  SetSendCtrlArea
**  功能描述:  在发送文件的时候设置各个发送区的状态
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::SetSendCtrlArea(bool Enable)
{
	GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_RETURN)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_FILEPATH)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_OPENFILE)->EnableWindow(Enable);
	SetDlgItemText(IDC_BUTTON_SENDFILE, (Enable == TRUE) ? "开始发送" : "停止发送");
	GetDlgItem(IDC_EDIT_SEND)->ShowWindow((Enable == TRUE) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BUTTON_SEND)->ShowWindow((Enable == TRUE) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_PROGRESS_SENDFILE)->ShowWindow((Enable == TRUE) ? SW_HIDE : SW_SHOW);

	if (Enable == TRUE) {
		SetDlgItemText(IDC_STATIC_SEND, "发送区");
	}
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== 以下为消息处理函数 ===================================== */

/**************************************************************************************************
**  函数名称:  OnUsrMsgHdlIconNotify
**  功能描述:  处理托盘图标消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlIconNotify(WPARAM wParam, LPARAM lParam)
{
	UINT    uMouseMsg = LOWORD(lParam);
	CMenu   oMenu;
	CPoint  oPoint;

	switch (uMouseMsg)
	{
		case WM_LBUTTONDBLCLK:                                                 /* 如果是左键双击 */
			ShowWindow(IsWindowVisible() ? SW_HIDE : SW_SHOWNORMAL);
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

	return 0;
}

/**************************************************************************************************
**  函数名称:  OnUsrMsgHdlComDevList
**  功能描述:  处理更新串口号下拉列表内容的消息 （串口设备监听线程监听到串口设备发生变化时，发送本消息给主窗体通知其刷新列表显示）
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlComDevList(WPARAM wParam, LPARAM lParam)
{
	UpdateComboComs();
	
	return true;
}

/**************************************************************************************************
**  函数名称:  OnUsrMsgHdlDataRecved
**  功能描述:  处理接收到了串口数据的消息 （串口数据监听线程收到串口数据时，发送本消息给主窗体进行数据解析处理）
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlDataRecved(WPARAM wParam, LPARAM lParam)
{
	unsigned char buff[MAX_SEND_BYTE];

	memcpy(buff, (unsigned char *)lParam, wParam);

	HandleUSARTData(buff, wParam);

	return true;
}

/**************************************************************************************************
**  函数名称:  OnUsrMsgHdlDatatoSend
**  功能描述:  处理有串口数据需要发送的消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlDatatoSend(WPARAM wParam, LPARAM lParam)
{
	unsigned char buff[MAX_SEND_BYTE];
	
	memcpy(buff, (unsigned char *)lParam, wParam);

	SendDatatoComm(buff, wParam, FALSE);

	return true;
}

/**************************************************************************************************
**  函数名称:  OnUsrMsgHdlARDlgClose
**  功能描述:  处理自动回复窗口关闭的消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlARDlgClose(WPARAM wParam, LPARAM lParam)
{
	//GetDlgItem(IDC_BUTTON_EXFUNCT)->EnableWindow(TRUE);

	return true;
}

/**************************************************************************************************
**  函数名称:  OnUsrMsgHdlDFDlgClose
**  功能描述:  处理显示过滤窗口关闭的消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlDFDlgClose(WPARAM wParam, LPARAM lParam)
{
	//GetDlgItem(IDC_BUTTON_EXFUNCT)->EnableWindow(TRUE);

	return true;
}

/**************************************************************************************************
**  函数名称:  OnUsrMsgHdlEFDlgClose
**  功能描述:  处理附加功能窗口关闭的消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlEFDlgClose(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_BUTTON_EXFUNCT)->EnableWindow(TRUE);

	return true;
}

/**************************************************************************************************
**  函数名称:  OnUsrMsgHdlSSDlgClose
**  功能描述:  处理高级发送窗口关闭的消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlSSDlgClose(WPARAM wParam, LPARAM lParam)
{
	SetDlgItemText(IDC_BUTTON_SRSEND, "高级发送");
	GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_OPENFILE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(TRUE);

	return true;
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== 以下为自定义处理函数 =================================== */

/**************************************************************************************************
**  函数名称:  CloseAllChildWin
**  功能描述:  关闭所有子窗口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::CloseAllChildWin(void)
{
	s_PDlgSuprSend->ShowHideDlgWindow(FALSE);                                  /* 关闭高级发送窗口 */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_SSDLGCLOSE, 0, 0); 

	s_PDlgExtrfunc->ShowHideDlgWindow(FALSE);                                  /* 关闭附加功能窗口 */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_EFDLGCLOSE, 0, 0);   

	s_PDlgDsplFilt->ShowHideDlgWindow(FALSE);                                  /* 关闭过滤设置窗口 */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_DFDLGCLOSE, 0, 0);

	s_PDlgAutoRply->ShowHideDlgWindow(FALSE);                                  /* 关闭自动回复窗口 */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_ARDLGCLOSE, 0, 0);
}

/**************************************************************************************************
**  函数名称:  SaveEditContent
**  功能描述:  保存编辑框的内容到文本文件
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CMySScomDlg::SaveEditContent(void)
{
    CFile   MyFile;                                                            /* 定义文件类 */
    CTime   NowTime  = CTime::GetCurrentTime();                                /* 获取现在时间 */
    CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";
    
    GetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
	
	if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite)) {
        MyFile.Write(m_Edit_Recv, m_Edit_Recv.GetLength());                    /* 写入文本文件 */
        MyFile.Close();                                                        /* 关闭文件 */
		return TRUE;
    } else {
		return FALSE;
	}
}

/**************************************************************************************************
**  函数名称:  UpdateEditStr
**  功能描述:  将更新部分的字符显示出来
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::UpdateEditStr(CString showstr)
{
	int     linecnt;
	CString TimeStr, TempStr;
	unsigned char sbuf[MAX_SEND_BYTE];

    /* 如果没有开启自动清空数据的功能，同时窗口内已经接收了太多的内容，为了防止CPU占用率过高，因此需要强制清空 */

    if ((m_Check_AutoClear == FALSE) && (s_RecvedByte >= MAX_DISP_BYTE)) {
        s_RecvedLine = 0;                                                      /* 首先清空变量值 */
        s_RecvedByte = 0;
        m_Edit_Recv = "";
        SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);                            /* 清空编辑框内容 */
		MessageBox("接收到的数据内容实在太多啦，我受不了啦\r\n所以就擅自清理掉了，还望您老不要生气哈......\r\n从系统稳定性出发，小的建议您老最好还是开启自动清空功能\r\n否则，老是给我塞啊塞却又从不清理一下的话，我很容易崩溃的哦~~~", "提示", MB_OK + MB_ICONINFORMATION);
    }

    /* 如果开启了显示过滤功能，则进行字符串匹配，不需要显示的字符串内容不予显示，只是更新一下状态栏的统计信息 */
	if ((m_Check_Filter == TRUE) && (s_PDlgDsplFilt->StringCanDisplay(showstr) == FALSE)) {
		UpdateStatusBarNow();
		return;
	}

	/* 如果在16进制显示模式下，同时开启了自动回复的功能。则判断接收到的字符中是否有满足条件的字段，并进行自动回复 */
	if ((m_Check_HexDspl == TRUE) && (m_Check_AutoReply == TRUE)) {
		for (int i = 0; i < s_PDlgAutoRply->GetTotalStringNo(); i++) {
			TempStr = s_PDlgAutoRply->GetRecvString(i);
			if ((TempStr.GetLength() > 0) && (showstr.Find(TempStr, 0) != -1)) {
				TempStr = s_PDlgAutoRply->GetSendString(i);
				if (TempStr.GetLength() > 0) {
					strncpy_s((char *)&sbuf[0], sizeof(sbuf), (LPCTSTR)TempStr, TempStr.GetLength());
					SendDatatoComm(sbuf, TempStr.GetLength(), TRUE);
				}
			}
		}
	}
    
    if (m_Check_HexDspl == TRUE) {                                             /* 16进制模式下 */
		linecnt = s_RecvedByte;                                                /* 以字符数来判断结果 */
	} else {                                                                   /* 字符模式下 */
        linecnt = s_RecvedLine;                                                /* 以行数来判断结果 */
    }

	#if 0                                                                      /* ◆◆这种方法会导致中文乱码◆◆ */
	{
		s_Edit_Recv->SetSel(-1, -1);                                           /* 添加本次的内容显示 */
		s_Edit_Recv->ReplaceSel((LPCTSTR)showstr);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);                    /* 让编辑框内容滚动到最后一行 */
	}
	#else                                                                      /* ◆◆这种方法会导致CPU占用率过高◆◆ */
	{
		m_Edit_Recv += showstr;                                                /* 添加本次的内容显示 */
		SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
        s_Edit_Recv->SetSel(-1, -1);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);                    /* 让编辑框内容滚动到最后一行 */
	}
	#endif

	if (showstr.Right(1) == "\n") {                                            /* 如果接收到了回车符 */

		if (m_Check_AutoClear == TRUE) {                                       /* 如果需要自动清空内容 */
			
			GetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                      /* 读取数据并保存 */
			
			if (linecnt >= atoi((LPSTR)(LPCTSTR)m_Edit_Lines)) {               /* 判断是否满足清空条件*/
				
				s_RecvedLine = 0;                                              /* 首先清空变量值 */
				s_RecvedByte = 0;
				
				if (m_Check_AutoSave) {
					SaveEditContent();                                         /* 保存编辑框的数据 */
				}
				
				m_Edit_Recv = "";
				SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);                    /* 清空编辑框内容 */
			}
		}
	}

    /*************************************************************************************************\
    |                          以下语句实现对接收编辑框的闪屏现象的屏蔽作用                           |
    \*************************************************************************************************/
    
    if (GetFocus() == GetDlgItem(IDC_EDIT_RECV)) {                             /* 将窗口焦点转移至发送编辑框 */
        GetDlgItem(IDC_EDIT_INPUT)->SetFocus();
    }

	UpdateStatusBarNow();                                                      /* 更新状态栏统计数据的显示 */
}

/**************************************************************************************************
**  函数名称:  UpdateEditDisplay
**  功能描述:  更新编辑框的显示
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::UpdateEditDisplay(void)
{
	CString TimeStr, TempStr;
    CTime   NowTime;

    if (m_Check_HexDspl == TRUE) {                                             /* 16进制模式下 */

        TempStr = TransformtoHex(s_RecvString);                                /* 转换结果为16进制显示 */

		if (s_NeedChgLne == TRUE) {                                            /* 如果需要换行显示 */
			if (m_Check_ShowTime == TRUE) {                                    /* 启用时间显示功能 */
				NowTime = CTime::GetCurrentTime();                             /* 获取现在时间 */
				TimeStr = NowTime.Format("[%H:%M:%S] ");
				TempStr = TimeStr + TempStr; 
			}
			s_NeedChgLne = FALSE;
		}
    } else {                                                                   /* 字符模式下 */
		TempStr = s_RecvString;                                                /* 不用转换，直接显示 */
    }

	s_RecvString = "";

	UpdateEditStr(TempStr);                                                    /* 更新显示接收到的字符 */
}

/**************************************************************************************************
**  函数名称:  HandleUSARTData
**  功能描述:  接收串口数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::HandleUSARTData(unsigned char *sbuf, DWORD len)
{
    DWORD   i;
    CString ShowStr, TempStr, TimeStr;
    CTime   NowTime;

	TempStr = "";
	ShowStr = "";

	if (s_RecvPaused == TRUE) return;                                          /* 暂停接收时，不进行处理 */

    for (i = 0; i < len; i++) {                                                /* 将数组转换为Cstring型变量 */

		if (m_Check_HexDspl == TRUE) {                                         /* 当前处于16进制显示模式 */

			/* 考虑到00字符的特殊性，需要对其进行转义才能存储。转义规则如下：00转义成FF 01，FF转义成FF 02，其他字符不转义 */

			if (sbuf[i] == 0) {                                                /* 00 转义成 FF 01 */
				TempStr.Format("%c%c", 0xFF, 0x01);
			} else if ((unsigned char)(sbuf[i]) == 0xFF) {                     /* FF 转义成 FF 02 */
				TempStr.Format("%c%c", 0xFF, 0x02);
			} else {
				TempStr.Format("%c", sbuf[i]);
			}

			ShowStr += TempStr;                                                /* 保存数据内容 */
			
			if (m_Check_FrameDspl == TRUE) {                                   /* 这里判断接下来一段时间内是否没有再收到其他数据 */
				KillTimer(Timer_No_FrameDspl);                                 /* 以实现16进制下，按帧换行显示的功能 */
				SetTimer(Timer_No_FrameDspl, CHNGLINE_INTERVAL, NULL);         /* 这里重新启动定时器判断是否没有再收到其他数据 */
			}
			
		} else {                                                               /* 当前处于字符显示模式 */

			if (s_NeedChgLne == TRUE) {                                        /* 如果接收完一整行 */

				if (m_Check_ShowTime == TRUE) {                                /* 如果启用了时间显示功能 */
					NowTime = CTime::GetCurrentTime();                         /* 获取当前系统时间 */
					TimeStr = NowTime.Format("[%H:%M:%S] ");
					ShowStr = ShowStr + TimeStr;
				}
				
				s_NeedChgLne = FALSE;
			}

			TempStr.Format("%c", sbuf[i]);                                     /* 处理接收到的数据 */
			ShowStr += TempStr;                                                /* 保存数据内容 */

			if (TempStr == "\n") {                                             /* 本次接收到回车符 */

				s_RecvedLine++;                                                /* 接收到的行数累加 */
			    s_NeedChgLne = TRUE;                                           /* 标记需要换行显示 */
			}
        }
    }

	s_RecvedByte += len;                                                       /* 接收字节数累加 */
    s_DataRecved  = TRUE;
	s_RecvString += ShowStr;                                                   /* 注意这里要用加号，不然会造成之前的数据丢失 */
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
    
    if (Timer > 0) {

        SetTimer(Timer_No_AutoSend, Timer, NULL);                              /* 启动定时器 */

        GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);

        m_Edit_AutoTimer = TempStr;                                            /* 更新编辑框内容 */
        SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);

        GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);                      /* 禁用发送按钮 */
		GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(FALSE);

    } else {

        MessageBox("发送时间间隔不能为0，请确认！  ", "提示", MB_OK + MB_ICONEXCLAMATION);

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

#if VERSION_CTRL == VERSION_YAXON
	if (DialogMain.Width() > 1300) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发部 - Designed By LEON (LEON1741@126.com) - 仅限内部交流，谢谢！";
	} else if (DialogMain.Width() > 1200) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发部 - Designed By LEON (LEON1741@126.com)";
	} else if (DialogMain.Width() > 1100) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发部 - Designed By LEON";
	} else if (DialogMain.Width() > 1000) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发部 - LEON";
	} else if (DialogMain.Width() > 900) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络研发部";
	} else if (DialogMain.Width() > 850) {
		DisplayStr = " 欢迎使用MySScom - 雅迅网络";
	} else if (DialogMain.Width() > 800) {
		DisplayStr = " 欢迎使用MySScom";
	} else if (DialogMain.Width() > 700) {
		DisplayStr = " 欢迎使用";
	} else {
		DisplayStr = "";
	}
#else
    if (DialogMain.Width() > 1200) {
        DisplayStr = " 欢迎使用MySScom - Designed By LEON (LEON1741@126.com) - Welcome to Email me!!";
    } else if (DialogMain.Width() > 1100) {
        DisplayStr = " 欢迎使用MySScom - Designed By LEON (LEON1741@126.com)";
    } else if (DialogMain.Width() > 1000) {
        DisplayStr = " 欢迎使用MySScom - Designed By LEON";
    } else if (DialogMain.Width() > 850) {
        DisplayStr = " 欢迎使用MySScom - LEON";
    } else if (DialogMain.Width() > 800) {
        DisplayStr = " 欢迎使用MySScom";
    } else if (DialogMain.Width() > 720) {
        DisplayStr = " 欢迎使用";
    } else {
        DisplayStr = "";
    }
#endif

	s_CStatusBar.SetPaneText(0, DisplayStr);
        
    DisplayStr = (SerialDevisOpened() == TRUE) ? " 串口已打开" : " 串口未打开";  
    s_CStatusBar.SetPaneText(1, DisplayStr);

    DisplayStr.Format(" Lines: %.5d", s_RecvedLine);
    s_CStatusBar.SetPaneText(2, DisplayStr);
        
    DisplayStr.Format(" Recv: %.6d", s_RecvedByte);
    s_CStatusBar.SetPaneText(3, DisplayStr);

    DisplayStr.Format(" Send: %.6d", s_SendedByte);
    s_CStatusBar.SetPaneText(4, DisplayStr);

    Nowtime = CTime::GetCurrentTime();
    DisplayStr = " 当前时间: " + Nowtime.Format("%Y-%m-%d") + " " + Nowtime.Format("%H:%M:%S");
    s_CStatusBar.SetPaneText(5, DisplayStr);
}

/**************************************************************************************************
**  函数名称:  SendDatatoComm
**  功能描述:  将指定的字符串发送出去
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CMySScomDlg::SendDatatoComm(unsigned char *sbuf, int slen, BOOL needhex)
{
	int j, len;
	CString  tempstr;
	unsigned char temp[MAX_SEND_BYTE];
	CByteArray hexdata;	
	
    if (needhex) {                                                             /* 如果需要以16进制发送 */

		if (slen > MAX_SEND_BYTE * 3) {                                        /* 数据长度过大 */
			return FALSE;
		}

		tempstr.Format("%s", sbuf);
		if (ParseCStrisLegal(tempstr) == FALSE) {                              /* 字符串内容非法 */
			return FALSE;
		}

        len = String2Hex(tempstr, hexdata);                                    /* 将字符串转换为实际对应的数据 */
		
        for (j = 0; j < len; j++) {                                            /* 将实际数据保存至数组 */
            temp[j] = hexdata.GetAt(j);
        }
        
        s_SendedByte += SendSerialData(temp, len);                             /* 写入串口发送，发送字节数累加 */
        
    } else {                                                                   /* 字符模式下，直接发送 */

		if (slen > MAX_SEND_BYTE) {                                            /* 数据长度过大 */
			return FALSE;
		}

        s_SendedByte += SendSerialData(sbuf, slen);                            /* 写入串口发送，发送字节数累加 */
    }
	
    if (m_Check_Return == TRUE) {                                              /* 补发回车换行符 */
		
        temp[0] = '\r';
        temp[1] = '\n';
        
        s_SendedByte += SendSerialData(temp, 2);
    }

    UpdateStatusBarNow();                                                      /* 更新状态栏统计数据的显示 */
	
	return TRUE;
}

/**************************************************************************************************
**  函数名称:  SendFileDatatoComm
**  功能描述:  将文件数据发送到串口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CMySScomDlg::SendFileDatatoComm(void)
{
	CFile          filename;
	int            baudrate, sendbyte;
	unsigned long  fileleng;
	unsigned char *filebuff;                                                   /* 用于存放文件数据 */
	double         tempbyte;
	CString        dsplystr;
	unsigned int   totltime, lefttime;

	if (filename.Open(m_Edit_FilePath, CFile::modeReadWrite | CFile::typeBinary) == 0) {
		MessageBox("读取文件失败，请确认路径正确且文件未处于打开状态！    ", "提示", MB_OK + MB_ICONINFORMATION);
		return FALSE;
	}

	fileleng = (unsigned long)filename.GetLength();                            /* 获取文件长度 */
	
	baudrate = m_Combo_Baud.GetCurSel();
	baudrate = Combo_Baud[baudrate];

	tempbyte = ((double)baudrate / FILESEND_BYTE) * 1.1;
	sendbyte = (int)tempbyte;

	if ((s_FileDatPos + sendbyte) > fileleng) {                                /* 这里需要对最后一包进行特殊判断 */
		sendbyte = fileleng - s_FileDatPos;
	}
	
    filebuff = new unsigned char[sendbyte];                                    /* 分配内存空间 */
	filename.Seek(s_FileDatPos, CFile::begin);                                 /* 定位到上次发送的位置 */
    filename.Read(filebuff, sendbyte);                                         /* 读取文件内容 */

	sendbyte = SendSerialData(filebuff, sendbyte);                             /* 发送数据，并统计长度 */
	s_FileDatPos += sendbyte;
	s_SendedByte += sendbyte;

	totltime = (fileleng * 10) / baudrate;                                     /* 计算发送整个文件的耗时 */
	lefttime = (fileleng - s_FileDatPos) * 10 / baudrate;                      /* 计算发送整个文件的耗时 */

	m_Progress_SendFile.SetPos(s_FileDatPos * PROGRESS_POS / fileleng);        /* 更新进度条显示 */

	dsplystr.Format("发送区：预计耗时%0.2d分%0.2d秒，当前进度%0.2d%%，剩余%0.2d分%0.2d秒", 
		            totltime / 60, totltime % 60, s_FileDatPos * 100 / fileleng, lefttime / 60, lefttime % 60);
	SetDlgItemText(IDC_STATIC_SEND, dsplystr);
	
	filename.Close();                                                          /* 关闭文件 */
	delete []filebuff;                                                         /* 释放空间 */

	if (s_FileDatPos >= fileleng) {                                            /* 全部数据发送完毕 */
		s_FileDatPos = 0;
		KillTimer(Timer_No_SendFile);
		SetSendCtrlArea(TRUE);                                                 /* 启用其他发送控件 */
	}

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
    CString temp;
	
	// 以下语句判断目录下是否存在INI文件，若不存在则创建该文件并写入默认值

    if (!(::GetPrivateProfileInt("SystemInfo", "Created", 0, ".\\Settings.ini"))) {

        ::WritePrivateProfileString("SystemInfo", "Created",    "1",    ".\\Settings.ini");
        ::WritePrivateProfileString("PortConfig", "CommPort",   "0",    ".\\Settings.ini");
        ::WritePrivateProfileString("PortConfig", "BaudRate",   "4",    ".\\Settings.ini");
        ::WritePrivateProfileString("PortConfig", "DataBits",   "3",    ".\\Settings.ini");
        ::WritePrivateProfileString("PortConfig", "CheckBits",  "0",    ".\\Settings.ini");
        ::WritePrivateProfileString("PortConfig", "StopBits",   "0",    ".\\Settings.ini");
        ::WritePrivateProfileString("RecvConfig", "ShowSData",  "1",    ".\\Settings.ini");
        ::WritePrivateProfileString("RecvConfig", "ShowDirec",  "1",    ".\\Settings.ini");
        ::WritePrivateProfileString("RecvConfig", "HexDispl",   "0",    ".\\Settings.ini");
        ::WritePrivateProfileString("RecvConfig", "AutoClar",   "0",    ".\\Settings.ini");
        ::WritePrivateProfileString("RecvConfig", "AutoSave",   "0",    ".\\Settings.ini");
        ::WritePrivateProfileString("RecvConfig", "FramDspl",   "1",    ".\\Settings.ini");
        ::WritePrivateProfileString("RecvConfig", "ShowTime",   "1",    ".\\Settings.ini");
        ::WritePrivateProfileString("SendConfig", "HexaSend",   "0",    ".\\Settings.ini");
        ::WritePrivateProfileString("SendConfig", "AutoTime",   "1000", ".\\Settings.ini");
        ::WritePrivateProfileString("SendConfig", "AddReturn",  "0",    ".\\Settings.ini");
        ::WritePrivateProfileString("SendConfig", "SendStrH",   "",     ".\\Settings.ini");
		::WritePrivateProfileString("SendConfig", "SendStrC",   "",     ".\\Settings.ini");
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
    char TempChar[MAX_SEND_BYTE];
    CString TempStr;

	s_DialogPos_X = (::GetPrivateProfileInt("DialogPos", "DialogPos_X",  0, ".\\Settings.ini"));
	s_DialogPos_Y = (::GetPrivateProfileInt("DialogPos", "DialogPos_Y",  0, ".\\Settings.ini"));

    TempData = (::GetPrivateProfileInt("PortConfig", "CommPort",  0, ".\\Settings.ini"));
    m_Combo_ComNo.SetCurSel(TempData);
    TempData = (::GetPrivateProfileInt("PortConfig", "BaudRate",  4, ".\\Settings.ini"));
    m_Combo_Baud.SetCurSel(TempData);
    TempData = (::GetPrivateProfileInt("PortConfig", "DataBits",  3, ".\\Settings.ini"));
    m_Combo_Data.SetCurSel(TempData);
    TempData = (::GetPrivateProfileInt("PortConfig", "CheckBits", 0, ".\\Settings.ini"));
    m_Combo_Check.SetCurSel(TempData);
    TempData = (::GetPrivateProfileInt("PortConfig", "StopBits",  0, ".\\Settings.ini"));
    m_Combo_Stop.SetCurSel(TempData);

    m_Check_HexDspl   = (::GetPrivateProfileInt("RecvConfig", "HexDispl", 0, ".\\Settings.ini")) ? TRUE : FALSE;
    m_Check_ShowTime  = (::GetPrivateProfileInt("RecvConfig", "ShowTime", 1, ".\\Settings.ini")) ? TRUE : FALSE;
    m_Check_FrameDspl = (::GetPrivateProfileInt("RecvConfig", "FramDspl", 1, ".\\Settings.ini")) ? TRUE : FALSE;

    ::GetPrivateProfileString("SendConfig", "AutoLines", "1000", TempChar, 5, ".\\Settings.ini");
    m_Edit_Lines.Format("%s", TempChar);
    SetDlgItemText(IDC_EDIT_LINES, TempChar);

    m_Check_HexSend = (::GetPrivateProfileInt("SendConfig", "HexaSend", 0, ".\\Settings.ini")) ? TRUE : FALSE;
    ::GetPrivateProfileString("SendConfig", "AutoTime", "1000", TempChar, 5, ".\\Settings.ini");
    m_Edit_AutoTimer.Format("%s", TempChar);

    m_Check_Return = (::GetPrivateProfileInt("SendConfig", "AddReturn", 0, ".\\Settings.ini")) ? TRUE : FALSE;

    ::GetPrivateProfileString("SendConfig", "SendStrC", "", TempChar, MAX_SEND_BYTE, ".\\Settings.ini");
    TempStr.Format("%s", TempChar);
	s_SendStr_Chr = FormatQuotesStrRead(TempStr);

	::GetPrivateProfileString("SendConfig", "SendStrH", "", TempChar, MAX_SEND_BYTE, ".\\Settings.ini");
	s_SendStr_Hex.Format("%s", TempChar);

	if (m_Check_HexDspl == TRUE) {                                             /* 根据读入的参数值初始化提示框内容 */
        SetDlgItemText(IDC_STATIC_LINES, "字符");
    } else {
        SetDlgItemText(IDC_STATIC_LINES, "行");
    }

	if (m_Check_HexSend == TRUE) {                                             /* 根据读入的参数值初始化提示框内容 */
		m_Edit_Send = s_SendStr_Hex;
	} else {
		m_Edit_Send = s_SendStr_Chr;
	}

	SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
    
	UpdateData(FALSE);                                                         /* 更新编辑框内容 */
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
    CString ParaStr, TempStr;
	CRect rect;

	GetWindowRect(&rect);
	s_DialogPos_X = rect.left;
	s_DialogPos_Y = rect.top;
    
	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString("DialogPos", "DialogPos_X", ParaStr, ".\\Settings.ini");

	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString("DialogPos", "DialogPos_Y", ParaStr, ".\\Settings.ini");
	
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

    ::WritePrivateProfileString("RecvConfig", "HexDispl",   m_Check_HexDspl   ? "1" : "0", ".\\Settings.ini");
    ::WritePrivateProfileString("RecvConfig", "ShowTime",   m_Check_ShowTime  ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("RecvConfig", "FramDspl",   m_Check_FrameDspl ? "1" : "0", ".\\Settings.ini");

    GetDlgItemText(IDC_EDIT_LINES, ParaStr);
    ::WritePrivateProfileString("SendConfig", "AutoLines", ParaStr, ".\\Settings.ini");

    ::WritePrivateProfileString("SendConfig", "HexaSend",  m_Check_HexSend ? "1" : "0", ".\\Settings.ini");
    GetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);
    ::WritePrivateProfileString("SendConfig", "AutoTime",  m_Edit_AutoTimer, ".\\Settings.ini");

    ::WritePrivateProfileString("SendConfig", "AddReturn", m_Check_Return  ? "1" : "0", ".\\Settings.ini");

    GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
	if (m_Check_HexSend == TRUE) {                                                /* 首先同步更新一下编辑框的内容 */
		s_SendStr_Hex = m_Edit_Send;
	} else {
		s_SendStr_Chr = m_Edit_Send;
	}

	::WritePrivateProfileString("SendConfig", "SendStrH",  s_SendStr_Hex, ".\\Settings.ini");

	ParaStr = FormatQuotesStrWrite(s_SendStr_Chr);
	::WritePrivateProfileString("SendConfig", "SendStrC",  ParaStr, ".\\Settings.ini");
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
    
    if (!s_CStatusBar.Create(this) || !s_CStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT))) {
        TRACE0("Failed to create status barn");
        return;
    }

    time = CTime::GetCurrentTime();
    m_strTime = " 当前时间: " + time.Format("%Y-%m-%d") + " " + time.Format("%H:%M:%S");

#if VERSION_CTRL == VERSION_YAXON
    s_CStatusBar.SetPaneInfo(0, nID, SBPS_STRETCH, 1);
    s_CStatusBar.SetPaneText(0, " 欢迎使用MySScom - 雅迅网络");
#else
    s_CStatusBar.SetPaneInfo(0, nID, SBPS_STRETCH, 1);
    s_CStatusBar.SetPaneText(0, " 欢迎使用MySScom - LEON");
#endif

    s_CStatusBar.SetPaneInfo(1, nID, SBPS_NORMAL, 90);
    s_CStatusBar.SetPaneText(1, " 串口未打开");

    s_CStatusBar.SetPaneInfo(2, nID, SBPS_NORMAL, 90);
    s_CStatusBar.SetPaneText(2, " Lines: 00000");
    
    s_CStatusBar.SetPaneInfo(3, nID, SBPS_NORMAL, 100);
    s_CStatusBar.SetPaneText(3, " Recv: 000000");
    
    s_CStatusBar.SetPaneInfo(4, nID, SBPS_NORMAL, 100);
    s_CStatusBar.SetPaneText(4, " Send: 000000");

    s_CStatusBar.SetPaneInfo(5, nID, SBPS_NORMAL, 200);
    s_CStatusBar.SetPaneText(5, m_strTime);
    
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
    EnumCommPortList();                                                        /* 枚举可用的串口 */

	m_Combo_ComNo.ResetContent();
	m_Combo_ComNo.AddString("请选择");                                         /* 第一行为提示行 */

    for (int i = 0; i < s_PortNumber.GetSize(); i++) {
        m_Combo_ComNo.AddString(s_PortNumber.GetAt(i));
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
**  函数名称:  InitiateChildWins
**  功能描述:  初始化各个子窗体页面
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CMySScomDlg::InitiateChildWins(void)
{
	s_PDlgSuprSend = new CDialogSuperSend();                                   /* 以下语句创建高级发送窗体，并隐藏待用 */

	if (s_PDlgSuprSend != NULL){

		int Result = s_PDlgSuprSend->Create(IDD_DIALOG_SRSEND, this);

		if (!Result) {
			MessageBox("系统资源不足，创建对话框失败......   ", "抱歉", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		s_PDlgSuprSend->ShowWindow(SW_HIDE);
		s_PDlgSuprSend->InitiateAllParas();
	}

	s_PDlgExtrfunc = new CDialogExtrafunct();                                  /* 以下语句创建附加功能窗体，并隐藏待用 */

	if (s_PDlgExtrfunc != NULL){

		int Result = s_PDlgExtrfunc->Create(IDD_DIALOG_EXFUNCT, this);

		if (!Result) {
			MessageBox("系统资源不足，创建对话框失败......   ", "抱歉", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		s_PDlgExtrfunc->ShowWindow(SW_HIDE);
		s_PDlgExtrfunc->InitiateAllParas();
	}

	s_PDlgDsplFilt = new CDialogDsplFilt();                                    /* 以下语句创建显示过滤设置窗体，并隐藏待用 */

	if (s_PDlgDsplFilt != NULL){

		int Result = s_PDlgDsplFilt->Create(IDD_DIALOG_FILTER, this);

		if (!Result) {
			MessageBox("系统资源不足，创建对话框失败......   ", "抱歉", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		s_PDlgDsplFilt->ShowWindow(SW_HIDE);
		s_PDlgDsplFilt->InitiateAllParas();
	}

	s_PDlgAutoRply = new CDialogAutoReply();                                   /* 以下语句创建自动回复窗体，并隐藏待用 */

	if (s_PDlgAutoRply != NULL){

		int Result = s_PDlgAutoRply->Create(IDD_DIALOG_AUTOREPLY, this);

		if (!Result) {
			MessageBox("系统资源不足，创建对话框失败......   ", "抱歉", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		s_PDlgAutoRply->ShowWindow(SW_HIDE);
		s_PDlgAutoRply->InitiateAllParas();
	}

	return TRUE;
}

/**************************************************************************************************
**  函数名称:  InitiateToolsTip
**  功能描述:  初始化主界面下各个控件的悬浮提示信息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::InitiateToolsTip(void)
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
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SEND),     IDS_STRING_015);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_HEXSEND),   IDS_STRING_016);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOSEND),  IDS_STRING_017);
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_TIMER),      IDS_STRING_018);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_RETURN),    IDS_STRING_020);
	m_tooltip.AddTool(GetDlgItem(IDC_COMBO_CHECK),     IDS_STRING_021);
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_LINES),      IDS_STRING_024);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_EXFUNCT),  IDS_STRING_025);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SRSEND),   IDS_STRING_026);
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_SEND),       IDS_STRING_027);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_OPENFILE), IDS_STRING_028);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SENDFILE), IDS_STRING_029);
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_FILEPATH),   IDS_STRING_030);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_SHOWTIME),  IDS_STRING_031);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_FRAMEDSPL), IDS_STRING_032);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_FILTER),    IDS_STRING_033);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOREPLY), IDS_STRING_034);
}

/**************************************************************************************************
**  函数名称:  UpdateComboComs
**  功能描述:  更新串口号组合框
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::UpdateComboComs(void)
{
    int      pindex;
	CString  comstr;
	
	pindex = m_Combo_ComNo.GetCurSel();                                        /* 首先获取当前选择的串口号 */

	if (pindex == 0) {                                                         /* 0表示没有选中有效的串口号 */
		comstr = "";
	} else {                                                                   /* 根据串口号获取其COM字符串 */
		comstr = s_PortNumber.GetAt(pindex - 1);
	}

	InitiateComboComs();

	if (comstr == "") {                                                        /* 表示之前没有选择有效串口号 */
		m_Combo_ComNo.SetCurSel(0);                                            /* 直接选中提示栏 */
		return;
	}

	for (pindex = 0; pindex < s_PortNumber.GetSize(); pindex++) {              /* 之前曾经选中过某个串口号 */
		if (s_PortNumber.GetAt(pindex) == comstr) {                            /* 逐个比对，定位出该串口的序号 */
			m_Combo_ComNo.SetCurSel(pindex + 1);                               /* 自动选中该串口号 */
			return;
		}
	}

	m_Combo_ComNo.SetCurSel(0);                                                /* 比对失败，说明之前选中的串口已消失，则恢复到提示栏 */
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
    d.uCallbackMessage = WM_USERMSG_NOTIFYICON;
    
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

/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ================================== 各个控件消息处理--开始 =================================== */

/**************************************************************************************************
**  函数名称:  OnButtonPortCtrl
**  功能描述:  串口开关
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonPortCtrl() 
{
    CString TempStr;
    SRL_DEV_PARA_T spara;
    
    if (SerialDevisOpened() == TRUE) {                                         /* 如果串口已经打开，那么执行关闭操作 */

        if ((m_Check_AutoSend == TRUE) || (s_PDlgSuprSend->s_issenddata == TRUE)) {
            MessageBox("请首先停用自动发送功能再尝试关闭串口...  ", "提示", MB_OK + MB_ICONINFORMATION);
            return;
        }

		if (s_FileDatPos != 0) {
            MessageBox("正在发送文件，请先停止文件的发送，再尝试关闭串口...  ", "提示", MB_OK + MB_ICONINFORMATION);
            return;
        }
        
		CloseSerialDevice();                                                   /* 关闭串口设备 */
		CloseAllChildWin();                                                    /* 关闭各个子窗体 */

		SetControlStatus(FALSE);

        SetDlgItemText(IDC_BUTTON_ONOFF, "打开串口");
        GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_DATA)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_CHECK)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_STOP)->EnableWindow(TRUE);

        return;
    }

    int ComNumber = m_Combo_ComNo.GetCurSel();                                 /* 得到串口号 */

    if (ComNumber == 0) {
        MessageBox("连串口号都没有选择，你叫我打开什么东东...？   ", "提示", MB_OK + MB_ICONINFORMATION);
        return;
    }

	m_Combo_ComNo.GetLBText(ComNumber, TempStr);                               /* 获取串口号选择项 */
    CString ComDevFile = "\\\\.\\" + TempStr;

    TempStr.Format("%d", Combo_Baud[m_Combo_Baud.GetCurSel()]);                /* 获取波特率选择项 */
    spara.baudrate = atoi(TempStr);
    
    TempStr.Format("%d", Combo_Data[m_Combo_Data.GetCurSel()]);                /* 获取数据位选择项 */
    spara.databits = atoi(TempStr);
    
    TempStr.Format("%d", Combo_Check[m_Combo_Check.GetCurSel()]);              /* 获取校验位选择项 */
    spara.checkbit = atoi(TempStr);

    TempStr.Format("%d", Combo_Stop[m_Combo_Stop.GetCurSel()]);                /* 获取停止位选择项 */
    spara.stopbits = atoi(TempStr);

	if (OpenSerialDevice(ComDevFile, &spara) == FALSE) {                       /* 打开串口并初始化 */
		return;
	}

    SetControlStatus(TRUE);                                                    /* 启用各个按钮控件 */
    SetDlgItemText(IDC_BUTTON_ONOFF, "关闭串口");
    GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_CHECK)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);
}

/**************************************************************************************************
**  函数名称:  OnButtonRecvPause
**  功能描述:  暂停接收/恢复接收
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonRecvPause() 
{
    if (s_RecvPaused == FALSE) {
        s_RecvPaused = TRUE;
        SetDlgItemText(IDC_BUTTON_PAUSE, "恢复接收");
        GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(FALSE);
    } else {
        s_RecvPaused = FALSE;
        SetDlgItemText(IDC_BUTTON_PAUSE, "暂停接收");
        GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(TRUE);
    }
}

/**************************************************************************************************
**  函数名称:  OnButtonClearAll
**  功能描述:  清除窗口内已经接收的数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonClearAll()
{
    m_Edit_Recv = "";
    SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);

    s_RecvedLine = 0;
    s_RecvedByte = 0;
    s_SendedByte = 0;
    s_RecvString = "";
    s_NeedChgLne = TRUE;                                                       /* 下次需要换行显示 */

    UpdateStatusBarNow();                                                      /* 更新状态栏的统计数据显示 */
}

/**************************************************************************************************
**  函数名称:  OnButtonSaveFile
**  功能描述:  将接收到的数据保存到文件中
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSaveFile()
{
    CTime   NowTime  = CTime::GetCurrentTime();                                /* 获取现在时间 */
    CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";           /* 指定文件名 */
    
    GetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
    
    if (m_Edit_Recv.GetLength() <= 0) {
        MessageBox("尚未接收到任何内容，无须保存！   ", "提示", MB_OK + MB_ICONINFORMATION);
        return;
    }

	if (SaveEditContent() == TRUE) {
		MessageBox("窗口数据已经成功保存至指定文件!      ", "恭喜", MB_OK + MB_ICONINFORMATION);
	} else {
		MessageBox("文件创建失败!         ", "抱歉", MB_OK + MB_ICONWARNING);
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonSendData
**  功能描述:  发送窗口内输入的数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSendData()
{
    unsigned char buff[MAX_SEND_BYTE];
	
	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
    
    if (m_Edit_Send.GetLength() <= 0) {
        MessageBox("发送窗口内容为空，未发送任何数据！ ", "提示", MB_OK + MB_ICONINFORMATION);
        return;
    }
	
	strncpy_s((char *)&buff[0], sizeof(buff), (LPCTSTR)m_Edit_Send, m_Edit_Send.GetLength());

	if (SendDatatoComm(buff, m_Edit_Send.GetLength(), m_Check_HexSend) == FALSE) {
		MessageBox("您输入的数据帧内容过长，或者存在非法字符，请确认！......       ", "提醒", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonSuperSend
**  功能描述:  显示高级发送窗口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSuperSend() 
{
	if (s_PDlgSuprSend->IsWindowVisible()) {                                     /* 窗口已经打开，尝试关闭 */

		if ((s_PDlgSuprSend->s_issenddata) == TRUE) {
			MessageBox("请先停止自动循环发送功能，再尝试关闭高级发送窗口......   ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			s_PDlgSuprSend->ShowHideDlgWindow(FALSE);
			SetDlgItemText(IDC_BUTTON_SRSEND, "高级发送");
			
			GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_OPENFILE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(TRUE);
		}
		
	} else {                                                                   /* 窗口尚未打开，尝试打开 */

		if (m_Check_AutoSend) {
			MessageBox("请先停止单条数据的自动发送功能，再尝试打开高级发送窗口......   ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			s_PDlgSuprSend->ShowHideDlgWindow(TRUE);
			SetDlgItemText(IDC_BUTTON_SRSEND, "正常发送");

			GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_OPENFILE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonExtrafunc
**  功能描述:  显示附加功能窗口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonExtrafunc() 
{
	if (s_PDlgExtrfunc->IsWindowVisible() == FALSE) {                            /* 窗口尚未打开，尝试打开 */
		s_PDlgExtrfunc->ShowHideDlgWindow(TRUE);
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonOpenFile
**  功能描述:  打开文件
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonOpenFile() 
{
	CFile myFile;
	
	CFileDialog dlg(TRUE, "*.bin", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, 
						  "所有支持的文件(*.bin;*.hex;*.dat)|*.bin;*.hex;*.dat|\
						   bin文件(*.bin)|*.bin|\
						   hex文件(*.hex)|*.hex|\
						   dat文件(*.dat)|*.dat|\
						   所有文件(*.*)|*.*||");
	
	if (dlg.DoModal() != IDOK) {                                               /* 未选择任何文件 */
		return;
	}
	
	m_Edit_FilePath = dlg.GetPathName();						               /* 保存文件的路径 */
	
	SetDlgItemText(IDC_EDIT_FILEPATH, m_Edit_FilePath);
}

/**************************************************************************************************
**  函数名称:  OnButtonSendFile
**  功能描述:  发送文件
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSendFile() 
{
	CFile myFile;
	
	if (s_FileDatPos == 0) {                                                   /* 尚未开始发送，则开始发送 */

		GetDlgItemText(IDC_EDIT_FILEPATH, m_Edit_FilePath);
		
		if (m_Edit_FilePath == "") {
			MessageBox("您尚未指定需要发送的文件的路径！    ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		}
		
		if (myFile.Open(m_Edit_FilePath, CFile::modeReadWrite | CFile::typeBinary) == 0) {
			MessageBox("读取文件失败，请确认路径正确且文件未处于打开状态！    ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			if (myFile.GetLength() <= 0) {
				MessageBox("文件内容为空，发送终止！    ", "提示", MB_OK + MB_ICONINFORMATION);
				return;
			} else {
				s_FileDatPos = 0;
				SetTimer(Timer_No_SendFile, FILESEND_BYTE, NULL);              /* 开启定时器 */
				SetSendCtrlArea(FALSE);                                        /* 禁用其他发送控件 */
				m_Progress_SendFile.SetPos(0);
			}
		}
	} else {                                                                   /* 正在发送过程中，则停止发送 */
		s_FileDatPos = 0;
		KillTimer(Timer_No_SendFile);                                          /* 关闭定时器 */
		SetSendCtrlArea(TRUE);                                                 /* 恢复其他发送控件 */
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonConfigAutoReply
**  功能描述:  打开自动回复功能的设置窗口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonConfigAutoReply()
{
	if (s_PDlgAutoRply->IsWindowVisible() == FALSE) {                            /* 窗口尚未打开，尝试打开 */
		s_PDlgAutoRply->ShowHideDlgWindow(TRUE);
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonConfigDsplFilt
**  功能描述:  打开显示过滤法则的设置窗口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonConfigDsplFilt()
{
	if (s_PDlgDsplFilt->IsWindowVisible() == FALSE) {                            /* 窗口尚未打开，尝试打开 */
		s_PDlgDsplFilt->ShowHideDlgWindow(TRUE);
	}
}

/**************************************************************************************************
**  函数名称:  OnCheckHexDisplay
**  功能描述:  显示16进制字符复选框状态切换
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckHexDisplay()
{
    m_Check_HexDspl = !m_Check_HexDspl;

	GetDlgItem(IDC_CHECK_FRAMEDSPL)->EnableWindow(m_Check_HexDspl);
	GetDlgItem(IDC_CHECK_AUTOREPLY)->EnableWindow(m_Check_HexDspl);
	GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(m_Check_HexDspl);

    if (m_Check_HexDspl == TRUE) {
        SetDlgItemText(IDC_STATIC_LINES, "字符");
		if (IsDlgButtonChecked(IDC_CHECK_AUTOREPLY) == TRUE) {
			GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(TRUE);
		} else {
			GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(FALSE);
		}
    } else {
        SetDlgItemText(IDC_STATIC_LINES, "行");
		if (s_PDlgAutoRply->IsWindowVisible() == TRUE) {
			s_PDlgAutoRply->ShowHideDlgWindow(FALSE);
		}
    }
}

/**************************************************************************************************
**  函数名称:  OnCheckAutoClear
**  功能描述:  自动清除功能复选框状态切换
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
    
    if (TempData < 100) {        
        MessageBox("您设置的行数值过小，系统不建议使用。请设置一个大于100的值！     ", "提示", MB_OK + MB_ICONINFORMATION);
        SetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                          /* 还原编辑框内容 */
        m_Check_AutoClear = FALSE;        
        UpdateData(FALSE);
        return;
    }

    if (m_Check_AutoClear == TRUE) {
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
**  功能描述:  自动保存功能复选框状态切换
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoSave()
{
    m_Check_AutoSave = !m_Check_AutoSave;
}

/**************************************************************************************************
**  函数名称:  OnCheckHexSend
**  功能描述:  发送16进制数据复选框状态切换
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckHexSend()
{
    m_Check_HexSend = !m_Check_HexSend;
	
	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);                                /* 首先保存当前内容，然后更新显示 */

	if (m_Check_HexSend == FALSE) {                                            /* 之前是16进制模式，则现在是字符模式 */
		s_SendStr_Hex = m_Edit_Send;
		SetDlgItemText(IDC_EDIT_SEND, s_SendStr_Chr);
	} else {                                                                   /* 之前是字符模式，则现在是16进制模式 */
		s_SendStr_Chr = m_Edit_Send;
		SetDlgItemText(IDC_EDIT_SEND, s_SendStr_Hex);
	}
	
	UpdateData(TRUE);
}

/**************************************************************************************************
**  函数名称:  OnCheckAutoSend
**  功能描述:  自动发送功能复选框状态切换
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
		GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(FALSE);

    } else {

        KillTimer(Timer_No_AutoSend);                                          /* 否则，用户取消了自动发送的功能 */
        GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);                       /* 重新启用发送按钮 */
		GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(TRUE);
    }
}

/**************************************************************************************************
**  函数名称:  OnCheckAddReturn
**  功能描述:  发送时补加回车符复选框状态切换
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAddReturn()
{
    m_Check_Return = !m_Check_Return;
}

/**************************************************************************************************
**  函数名称:  OnCheckShowTime
**  功能描述:  行头位置显示时间复选框状态切换
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckShowTime()
{
    m_Check_ShowTime = !m_Check_ShowTime;
}

/**************************************************************************************************
**  函数名称:  OnCheckFrameDspl
**  功能描述:  帧格式显示自动换行功能复选框状态切换
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckFrameDspl() 
{
	m_Check_FrameDspl = !m_Check_FrameDspl;
}

/**************************************************************************************************
**  函数名称:  OnCheckAutoReply
**  功能描述:  自动回复复选框状态切换
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoReply()
{
	m_Check_AutoReply = !m_Check_AutoReply;

	GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(m_Check_AutoReply);

	if (m_Check_AutoReply == FALSE) {
		if (s_PDlgAutoRply->IsWindowVisible() == TRUE) {                         /* 窗口尚未关闭 */
			s_PDlgAutoRply->ShowHideDlgWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  函数名称:  OnCheckDsplFilt
**  功能描述:  显示内容过滤复选框状态切换
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckDsplFilt()
{
	m_Check_Filter = !m_Check_Filter;

	GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(m_Check_Filter);

	if (m_Check_Filter == FALSE) {
		if (s_PDlgDsplFilt->IsWindowVisible() == TRUE) {                       /* 窗口尚未关闭 */
			s_PDlgDsplFilt->ShowHideDlgWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  函数名称:  OnMenuEditCopy
**  功能描述:  编辑框菜单 - 复制所选内容
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditCopy()
{
	CString selstr;
	HGLOBAL clipbuffer;
	char    *buffer;

	selstr = m_RichEdit_Recv.GetSelText();

	if (OpenClipboard() == TRUE) {
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, selstr.GetLength() + 1);
		buffer = (char *)GlobalLock(clipbuffer);
		strcpy_s(buffer, selstr.GetLength() + 1, LPCSTR(selstr));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT, buffer);
		CloseClipboard();
	}
}

/**************************************************************************************************
**  函数名称:  OnMenuEditClear
**  功能描述:  编辑框菜单 - 清除全部内容
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditClear()
{
	if (MessageBox("确认要将所接收到的全部内容清空？", "提示", MB_OKCANCEL + MB_ICONQUESTION) != IDOK) {
		return;
	}
	
	OnButtonClearAll();
}

/**************************************************************************************************
**  函数名称:  OnMenuEditFont
**  功能描述:  编辑框菜单 - 显示字体设置
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditFont()
{
	CHARFORMAT cf;
	LOGFONT lf;

	memset(&cf, 0, sizeof(CHARFORMAT));
	memset(&lf, 0, sizeof(LOGFONT));

	m_RichEdit_Recv.GetDefaultCharFormat(cf);

	BOOL bIsBold = cf.dwEffects & CFE_BOLD;
	BOOL bIsItalic = cf.dwEffects & CFE_ITALIC;
	BOOL bIsUnderline = cf.dwEffects & CFE_UNDERLINE;
	BOOL bIsStrickout = cf.dwEffects & CFE_STRIKEOUT;

	//设置属性
	lf.lfCharSet = cf.bCharSet;
	lf.lfHeight = cf.yHeight/15;
	lf.lfPitchAndFamily = cf.bPitchAndFamily;
	lf.lfItalic = bIsItalic;
	lf.lfWeight = (bIsBold ? FW_BOLD : FW_NORMAL);
	lf.lfUnderline = bIsUnderline;
	lf.lfStrikeOut = bIsStrickout;
	sprintf_s(lf.lfFaceName, cf.szFaceName);

	CFontDialog dlg(&lf);

	dlg.m_cf.rgbColors = cf.crTextColor;

	if (dlg.DoModal() == IDOK) {
		dlg.GetCharFormat(cf);
		m_RichEdit_Recv.SetDefaultCharFormat(cf);
	}
}

/**************************************************************************************************
**  函数名称:  OnMenuEditAbout
**  功能描述:  编辑框菜单 - 程序介绍说明
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditAbout()
{
	CDialogAboutMe Dlgabout;

	Dlgabout.DoModal();
}

/**************************************************************************************************
**  函数名称:  OnMenuEditColorWhite
**  功能描述:  编辑框菜单 - 背景颜色设置 - 雪花白
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorWhite()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_WHITE);
}

/**************************************************************************************************
**  函数名称:  OnMenuEditColorGray
**  功能描述:  编辑框菜单 - 背景颜色设置 - 科技灰
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorGray()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_GRAY);
}

/**************************************************************************************************
**  函数名称:  OnMenuEditColorGreen
**  功能描述:  编辑框菜单 - 背景颜色设置 - 薄荷绿
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorGreen()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_GREEN);
}

/**************************************************************************************************
**  函数名称:  OnMenuEditColorBlue
**  功能描述:  编辑框菜单 - 背景颜色设置 - 碧空蓝
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorBlue()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_BLUE);
}

/**************************************************************************************************
**  函数名称:  OnMenuEditColorPink
**  功能描述:  编辑框菜单 - 背景颜色设置 - 浪漫粉
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorPink()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_PINK);
}

/**************************************************************************************************
**  函数名称:  OnMenuEditColorPurple
**  功能描述:  编辑框菜单 - 背景颜色设置 - 轻纱紫
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorPurple()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_PURPLE);
}

/**************************************************************************************************
**  函数名称:  OnMenuTrayAbout
**  功能描述:  托盘菜单 - 关于程序
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayAbout()
{
    CDialogAboutMe Dlgabout;
    
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
    CloseAllChildWin();                                                        /* 关闭各个子窗体 */
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
    CloseAllChildWin();                                                        /* 关闭各个子窗体 */
	
	RecordAllParas();                                                          /* 保存各个参数数据 */

	s_PDlgSuprSend->RecordAllParas();
	s_PDlgExtrfunc->RecordAllParas();
	s_PDlgDsplFilt->RecordAllParas();
	s_PDlgAutoRply->RecordAllParas();

	CloseSerialDevice();                                                       /* 关闭串口设备 */
    
    TaskBarDeleteIcon(GetSafeHwnd(), IDR_MAINFRAME);                           /* 删除任务栏的图标 */
    
    ::PostQuitMessage(0);                                                      /* 程序退出的唯一方式 */
}


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

	s_RecvPaused = FALSE;
	s_RecvString = "";
	s_LopSendCnt = 0;
	s_RecvedLine = 0;
	s_RecvedByte = 0;
	s_SendedByte = 0;
	s_FileDatPos = 0;

	CreateDirectory(RecordPath, NULL);                                         /* 创建Record文件夹，用于保存数据 */
	CreateSettingFile();                                                       /* 创建程序配置参数文件并初始化各个参数 */

	if (InitiateChildWins() == FALSE) {                                        /* 创建各个子窗体的页面 */
		return FALSE;
	}
	
	GetDlgItem(IDC_PROGRESS_SENDFILE)->ShowWindow(SW_HIDE);                    /* 隐藏进度条，并初始化配置 */
	m_Progress_SendFile.SetRange(0, PROGRESS_POS);
	m_Progress_SendFile.SetPos(0);

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    s_Edit_Recv = (CEdit*)GetDlgItem(IDC_EDIT_RECV);
    s_Edit_Send = (CEdit*)GetDlgItem(IDC_EDIT_SEND);

    InitiateStatusBar();                                                       /* 初始化状态栏各个区域位置 */
    InitiateComboComs();                                                       /* 初始化选择串口号的列表框 */
    InitiateComboBaud();                                                       /* 初始化选择波特率的列表框 */
    InitiateComboData();                                                       /* 初始化选择数据位的列表框 */
    InitiateComboCheck();                                                      /* 初始化选择校验位的列表框 */
    InitiateComboStop();                                                       /* 初始化选择停止位的列表框 */
	InitiateAllParas();                                                        /* 初始化主界面下各控件参数 */
	InitiateToolsTip();                                                        /* 初始化控件的悬浮提示信息 */

    SetControlStatus(FALSE);                                                   /* 首先禁用各个按钮控件 */

    SetTimer(Timer_No_UpdateDsp, UPDATEEDIT_TIME, NULL);
    SetTimer(Timer_No_StatusBar, STATUSBAR_TIME, NULL);

    INIT_EASYSIZE;                                                             /* 初始化各个控件的位置 */

	if (CreateDeviceThread() == FALSE) {                                       /* 如果线程创建失败 */
        MessageBox("串口设备监听线程创建失败！请重启程序！", "提示", MB_OK + MB_ICONERROR);
        return FALSE;
    }

	s_PDlgSuprSend->InitateSrDlgPos();                                         /* 这句话一定要放在最后面 */
	
    TaskBarAddIcon(GetSafeHwnd(), IDR_MAINFRAME, AfxGetApp()->LoadIcon(IDR_MAINFRAME), "MySScom");

	CRect rect;                                                                /* 初始化主窗体位置，并限制高度和宽度 */
	GetWindowRect(&rect);
	SetWindowPos(NULL, s_DialogPos_X, s_DialogPos_Y, MIN_WIN_WIDTH, MIN_WIN_HIGHT, SWP_NOSIZE);

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
    unsigned char buff[MAX_SEND_BYTE];
	
	switch (nIDEvent)
    {
        case Timer_No_UpdateDsp:                                              /* 更新编辑框内容显示 */
            if (s_DataRecved == TRUE) {
                UpdateEditDisplay();
                s_DataRecved = FALSE;
            }
            break;
        
        case Timer_No_StatusBar:                                               /* 状态栏定时更新 */
            UpdateStatusBarNow();
            break;
            
        case Timer_No_AutoSend:                                                /* 自动发送数据 */
            GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
			strncpy_s((char *)&buff[0], sizeof(buff), (LPCTSTR)m_Edit_Send, m_Edit_Send.GetLength());
			if (SendDatatoComm(buff, m_Edit_Send.GetLength(), m_Check_HexSend) == FALSE) {
				OnCheckAutoSend();
				UpdateData(FALSE);
				MessageBox("您输入的数据帧内容过长，或者存在非法字符，请确认！......       ", "提醒", MB_OK + MB_ICONEXCLAMATION);
			}
            break;
            
		case Timer_No_FrameDspl:                                               /* 16进制下按帧换行显示判定 */
			KillTimer(Timer_No_FrameDspl);
			s_RecvedLine++;
			UpdateEditStr("\r\n");                                             /* 立即换行显示 */
			s_NeedChgLne = TRUE;                                               /* 标志下次需要换行显示 */
			break;
			
		case Timer_No_SendFile:                                                /* 发送文件数据 */
			if (SendFileDatatoComm() == FALSE) {                               /* 本次发送数据失败 */
				s_FileDatPos = 0;
				KillTimer(Timer_No_SendFile);                                  /* 停止发送 */
				SetSendCtrlArea(TRUE);                                         /* 恢复其他发送控件 */
			}
			UpdateStatusBarNow();
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
    unsigned char keyvalue;
    
    m_tooltip.RelayEvent(pMsg);

    if (pMsg->message == WM_KEYDOWN) {

		if (SerialDevisOpened() == TRUE) {
			if ((GetFocus() == GetDlgItem(IDC_EDIT_INPUT)) || GetFocus() == GetDlgItem(IDC_EDIT_RECV)) {
				keyvalue = GetKeyValue(pMsg->wParam);
				if (keyvalue > 0) {
					s_SendedByte += SendSerialData(&keyvalue, 1);
				}
			}
		}

        if ((pMsg->wParam == VK_ESCAPE) || (pMsg->wParam == VK_RETURN)) {      /* 返回键和确认键需要进行预处理 */
            return true;
        }
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
    if ((m_Check_AutoSend == TRUE) || (s_PDlgSuprSend->s_issenddata == TRUE)) {
		MessageBox("请首先停用自动发送功能再尝试关闭本窗口...  ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
    }
	
	CloseAllChildWin();                                                        /* 关闭所有子窗口 */
	
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

	UpdateStatusBarNow();

    EASYSIZE_MINSIZE(MIN_WIN_WIDTH, MIN_WIN_HIGHT, fwSide, pRect);             /* 限制窗体的最小尺寸 */
}

/**************************************************************************************************
**  函数名称:  OnContextMenu
**  功能描述:  处理上下文菜单消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu popMenu, *pPopup;
	
	if (pWnd->m_hWnd == m_RichEdit_Recv.m_hWnd) {                              /* 如果在编辑框内右击 */

		popMenu.LoadMenu(IDR_MENU_EDIT);                                       /* 载入菜单 */
		pPopup = popMenu.GetSubMenu(0);                                        /* 获得菜单指针 */

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		pPopup->Detach();
		popMenu.DestroyMenu();
	}
}

/**************************************************************************************************
**  函数名称:  OnSysCommand
**  功能描述:  处理系统消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_MINIMIZE) {                                                  /* 如果是要窗体最小化 */
		CloseAllChildWin();                                                    /* 关闭所有子窗口 */
	}

	CDialog::OnSysCommand(nID, lParam);
}


