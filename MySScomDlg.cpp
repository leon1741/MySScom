#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "version")

static const int    Combo_Baud[12] = {600,  1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
static const int    Combo_Data[4]  = {5,    6,    7,    8};
static const double Combo_Stop[4]  = {1,    1.5,  2};
static const int    Combo_Check[5] = {0,    1,    2,    3,   4};


CMySScomDlg::CMySScomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySScomDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	AfxInitRichEdit();                                                         /* ��ʼ��RichEdit�ؼ� */
}

void CMySScomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_SENDFILE, m_Progs_SendFile);
	DDX_Control(pDX, IDC_COMBO_COMMPORT, m_Combo_CommPort);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_Combo_BaudRate);
	DDX_Control(pDX, IDC_COMBO_DATABITS, m_Combo_DataBits);
	DDX_Control(pDX, IDC_COMBO_CHECKBIT, m_Combo_CheckBit);
	DDX_Control(pDX, IDC_COMBO_STOPBITS, m_Combo_StopBits);

	DDX_Check(pDX, IDC_CHECK_SHOWTIME, m_Check_ShowTime);
	DDX_Check(pDX, IDC_CHECK_HEXDISPL, m_Check_HexDispl);
	DDX_Check(pDX, IDC_CHECK_HEXFRAME, m_Check_HexFrame);
	DDX_Check(pDX, IDC_CHECK_PROTOACK, m_Check_ProtoACK);
	DDX_Check(pDX, IDC_CHECK_AUTOCLER, m_Check_AutoCler);
	DDX_Check(pDX, IDC_CHECK_AUTOSAVE, m_Check_AutoSave);
	DDX_Check(pDX, IDC_CHECK_AUTOFILT, m_Check_AutoFilt);
	DDX_Check(pDX, IDC_CHECK_KEYWORDS, m_Check_Keywords);
	DDX_Check(pDX, IDC_CHECK_HEXSSEND, m_Check_HexsSend);
	DDX_Check(pDX, IDC_CHECK_CRLFSEND, m_Check_CRLFSend);
	DDX_Check(pDX, IDC_CHECK_AUTOSEND, m_Check_AutoSend);
	
	DDX_Text(pDX, IDC_EDIT_RECVCSTR, m_Edit_RecvCstr);
	DDX_Text(pDX, IDC_EDIT_SENDCSTR, m_Edit_SendCstr);

	DDX_Text(pDX, IDC_EDIT_SENDTIME, m_Edit_SendTime);
	DDV_MaxChars(pDX, m_Edit_SendTime, 5);

	DDX_Text(pDX, IDC_EDIT_AUTCLRKB, m_Edit_AutClrKB);
	DDV_MaxChars(pDX, m_Edit_AutClrKB, 5);

	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_Edit_FilePath);

	DDX_Control(pDX, IDC_EDIT_RECVCSTR, m_RichEdit_Recv);
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
	ON_BN_CLICKED(IDC_BUTTON_KEYWORD, OnButtonConfigKeywords)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, OnButtonOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_SENDFILE, OnButtonSendFile)
	ON_BN_CLICKED(IDC_BUTTON_SETFILTER, OnButtonConfigDsplFilt)
	ON_BN_CLICKED(IDC_BUTTON_SETREPLY, OnButtonConfigAutoReply)

	ON_BN_CLICKED(IDC_CHECK_HEXDISPL, OnCheckHexDisplay)
	ON_BN_CLICKED(IDC_CHECK_AUTOSAVE, OnCheckAutoSave)
	ON_BN_CLICKED(IDC_CHECK_HEXSSEND, OnCheckHexSend)
	ON_BN_CLICKED(IDC_CHECK_AUTOSEND, OnCheckAutoSend)
	ON_BN_CLICKED(IDC_CHECK_CRLFSEND, OnCheckAddReturn)
	ON_BN_CLICKED(IDC_CHECK_SHOWTIME, OnCheckShowTime)
	ON_BN_CLICKED(IDC_CHECK_AUTOCLER, OnCheckAutoClear)
	ON_BN_CLICKED(IDC_CHECK_HEXFRAME, OnCheckFrameDspl)
	ON_BN_CLICKED(IDC_CHECK_AUTOFILT, OnCheckDsplFilt)
	ON_BN_CLICKED(IDC_CHECK_PROTOACK, OnCheckAutoReply)
	ON_BN_CLICKED(IDC_CHECK_KEYWORDS, OnCheckKeyword)
	
	ON_MESSAGE(WM_USERMSG_NOTIFYICON, OnUsrMsgHdlIconNotify)
	ON_MESSAGE(WM_USERMSG_COMDEVLIST, OnUsrMsgHdlComDevList)
	ON_MESSAGE(WM_USERMSG_COMDEVWAIT, OnUsrMsgHdlComDevWait)
	ON_MESSAGE(WM_USERMSG_DATARECVED, OnUsrMsgHdlDataRecved)
	ON_MESSAGE(WM_USERMSG_DATATOSEND, OnUsrMsgHdlDatatoSend)
	ON_MESSAGE(WM_USERMSG_ARDLGCLOSE, OnUsrMsgHdlARDlgClose)
	ON_MESSAGE(WM_USERMSG_DFDLGCLOSE, OnUsrMsgHdlDFDlgClose)
	ON_MESSAGE(WM_USERMSG_EFDLGCLOSE, OnUsrMsgHdlEFDlgClose)
	ON_MESSAGE(WM_USERMSG_SSDLGCLOSE, OnUsrMsgHdlSSDlgClose)
	ON_MESSAGE(WM_USERMSG_KWDLGCLOSE, OnUsrMsgHdlKWDlgClose)

	ON_WM_SYSCOMMAND()
	ON_WM_CONTEXTMENU()
	ON_EN_CHANGE(IDC_EDIT_SENDCSTR, &CMySScomDlg::OnChangeEditSendcstr)
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
	EASYSIZE(IDC_EDIT_RECVCSTR,     ES_BORDER,           ES_BORDER,          ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_EDIT_SENDCSTR,     ES_BORDER,           ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_PROGRESS_SENDFILE, ES_BORDER,           ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_BUTTON_SEND,       ES_KEEPSIZE,         ES_KEEPSIZE,        ES_BORDER,          IDC_STATIC_SEND,  0)
	EASYSIZE(IDC_EDIT_FILEPATH,     ES_BORDER,           ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,        0)
	EASYSIZE(IDC_BUTTON_OPENFILE,   ES_KEEPSIZE,         ES_KEEPSIZE,        ES_BORDER,          IDC_STATIC_SEND,  0)
	EASYSIZE(IDC_BUTTON_SENDFILE,   ES_KEEPSIZE,         ES_KEEPSIZE,        ES_BORDER,          IDC_STATIC_SEND,  0)
END_EASYSIZE_MAP


