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
	m_Check_LoopSend = FALSE;	
	m_Check_HexDspl = FALSE;
	m_Check_HexSend = FALSE;
	m_Check_AutoClear = FALSE;
	m_Edit_Recv = _T("");
	m_Edit_Send = _T("");
	m_Edit_AutoTimer = _T("1000");
	m_Edit_LoopTimer = _T("1000");
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
	EASYSIZE(IDC_STATIC_EX01,    ES_BORDER,          ES_BORDER,          ES_KEEPSIZE,        ES_BORDER,       0)
	EASYSIZE(IDC_STATIC_EX02,    ES_KEEPSIZE,        ES_BORDER,          ES_BORDER,          ES_BORDER,       0)
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

	GetDlgItem(IDC_BUTTON_SRSEND)->EnableWindow(Enable);
}

void CMySScomDlg::SetSendButtonStatus(bool Enable)
{
	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_RESPITE)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_REIPUT)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(Enable);
}

void CMySScomDlg::SetSendingStatus(bool Enable)
{
	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_RESPITE)->EnableWindow(Enable);
	GetDlgItem(IDC_BUTTON_REIPUT)->EnableWindow(Enable);

	GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(Enable);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(Enable);
}

void CMySScomDlg::SwitchSendStatus(bool IsNormal)
{
	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(IsNormal);
	GetDlgItem(IDC_BUTTON_RESPITE)->EnableWindow(IsNormal);

	GetDlgItem(IDC_CHECK_AUTOSEND)->EnableWindow(IsNormal);
	GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(IsNormal);
	GetDlgItem(IDC_STATIC_MS)->EnableWindow(IsNormal);
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
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);          // 让编辑框内容滚动到最后一行

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
		s_Edit_Recv->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);          // 让编辑框内容滚动到最后一行

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

		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(FALSE);

		m_Edit_AutoTimer = TempStr;                                  // 更新编辑框内容
		SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);

		SetSendButtonStatus(FALSE);                                  // 禁用发送区各个按钮

	} else {

		MessageBox("定时时间必须在0至10秒钟之间，请确认！     ", "提示", MB_OK + MB_ICONEXCLAMATION);

		SetDlgItemText(IDC_EDIT_TIMER, m_Edit_AutoTimer);            // 还原编辑框内容

		m_Check_AutoSend = FALSE;
		UpdateData(FALSE);                                           // 取消复选框被选中的状态

		return;
	}
}

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
		SetDlgItemText(IDC_EDIT_SRAUTO, m_Edit_AutoTimer);
		
	} else {
		
		MessageBox("定时时间必须在0至10秒钟之间，请确认！     ", "提示", MB_OK + MB_ICONEXCLAMATION);
		
		SetDlgItemText(IDC_EDIT_SRAUTO, m_Edit_AutoTimer);           // 还原编辑框内容
		
		m_Check_LoopSend = FALSE;
		UpdateData(FALSE);                                           // 取消复选框被选中的状态
		
		return;
	}
}

void CMySScomDlg::UpdateStatusBarNow(void)
{
	CTime   Nowtime;
	CString TempStr, DisplayStr;
	
	Nowtime = CTime::GetCurrentTime();
	
	DisplayStr = m_PortOpened ? " 串口已打开" : " 串口未打开";	
	m_StatusBar.SetPaneText(1, DisplayStr);

	DisplayStr.Format(" Recv: %.4d", RecvedData);
	m_StatusBar.SetPaneText(2, DisplayStr);

	DisplayStr.Format(" Send: %.4d", SendedData);
	m_StatusBar.SetPaneText(3, DisplayStr);

	DisplayStr = " 当前时间: " + Nowtime.Format("%Y-%m-%d") + " " + Nowtime.Format("%H:%M:%S");
	m_StatusBar.SetPaneText(4, DisplayStr);
}

