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

static const int Combo_Baud[12] = {600,  1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
static const int Combo_Data[4]  = {5,    6,    7,    8};
static const int Combo_Stop[4]  = {0,    1,    2,    3};
static const int Combo_Check[5] = {'n',  'o',  'e',  'm',   's'};

/////////////////////////////////////////////////////////////////////////////
// CMySScomDlg dialog

CMySScomDlg::CMySScomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySScomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMySScomDlg)
	m_Check_AutoSave = FALSE;
	m_Check_AutoSend = FALSE;
	m_Check_LoopSend = FALSE;	
	m_Check_HexDspl = FALSE;
	m_Check_HexSend = FALSE;
	m_Check_AutoClear = FALSE;
	m_Edit_Recv = _T("");
	m_Edit_Send = _T("");
	m_Edit_AutoTimer = _T("");
	m_Edit_LoopTimer = _T("");
	m_Check_SrSend_01 = FALSE;
	m_Check_SrSend_02 = FALSE;
	m_Check_SrSend_03 = FALSE;
	m_Check_SrSend_04 = FALSE;
	m_Check_SrSend_05 = FALSE;
	m_Check_SrSend_06 = FALSE;
	m_Check_SrSend_07 = FALSE;
	m_Check_SrSend_08 = FALSE;
	m_Check_SrSend_09 = FALSE;
	m_Check_SrSend_10 = FALSE;
	m_Check_SrSend_11 = FALSE;
	m_Check_SrSend_12 = FALSE;
	m_Check_SrSend_13 = FALSE;
	m_Check_SrSend_14 = FALSE;
	m_Check_SrSend_15 = FALSE;
	m_Check_SrSend_16 = FALSE;
	m_Check_SrSend_17 = FALSE;
	m_Check_SrSend_18 = FALSE;
	m_Check_SrSend_19 = FALSE;
	m_Check_SrSend_20 = FALSE;
    m_Edit_Lines = _T("1000");
	m_Check_Return = FALSE;
	m_NeedTime = TRUE;
	m_DataRecvd = FALSE;
	m_Check_ShowTime = FALSE;
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
	DDX_Check(pDX, IDC_CHECK_SRAUTO, m_Check_LoopSend);
	DDX_Check(pDX, IDC_CHECK_HEXDSPL, m_Check_HexDspl);
	DDX_Check(pDX, IDC_CHECK_HEXSEND, m_Check_HexSend);
	DDX_Check(pDX, IDC_CHECK_AUTOCLEAR, m_Check_AutoClear);
	DDX_Text(pDX, IDC_EDIT_RECV, m_Edit_Recv);
	DDX_Text(pDX, IDC_EDIT_SEND, m_Edit_Send);
	DDX_Text(pDX, IDC_EDIT_TIMER, m_Edit_AutoTimer);
	DDX_Text(pDX, IDC_EDIT_SRAUTO, m_Edit_LoopTimer);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Check(pDX, IDC_CHECK_SR01, m_Check_SrSend_01);
	DDX_Check(pDX, IDC_CHECK_SR02, m_Check_SrSend_02);
	DDX_Check(pDX, IDC_CHECK_SR03, m_Check_SrSend_03);
	DDX_Check(pDX, IDC_CHECK_SR04, m_Check_SrSend_04);
	DDX_Check(pDX, IDC_CHECK_SR05, m_Check_SrSend_05);
	DDX_Check(pDX, IDC_CHECK_SR06, m_Check_SrSend_06);
	DDX_Check(pDX, IDC_CHECK_SR07, m_Check_SrSend_07);
	DDX_Check(pDX, IDC_CHECK_SR08, m_Check_SrSend_08);
	DDX_Check(pDX, IDC_CHECK_SR09, m_Check_SrSend_09);
	DDX_Check(pDX, IDC_CHECK_SR10, m_Check_SrSend_10);
	DDX_Check(pDX, IDC_CHECK_SR11, m_Check_SrSend_11);
	DDX_Check(pDX, IDC_CHECK_SR12, m_Check_SrSend_12);
	DDX_Check(pDX, IDC_CHECK_SR13, m_Check_SrSend_13);
	DDX_Check(pDX, IDC_CHECK_SR14, m_Check_SrSend_14);
	DDX_Check(pDX, IDC_CHECK_SR15, m_Check_SrSend_15);
	DDX_Check(pDX, IDC_CHECK_SR16, m_Check_SrSend_16);
	DDX_Check(pDX, IDC_CHECK_SR17, m_Check_SrSend_17);
	DDX_Check(pDX, IDC_CHECK_SR18, m_Check_SrSend_18);
	DDX_Check(pDX, IDC_CHECK_SR19, m_Check_SrSend_19);
	DDX_Check(pDX, IDC_CHECK_SR20, m_Check_SrSend_20);
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
	ON_BN_CLICKED(IDC_BUTTON_SRSEND, OnButtonSrSend)
	ON_BN_CLICKED(IDC_CHECK_SRAUTO, OnCheckSrAuto)
	ON_BN_CLICKED(IDC_BUTTON_SR01, OnButtonSrSend01)
	ON_BN_CLICKED(IDC_BUTTON_SR02, OnButtonSrSend02)
	ON_BN_CLICKED(IDC_BUTTON_SR03, OnButtonSrSend03)
	ON_BN_CLICKED(IDC_BUTTON_SR04, OnButtonSrSend04)
	ON_BN_CLICKED(IDC_BUTTON_SR05, OnButtonSrSend05)
	ON_BN_CLICKED(IDC_BUTTON_SR06, OnButtonSrSend06)
	ON_BN_CLICKED(IDC_BUTTON_SR07, OnButtonSrSend07)
	ON_BN_CLICKED(IDC_BUTTON_SR08, OnButtonSrSend08)
	ON_BN_CLICKED(IDC_BUTTON_SR09, OnButtonSrSend09)
	ON_BN_CLICKED(IDC_BUTTON_SR10, OnButtonSrSend10)
	ON_BN_CLICKED(IDC_BUTTON_SR11, OnButtonSrSend11)
	ON_BN_CLICKED(IDC_BUTTON_SR12, OnButtonSrSend12)
	ON_BN_CLICKED(IDC_BUTTON_SR13, OnButtonSrSend13)
	ON_BN_CLICKED(IDC_BUTTON_SR14, OnButtonSrSend14)
	ON_BN_CLICKED(IDC_BUTTON_SR15, OnButtonSrSend15)
	ON_BN_CLICKED(IDC_BUTTON_SR16, OnButtonSrSend16)
	ON_BN_CLICKED(IDC_BUTTON_SR17, OnButtonSrSend17)
	ON_BN_CLICKED(IDC_BUTTON_SR18, OnButtonSrSend18)
	ON_BN_CLICKED(IDC_BUTTON_SR19, OnButtonSrSend19)
	ON_BN_CLICKED(IDC_BUTTON_SR20, OnButtonSrSend20)
	ON_BN_CLICKED(IDC_CHECK_SR01, OnCheckSrSend01)
	ON_BN_CLICKED(IDC_CHECK_SR02, OnCheckSrSend02)
	ON_BN_CLICKED(IDC_CHECK_SR03, OnCheckSrSend03)
	ON_BN_CLICKED(IDC_CHECK_SR04, OnCheckSrSend04)
	ON_BN_CLICKED(IDC_CHECK_SR05, OnCheckSrSend05)
	ON_BN_CLICKED(IDC_CHECK_SR06, OnCheckSrSend06)
	ON_BN_CLICKED(IDC_CHECK_SR07, OnCheckSrSend07)
	ON_BN_CLICKED(IDC_CHECK_SR08, OnCheckSrSend08)
	ON_BN_CLICKED(IDC_CHECK_SR09, OnCheckSrSend09)
	ON_BN_CLICKED(IDC_CHECK_SR10, OnCheckSrSend10)
	ON_BN_CLICKED(IDC_CHECK_SR11, OnCheckSrSend11)
	ON_BN_CLICKED(IDC_CHECK_SR12, OnCheckSrSend12)
	ON_BN_CLICKED(IDC_CHECK_SR13, OnCheckSrSend13)
	ON_BN_CLICKED(IDC_CHECK_SR14, OnCheckSrSend14)
	ON_BN_CLICKED(IDC_CHECK_SR15, OnCheckSrSend15)
	ON_BN_CLICKED(IDC_CHECK_SR16, OnCheckSrSend16)
	ON_BN_CLICKED(IDC_CHECK_SR17, OnCheckSrSend17)
	ON_BN_CLICKED(IDC_CHECK_SR18, OnCheckSrSend18)
	ON_BN_CLICKED(IDC_CHECK_SR19, OnCheckSrSend19)
	ON_BN_CLICKED(IDC_CHECK_SR20, OnCheckSrSend20)
	ON_WM_CLOSE()
	ON_COMMAND(IDC_MENU_TRAY_EXIT, OnMenuTrayExit)
	ON_COMMAND(IDC_MENU_TRAY_HIDE, OnMenuTrayHide)
	ON_COMMAND(IDC_MENU_TRAY_SHOW, OnMenuTrayShow)
	ON_MESSAGE(MYWM_NOTIFYICON, OnMyIconNotify)
	ON_BN_CLICKED(IDC_CHECK_RETURN, OnCheckReturn)
	ON_BN_CLICKED(IDC_CHECK_SHOWTIME, OnCheckShowTime)
	ON_COMMAND(IDC_MENU_TRAY_ABOUT, OnMenuTrayAbout)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
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
	EASYSIZE(IDC_BUTTON_HELP,    ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,        ES_BORDER,       0)
	EASYSIZE(IDC_STATIC_EX02,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_BORDER,       0)
	EASYSIZE(IDC_BUTTON_SEND,    ES_KEEPSIZE,        ES_KEEPSIZE,        ES_BORDER,          IDC_STATIC_SEND, 0)
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
	// ��������չ�����������������ؼ�����������
	EASYSIZE(IDC_STATIC_LABLE,   ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_STATIC_SRAUTO,  ES_KEEPSIZE,        IDC_STATIC_SRAUTO,  ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SRAUTO,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SRAUTO,   ES_KEEPSIZE,        IDC_EDIT_SRAUTO,    ES_BORDER,          ES_KEEPSIZE,     0)