/**************************************************************************************************
**  ��������:  EnumCommPortList
**  ��������:  ����������ö�ٵ����ϴ��ڿ��õĴ���
**************************************************************************************************/
BOOL CMySScomDlg::EnumCommPortList(void)
{
	HKEY    hSERIALCOMM;
	BOOL    bSuccess = FALSE;
	CString comstr;
	bool    newone;
	
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

						newone = TRUE;

						for (int i = 0; i < s_PortNumber.GetSize(); i++) {     /* ��λ��������޳�����һ�����ظ��� */
							comstr = s_PortNumber.GetAt(i);
							if (comstr == szPort) {
								newone = FALSE;
							}
						}
						if (newone == TRUE) {
							s_PortNumber.Add(szPort);
						}
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
**************************************************************************************************/
void CMySScomDlg::SetControlStatus(bool Enable)
{
    GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(Enable);
    GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_OPENFILE)->EnableWindow(Enable);
    GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_HEXDISPL)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_AUTOCLER)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(Enable);
    GetDlgItem(IDC_CHECK_HEXSSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_SHOWTIME)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_AUTOFILT)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_KEYWORDS)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_KEYWORD)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_OVER)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_LINES)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_AUTCLRKB)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_SENDTIME)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_CRLFSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(Enable);

    if ((IsDlgButtonChecked(IDC_CHECK_AUTOCLER) == FALSE) || (Enable == FALSE)) {
        GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_HEXFRAME)->EnableWindow(FALSE);
    } else {
        GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_HEXFRAME)->EnableWindow(TRUE);
    }

	if (IsDlgButtonChecked(IDC_CHECK_HEXDISPL) == FALSE) {
		GetDlgItem(IDC_CHECK_HEXFRAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_PROTOACK)->EnableWindow(FALSE);
	} else {
		GetDlgItem(IDC_CHECK_HEXFRAME)->EnableWindow(Enable);
		GetDlgItem(IDC_CHECK_PROTOACK)->EnableWindow(Enable);
	}

	if (Enable == TRUE) {
		if (IsDlgButtonChecked(IDC_CHECK_PROTOACK) == TRUE) {
			GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(TRUE);
		} else {
			GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(FALSE);
		}

		if (IsDlgButtonChecked(IDC_CHECK_AUTOFILT) == TRUE) {
			GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(TRUE);
		} else {
			GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(FALSE);
		}

		if (IsDlgButtonChecked(IDC_CHECK_KEYWORDS) == TRUE) {
			GetDlgItem(IDC_BUTTON_KEYWORD)->EnableWindow(TRUE);
		} else {
			GetDlgItem(IDC_BUTTON_KEYWORD)->EnableWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  ��������:  SetSendCtrlArea
**  ��������:  �ڷ����ļ���ʱ�����ø�����������״̬
**************************************************************************************************/
void CMySScomDlg::SetSendCtrlArea(bool Enable)
{
	GetDlgItem(IDC_CHECK_HEXSSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_SENDTIME)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_CHECK_CRLFSEND)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_FILEPATH)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_OPENFILE)->EnableWindow(Enable);
	SetDlgItemText(IDC_BUTTON_SENDFILE, (Enable == TRUE) ? "��ʼ����" : "ֹͣ����");
	GetDlgItem(IDC_EDIT_SENDCSTR)->ShowWindow((Enable == TRUE) ? SW_SHOW : SW_HIDE);
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
**  ��������:  ������´��ں������б����ݵ���Ϣ �������豸�����̼߳����������豸�����仯ʱ�����ͱ���Ϣ��������֪ͨ������ˢ���б���ʾ��
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlComDevList(WPARAM wParam, LPARAM lParam)
{
	UpdateComboComs();
	
	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlComDevWait
**  ��������:  �����Ժ���´����豸�б����Ϣ �������豸�����̼߳����������豸�����仯ʱ�����ͱ���Ϣ��������֪ͨ���Ժ�ˢ���б���ʾ��
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlComDevWait(WPARAM wParam, LPARAM lParam)
{
	s_DevNeedUpd = TRUE;

	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlDataRecved
**  ��������:  ������յ��˴������ݵ���Ϣ ���������ݼ����߳��յ���������ʱ�����ͱ���Ϣ��������������ݽ�������
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
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlARDlgClose(WPARAM wParam, LPARAM lParam)
{
	//GetDlgItem(IDC_BUTTON_EXFUNCT)->EnableWindow(TRUE);

	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlDFDlgClose
**  ��������:  ������ʾ���˴��ڹرյ���Ϣ
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlDFDlgClose(WPARAM wParam, LPARAM lParam)
{
	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlKWDlgClose
**  ��������:  ����ؼ���ƥ�䴰�ڹرյ���Ϣ
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlKWDlgClose(WPARAM wParam, LPARAM lParam)
{
	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlEFDlgClose
**  ��������:  �����ӹ��ܴ��ڹرյ���Ϣ
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlEFDlgClose(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_BUTTON_EXFUNCT)->EnableWindow(TRUE);

	return true;
}

/**************************************************************************************************
**  ��������:  OnUsrMsgHdlSSDlgClose
**  ��������:  ����߼����ʹ��ڹرյ���Ϣ
**************************************************************************************************/
LRESULT CMySScomDlg::OnUsrMsgHdlSSDlgClose(WPARAM wParam, LPARAM lParam)
{
	SetDlgItemText(IDC_BUTTON_SRSEND, "�߼�����");
	GetDlgItem(IDC_CHECK_HEXSSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SENDTIME)->EnableWindow(TRUE);
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
**  ��������:  ShowAboutMeDialog
**  ��������:  ��ʾ�����ҵĶԻ���
**************************************************************************************************/
void CMySScomDlg::ShowAboutMeDialog(void)
{
	ShellExecute(NULL, _T("open"), "https://gitee.com/leon1741/MySScom/blob/main/README.md", NULL, NULL, SW_SHOW);
}

/**************************************************************************************************
**  ��������:  KeyWordMatchOK
**  ��������:  �ؼ���ƥ��ɹ�
**************************************************************************************************/
bool CMySScomDlg::KeyWordMatchOK(CString showstr)
{
	CString  tempstr;
	
	for (int i = 1; i < s_PDlgKeyWords->GetKeywordMax(); i++) {                /* �����������ؼ����Ƿ�ƥ��ɹ� */
		tempstr = s_PDlgKeyWords->GetKeywordX(i);
		if ((tempstr != "") && (tempstr.GetLength() > 0)) {
			if (showstr.Find(tempstr, 0) != -1) {
				s_PDlgKeyWords->AddNewMatchRec(i);                             /* ��ƥ����֪ͨ����ҳ����д��� */
				return TRUE;
			}
		}
	}

	return FALSE;
}

/**************************************************************************************************
**  ��������:  ShakeMainWindow
**  ��������:  ��������
**************************************************************************************************/
void CMySScomDlg::ShakeMainWindow(void)
{
	CRect rect;  
	int m_move = SHAKE_DISTANCE;

	GetWindowRect(&rect);  

	for (int i = 1; i < 11; i++)  {                                            /* Ϊ��ʹ���ڶ������ܻص�ԭ����λ�ã���������i����Ϊ5�ı�������i<5*n+1 */
		rect.OffsetRect(0, m_move);                                            /* OffsetRect������ָ���ľ����ƶ���ָ����λ��,�����ǽ����������ƶ�10���� */
		MoveWindow(&rect);  
		Sleep(40);
		rect.OffsetRect(m_move,0);
		MoveWindow(&rect);
		Sleep(40);
		m_move = (m_move == SHAKE_DISTANCE) ? (-SHAKE_DISTANCE) : SHAKE_DISTANCE;
	}
}

/**************************************************************************************************
**  ��������:  AttractAttention
**  ��������:  �����û���ע��
**************************************************************************************************/
void CMySScomDlg::AttractAttention(void)
{
	FlashWindowEx(FLASHW_ALL | FLASHW_TIMERNOFG, 10, 0);

	if (IsIconic() == TRUE) {                                                  /* ��������Ѿ���С�������������ʾ */
		ShowWindow(SW_SHOWMAXIMIZED);
	} else {                                                                   /* ���򣬽��䰴ԭ����״̬��ʾ�������� */
		ShowWindow(SW_SHOW);
	}

	ShakeMainWindow();

	if (s_PDlgKeyWords->IsWindowVisible() == FALSE) {
		s_PDlgKeyWords->ShowHideDlgWindow(TRUE);                               /* �������壬����չʾƥ���� */
	}
}

/**************************************************************************************************
**  ��������:  CloseAllChildWin
**  ��������:  �ر������Ӵ���
**************************************************************************************************/
void CMySScomDlg::CloseAllChildWin(void)
{
	s_PDlgSuprSend->ShowHideDlgWindow(FALSE);                                  /* �رո߼����ʹ��� */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_SSDLGCLOSE, 0, 0); 

	s_PDlgExtrfunc->ShowHideDlgWindow(FALSE);                                  /* �رո��ӹ��ܴ��� */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_EFDLGCLOSE, 0, 0);   

	s_PDlgDsplFilt->ShowHideDlgWindow(FALSE);                                  /* �رչ������ô��� */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_DFDLGCLOSE, 0, 0);

	s_PDlgKeyWords->ShowHideDlgWindow(FALSE);                                  /* �رչؼ��ַ����� */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_KWDLGCLOSE, 0, 0);

	s_PDlgAutoRply->ShowHideDlgWindow(FALSE);                                  /* �ر��Զ��ظ����� */
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_ARDLGCLOSE, 0, 0);
}

/**************************************************************************************************
**  ��������:  UserFnKeyHdl
**  ��������:  �û��Զ���Fn���ܼ���Ϣ����
**************************************************************************************************/
bool CMySScomDlg::UserFnKeyHdl(WPARAM key)
{
	unsigned char dirbuf[512];
	CString       pathstr;
	
	if (key == VK_F1) {                                                        /* ����F1��������ϵͳ�����ĶԻ��� */
		ShowAboutMeDialog();
		return true;
	}

	if (key == VK_F2) {                                                        /* ����F2�����Զ���ϵͳ�����ļ���Ŀ¼ */
		GetCurrentDirectory(512, (LPSTR)dirbuf);
		pathstr = dirbuf;
		pathstr = pathstr + "\\" + REC_DIR_PATH;
		ShellExecute(NULL, "open", pathstr, NULL, NULL, SW_SHOWNORMAL);
		return true;
	}

	if (key == VK_F5) {                                                        /* ����F5����������ݴ��ڵ�ȫ������ */
		OnButtonClearAll();
		return true;
	}

	if (key == VK_F8) {                                                        /* ����F8������ʼ�����ļ��������� */
		if (SerialDevisOpened() == TRUE) {
			OnButtonSendFile();
		} else {
			MessageBox("���ڶ�û�򿪣������Ұ��ļ������﷢�ͣ�", "��ʾ", MB_OK + MB_ICONERROR);
		}
		return true;
	}

	if (key == VK_F12) {                                                       /* ����F12�����������ݴ��ڵ�ȫ������ */
		OnButtonSaveFile();
		return true;
	}

	MessageBox("���ȼ��Ĺ�����δ����......\r\n�����Ƿ��кܺõĽ��飿��ӭ��ʱ��ı���ߣ�", "��ʾ", MB_OK + MB_ICONINFORMATION);
	return false;
}

/**************************************************************************************************
**  ��������:  GetHighExactTime
**  ��������:  ��ȡ��ȷ��ʱ��
**************************************************************************************************/
CString CMySScomDlg::GetHighExactTime(void)
{
	CString       timestr;
	LARGE_INTEGER litmp;
	CTime         NowTime;
	LONGLONG      NowTick;
	double        difFreq, difTime;

	QueryPerformanceFrequency(&litmp);
	difFreq = (double)litmp.QuadPart;                                          /* ��ü�������ʱ��Ƶ�� */

	QueryPerformanceCounter(&litmp);
	NowTick = litmp.QuadPart;                                                  /* �����ֵֹ */

	difTime = (1000 * ((double)(NowTick - s_StartdTcik))) / difFreq;           /* ��ö�Ӧ��ʱ��ֵ����λΪms */

	NowTime = CTime::GetCurrentTime();
	timestr.Format("[%.2d:%.2d:%.2d:%.3d] ", NowTime.GetHour(), NowTime.GetMinute(), NowTime.GetSecond(), ((int)difTime % 1000));

	return timestr;
}