void CMySScomDlg::InitiateStatusBar(void)
{
	static UINT indicators[] =
	{
		ID_SEPARATOR,
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
		ID_INDICATOR_OVR,
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
	
	m_StatusBar.SetPaneInfo(0, nID, SBPS_STRETCH, 200);
	m_StatusBar.SetPaneText(0, " 欢迎使用MySScom - 雅迅网络研发一部测试组");
	
	m_StatusBar.SetPaneInfo(1, nID, SBPS_NORMAL, 100);
	m_StatusBar.SetPaneText(1, " 串口未打开");

	m_StatusBar.SetPaneInfo(2, nID, SBPS_NORMAL, 100);
	m_StatusBar.SetPaneText(2, " Recv: 0000");
	
	m_StatusBar.SetPaneInfo(3, nID, SBPS_NORMAL, 100);
	m_StatusBar.SetPaneText(3, " Send: 0000");

	m_StatusBar.SetPaneInfo(4, nID, SBPS_NORMAL, 200);
	m_StatusBar.SetPaneText(4, m_strTime);
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
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

void CMySScomDlg::InitiateMainFrame(void)
{
	CRect DialogMain;

	this->GetWindowRect(&DialogMain);                                // 获取主界面在屏幕上的位置

	this->MoveWindow((DialogMain.left), (DialogMain.top), (DialogMain.Width()), (DialogMain.Height()));
}

void CMySScomDlg::InitiateSrSendArea(void)
{
	m_SrSendEnable = FALSE;

	HideSrSendArea();                                                // 默认状态下不显示高级发送功能
}

void CMySScomDlg::SendEditDatatoComm(void)
{
	assert(m_SrSendEnable == FALSE);
	
	if (m_bSendPause == FALSE) {                                     // 确认是否允许发送数据

		GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);                  // 获取编辑框的内容

		if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {              // 如果数据长度过大，则切换到大数据发送模式

			MessageBox("文件内容较大，发送将持续一段时间，请耐心等待......      ", "提示", MB_OK + MB_ICONINFORMATION);
						
			SetDlgItemText(IDC_BUTTON_SEND, "取消发送");

			SetSendingStatus(FALSE);
			
			Send_Status  = SEND_LONG_FILE;
			Send_Counter = 0;

			SetTimer(Timer_No_SendFile, MAX_SEND_BYTE, NULL);        // 启动定时器，获取前N个字符发送

			StrToSend = m_Edit_Send.Left(MAX_SEND_BYTE);
			Send_Counter++;

			m_ctrlComm.SetOutput(COleVariant(StrToSend));            // 发送ASCII字符数据
			SendedData += StrToSend.GetLength();                     // 发送字节数累加

		} else {                                                     // 否则，切换到小数据模式，并停止定时器
			
			Send_Status  = SEND_SHORT_DATA;
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
	assert(m_SrSendEnable == FALSE);
	
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

				OnButtonSend();                                      // 通知控件，数据发送完毕
			}
		} else {

			KillTimer(Timer_No_SendFile);                            // 停止定时器
		}
		
		m_ctrlComm.SetOutput(COleVariant(StrToSend));                // 发送ASCII字符数据
		
		SendedData += StrToSend.GetLength();                         // 发送字节数累加
		
		UpdateStatusBarNow();                                        // 更新状态栏统计数据的显示
	}
}

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

void CMySScomDlg::ShowSrSendOthers(bool Enable)
{
	GetDlgItem(IDC_STATIC_SRSEND)->ShowWindow(Enable);
	GetDlgItem(IDC_STATIC_LABLE)->ShowWindow(Enable);
	
	GetDlgItem(IDC_STATIC_EX02)->ShowWindow(Enable);

	GetDlgItem(IDC_CHECK_SRAUTO)->ShowWindow(Enable);
	GetDlgItem(IDC_EDIT_SRAUTO)->ShowWindow(Enable);
	GetDlgItem(IDC_STATIC_SRAUTO)->ShowWindow(Enable);
}

