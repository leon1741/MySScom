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
	// 以下是扩展发送区的按钮控件的属性设置
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
	// 以下是扩展发送区的编辑框控件的属性设置
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
	// 以下是扩展发送区的复选框控件的属性设置
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
	// 以下是扩展发送区的其他各个控件的属性设置
	EASYSIZE(IDC_STATIC_LABLE,   ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_STATIC_SRAUTO,  ES_KEEPSIZE,        IDC_STATIC_SRAUTO,  ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_EDIT_SRAUTO,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,     0)
	EASYSIZE(IDC_CHECK_SRAUTO,   ES_KEEPSIZE,        IDC_EDIT_SRAUTO,    ES_BORDER,          ES_KEEPSIZE,     0)
END_EASYSIZE_MAP


/* ==================================== 自定义函数区--开始 ===================================== */

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
**  函数名称:  SetSrSendCtrlStatus
**  功能描述:  设置高级发送区控件的状态
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::SetSrSendCtrlStatus(bool Enable)
{
	GetDlgItem(IDC_CHECK_SRAUTO)->EnableWindow(Enable);
	GetDlgItem(IDC_EDIT_SRAUTO)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_SRAUTO)->EnableWindow(Enable);
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
		TempCStr = TempCStr.Right(3);                                // 截取右边有效位
		ResultCStr += TempCStr;
	}
	
	return ResultCStr;
}

/**************************************************************************************************
**  函数名称:  SaveEditContent
**  功能描述:  保存编辑框的内容到文本文件
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
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

/**************************************************************************************************
**  函数名称:  UpdateEditDisplay
**  功能描述:  更新编辑框的显示
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::UpdateEditDisplay(void)
{
	CWnd *hwnd;
	
	if (m_Check_HexDspl) {                                           // 如果需要16进制显示，进行转换

		m_Edit_Recv = TransformtoHex(StrRecved);
		SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);          // 让编辑框内容滚动到最后一行

		if (m_Check_AutoClear) {                                     // 如果需要自动清空内容

			if (RecvedData >= MaxRecvLines) {                        // 在16进制模式下，对数据内容长度进行判断

				RecvedLine = 0;                                      // 首先清空变量值
				RecvedData = 0;
				
				if (m_Check_AutoSave) {
					SaveEditContent();                               // 保存编辑框的数据
				}

				StrRecved   = "";
				m_Edit_Recv = "";
				SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);          // 清空编辑框内容
			}
		}

	} else {                                                         // 否则，直接显示数据内容

		m_Edit_Recv = StrRecved;
		SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);          // 让编辑框内容滚动到最后一行

		if (m_Check_AutoClear) {                                     // 如果需要自动清空内容
			
            if (RecvedLine >= MaxRecvLines) {                        // 在字符模式下，对数据行数进行判断

				RecvedLine = 0;                                      // 首先清空变量值
				RecvedData = 0;
				
				if (m_Check_AutoSave) {
					SaveEditContent();                               // 保存编辑框的数据
				}

				StrRecved   = "";
				m_Edit_Recv = "";
				SetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);          // 清空编辑框内容
			}
		}
	}

	/*************************************************************************************************\
	|                          以下语句实现对接收编辑框的闪屏现象的屏蔽作用                           |
    \*************************************************************************************************/
	
	hwnd = GetDlgItem(IDC_EDIT_RECV);                                // 获取接收编辑框的控件ID

	if (GetFocus() == hwnd) {                                        // 将窗口焦点转移至发送编辑框
		GetDlgItem(IDC_EDIT_SEND)->SetFocus();
	}
}

