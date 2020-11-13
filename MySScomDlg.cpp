#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const CString RecordPath = "Record\\";                                  /* �����������ļ����ļ��е�·�� */

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

	AfxInitRichEdit();                                                         /* ��ʼ��RichEdit�ؼ� */
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
**  ��������:  EnumCommPortList
**  ��������:  ����������ö�ٵ����ϴ��ڿ��õĴ���
**  �������:  
**  ���ز���:  
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
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== ����Ϊ�ؼ�״̬���� ===================================== */

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
**  ��������:  SetSendCtrlArea
**  ��������:  �ڷ����ļ���ʱ�����ø�����������״̬
**  �������:  
**  ���ز���:  
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
	SetDlgItemText(IDC_BUTTON_SENDFILE, (Enable == TRUE) ? "��ʼ����" : "ֹͣ����");
	GetDlgItem(IDC_EDIT_SEND)->ShowWindow((Enable == TRUE) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BUTTON_SEND)->ShowWindow((Enable == TRUE) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_PROGRESS_SENDFILE)->ShowWindow((Enable == TRUE) ? SW_HIDE : SW_SHOW);

	if (Enable == TRUE) {
		SetDlgItemText(IDC_STATIC_SEND, "������");
	}
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== ����Ϊ��Ϣ������ ===================================== */

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlIconNotify
**  ��������:  ��������ͼ����Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlIconNotify(WPARAM wParam, LPARAM lParam)
{
	UINT    uMouseMsg = LOWORD(lParam);
	CMenu   oMenu;
	CPoint  oPoint;

	switch (uMouseMsg)
	{
		case WM_LBUTTONDBLCLK:                                                 /* ��������˫�� */
			ShowWindow(IsWindowVisible() ? SW_HIDE : SW_SHOWNORMAL);
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

	return 0;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlComDevList
**  ��������:  ������´��ں������б����ݵ���Ϣ �������豸�����̼߳����������豸�����仯ʱ�����ͱ���Ϣ��������֪ͨ��ˢ���б���ʾ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlComDevList(WPARAM wParam, LPARAM lParam)
{
	UpdateComboComs();
	
	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlDataRecved
**  ��������:  ������յ��˴������ݵ���Ϣ ���������ݼ����߳��յ���������ʱ�����ͱ���Ϣ��������������ݽ�������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlDataRecved(WPARAM wParam, LPARAM lParam)
{
	unsigned char buff[MAX_SEND_BYTE];

	memcpy(buff, (unsigned char *)lParam, wParam);

	HandleUSARTData(buff, wParam);

	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlDatatoSend
**  ��������:  �����д���������Ҫ���͵���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlDatatoSend(WPARAM wParam, LPARAM lParam)
{
	unsigned char buff[MAX_SEND_BYTE];
	
	memcpy(buff, (unsigned char *)lParam, wParam);

	SendDatatoComm(buff, wParam, FALSE);

	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlARDlgClose
**  ��������:  �����Զ��ظ����ڹرյ���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlARDlgClose(WPARAM wParam, LPARAM lParam)
{
	//GetDlgItem(IDC_BUTTON_EXFUNCT)->EnableWindow(TRUE);

	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlDFDlgClose
**  ��������:  ������ʾ���˴��ڹرյ���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlDFDlgClose(WPARAM wParam, LPARAM lParam)
{
	//GetDlgItem(IDC_BUTTON_EXFUNCT)->EnableWindow(TRUE);

	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlEFDlgClose
**  ��������:  �����ӹ��ܴ��ڹرյ���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlEFDlgClose(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_BUTTON_EXFUNCT)->EnableWindow(TRUE);

	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlSSDlgClose
**  ��������:  ����߼����ʹ��ڹرյ���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlSSDlgClose(WPARAM wParam, LPARAM lParam)
{
	SetDlgItemText(IDC_BUTTON_SRSEND, "�߼�����");
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
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ==================================== ����Ϊ�Զ��崦���� =================================== */

/**************************************************************************************************
**  ��������:  CloseAllChildWin
**  ��������:  �ر������Ӵ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::CloseAllChildWin(void)
{
	s_PDlgSuprSend->ShowHideDlgWindow(FALSE);                                  /* �رո߼����ʹ��� */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_SSDLGCLOSE, 0, 0); 

	s_PDlgExtrfunc->ShowHideDlgWindow(FALSE);                                  /* �رո��ӹ��ܴ��� */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_EFDLGCLOSE, 0, 0);   

	s_PDlgDsplFilt->ShowHideDlgWindow(FALSE);                                  /* �رչ������ô��� */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_DFDLGCLOSE, 0, 0);

	s_PDlgAutoRply->ShowHideDlgWindow(FALSE);                                  /* �ر��Զ��ظ����� */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_ARDLGCLOSE, 0, 0);
}

/**************************************************************************************************
**  ��������:  SaveEditContent
**  ��������:  ����༭������ݵ��ı��ļ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CMySScomDlg::SaveEditContent(void)
{
    CFile   MyFile;                                                            /* �����ļ��� */
    CTime   NowTime  = CTime::GetCurrentTime();                                /* ��ȡ����ʱ�� */
    CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";
    
    GetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
	
	if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite)) {
        MyFile.Write(m_Edit_Recv, m_Edit_Recv.GetLength());                    /* д���ı��ļ� */
        MyFile.Close();                                                        /* �ر��ļ� */
		return TRUE;
    } else {
		return FALSE;
	}
}

