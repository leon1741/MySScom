// DialogSrSend.cpp : implementation file
//

#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogSrSend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSrSend dialog


CDialogSrSend::CDialogSrSend(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSrSend::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSrSend)
	m_Check_01 = FALSE;
	m_Check_02 = FALSE;
	m_Check_03 = FALSE;
	m_Check_04 = FALSE;
	m_Check_05 = FALSE;
	m_Check_06 = FALSE;
	m_Check_07 = FALSE;
	m_Check_08 = FALSE;
	m_Check_09 = FALSE;
	m_Check_10 = FALSE;
	m_Check_11 = FALSE;
	m_Check_12 = FALSE;
	m_Check_13 = FALSE;
	m_Check_14 = FALSE;
	m_Check_15 = FALSE;
	m_Check_16 = FALSE;
	m_Check_17 = FALSE;
	m_Check_18 = FALSE;
	m_Check_19 = FALSE;
	m_Check_20 = FALSE;
	m_Check_21 = FALSE;
	m_Check_22 = FALSE;
	m_Check_23 = FALSE;
	m_Check_24 = FALSE;
	m_Check_25 = FALSE;
	m_Check_26 = FALSE;
	m_Check_27 = FALSE;
	m_Check_28 = FALSE;
	m_Check_29 = FALSE;
	m_Check_30 = FALSE;
	m_Check_31 = FALSE;
	m_Check_32 = FALSE;
	m_Check_33 = FALSE;
	m_Check_34 = FALSE;
	m_Check_35 = FALSE;
	m_Check_36 = FALSE;
	m_Check_37 = FALSE;
	m_Check_38 = FALSE;
	m_Check_39 = FALSE;
	m_Check_40 = FALSE;
	m_Check_AutoSend = FALSE;
	//}}AFX_DATA_INIT
}