END_EASYSIZE_MAP


/* ==================================== �Զ��庯����--��ʼ ===================================== */

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
**  ��������:  SetSrSendCtrlStatus
**  ��������:  ���ø߼��������ؼ���״̬
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::SetSrSendCtrlStatus(bool Enable)
{
	GetDlgItem(IDC_CHECK_SRAUTO)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_SRAUTO)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_SRAUTO)->EnableWindow(Enable);
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
		TempCStr = TempCStr.Right(3);                                // ��ȡ�ұ���Чλ
		ResultCStr += TempCStr;
	}
	
	return ResultCStr;
}

/**************************************************************************************************
**  ��������:  SaveEditContent
**  ��������:  ����༭������ݵ��ı��ļ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
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

/**************************************************************************************************
**  ��������:  UpdateEditDisplay
**  ��������:  ���±༭�����ʾ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::UpdateEditDisplay(void)
{
	CWnd *hwnd;
	
	if (m_Check_HexDspl) {                                           // �����Ҫ16������ʾ������ת��

		m_Edit_Recv = TransformtoHex(StrRecved);
		SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);          // �ñ༭�����ݹ��������һ��

		if (m_Check_AutoClear) {                                     // �����Ҫ�Զ��������

			if (RecvedData >= MaxRecvLines) {                        // ��16����ģʽ�£����������ݳ��Ƚ����ж�

				RecvedLine = 0;                                      // ������ձ���ֵ
				RecvedData = 0;
				
				if (m_Check_AutoSave) {
					SaveEditContent();                               // ����༭�������
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
			
            if (RecvedLine >= MaxRecvLines) {                        // ���ַ�ģʽ�£����������������ж�

				RecvedLine = 0;                                      // ������ձ���ֵ
				RecvedData = 0;
				
				if (m_Check_AutoSave) {
					SaveEditContent();                               // ����༭�������
				}

				StrRecved   = "";
				m_Edit_Recv = "";
				SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);          // ��ձ༭������
			}
		}
	}

	/*************************************************************************************************\
	|                          �������ʵ�ֶԽ��ձ༭��������������������                           |
    \*************************************************************************************************/
	
	hwnd = GetDlgItem(IDC_EDIT_RECV);                                // ��ȡ���ձ༭��Ŀؼ�ID

	if (GetFocus() == hwnd) {                                        // �����ڽ���ת�������ͱ༭��
		GetDlgItem(IDC_EDIT_SEND)->SetFocus();
	}
}