/**************************************************************************************************
**  ��������:  UpdateEditStr
**  ��������:  �����²��ֵ��ַ���ʾ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::UpdateEditStr(CString showstr)
{
	int     linecnt;
	CString TimeStr, TempStr;
	unsigned char sbuf[MAX_SEND_BYTE];

    /* ���û�п����Զ�������ݵĹ��ܣ�ͬʱ�������Ѿ�������̫������ݣ�Ϊ�˷�ֹCPUռ���ʹ��ߣ������Ҫǿ����� */

    if ((m_Check_AutoClear == FALSE) && (s_RecvedByte >= MAX_DISP_BYTE)) {
        s_RecvedLine = 0;                                                      /* ������ձ���ֵ */
        s_RecvedByte = 0;
        m_Edit_Recv = "";
        SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);                            /* ��ձ༭������ */
		MessageBox("���յ�����������ʵ��̫���������ܲ�����\r\n���Ծ�����������ˣ��������ϲ�Ҫ������......\r\n��ϵͳ�ȶ��Գ�����С�Ľ���������û��ǿ����Զ���չ���\r\n�������Ǹ���������ȴ�ִӲ�����һ�µĻ����Һ����ױ�����Ŷ~~~", "��ʾ", MB_OK + MB_ICONINFORMATION);
    }

    /* �����������ʾ���˹��ܣ�������ַ���ƥ�䣬����Ҫ��ʾ���ַ������ݲ�����ʾ��ֻ�Ǹ���һ��״̬����ͳ����Ϣ */
	if ((m_Check_Filter == TRUE) && (s_PDlgDsplFilt->StringCanDisplay(showstr) == FALSE)) {
		UpdateStatusBarNow();
		return;
	}

	/* �����16������ʾģʽ�£�ͬʱ�������Զ��ظ��Ĺ��ܡ����жϽ��յ����ַ����Ƿ��������������ֶΣ��������Զ��ظ� */
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
    
    if (m_Check_HexDspl == TRUE) {                                             /* 16����ģʽ�� */
		linecnt = s_RecvedByte;                                                /* ���ַ������жϽ�� */
	} else {                                                                   /* �ַ�ģʽ�� */
        linecnt = s_RecvedLine;                                                /* ���������жϽ�� */
    }

	#if 0                                                                      /* �������ַ����ᵼ������������� */
	{
		s_Edit_Recv->SetSel(-1, -1);                                           /* ��ӱ��ε�������ʾ */
		s_Edit_Recv->ReplaceSel((LPCTSTR)showstr);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);                    /* �ñ༭�����ݹ��������һ�� */
	}
	#else                                                                      /* �������ַ����ᵼ��CPUռ���ʹ��ߡ��� */
	{
		m_Edit_Recv += showstr;                                                /* ��ӱ��ε�������ʾ */
		SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
        s_Edit_Recv->SetSel(-1, -1);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);                    /* �ñ༭�����ݹ��������һ�� */
	}
	#endif

	if (showstr.Right(1) == "\n") {                                            /* ������յ��˻س��� */

		if (m_Check_AutoClear == TRUE) {                                       /* �����Ҫ�Զ�������� */
			
			GetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                      /* ��ȡ���ݲ����� */
			
			if (linecnt >= atoi((LPSTR)(LPCTSTR)m_Edit_Lines)) {               /* �ж��Ƿ������������*/
				
				s_RecvedLine = 0;                                              /* ������ձ���ֵ */
				s_RecvedByte = 0;
				
				if (m_Check_AutoSave) {
					SaveEditContent();                                         /* ����༭������� */
				}
				
				m_Edit_Recv = "";
				SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);                    /* ��ձ༭������ */
			}
		}
	}

    /*************************************************************************************************\
    |                          �������ʵ�ֶԽ��ձ༭��������������������                           |
    \*************************************************************************************************/
    
    if (GetFocus() == GetDlgItem(IDC_EDIT_RECV)) {                             /* �����ڽ���ת�������ͱ༭�� */
        GetDlgItem(IDC_EDIT_INPUT)->SetFocus();
    }

	UpdateStatusBarNow();                                                      /* ����״̬��ͳ�����ݵ���ʾ */
}

/**************************************************************************************************
**  ��������:  UpdateEditDisplay
**  ��������:  ���±༭�����ʾ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::UpdateEditDisplay(void)
{
	CString TimeStr, TempStr;
    CTime   NowTime;

    if (m_Check_HexDspl == TRUE) {                                             /* 16����ģʽ�� */

        TempStr = TransformtoHex(s_RecvString);                                /* ת�����Ϊ16������ʾ */

		if (s_NeedChgLne == TRUE) {                                            /* �����Ҫ������ʾ */
			if (m_Check_ShowTime == TRUE) {                                    /* ����ʱ����ʾ���� */
				NowTime = CTime::GetCurrentTime();                             /* ��ȡ����ʱ�� */
				TimeStr = NowTime.Format("[%H:%M:%S] ");
				TempStr = TimeStr + TempStr; 
			}
			s_NeedChgLne = FALSE;
		}
    } else {                                                                   /* �ַ�ģʽ�� */
		TempStr = s_RecvString;                                                /* ����ת����ֱ����ʾ */
    }

	s_RecvString = "";

	UpdateEditStr(TempStr);                                                    /* ������ʾ���յ����ַ� */
}

/**************************************************************************************************
**  ��������:  HandleUSARTData
**  ��������:  ���մ�������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::HandleUSARTData(unsigned char *sbuf, DWORD len)
{
    DWORD   i;
    CString ShowStr, TempStr, TimeStr;
    CTime   NowTime;

	TempStr = "";
	ShowStr = "";

	if (s_RecvPaused == TRUE) return;                                          /* ��ͣ����ʱ�������д��� */

    for (i = 0; i < len; i++) {                                                /* ������ת��ΪCstring�ͱ��� */

		if (m_Check_HexDspl == TRUE) {                                         /* ��ǰ����16������ʾģʽ */

			/* ���ǵ�00�ַ��������ԣ���Ҫ�������ת����ܴ洢��ת��������£�00ת���FF 01��FFת���FF 02�������ַ���ת�� */

			if (sbuf[i] == 0) {                                                /* 00 ת��� FF 01 */
				TempStr.Format("%c%c", 0xFF, 0x01);
			} else if ((unsigned char)(sbuf[i]) == 0xFF) {                     /* FF ת��� FF 02 */
				TempStr.Format("%c%c", 0xFF, 0x02);
			} else {
				TempStr.Format("%c", sbuf[i]);
			}

			ShowStr += TempStr;                                                /* ������������ */
			
			if (m_Check_FrameDspl == TRUE) {                                   /* �����жϽ�����һ��ʱ�����Ƿ�û�����յ��������� */
				KillTimer(Timer_No_FrameDspl);                                 /* ��ʵ��16�����£���֡������ʾ�Ĺ��� */
				SetTimer(Timer_No_FrameDspl, CHNGLINE_INTERVAL, NULL);         /* ��������������ʱ���ж��Ƿ�û�����յ��������� */
			}
			
		} else {                                                               /* ��ǰ�����ַ���ʾģʽ */

			if (s_NeedChgLne == TRUE) {                                        /* ���������һ���� */

				if (m_Check_ShowTime == TRUE) {                                /* ���������ʱ����ʾ���� */
					NowTime = CTime::GetCurrentTime();                         /* ��ȡ��ǰϵͳʱ�� */
					TimeStr = NowTime.Format("[%H:%M:%S] ");
					ShowStr = ShowStr + TimeStr;
				}
				
				s_NeedChgLne = FALSE;
			}

			TempStr.Format("%c", sbuf[i]);                                     /* ������յ������� */
			ShowStr += TempStr;                                                /* ������������ */

			if (TempStr == "\n") {                                             /* ���ν��յ��س��� */

				s_RecvedLine++;                                                /* ���յ��������ۼ� */
			    s_NeedChgLne = TRUE;                                           /* �����Ҫ������ʾ */
			}
        }
    }

	s_RecvedByte += len;                                                       /* �����ֽ����ۼ� */
    s_DataRecved  = TRUE;
	s_RecvString += ShowStr;                                                   /* ע������Ҫ�üӺţ���Ȼ�����֮ǰ�����ݶ�ʧ */
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
    
    if (Timer > 0) {

        SetTimer(Timer_No_AutoSend, Timer, NULL);                              /* ������ʱ�� */

        GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);

        m_Edit_AutoTimer = TempStr;                                            /* ���±༭������ */
        SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);

        GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);                      /* ���÷��Ͱ�ť */
		GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(FALSE);

    } else {

        MessageBox("����ʱ��������Ϊ0����ȷ�ϣ�  ", "��ʾ", MB_OK + MB_ICONEXCLAMATION);

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

#if VERSION_CTRL == VERSION_YAXON
	if (DialogMain.Width() > 1300) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з��� - Designed By LEON (LEON1741@126.com) - �����ڲ�������лл��";
	} else if (DialogMain.Width() > 1200) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з��� - Designed By LEON (LEON1741@126.com)";
	} else if (DialogMain.Width() > 1100) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з��� - Designed By LEON";
	} else if (DialogMain.Width() > 1000) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з��� - LEON";
	} else if (DialogMain.Width() > 900) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ�����з���";
	} else if (DialogMain.Width() > 850) {
		DisplayStr = " ��ӭʹ��MySScom - ��Ѹ����";
	} else if (DialogMain.Width() > 800) {
		DisplayStr = " ��ӭʹ��MySScom";
	} else if (DialogMain.Width() > 700) {
		DisplayStr = " ��ӭʹ��";
	} else {
		DisplayStr = "";
	}