void CDialogSrSend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSrSend)
	DDX_Check(pDX, IDC_CHECK_01, m_Check_01);
	DDX_Check(pDX, IDC_CHECK_02, m_Check_02);
	DDX_Check(pDX, IDC_CHECK_03, m_Check_03);
	DDX_Check(pDX, IDC_CHECK_04, m_Check_04);
	DDX_Check(pDX, IDC_CHECK_05, m_Check_05);
	DDX_Check(pDX, IDC_CHECK_06, m_Check_06);
	DDX_Check(pDX, IDC_CHECK_07, m_Check_07);
	DDX_Check(pDX, IDC_CHECK_08, m_Check_08);
	DDX_Check(pDX, IDC_CHECK_09, m_Check_09);
	DDX_Check(pDX, IDC_CHECK_10, m_Check_10);
	DDX_Check(pDX, IDC_CHECK_11, m_Check_11);
	DDX_Check(pDX, IDC_CHECK_12, m_Check_12);
	DDX_Check(pDX, IDC_CHECK_13, m_Check_13);
	DDX_Check(pDX, IDC_CHECK_14, m_Check_14);
	DDX_Check(pDX, IDC_CHECK_15, m_Check_15);
	DDX_Check(pDX, IDC_CHECK_16, m_Check_16);
	DDX_Check(pDX, IDC_CHECK_17, m_Check_17);
	DDX_Check(pDX, IDC_CHECK_18, m_Check_18);
	DDX_Check(pDX, IDC_CHECK_19, m_Check_19);
	DDX_Check(pDX, IDC_CHECK_20, m_Check_20);
	DDX_Check(pDX, IDC_CHECK_21, m_Check_21);
	DDX_Check(pDX, IDC_CHECK_22, m_Check_22);
	DDX_Check(pDX, IDC_CHECK_23, m_Check_23);
	DDX_Check(pDX, IDC_CHECK_24, m_Check_24);
	DDX_Check(pDX, IDC_CHECK_25, m_Check_25);
	DDX_Check(pDX, IDC_CHECK_26, m_Check_26);
	DDX_Check(pDX, IDC_CHECK_27, m_Check_27);
	DDX_Check(pDX, IDC_CHECK_28, m_Check_28);
	DDX_Check(pDX, IDC_CHECK_29, m_Check_29);
	DDX_Check(pDX, IDC_CHECK_30, m_Check_30);
	DDX_Check(pDX, IDC_CHECK_31, m_Check_31);
	DDX_Check(pDX, IDC_CHECK_32, m_Check_32);
	DDX_Check(pDX, IDC_CHECK_33, m_Check_33);
	DDX_Check(pDX, IDC_CHECK_34, m_Check_34);
	DDX_Check(pDX, IDC_CHECK_35, m_Check_35);
	DDX_Check(pDX, IDC_CHECK_36, m_Check_36);
	DDX_Check(pDX, IDC_CHECK_37, m_Check_37);
	DDX_Check(pDX, IDC_CHECK_38, m_Check_38);
	DDX_Check(pDX, IDC_CHECK_39, m_Check_39);
	DDX_Check(pDX, IDC_CHECK_40, m_Check_40);
	DDX_Check(pDX, IDC_CHECK_AUTOSEND, m_Check_AutoSend);
	DDX_Text(pDX, IDC_EDIT_AUTOTIME, m_Edit_AutoTime);
	DDV_MaxChars(pDX, m_Edit_AutoTime, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSrSend, CDialog)
	//{{AFX_MSG_MAP(CDialogSrSend)
	ON_BN_CLICKED(IDC_CHECK_AUTOSEND, OnCheckAutoSend)
	ON_BN_CLICKED(IDC_BUTTON_EXPAND, OnButtonExpand)
	ON_BN_CLICKED(IDC_BUTTON_SEND01, OnButtonSend01)
	ON_BN_CLICKED(IDC_BUTTON_SEND02, OnButtonSend02)
	ON_BN_CLICKED(IDC_BUTTON_SEND03, OnButtonSend03)
	ON_BN_CLICKED(IDC_BUTTON_SEND04, OnButtonSend04)
	ON_BN_CLICKED(IDC_BUTTON_SEND05, OnButtonSend05)
	ON_BN_CLICKED(IDC_BUTTON_SEND06, OnButtonSend06)
	ON_BN_CLICKED(IDC_BUTTON_SEND07, OnButtonSend07)
	ON_BN_CLICKED(IDC_BUTTON_SEND08, OnButtonSend08)
	ON_BN_CLICKED(IDC_BUTTON_SEND09, OnButtonSend09)
	ON_BN_CLICKED(IDC_BUTTON_SEND10, OnButtonSend10)
	ON_BN_CLICKED(IDC_BUTTON_SEND11, OnButtonSend11)
	ON_BN_CLICKED(IDC_BUTTON_SEND12, OnButtonSend12)
	ON_BN_CLICKED(IDC_BUTTON_SEND13, OnButtonSend13)
	ON_BN_CLICKED(IDC_BUTTON_SEND14, OnButtonSend14)
	ON_BN_CLICKED(IDC_BUTTON_SEND15, OnButtonSend15)
	ON_BN_CLICKED(IDC_BUTTON_SEND16, OnButtonSend16)
	ON_BN_CLICKED(IDC_BUTTON_SEND17, OnButtonSend17)
	ON_BN_CLICKED(IDC_BUTTON_SEND18, OnButtonSend18)
	ON_BN_CLICKED(IDC_BUTTON_SEND19, OnButtonSend19)
	ON_BN_CLICKED(IDC_BUTTON_SEND20, OnButtonSend20)
	ON_BN_CLICKED(IDC_BUTTON_SEND21, OnButtonSend21)
	ON_BN_CLICKED(IDC_BUTTON_SEND22, OnButtonSend22)
	ON_BN_CLICKED(IDC_BUTTON_SEND23, OnButtonSend23)
	ON_BN_CLICKED(IDC_BUTTON_SEND24, OnButtonSend24)
	ON_BN_CLICKED(IDC_BUTTON_SEND25, OnButtonSend25)
	ON_BN_CLICKED(IDC_BUTTON_SEND26, OnButtonSend26)
	ON_BN_CLICKED(IDC_BUTTON_SEND27, OnButtonSend27)
	ON_BN_CLICKED(IDC_BUTTON_SEND28, OnButtonSend28)
	ON_BN_CLICKED(IDC_BUTTON_SEND29, OnButtonSend29)
	ON_BN_CLICKED(IDC_BUTTON_SEND30, OnButtonSend30)
	ON_BN_CLICKED(IDC_BUTTON_SEND31, OnButtonSend31)
	ON_BN_CLICKED(IDC_BUTTON_SEND32, OnButtonSend32)
	ON_BN_CLICKED(IDC_BUTTON_SEND33, OnButtonSend33)
	ON_BN_CLICKED(IDC_BUTTON_SEND34, OnButtonSend34)
	ON_BN_CLICKED(IDC_BUTTON_SEND35, OnButtonSend35)
	ON_BN_CLICKED(IDC_BUTTON_SEND36, OnButtonSend36)
	ON_BN_CLICKED(IDC_BUTTON_SEND37, OnButtonSend37)
	ON_BN_CLICKED(IDC_BUTTON_SEND38, OnButtonSend38)
	ON_BN_CLICKED(IDC_BUTTON_SEND39, OnButtonSend39)
	ON_BN_CLICKED(IDC_BUTTON_SEND40, OnButtonSend40)
	ON_BN_CLICKED(IDC_CHECK_01, OnCheck01)
	ON_BN_CLICKED(IDC_CHECK_02, OnCheck02)
	ON_BN_CLICKED(IDC_CHECK_03, OnCheck03)
	ON_BN_CLICKED(IDC_CHECK_04, OnCheck04)
	ON_BN_CLICKED(IDC_CHECK_05, OnCheck05)
	ON_BN_CLICKED(IDC_CHECK_06, OnCheck06)
	ON_BN_CLICKED(IDC_CHECK_07, OnCheck07)
	ON_BN_CLICKED(IDC_CHECK_08, OnCheck08)
	ON_BN_CLICKED(IDC_CHECK_09, OnCheck09)
	ON_BN_CLICKED(IDC_CHECK_10, OnCheck10)
	ON_BN_CLICKED(IDC_CHECK_11, OnCheck11)
	ON_BN_CLICKED(IDC_CHECK_12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK_13, OnCheck13)
	ON_BN_CLICKED(IDC_CHECK_14, OnCheck14)
	ON_BN_CLICKED(IDC_CHECK_15, OnCheck15)
	ON_BN_CLICKED(IDC_CHECK_16, OnCheck16)
	ON_BN_CLICKED(IDC_CHECK_17, OnCheck17)
	ON_BN_CLICKED(IDC_CHECK_18, OnCheck18)
	ON_BN_CLICKED(IDC_CHECK_19, OnCheck19)
	ON_BN_CLICKED(IDC_CHECK_20, OnCheck20)
	ON_BN_CLICKED(IDC_CHECK_21, OnCheck21)
	ON_BN_CLICKED(IDC_CHECK_22, OnCheck22)
	ON_BN_CLICKED(IDC_CHECK_23, OnCheck23)
	ON_BN_CLICKED(IDC_CHECK_24, OnCheck24)
	ON_BN_CLICKED(IDC_CHECK_25, OnCheck25)
	ON_BN_CLICKED(IDC_CHECK_26, OnCheck26)
	ON_BN_CLICKED(IDC_CHECK_27, OnCheck27)
	ON_BN_CLICKED(IDC_CHECK_28, OnCheck28)
	ON_BN_CLICKED(IDC_CHECK_29, OnCheck29)
	ON_BN_CLICKED(IDC_CHECK_30, OnCheck30)
	ON_BN_CLICKED(IDC_CHECK_31, OnCheck31)
	ON_BN_CLICKED(IDC_CHECK_32, OnCheck32)
	ON_BN_CLICKED(IDC_CHECK_33, OnCheck33)
	ON_BN_CLICKED(IDC_CHECK_34, OnCheck34)
	ON_BN_CLICKED(IDC_CHECK_35, OnCheck35)
	ON_BN_CLICKED(IDC_CHECK_36, OnCheck36)
	ON_BN_CLICKED(IDC_CHECK_37, OnCheck37)
	ON_BN_CLICKED(IDC_CHECK_38, OnCheck38)
	ON_BN_CLICKED(IDC_CHECK_39, OnCheck39)
	ON_BN_CLICKED(IDC_CHECK_40, OnCheck40)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊ�ڲ����ߺ��� ===================================== */