/**************************************************************************************************
**  函数名称:  HandleUSARTData
**  功能描述:  定时接收串口数据并显示
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::HandleUSARTData(void)
{
    VARIANT       Input_Vrt;
    COleSafeArray Input_Ary;
    LONG          RecvLen, i;
    BYTE          RecvData[2048];                                    // 设置BYTE数组
    CString       TimeStr, TempStr;
	CTime         NowTime;
	
	if (m_PortOpened == FALSE) {
		return;
	}
	
    if (m_ctrlComm.GetCommEvent() == 2) {                            // 事件值为2表示接收缓冲区内有字符
		
        Input_Vrt = m_ctrlComm.GetInput();                           // 读缓冲区
        Input_Ary = Input_Vrt;                                       // VARIANT型变量转换为ColeSafeArray型变量
        RecvLen   = Input_Ary.GetOneDimSize();                       // 得到有效数据长度
        
		for (i = 0; i < RecvLen; i++) {
            Input_Ary.GetElement(&i, RecvData + i);                  // 转换为BYTE型数组存放到RecvData数组
		}
		
		if (m_bRecvPause == FALSE) {                                 // 如果暂停接收了，则不存储数据，直接返回
			return;
		}
		
        for (i = 0; i < RecvLen; i++) {                              // 将数组转换为Cstring型变量
			
            BYTE bt = *(char *)(RecvData + i);                       // 读取单个字符
			
			//if (bt == 0) {                                         // 转换为字符型
			//	TempStr = CString(bt);
			//} else {
			//	TempStr.Format("%c", bt);
			//}

			TempStr.Format("%c", bt);
			
			if (m_Check_ShowTime == TRUE) {                          // 只有在启用时间显示功能时才判断
				
				if (TempStr == "\n") {                               // 本次接收到了回车符，切换到下一行显示
					m_NeedTime = TRUE;
					RecvedLine++;
				} else {
					if (m_NeedTime == TRUE) {
						NowTime = CTime::GetCurrentTime();	         // 获取现在时间
						TimeStr = NowTime.Format("[%H:%M:%S] ");
						
						StrRecved += TimeStr;                        // 在行头显示时间
						m_NeedTime = FALSE;
					}
				}
			} else {                                                 // 不需要在行头位置显示时间
				
				if (m_Check_HexDspl == FALSE) {                      // 16进制模式下不进行判断

					if (TempStr == "\n") {                           // 本次接收到回车符
						RecvedLine++;
					}
				} else {

					RecvedLine = 0;                                  // 
				}
			}
			
			StrRecved += TempStr;                                    // 保存数据内容
			RecvedData++;                                            // 接收字节数累加
        }
    }
	
    UpdateEditDisplay();                                             // 更新编辑框内容显示
    
    UpdateStatusBarNow();                                            // 更新状态栏统计数据的显示
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

		SetTimer(Timer_No_AutoSend, Timer, NULL);                    // 启动定时器

		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);

		m_Edit_AutoTimer = TempStr;                                  // 更新编辑框内容
		SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);

		SetSendButtonStatus(FALSE);                                  // 禁用发送区各个按钮

	} else {

		MessageBox("定时时间必须在0至100秒钟之间，请确认！  ", "提示", MB_OK + MB_ICONEXCLAMATION);

		SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);            // 还原编辑框内容

		m_Check_AutoSend = FALSE;
		UpdateData(FALSE);                                           // 取消复选框被选中的状态

		return;
	}
}

/**************************************************************************************************
**  函数名称:  NeedLoopSendData
**  功能描述:  启动循环发送数据的功能
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::NeedLoopSendData(void)
{
	int Timer;
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SRAUTO, TempStr);
	
	Timer = atoi((LPSTR)(LPCTSTR)TempStr);
	
	if ((Timer > 0) && (Timer <= 10000)) {
		
		SetTimer(Timer_No_LoopSend, Timer, NULL);                    // 启动定时器
		Loop_Counter = 0;
		
		GetDlgItem(IDC_EDIT_SRAUTO)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_SRAUTO)->EnableWindow(FALSE);
		
		m_Edit_LoopTimer = TempStr;                                  // 更新编辑框内容
		SetDlgItemText(IDC_EDIT_SRAUTO, m_Edit_LoopTimer);
		
	} else {
		
		MessageBox("定时时间必须在0至10秒钟之间，请确认！  ", "提示", MB_OK + MB_ICONEXCLAMATION);
		
		SetDlgItemText(IDC_EDIT_SRAUTO, m_Edit_LoopTimer);           // 还原编辑框内容
		
		m_Check_LoopSend = FALSE;
		UpdateData(FALSE);                                           // 取消复选框被选中的状态
		
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

	this->GetWindowRect(&DialogMain);                                // 获取主界面在屏幕上的位置
	
	if (DialogMain.Width() < 900) {
		DisplayStr = " 欢迎使用MySScom";	
		m_StatusBar.SetPaneText(0, DisplayStr);
	} else if ((DialogMain.Width() >= 900) && (DialogMain.Width() < 1050)) {
		DisplayStr = " 欢迎使用MySScom - Designed By LEON";	
		m_StatusBar.SetPaneText(0, DisplayStr);
	} else if ((DialogMain.Width() >= 1050) && (DialogMain.Width() < 1200)) {
		DisplayStr = " 欢迎使用MySScom - Designed By LEON (QQ: 39110103)";	
		m_StatusBar.SetPaneText(0, DisplayStr);
	} else if ((DialogMain.Width() >= 1200) && (DialogMain.Width() < 1350)) {
		DisplayStr = " 欢迎使用MySScom - Designed By LEON (QQ: 39110103, LEON1741@126.com)";	
		m_StatusBar.SetPaneText(0, DisplayStr);
	} else {
		DisplayStr = " 欢迎使用MySScom - Designed By LEON (QQ: 39110103, LEON1741@126.com. \"Never Stop Trying\"!)";	
		m_StatusBar.SetPaneText(0, DisplayStr);
	}
	
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
**  函数名称:  InitiateAllParas
**  功能描述:  读取配置文件的各个参数内容并初始化对话框的值
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::InitiateAllParas(void)
{
	int  TempData;                                                   // 需要注意的是：自动发送使能和循环发送使能两项无须初始化
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

	if (m_Check_HexDspl) {                                           // 根据读入的参数值初始化提示框内容
		SetDlgItemText(IDC_STATIC_LINES, "字符");
	} else {
		SetDlgItemText(IDC_STATIC_LINES, "行");
	}
	
	UpdateData(FALSE);                                               // 更新编辑框内容
}

/**************************************************************************************************
**  函数名称:  RecordAllParas
**  功能描述:  将对话框中各个参数的值记录到配置文件中
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::RecordAllParas(void)
{
	int TempData;                                          // 需要注意的是：自动发送使能和循环发送使能两项无须保存
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
	m_StatusBar.SetPaneText(0, " 欢迎使用MySScom");
	
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
	EnumComm();                                                      // 枚举可用的串口

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
	CString TempStr;
	
	for (int i = 0; i < (sizeof(Combo_Stop) / sizeof(Combo_Stop[0])); i++) {
		
		TempStr.Format("%d 位", Combo_Stop[i]);
		
		m_Combo_Stop.AddString(TempStr);
	}
}

/**************************************************************************************************
**  函数名称:  InitiateMainFrame
**  功能描述:  初始化主窗口的位置
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::InitiateMainFrame(void)
{
	CRect DialogMain;

	this->GetWindowRect(&DialogMain);                                // 获取主界面在屏幕上的位置

	this->MoveWindow((DialogMain.left), (DialogMain.top), (DialogMain.Width()), (DialogMain.Height()));
}

/**************************************************************************************************
**  函数名称:  InitiateSrSendArea
**  功能描述:  初始化高级发送区的显示
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::InitiateSrSendArea(void)
{
	m_SrSendEnable = FALSE;

	HideSrSendArea();                                                // 默认状态下不显示高级发送功能

	OnButtonSrSend();                                                // 目前会出现初次显示时发送区的位置有点偏移
	OnButtonSrSend();                                                // 通过连续调用两次切换函数暂时覆盖整个BUG
}

/**************************************************************************************************
**  函数名称:  SendEditDatatoComm
**  功能描述:  将编辑框内的数据发送到串口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::SendEditDatatoComm(void)
{
	assert(m_SrSendEnable == FALSE);
	
	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);                      // 获取编辑框的内容
	
	if (m_Edit_Send.GetLength() > MAX_SEND_BYTE) {                   // 数据长度过大
		
		MessageBox("发送内容过长，提交请求失败......   ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}

	if (m_Check_HexSend) {                                           // 如果需要以16进制发送
		
		CByteArray hexdata;
		int len;                                                     // 此处返回的len可以用于计算发送了多少个十六进制数
		
		len = String2Hex(m_Edit_Send, hexdata);
		m_ctrlComm.SetOutput(COleVariant(hexdata));                  // 发送十六进制数据
		SendedData += len;                                           // 发送字节数累加
		
	} else {
		
		m_ctrlComm.SetOutput(COleVariant(m_Edit_Send));              // 发送ASCII字符数据
		SendedData += m_Edit_Send.GetLength();                       // 发送字节数累加
	}

	if (m_Check_Return) {                                            // 补发回车换行符
		m_ctrlComm.SetOutput(COleVariant("\r"));
		m_ctrlComm.SetOutput(COleVariant("\n"));
		SendedData += 2;
	}

	UpdateStatusBarNow();                                            // 更新状态栏统计数据的显示
}

/**************************************************************************************************
**  函数名称:  ShowSrSendCheck
**  功能描述:  显示高级发送区内的check控件
**  输入参数:  
**  返回参数:  
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
**  函数名称:  ShowSrSendEdit
**  功能描述:  显示高级发送区内的edit控件
**  输入参数:  
**  返回参数:  
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
**  函数名称:  ShowSrSendButton
**  功能描述:  显示高级发送区内的button控件
**  输入参数:  
**  返回参数:  
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
**  函数名称:  ShowSrSendOthers
**  功能描述:  显示高级发送区内的其他控件
**  输入参数:  
**  返回参数:  
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
**  函数名称:  HideSrSendArea
**  功能描述:  隐藏高级发送区
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::HideSrSendArea(void)
{
	CRect DialogMain, RecvEdit, SendEdit, SendButton;
	CRect RecvStatic, SendStatic, SrSdStatic, ControlStatic;
	
	this->GetWindowRect(&DialogMain);                                // 获取主界面在屏幕上的位置
	
	if ((s_top_offset == 0) && (s_left_offset == 0)) {               // 根据不同主题边框大小调整偏移量

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
**  函数名称:  ShowSrSendArea
**  功能描述:  显示高级发送区
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::ShowSrSendArea(void)
{
	CRect DialogMain, RecvEdit, SendEdit, SendButton;
	CRect RecvStatic, SendStatic, SrSdStatic, ControlStatic;
	
	this->GetWindowRect(&DialogMain);                                // 获取主界面在屏幕上的位置

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
**  函数名称:  SrEditDataValid
**  功能描述:  判断edit控件内的数据是否有效
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
bool CMySScomDlg::SrEditDataValid(int EditID)
{
	assert(m_SrSendEnable == TRUE);
	
	CString EditStr;
	
	GetDlgItemText(EditID, EditStr);
	
	if (EditStr.GetLength() > 0) {                                   // 判断编辑框内容的长度是否有效
		return TRUE;
	} else {
		return FALSE;
	}
}

/**************************************************************************************************
**  函数名称:  GetSrValidDataNo
**  功能描述:  获取高级发送区内edit控件内数据有效的控件ID
**  输入参数:  
**  返回参数:  
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
		return 0;                                                    // 返回内容有效的编辑框的序号，全无效则返回0
	}
}

/**************************************************************************************************
**  函数名称:  TrytoSrSendData
**  功能描述:  尝试发送高级发送区内的数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::TrytoSrSendData(CString InputStr, BOOL NeedHex)
{
	assert(m_SrSendEnable == TRUE);
	
	if (InputStr.GetLength() <= 0) {
		MessageBox("发送窗口内容为空，未发送任何数据！  ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	if (NeedHex == TRUE) {                                           // 如果需要以16进制发送
		
		CByteArray SendData;
		int len;                                                     // 此处返回的len可以用于计算发送了多少个十六进制数
		
		len = String2Hex(InputStr, SendData);
		
		m_ctrlComm.SetOutput(COleVariant(SendData));                 // 发送十六进制数据
		
		SendedData += len;                                           // 发送字节数累加

		m_Check_HexSend = TRUE;                                      // 将数据同步复制到发送栏
		m_Edit_Send = InputStr;
		SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
		
	} else {
		
		m_ctrlComm.SetOutput(COleVariant(InputStr));                 // 发送ASCII字符数据
		
		SendedData += InputStr.GetLength();                          // 发送字节数累加

		m_Check_HexSend = FALSE;                                     // 将数据同步复制到发送栏
		m_Edit_Send = InputStr;
		SetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
	}

	if (m_Check_Return) {                                            // 补发回车换行符
		m_ctrlComm.SetOutput(COleVariant("\r"));
		m_ctrlComm.SetOutput(COleVariant("\n"));
		SendedData += 2;
	}
	
	UpdateStatusBarNow();                                            // 更新状态栏统计数据的显示

	UpdateData(FALSE);
}

/**************************************************************************************************
**  函数名称:  ContinueLoopSrSend
**  功能描述:  对高级发送区内的数据进行循环发送
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::ContinueLoopSrSend(void)
{
	assert(m_SrSendEnable == TRUE);

	for (; ;) {                                                      // 依次判断每个编辑框的内容是否有效，并发送之
		
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


/* ================================== 高级发送功能处理--开始 =================================== */