/**************************************************************************************************
**  ��������:  SaveEditContent
**  ��������:  ����༭������ݵ��ı��ļ�
**************************************************************************************************/
bool CMySScomDlg::SaveEditContent(void)
{
    CFile   MyFile;                                                            /* �����ļ��� */
	CString CommStr, FileName;
	int     ComNumber;
    CTime   NowTime  = CTime::GetCurrentTime();                                /* ��ȡ����ʱ�� */

	ComNumber = m_Combo_CommPort.GetCurSel();
	m_Combo_CommPort.GetLBText(ComNumber, CommStr);

	FileName = "All_Rec_" + CommStr + NowTime.Format("_%y-%m-%d_%H-%M-%S") + ".txt";
    
    GetDlgItemText(IDC_EDIT_RECVCSTR, m_Edit_RecvCstr);
	
	if (MyFile.Open(REC_DIR_PATH + FileName, CFile::modeCreate | CFile::modeReadWrite)) {
        MyFile.Write(m_Edit_RecvCstr, m_Edit_RecvCstr.GetLength());            /* д���ı��ļ� */
        MyFile.Close();                                                        /* �ر��ļ� */
		return TRUE;
    } else {
		return FALSE;
	}
}

/**************************************************************************************************
**  ��������:  ExcuteAutoReply
**  ��������:  ����Э�����ݵ��Զ��ظ�
**************************************************************************************************/
void CMySScomDlg::ExcuteAutoReply(CString instr)
{
	CString TempStr;
	unsigned char sbuf[MAX_SEND_BYTE];

	for (int i = 0; i < s_PDlgAutoRply->GetTotalStringNo(); i++) {
		TempStr = s_PDlgAutoRply->GetRecvString(i);
		if ((TempStr.GetLength() > 0) && (instr.Find(TempStr, 0) != -1)) {
			TempStr = s_PDlgAutoRply->GetSendString(i);
			if (TempStr.GetLength() > 0) {
				strncpy_s((char *)&sbuf[0], sizeof(sbuf), (LPCTSTR)TempStr, TempStr.GetLength());
				SendDatatoComm(sbuf, TempStr.GetLength(), TRUE);
			}
		}
	}
}

/**************************************************************************************************
**  ��������:  UpdateEditStr
**  ��������:  �����²��ֵ��ַ���ʾ����
**************************************************************************************************/
void CMySScomDlg::UpdateEditStr(CString showstr)
{
    /* �����������ʾ���˹��ܣ�������ַ���ƥ�䣬����Ҫ��ʾ���ַ������ݲ�����ʾ��ֻ�Ǹ���һ��״̬����ͳ����Ϣ */
	if ((m_Check_AutoFilt == TRUE) && (s_PDlgDsplFilt->StringCanDisplay(showstr) == FALSE)) {
		UpdateStatusBarNow();
		return;
	}

	/* ��������˹ؼ����Զ�ƥ��Ĺ��ܣ�������ַ���ƥ�䡣ƥ��ɹ�ʱ���Զ����д��嶶���������Ի�����ʾ���������û���ע�� */
	if ((m_Check_Keywords == TRUE) && (KeyWordMatchOK(showstr) == TRUE)) {
		AttractAttention();
	}

	/* �����16������ʾģʽ�£�ͬʱ�������Զ��ظ��Ĺ��ܡ����жϽ��յ����ַ����Ƿ��������������ֶΣ��������Զ��ظ� */
	if ((m_Check_HexDispl == TRUE) && (m_Check_ProtoACK == TRUE)) {
		ExcuteAutoReply(showstr);
	}

	#if 1                                                                      /* �������ַ����ᵼ������������� */
	{
		s_Edit_Recv->SetSel(-1, -1);                                           /* ��ӱ��ε�������ʾ */
		s_Edit_Recv->ReplaceSel((LPCTSTR)showstr);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);                    /* �ñ༭�����ݹ��������һ�� */
	}
	#else                                                                      /* �������ַ����ᵼ��CPUռ���ʹ��ߡ��� */
	{
		m_Edit_RecvCstr += showstr;                                            /* ��ӱ��ε�������ʾ */
		SetDlgItemText(IDC_EDIT_RECVCSTR, m_Edit_RecvCstr);
        s_Edit_Recv->SetSel(-1, -1);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);                    /* �ñ༭�����ݹ��������һ�� */
	}
	#endif

	if (showstr.Right(1) == "\n") {                                            /* ������յ��˻س��� */
		if (m_Check_AutoCler == TRUE) {                                        /* �����Ҫ�Զ�������� */
			GetDlgItemText(IDC_EDIT_AUTCLRKB, m_Edit_AutClrKB);                /* ��ȡ���ݲ����� */
			if (s_RecvedByte >= (atoi((LPSTR)(LPCTSTR)m_Edit_AutClrKB) * 1024)) {        /* �ж��Ƿ������������*/
				if (m_Check_AutoSave == TRUE) {                                /* �����Ҫ�Զ����� */
					SaveEditContent();                                         /* ����༭������� */
				}
				s_RecvedByte = 0;
				m_Edit_RecvCstr = "";
				SetDlgItemText(IDC_EDIT_RECVCSTR, m_Edit_RecvCstr);            /* ��ձ༭������ */
			}
		}
	}

	UpdateStatusBarNow();                                                      /* ����״̬��ͳ�����ݵ���ʾ */
}