#else
    if (DialogMain.Width() > 1200) {
        DisplayStr = " ��ӭʹ��MySScom - Designed By LEON (LEON1741@126.com) - Welcome to Email me!!";
    } else if (DialogMain.Width() > 1100) {
        DisplayStr = " ��ӭʹ��MySScom - Designed By LEON (LEON1741@126.com)";
    } else if (DialogMain.Width() > 1000) {
        DisplayStr = " ��ӭʹ��MySScom - Designed By LEON";
    } else if (DialogMain.Width() > 850) {
        DisplayStr = " ��ӭʹ��MySScom - LEON";
    } else if (DialogMain.Width() > 800) {
        DisplayStr = " ��ӭʹ��MySScom";
    } else if (DialogMain.Width() > 720) {
        DisplayStr = " ��ӭʹ��";
    } else {
        DisplayStr = "";
    }
#endif

	s_CStatusBar.SetPaneText(0, DisplayStr);
        
    DisplayStr = (SerialDevisOpened() == TRUE) ? " �����Ѵ�" : " ����δ��";  
    s_CStatusBar.SetPaneText(1, DisplayStr);

    DisplayStr.Format(" Lines: %.5d", s_RecvedLine);
    s_CStatusBar.SetPaneText(2, DisplayStr);
        
    DisplayStr.Format(" Recv: %.6d", s_RecvedByte);
    s_CStatusBar.SetPaneText(3, DisplayStr);

    DisplayStr.Format(" Send: %.6d", s_SendedByte);
    s_CStatusBar.SetPaneText(4, DisplayStr);

    Nowtime = CTime::GetCurrentTime();
    DisplayStr = " ��ǰʱ��: " + Nowtime.Format("%Y-%m-%d") + " " + Nowtime.Format("%H:%M:%S");
    s_CStatusBar.SetPaneText(5, DisplayStr);
}

/**************************************************************************************************
**  ��������:  SendDatatoComm
**  ��������:  ��ָ�����ַ������ͳ�ȥ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CMySScomDlg::SendDatatoComm(unsigned char *sbuf, int slen, BOOL needhex)
{
	int j, len;
	CString  tempstr;
	unsigned char temp[MAX_SEND_BYTE];
	CByteArray hexdata;	
	
    if (needhex) {                                                             /* �����Ҫ��16���Ʒ��� */

		if (slen > MAX_SEND_BYTE * 3) {                                        /* ���ݳ��ȹ��� */
			return FALSE;
		}

		tempstr.Format("%s", sbuf);
		if (ParseCStrisLegal(tempstr) == FALSE) {                              /* �ַ������ݷǷ� */
			return FALSE;
		}

        len = String2Hex(tempstr, hexdata);                                    /* ���ַ���ת��Ϊʵ�ʶ�Ӧ������ */
		
        for (j = 0; j < len; j++) {                                            /* ��ʵ�����ݱ��������� */
            temp[j] = hexdata.GetAt(j);
        }
        
        s_SendedByte += SendSerialData(temp, len);                             /* д�봮�ڷ��ͣ������ֽ����ۼ� */
        
    } else {                                                                   /* �ַ�ģʽ�£�ֱ�ӷ��� */

		if (slen > MAX_SEND_BYTE) {                                            /* ���ݳ��ȹ��� */
			return FALSE;
		}

        s_SendedByte += SendSerialData(sbuf, slen);                            /* д�봮�ڷ��ͣ������ֽ����ۼ� */
    }
	
    if (m_Check_Return == TRUE) {                                              /* �����س����з� */
		
        temp[0] = '\r';
        temp[1] = '\n';
        
        s_SendedByte += SendSerialData(temp, 2);
    }

    UpdateStatusBarNow();                                                      /* ����״̬��ͳ�����ݵ���ʾ */
	
	return TRUE;
}