/**************************************************************************************************
**  ��������:  EditDataValid
**  ��������:  �ж�edit�ؼ��ڵ������Ƿ���Ч
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CDialogSrSend::EditDataValid(int EditID)
{
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
**  ���ز���:  ����������Ч�ı༭�����ţ�ȫ��Ч�򷵻�0
**************************************************************************************************/
int CDialogSrSend::GetSrValidDataNo(void)
{
	if (s_expandmode == FALSE) {                                               // ����չ����ģʽ�£�ֻ�ж����20��
		if (EditDataValid(IDC_EDIT_01) == TRUE) {
			return IDC_EDIT_01;
		} else if (EditDataValid(IDC_EDIT_02) == TRUE) {
			return IDC_EDIT_02;
		} else if (EditDataValid(IDC_EDIT_03) == TRUE) {
			return IDC_EDIT_03;
		} else if (EditDataValid(IDC_EDIT_04) == TRUE) {
			return IDC_EDIT_04;
		} else if (EditDataValid(IDC_EDIT_05) == TRUE) {
			return IDC_EDIT_05;
		} else if (EditDataValid(IDC_EDIT_06) == TRUE) {
			return IDC_EDIT_06;
		} else if (EditDataValid(IDC_EDIT_07) == TRUE) {
			return IDC_EDIT_07;
		} else if (EditDataValid(IDC_EDIT_08) == TRUE) {
			return IDC_EDIT_08;
		} else if (EditDataValid(IDC_EDIT_09) == TRUE) {
			return IDC_EDIT_09;
		} else if (EditDataValid(IDC_EDIT_10) == TRUE) {
			return IDC_EDIT_10;
		} else if (EditDataValid(IDC_EDIT_11) == TRUE) {
			return IDC_EDIT_11;
		} else if (EditDataValid(IDC_EDIT_12) == TRUE) {
			return IDC_EDIT_12;
		} else if (EditDataValid(IDC_EDIT_13) == TRUE) {
			return IDC_EDIT_13;
		} else if (EditDataValid(IDC_EDIT_14) == TRUE) {
			return IDC_EDIT_14;
		} else if (EditDataValid(IDC_EDIT_15) == TRUE) {
			return IDC_EDIT_15;
		} else if (EditDataValid(IDC_EDIT_16) == TRUE) {
			return IDC_EDIT_16;
		} else if (EditDataValid(IDC_EDIT_17) == TRUE) {
			return IDC_EDIT_17;
		} else if (EditDataValid(IDC_EDIT_18) == TRUE) {
			return IDC_EDIT_18;
		} else if (EditDataValid(IDC_EDIT_19) == TRUE) {
			return IDC_EDIT_19;
		} else if (EditDataValid(IDC_EDIT_20) == TRUE) {
			return IDC_EDIT_20;
		} else {
			return 0;
		}
	} else {                                                                   // ��չ����ģʽ�£��ж�ȫ��40��
		if (EditDataValid(IDC_EDIT_01) == TRUE) {
			return IDC_EDIT_01;
		} else if (EditDataValid(IDC_EDIT_02) == TRUE) {
			return IDC_EDIT_02;
		} else if (EditDataValid(IDC_EDIT_03) == TRUE) {
			return IDC_EDIT_03;
		} else if (EditDataValid(IDC_EDIT_04) == TRUE) {
			return IDC_EDIT_04;
		} else if (EditDataValid(IDC_EDIT_05) == TRUE) {
			return IDC_EDIT_05;
		} else if (EditDataValid(IDC_EDIT_06) == TRUE) {
			return IDC_EDIT_06;
		} else if (EditDataValid(IDC_EDIT_07) == TRUE) {
			return IDC_EDIT_07;
		} else if (EditDataValid(IDC_EDIT_08) == TRUE) {
			return IDC_EDIT_08;
		} else if (EditDataValid(IDC_EDIT_09) == TRUE) {
			return IDC_EDIT_09;
		} else if (EditDataValid(IDC_EDIT_10) == TRUE) {
			return IDC_EDIT_10;
		} else if (EditDataValid(IDC_EDIT_11) == TRUE) {
			return IDC_EDIT_11;
		} else if (EditDataValid(IDC_EDIT_12) == TRUE) {
			return IDC_EDIT_12;
		} else if (EditDataValid(IDC_EDIT_13) == TRUE) {
			return IDC_EDIT_13;
		} else if (EditDataValid(IDC_EDIT_14) == TRUE) {
			return IDC_EDIT_14;
		} else if (EditDataValid(IDC_EDIT_15) == TRUE) {
			return IDC_EDIT_15;
		} else if (EditDataValid(IDC_EDIT_16) == TRUE) {
			return IDC_EDIT_16;
		} else if (EditDataValid(IDC_EDIT_17) == TRUE) {
			return IDC_EDIT_17;
		} else if (EditDataValid(IDC_EDIT_18) == TRUE) {
			return IDC_EDIT_18;
		} else if (EditDataValid(IDC_EDIT_19) == TRUE) {
			return IDC_EDIT_19;
		} else if (EditDataValid(IDC_EDIT_20) == TRUE) {
			return IDC_EDIT_20;
		} else if (EditDataValid(IDC_EDIT_21) == TRUE) {
			return IDC_EDIT_21;
		} else if (EditDataValid(IDC_EDIT_22) == TRUE) {
			return IDC_EDIT_22;
		} else if (EditDataValid(IDC_EDIT_23) == TRUE) {
			return IDC_EDIT_23;
		} else if (EditDataValid(IDC_EDIT_24) == TRUE) {
			return IDC_EDIT_24;
		} else if (EditDataValid(IDC_EDIT_25) == TRUE) {
			return IDC_EDIT_25;
		} else if (EditDataValid(IDC_EDIT_26) == TRUE) {
			return IDC_EDIT_26;
		} else if (EditDataValid(IDC_EDIT_27) == TRUE) {
			return IDC_EDIT_27;
		} else if (EditDataValid(IDC_EDIT_28) == TRUE) {
			return IDC_EDIT_28;
		} else if (EditDataValid(IDC_EDIT_29) == TRUE) {
			return IDC_EDIT_29;
		} else if (EditDataValid(IDC_EDIT_30) == TRUE) {
			return IDC_EDIT_30;
		} else if (EditDataValid(IDC_EDIT_31) == TRUE) {
			return IDC_EDIT_31;
		} else if (EditDataValid(IDC_EDIT_32) == TRUE) {
			return IDC_EDIT_32;
		} else if (EditDataValid(IDC_EDIT_33) == TRUE) {
			return IDC_EDIT_33;
		} else if (EditDataValid(IDC_EDIT_34) == TRUE) {
			return IDC_EDIT_34;
		} else if (EditDataValid(IDC_EDIT_35) == TRUE) {
			return IDC_EDIT_35;
		} else if (EditDataValid(IDC_EDIT_36) == TRUE) {
			return IDC_EDIT_36;
		} else if (EditDataValid(IDC_EDIT_37) == TRUE) {
			return IDC_EDIT_37;
		} else if (EditDataValid(IDC_EDIT_38) == TRUE) {
			return IDC_EDIT_38;
		} else if (EditDataValid(IDC_EDIT_39) == TRUE) {
			return IDC_EDIT_39;
		} else if (EditDataValid(IDC_EDIT_40) == TRUE) {
			return IDC_EDIT_40;
		} else {
			return 0;
		}
	}
}