/**************************************************************************************************
**  ��������:  HandleUSARTData
**  ��������:  ���մ�������
**************************************************************************************************/
void CMySScomDlg::HandleUSARTData(unsigned char *sbuf, DWORD len)
{
    DWORD   i;
    CString ShowStr, TempStr, TimeStr;

	TempStr = "";
	ShowStr = "";

	if (s_RecvPaused == TRUE) return;                                          /* ��ͣ����ʱ�������д��� */

    for (i = 0; i < len; i++) {                                                /* ������ת��ΪCstring�ͱ��� */

		if (m_Check_HexDispl == TRUE) {                                        /* ��ǰ����16������ʾģʽ */

			/* ���ǵ�00�ַ��������ԣ���Ҫ�������ת����ܴ洢��ת��������£�00ת���FF 01��FFת���FF 02�������ַ���ת�� */

			if (sbuf[i] == 0) {                                                /* 00 ת��� FF 01 */
				TempStr.Format("%c%c", 0xFF, 0x01);
			} else if ((unsigned char)(sbuf[i]) == 0xFF) {                     /* FF ת��� FF 02 */
				TempStr.Format("%c%c", 0xFF, 0x02);
			} else {
				TempStr.Format("%c", sbuf[i]);
			}

			TempStr = TransformtoHex(TempStr);                                 /* ת�����Ϊ16������ʾ */

			if ((s_NeedChgLne == TRUE) && (m_Check_ShowTime == TRUE)) {        /* �����Ҫ������ʾ */
				ShowStr +=  GetHighExactTime() + TempStr; 
				s_NeedChgLne = FALSE;
			} else {
				ShowStr += TempStr; 
			}
			
			if (m_Check_HexFrame == TRUE) {                                    /* �����жϽ�����һ��ʱ�����Ƿ�û�����յ��������� */
				KillTimer(Timer_No_FrameDspl);                                 /* ��ʵ��16�����£���֡������ʾ�Ĺ��� */
				SetTimer(Timer_No_FrameDspl, CHNGLINE_INTERVAL, NULL);         /* ��������������ʱ���ж��Ƿ�û�����յ��������� */
			}
			
		} else {                                                               /* ��ǰ�����ַ���ʾģʽ */

			if (s_NeedChgLne == TRUE) {                                        /* ���������һ���� */

				if (m_Check_ShowTime == TRUE) {                                /* ���������ʱ����ʾ���� */
					ShowStr = ShowStr + GetHighExactTime();
				}
				
				s_NeedChgLne = FALSE;
			}

			TempStr.Format("%c", sbuf[i]);                                     /* ������յ������� */
			ShowStr += TempStr;                                                /* ������������ */

			if (TempStr == "\n") {                                             /* ���ν��յ��س��� */
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
**************************************************************************************************/
void CMySScomDlg::NeedAutoSendData(void)
{
    int Timer;
    CString TempStr;

    GetDlgItemText(IDC_EDIT_SENDTIME, TempStr);
    
    Timer = atoi((LPSTR)(LPCTSTR)TempStr);
    
    if (Timer > 0) {

        SetTimer(Timer_No_AutoSend, Timer, NULL);                              /* ������ʱ�� */

        GetDlgItem(IDC_EDIT_SENDTIME)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);

        m_Edit_SendTime = TempStr;                                             /* ���±༭������ */
        SetDlgItemText(IDC_EDIT_SENDTIME, m_Edit_SendTime);

        GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);                      /* ���÷��Ͱ�ť */
		GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(FALSE);

    } else {

        MessageBox("����ʱ��������Ϊ0����ȷ�ϣ�  ", "��ʾ", MB_OK + MB_ICONEXCLAMATION);

        SetDlgItemText(IDC_EDIT_SENDTIME, m_Edit_SendTime);                    /* ��ԭ�༭������ */

        m_Check_AutoSend = FALSE;
        UpdateData(FALSE);                                                    /* ȡ����ѡ��ѡ�е�״̬ */

        return;
    }
}

/**************************************************************************************************
**  ��������:  UpdateStatusBarNow
**  ��������:  ����״̬������ʾ
**************************************************************************************************/
void CMySScomDlg::UpdateStatusBarNow(void)
{
    CTime   Nowtime;
    CString TempStr, DisplayStr;
    CRect   DialogMain;

    this->GetWindowRect(&DialogMain);                                          /* ��ȡ����������Ļ�ϵ�λ�� */

#if VERSION_CTRL == VERSION_YAXON
	if (DialogMain.Width() > 1200) {
		DisplayStr = " ��ӭʹ��MySScom �� ��Ѹ���Լ��Ĵ��ڵ��Թ��� �� ����ߣ�Ҧ�� �� ��ӭ����޸�����ͽ���";
	} else if (DialogMain.Width() > 1100) {
		DisplayStr = " ��ӭʹ��MySScom �� ��Ѹ���Լ��Ĵ��ڵ��Թ��� �� ����ߣ�Ҧ��";
	} else if (DialogMain.Width() > 1000) {
		DisplayStr = " ��ӭʹ��MySScom �� ��Ѹ���Լ��Ĵ��ڵ��Թ���";
	} else if (DialogMain.Width() > 800) {
		DisplayStr = " ��ӭʹ��MySScom";
	} else if (DialogMain.Width() > 700) {
		DisplayStr = " ��ӭʹ��";
	} else {
		DisplayStr = "";
	}
#else
    if (DialogMain.Width() > 1200) {
        DisplayStr = " ��ӭʹ��MySScom �� Designed By LEON (LEON1741@126.com) �� Welcome to Email me!!";
    } else if (DialogMain.Width() > 1100) {
        DisplayStr = " ��ӭʹ��MySScom �� Designed By LEON (LEON1741@126.com)";
    } else if (DialogMain.Width() > 1000) {
        DisplayStr = " ��ӭʹ��MySScom �� Designed By LEON";
    } else if (DialogMain.Width() > 850) {
        DisplayStr = " ��ӭʹ��MySScom �� LEON";
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
        
	DisplayStr.Format(" ����: %.3d, %.3d, %.3d", (s_RecvedByte / 1000000), ((s_RecvedByte % 1000000)  / 1000), (s_RecvedByte % 1000));
    s_CStatusBar.SetPaneText(2, DisplayStr);

	DisplayStr.Format(" ����: %.3d, %.3d, %.3d", (s_SendedByte / 1000000), ((s_SendedByte % 1000000)  / 1000), (s_SendedByte % 1000));
    s_CStatusBar.SetPaneText(3, DisplayStr);

    Nowtime = CTime::GetCurrentTime();
    DisplayStr = " ��ǰʱ��: " + Nowtime.Format("%Y-%m-%d") + " " + Nowtime.Format("%H:%M:%S");
    s_CStatusBar.SetPaneText(4, DisplayStr);

	UpdateMainStatic();                                                        /* ������ʾ�����ʾ */
}

/**************************************************************************************************
**  ��������:  SendDatatoComm
**  ��������:  ��ָ�����ַ������ͳ�ȥ
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
	
    if (m_Check_CRLFSend == TRUE) {                                            /* �����س����з� */
		
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
**************************************************************************************************/
bool CMySScomDlg::SendFileDatatoComm(void)
{
	CFile          filename;
	int            baudrate, sendbyte;
	unsigned long  filetlen;
	unsigned char *filebuff;                                                   /* ���ڴ���ļ����� */
	double         tempbyte;
	CString        dsplystr;
	unsigned int   totltime, lefttime;

	if (filename.Open(m_Edit_FilePath, CFile::modeReadWrite | CFile::typeBinary) == 0) {
		MessageBox("��ȡ�ļ�ʧ�ܣ���ȷ��·����ȷ���ļ�δ���ڴ�״̬��    ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return FALSE;
	}

	filetlen = (unsigned long)filename.GetLength();                            /* ��ȡ�ļ����� */
	
	baudrate = m_Combo_BaudRate.GetCurSel();
	baudrate = Combo_Baud[baudrate];

	tempbyte = ((double)baudrate / FILESEND_BYTE) * 1.1;
	sendbyte = (int)tempbyte;

	if ((s_FileDatPos + sendbyte) > filetlen) {                                /* ������Ҫ�����һ�����������ж� */
		sendbyte = filetlen - s_FileDatPos;
	}
	
    filebuff = new unsigned char[sendbyte];                                    /* �����ڴ�ռ� */
	filename.Seek(s_FileDatPos, CFile::begin);                                 /* ��λ���ϴη��͵�λ�� */
    filename.Read(filebuff, sendbyte);                                         /* ��ȡ�ļ����� */

	sendbyte = SendSerialData(filebuff, sendbyte);                             /* �������ݣ���ͳ�Ƴ��� */
	s_FileDatPos += sendbyte;
	s_SendedByte += sendbyte;

	totltime = (filetlen * 10) / baudrate + 1;                                 /* ���㷢�������ļ��ĺ�ʱ */
	lefttime = (filetlen - s_FileDatPos) * 10 / baudrate + 1;                  /* ���㷢��ʣ�ಿ�ֵĺ�ʱ */

	m_Progs_SendFile.SetPos(s_FileDatPos * PROGRESS_POS / filetlen);           /* ���½�������ʾ */

	dsplystr.Format("��������Ԥ�ƺ�ʱ%0.2d��%0.2d�룬��ǰ����%0.2d%%��ʣ��%0.2d��%0.2d��", 
		            totltime / 60, totltime % 60, s_FileDatPos * 100 / filetlen, lefttime / 60, lefttime % 60);
	SetDlgItemText(IDC_STATIC_SEND, dsplystr);
	
	filename.Close();                                                          /* �ر��ļ� */
	delete []filebuff;                                                         /* �ͷſռ� */

	if (s_FileDatPos >= filetlen) {                                            /* ȫ�����ݷ������ */
		s_FileDatPos = 0;
		KillTimer(Timer_No_SendFile);
		SetSendCtrlArea(TRUE);                                                 /* �����������Ϳؼ� */
	}

	return TRUE;
}

/**************************************************************************************************
**  ��������:  ConfigFileCanUse
**  ��������:  ������ǰ�汾�ĳ����Ƿ��ܹ�����ʹ��Ŀ��汾�µ������ļ�
**************************************************************************************************/
bool CMySScomDlg::ConfigFileCanUse(CString target)
{
	return TRUE;
}

/**************************************************************************************************
**  ��������:  CreateSettingFile
**  ��������:  ���������ļ�����д��Ĭ�ϲ���
**  ע������:  �������ļ��Ѿ����ڣ�����У�����еİ汾�ţ��Ӷ��������Ƿ���ݸð汾���ļ���ʽ
**************************************************************************************************/
void CMySScomDlg::CreateSettingFile(void)
{
	char TempChar[256];
	CString oldver, showstr;
	
	// ��������ж�Ŀ¼���Ƿ����INI�ļ������������򴴽����ļ���д��Ĭ��ֵ

    if ((::GetPrivateProfileInt(FLAG_SYSRUNREC, SYSRUNREC_RUNTIMES, 0, CONFIGFILENAME)) == FALSE) {
		::WritePrivateProfileString(FLAG_SYSRUNREC, SYSRUNREC_PROGMVER, GetProgramVersion(), CONFIGFILENAME);
        ::WritePrivateProfileString(FLAG_SYSRUNREC, SYSRUNREC_RUNTIMES, "1",  CONFIGFILENAME);
		return;
	}

	::GetPrivateProfileString(FLAG_SYSRUNREC, SYSRUNREC_PROGMVER, "", TempChar, sizeof(TempChar), CONFIGFILENAME);
	oldver.Format("%s", TempChar);

	if (ConfigFileCanUse(oldver) == FALSE) {                                   /* �����ļ��汾���ܼ��� */
		showstr = "��⵽Ŀ¼�����е������ļ��汾���ɣ��޷�ʹ�ã�\r\nϵͳ�����Զ�����һ��ȫ�µ������ļ�\r\n����ԭ���������ļ�����Ϊ\"Settings_old.ini\"\r\n�����ļ��д�����Ҫ��Ϣ�����ֶ��������е����ݵ����ļ��У�";
		MessageBox(showstr, "��Ǹ", MB_OK + MB_ICONINFORMATION);
		rename(CONFIGFILENAME, CONFIGBACKNAME);                                /* ��ԭ�е������ļ�������Ȼ���½�һ������д��ؼ���Ϣ */
		::WritePrivateProfileString(FLAG_SYSRUNREC, SYSRUNREC_PROGMVER, GetProgramVersion(), CONFIGFILENAME);
		::WritePrivateProfileString(FLAG_SYSRUNREC, SYSRUNREC_RUNTIMES, "1",  CONFIGFILENAME);
	}
}

/**************************************************************************************************
**  ��������:  InitiateAllParas
**  ��������:  ��ȡ�����ļ��ĸ����������ݲ���ʼ���Ի����ֵ
**************************************************************************************************/
void CMySScomDlg::InitiateAllParas(void)
{
    char TempChar[MAX_SEND_BYTE];

	s_DialogPos_X = (::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_POSTIONX, 0, CONFIGFILENAME));
	s_DialogPos_Y = (::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_POSTIONY, 0, CONFIGFILENAME));

    m_Combo_CommPort.SetCurSel(::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_COMMPORT, 0, CONFIGFILENAME));
    m_Combo_BaudRate.SetCurSel(::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_BAUDRATE, 4, CONFIGFILENAME));
    m_Combo_DataBits.SetCurSel(::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_DATABITS, 3, CONFIGFILENAME));
    m_Combo_CheckBit.SetCurSel(::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_CHECKBIT, 0, CONFIGFILENAME));
    m_Combo_StopBits.SetCurSel(::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_STOPBITS, 0, CONFIGFILENAME));

	m_Check_ShowTime = (::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_SHOWTIME, 1, CONFIGFILENAME)) ? TRUE : FALSE;
    m_Check_HexDispl = (::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_HEXDISPL, 0, CONFIGFILENAME)) ? TRUE : FALSE;
    m_Check_HexFrame = (::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_HEXFRAME, 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_ProtoACK = (::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_PROTOACK, 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_HexsSend = (::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_HEXSSEND, 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_CRLFSend = (::GetPrivateProfileInt(FLAG_MAINFRAME, MAINFRAME_CRLFSEND, 0, CONFIGFILENAME)) ? TRUE : FALSE;

    ::GetPrivateProfileString(FLAG_MAINFRAME, MAINFRAME_AUTCLRKB, "1000", TempChar, 5, CONFIGFILENAME);
    m_Edit_AutClrKB.Format("%s", TempChar);
    
    ::GetPrivateProfileString(FLAG_MAINFRAME, MAINFRAME_SENDTIME, "1000", TempChar, 5, CONFIGFILENAME);
    m_Edit_SendTime.Format("%s", TempChar);

    ::GetPrivateProfileString(FLAG_MAINFRAME, MAINFRAME_SENDSTRS, "", TempChar, MAX_SEND_BYTE, CONFIGFILENAME);
    s_SendStr_Chr.Format("%s", TempChar);
	s_SendStr_Chr = FormatQuotesStrRead(s_SendStr_Chr);

	::GetPrivateProfileString(FLAG_MAINFRAME, MAINFRAME_SENDHEXS, "", TempChar, MAX_SEND_BYTE, CONFIGFILENAME);
	s_SendStr_Hex.Format("%s", TempChar);

	m_Edit_SendCstr = (m_Check_HexsSend == TRUE) ? s_SendStr_Hex : s_SendStr_Chr;

	::GetPrivateProfileString(FLAG_MAINFRAME, MAINFRAME_FILEPATH, "", TempChar, 1024, CONFIGFILENAME);
	m_Edit_FilePath.Format("%s", TempChar);
    
	UpdateData(FALSE);                                                         /* ���±༭������ */
}

/**************************************************************************************************
**  ��������:  RecordAllParas
**  ��������:  ���Ի����и���������ֵ��¼�������ļ���
**************************************************************************************************/
void CMySScomDlg::RecordAllParas(void)
{
    int TempData;                                                              /* ��Ҫע����ǣ��Զ�����ʹ�ܺ�ѭ������ʹ���������뱣�� */
    CString ParaStr, TempStr;
	CRect rect;

	TempData = (::GetPrivateProfileInt(FLAG_SYSRUNREC, SYSRUNREC_RUNTIMES, 0, CONFIGFILENAME));
	ParaStr.Format("%d", TempData + 1);
	::WritePrivateProfileString(FLAG_SYSRUNREC, SYSRUNREC_RUNTIMES, ParaStr, CONFIGFILENAME);
    
	GetWindowRect(&rect);
	s_DialogPos_X = (rect.left < 0) ? 0 : rect.left;                           /* ����Ҫ��ֹ���ָ�ֵ�����Ҫ���޶� */
	s_DialogPos_Y = (rect.top  < 0) ? 0 : rect.top;

	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_POSTIONX, ParaStr, CONFIGFILENAME);

	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_POSTIONY, ParaStr, CONFIGFILENAME);
	
    ParaStr.Format("%d", m_Combo_CommPort.GetCurSel());
    ::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_COMMPORT, ParaStr, CONFIGFILENAME);

    ParaStr.Format("%d", m_Combo_BaudRate.GetCurSel());
    ::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_BAUDRATE, ParaStr, CONFIGFILENAME);

    ParaStr.Format("%d", m_Combo_DataBits.GetCurSel());
    ::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_DATABITS, ParaStr, CONFIGFILENAME);

    ParaStr.Format("%d", m_Combo_CheckBit.GetCurSel());
    ::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_CHECKBIT, ParaStr, CONFIGFILENAME);

    ParaStr.Format("%d", m_Combo_StopBits.GetCurSel());
    ::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_STOPBITS, ParaStr, CONFIGFILENAME);

    ::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_SHOWTIME, m_Check_ShowTime  ?  "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_HEXDISPL, m_Check_HexDispl  ?  "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_HEXFRAME, m_Check_HexFrame  ?  "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_HEXSSEND, m_Check_HexsSend  ?  "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_CRLFSEND, m_Check_CRLFSend  ?  "1" : "0", CONFIGFILENAME);

    GetDlgItemText(IDC_EDIT_AUTCLRKB, m_Edit_AutClrKB);
    ::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_AUTCLRKB, m_Edit_AutClrKB, CONFIGFILENAME);

	::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_AUTOSEND, m_Check_AutoSend  ?  "1" : "0", CONFIGFILENAME);
    GetDlgItemText(IDC_EDIT_SENDTIME, m_Edit_SendTime);
    ::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_SENDTIME, m_Edit_SendTime, CONFIGFILENAME);

	::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_SENDHEXS, s_SendStr_Hex, CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_SENDSTRS, FormatQuotesStrWrite(s_SendStr_Chr), CONFIGFILENAME);

	GetDlgItemText(IDC_EDIT_FILEPATH, m_Edit_FilePath);
	::WritePrivateProfileString(FLAG_MAINFRAME, MAINFRAME_FILEPATH, m_Edit_FilePath, CONFIGFILENAME);
}