/**************************************************************************************************
**  函数名称:  
**  功能描述:  
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrAuto() 
{
	assert(m_SrSendEnable == TRUE);
	
	m_Check_LoopSend = !m_Check_LoopSend;
	
	if (m_Check_LoopSend) {

		if (GetSrValidDataNo() == 0) {

			MessageBox("貌似您尚未输入任何需要的发送的内容，叫我发送什么呢？~~~  ", "提示", MB_OK + MB_ICONINFORMATION);
			
			m_Check_LoopSend = FALSE;
			UpdateData(FALSE);                                       // 取消复选框被选中的状态
			
			return;
		}

		SwitchSendStatus(FALSE);
		
		NeedLoopSendData();
		
	} else {
		
		Loop_Counter = 0;
		KillTimer(Timer_No_LoopSend);                                // 取消自动发送功能
		
		GetDlgItem(IDC_EDIT_SRAUTO)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_SRAUTO)->EnableWindow(TRUE);

		SwitchSendStatus(TRUE);
	}
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend01
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend01() 
{
	m_Check_SrSend_01 = !m_Check_SrSend_01;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend02
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend02() 
{
	m_Check_SrSend_02 = !m_Check_SrSend_02;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend03
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend03() 
{
	m_Check_SrSend_03 = !m_Check_SrSend_03;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend04
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend04() 
{
	m_Check_SrSend_04 = !m_Check_SrSend_04;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend05
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend05() 
{
	m_Check_SrSend_05 = !m_Check_SrSend_05;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend06
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend06() 
{
	m_Check_SrSend_06 = !m_Check_SrSend_06;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend07
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend07() 
{
	m_Check_SrSend_07 = !m_Check_SrSend_07;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend08
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend08() 
{
	m_Check_SrSend_08 = !m_Check_SrSend_08;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend09
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend09() 
{
	m_Check_SrSend_09 = !m_Check_SrSend_09;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend10
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend10() 
{
	m_Check_SrSend_10 = !m_Check_SrSend_10;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend11
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend11() 
{
	m_Check_SrSend_11 = !m_Check_SrSend_11;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend12
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend12() 
{
	m_Check_SrSend_12 = !m_Check_SrSend_12;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend13
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend13() 
{
	m_Check_SrSend_13 = !m_Check_SrSend_13;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend14
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend14() 
{
	m_Check_SrSend_14 = !m_Check_SrSend_14;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend15
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend15() 
{
	m_Check_SrSend_15 = !m_Check_SrSend_15;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend16
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend16() 
{
	m_Check_SrSend_16 = !m_Check_SrSend_16;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend17
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend17() 
{
	m_Check_SrSend_17 = !m_Check_SrSend_17;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend18
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend18() 
{
	m_Check_SrSend_18 = !m_Check_SrSend_18;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend19
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend19() 
{
	m_Check_SrSend_19 = !m_Check_SrSend_19;
}

/**************************************************************************************************
**  函数名称:  OnCheckSrSend20
**  功能描述:  高级发送区的复选框消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnCheckSrSend20() 
{
	m_Check_SrSend_20 = !m_Check_SrSend_20;
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend01
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend01() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR01, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_01);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend02
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend02() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR02, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_02);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend03
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend03() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR03, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_03);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend04
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend04() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR04, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_04);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend05
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend05() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR05, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_05);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend06
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend06() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR06, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_06);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend07
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend07() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR07, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_07);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend08
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend08() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR08, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_08);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend09
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend09() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR09, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_09);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend10
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend10() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR10, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_10);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend11
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend11() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR11, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_11);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend12
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend12() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR12, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_12);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend13
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend13() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR13, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_13);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend14
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend14() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR14, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_14);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend15
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend15() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR15, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_15);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend16
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend16() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR16, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_16);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend17
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend17() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR17, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_17);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend18
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend18() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR18, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_18);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend19
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend19() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR19, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_19);
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend20
**  功能描述:  高级发送区的按钮消息处理
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend20() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR20, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_20);
}


/* ================================== 高级发送功能处理--结束 =================================== */


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
	CString TempStr, SettingStr;
    
	if (m_PortOpened == TRUE) {                                      // 如果串口已经打开，那么执行关闭操作

		if (m_Check_AutoSend || m_Check_LoopSend) {
			MessageBox("请首先停用自动发送功能再尝试关闭串口...  ", "提示", MB_OK + MB_ICONEXCLAMATION);
			return;
		}

		m_ctrlComm.SetPortOpen(FALSE);

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

	int Number = m_Combo_ComNo.GetCurSel();                          // 得到串口号
	
	if (Number == 0) {
		MessageBox("串口号都没有选择，你叫我打开什么东东...？   ", "提示", MB_OK + MB_ICONINFORMATION);
        return;
    }
	
	if (m_ctrlComm.GetPortOpen()) {                                  // 判断是否已经打开
        m_ctrlComm.SetPortOpen(FALSE);
	}
	
	m_Combo_ComNo.GetLBText(Number, TempStr);
	TempStr.TrimLeft("COM");                                         // 删除"COM"字段
	
	m_ctrlComm.SetCommPort(atoi(TempStr.Mid(0)));                    // 指定串口号
	
    if (!m_ctrlComm.GetPortOpen()) {

        m_ctrlComm.SetPortOpen(TRUE);                                // 尝试打开串口

		SettingStr = "";
		
		int ComBaudSel = m_Combo_Baud.GetCurSel();                   // 获取波特率的选择项
		TempStr.Format("%d", Combo_Baud[ComBaudSel]);
		SettingStr += TempStr;

		SettingStr += ",";

		int ComCheckSel = m_Combo_Check.GetCurSel();                 // 获取校验位的选择项
		TempStr.Format("%c", Combo_Check[ComCheckSel]);
		SettingStr += TempStr;
		
		SettingStr += ",";
		
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
		
		SetControlStatus(TRUE);                                      // 启用各个按钮控件
		
		SetDlgItemText(IDC_BUTTON_ONOFF, "关闭串口");

		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_CHECK)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);		

	} else {

        MessageBox("打开串口失败，该串口可能正在使用中...   ", "提示", MB_OK + MB_ICONERROR);
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
		SetDlgItemText(IDC_BUTTON_PAUSE, "暂停接收");
		GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(TRUE);
	} else {
		m_bRecvPause = FALSE;
		SetDlgItemText(IDC_BUTTON_PAUSE, "恢复接收");
		GetDlgItem(IDC_BUTTON_ONOFF)->EnableWindow(FALSE);
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
		m_NeedTime = TRUE;                                           // 下一次收到数据时显示时间
	}

	RecvedLine = 0;
	RecvedData = 0;
	UpdateStatusBarNow();                                            // 更新状态栏的统计数据显示
}