/**************************************************************************************************
**  ��������:  TrytoSendData
**  ��������:  ���Է�������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogSrSend::TrytoSendData(CString InputStr, BOOL NeedHex)
{	
	CMySScomDlg *pDlg;
	
	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;
	
	if (InputStr.GetLength() <= 0) {
		MessageBox("���ʹ�������Ϊ�գ�δ�����κ����ݣ�  ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	if (InputStr.GetLength() > MAX_SEND_BYTE) {
		MessageBox("���ʹ�������̫�࣬��ɾ������֮���ٳ��ԣ�  ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}
	
	if ((pDlg->SendDatatoComm(InputStr, NeedHex)) == FALSE) {                  // �������ʧ�ܣ��Ҵ�������ģʽ����ֹͣ����
		if (m_Check_AutoSend == TRUE) {
			OnCheckAutoSend();
			UpdateData(FALSE);
		}
		MessageBox("�������CAN����֡���ݹ��������ߴ��ڷǷ��ַ�����ȷ�ϣ�......       ", "����", MB_OK + MB_ICONEXCLAMATION);
	}
}

/**************************************************************************************************
**  ��������:  TrytoContinueSend
**  ��������:  ���Լ�����������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogSrSend::TrytoContinueSend(void)
{
	if (s_expandmode == FALSE) {                                               // ����չ����ģʽ�£�ֻ�ж����20��

		if ((s_curdatacnt < IDC_EDIT_01) && (EditDataValid(IDC_EDIT_01) == TRUE)) {		
			OnButtonSend01();
			s_curdatacnt = IDC_EDIT_01;
		} else if ((s_curdatacnt < IDC_EDIT_02) && (EditDataValid(IDC_EDIT_02) == TRUE)) {
			OnButtonSend02();
			s_curdatacnt = IDC_EDIT_02;
		} else if ((s_curdatacnt < IDC_EDIT_03) && (EditDataValid(IDC_EDIT_03) == TRUE)) {
			OnButtonSend03();
			s_curdatacnt = IDC_EDIT_03;
		} else if ((s_curdatacnt < IDC_EDIT_04) && (EditDataValid(IDC_EDIT_04) == TRUE)) {
			OnButtonSend04();
			s_curdatacnt = IDC_EDIT_04;
		} else if ((s_curdatacnt < IDC_EDIT_05) && (EditDataValid(IDC_EDIT_05) == TRUE)) {
			OnButtonSend05();
			s_curdatacnt = IDC_EDIT_05;
		} else if ((s_curdatacnt < IDC_EDIT_06) && (EditDataValid(IDC_EDIT_06) == TRUE)) {
			OnButtonSend06();
			s_curdatacnt = IDC_EDIT_06;
		} else if ((s_curdatacnt < IDC_EDIT_07) && (EditDataValid(IDC_EDIT_07) == TRUE)) {
			OnButtonSend07();
			s_curdatacnt = IDC_EDIT_07;
		} else if ((s_curdatacnt < IDC_EDIT_08) && (EditDataValid(IDC_EDIT_08) == TRUE)) {
			OnButtonSend08();
			s_curdatacnt = IDC_EDIT_08;
		} else if ((s_curdatacnt < IDC_EDIT_09) && (EditDataValid(IDC_EDIT_09) == TRUE)) {
			OnButtonSend09();
			s_curdatacnt = IDC_EDIT_09;
		} else if ((s_curdatacnt < IDC_EDIT_10) && (EditDataValid(IDC_EDIT_10) == TRUE)) {
			OnButtonSend10();
			s_curdatacnt = IDC_EDIT_10;
		} else if ((s_curdatacnt < IDC_EDIT_11) && (EditDataValid(IDC_EDIT_11) == TRUE)) {
			OnButtonSend11();
			s_curdatacnt = IDC_EDIT_11;
		} else if ((s_curdatacnt < IDC_EDIT_12) && (EditDataValid(IDC_EDIT_12) == TRUE)) {
			OnButtonSend12();
			s_curdatacnt = IDC_EDIT_12;
		} else if ((s_curdatacnt < IDC_EDIT_13) && (EditDataValid(IDC_EDIT_13) == TRUE)) {
			OnButtonSend13();
			s_curdatacnt = IDC_EDIT_13;
		} else if ((s_curdatacnt < IDC_EDIT_14) && (EditDataValid(IDC_EDIT_14) == TRUE)) {
			OnButtonSend14();
			s_curdatacnt = IDC_EDIT_14;
		} else if ((s_curdatacnt < IDC_EDIT_15) && (EditDataValid(IDC_EDIT_15) == TRUE)) {
			OnButtonSend15();
			s_curdatacnt = IDC_EDIT_15;
		} else if ((s_curdatacnt < IDC_EDIT_16) && (EditDataValid(IDC_EDIT_16) == TRUE)) {
			OnButtonSend16();
			s_curdatacnt = IDC_EDIT_16;
		} else if ((s_curdatacnt < IDC_EDIT_17) && (EditDataValid(IDC_EDIT_17) == TRUE)) {
			OnButtonSend17();
			s_curdatacnt = IDC_EDIT_17;
		} else if ((s_curdatacnt < IDC_EDIT_18) && (EditDataValid(IDC_EDIT_18) == TRUE)) {
			OnButtonSend18();
			s_curdatacnt = IDC_EDIT_18;
		} else if ((s_curdatacnt < IDC_EDIT_19) && (EditDataValid(IDC_EDIT_19) == TRUE)) {
			OnButtonSend19();
			s_curdatacnt = IDC_EDIT_19;
		} else if ((s_curdatacnt < IDC_EDIT_20) && (EditDataValid(IDC_EDIT_20) == TRUE)) {
			OnButtonSend20();
			s_curdatacnt = IDC_EDIT_20;
		} else {
			s_curdatacnt = 0;
		}
	} else {                                                                   // ��չ����ģʽ�£��ж�ȫ��40��

		if ((s_curdatacnt < IDC_EDIT_01) && (EditDataValid(IDC_EDIT_01) == TRUE)) {		
			OnButtonSend01();
			s_curdatacnt = IDC_EDIT_01;
		} else if ((s_curdatacnt < IDC_EDIT_02) && (EditDataValid(IDC_EDIT_02) == TRUE)) {
			OnButtonSend02();
			s_curdatacnt = IDC_EDIT_02;
		} else if ((s_curdatacnt < IDC_EDIT_03) && (EditDataValid(IDC_EDIT_03) == TRUE)) {
			OnButtonSend03();
			s_curdatacnt = IDC_EDIT_03;
		} else if ((s_curdatacnt < IDC_EDIT_04) && (EditDataValid(IDC_EDIT_04) == TRUE)) {
			OnButtonSend04();
			s_curdatacnt = IDC_EDIT_04;
		} else if ((s_curdatacnt < IDC_EDIT_05) && (EditDataValid(IDC_EDIT_05) == TRUE)) {
			OnButtonSend05();
			s_curdatacnt = IDC_EDIT_05;
		} else if ((s_curdatacnt < IDC_EDIT_06) && (EditDataValid(IDC_EDIT_06) == TRUE)) {
			OnButtonSend06();
			s_curdatacnt = IDC_EDIT_06;
		} else if ((s_curdatacnt < IDC_EDIT_07) && (EditDataValid(IDC_EDIT_07) == TRUE)) {
			OnButtonSend07();
			s_curdatacnt = IDC_EDIT_07;
		} else if ((s_curdatacnt < IDC_EDIT_08) && (EditDataValid(IDC_EDIT_08) == TRUE)) {
			OnButtonSend08();
			s_curdatacnt = IDC_EDIT_08;
		} else if ((s_curdatacnt < IDC_EDIT_09) && (EditDataValid(IDC_EDIT_09) == TRUE)) {
			OnButtonSend09();
			s_curdatacnt = IDC_EDIT_09;
		} else if ((s_curdatacnt < IDC_EDIT_10) && (EditDataValid(IDC_EDIT_10) == TRUE)) {
			OnButtonSend10();
			s_curdatacnt = IDC_EDIT_10;
		} else if ((s_curdatacnt < IDC_EDIT_11) && (EditDataValid(IDC_EDIT_11) == TRUE)) {
			OnButtonSend11();
			s_curdatacnt = IDC_EDIT_11;
		} else if ((s_curdatacnt < IDC_EDIT_12) && (EditDataValid(IDC_EDIT_12) == TRUE)) {
			OnButtonSend12();
			s_curdatacnt = IDC_EDIT_12;
		} else if ((s_curdatacnt < IDC_EDIT_13) && (EditDataValid(IDC_EDIT_13) == TRUE)) {
			OnButtonSend13();
			s_curdatacnt = IDC_EDIT_13;
		} else if ((s_curdatacnt < IDC_EDIT_14) && (EditDataValid(IDC_EDIT_14) == TRUE)) {
			OnButtonSend14();
			s_curdatacnt = IDC_EDIT_14;
		} else if ((s_curdatacnt < IDC_EDIT_15) && (EditDataValid(IDC_EDIT_15) == TRUE)) {
			OnButtonSend15();
			s_curdatacnt = IDC_EDIT_15;
		} else if ((s_curdatacnt < IDC_EDIT_16) && (EditDataValid(IDC_EDIT_16) == TRUE)) {
			OnButtonSend16();
			s_curdatacnt = IDC_EDIT_16;
		} else if ((s_curdatacnt < IDC_EDIT_17) && (EditDataValid(IDC_EDIT_17) == TRUE)) {
			OnButtonSend17();
			s_curdatacnt = IDC_EDIT_17;
		} else if ((s_curdatacnt < IDC_EDIT_18) && (EditDataValid(IDC_EDIT_18) == TRUE)) {
			OnButtonSend18();
			s_curdatacnt = IDC_EDIT_18;
		} else if ((s_curdatacnt < IDC_EDIT_19) && (EditDataValid(IDC_EDIT_19) == TRUE)) {
			OnButtonSend19();
			s_curdatacnt = IDC_EDIT_19;
		} else if ((s_curdatacnt < IDC_EDIT_20) && (EditDataValid(IDC_EDIT_20) == TRUE)) {
			OnButtonSend20();
			s_curdatacnt = IDC_EDIT_20;
		} else if ((s_curdatacnt < IDC_EDIT_21) && (EditDataValid(IDC_EDIT_21) == TRUE)) {		
			OnButtonSend21();
			s_curdatacnt = IDC_EDIT_21;
		} else if ((s_curdatacnt < IDC_EDIT_22) && (EditDataValid(IDC_EDIT_22) == TRUE)) {
			OnButtonSend22();
			s_curdatacnt = IDC_EDIT_22;
		} else if ((s_curdatacnt < IDC_EDIT_23) && (EditDataValid(IDC_EDIT_23) == TRUE)) {
			OnButtonSend23();
			s_curdatacnt = IDC_EDIT_23;
		} else if ((s_curdatacnt < IDC_EDIT_24) && (EditDataValid(IDC_EDIT_24) == TRUE)) {
			OnButtonSend24();
			s_curdatacnt = IDC_EDIT_24;
		} else if ((s_curdatacnt < IDC_EDIT_25) && (EditDataValid(IDC_EDIT_25) == TRUE)) {
			OnButtonSend25();
			s_curdatacnt = IDC_EDIT_25;
		} else if ((s_curdatacnt < IDC_EDIT_26) && (EditDataValid(IDC_EDIT_26) == TRUE)) {
			OnButtonSend26();
			s_curdatacnt = IDC_EDIT_26;
		} else if ((s_curdatacnt < IDC_EDIT_27) && (EditDataValid(IDC_EDIT_27) == TRUE)) {
			OnButtonSend27();
			s_curdatacnt = IDC_EDIT_27;
		} else if ((s_curdatacnt < IDC_EDIT_28) && (EditDataValid(IDC_EDIT_28) == TRUE)) {
			OnButtonSend28();
			s_curdatacnt = IDC_EDIT_28;
		} else if ((s_curdatacnt < IDC_EDIT_29) && (EditDataValid(IDC_EDIT_29) == TRUE)) {
			OnButtonSend29();
			s_curdatacnt = IDC_EDIT_29;
		} else if ((s_curdatacnt < IDC_EDIT_30) && (EditDataValid(IDC_EDIT_30) == TRUE)) {
			OnButtonSend30();
			s_curdatacnt = IDC_EDIT_30;
		} else if ((s_curdatacnt < IDC_EDIT_31) && (EditDataValid(IDC_EDIT_31) == TRUE)) {
			OnButtonSend31();
			s_curdatacnt = IDC_EDIT_31;
		} else if ((s_curdatacnt < IDC_EDIT_32) && (EditDataValid(IDC_EDIT_32) == TRUE)) {
			OnButtonSend32();
			s_curdatacnt = IDC_EDIT_32;
		} else if ((s_curdatacnt < IDC_EDIT_33) && (EditDataValid(IDC_EDIT_33) == TRUE)) {
			OnButtonSend33();
			s_curdatacnt = IDC_EDIT_33;
		} else if ((s_curdatacnt < IDC_EDIT_34) && (EditDataValid(IDC_EDIT_34) == TRUE)) {
			OnButtonSend34();
			s_curdatacnt = IDC_EDIT_34;
		} else if ((s_curdatacnt < IDC_EDIT_35) && (EditDataValid(IDC_EDIT_35) == TRUE)) {
			OnButtonSend35();
			s_curdatacnt = IDC_EDIT_35;
		} else if ((s_curdatacnt < IDC_EDIT_36) && (EditDataValid(IDC_EDIT_36) == TRUE)) {
			OnButtonSend36();
			s_curdatacnt = IDC_EDIT_36;
		} else if ((s_curdatacnt < IDC_EDIT_37) && (EditDataValid(IDC_EDIT_37) == TRUE)) {
			OnButtonSend37();
			s_curdatacnt = IDC_EDIT_37;
		} else if ((s_curdatacnt < IDC_EDIT_38) && (EditDataValid(IDC_EDIT_38) == TRUE)) {
			OnButtonSend38();
			s_curdatacnt = IDC_EDIT_38;
		} else if ((s_curdatacnt < IDC_EDIT_39) && (EditDataValid(IDC_EDIT_39) == TRUE)) {
			OnButtonSend39();
			s_curdatacnt = IDC_EDIT_39;
		} else if ((s_curdatacnt < IDC_EDIT_40) && (EditDataValid(IDC_EDIT_40) == TRUE)) {
			OnButtonSend40();
			s_curdatacnt = IDC_EDIT_40;
		} else {
			s_curdatacnt = 0;
		}
	}
}

/**************************************************************************************************
**  ��������:  DataisSending
**  ��������:  �Ƿ����������ڷ�����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CDialogSrSend::DataisSending(void)
{
	if (m_Check_AutoSend) {                                                    // ����Զ����͹����Ѿ���������Ϊ���������ڷ���
		return TRUE;
	} else {
		return FALSE;
	}
}

/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊ�ؼ���Ϣ���� ===================================== */