/**************************************************************************************************
**  ��������:  InitiateStatusBar
**  ��������:  ��ʼ��״̬��
**************************************************************************************************/
void CMySScomDlg::InitiateStatusBar(void)
{
    static UINT indicators[] =
    {
        ID_SEPARATOR,
        ID_INDICATOR_CAPS,
        ID_INDICATOR_NUM,
        ID_INDICATOR_SCRL,
        ID_INDICATOR_OVR
    };

    CTime   time;
    CString m_strTime;
    UINT    nID = 0;
    
    if (!s_CStatusBar.Create(this) || !s_CStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT))) {
        TRACE0("Failed to create status bar!");
        return;
    }

    time = CTime::GetCurrentTime();
    m_strTime = " ��ǰʱ��: " + time.Format("%Y-%m-%d") + " " + time.Format("%H:%M:%S");

    s_CStatusBar.SetPaneInfo(0, nID, SBPS_STRETCH, 1);
    s_CStatusBar.SetPaneText(0, " ��ӭʹ��MySScom");

    s_CStatusBar.SetPaneInfo(1, nID, SBPS_NORMAL, 90);
    s_CStatusBar.SetPaneText(1, " ����δ��");
    
    s_CStatusBar.SetPaneInfo(2, nID, SBPS_NORMAL, 140);
    s_CStatusBar.SetPaneText(2, " ����: 000, 000, 000");
    
    s_CStatusBar.SetPaneInfo(3, nID, SBPS_NORMAL, 140);
    s_CStatusBar.SetPaneText(3, " ����: 000, 000, 000");

    s_CStatusBar.SetPaneInfo(4, nID, SBPS_NORMAL, 200);
    s_CStatusBar.SetPaneText(4, m_strTime);

    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}

/**************************************************************************************************
**  ��������:  InitiateComboComs
**  ��������:  ��ʼ�����ں���Ͽ�
**************************************************************************************************/
void CMySScomDlg::InitiateComboComs(void)
{
    EnumCommPortList();                                                        /* ö�ٿ��õĴ��� */

	m_Combo_CommPort.ResetContent();
	m_Combo_CommPort.AddString("��ѡ��");                                      /* ��һ��Ϊ��ʾ�� */

    for (int i = 0; i < s_PortNumber.GetSize(); i++) {
        m_Combo_CommPort.AddString(s_PortNumber.GetAt(i));
    }
}

/**************************************************************************************************
**  ��������:  InitiateComboBaud
**  ��������:  ��ʼ����������Ͽ�
**************************************************************************************************/
void CMySScomDlg::InitiateComboBaud(void)
{
    CString TempStr;
    
    for (int i = 0; i < (sizeof(Combo_Baud) / sizeof(Combo_Baud[0])); i++) {
        TempStr.Format("%d bps", Combo_Baud[i]);
        m_Combo_BaudRate.AddString(TempStr);
    }
}

/**************************************************************************************************
**  ��������:  InitiateComboData
**  ��������:  ��ʼ������λ��Ͽ�
**************************************************************************************************/
void CMySScomDlg::InitiateComboData(void)
{
    CString TempStr;
    
    for (int i = 0; i < (sizeof(Combo_Data) / sizeof(Combo_Data[0])); i++) {
        TempStr.Format("%d λ", Combo_Data[i]);
        m_Combo_DataBits.AddString(TempStr);
    }
}

/**************************************************************************************************
**  ��������:  InitiateComboCheck
**  ��������:  ��ʼ��У��λ��Ͽ�
**************************************************************************************************/
void CMySScomDlg::InitiateComboCheck(void)
{
    m_Combo_CheckBit.AddString("None У��");
    m_Combo_CheckBit.AddString("Odd  У��");
    m_Combo_CheckBit.AddString("Even У��");
    m_Combo_CheckBit.AddString("Mark У��");
    m_Combo_CheckBit.AddString("SpaceУ��");
}

/**************************************************************************************************
**  ��������:  InitiateComboStop
**  ��������:  ��ʼ��ֹͣλ��Ͽ�
**************************************************************************************************/
void CMySScomDlg::InitiateComboStop(void)
{
    m_Combo_StopBits.AddString("1  λ");
    m_Combo_StopBits.AddString("1.5λ");
    m_Combo_StopBits.AddString("2  λ");
}