/**************************************************************************************************
**  ��������:  SendFileDatatoComm
**  ��������:  ���ļ����ݷ��͵�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CMySScomDlg::SendFileDatatoComm(void)
{
	CFile          filename;
	int            baudrate, sendbyte;
	unsigned long  fileleng;
	unsigned char *filebuff;                                                   /* ���ڴ���ļ����� */
	double         tempbyte;
	CString        dsplystr;
	unsigned int   totltime, lefttime;

	if (filename.Open(m_Edit_FilePath, CFile::modeReadWrite | CFile::typeBinary) == 0) {
		MessageBox("��ȡ�ļ�ʧ�ܣ���ȷ��·����ȷ���ļ�δ���ڴ�״̬��    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return FALSE;
	}

	fileleng = (unsigned long)filename.GetLength();                            /* ��ȡ�ļ����� */
	
	baudrate = m_Combo_Baud.GetCurSel();
	baudrate = Combo_Baud[baudrate];

	tempbyte = ((double)baudrate / FILESEND_BYTE) * 1.1;
	sendbyte = (int)tempbyte;

	if ((s_FileDatPos + sendbyte) > fileleng) {                                /* ������Ҫ�����һ�����������ж� */
		sendbyte = fileleng - s_FileDatPos;
	}
	
    filebuff = new unsigned char[sendbyte];                                    /* �����ڴ�ռ� */
	filename.Seek(s_FileDatPos, CFile::begin);                                 /* ��λ���ϴη��͵�λ�� */
    filename.Read(filebuff, sendbyte);                                         /* ��ȡ�ļ����� */

	sendbyte = SendSerialData(filebuff, sendbyte);                             /* �������ݣ���ͳ�Ƴ��� */
	s_FileDatPos += sendbyte;
	s_SendedByte += sendbyte;

	totltime = (fileleng * 10) / baudrate;                                     /* ���㷢�������ļ��ĺ�ʱ */
	lefttime = (fileleng - s_FileDatPos) * 10 / baudrate;                      /* ���㷢�������ļ��ĺ�ʱ */

	m_Progress_SendFile.SetPos(s_FileDatPos * PROGRESS_POS / fileleng);        /* ���½�������ʾ */

	dsplystr.Format("��������Ԥ�ƺ�ʱ%0.2d��%0.2d�룬��ǰ����%0.2d%%��ʣ��%0.2d��%0.2d��", 
		            totltime / 60, totltime % 60, s_FileDatPos * 100 / fileleng, lefttime / 60, lefttime % 60);
	SetDlgItemText(IDC_STATIC_SEND, dsplystr);
	
	filename.Close();                                                          /* �ر��ļ� */
	delete []filebuff;                                                         /* �ͷſռ� */

	if (s_FileDatPos >= fileleng) {                                            /* ȫ�����ݷ������ */
		s_FileDatPos = 0;
		KillTimer(Timer_No_SendFile);
		SetSendCtrlArea(TRUE);                                                 /* �����������Ϳؼ� */
	}

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
    CString temp;
	
	// ��������ж�Ŀ¼���Ƿ����INI�ļ������������򴴽����ļ���д��Ĭ��ֵ

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
**  ��������:  InitiateAllParas
**  ��������:  ��ȡ�����ļ��ĸ����������ݲ���ʼ���Ի����ֵ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateAllParas(void)
{
    int  TempData;                                                             /* ��Ҫע����ǣ��Զ�����ʹ�ܺ�ѭ������ʹ�����������ʼ�� */
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

	if (m_Check_HexDspl == TRUE) {                                             /* ���ݶ���Ĳ���ֵ��ʼ����ʾ������ */
        SetDlgItemText(IDC_STATIC_LINES, "�ַ�");
    } else {
        SetDlgItemText(IDC_STATIC_LINES, "��");
    }

	if (m_Check_HexSend == TRUE) {                                             /* ���ݶ���Ĳ���ֵ��ʼ����ʾ������ */
		m_Edit_Send = s_SendStr_Hex;
	} else {
		m_Edit_Send = s_SendStr_Chr;
	}

	SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
    
	UpdateData(FALSE);                                                         /* ���±༭������ */
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
	if (m_Check_HexSend == TRUE) {                                                /* ����ͬ������һ�±༭������� */
		s_SendStr_Hex = m_Edit_Send;
	} else {
		s_SendStr_Chr = m_Edit_Send;
	}

	::WritePrivateProfileString("SendConfig", "SendStrH",  s_SendStr_Hex, ".\\Settings.ini");

	ParaStr = FormatQuotesStrWrite(s_SendStr_Chr);
	::WritePrivateProfileString("SendConfig", "SendStrC",  ParaStr, ".\\Settings.ini");
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
    
    if (!s_CStatusBar.Create(this) || !s_CStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT))) {
        TRACE0("Failed to create status barn");
        return;
    }

    time = CTime::GetCurrentTime();
    m_strTime = " ��ǰʱ��: " + time.Format("%Y-%m-%d") + " " + time.Format("%H:%M:%S");

#if VERSION_CTRL == VERSION_YAXON
    s_CStatusBar.SetPaneInfo(0, nID, SBPS_STRETCH, 1);
    s_CStatusBar.SetPaneText(0, " ��ӭʹ��MySScom - ��Ѹ����");
#else
    s_CStatusBar.SetPaneInfo(0, nID, SBPS_STRETCH, 1);
    s_CStatusBar.SetPaneText(0, " ��ӭʹ��MySScom - LEON");