/**************************************************************************************************
**  函数名称:  OnButtonSave
**  功能描述:  将接收到的数据保存到文件中
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSave() 
{
	CFile   MyFile;	                                                 // 定义文件类
	int     nLength;
	CString Temp_String;
	
	CTime   NowTime  = CTime::GetCurrentTime();	                     // 获取现在时间
	CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt"; // 指定文件名
	
	GetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
	
	nLength = m_Edit_Recv.GetLength();                               // 获取长度
	
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
	
	MyFile.Write(m_Edit_Recv, nLength);	                             // 写入文本文件
	MyFile.Close();	                                                 // 关闭文件
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

	SendEditDatatoComm();
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

	UpdateStatusBarNow();                                            // 更新状态栏的统计数据显示
}

/**************************************************************************************************
**  函数名称:  OnButtonSrSend
**  功能描述:  是否显示高级发送窗口
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnButtonSrSend() 
{
	if (m_SrSendEnable == TRUE) {                                    // 如果已经启用高级发送功能，则禁用之

		if (m_Check_LoopSend) {

			MessageBox("自动发送功能已开启，请先停用之！ ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		}

		HideSrSendArea();

		m_SrSendEnable = FALSE;

		SetDlgItemText(IDC_BUTTON_SRSEND, "高级发送");

	} else {                                                         // 如果没有启用高级发送功能，则启用之

		if (m_Check_AutoSend) {

			MessageBox("自动发送功能已开启，请先停用之！ ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		}

		ShowSrSendArea();

		m_SrSendEnable = TRUE;

		SetDlgItemText(IDC_BUTTON_SRSEND, "普通发送");
	}
	
	INIT_EASYSIZE;                                                   // 重新初始化各个控件的位置
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

		UpdateEditDisplay();                                             // 更新显示
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
        SetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                // 还原编辑框内容
        m_Check_AutoClear = FALSE;        
        UpdateData(FALSE);
        return;
    }

    GetDlgItemText(IDC_EDIT_LINES, m_Edit_Lines);                    // 读取数据并保存
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
	assert(m_SrSendEnable == FALSE);
	
	m_Check_AutoSend = !m_Check_AutoSend;

	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);

	if (m_Edit_Send.GetLength() <= 0) {
		MessageBox("貌似发送区为空吧，请问您老想让我发送什么东东？ ", "提示", MB_OK + MB_ICONINFORMATION);
		m_Check_AutoSend = FALSE;
		UpdateData(FALSE);
		return;
	}

	if (m_Check_AutoSend) {

		if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {              // 确保输入的数据不会过长

			MessageBox("您输入的数据过长，提交发送请求失败......   ", "提示", MB_OK + MB_ICONINFORMATION);
			m_Check_AutoSend = FALSE;
			UpdateData(FALSE);
			return;
		}

		SetSrSendCtrlStatus(FALSE);

		NeedAutoSendData();                                          // 开始尝试自动发送数据

	} else {

		KillTimer(Timer_No_AutoSend);                                // 否则，用户取消了自动发送的功能
		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);

		SetSrSendCtrlStatus(TRUE);

		SetSendButtonStatus(TRUE);                                   // 重新启用发送区各个按钮
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
	RecordAllParas();                                                // 保存各个参数数据
	
	TaskBarDeleteIcon(GetSafeHwnd(), 120);                           // 删除任务栏的图标 
	
	::PostQuitMessage(0);                                            // 程序退出的唯一方式
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

	s_top_offset  = 0;                                               // 该语句不能移动位置
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

	InitiateStatusBar();                                             // 初始化状态栏各个区域位置
	InitiateComboComs();                                             // 初始化选择串口号的列表框
	InitiateComboBaud();                                             // 初始化选择波特率的列表框
	InitiateComboData();                                             // 初始化选择数据位的列表框
	InitiateComboCheck();                                            // 初始化选择校验位的列表框
	InitiateComboStop();                                             // 初始化选择停止位的列表框
	InitiateSrSendArea();                                            // 初始化不显示高级发送区内容

	SetControlStatus(FALSE);                                         // 首先禁用各个按钮控件

	CreateDirectory(RecordPath, NULL);                               // 创建Record文件夹，用于保存数据

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

	INIT_EASYSIZE;                                                   // 初始化各个控件的位置

	InitiateMainFrame();                                             // 初始化主界面的大小

	CreateSettingFile();                                             // 创建程序配置参数文件并初始化各个参数
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
	    case Timer_No_RecvData:                                      // 接收串口数据
			if (m_DataRecvd == TRUE) {
				HandleUSARTData();
				m_DataRecvd = FALSE;
			}
		    break;

		case Timer_No_StatusBar:                                     // 状态栏定时更新
			UpdateStatusBarNow();
			break;
			
		case Timer_No_AutoSend:                                      // 自动发送短数据
			SendEditDatatoComm();
			break;
			
		case Timer_No_LoopSend:                                      // 处于高级循环发送状态
			ContinueLoopSrSend();
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
**  函数名称:  OnClose
**  功能描述:  处理窗口关闭消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnClose() 
{
	ShowWindow(SW_HIDE);                                             // 隐藏主窗口但是不退出
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

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);      // 同步状态栏的位置
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

	EASYSIZE_MINSIZE(800, 546, fwSide, pRect);                       // 限制窗体的最小尺寸
}

/**************************************************************************************************
**  函数名称:  OnOnCommMscomm
**  功能描述:  处理串口通信控件消息
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CMySScomDlg::OnOnCommMscomm() 
{
    if (m_DataRecvd == FALSE) {
		m_DataRecvd = TRUE;
	}
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
	    case WM_LBUTTONDBLCLK:                                       // 如果是左键双击
			ShowWindow(IsWindowVisible()? SW_HIDE:SW_SHOWNORMAL);
			break;
		
	    case WM_RBUTTONDOWN:                                         // 如果是右键
            if (oMenu.LoadMenu(IDR_MENU_TRAY)) {
				CMenu* pPopup = oMenu.GetSubMenu(0);
				ASSERT(pPopup != NULL);
				
				GetCursorPos(&oPoint);                               // 确定鼠标位置以便在该位置附近显示菜单
				SetForegroundWindow();
				pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, oPoint.x, oPoint.y, this); 
            }
		    break;
	}
}