/**************************************************************************************************
**  ��������:  InitiateChildWins
**  ��������:  ��ʼ�������Ӵ���ҳ��
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

	s_PDlgKeyWords = new CDialogKeywords();                                    /* ������䴴���ؼ��ּ������壬�����ش��� */

	if (s_PDlgKeyWords != NULL){

		int Result = s_PDlgKeyWords->Create(IDD_DIALOG_KEYWORDS, this);

		if (!Result) {
			MessageBox("ϵͳ��Դ���㣬�����Ի���ʧ��......   ", "��Ǹ", MB_OK + MB_ICONERROR);
			return FALSE;
		}

		s_PDlgKeyWords->ShowWindow(SW_HIDE);
		s_PDlgKeyWords->InitiateAllParas();
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
**************************************************************************************************/
void CMySScomDlg::InitiateToolsTip(void)
{
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);

	m_tooltip.AddTool(GetDlgItem(IDC_COMBO_COMMPORT),  IDS_STRING_001);
	m_tooltip.AddTool(GetDlgItem(IDC_COMBO_BAUDRATE),  IDS_STRING_002);
	m_tooltip.AddTool(GetDlgItem(IDC_COMBO_DATABITS),  IDS_STRING_003);
	m_tooltip.AddTool(GetDlgItem(IDC_COMBO_STOPBITS),  IDS_STRING_004);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_ONOFF),    IDS_STRING_005);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_PAUSE),    IDS_STRING_006);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_CLEAR),    IDS_STRING_007);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SAVE),     IDS_STRING_008);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_HEXDISPL),  IDS_STRING_009);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOCLER),  IDS_STRING_010);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOSAVE),  IDS_STRING_011);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SEND),     IDS_STRING_015);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_HEXSSEND),  IDS_STRING_016);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOSEND),  IDS_STRING_017);
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_SENDTIME),   IDS_STRING_018);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_CRLFSEND),  IDS_STRING_020);
	m_tooltip.AddTool(GetDlgItem(IDC_COMBO_CHECKBIT),  IDS_STRING_021);
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_AUTCLRKB),   IDS_STRING_024);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_EXFUNCT),  IDS_STRING_025);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SRSEND),   IDS_STRING_026);
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_SENDCSTR),   IDS_STRING_027);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_OPENFILE), IDS_STRING_028);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SENDFILE), IDS_STRING_029);
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_FILEPATH),   IDS_STRING_030);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_SHOWTIME),  IDS_STRING_031);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_HEXFRAME),  IDS_STRING_032);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOFILT),  IDS_STRING_033);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_PROTOACK),  IDS_STRING_034);
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_KEYWORDS),  IDS_STRING_035);
}

/**************************************************************************************************
**  ��������:  InitiateMainStatic
**  ��������:  ��ʼ�������������ʾ�����ʾ
**************************************************************************************************/
void CMySScomDlg::InitiateMainStatic(void)
{
	CFont* font = new CFont;

	s_MainStatic = new CStatic;
	CRect rect1(STATIC_LEFT, STATIC_TOP, STATIC_LEFT + STATIC_WIDTH, STATIC_TOP + STATIC_HEIGHT);

	s_MainStatic->CreateEx(NULL, "static", STATIC_TEXT, WS_CHILD | WS_VISIBLE, rect1, this, IDS_MAINSTATIC, NULL);
	
	font->CreateFont(14, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "arial");
	s_MainStatic->SetFont(font);

	s_MainStatic->ShowWindow(FALSE);
}

/**************************************************************************************************
**  ��������:  UpdateMainStatic
**  ��������:  �������������Ϣ��ʾ�����ʾ
**************************************************************************************************/
void CMySScomDlg::UpdateMainStatic(void)
{
	CRect rectDlg;
	GetClientRect(rectDlg);

	if (rectDlg.Height() > MAINWIN_HEIGHT) {                                   /* ���ݴ��嵱ǰ�ĸ߶����ж� */
		s_MainStatic->ShowWindow(TRUE);
	} else {
		s_MainStatic->ShowWindow(FALSE);
	}
}

/**************************************************************************************************
**  ��������:  UpdateComboComs
**  ��������:  ���´��ں���Ͽ�
**************************************************************************************************/
void CMySScomDlg::UpdateComboComs(void)
{
    int      pindex;
	CString  comstr;
	
	pindex = m_Combo_CommPort.GetCurSel();                                     /* ���Ȼ�ȡ��ǰѡ��Ĵ��ں� */

	if (pindex == 0) {                                                         /* 0��ʾû��ѡ����Ч�Ĵ��ں� */
		comstr = "";
	} else {                                                                   /* ���ݴ��ںŻ�ȡ��COM�ַ��� */
		comstr = s_PortNumber.GetAt(pindex - 1);
	}

	InitiateComboComs();

	if (comstr == "") {                                                        /* ��ʾ֮ǰû��ѡ����Ч���ں� */
		m_Combo_CommPort.SetCurSel(0);                                         /* ֱ��ѡ����ʾ�� */
		return;
	}

	for (pindex = 0; pindex < s_PortNumber.GetSize(); pindex++) {              /* ֮ǰ����ѡ�й�ĳ�����ں� */
		if (s_PortNumber.GetAt(pindex) == comstr) {                            /* ����ȶԣ���λ���ô��ڵ���� */
			m_Combo_CommPort.SetCurSel(pindex + 1);                            /* �Զ�ѡ�иô��ں� */
			return;
		}
	}

	m_Combo_CommPort.SetCurSel(0);                                             /* �ȶ�ʧ�ܣ�˵��֮ǰѡ�еĴ�������ʧ����ָ�����ʾ�� */
}

/**************************************************************************************************
**  ��������:  TaskBarAddIcon
**  ��������:  ������������ͼ����ʾ
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
        GetDlgItem(IDC_COMBO_COMMPORT)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_BAUDRATE)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_DATABITS)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_CHECKBIT)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_STOPBITS)->EnableWindow(TRUE);

        return;
    }

    int ComNumber = m_Combo_CommPort.GetCurSel();                              /* �õ����ں� */

    if (ComNumber == 0) {
        MessageBox("�����ںŶ�û��ѡ������Ҵ�ʲô����...��   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        return;
    }

	m_Combo_CommPort.GetLBText(ComNumber, TempStr);                            /* ��ȡ���ں�ѡ���� */
    CString ComDevFile = "\\\\.\\" + TempStr;

    TempStr.Format("%d", Combo_Baud[m_Combo_BaudRate.GetCurSel()]);            /* ��ȡ������ѡ���� */
    spara.baudrate = atoi(TempStr);
    
    TempStr.Format("%d", Combo_Data[m_Combo_DataBits.GetCurSel()]);            /* ��ȡ����λѡ���� */
    spara.databits = atoi(TempStr);
    
    TempStr.Format("%d", Combo_Check[m_Combo_CheckBit.GetCurSel()]);           /* ��ȡУ��λѡ���� */
    spara.checkbit = atoi(TempStr);

    TempStr.Format("%d", Combo_Stop[m_Combo_StopBits.GetCurSel()]);            /* ��ȡֹͣλѡ���� */
    spara.stopbits = atoi(TempStr);

	if (OpenSerialDevice(ComDevFile, &spara) == FALSE) {                       /* �򿪴��ڲ���ʼ�� */
		return;
	}

    SetControlStatus(TRUE);                                                    /* ���ø�����ť�ؼ� */
    SetDlgItemText(IDC_BUTTON_ONOFF, "�رմ���");
    GetDlgItem(IDC_COMBO_COMMPORT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_BAUDRATE)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_DATABITS)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_CHECKBIT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_STOPBITS)->EnableWindow(FALSE);
}

/**************************************************************************************************
**  ��������:  OnButtonRecvPause
**  ��������:  ��ͣ����/�ָ�����
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
**************************************************************************************************/
void CMySScomDlg::OnButtonClearAll()
{
    m_Edit_RecvCstr = "";
    SetDlgItemText(IDC_EDIT_RECVCSTR, m_Edit_RecvCstr);

    s_RecvedByte = 0;
    s_SendedByte = 0;
    s_RecvString = "";
    s_NeedChgLne = TRUE;                                                       /* �´���Ҫ������ʾ */

    UpdateStatusBarNow();                                                      /* ����״̬����ͳ��������ʾ */
}