void CMySScomDlg::HideSrSendArea(void)
{
	CRect DialogMain, RecvEdit, SendEdit;
	CRect RecvStatic, SendStatic, SrSdStatic;
	
	ShowSrSendCheck(FALSE);
	ShowSrSendEdit(FALSE);
	ShowSrSendButton(FALSE);
	ShowSrSendOthers(FALSE);
	
	this->GetWindowRect(&DialogMain);                                // 获取主界面在屏幕上的位置

	GetDlgItem(IDC_STATIC_RECEIVE)->GetWindowRect(&RecvStatic);
	GetDlgItem(IDC_STATIC_SEND)->GetWindowRect(&SendStatic);
	GetDlgItem(IDC_STATIC_SRSEND)->GetWindowRect(&SrSdStatic);
	
	GetDlgItem(IDC_EDIT_RECV)->GetWindowRect(&RecvEdit);
	GetDlgItem(IDC_EDIT_SEND)->GetWindowRect(&SendEdit);

	GetDlgItem(IDC_STATIC_RECEIVE)->MoveWindow((RecvStatic.left - DialogMain.left - 4), 
											   (RecvStatic.top - DialogMain.top - 23), 
		                                       (RecvStatic.Width() + SrSdStatic.Width() + 10), 
											   (RecvStatic.Height()));
	
	GetDlgItem(IDC_EDIT_RECV)->MoveWindow((RecvEdit.left - DialogMain.left - 4), 
		                                  (RecvEdit.top - DialogMain.top - 23), 
		                                  (RecvEdit.Width() + SrSdStatic.Width() + 10), 
										  (RecvEdit.Height()));

	GetDlgItem(IDC_STATIC_SEND)->MoveWindow((SendStatic.left - DialogMain.left - 4), 
	                                        (SendStatic.top - DialogMain.top - 23), 
	                                        (SendStatic.Width() + SrSdStatic.Width() + 10), 
											(SendStatic.Height()));

	GetDlgItem(IDC_EDIT_SEND)->MoveWindow((SendEdit.left - DialogMain.left - 4), 
	                                      (SendEdit.top - DialogMain.top - 23), 
		                                  (SendEdit.Width() + SrSdStatic.Width() + 10), 
										  (SendEdit.Height()));
}

void CMySScomDlg::ShowSrSendArea(void)
{
	CRect DialogMain, RecvEdit, SendEdit;
	CRect RecvStatic, SendStatic, SrSdStatic;

	ShowSrSendCheck(TRUE);
	ShowSrSendEdit(TRUE);
	ShowSrSendButton(TRUE);
	ShowSrSendOthers(TRUE);
	
	this->GetWindowRect(&DialogMain);                                // 获取主界面在屏幕上的位置

	GetDlgItem(IDC_STATIC_RECEIVE)->GetWindowRect(&RecvStatic);
	GetDlgItem(IDC_STATIC_SEND)->GetWindowRect(&SendStatic);
	GetDlgItem(IDC_STATIC_SRSEND)->GetWindowRect(&SrSdStatic);
	
	GetDlgItem(IDC_EDIT_RECV)->GetWindowRect(&RecvEdit);
	GetDlgItem(IDC_EDIT_SEND)->GetWindowRect(&SendEdit);
	
	GetDlgItem(IDC_STATIC_RECEIVE)->MoveWindow((RecvStatic.left - DialogMain.left - 4), 
											   (RecvStatic.top - DialogMain.top - 23), 
		                                       (RecvStatic.Width() - SrSdStatic.Width() - 10), 
											   (RecvStatic.Height()));
	
	GetDlgItem(IDC_EDIT_RECV)->MoveWindow((RecvEdit.left - DialogMain.left - 4), 
		                                  (RecvEdit.top - DialogMain.top - 23), 
		                                  (RecvEdit.Width() - SrSdStatic.Width() - 10), 
										  (RecvEdit.Height()));

	GetDlgItem(IDC_STATIC_SEND)->MoveWindow((SendStatic.left - DialogMain.left - 4), 
	                                        (SendStatic.top - DialogMain.top - 23), 
	                                        (SendStatic.Width() - SrSdStatic.Width() - 10), 
											(SendStatic.Height()));

	GetDlgItem(IDC_EDIT_SEND)->MoveWindow((SendEdit.left - DialogMain.left - 4), 
	                                      (SendEdit.top - DialogMain.top - 23), 
		                                  (SendEdit.Width() - SrSdStatic.Width() - 10), 
										  (SendEdit.Height()));
}

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