void CDialogSrSend::OnCheckAutoSend() 
{
	int Timer;
	CString TempStr;
	
	m_Check_AutoSend = !m_Check_AutoSend;
	
	if (m_Check_AutoSend) {                                                    // ������������Զ���������
		
		if (GetSrValidDataNo() == 0) {                                         // �ж��������Ƿ���Ч
			
			MessageBox("ò������δ�����κ���Ҫ�ķ��͵����ݣ����ҷ���ʲô�أ�~~~  ", "��ʾ", MB_OK + MB_ICONINFORMATION);
			
			m_Check_AutoSend = FALSE;
			UpdateData(FALSE);                                                 // ȡ����ѡ��ѡ�е�״̬
			return;
		}
		
		GetDlgItemText(IDC_EDIT_AUTOTIME, TempStr);
		
		Timer = atoi((LPSTR)(LPCTSTR)TempStr);
		
		if ((Timer > 0) && (Timer <= 10000)) {                                 // ʱ��Ϸ�
			
			SetTimer(Timer_No_SrAutoSend, Timer, NULL);                        // ������ʱ��
			s_curdatacnt = 0;
			
			GetDlgItem(IDC_EDIT_AUTOTIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_AUTOTIME)->EnableWindow(FALSE);
			
		} else {
			
			MessageBox("��ʱʱ�������0��10����֮�䣬��ȷ�ϣ�  ", "��ʾ", MB_OK + MB_ICONEXCLAMATION);
			
			SetDlgItemText(IDC_EDIT_AUTOTIME, m_Edit_AutoTime);               // ��ԭ�༭������
			
			m_Check_AutoSend = FALSE;
			UpdateData(FALSE);                                                 // ȡ����ѡ��ѡ�е�״̬
			return;
		}
		
	} else {                                                                   // ��������˳��Զ���������
		
		s_curdatacnt = 0;
		KillTimer(Timer_No_SrAutoSend);                                        // ȡ���Զ����͹���
		
		GetDlgItem(IDC_EDIT_AUTOTIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_AUTOTIME)->EnableWindow(TRUE);
	}
}