/**************************************************************************************************
**  ��������:  HandleUSARTData
**  ��������:  ��ʱ���մ������ݲ���ʾ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::HandleUSARTData(void)
{
    VARIANT       Input_Vrt;
    COleSafeArray Input_Ary;
    LONG          RecvLen, i;
    BYTE          RecvData[2048];                                    // ����BYTE����
    CString       TimeStr, TempStr;
	CTime         NowTime;
	
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
			
            BYTE bt = *(char *)(RecvData + i);                       // ��ȡ�����ַ�
			
			//if (bt == 0) {                                         // ת��Ϊ�ַ���
			//	TempStr = CString(bt);
			//} else {
			//	TempStr.Format("%c", bt);
			//}

			TempStr.Format("%c", bt);
			
			if (m_Check_ShowTime == TRUE) {                          // ֻ��������ʱ����ʾ����ʱ���ж�
				
				if (TempStr == "\n") {                               // ���ν��յ��˻س������л�����һ����ʾ
					m_NeedTime = TRUE;
					RecvedLine++;
				} else {
					if (m_NeedTime == TRUE) {
						NowTime = CTime::GetCurrentTime();	         // ��ȡ����ʱ��
						TimeStr = NowTime.Format("[%H:%M:%S] ");
						
						StrRecved += TimeStr;                        // ����ͷ��ʾʱ��
						m_NeedTime = FALSE;
					}
				}
			} else {                                                 // ����Ҫ����ͷλ����ʾʱ��
				
				if (m_Check_HexDspl == FALSE) {                      // 16����ģʽ�²������ж�

					if (TempStr == "\n") {                           // ���ν��յ��س���
						RecvedLine++;
					}
				} else {

					RecvedLine = 0;                                  // 
				}
			}
			
			StrRecved += TempStr;                                    // ������������
			RecvedData++;                                            // �����ֽ����ۼ�
        }
    }
	
    UpdateEditDisplay();                                             // ���±༭��������ʾ
    
    UpdateStatusBarNow();                                            // ����״̬��ͳ�����ݵ���ʾ
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

		SetTimer(Timer_No_AutoSend, Timer, NULL);                    // ������ʱ��

		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);

		m_Edit_AutoTimer = TempStr;                                  // ���±༭������
		SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);

		SetSendButtonStatus(FALSE);                                  // ���÷�����������ť

	} else {

		MessageBox("��ʱʱ�������0��100����֮�䣬��ȷ�ϣ�  ", "��ʾ", MB_OK + MB_ICONEXCLAMATION);

		SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);            // ��ԭ�༭������

		m_Check_AutoSend = FALSE;
		UpdateData(FALSE);                                           // ȡ����ѡ��ѡ�е�״̬

		return;
	}
}

/**************************************************************************************************
**  ��������:  NeedLoopSendData
**  ��������:  ����ѭ���������ݵĹ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::NeedLoopSendData(void)
{
	int Timer;
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SRAUTO, TempStr);
	
	Timer = atoi((LPSTR)(LPCTSTR)TempStr);
	
	if ((Timer > 0) && (Timer <= 10000)) {
		
		SetTimer(Timer_No_LoopSend, Timer, NULL);                    // ������ʱ��
		Loop_Counter = 0;
		
		GetDlgItem(IDC_EDIT_SRAUTO)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_SRAUTO)->EnableWindow(FALSE);
		
		m_Edit_LoopTimer = TempStr;                                  // ���±༭������
		SetDlgItemText(IDC_EDIT_SRAUTO, m_Edit_LoopTimer);
		
	} else {
		
		MessageBox("��ʱʱ�������0��10����֮�䣬��ȷ�ϣ�  ", "��ʾ", MB_OK + MB_ICONEXCLAMATION);
		
		SetDlgItemText(IDC_EDIT_SRAUTO, m_Edit_LoopTimer);           // ��ԭ�༭������
		
		m_Check_LoopSend = FALSE;
		UpdateData(FALSE);                                           // ȡ����ѡ��ѡ�е�״̬
		
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

	this->GetWindowRect(&DialogMain);                                // ��ȡ����������Ļ�ϵ�λ��
	
	if (DialogMain.Width() < 900) {
		DisplayStr = " ��ӭʹ��MySScom";	
		m_StatusBar.SetPaneText(0, DisplayStr);
	} else if ((DialogMain.Width() >= 900) && (DialogMain.Width() < 1050)) {
		DisplayStr = " ��ӭʹ��MySScom - Designed By LEON";	
		m_StatusBar.SetPaneText(0, DisplayStr);
	} else if ((DialogMain.Width() >= 1050) && (DialogMain.Width() < 1200)) {
		DisplayStr = " ��ӭʹ��MySScom - Designed By LEON (QQ: 39110103)";	
		m_StatusBar.SetPaneText(0, DisplayStr);
	} else if ((DialogMain.Width() >= 1200) && (DialogMain.Width() < 1350)) {
		DisplayStr = " ��ӭʹ��MySScom - Designed By LEON (QQ: 39110103, LEON1741@126.com)";	
		m_StatusBar.SetPaneText(0, DisplayStr);
	} else {
		DisplayStr = " ��ӭʹ��MySScom - Designed By LEON (QQ: 39110103, LEON1741@126.com. \"Never Stop Trying\"!)";	
		m_StatusBar.SetPaneText(0, DisplayStr);
	}
	
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
	int  TempData;                                                   // ��Ҫע����ǣ��Զ�����ʹ�ܺ�ѭ������ʹ�����������ʼ��
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

	m_Check_HexDspl   = (::GetPrivateProfileInt("RecvConfig", "HexDispl", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_ShowTime  = (::GetPrivateProfileInt("RecvConfig", "ShowTime", 1, ".\\Settings.ini")) ? TRUE : FALSE;

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

	m_Check_SrSend_01 = (::GetPrivateProfileInt("SrSendArea", "SrHexa01", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_02 = (::GetPrivateProfileInt("SrSendArea", "SrHexa02", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_03 = (::GetPrivateProfileInt("SrSendArea", "SrHexa03", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_04 = (::GetPrivateProfileInt("SrSendArea", "SrHexa04", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_05 = (::GetPrivateProfileInt("SrSendArea", "SrHexa05", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_06 = (::GetPrivateProfileInt("SrSendArea", "SrHexa06", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_07 = (::GetPrivateProfileInt("SrSendArea", "SrHexa07", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_08 = (::GetPrivateProfileInt("SrSendArea", "SrHexa08", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_09 = (::GetPrivateProfileInt("SrSendArea", "SrHexa09", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_10 = (::GetPrivateProfileInt("SrSendArea", "SrHexa10", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_11 = (::GetPrivateProfileInt("SrSendArea", "SrHexa11", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_12 = (::GetPrivateProfileInt("SrSendArea", "SrHexa12", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_13 = (::GetPrivateProfileInt("SrSendArea", "SrHexa13", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_14 = (::GetPrivateProfileInt("SrSendArea", "SrHexa14", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_15 = (::GetPrivateProfileInt("SrSendArea", "SrHexa15", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_16 = (::GetPrivateProfileInt("SrSendArea", "SrHexa16", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_17 = (::GetPrivateProfileInt("SrSendArea", "SrHexa17", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_18 = (::GetPrivateProfileInt("SrSendArea", "SrHexa18", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_19 = (::GetPrivateProfileInt("SrSendArea", "SrHexa19", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	m_Check_SrSend_20 = (::GetPrivateProfileInt("SrSendArea", "SrHexa20", 0, ".\\Settings.ini")) ? TRUE : FALSE;
	
	::GetPrivateProfileString("SrSendArea", "SrData01", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR01, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData02", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR02, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData03", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR03, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData04", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR04, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData05", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR05, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData06", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR06, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData07", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR07, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData08", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR08, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData09", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR09, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData10", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR10, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData11", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR11, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData12", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR12, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData13", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR13, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData14", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR14, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData15", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR15, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData16", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR16, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData17", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR17, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData18", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR18, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData19", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR19, TempPara);
	::GetPrivateProfileString("SrSendArea", "SrData20", "", TempStr, MAX_LOOP_BYTE, ".\\Settings.ini");
	TempPara.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SR20, TempPara);

	::GetPrivateProfileString("SrSendArea", "LoopTime", "1000", TempStr, 5, ".\\Settings.ini");
	m_Edit_LoopTimer.Format("%s", TempStr);
	SetDlgItemText(IDC_EDIT_SRAUTO, TempPara);

	if (m_Check_HexDspl) {                                           // ���ݶ���Ĳ���ֵ��ʼ����ʾ������
		SetDlgItemText(IDC_STATIC_LINES, "�ַ�");
	} else {
		SetDlgItemText(IDC_STATIC_LINES, "��");
	}
	
	UpdateData(FALSE);                                               // ���±༭������
}

/**************************************************************************************************
**  ��������:  RecordAllParas
**  ��������:  ���Ի����и���������ֵ��¼�������ļ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::RecordAllParas(void)
{
	int TempData;                                          // ��Ҫע����ǣ��Զ�����ʹ�ܺ�ѭ������ʹ���������뱣��
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

	::WritePrivateProfileString("SrSendArea", "SrHexa01",  m_Check_SrSend_01 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa02",  m_Check_SrSend_02 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa03",  m_Check_SrSend_03 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa04",  m_Check_SrSend_04 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa05",  m_Check_SrSend_05 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa06",  m_Check_SrSend_06 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa07",  m_Check_SrSend_07 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa08",  m_Check_SrSend_08 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa09",  m_Check_SrSend_09 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa10",  m_Check_SrSend_10 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa11",  m_Check_SrSend_11 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa12",  m_Check_SrSend_12 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa13",  m_Check_SrSend_13 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa14",  m_Check_SrSend_14 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa15",  m_Check_SrSend_15 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa16",  m_Check_SrSend_16 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa17",  m_Check_SrSend_17 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa18",  m_Check_SrSend_18 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa19",  m_Check_SrSend_19 ? "1" : "0", ".\\Settings.ini");
	::WritePrivateProfileString("SrSendArea", "SrHexa20",  m_Check_SrSend_20 ? "1" : "0", ".\\Settings.ini");

	GetDlgItemText(IDC_EDIT_SR01, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData01", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR02, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData02", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR03, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData03", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR04, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData04", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR05, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData05", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR06, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData06", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR07, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData07", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR08, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData08", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR09, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData09", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR10, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData10", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR11, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData11", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR12, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData12", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR13, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData13", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR14, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData14", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR15, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData15", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR16, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData16", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR17, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData17", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR18, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData18", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR19, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData19", ParaStr, ".\\Settings.ini");
	GetDlgItemText(IDC_EDIT_SR20, ParaStr);
	::WritePrivateProfileString("SrSendArea", "SrData20", ParaStr, ".\\Settings.ini");

	GetDlgItemText(IDC_EDIT_SRAUTO, ParaStr);
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
	m_StatusBar.SetPaneText(0, " ��ӭʹ��MySScom");
	
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
	EnumComm();                                                      // ö�ٿ��õĴ���

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
	CString TempStr;
	
	for (int i = 0; i < (sizeof(Combo_Stop) / sizeof(Combo_Stop[0])); i++) {
		
		TempStr.Format("%d λ", Combo_Stop[i]);
		
		m_Combo_Stop.AddString(TempStr);
	}
}

/**************************************************************************************************
**  ��������:  InitiateMainFrame
**  ��������:  ��ʼ�������ڵ�λ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateMainFrame(void)
{
	CRect DialogMain;

	this->GetWindowRect(&DialogMain);                                // ��ȡ����������Ļ�ϵ�λ��

	this->MoveWindow((DialogMain.left), (DialogMain.top), (DialogMain.Width()), (DialogMain.Height()));
}

/**************************************************************************************************
**  ��������:  InitiateSrSendArea
**  ��������:  ��ʼ���߼�����������ʾ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::InitiateSrSendArea(void)
{
	m_SrSendEnable = FALSE;

	HideSrSendArea();                                                // Ĭ��״̬�²���ʾ�߼����͹���

	OnButtonSrSend();                                                // Ŀǰ����ֳ�����ʾʱ��������λ���е�ƫ��
	OnButtonSrSend();                                                // ͨ���������������л�������ʱ��������BUG
}

/**************************************************************************************************
**  ��������:  SendEditDatatoComm
**  ��������:  ���༭���ڵ����ݷ��͵�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::SendEditDatatoComm(void)
{
	assert(m_SrSendEnable == FALSE);
	
	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);                      // ��ȡ�༭�������
	
	if (m_Edit_Send.GetLength() > MAX_SEND_BYTE) {                   // ���ݳ��ȹ���
		
		MessageBox("�������ݹ������ύ����ʧ��......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}

	if (m_Check_HexSend) {                                           // �����Ҫ��16���Ʒ���
		
		CByteArray hexdata;
		int len;                                                     // �˴����ص�len�������ڼ��㷢���˶��ٸ�ʮ��������
		
		len = String2Hex(m_Edit_Send, hexdata);
		m_ctrlComm.SetOutput(COleVariant(hexdata));                  // ����ʮ����������
		SendedData += len;                                           // �����ֽ����ۼ�
		
	} else {
		
		m_ctrlComm.SetOutput(COleVariant(m_Edit_Send));              // ����ASCII�ַ�����
		SendedData += m_Edit_Send.GetLength();                       // �����ֽ����ۼ�
	}

	if (m_Check_Return) {                                            // �����س����з�
		m_ctrlComm.SetOutput(COleVariant("\r"));
		m_ctrlComm.SetOutput(COleVariant("\n"));
		SendedData += 2;
	}

	UpdateStatusBarNow();                                            // ����״̬��ͳ�����ݵ���ʾ
}

/**************************************************************************************************
**  ��������:  ShowSrSendCheck
**  ��������:  ��ʾ�߼��������ڵ�check�ؼ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
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

/**************************************************************************************************
**  ��������:  ShowSrSendEdit
**  ��������:  ��ʾ�߼��������ڵ�edit�ؼ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
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

/**************************************************************************************************
**  ��������:  ShowSrSendButton
**  ��������:  ��ʾ�߼��������ڵ�button�ؼ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
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

/**************************************************************************************************
**  ��������:  ShowSrSendOthers
**  ��������:  ��ʾ�߼��������ڵ������ؼ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::ShowSrSendOthers(bool Enable)
{
	GetDlgItem(IDC_STATIC_SRSEND)->ShowWindow(Enable);
	GetDlgItem(IDC_STATIC_LABLE)->ShowWindow(Enable);
	
	GetDlgItem(IDC_STATIC_EX02)->ShowWindow(Enable);

	GetDlgItem(IDC_CHECK_SRAUTO)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SRAUTO)->ShowWindow(Enable);
	GetDlgItem(IDC_STATIC_SRAUTO)->ShowWindow(Enable);
}

/**************************************************************************************************
**  ��������:  HideSrSendArea
**  ��������:  ���ظ߼�������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::HideSrSendArea(void)
{
	CRect DialogMain, RecvEdit, SendEdit, SendButton;
	CRect RecvStatic, SendStatic, SrSdStatic, ControlStatic;
	
	this->GetWindowRect(&DialogMain);                                // ��ȡ����������Ļ�ϵ�λ��
	
	if ((s_top_offset == 0) && (s_left_offset == 0)) {               // ���ݲ�ͬ����߿��С����ƫ����

		s_top_offset  = 23 + DialogMain.bottom - MIN_FRAME_OFFSET;
		s_left_offset = 4;
	}
	
	GetDlgItem(IDC_STATIC_CONTROL)->GetWindowRect(&ControlStatic);
	GetDlgItem(IDC_STATIC_CONTROL)->MoveWindow((ControlStatic.left - DialogMain.left - s_left_offset), 
		                                       (ControlStatic.top - DialogMain.top - s_top_offset), 
		                                       (ControlStatic.Width()), 
	                          	               (ControlStatic.Height()));
	
	GetDlgItem(IDC_STATIC_SRSEND)->GetWindowRect(&SrSdStatic);
	GetDlgItem(IDC_STATIC_SRSEND)->MoveWindow((SrSdStatic.left - DialogMain.left - s_left_offset), 
		                                      (SrSdStatic.top - DialogMain.top - s_top_offset), 
		                                      (SrSdStatic.Width()), 
		                                      (SrSdStatic.Height()));
	
	GetDlgItem(IDC_STATIC_RECEIVE)->GetWindowRect(&RecvStatic);
	GetDlgItem(IDC_STATIC_RECEIVE)->MoveWindow((RecvStatic.left - DialogMain.left - s_left_offset), 
											   (ControlStatic.top - DialogMain.top - s_top_offset), 
		                                       (RecvStatic.Width() + SrSdStatic.Width() + 10), 
											   (RecvStatic.Height()));
	
	GetDlgItem(IDC_EDIT_RECV)->GetWindowRect(&RecvEdit);
	GetDlgItem(IDC_EDIT_RECV)->MoveWindow((RecvEdit.left - DialogMain.left - s_left_offset), 
		                                  (ControlStatic.top - DialogMain.top - s_top_offset + 20), 
		                                  (RecvEdit.Width() + SrSdStatic.Width() + 10), 
										  (RecvEdit.Height()));

	GetDlgItem(IDC_STATIC_SEND)->GetWindowRect(&SendStatic);
	GetDlgItem(IDC_STATIC_SEND)->MoveWindow((SendStatic.left - DialogMain.left - s_left_offset), 
	                                        (RecvEdit.bottom - DialogMain.top - s_top_offset + 16), 
	                                        (SendStatic.Width() + SrSdStatic.Width() + 10), 
											(SendStatic.Height()));

	GetDlgItem(IDC_EDIT_SEND)->GetWindowRect(&SendEdit);
	GetDlgItem(IDC_EDIT_SEND)->MoveWindow((SendEdit.left - DialogMain.left - s_left_offset), 
	                                      (SendStatic.top - DialogMain.top - s_top_offset + 20), 
		                                  (SendEdit.Width() + SrSdStatic.Width() + 10), 
										  (SendEdit.Height()));

	GetDlgItem(IDC_BUTTON_SEND)->GetWindowRect(&SendButton);
	GetDlgItem(IDC_BUTTON_SEND)->MoveWindow((SendEdit.left - DialogMain.left + SendEdit.Width() + 258), 
											(SendStatic.top - DialogMain.top - s_top_offset + 16), 
											(SendButton.Width()), (SendButton.Height()));

	ShowSrSendCheck(FALSE);
	ShowSrSendEdit(FALSE);
	ShowSrSendButton(FALSE);
	ShowSrSendOthers(FALSE);
}

/**************************************************************************************************
**  ��������:  ShowSrSendArea
**  ��������:  ��ʾ�߼�������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::ShowSrSendArea(void)
{
	CRect DialogMain, RecvEdit, SendEdit, SendButton;
	CRect RecvStatic, SendStatic, SrSdStatic, ControlStatic;
	
	this->GetWindowRect(&DialogMain);                                // ��ȡ����������Ļ�ϵ�λ��

	GetDlgItem(IDC_STATIC_CONTROL)->GetWindowRect(&ControlStatic);
	GetDlgItem(IDC_STATIC_CONTROL)->MoveWindow((ControlStatic.left - DialogMain.left - s_left_offset), 
		                                       (ControlStatic.top - DialogMain.top - s_top_offset), 
		                                       (ControlStatic.Width()), 
	                                      	   (ControlStatic.Height()));
	
	GetDlgItem(IDC_STATIC_SRSEND)->GetWindowRect(&SrSdStatic);
	GetDlgItem(IDC_STATIC_SRSEND)->MoveWindow((SrSdStatic.left - DialogMain.left - s_left_offset), 
		                                      (SrSdStatic.top - DialogMain.top - s_top_offset), 
	 	                                      (SrSdStatic.Width()), 
		                                      (SrSdStatic.Height()));
	
	GetDlgItem(IDC_STATIC_RECEIVE)->GetWindowRect(&RecvStatic);
	GetDlgItem(IDC_STATIC_RECEIVE)->MoveWindow((RecvStatic.left - DialogMain.left - s_left_offset), 
											   (ControlStatic.top - DialogMain.top - s_top_offset), 
		                                       (RecvStatic.Width() - SrSdStatic.Width() - 10), 
											   (RecvStatic.Height()));
	
	GetDlgItem(IDC_EDIT_RECV)->GetWindowRect(&RecvEdit);
	GetDlgItem(IDC_EDIT_RECV)->MoveWindow((RecvEdit.left - DialogMain.left - s_left_offset), 
		                                  (ControlStatic.top - DialogMain.top - s_top_offset + 20), 
		                                  (RecvEdit.Width() - SrSdStatic.Width() - 10), 
										  (RecvEdit.Height()));

	GetDlgItem(IDC_STATIC_SEND)->GetWindowRect(&SendStatic);
	GetDlgItem(IDC_STATIC_SEND)->MoveWindow((SendStatic.left - DialogMain.left - s_left_offset), 
	                                        (RecvEdit.bottom - DialogMain.top - s_top_offset + 16), 
	                                        (SendStatic.Width() - SrSdStatic.Width() - 10), 
											(SendStatic.Height()));

	GetDlgItem(IDC_EDIT_SEND)->GetWindowRect(&SendEdit);
	GetDlgItem(IDC_EDIT_SEND)->MoveWindow((SendEdit.left - DialogMain.left - s_left_offset), 
	                                      (SendStatic.top - DialogMain.top - s_top_offset + 20), 
		                                  (SendEdit.Width() - SrSdStatic.Width() - 10), 
										  (SendEdit.Height()));

	GetDlgItem(IDC_BUTTON_SEND)->GetWindowRect(&SendButton);
	GetDlgItem(IDC_BUTTON_SEND)->MoveWindow((SendEdit.left - DialogMain.left + SendEdit.Width() - 258), 
											(SendStatic.top - DialogMain.top - s_top_offset + 16), 
											(SendButton.Width()), (SendButton.Height()));
	
	ShowSrSendCheck(TRUE);
	ShowSrSendEdit(TRUE);
	ShowSrSendButton(TRUE);
	ShowSrSendOthers(TRUE);
}

/**************************************************************************************************
**  ��������:  SrEditDataValid
**  ��������:  �ж�edit�ؼ��ڵ������Ƿ���Ч
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CMySScomDlg::SrEditDataValid(int EditID)
{
	assert(m_SrSendEnable == TRUE);
	
	CString EditStr;
	
	GetDlgItemText(EditID, EditStr);
	
	if (EditStr.GetLength() > 0) {                                   // �жϱ༭�����ݵĳ����Ƿ���Ч
		return TRUE;
	} else {
		return FALSE;
	}
}

/**************************************************************************************************
**  ��������:  GetSrValidDataNo
**  ��������:  ��ȡ�߼���������edit�ؼ���������Ч�Ŀؼ�ID
**  �������:  
**  ���ز���:  
**************************************************************************************************/
int CMySScomDlg::GetSrValidDataNo(void)
{
	assert(m_SrSendEnable == TRUE);
	
	if (SrEditDataValid(IDC_EDIT_SR01) == TRUE) {
		return IDC_EDIT_SR01;
	} else if (SrEditDataValid(IDC_EDIT_SR02) == TRUE) {
		return IDC_EDIT_SR02;
	} else if (SrEditDataValid(IDC_EDIT_SR03) == TRUE) {
		return IDC_EDIT_SR03;
	} else if (SrEditDataValid(IDC_EDIT_SR04) == TRUE) {
		return IDC_EDIT_SR04;
	} else if (SrEditDataValid(IDC_EDIT_SR05) == TRUE) {
		return IDC_EDIT_SR05;
	} else if (SrEditDataValid(IDC_EDIT_SR06) == TRUE) {
		return IDC_EDIT_SR06;
	} else if (SrEditDataValid(IDC_EDIT_SR07) == TRUE) {
		return IDC_EDIT_SR07;
	} else if (SrEditDataValid(IDC_EDIT_SR08) == TRUE) {
		return IDC_EDIT_SR08;
	} else if (SrEditDataValid(IDC_EDIT_SR09) == TRUE) {
		return IDC_EDIT_SR09;
	} else if (SrEditDataValid(IDC_EDIT_SR10) == TRUE) {
		return IDC_EDIT_SR10;
	} else if (SrEditDataValid(IDC_EDIT_SR11) == TRUE) {
		return IDC_EDIT_SR11;
	} else if (SrEditDataValid(IDC_EDIT_SR12) == TRUE) {
		return IDC_EDIT_SR12;
	} else if (SrEditDataValid(IDC_EDIT_SR13) == TRUE) {
		return IDC_EDIT_SR13;
	} else if (SrEditDataValid(IDC_EDIT_SR14) == TRUE) {
		return IDC_EDIT_SR14;
	} else if (SrEditDataValid(IDC_EDIT_SR15) == TRUE) {
		return IDC_EDIT_SR15;
	} else if (SrEditDataValid(IDC_EDIT_SR16) == TRUE) {
		return IDC_EDIT_SR16;
	} else if (SrEditDataValid(IDC_EDIT_SR17) == TRUE) {
		return IDC_EDIT_SR17;
	} else if (SrEditDataValid(IDC_EDIT_SR18) == TRUE) {
		return IDC_EDIT_SR18;
	} else if (SrEditDataValid(IDC_EDIT_SR19) == TRUE) {
		return IDC_EDIT_SR19;
	} else if (SrEditDataValid(IDC_EDIT_SR20) == TRUE) {
		return IDC_EDIT_SR20;
	} else {
		return 0;                                                    // ����������Ч�ı༭�����ţ�ȫ��Ч�򷵻�0
	}
}