void CMySScomDlg::TrytoSrSendData(CString InputStr, BOOL NeedHex)
{
	assert(m_SrSendEnable == TRUE);
	
	if (InputStr.GetLength() <= 0) {
		MessageBox("发送窗口内容为空，未发送任何数据！    ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	if (NeedHex == TRUE) {                                           // 如果需要以16进制发送
		
		CByteArray SendData;
		int len;                                                     // 此处返回的len可以用于计算发送了多少个十六进制数
		
		len = String2Hex(InputStr, SendData);
		
		m_ctrlComm.SetOutput(COleVariant(SendData));                 // 发送十六进制数据
		
		SendedData += len;                                           // 发送字节数累加
		
	} else {
		
		m_ctrlComm.SetOutput(COleVariant(InputStr));                 // 发送ASCII字符数据
		
		SendedData += InputStr.GetLength();                          // 发送字节数累加
	}
	
	UpdateStatusBarNow();                                            // 更新状态栏统计数据的显示
}

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


/* ==================================== 自定义函数区--结束 ===================================== */


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ================================== 高级发送功能处理--结束 =================================== */


void CMySScomDlg::OnCheckSrAuto() 
{
	assert(m_SrSendEnable == TRUE);
	
	m_Check_LoopSend = !m_Check_LoopSend;
	
	if (m_Check_LoopSend) {

		if (GetSrValidDataNo() == 0) {

			MessageBox("貌似您尚未输入任何需要的发送的内容，叫我发送什么呢？~~~     ", "提示", MB_OK + MB_ICONINFORMATION);
			
			m_Check_LoopSend = FALSE;
			UpdateData(FALSE);                                       // 取消复选框被选中的状态
			
			return;
		}
		
		NeedLoopSendData();
		
	} else {
		
		Loop_Counter = 0;
		KillTimer(Timer_No_LoopSend);                                // 取消自动发送功能
		
		GetDlgItem(IDC_EDIT_SRAUTO)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_SRAUTO)->EnableWindow(TRUE);
	}
}

void CMySScomDlg::OnCheckSrSend01() 
{
	m_Check_SrSend_01 = !m_Check_SrSend_01;
}

void CMySScomDlg::OnCheckSrSend02() 
{
	m_Check_SrSend_02 = !m_Check_SrSend_02;
}

void CMySScomDlg::OnCheckSrSend03() 
{
	m_Check_SrSend_03 = !m_Check_SrSend_03;
}

void CMySScomDlg::OnCheckSrSend04() 
{
	m_Check_SrSend_04 = !m_Check_SrSend_04;
}

void CMySScomDlg::OnCheckSrSend05() 
{
	m_Check_SrSend_05 = !m_Check_SrSend_05;
}

void CMySScomDlg::OnCheckSrSend06() 
{
	m_Check_SrSend_06 = !m_Check_SrSend_06;
}

void CMySScomDlg::OnCheckSrSend07() 
{
	m_Check_SrSend_07 = !m_Check_SrSend_07;
}

void CMySScomDlg::OnCheckSrSend08() 
{
	m_Check_SrSend_08 = !m_Check_SrSend_08;
}

void CMySScomDlg::OnCheckSrSend09() 
{
	m_Check_SrSend_09 = !m_Check_SrSend_09;
}

void CMySScomDlg::OnCheckSrSend10() 
{
	m_Check_SrSend_10 = !m_Check_SrSend_10;
}

void CMySScomDlg::OnCheckSrSend11() 
{
	m_Check_SrSend_11 = !m_Check_SrSend_11;
}