void CDialogSrSend::OnButtonExpand() 
{
	CRect rect;
	
	GetWindowRect(&rect);

	if (s_expandmode == TRUE) {
		SetWindowPos(NULL, 0, 0, rect.Width() / 2, rect.Height(), SWP_NOMOVE);
		SetDlgItemText(IDC_BUTTON_EXPAND, "20�����ݲ����ã�����չ������������ >>");
		s_expandmode = FALSE;
	} else {
		SetWindowPos(NULL, 0, 0, rect.Width() * 2, rect.Height(), SWP_NOMOVE);
		SetDlgItemText(IDC_BUTTON_EXPAND, "40�������ò��ꣿ�������أ�������� <<");
		s_expandmode = TRUE;
	}
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊ���Ͱ�ť���� ===================================== */


void CDialogSrSend::OnButtonSend01() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_01, TempStr);
	
	TrytoSendData(TempStr, m_Check_01);
}

void CDialogSrSend::OnButtonSend02() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_02, TempStr);
	
	TrytoSendData(TempStr, m_Check_02);
}

void CDialogSrSend::OnButtonSend03() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_03, TempStr);
	
	TrytoSendData(TempStr, m_Check_03);
}

void CDialogSrSend::OnButtonSend04() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_04, TempStr);
	
	TrytoSendData(TempStr, m_Check_04);
}