/**************************************************************************************************
**  ��������:  TrytoSrSendData
**  ��������:  ���Է��͸߼��������ڵ�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::TrytoSrSendData(CString InputStr, BOOL NeedHex)
{
	assert(m_SrSendEnable == TRUE);
	
	if (InputStr.GetLength() <= 0) {
		MessageBox("���ʹ�������Ϊ�գ�δ�����κ����ݣ�  ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	if (NeedHex == TRUE) {                                           // �����Ҫ��16���Ʒ���
		
		CByteArray SendData;
		int len;                                                     // �˴����ص�len�������ڼ��㷢���˶��ٸ�ʮ��������
		
		len = String2Hex(InputStr, SendData);
		
		m_ctrlComm.SetOutput(COleVariant(SendData));                 // ����ʮ����������
		
		SendedData += len;                                           // �����ֽ����ۼ�

		m_Check_HexSend = TRUE;                                      // ������ͬ�����Ƶ�������
		m_Edit_Send = InputStr;
		SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
		
	} else {
		
		m_ctrlComm.SetOutput(COleVariant(InputStr));                 // ����ASCII�ַ�����
		
		SendedData += InputStr.GetLength();                          // �����ֽ����ۼ�

		m_Check_HexSend = FALSE;                                     // ������ͬ�����Ƶ�������
		m_Edit_Send = InputStr;
		SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
	}

	if (m_Check_Return) {                                            // �����س����з�
		m_ctrlComm.SetOutput(COleVariant("\r"));
		m_ctrlComm.SetOutput(COleVariant("\n"));
		SendedData += 2;
	}
	
	UpdateStatusBarNow();                                            // ����״̬��ͳ�����ݵ���ʾ

	UpdateData(FALSE);
}

/**************************************************************************************************
**  ��������:  ContinueLoopSrSend
**  ��������:  �Ը߼��������ڵ����ݽ���ѭ������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::ContinueLoopSrSend(void)
{
	assert(m_SrSendEnable == TRUE);

	for (; ;) {                                                      // �����ж�ÿ���༭��������Ƿ���Ч��������֮
		
		if ((Loop_Counter < IDC_EDIT_SR01) && (SrEditDataValid(IDC_EDIT_SR01) == TRUE)) {		
			OnButtonSrSend01();
			Loop_Counter = IDC_EDIT_SR01;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR02) && (SrEditDataValid(IDC_EDIT_SR02) == TRUE)) {
			OnButtonSrSend02();
			Loop_Counter = IDC_EDIT_SR02;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR03) && (SrEditDataValid(IDC_EDIT_SR03) == TRUE)) {
			OnButtonSrSend03();
			Loop_Counter = IDC_EDIT_SR03;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR04) && (SrEditDataValid(IDC_EDIT_SR04) == TRUE)) {
			OnButtonSrSend04();
			Loop_Counter = IDC_EDIT_SR04;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR05) && (SrEditDataValid(IDC_EDIT_SR05) == TRUE)) {
			OnButtonSrSend05();
			Loop_Counter = IDC_EDIT_SR05;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR06) && (SrEditDataValid(IDC_EDIT_SR06) == TRUE)) {
			OnButtonSrSend06();
			Loop_Counter = IDC_EDIT_SR06;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR07) && (SrEditDataValid(IDC_EDIT_SR07) == TRUE)) {
			OnButtonSrSend07();
			Loop_Counter = IDC_EDIT_SR07;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR08) && (SrEditDataValid(IDC_EDIT_SR08) == TRUE)) {
			OnButtonSrSend08();
			Loop_Counter = IDC_EDIT_SR08;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR09) && (SrEditDataValid(IDC_EDIT_SR09) == TRUE)) {
			OnButtonSrSend09();
			Loop_Counter = IDC_EDIT_SR09;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR10) && (SrEditDataValid(IDC_EDIT_SR10) == TRUE)) {
			OnButtonSrSend10();
			Loop_Counter = IDC_EDIT_SR10;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR11) && (SrEditDataValid(IDC_EDIT_SR11) == TRUE)) {
			OnButtonSrSend11();
			Loop_Counter = IDC_EDIT_SR11;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR12) && (SrEditDataValid(IDC_EDIT_SR12) == TRUE)) {
			OnButtonSrSend12();
			Loop_Counter = IDC_EDIT_SR12;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR13) && (SrEditDataValid(IDC_EDIT_SR13) == TRUE)) {
			OnButtonSrSend13();
			Loop_Counter = IDC_EDIT_SR13;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR14) && (SrEditDataValid(IDC_EDIT_SR14) == TRUE)) {
			OnButtonSrSend14();
			Loop_Counter = IDC_EDIT_SR14;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR15) && (SrEditDataValid(IDC_EDIT_SR15) == TRUE)) {
			OnButtonSrSend15();
			Loop_Counter = IDC_EDIT_SR15;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR16) && (SrEditDataValid(IDC_EDIT_SR16) == TRUE)) {
			OnButtonSrSend16();
			Loop_Counter = IDC_EDIT_SR16;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR17) && (SrEditDataValid(IDC_EDIT_SR17) == TRUE)) {
			OnButtonSrSend17();
			Loop_Counter = IDC_EDIT_SR17;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR18) && (SrEditDataValid(IDC_EDIT_SR18) == TRUE)) {
			OnButtonSrSend18();
			Loop_Counter = IDC_EDIT_SR18;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR19) && (SrEditDataValid(IDC_EDIT_SR19) == TRUE)) {
			OnButtonSrSend19();
			Loop_Counter = IDC_EDIT_SR19;
			break;
		} else if ((Loop_Counter < IDC_EDIT_SR20) && (SrEditDataValid(IDC_EDIT_SR20) == TRUE)) {
			OnButtonSrSend20();
			Loop_Counter = IDC_EDIT_SR20;
			break;
		} else {
			Loop_Counter = 0;
		}
	}
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


/* ================================== �߼����͹��ܴ���--��ʼ =================================== */