/**************************************************************************************************
**  ��������:  OnButtonSaveFile
**  ��������:  �����յ������ݱ��浽�ļ���
**************************************************************************************************/
void CMySScomDlg::OnButtonSaveFile()
{
    CTime   NowTime  = CTime::GetCurrentTime();                                /* ��ȡ����ʱ�� */
    CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt";           /* ָ���ļ��� */
    
    GetDlgItemText(IDC_EDIT_RECVCSTR, m_Edit_RecvCstr);
    
    if (m_Edit_RecvCstr.GetLength() <= 0) {
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
**************************************************************************************************/
void CMySScomDlg::OnButtonSendData()
{
    unsigned char buff[MAX_SEND_BYTE];
	
	GetDlgItemText(IDC_EDIT_SENDCSTR, m_Edit_SendCstr);
    
    if (m_Edit_SendCstr.GetLength() <= 0) {
        MessageBox("���ʹ�������Ϊ�գ�δ�����κ����ݣ� ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        return;
    }
	
	strncpy_s((char *)&buff[0], sizeof(buff), (LPCTSTR)m_Edit_SendCstr, m_Edit_SendCstr.GetLength());

	if (SendDatatoComm(buff, m_Edit_SendCstr.GetLength(), m_Check_HexsSend) == FALSE) {
		MessageBox("�����������֡���ݹ��������ߴ��ڷǷ��ַ�����ȷ�ϣ�......       ", "����", MB_OK + MB_ICONEXCLAMATION);
		return;
	}
}

/**************************************************************************************************
**  ��������:  OnButtonSuperSend
**  ��������:  ��ʾ�߼����ʹ���
**************************************************************************************************/
void CMySScomDlg::OnButtonSuperSend() 
{
	if (s_PDlgSuprSend->IsWindowVisible()) {                                   /* �����Ѿ��򿪣����Թر� */

		if ((s_PDlgSuprSend->s_issenddata) == TRUE) {
			MessageBox("����ֹͣ�Զ�ѭ�����͹��ܣ��ٳ��Թرո߼����ʹ���......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			return;
		} else {
			s_PDlgSuprSend->ShowHideDlgWindow(FALSE);
			SetDlgItemText(IDC_BUTTON_SRSEND, "�߼�����");
			
			GetDlgItem(IDC_CHECK_HEXSSEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SENDTIME)->EnableWindow(TRUE);
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

			GetDlgItem(IDC_CHECK_HEXSSEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SENDTIME)->EnableWindow(FALSE);
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
**************************************************************************************************/
void CMySScomDlg::OnButtonExtrafunc() 
{
	if (s_PDlgExtrfunc->IsWindowVisible() == FALSE) {                          /* ������δ�򿪣����Դ� */
		s_PDlgExtrfunc->ShowHideDlgWindow(TRUE);
	}
}

/**************************************************************************************************
**  ��������:  OnButtonOpenFile
**  ��������:  ���ļ�
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
				m_Progs_SendFile.SetPos(0);
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
**************************************************************************************************/
void CMySScomDlg::OnButtonConfigAutoReply()
{
	if (s_PDlgAutoRply->IsWindowVisible() == FALSE) {                          /* ������δ�򿪣����Դ� */
		s_PDlgAutoRply->ShowHideDlgWindow(TRUE);
	}
}

/**************************************************************************************************
**  ��������:  OnButtonConfigDsplFilt
**  ��������:  ����ʾ���˷�������ô���
**************************************************************************************************/
void CMySScomDlg::OnButtonConfigDsplFilt()
{
	if (s_PDlgDsplFilt->IsWindowVisible() == FALSE) {                          /* ������δ�򿪣����Դ� */
		s_PDlgDsplFilt->ShowHideDlgWindow(TRUE);
	}
}

/**************************************************************************************************
**  ��������:  OnButtonConfigKeywords
**  ��������:  �򿪹ؼ��ַ�ƥ������ô���
**************************************************************************************************/
void CMySScomDlg::OnButtonConfigKeywords()
{
	if (s_PDlgKeyWords->IsWindowVisible() == FALSE) {                          /* ������δ�򿪣����Դ� */
		s_PDlgKeyWords->ShowHideDlgWindow(TRUE);
	}
}

/**************************************************************************************************
**  ��������:  OnCheckHexDisplay
**  ��������:  ��ʾ16�����ַ���ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckHexDisplay()
{
    m_Check_HexDispl = !m_Check_HexDispl;

	GetDlgItem(IDC_CHECK_HEXFRAME)->EnableWindow(m_Check_HexDispl);
	GetDlgItem(IDC_CHECK_PROTOACK)->EnableWindow(m_Check_HexDispl);
	GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(m_Check_HexDispl);

    if (m_Check_HexDispl == TRUE) {
		if (IsDlgButtonChecked(IDC_CHECK_PROTOACK) == TRUE) {
			GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(TRUE);
		} else {
			GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(FALSE);
		}
    } else {
		if (s_PDlgAutoRply->IsWindowVisible() == TRUE) {
			s_PDlgAutoRply->ShowHideDlgWindow(FALSE);
		}
    }
}

/**************************************************************************************************
**  ��������:  OnCheckAutoClear
**  ��������:  �Զ�������ܸ�ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoClear() 
{
    int     TempData;
    CString TempStr;
    
    m_Check_AutoCler = !m_Check_AutoCler;
    
    GetDlgItemText(IDC_EDIT_AUTCLRKB, TempStr);

    TempData = atoi((LPSTR)(LPCTSTR)TempStr);
    
    if (TempData < 100) {        
        MessageBox("�����õ�����ֵ��С��������ʹ�á�������һ������100��ֵ��     ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        SetDlgItemText(IDC_EDIT_AUTCLRKB, m_Edit_AutClrKB);                    /* ��ԭ�༭������ */
        m_Check_AutoCler = FALSE;        
        UpdateData(FALSE);
        return;
    }

    if (m_Check_AutoCler == TRUE) {
        GetDlgItem(IDC_STATIC_OVER)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_LINES)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AUTCLRKB)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(TRUE);
    } else {
        GetDlgItem(IDC_STATIC_OVER)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_LINES)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_AUTCLRKB)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(FALSE);
    }
}

/**************************************************************************************************
**  ��������:  OnCheckAutoSave
**  ��������:  �Զ����湦�ܸ�ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoSave()
{
    m_Check_AutoSave = !m_Check_AutoSave;
}

/**************************************************************************************************
**  ��������:  OnCheckHexSend
**  ��������:  ����16�������ݸ�ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckHexSend()
{
    m_Check_HexsSend = !m_Check_HexsSend;
	
	GetDlgItemText(IDC_EDIT_SENDCSTR, m_Edit_SendCstr);                        /* ���ȱ��浱ǰ���ݣ�Ȼ�������ʾ */

	if (m_Check_HexsSend == FALSE) {                                           /* ֮ǰ��16����ģʽ�����������ַ�ģʽ */
		s_SendStr_Hex = m_Edit_SendCstr;
		SetDlgItemText(IDC_EDIT_SENDCSTR, s_SendStr_Chr);
	} else {                                                                   /* ֮ǰ���ַ�ģʽ����������16����ģʽ */
		s_SendStr_Chr = m_Edit_SendCstr;
		SetDlgItemText(IDC_EDIT_SENDCSTR, s_SendStr_Hex);
	}
	
	UpdateData(TRUE);
}

/**************************************************************************************************
**  ��������:  OnCheckAutoSend
**  ��������:  �Զ����͹��ܸ�ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoSend()
{   
    m_Check_AutoSend = !m_Check_AutoSend;

    GetDlgItemText(IDC_EDIT_SENDCSTR, m_Edit_SendCstr);

    if (m_Edit_SendCstr.GetLength() <= 0) {
        MessageBox("ʲô���ݶ��������Ҫ����һ������ô......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        m_Check_AutoSend = FALSE;
        UpdateData(FALSE);
        return;
    }

    if (m_Check_AutoSend) {
        if (m_Edit_SendCstr.GetLength() >= MAX_SEND_BYTE) {                    /* ȷ����������ݲ������ */
            MessageBox("����������ݹ������ύ��������ʧ��......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
            m_Check_AutoSend = FALSE;
            UpdateData(FALSE);
            return;
        }

        NeedAutoSendData();                                                    /* ��ʼ�����Զ��������� */
		GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(FALSE);

    } else {

        KillTimer(Timer_No_AutoSend);                                          /* �����û�ȡ�����Զ����͵Ĺ��� */
        GetDlgItem(IDC_EDIT_SENDTIME)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);                       /* �������÷��Ͱ�ť */
		GetDlgItem(IDC_BUTTON_SENDFILE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(TRUE);
    }
}

/**************************************************************************************************
**  ��������:  OnCheckAddReturn
**  ��������:  ����ʱ���ӻس�����ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckAddReturn()
{
    m_Check_CRLFSend = !m_Check_CRLFSend;
}

/**************************************************************************************************
**  ��������:  OnCheckShowTime
**  ��������:  ��ͷλ����ʾʱ�临ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckShowTime()
{
    m_Check_ShowTime = !m_Check_ShowTime;
}

/**************************************************************************************************
**  ��������:  OnCheckFrameDspl
**  ��������:  ֡��ʽ��ʾ�Զ����й��ܸ�ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckFrameDspl() 
{
	m_Check_HexFrame = !m_Check_HexFrame;
}

/**************************************************************************************************
**  ��������:  OnCheckAutoReply
**  ��������:  �Զ��ظ���ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckAutoReply()
{
	m_Check_ProtoACK = !m_Check_ProtoACK;

	GetDlgItem(IDC_BUTTON_SETREPLY)->EnableWindow(m_Check_ProtoACK);

	if (m_Check_ProtoACK == FALSE) {
		if (s_PDlgAutoRply->IsWindowVisible() == TRUE) {                       /* ������δ�ر� */
			s_PDlgAutoRply->ShowHideDlgWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  ��������:  OnCheckDsplFilt
**  ��������:  ��ʾ���ݹ��˸�ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckDsplFilt()
{
	m_Check_AutoFilt = !m_Check_AutoFilt;

	GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(m_Check_AutoFilt);

	if (m_Check_AutoFilt == FALSE) {
		if (s_PDlgDsplFilt->IsWindowVisible() == TRUE) {                       /* ������δ�ر� */
			s_PDlgDsplFilt->ShowHideDlgWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  ��������:  OnCheckKeyword
**  ��������:  �ؼ��ּ������ظ�ѡ��״̬�л�
**************************************************************************************************/
void CMySScomDlg::OnCheckKeyword()
{
	m_Check_Keywords = !m_Check_Keywords;

	GetDlgItem(IDC_BUTTON_KEYWORD)->EnableWindow(m_Check_Keywords);

	if (m_Check_Keywords == FALSE) {
		if (s_PDlgKeyWords->IsWindowVisible() == TRUE) {                       /* ������δ�ر� */
			s_PDlgKeyWords->ShowHideDlgWindow(FALSE);
		}
	}
}

/**************************************************************************************************
**  ��������:  OnChangeEditSendcstr
**  ��������:  ���ͱ༭�����ݱ仯
**************************************************************************************************/
void CMySScomDlg::OnChangeEditSendcstr()
{
	GetDlgItemText(IDC_EDIT_SENDCSTR, m_Edit_SendCstr);
	
	if (m_Check_HexsSend == FALSE) {                                           /* �ַ�ģʽ�¸���s_SendStr_Chr */
		s_SendStr_Chr = m_Edit_SendCstr;
	} else {                                                                   /* 16����ģʽ����s_SendStr_Hex */
		s_SendStr_Hex = m_Edit_SendCstr;
	}
}

/**************************************************************************************************
**  ��������:  OnMenuEditCopy
**  ��������:  �༭��˵� - ������ѡ����
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

	lf.lfCharSet        = cf.bCharSet;
	lf.lfHeight         = cf.yHeight / 15;
	lf.lfPitchAndFamily = cf.bPitchAndFamily;
	lf.lfItalic         = bIsItalic;
	lf.lfWeight         = (bIsBold ? FW_BOLD : FW_NORMAL);
	lf.lfUnderline      = bIsUnderline;
	lf.lfStrikeOut      = bIsStrickout;
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
**************************************************************************************************/
void CMySScomDlg::OnMenuEditAbout()
{
	ShowAboutMeDialog();
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorWhite
**  ��������:  �༭��˵� - ������ɫ���� - ѩ����
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorWhite()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_WHITE);
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorGray
**  ��������:  �༭��˵� - ������ɫ���� - �Ƽ���
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorGray()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_GRAY);
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorGreen
**  ��������:  �༭��˵� - ������ɫ���� - ������
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorGreen()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_GREEN);
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorBlue
**  ��������:  �༭��˵� - ������ɫ���� - �̿���
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorBlue()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_BLUE);
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorPink
**  ��������:  �༭��˵� - ������ɫ���� - ������
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorPink()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_PINK);
}