void CDialogSrSend::OnButtonSend05() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_05, TempStr);
	
	TrytoSendData(TempStr, m_Check_05);
}

void CDialogSrSend::OnButtonSend06() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_06, TempStr);
	
	TrytoSendData(TempStr, m_Check_06);
}

void CDialogSrSend::OnButtonSend07() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_07, TempStr);
	
	TrytoSendData(TempStr, m_Check_07);
}

void CDialogSrSend::OnButtonSend08() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_08, TempStr);
	
	TrytoSendData(TempStr, m_Check_08);
}

void CDialogSrSend::OnButtonSend09() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_09, TempStr);
	
	TrytoSendData(TempStr, m_Check_09);
}

void CDialogSrSend::OnButtonSend10() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_10, TempStr);
	
	TrytoSendData(TempStr, m_Check_10);
}

void CDialogSrSend::OnButtonSend11() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_11, TempStr);
	
	TrytoSendData(TempStr, m_Check_11);
}

void CDialogSrSend::OnButtonSend12() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_12, TempStr);
	
	TrytoSendData(TempStr, m_Check_12);
}

void CDialogSrSend::OnButtonSend13() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_13, TempStr);
	
	TrytoSendData(TempStr, m_Check_13);
}

void CDialogSrSend::OnButtonSend14() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_14, TempStr);
	
	TrytoSendData(TempStr, m_Check_14);
}

void CDialogSrSend::OnButtonSend15() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_15, TempStr);
	
	TrytoSendData(TempStr, m_Check_15);
}

void CDialogSrSend::OnButtonSend16() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_16, TempStr);
	
	TrytoSendData(TempStr, m_Check_16);
}

void CDialogSrSend::OnButtonSend17() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_17, TempStr);
	
	TrytoSendData(TempStr, m_Check_17);
}

void CDialogSrSend::OnButtonSend18() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_18, TempStr);
	
	TrytoSendData(TempStr, m_Check_18);
}

void CDialogSrSend::OnButtonSend19() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_19, TempStr);
	
	TrytoSendData(TempStr, m_Check_19);
}

void CDialogSrSend::OnButtonSend20() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_20, TempStr);
	
	TrytoSendData(TempStr, m_Check_20);
}

void CDialogSrSend::OnButtonSend21() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_21, TempStr);
	
	TrytoSendData(TempStr, m_Check_21);
}

void CDialogSrSend::OnButtonSend22() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_22, TempStr);
	
	TrytoSendData(TempStr, m_Check_22);
}

void CDialogSrSend::OnButtonSend23() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_23, TempStr);
	
	TrytoSendData(TempStr, m_Check_23);
}

void CDialogSrSend::OnButtonSend24() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_24, TempStr);
	
	TrytoSendData(TempStr, m_Check_24);
}

void CDialogSrSend::OnButtonSend25() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_25, TempStr);
	
	TrytoSendData(TempStr, m_Check_25);
}

void CDialogSrSend::OnButtonSend26() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_26, TempStr);
	
	TrytoSendData(TempStr, m_Check_26);
}

void CDialogSrSend::OnButtonSend27() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_27, TempStr);
	
	TrytoSendData(TempStr, m_Check_27);
}

void CDialogSrSend::OnButtonSend28() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_28, TempStr);
	
	TrytoSendData(TempStr, m_Check_28);
}

void CDialogSrSend::OnButtonSend29() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_29, TempStr);
	
	TrytoSendData(TempStr, m_Check_29);
}

void CDialogSrSend::OnButtonSend30() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_30, TempStr);
	
	TrytoSendData(TempStr, m_Check_30);
}

void CDialogSrSend::OnButtonSend31() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_31, TempStr);
	
	TrytoSendData(TempStr, m_Check_31);
}

void CDialogSrSend::OnButtonSend32() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_32, TempStr);
	
	TrytoSendData(TempStr, m_Check_32);
}

void CDialogSrSend::OnButtonSend33() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_33, TempStr);
	
	TrytoSendData(TempStr, m_Check_33);
}

void CDialogSrSend::OnButtonSend34() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_34, TempStr);
	
	TrytoSendData(TempStr, m_Check_34);
}