/**************************************************************************************************
**  ��������:  
**  ��������:  
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrAuto() 
{
	assert(m_SrSendEnable == TRUE);
	
	m_Check_LoopSend = !m_Check_LoopSend;
	
	if (m_Check_LoopSend) {

		if (GetSrValidDataNo() == 0) {

			MessageBox("ò������δ�����κ���Ҫ�ķ��͵����ݣ����ҷ���ʲô�أ�~~~  ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			
			m_Check_LoopSend = FALSE;
			UpdateData(FALSE);                                       // ȡ����ѡ��ѡ�е�״̬
			
			return;
		}

		SwitchSendStatus(FALSE);
		
		NeedLoopSendData();
		
	} else {
		
		Loop_Counter = 0;
		KillTimer(Timer_No_LoopSend);                                // ȡ���Զ����͹���
		
		GetDlgItem(IDC_EDIT_SRAUTO)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_SRAUTO)->EnableWindow(TRUE);

		SwitchSendStatus(TRUE);
	}
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend01
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend01() 
{
	m_Check_SrSend_01 = !m_Check_SrSend_01;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend02
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend02() 
{
	m_Check_SrSend_02 = !m_Check_SrSend_02;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend03
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend03() 
{
	m_Check_SrSend_03 = !m_Check_SrSend_03;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend04
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend04() 
{
	m_Check_SrSend_04 = !m_Check_SrSend_04;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend05
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend05() 
{
	m_Check_SrSend_05 = !m_Check_SrSend_05;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend06
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend06() 
{
	m_Check_SrSend_06 = !m_Check_SrSend_06;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend07
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend07() 
{
	m_Check_SrSend_07 = !m_Check_SrSend_07;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend08
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend08() 
{
	m_Check_SrSend_08 = !m_Check_SrSend_08;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend09
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend09() 
{
	m_Check_SrSend_09 = !m_Check_SrSend_09;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend10
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend10() 
{
	m_Check_SrSend_10 = !m_Check_SrSend_10;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend11
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend11() 
{
	m_Check_SrSend_11 = !m_Check_SrSend_11;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend12
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend12() 
{
	m_Check_SrSend_12 = !m_Check_SrSend_12;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend13
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend13() 
{
	m_Check_SrSend_13 = !m_Check_SrSend_13;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend14
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend14() 
{
	m_Check_SrSend_14 = !m_Check_SrSend_14;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend15
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend15() 
{
	m_Check_SrSend_15 = !m_Check_SrSend_15;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend16
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend16() 
{
	m_Check_SrSend_16 = !m_Check_SrSend_16;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend17
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend17() 
{
	m_Check_SrSend_17 = !m_Check_SrSend_17;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend18
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend18() 
{
	m_Check_SrSend_18 = !m_Check_SrSend_18;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend19
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend19() 
{
	m_Check_SrSend_19 = !m_Check_SrSend_19;
}

/**************************************************************************************************
**  ��������:  OnCheckSrSend20
**  ��������:  �߼��������ĸ�ѡ����Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend20() 
{
	m_Check_SrSend_20 = !m_Check_SrSend_20;
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend01
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend01() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR01, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_01);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend02
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend02() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR02, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_02);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend03
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend03() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR03, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_03);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend04
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend04() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR04, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_04);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend05
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend05() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR05, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_05);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend06
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend06() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR06, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_06);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend07
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend07() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR07, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_07);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend08
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend08() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR08, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_08);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend09
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend09() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR09, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_09);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend10
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend10() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR10, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_10);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend11
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend11() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR11, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_11);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend12
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend12() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR12, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_12);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend13
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend13() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR13, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_13);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend14
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend14() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR14, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_14);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend15
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend15() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR15, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_15);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend16
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend16() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR16, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_16);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend17
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend17() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR17, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_17);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend18
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend18() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR18, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_18);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend19
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend19() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR19, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_19);
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend20
**  ��������:  �߼��������İ�ť��Ϣ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend20() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR20, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_20);
}


/* ================================== �߼����͹��ܴ���--���� =================================== */


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
	CString TempStr, SettingStr;
    
	if (m_PortOpened == TRUE) {                                      // ��������Ѿ��򿪣���ôִ�йرղ���

		if (m_Check_AutoSend || m_Check_LoopSend) {
			MessageBox("������ͣ���Զ����͹����ٳ��Թرմ���...  ", "��ʾ", MB_OK + MB_ICONEXCLAMATION);
			return;
		}

		m_ctrlComm.SetPortOpen(FALSE);

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

	int Number = m_Combo_ComNo.GetCurSel();                          // �õ����ں�
	
	if (Number == 0) {
		MessageBox("���ںŶ�û��ѡ������Ҵ�ʲô����...��   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
        return;
    }
	
	if (m_ctrlComm.GetPortOpen()) {                                  // �ж��Ƿ��Ѿ���
        m_ctrlComm.SetPortOpen(FALSE);
	}
	
	m_Combo_ComNo.GetLBText(Number, TempStr);
	TempStr.TrimLeft("COM");                                         // ɾ��"COM"�ֶ�
	
	m_ctrlComm.SetCommPort(atoi(TempStr.Mid(0)));                    // ָ�����ں�
	
    if (!m_ctrlComm.GetPortOpen()) {

        m_ctrlComm.SetPortOpen(TRUE);                                // ���Դ򿪴���

		SettingStr = "";
		
		int ComBaudSel = m_Combo_Baud.GetCurSel();                   // ��ȡ�����ʵ�ѡ����
		TempStr.Format("%d", Combo_Baud[ComBaudSel]);
		SettingStr += TempStr;

		SettingStr += ",";

		int ComCheckSel = m_Combo_Check.GetCurSel();                 // ��ȡУ��λ��ѡ����
		TempStr.Format("%c", Combo_Check[ComCheckSel]);
		SettingStr += TempStr;
		
		SettingStr += ",";
		
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
		GetDlgItem(IDC_COMBO_CHECK)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);		

	} else {

        MessageBox("�򿪴���ʧ�ܣ��ô��ڿ�������ʹ����...   ", "��ʾ", MB_OK + MB_ICONERROR);
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
		SetDlgItemText(IDC_BUTTON_PAUSE, "��ͣ����");
		GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(TRUE);
	} else {
		m_bRecvPause = FALSE;
		SetDlgItemText(IDC_BUTTON_PAUSE, "�ָ�����");
		GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(FALSE);
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
		m_NeedTime = TRUE;                                           // ��һ���յ�����ʱ��ʾʱ��
	}

	RecvedLine = 0;
	RecvedData = 0;
	UpdateStatusBarNow();                                            // ����״̬����ͳ��������ʾ
}