#endif

    s_CStatusBar.SetPaneInfo(1, nID, SBPS_NORMAL, 90);
    s_CStatusBar.SetPaneText(1, " ����δ��");

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
**  ��������:  InitiateComboComs
**  ��������:  ��ʼ�����ں���Ͽ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateComboComs(void)
{
    EnumCommPortList();                                                        /* ö�ٿ��õĴ��� */

	m_Combo_ComNo.ResetContent();
	m_Combo_ComNo.AddString("��ѡ��");                                         /* ��һ��Ϊ��ʾ�� */

    for (int i = 0; i < s_PortNumber.GetSize(); i++) {
        m_Combo_ComNo.AddString(s_PortNumber.GetAt(i));
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
**  ��������:  InitiateChildWins
**  ��������:  ��ʼ�������Ӵ���ҳ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CMySScomDlg::InitiateChildWins(void)
{
	s_PDlgSuprSend = new CDialogSuperSend();                                   /* ������䴴���߼����ʹ��壬�����ش��� */

	if (s_PDlgSuprSend != NULL){

		int Result = s_PDlgSuprSend->Create(IDD_DIALOG_SRSEND, this);

		if (!Result) {
			MessageBox("ϵͳ��Դ���㣬�����Ի���ʧ��......   ", "��Ǹ", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		s_PDlgSuprSend->ShowWindow(SW_HIDE);
		s_PDlgSuprSend->InitiateAllParas();
	}

	s_PDlgExtrfunc = new CDialogExtrafunct();                                  /* ������䴴�����ӹ��ܴ��壬�����ش��� */

	if (s_PDlgExtrfunc != NULL){

		int Result = s_PDlgExtrfunc->Create(IDD_DIALOG_EXFUNCT, this);

		if (!Result) {
			MessageBox("ϵͳ��Դ���㣬�����Ի���ʧ��......   ", "��Ǹ", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		s_PDlgExtrfunc->ShowWindow(SW_HIDE);
		s_PDlgExtrfunc->InitiateAllParas();
	}

	s_PDlgDsplFilt = new CDialogDsplFilt();                                    /* ������䴴����ʾ�������ô��壬�����ش��� */

	if (s_PDlgDsplFilt != NULL){

		int Result = s_PDlgDsplFilt->Create(IDD_DIALOG_FILTER, this);

		if (!Result) {
			MessageBox("ϵͳ��Դ���㣬�����Ի���ʧ��......   ", "��Ǹ", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		s_PDlgDsplFilt->ShowWindow(SW_HIDE);
		s_PDlgDsplFilt->InitiateAllParas();
	}

	s_PDlgAutoRply = new CDialogAutoReply();                                   /* ������䴴���Զ��ظ����壬�����ش��� */

	if (s_PDlgAutoRply != NULL){

		int Result = s_PDlgAutoRply->Create(IDD_DIALOG_AUTOREPLY, this);

		if (!Result) {
			MessageBox("ϵͳ��Դ���㣬�����Ի���ʧ��......   ", "��Ǹ", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		s_PDlgAutoRply->ShowWindow(SW_HIDE);
		s_PDlgAutoRply->InitiateAllParas();
	}

	return TRUE;
}

/**************************************************************************************************
**  ��������:  InitiateToolsTip
**  ��������:  ��ʼ���������¸����ؼ���������ʾ��Ϣ
**  �������:  
**  ���ز���:  
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
**  ��������:  UpdateComboComs
**  ��������:  ���´��ں���Ͽ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::UpdateComboComs(void)
{
    int      pindex;
	CString  comstr;
	
	pindex = m_Combo_ComNo.GetCurSel();                                        /* ���Ȼ�ȡ��ǰѡ��Ĵ��ں� */

	if (pindex == 0) {                                                         /* 0��ʾû��ѡ����Ч�Ĵ��ں� */
		comstr = "";
	} else {                                                                   /* ���ݴ��ںŻ�ȡ��COM�ַ��� */
		comstr = s_PortNumber.GetAt(pindex - 1);
	}

	InitiateComboComs();

	if (comstr == "") {                                                        /* ��ʾ֮ǰû��ѡ����Ч���ں� */
		m_Combo_ComNo.SetCurSel(0);                                            /* ֱ��ѡ����ʾ�� */
		return;
	}

	for (pindex = 0; pindex < s_PortNumber.GetSize(); pindex++) {              /* ֮ǰ����ѡ�й�ĳ�����ں� */
		if (s_PortNumber.GetAt(pindex) == comstr) {                            /* ����ȶԣ���λ���ô��ڵ���� */
			m_Combo_ComNo.SetCurSel(pindex + 1);                               /* �Զ�ѡ�иô��ں� */
			return;
		}
	}

	m_Combo_ComNo.SetCurSel(0);                                                /* �ȶ�ʧ�ܣ�˵��֮ǰѡ�еĴ�������ʧ����ָ�����ʾ�� */
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
    d.uCallbackMessage = WM_USERMSG_NOTIFYICON;
    
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

/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */

/* ================================== �����ؼ���Ϣ����--��ʼ =================================== */

/**************************************************************************************************
**  ��������:  OnButtonPortCtrl
**  ��������:  ���ڿ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonPortCtrl() 
{
    CString TempStr;
    SRL_DEV_PARA_T spara;
    
    if (SerialDevisOpened() == TRUE) {                                         /* ��������Ѿ��򿪣���ôִ�йرղ��� */

        if ((m_Check_AutoSend == TRUE) || (s_PDlgSuprSend->s_issenddata == TRUE)) {
            MessageBox("������ͣ���Զ����͹����ٳ��Թرմ���...  ", "��ʾ", MB_OK + MB_ICONINFORMATION);
            return;
        }

		if (s_FileDatPos != 0) {
            MessageBox("���ڷ����ļ�������ֹͣ�ļ��ķ��ͣ��ٳ��Թرմ���...  ", "��ʾ", MB_OK + MB_ICONINFORMATION);
            return;
        }
        
		CloseSerialDevice();                                                   /* �رմ����豸 */
		CloseAllChildWin();                                                    /* �رո����Ӵ��� */

		SetControlStatus(FALSE);

        SetDlgItemText(IDC_BUTTON_ONOFF, "�򿪴���");
        GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_DATA)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_CHECK)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_STOP)->EnableWindow(TRUE);

        return;
    }

    int ComNumber = m_Combo_ComNo.GetCurSel();                                 /* �õ����ں� */

    if (ComNumber == 0) {
        MessageBox("�����ںŶ�û��ѡ������Ҵ�ʲô����...��   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        return;
    }

	m_Combo_ComNo.GetLBText(ComNumber, TempStr);                               /* ��ȡ���ں�ѡ���� */
    CString ComDevFile = "\\\\.\\" + TempStr;

    TempStr.Format("%d", Combo_Baud[m_Combo_Baud.GetCurSel()]);                /* ��ȡ������ѡ���� */
    spara.baudrate = atoi(TempStr);
    
    TempStr.Format("%d", Combo_Data[m_Combo_Data.GetCurSel()]);                /* ��ȡ����λѡ���� */
    spara.databits = atoi(TempStr);
    
    TempStr.Format("%d", Combo_Check[m_Combo_Check.GetCurSel()]);              /* ��ȡУ��λѡ���� */
    spara.checkbit = atoi(TempStr);

    TempStr.Format("%d", Combo_Stop[m_Combo_Stop.GetCurSel()]);                /* ��ȡֹͣλѡ���� */
    spara.stopbits = atoi(TempStr);

	if (OpenSerialDevice(ComDevFile, &spara) == FALSE) {                       /* �򿪴��ڲ���ʼ�� */
		return;
	}

    SetControlStatus(TRUE);                                                    /* ���ø�����ť�ؼ� */
    SetDlgItemText(IDC_BUTTON_ONOFF, "�رմ���");
    GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_CHECK)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);
}

/**************************************************************************************************
**  ��������:  OnButtonRecvPause
**  ��������:  ��ͣ����/�ָ�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonRecvPause() 
{
    if (s_RecvPaused == FALSE) {
        s_RecvPaused = TRUE;
        SetDlgItemText(IDC_BUTTON_PAUSE, "�ָ�����");
        GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(FALSE);
    } else {
        s_RecvPaused = FALSE;
        SetDlgItemText(IDC_BUTTON_PAUSE, "��ͣ����");
        GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(TRUE);
    }
}

/**************************************************************************************************
**  ��������:  OnButtonClearAll
**  ��������:  ����������Ѿ����յ�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonClearAll()
{
    m_Edit_Recv = "";
    SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);

    s_RecvedLine = 0;
    s_RecvedByte = 0;
    s_SendedByte = 0;
    s_RecvString = "";
    s_NeedChgLne = TRUE;                                                       /* �´���Ҫ������ʾ */

    UpdateStatusBarNow();                                                      /* ����״̬����ͳ��������ʾ */
}

/**************************************************************************************************
**  ��������:  OnButtonSaveFile
**  ��������:  �����յ������ݱ��浽�ļ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSaveFile()
{
    CTime   NowTime  = CTime::GetCurrentTime();                                /* ��ȡ����ʱ�� */
    CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";           /* ָ���ļ��� */
    
    GetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
    
    if (m_Edit_Recv.GetLength() <= 0) {
        MessageBox("��δ���յ��κ����ݣ����뱣�棡   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        return;
    }

	if (SaveEditContent() == TRUE) {
		MessageBox("���������Ѿ��ɹ�������ָ���ļ�!      ", "��ϲ", MB_OK + MB_ICONINFORMATION);
	} else {
		MessageBox("�ļ�����ʧ��!         ", "��Ǹ", MB_OK + MB_ICONWARNING);
	}
}

/**************************************************************************************************
**  ��������:  OnButtonSendData
**  ��������:  ���ʹ��������������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSendData()
{
    unsigned char buff[MAX_SEND_BYTE];
	
	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
    
    if (m_Edit_Send.GetLength() <= 0) {
        MessageBox("���ʹ�������Ϊ�գ�δ�����κ����ݣ� ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        return;
    }
	
	strncpy_s((char *)&buff[0], sizeof(buff), (LPCTSTR)m_Edit_Send, m_Edit_Send.GetLength());

	if (SendDatatoComm(buff, m_Edit_Send.GetLength(), m_Check_HexSend) == FALSE) {
		MessageBox("�����������֡���ݹ��������ߴ��ڷǷ��ַ�����ȷ�ϣ�......       ", "����", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
}

/**************************************************************************************************
**  ��������:  OnButtonSuperSend
**  ��������:  ��ʾ�߼����ʹ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSuperSend() 
{
	if (s_PDlgSuprSend->IsWindowVisible()) {                                     /* �����Ѿ��򿪣����Թر� */

		if ((s_PDlgSuprSend->s_issenddata) == TRUE) {
			MessageBox("����ֹͣ�Զ�ѭ�����͹��ܣ��ٳ��Թرո߼����ʹ���......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			s_PDlgSuprSend->ShowHideDlgWindow(FALSE);
			SetDlgItemText(IDC_BUTTON_SRSEND, "�߼�����");
			
			GetDlgItem(IDC_CHECK_HEXSEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_OPENFILE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(TRUE);
		}
		
	} else {                                                                   /* ������δ�򿪣����Դ� */

		if (m_Check_AutoSend) {
			MessageBox("����ֹͣ�������ݵ��Զ����͹��ܣ��ٳ��Դ򿪸߼����ʹ���......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			s_PDlgSuprSend->ShowHideDlgWindow(TRUE);
			SetDlgItemText(IDC_BUTTON_SRSEND, "��������");

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
**  ��������:  OnButtonExtrafunc
**  ��������:  ��ʾ���ӹ��ܴ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonExtrafunc() 
{
	if (s_PDlgExtrfunc->IsWindowVisible() == FALSE) {                            /* ������δ�򿪣����Դ� */
		s_PDlgExtrfunc->ShowHideDlgWindow(TRUE);
	}
}

/**************************************************************************************************
**  ��������:  OnButtonOpenFile
**  ��������:  ���ļ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonOpenFile() 
{
	CFile myFile;
	
	CFileDialog dlg(TRUE, "*.bin", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, 
						  "����֧�ֵ��ļ�(*.bin;*.hex;*.dat)|*.bin;*.hex;*.dat|\
						   bin�ļ�(*.bin)|*.bin|\
						   hex�ļ�(*.hex)|*.hex|\
						   dat�ļ�(*.dat)|*.dat|\
						   �����ļ�(*.*)|*.*||");
	
	if (dlg.DoModal() != IDOK) {                                               /* δѡ���κ��ļ� */
		return;
	}
	
	m_Edit_FilePath = dlg.GetPathName();						               /* �����ļ���·�� */
	
	SetDlgItemText(IDC_EDIT_FILEPATH, m_Edit_FilePath);
}

/**************************************************************************************************
**  ��������:  OnButtonSendFile
**  ��������:  �����ļ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSendFile() 
{
	CFile myFile;
	
	if (s_FileDatPos == 0) {                                                   /* ��δ��ʼ���ͣ���ʼ���� */

		GetDlgItemText(IDC_EDIT_FILEPATH, m_Edit_FilePath);
		
		if (m_Edit_FilePath == "") {
			MessageBox("����δָ����Ҫ���͵��ļ���·����    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			return;
		}
		
		if (myFile.Open(m_Edit_FilePath, CFile::modeReadWrite | CFile::typeBinary) == 0) {
			MessageBox("��ȡ�ļ�ʧ�ܣ���ȷ��·����ȷ���ļ�δ���ڴ�״̬��    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			if (myFile.GetLength() <= 0) {
				MessageBox("�ļ�����Ϊ�գ�������ֹ��    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
				return;
			} else {
				s_FileDatPos = 0;
				SetTimer(Timer_No_SendFile, FILESEND_BYTE, NULL);              /* ������ʱ�� */
				SetSendCtrlArea(FALSE);                                        /* �����������Ϳؼ� */
				m_Progress_SendFile.SetPos(0);
			}
		}
	} else {                                                                   /* ���ڷ��͹����У���ֹͣ���� */
		s_FileDatPos = 0;
		KillTimer(Timer_No_SendFile);                                          /* �رն�ʱ�� */
		SetSendCtrlArea(TRUE);                                                 /* �ָ��������Ϳؼ� */
	}
}

/**************************************************************************************************
**  ��������:  OnButtonConfigAutoReply
**  ��������:  ���Զ��ظ����ܵ����ô���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonConfigAutoReply()
{
	if (s_PDlgAutoRply->IsWindowVisible() == FALSE) {                            /* ������δ�򿪣����Դ� */
		s_PDlgAutoRply->ShowHideDlgWindow(TRUE);
	}
}

/**************************************************************************************************
**  ��������:  OnButtonConfigDsplFilt
**  ��������:  ����ʾ���˷�������ô���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonConfigDsplFilt()
{
	if (s_PDlgDsplFilt->IsWindowVisible() == FALSE) {                            /* ������δ�򿪣����Դ� */
		s_PDlgDsplFilt->ShowHideDlgWindow(TRUE);
	}
}

/**************************************************************************************************
**  ��������:  OnCheckHexDisplay
**  ��������:  ��ʾ16�����ַ���ѡ��״̬�л�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckHexDisplay()
{
    m_Check_HexDspl = !m_Check_HexDspl;

	GetDlgItem(IDC_CHECK_FRAMEDSPL)->EnableWindow(m_Check_HexDspl);
	GetDlgItem(IDC_CHECK_AUTOREPLY)->EnableWindow(m_Check_HexDspl);
	GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(m_Check_HexDspl);

    if (m_Check_HexDspl == TRUE) {
        SetDlgItemText(IDC_STATIC_LINES, "�ַ�");
		if (IsDlgButtonChecked(IDC_CHECK_AUTOREPLY) == TRUE) {
			GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(TRUE);
		} else {
			GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(FALSE);
		}
    } else {
        SetDlgItemText(IDC_STATIC_LINES, "��");
		if (s_PDlgAutoRply->IsWindowVisible() == TRUE) {
			s_PDlgAutoRply->ShowHideDlgWindow(FALSE);
		}
    }
}

/**************************************************************************************************
**  ��������:  OnCheckAutoClear
**  ��������:  �Զ�������ܸ�ѡ��״̬�л�
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
    
    if (TempData < 100) {        
        MessageBox("�����õ�����ֵ��С��ϵͳ������ʹ�á�������һ������100��ֵ��     ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        SetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                          /* ��ԭ�༭������ */
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
**  ��������:  OnCheckAutoSave
**  ��������:  �Զ����湦�ܸ�ѡ��״̬�л�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoSave()
{
    m_Check_AutoSave = !m_Check_AutoSave;
}

/**************************************************************************************************
**  ��������:  OnCheckHexSend
**  ��������:  ����16�������ݸ�ѡ��״̬�л�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckHexSend()
{
    m_Check_HexSend = !m_Check_HexSend;
	
	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);                                /* ���ȱ��浱ǰ���ݣ�Ȼ�������ʾ */

	if (m_Check_HexSend == FALSE) {                                            /* ֮ǰ��16����ģʽ�����������ַ�ģʽ */
		s_SendStr_Hex = m_Edit_Send;
		SetDlgItemText(IDC_EDIT_SEND, s_SendStr_Chr);
	} else {                                                                   /* ֮ǰ���ַ�ģʽ����������16����ģʽ */
		s_SendStr_Chr = m_Edit_Send;
		SetDlgItemText(IDC_EDIT_SEND, s_SendStr_Hex);
	}
	
	UpdateData(TRUE);
}