/**************************************************************************************************
**  ��������:  OnMenuEditColorPurple
**  ��������:  �༭��˵� - ������ɫ���� - ��ɴ��
**************************************************************************************************/
void CMySScomDlg::OnMenuEditColorPurple()
{
	m_RichEdit_Recv.SetBackgroundColor(FALSE, RGB_LIGHT_PURPLE);
}

/**************************************************************************************************
**  ��������:  OnMenuTrayAbout
**  ��������:  ���̲˵� - ���ڳ���
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayAbout()
{
	ShowAboutMeDialog();
}

/**************************************************************************************************
**  ��������:  OnMenuTrayShow
**  ��������:  ���̲˵� - ��ʾ����
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayShow()
{
    ShowWindow(SW_SHOW);
}

/**************************************************************************************************
**  ��������:  OnMenuTrayHide
**  ��������:  ���̲˵� - ���ؽ���
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayHide()
{
    CloseAllChildWin();                                                        /* �رո����Ӵ��� */
	ShowWindow(SW_HIDE);
}

/**************************************************************************************************
**  ��������:  OnMenuTrayExit
**  ��������:  ���̲˵� - �˳�����
**************************************************************************************************/
void CMySScomDlg::OnMenuTrayExit()
{
    CloseAllChildWin();                                                        /* �رո����Ӵ��� */
	
	RecordAllParas();                                                          /* ��������������� */

	s_PDlgSuprSend->RecordAllParas();
	s_PDlgExtrfunc->RecordAllParas();
	s_PDlgDsplFilt->RecordAllParas();
	s_PDlgAutoRply->RecordAllParas();
	s_PDlgKeyWords->RecordAllParas();

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
**************************************************************************************************/
HCURSOR CMySScomDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

/**************************************************************************************************
**  ��������:  OnInitDialog
**  ��������:  ���ڳ�ʼ��
**************************************************************************************************/
BOOL CMySScomDlg::OnInitDialog()
{
    LARGE_INTEGER litmp;
	
	CDialog::OnInitDialog();

	s_RecvPaused = FALSE;
	s_DevNeedUpd = FALSE;
	s_NeedChgLne = TRUE;
	s_RecvString = "";
	s_LopSendCnt = 0;
	s_RecvedByte = 0;
	s_SendedByte = 0;
	s_FileDatPos = 0;

	QueryPerformanceCounter(&litmp);
	s_StartdTcik = litmp.QuadPart;                                             /* ��ó�ʼֵ */

	CreateDirectory(REC_DIR_PATH, NULL);                                       /* ����Record�ļ��У����ڱ������� */
	CreateSettingFile();                                                       /* �����������ò����ļ�����ʼ���������� */

	if (InitiateChildWins() == FALSE) {                                        /* ���������Ӵ����ҳ�� */
		return FALSE;
	}
	
	GetDlgItem(IDC_PROGRESS_SENDFILE)->ShowWindow(SW_HIDE);                    /* ���ؽ�����������ʼ������ */
	m_Progs_SendFile.SetRange(0, PROGRESS_POS);
	m_Progs_SendFile.SetPos(0);

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

	#if RELEASE_VERSION == 1
	SetWindowText("MySScom V" + GetProgramVersion());                          /* ���öԻ������Ϊ����汾�� */
	#else
	SetWindowText("MySScom V" + GetProgramVersion() + " <Built @ " + __DATE__ + " " + __TIME__ + ">");
	#endif

    s_Edit_Recv = (CEdit*)GetDlgItem(IDC_EDIT_RECVCSTR);
    s_Edit_Send = (CEdit*)GetDlgItem(IDC_EDIT_SENDCSTR);

    InitiateStatusBar();                                                       /* ��ʼ��״̬����������λ�� */
    InitiateComboComs();                                                       /* ��ʼ��ѡ�񴮿ںŵ��б�� */
    InitiateComboBaud();                                                       /* ��ʼ��ѡ�����ʵ��б�� */
    InitiateComboData();                                                       /* ��ʼ��ѡ������λ���б�� */
    InitiateComboCheck();                                                      /* ��ʼ��ѡ��У��λ���б�� */
    InitiateComboStop();                                                       /* ��ʼ��ѡ��ֹͣλ���б�� */
	InitiateAllParas();                                                        /* ��ʼ���������¸��ؼ����� */
	InitiateToolsTip();                                                        /* ��ʼ���ؼ���������ʾ��Ϣ */
	InitiateMainStatic();                                                      /* ��ʼ����������ʾ�����ʾ */

    SetControlStatus(FALSE);                                                   /* ���Ƚ��ø�����ť�ؼ� */

    SetTimer(Timer_No_UpdateDsp, UPDATEEDIT_TIME, NULL);
    SetTimer(Timer_No_StatusBar, STATUSBAR_TIME, NULL);

    INIT_EASYSIZE;                                                             /* ��ʼ�������ؼ���λ�� */

	if (CreateDeviceThread() == FALSE) {                                       /* ����̴߳���ʧ�� */
        MessageBox("ϵͳ��Դ�쳣�������豸�����̴߳���ʧ�ܣ�����������", "��ʾ", MB_OK + MB_ICONERROR);
        return FALSE;
    }

	if (CreateUpdateThread() == FALSE) {                                       /* ����̴߳���ʧ�� */
		MessageBox("ϵͳ��Դ�쳣����̨���������̴߳���ʧ�ܣ�����������", "��ʾ", MB_OK + MB_ICONERROR);
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
**************************************************************************************************/
void CMySScomDlg::OnTimer(UINT nIDEvent) 
{
    unsigned char buff[MAX_SEND_BYTE];
	
	switch (nIDEvent)
    {
        case Timer_No_UpdateDsp:                                              /* ���±༭��������ʾ */
            if (s_DataRecved == TRUE) {
				UpdateEditStr(s_RecvString);
				s_RecvString = "";
                s_DataRecved = FALSE;
            }
            break;
        
        case Timer_No_StatusBar:                                               /* ״̬����ʱ���� */
            UpdateStatusBarNow();
			if (s_DevNeedUpd == TRUE) {                                        /* ˳�����һ�´����豸�б� */
				s_DevNeedUpd = FALSE;
				UpdateComboComs();
			}
            break;
            
        case Timer_No_AutoSend:                                                /* �Զ��������� */
            GetDlgItemText(IDC_EDIT_SENDCSTR, m_Edit_SendCstr);
			strncpy_s((char *)&buff[0], sizeof(buff), (LPCTSTR)m_Edit_SendCstr, m_Edit_SendCstr.GetLength());
			if (SendDatatoComm(buff, m_Edit_SendCstr.GetLength(), m_Check_HexsSend) == FALSE) {
				OnCheckAutoSend();
				UpdateData(FALSE);
				MessageBox("�����������֡���ݹ��������ߴ��ڷǷ��ַ�����ȷ�ϣ�......       ", "����", MB_OK + MB_ICONEXCLAMATION);
			}
            break;
            
		case Timer_No_FrameDspl:                                               /* 16�����°�֡������ʾ�ж� */
			KillTimer(Timer_No_FrameDspl);
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
**************************************************************************************************/
BOOL CMySScomDlg::PreTranslateMessage(MSG* pMsg) 
{
    unsigned char keyvalue;
    
    m_tooltip.RelayEvent(pMsg);

    if (pMsg->message == WM_KEYDOWN) {

		if ((pMsg->wParam >= VK_F1) && (pMsg->wParam <= VK_F12)) {             /* �˴������û��Զ����Fn���ܼ� */
			UserFnKeyHdl(pMsg->wParam);
			return true;
		}

		if (SerialDevisOpened() == TRUE) {                                     /* �˴����û�������ֵ���͵����� */
			if ((GetFocus() == GetDlgItem(IDC_EDIT_INPUT)) || GetFocus() == GetDlgItem(IDC_EDIT_RECVCSTR)) {
				keyvalue = GetKeyValue(pMsg->wParam);                          /* ֻ��ȡ��Щ������İ�����ֵ */
				if (keyvalue > 0) {
					s_SendedByte += SendSerialData(&keyvalue, 1);              /* ��������ֵͨ�����ڷ��ͳ�ȥ */
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
**  ��������:  �����ڴ�С������Ϣ ���䶯�󣬴�ʱ�����С�Ѿ�ȷ����
**************************************************************************************************/
void CMySScomDlg::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);

    UPDATE_EASYSIZE;

    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);      /* ͬ��״̬����λ�� */
}

/**************************************************************************************************
**  ��������:  OnSizing
**  ��������:  �����ڴ�С������Ϣ ���ı��У���ʱ�����С��δ���ͣ�
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
**  ��������:  WinHelp
**  ��������:  ����ϵͳ�������� - ��������ϵͳ��������
**************************************************************************************************/
void CMySScomDlg::WinHelp(DWORD dwData, UINT nCmd)
{
	return;
}

/**************************************************************************************************
**  ��������:  OnSysCommand
**  ��������:  ����ϵͳ��Ϣ
**************************************************************************************************/
void CMySScomDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_MINIMIZE) {                                                  /* �����Ҫ������С�� */
		CloseAllChildWin();                                                    /* �ر������Ӵ��� */
	}

	UpdateStatusBarNow();

	CDialog::OnSysCommand(nID, lParam);
}