void CMySScomDlg::OnCheckSrSend12() 
{
	m_Check_SrSend_12 = !m_Check_SrSend_12;
}

void CMySScomDlg::OnCheckSrSend13() 
{
	m_Check_SrSend_13 = !m_Check_SrSend_13;
}

void CMySScomDlg::OnCheckSrSend14() 
{
	m_Check_SrSend_14 = !m_Check_SrSend_14;
}

void CMySScomDlg::OnCheckSrSend15() 
{
	m_Check_SrSend_15 = !m_Check_SrSend_15;
}

void CMySScomDlg::OnCheckSrSend16() 
{
	m_Check_SrSend_16 = !m_Check_SrSend_16;
}

void CMySScomDlg::OnCheckSrSend17() 
{
	m_Check_SrSend_17 = !m_Check_SrSend_17;
}

void CMySScomDlg::OnCheckSrSend18() 
{
	m_Check_SrSend_18 = !m_Check_SrSend_18;
}

void CMySScomDlg::OnCheckSrSend19() 
{
	m_Check_SrSend_19 = !m_Check_SrSend_19;
}

void CMySScomDlg::OnCheckSrSend20() 
{
	m_Check_SrSend_20 = !m_Check_SrSend_20;
}

void CMySScomDlg::OnButtonSrSend01() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR01, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_01);
}

void CMySScomDlg::OnButtonSrSend02() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR02, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_02);
}

void CMySScomDlg::OnButtonSrSend03() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR03, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_03);
}

void CMySScomDlg::OnButtonSrSend04() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR04, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_04);
}

void CMySScomDlg::OnButtonSrSend05() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR05, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_05);
}

void CMySScomDlg::OnButtonSrSend06() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR06, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_06);
}

void CMySScomDlg::OnButtonSrSend07() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR07, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_07);
}

void CMySScomDlg::OnButtonSrSend08() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR08, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_08);
}

void CMySScomDlg::OnButtonSrSend09() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR09, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_09);
}

void CMySScomDlg::OnButtonSrSend10() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR10, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_10);
}

void CMySScomDlg::OnButtonSrSend11() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR11, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_11);
}

void CMySScomDlg::OnButtonSrSend12() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR12, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_12);
}

void CMySScomDlg::OnButtonSrSend13() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR13, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_13);
}

void CMySScomDlg::OnButtonSrSend14() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR14, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_14);
}

void CMySScomDlg::OnButtonSrSend15() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR15, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_15);
}

void CMySScomDlg::OnButtonSrSend16() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR16, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_16);
}

void CMySScomDlg::OnButtonSrSend17() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR17, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_17);
}

void CMySScomDlg::OnButtonSrSend18() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR18, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_18);
}

void CMySScomDlg::OnButtonSrSend19() 
{
	assert(m_SrSendEnable == TRUE);
	
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SR19, TempStr);
	
	TrytoSrSendData(TempStr, m_Check_SrSend_19);
}

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