/**************************************************************************************************
**  ��������:  OnButtonSave
**  ��������:  �����յ������ݱ��浽�ļ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
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
	
	MyFile.Write(m_Edit_Recv, nLength);	                             // д���ı��ļ�
	MyFile.Close();	                                                 // �ر��ļ�
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

	SendEditDatatoComm();
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

	UpdateStatusBarNow();                                            // ����״̬����ͳ��������ʾ
}

/**************************************************************************************************
**  ��������:  OnButtonSrSend
**  ��������:  �Ƿ���ʾ�߼����ʹ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend() 
{
	if (m_SrSendEnable == TRUE) {                                    // ����Ѿ����ø߼����͹��ܣ������֮

		if (m_Check_LoopSend) {

			MessageBox("�Զ����͹����ѿ���������ͣ��֮�� ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			return;
		}

		HideSrSendArea();

		m_SrSendEnable = FALSE;

		SetDlgItemText(IDC_BUTTON_SRSEND, "�߼�����");

	} else {                                                         // ���û�����ø߼����͹��ܣ�������֮

		if (m_Check_AutoSend) {

			MessageBox("�Զ����͹����ѿ���������ͣ��֮�� ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			return;
		}

		ShowSrSendArea();

		m_SrSendEnable = TRUE;

		SetDlgItemText(IDC_BUTTON_SRSEND, "��ͨ����");
	}
	
	INIT_EASYSIZE;                                                   // ���³�ʼ�������ؼ���λ��
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

		UpdateEditDisplay();                                             // ������ʾ
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
        SetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                // ��ԭ�༭������
        m_Check_AutoClear = FALSE;        
        UpdateData(FALSE);
        return;
    }

    GetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                    // ��ȡ���ݲ�����
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
	assert(m_SrSendEnable == FALSE);
	
	m_Check_AutoSend = !m_Check_AutoSend;

	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);

	if (m_Edit_Send.GetLength() <= 0) {
		MessageBox("ò�Ʒ�����Ϊ�հɣ��������������ҷ���ʲô������ ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		m_Check_AutoSend = FALSE;
		UpdateData(FALSE);
		return;
	}

	if (m_Check_AutoSend) {

		if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {              // ȷ����������ݲ������

			MessageBox("����������ݹ������ύ��������ʧ��......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			m_Check_AutoSend = FALSE;
			UpdateData(FALSE);
			return;
		}

		SetSrSendCtrlStatus(FALSE);

		NeedAutoSendData();                                          // ��ʼ�����Զ���������

	} else {

		KillTimer(Timer_No_AutoSend);                                // �����û�ȡ�����Զ����͵Ĺ���
		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);

		SetSrSendCtrlStatus(TRUE);

		SetSendButtonStatus(TRUE);                                   // �������÷�����������ť
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
	RecordAllParas();                                                // ���������������
	
	TaskBarDeleteIcon(GetSafeHwnd(), 120);                           // ɾ����������ͼ�� 
	
	::PostQuitMessage(0);                                            // �����˳���Ψһ��ʽ
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

	s_top_offset  = 0;                                               // ����䲻���ƶ�λ��
	s_left_offset = 0;
	
	m_bRecvPause = TRUE;
	m_PortOpened  = FALSE;
	
	StrRecved = "";
	
	Loop_Counter = 0;
	
	RecvedLine = 0;
	RecvedData = 0;
	SendedData = 0;
	
    MaxRecvLines = 0;

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	s_Edit_Recv = (CEdit*)GetDlgItem(IDC_EDIT_RECV);
	s_Edit_Send = (CEdit*)GetDlgItem(IDC_EDIT_SEND);

	InitiateStatusBar();                                             // ��ʼ��״̬����������λ��
	InitiateComboComs();                                             // ��ʼ��ѡ�񴮿ںŵ��б��
	InitiateComboBaud();                                             // ��ʼ��ѡ�����ʵ��б��
	InitiateComboData();                                             // ��ʼ��ѡ������λ���б��
	InitiateComboCheck();                                            // ��ʼ��ѡ��У��λ���б��
	InitiateComboStop();                                             // ��ʼ��ѡ��ֹͣλ���б��
	InitiateSrSendArea();                                            // ��ʼ������ʾ�߼�����������

	SetControlStatus(FALSE);                                         // ���Ƚ��ø�����ť�ؼ�

	CreateDirectory(RecordPath, NULL);                               // ����Record�ļ��У����ڱ�������

	SetTimer(Timer_No_RecvData,  10,  NULL);
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

	INIT_EASYSIZE;                                                   // ��ʼ�������ؼ���λ��

	InitiateMainFrame();                                             // ��ʼ��������Ĵ�С

	CreateSettingFile();                                             // �����������ò����ļ�����ʼ����������
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
	    case Timer_No_RecvData:                                      // ���մ�������
			if (m_DataRecvd == TRUE) {
				HandleUSARTData();
				m_DataRecvd = FALSE;
			}
		    break;

		case Timer_No_StatusBar:                                     // ״̬����ʱ����
			UpdateStatusBarNow();
			break;
			
		case Timer_No_AutoSend:                                      // �Զ����Ͷ�����
			SendEditDatatoComm();
			break;
			
		case Timer_No_LoopSend:                                      // ���ڸ߼�ѭ������״̬
			ContinueLoopSrSend();
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

	if (pMsg -> message == WM_KEYDOWN)
	{
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
	ShowWindow(SW_HIDE);                                             // ���������ڵ��ǲ��˳�
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

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);      // ͬ��״̬����λ��
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

	EASYSIZE_MINSIZE(800, 546, fwSide, pRect);                       // ���ƴ������С�ߴ�
}

/**************************************************************************************************
**  ��������:  OnOnCommMscomm
**  ��������:  ������ͨ�ſؼ���Ϣ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CMySScomDlg::OnOnCommMscomm() 
{
    if (m_DataRecvd == FALSE) {
		m_DataRecvd = TRUE;
	}
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
	    case WM_LBUTTONDBLCLK:                                       // ��������˫��
			ShowWindow(IsWindowVisible()? SW_HIDE:SW_SHOWNORMAL);
			break;
		
	    case WM_RBUTTONDOWN:                                         // ������Ҽ�
            if (oMenu.LoadMenu(IDR_MENU_TRAY)) {
				CMenu* pPopup = oMenu.GetSubMenu(0);
				ASSERT(pPopup != NULL);
				
				GetCursorPos(&oPoint);                               // ȷ�����λ���Ա��ڸ�λ�ø�����ʾ�˵�
				SetForegroundWindow();
				pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, oPoint.x, oPoint.y, this); 
            }
		    break;
	}
}