void CDialogSrSend::OnButtonSend35() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_35, TempStr);
	
	TrytoSendData(TempStr, m_Check_35);
}

void CDialogSrSend::OnButtonSend36() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_36, TempStr);
	
	TrytoSendData(TempStr, m_Check_36);
}

void CDialogSrSend::OnButtonSend37() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_37, TempStr);
	
	TrytoSendData(TempStr, m_Check_37);
}

void CDialogSrSend::OnButtonSend38() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_38, TempStr);
	
	TrytoSendData(TempStr, m_Check_38);
}

void CDialogSrSend::OnButtonSend39() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_39, TempStr);
	
	TrytoSendData(TempStr, m_Check_39);
}

void CDialogSrSend::OnButtonSend40() 
{
	CString TempStr;
	
	GetDlgItemText(IDC_EDIT_40, TempStr);
	
	TrytoSendData(TempStr, m_Check_40);
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */


void CDialogSrSend::OnCheck01() 
{
	m_Check_01 = !m_Check_01;
}

void CDialogSrSend::OnCheck02() 
{
	m_Check_02 = !m_Check_02;
}

void CDialogSrSend::OnCheck03() 
{
	m_Check_03 = !m_Check_03;
}

void CDialogSrSend::OnCheck04() 
{
	m_Check_04 = !m_Check_04;
}

void CDialogSrSend::OnCheck05() 
{
	m_Check_05 = !m_Check_05;
}

void CDialogSrSend::OnCheck06() 
{
	m_Check_06 = !m_Check_06;
}

void CDialogSrSend::OnCheck07() 
{
	m_Check_07 = !m_Check_07;
}

void CDialogSrSend::OnCheck08() 
{
	m_Check_08 = !m_Check_08;
}

void CDialogSrSend::OnCheck09() 
{
	m_Check_09 = !m_Check_09;
}

void CDialogSrSend::OnCheck10() 
{
	m_Check_10 = !m_Check_10;
}

void CDialogSrSend::OnCheck11() 
{
	m_Check_11 = !m_Check_11;
}

void CDialogSrSend::OnCheck12() 
{
	m_Check_12 = !m_Check_12;
}

void CDialogSrSend::OnCheck13() 
{
	m_Check_13 = !m_Check_13;
}

void CDialogSrSend::OnCheck14() 
{
	m_Check_14 = !m_Check_14;
}

void CDialogSrSend::OnCheck15() 
{
	m_Check_15 = !m_Check_15;
}

void CDialogSrSend::OnCheck16() 
{
	m_Check_16 = !m_Check_16;
}

void CDialogSrSend::OnCheck17() 
{
	m_Check_17 = !m_Check_17;
}

void CDialogSrSend::OnCheck18() 
{
	m_Check_18 = !m_Check_18;
}

void CDialogSrSend::OnCheck19() 
{
	m_Check_19 = !m_Check_19;
}

void CDialogSrSend::OnCheck20() 
{
	m_Check_20 = !m_Check_20;
}

void CDialogSrSend::OnCheck21() 
{
	m_Check_21 = !m_Check_21;
}

void CDialogSrSend::OnCheck22() 
{
	m_Check_22 = !m_Check_22;
}

void CDialogSrSend::OnCheck23() 
{
	m_Check_23 = !m_Check_23;
}

void CDialogSrSend::OnCheck24() 
{
	m_Check_24 = !m_Check_24;
}

void CDialogSrSend::OnCheck25() 
{
	m_Check_25 = !m_Check_25;
}

void CDialogSrSend::OnCheck26() 
{
	m_Check_26 = !m_Check_26;
}

void CDialogSrSend::OnCheck27() 
{
	m_Check_27 = !m_Check_27;
}

void CDialogSrSend::OnCheck28() 
{
	m_Check_28 = !m_Check_28;
}

void CDialogSrSend::OnCheck29() 
{
	m_Check_29 = !m_Check_29;
}

void CDialogSrSend::OnCheck30() 
{
	m_Check_30 = !m_Check_30;
}

void CDialogSrSend::OnCheck31() 
{
	m_Check_31 = !m_Check_31;
}

void CDialogSrSend::OnCheck32() 
{
	m_Check_32 = !m_Check_32;
}

void CDialogSrSend::OnCheck33() 
{
	m_Check_33 = !m_Check_33;
}

void CDialogSrSend::OnCheck34() 
{
	m_Check_34 = !m_Check_34;
}

void CDialogSrSend::OnCheck35() 
{
	m_Check_35 = !m_Check_35;
}

void CDialogSrSend::OnCheck36() 
{
	m_Check_36 = !m_Check_36;
}

void CDialogSrSend::OnCheck37() 
{
	m_Check_37 = !m_Check_37;
}

void CDialogSrSend::OnCheck38() 
{
	m_Check_38 = !m_Check_38;
}

void CDialogSrSend::OnCheck39() 
{
	m_Check_39 = !m_Check_39;
}

void CDialogSrSend::OnCheck40() 
{
	m_Check_40 = !m_Check_40;
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */


BOOL CDialogSrSend::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rect;
	
	GetWindowRect(&rect);	
	
	SetWindowPos(NULL, 0, 0, rect.Width() / 2, rect.Height(), SWP_NOMOVE);
	
	return TRUE;
}

void CDialogSrSend::OnTimer(UINT nIDEvent) 
{
	switch (nIDEvent)
	{
		case Timer_No_SrAutoSend:
			TrytoContinueSend();
			break;
			
		default:
			return;
	}
	
	CDialog::OnTimer(nIDEvent);
}


void CDialogSrSend::OnClose() 
{
	CMySScomDlg *pDlg;
	
	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;

	if (DataisSending()) {
		MessageBox("����ֹͣ�Զ�ѭ�����͹��ܣ��ٳ��Թرո߼����ʹ���......   ", "��ʾ", MB_OK + MB_ICONINFORMATION);
		return;
	}

	pDlg->InformDlgClose();                                                    // ֪ͨ�����洰���ѱ��ر�
	
	CDialog::OnClose();
}