void CMySScomDlg::OnButtonONOFF() 
{
	CString TempStr, SettingStr;
    
	if (m_PortOpened == TRUE) {                                      // 如果串口已经打开，那么执行关闭操作

		if (m_Check_AutoSend) {
			MessageBox("请首先停用自动发送功能再尝试关闭串口    ", "提示", MB_OK + MB_ICONEXCLAMATION);
			return;
		}

		if (m_SrSendEnable) {                                        // 如果处于扩展发送状态下，切换回普通发送状态
			OnButtonSrSend();
		}
		
		m_ctrlComm.SetPortOpen(FALSE);

		MessageBox("◆◆◆   成功关闭串口!   ◆◆◆    ", "提示", MB_OK + MB_ICONINFORMATION);

		SetDlgItemText(IDC_BUTTON_ONOFF, "打开串口");

		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DATA)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_STOP)->EnableWindow(TRUE);

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

		MessageBox("※※※   成功打开串口!   ※※※    ", "恭喜", MB_OK + MB_ICONINFORMATION);

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
		
		SetControlStatus(TRUE);                                      // 启用各个按钮控件
		
		SetDlgItemText(IDC_BUTTON_ONOFF, "关闭串口");

		GetDlgItem(IDC_COMBO_COMNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_STOP)->EnableWindow(FALSE);		

	} else {

        MessageBox("打开串口失败，该串口可能正在使用中...    ", "提示", MB_OK + MB_ICONERROR);
	}
}

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
	CFile   MyFile;	                                                 // 定义文件类
	int     nLength;
	CString Temp_String;
	
	CTime   NowTime  = CTime::GetCurrentTime();	                     // 获取现在时间
	CString FileName = NowTime.Format("%y-%m-%d %H-%M-%S") + ".txt"; // 指定文件名
	
	GetDlgItemText(IDC_EDIT_RECV, m_Edit_Recv);
	
	nLength = m_Edit_Recv.GetLength();                               // 获取长度
	
	if (nLength <= 0) {
		MessageBox("尚未接收到任何内容，无须保存！          ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	if (MyFile.Open(RecordPath + FileName, CFile::modeCreate | CFile::modeReadWrite) == 0) {
		Temp_String = "文件 " + FileName + " 创建失败！         ";
		MessageBox(Temp_String, "抱歉", MB_OK + MB_ICONWARNING);
		return;
	} else {
		Temp_String = "文件 " + FileName + " 创建成功！         ";
		MessageBox(Temp_String, "恭喜", MB_OK + MB_ICONINFORMATION);
	}
	
	MyFile.Write(m_Edit_Recv, nLength);	                             // 写入文本文件
	MyFile.Close();	                                                 // 关闭文件
}