/**************************************************************************************************
**  ��������:  OnCheckAutoSend
**  ��������:  �Զ����͹��ܸ�ѡ��״̬�л�
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
		GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(FALSE);

    } else {

        KillTimer(Timer_No_AutoSend);                                          /* �����û�ȡ�����Զ����͵Ĺ��� */
        GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);                       /* �������÷��Ͱ�ť */
		GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(TRUE);
    }
}

/**************************************************************************************************
**  ��������:  OnCheckAddReturn
**  ��������:  ����ʱ���ӻس�����ѡ��״̬�л�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAddReturn()
{
    m_Check_Return = !m_Check_Return;
}

/**************************************************************************************************
**  ��������:  OnCheckShowTime
**  ��������:  ��ͷλ����ʾʱ�临ѡ��״̬�л�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckShowTime()
{
    m_Check_ShowTime = !m_Check_ShowTime;
}

/**************************************************************************************************
**  ��������:  OnCheckFrameDspl
**  ��������:  ֡��ʽ��ʾ�Զ����й��ܸ�ѡ��״̬�л�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckFrameDspl() 
{
	m_Check_FrameDspl = !m_Check_FrameDspl;
}

/**************************************************************************************************
**  ��������:  OnCheckAutoReply
**  ��������:  �Զ��ظ���ѡ��״̬�л�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoReply()
{
	m_Check_AutoReply = !m_Check_AutoReply;

	GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(m_Check_AutoReply);

	if (m_Check_AutoReply == FALSE) {
		if (s_PDlgAutoRply->IsWindowVisible() == TRUE) {                         /* ������δ�ر� */
			s_PDlgAutoRply->ShowHideDlgWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  ��������:  OnCheckDsplFilt
**  ��������:  ��ʾ���ݹ��˸�ѡ��״̬�л�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckDsplFilt()
{
	m_Check_Filter = !m_Check_Filter;

	GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(m_Check_Filter);

	if (m_Check_Filter == FALSE) {
		if (s_PDlgDsplFilt->IsWindowVisible() == TRUE) {                       /* ������δ�ر� */
			s_PDlgDsplFilt->ShowHideDlgWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  ��������:  OnMenuEditCopy
**  ��������:  �༭��˵� - ������ѡ����
**  �������:  
**  ���ز���:  
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
**  ��������:  OnMenuEditClear
**  ��������:  �༭��˵� - ���ȫ������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditClear()
{
	if (MessageBox("ȷ��Ҫ�������յ���ȫ��������գ�", "��ʾ", MB_OKCANCEL + MB_ICONQUESTION) != IDOK) {
		return;
	}
	
	OnButtonClearAll();
}

/**************************************************************************************************
**  ��������:  OnMenuEditFont
**  ��������:  �༭��˵� - ��ʾ��������
**  �������:  
**  ���ز���:  
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

	//��������
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
**  ��������:  OnMenuEditAbout
**  ��������:  �༭��˵� - �������˵��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditAbout()
{
	CDialogAboutMe Dlgabout;

	Dlgabout.DoModal();
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorWhite
**  ��������:  �༭��˵� - ������ɫ���� - ѩ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorWhite()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_WHITE);
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorGray
**  ��������:  �༭��˵� - ������ɫ���� - �Ƽ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorGray()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_GRAY);
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorGreen
**  ��������:  �༭��˵� - ������ɫ���� - ������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorGreen()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_GREEN);
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorBlue
**  ��������:  �༭��˵� - ������ɫ���� - �̿���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorBlue()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_BLUE);
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorPink
**  ��������:  �༭��˵� - ������ɫ���� - ������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorPink()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_PINK);
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorPurple
**  ��������:  �༭��˵� - ������ɫ���� - ��ɴ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorPurple()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_PURPLE);
}

/**************************************************************************************************
**  ��������:  OnMenuTrayAbout
**  ��������:  ���̲˵� - ���ڳ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayAbout()
{
    CDialogAboutMe Dlgabout;
    
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
    CloseAllChildWin();                                                        /* �رո����Ӵ��� */
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
    CloseAllChildWin();                                                        /* �رո����Ӵ��� */
	
	RecordAllParas();                                                          /* ��������������� */

	s_PDlgSuprSend->RecordAllParas();
	s_PDlgExtrfunc->RecordAllParas();
	s_PDlgDsplFilt->RecordAllParas();
	s_PDlgAutoRply->RecordAllParas();

	CloseSerialDevice();                                                       /* �رմ����豸 */
    
    TaskBarDeleteIcon(GetSafeHwnd(), IDR_MAINFRAME);                           /* ɾ����������ͼ�� */
    
    ::PostQuitMessage(0);                                                      /* �����˳���Ψһ��ʽ */
}


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

	s_RecvPaused = FALSE;
	s_RecvString = "";
	s_LopSendCnt = 0;
	s_RecvedLine = 0;
	s_RecvedByte = 0;
	s_SendedByte = 0;
	s_FileDatPos = 0;

	CreateDirectory(RecordPath, NULL);                                         /* ����Record�ļ��У����ڱ������� */
	CreateSettingFile();                                                       /* �����������ò����ļ�����ʼ���������� */

	if (InitiateChildWins() == FALSE) {                                        /* ���������Ӵ����ҳ�� */
		return FALSE;
	}
	
	GetDlgItem(IDC_PROGRESS_SENDFILE)->ShowWindow(SW_HIDE);                    /* ���ؽ�����������ʼ������ */
	m_Progress_SendFile.SetRange(0, PROGRESS_POS);
	m_Progress_SendFile.SetPos(0);

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    s_Edit_Recv = (CEdit*)GetDlgItem(IDC_EDIT_RECV);
    s_Edit_Send = (CEdit*)GetDlgItem(IDC_EDIT_SEND);

    InitiateStatusBar();                                                       /* ��ʼ��״̬����������λ�� */
    InitiateComboComs();                                                       /* ��ʼ��ѡ�񴮿ںŵ��б�� */
    InitiateComboBaud();                                                       /* ��ʼ��ѡ�����ʵ��б�� */
    InitiateComboData();                                                       /* ��ʼ��ѡ������λ���б�� */
    InitiateComboCheck();                                                      /* ��ʼ��ѡ��У��λ���б�� */
    InitiateComboStop();                                                       /* ��ʼ��ѡ��ֹͣλ���б�� */
	InitiateAllParas();                                                        /* ��ʼ���������¸��ؼ����� */
	InitiateToolsTip();                                                        /* ��ʼ���ؼ���������ʾ��Ϣ */

    SetControlStatus(FALSE);                                                   /* ���Ƚ��ø�����ť�ؼ� */

    SetTimer(Timer_No_UpdateDsp, UPDATEEDIT_TIME, NULL);
    SetTimer(Timer_No_StatusBar, STATUSBAR_TIME, NULL);

    INIT_EASYSIZE;                                                             /* ��ʼ�������ؼ���λ�� */

	if (CreateDeviceThread() == FALSE) {                                       /* ����̴߳���ʧ�� */
        MessageBox("�����豸�����̴߳���ʧ�ܣ�����������", "��ʾ", MB_OK + MB_ICONERROR);
        return FALSE;
    }

	s_PDlgSuprSend->InitateSrDlgPos();                                         /* ��仰һ��Ҫ��������� */
	
    TaskBarAddIcon(GetSafeHwnd(), IDR_MAINFRAME, AfxGetApp()->LoadIcon(IDR_MAINFRAME), "MySScom");

	CRect rect;                                                                /* ��ʼ��������λ�ã������Ƹ߶ȺͿ�� */
	GetWindowRect(&rect);
	SetWindowPos(NULL, s_DialogPos_X, s_DialogPos_Y, MIN_WIN_WIDTH, MIN_WIN_HIGHT, SWP_NOSIZE);

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
    unsigned char buff[MAX_SEND_BYTE];
	
	switch (nIDEvent)
    {
        case Timer_No_UpdateDsp:                                              /* ���±༭��������ʾ */
            if (s_DataRecved == TRUE) {
                UpdateEditDisplay();
                s_DataRecved = FALSE;
            }
            break;
        
        case Timer_No_StatusBar:                                               /* ״̬����ʱ���� */
            UpdateStatusBarNow();
            break;
            
        case Timer_No_AutoSend:                                                /* �Զ��������� */
            GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
			strncpy_s((char *)&buff[0], sizeof(buff), (LPCTSTR)m_Edit_Send, m_Edit_Send.GetLength());
			if (SendDatatoComm(buff, m_Edit_Send.GetLength(), m_Check_HexSend) == FALSE) {
				OnCheckAutoSend();
				UpdateData(FALSE);
				MessageBox("�����������֡���ݹ��������ߴ��ڷǷ��ַ�����ȷ�ϣ�......       ", "����", MB_OK + MB_ICONEXCLAMATION);
			}
            break;
            
		case Timer_No_FrameDspl:                                               /* 16�����°�֡������ʾ�ж� */
			KillTimer(Timer_No_FrameDspl);
			s_RecvedLine++;
			UpdateEditStr("\r\n");                                             /* ����������ʾ */
			s_NeedChgLne = TRUE;                                               /* ��־�´���Ҫ������ʾ */
			break;
			
		case Timer_No_SendFile:                                                /* �����ļ����� */
			if (SendFileDatatoComm() == FALSE) {                               /* ���η�������ʧ�� */
				s_FileDatPos = 0;
				KillTimer(Timer_No_SendFile);                                  /* ֹͣ���� */
				SetSendCtrlArea(TRUE);                                         /* �ָ��������Ϳؼ� */
			}
			UpdateStatusBarNow();
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

        if ((pMsg->wParam == VK_ESCAPE) || (pMsg->wParam == VK_RETURN)) {      /* ���ؼ���ȷ�ϼ���Ҫ����Ԥ���� */
            return true;
        }
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
    if ((m_Check_AutoSend == TRUE) || (s_PDlgSuprSend->s_issenddata == TRUE)) {
		MessageBox("������ͣ���Զ����͹����ٳ��Թرձ�����...  ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
    }
	
	CloseAllChildWin();                                                        /* �ر������Ӵ��� */
	
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

	UpdateStatusBarNow();

    EASYSIZE_MINSIZE(MIN_WIN_WIDTH, MIN_WIN_HIGHT, fwSide, pRect);             /* ���ƴ������С�ߴ� */
}

/**************************************************************************************************
**  ��������:  OnContextMenu
**  ��������:  ���������Ĳ˵���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu popMenu, *pPopup;
	
	if (pWnd->m_hWnd == m_RichEdit_Recv.m_hWnd) {                              /* ����ڱ༭�����һ� */

		popMenu.LoadMenu(IDR_MENU_EDIT);                                       /* ����˵� */
		pPopup = popMenu.GetSubMenu(0);                                        /* ��ò˵�ָ�� */

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		pPopup->Detach();
		popMenu.DestroyMenu();
	}
}

/**************************************************************************************************
**  ��������:  OnSysCommand
**  ��������:  ����ϵͳ��Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_MINIMIZE) {                                                  /* �����Ҫ������С�� */
		CloseAllChildWin();                                                    /* �ر������Ӵ��� */
	}

	CDialog::OnSysCommand(nID, lParam);
}