void CMySScomDlg::OnButtonRead() 
{
	assert(m_SrSendEnable == FALSE);
	
	CFile myFile;

	if (m_Check_AutoSend) {
		MessageBox("自动发送功能已开启，请先停用之！    ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	CFileDialog dlg(TRUE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		            "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*|");
	
	if (dlg.DoModal() != IDOK) {
		return;
	}
	
	CString FilePath = dlg.GetPathName();						     // 保存文件的路径
		
	if (myFile.Open(FilePath, CFile::modeRead) == 0) {
		MessageBox("读取文件失败，请确认路径正确且文件未处于打开状态！    ", "提示", MB_OK + MB_ICONINFORMATION);
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
	assert(m_SrSendEnable == FALSE);
	
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
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);
	
	if (m_Edit_Send.GetLength() <= 0) {
		MessageBox("发送窗口内容为空，未发送任何数据！    ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	GetDlgItemText(IDC_BUTTON_SEND, TempStr);

	if (TempStr == "发送数据") {
		SendEditDatatoComm();
	}
	
	if (TempStr == "取消发送") {
		Send_Status  = SEND_SHORT_DATA;
		KillTimer(Timer_No_SendFile);
		Send_Counter = 0;

		SetSendingStatus(TRUE);

		SetDlgItemText(IDC_BUTTON_SEND, "发送数据");
	}
}

void CMySScomDlg::OnButtonCount() 
{
	RecvedData = 0;
	SendedData = 0;

	UpdateStatusBarNow();                                            // 更新状态栏的统计数据显示
}

void CMySScomDlg::OnButtonSrSend() 
{
	if (m_SrSendEnable == TRUE) {                                    // 如果已经启用高级发送功能，则禁用之

		if (m_Check_LoopSend) {

			MessageBox("自动发送功能已开启，请先停用之！    ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		}

		HideSrSendArea();

		m_SrSendEnable = FALSE;

		SetDlgItemText(IDC_BUTTON_SRSEND, "高级发送");

		SwitchSendStatus(TRUE);

	} else {                                                         // 如果没有启用高级发送功能，则启用之

		if (m_Check_AutoSend) {

			MessageBox("自动发送功能已开启，请先停用之！    ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		}

		if (Send_Status == SEND_LONG_FILE) {

			MessageBox("当前缓冲区的数据尚未发送完成，请稍后再操作！     ", "提示", MB_OK + MB_ICONINFORMATION);
			return;
		}

		ShowSrSendArea();

		m_SrSendEnable = TRUE;

		SetDlgItemText(IDC_BUTTON_SRSEND, "普通发送");

		SwitchSendStatus(FALSE);
	}
	
	INIT_EASYSIZE;                                                   // 重新初始化各个控件的位置
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
	assert(m_SrSendEnable == FALSE);
	
	m_Check_AutoSend = !m_Check_AutoSend;

	GetDlgItemText(IDC_EDIT_SEND, m_Edit_Send);

	if (m_Edit_Send.GetLength() <= 0) {
		MessageBox("貌似发送区为空吧，请问您老想让我发送什么东东？    ", "提示", MB_OK + MB_ICONINFORMATION);
		m_Check_AutoSend = FALSE;
		UpdateData(FALSE);
		return;
	}

	if (m_Check_AutoSend) {

		if (m_Edit_Send.GetLength() >= MAX_SEND_BYTE) {              // 确保输入的数据不会过长

			MessageBox("您输入的数据过长，无法一次发送完成。请分批输入或者以文件形式发送......       ", "提示", MB_OK + MB_ICONINFORMATION);
			m_Check_AutoSend = FALSE;
			UpdateData(FALSE);
			return;
		}

		NeedAutoSendData();                                          // 开始尝试自动发送数据

	} else {

		KillTimer(Timer_No_AutoSend);                                // 否则，用户取消了自动发送的功能
		GetDlgItem(IDC_EDIT_TIMER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_MS)->EnableWindow(TRUE);

		SetSendButtonStatus(TRUE);                                   // 重新启用发送区各个按钮
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
	InitiateSrSendArea();                                            // 初始化不显示高级发送区内容

	m_Combo_ComNo.SetCurSel(0);
	m_Combo_Baud.SetCurSel(2);
	m_Combo_Data.SetCurSel(3);
	m_Combo_Stop.SetCurSel(1);

	GetDlgItem(IDC_CHECK_AUTOSAVE)->EnableWindow(FALSE);

	SetControlStatus(FALSE);                                         // 首先禁用各个按钮控件

	m_bRecvPause = TRUE;
	m_bSendPause  = FALSE;
	m_PortOpened  = FALSE;

	StrRecved = "";
	StrToSend = "";

	Send_Status  = SEND_SHORT_DATA;
	Send_Counter = 0;
	Loop_Counter = 0;

	RecvedData = 0;
	SendedData = 0;

	CreateDirectory(RecordPath, NULL);                               // 创建Record文件夹，用于保存数据

	SetTimer(Timer_No_StatusBar, 1000, NULL);
	
	// CG: The following block was added by the ToolTips component.
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
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_READ),     IDS_STRING_012);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_RESPITE),  IDS_STRING_013);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_REIPUT),   IDS_STRING_014);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SEND),     IDS_STRING_015);
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK_HEXSEND),   IDS_STRING_016);
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK_AUTOSEND),  IDS_STRING_017);
		m_tooltip.AddTool(GetDlgItem(IDC_EDIT_TIMER),      IDS_STRING_018);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_COUNT),    IDS_STRING_019);
	}

	INIT_EASYSIZE;                                                   // 初始化各个控件的位置

	InitiateMainFrame();                                             // 初始化主界面的大小

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
	} else if (nIDEvent == Timer_No_LoopSend) {                      // 处于高级循环发送状态
		ContinueLoopSrSend();
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

	UPDATE_EASYSIZE;

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);      // 同步状态栏的位置
}

void CMySScomDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);

	EASYSIZE_MINSIZE(854, 546, fwSide, pRect);                       // 限制窗体的最小尺寸
}

void CMySScomDlg::OnOnCommMscomm() 
{
	VARIANT       Input_Vrt;
    COleSafeArray Input_Ary;
    LONG RecvLen, i;
    BYTE RecvData[2048];                                             // 设置BYTE数组
    CString TempStr;

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

