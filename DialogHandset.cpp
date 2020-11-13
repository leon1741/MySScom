// DialogHandset.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogHandset.h"
#include "afxdialogex.h"

// CDialogHandset �Ի���

IMPLEMENT_DYNAMIC(CDialogHandset, CDialog)

CDialogHandset::CDialogHandset(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogHandset::IDD, pParent)
{
	AfxInitRichEdit();                                                         /* ��ʼ��RichEdit�ؼ� */
}

CDialogHandset::~CDialogHandset()
{
}

void CDialogHandset::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT_DISP, m_RichEdit);
	DDX_Control(pDX, IDC_STATIC_LINE1, m_Picture_Line1);
	DDX_Control(pDX, IDC_STATIC_LINE2, m_Picture_Line2);
	DDX_Control(pDX, IDC_STATIC_BAT, m_Picture_BAT);
	DDX_Control(pDX, IDC_STATIC_GPS, m_Picture_GPS);
	DDX_Control(pDX, IDC_STATIC_PHONE, m_Picture_Phone);
	DDX_Control(pDX, IDC_STATIC_SMS, m_Picture_SMS);
	DDX_Control(pDX, IDC_STATIC_GSM0, m_Picture_GSM0);
	DDX_Control(pDX, IDC_STATIC_GSM1, m_Picture_GSM1);
	DDX_Control(pDX, IDC_STATIC_GSM2, m_Picture_GSM2);
	DDX_Control(pDX, IDC_STATIC_GSM3, m_Picture_GSM3);
	DDX_Control(pDX, IDC_STATIC_GSM4, m_Picture_GSM4);
}


BEGIN_MESSAGE_MAP(CDialogHandset, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTONC, &CDialogHandset::OnBnClickedButtonc)
	ON_BN_CLICKED(IDC_BUTTONOK, &CDialogHandset::OnBnClickedButtonok)
	ON_BN_CLICKED(IDC_BUTTONUP, &CDialogHandset::OnBnClickedButtonup)
	ON_BN_CLICKED(IDC_BUTTONDOWN, &CDialogHandset::OnBnClickedButtondown)
	ON_BN_CLICKED(IDC_BUTTONSET, &CDialogHandset::OnBnClickedButtonset)
	ON_BN_CLICKED(IDC_BUTTON_1, &CDialogHandset::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CDialogHandset::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CDialogHandset::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CDialogHandset::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CDialogHandset::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CDialogHandset::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CDialogHandset::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CDialogHandset::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CDialogHandset::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_0, &CDialogHandset::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_X, &CDialogHandset::OnBnClickedButtonX)
	ON_BN_CLICKED(IDC_BUTTON_J, &CDialogHandset::OnBnClickedButtonJ)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONO, &CDialogHandset::OnBnClickedButtono)
END_MESSAGE_MAP()


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊ����ӿں��� ===================================== */

/**************************************************************************************************
**  ��������:  SendHstData
**  ��������:  ���ʹ�������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogHandset::SendHstData(char ch)
{
	char cbuf[4];

	CMySScomDlg *pDlg;

	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;
	
	cbuf[0] = -1;
	cbuf[1] = ch;
	cbuf[2] = ch;
	cbuf[3] = -1;
		
	pDlg->WriteComm(cbuf, 4);
}

/**************************************************************************************************
**  ��������:  HandleHstProtcol
**  ��������:  �����ֱ�Э������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogHandset::HandleHstProtcol(void)
{
	char dispbuf[27];

	if ((s_recv_buff[0] == 'D') && (s_recv_buff[1] == 'H')) {                  // ������ʾ����
		memcpy(&dispbuf[0], &s_recv_buff[2], 12);
		dispbuf[12] = '\r';
		dispbuf[13] = '\n';
		memcpy(&dispbuf[14], &s_recv_buff[14], 12);
		dispbuf[26] = '\0';

		SetDlgItemText(IDC_RICHEDIT_DISP, dispbuf);
		m_Picture_Line1.ShowWindow(FALSE);
		m_Picture_Line2.ShowWindow(FALSE);
	} 
	
	if ((s_recv_buff[0] == 'S') && (s_recv_buff[1] == 'R')) {                  // ����
		if (s_recv_buff[2] == 0) {
			m_Picture_Line1.ShowWindow(TRUE);
			m_Picture_Line2.ShowWindow(FALSE);
		} else {
			m_Picture_Line1.ShowWindow(FALSE);
			m_Picture_Line2.ShowWindow(TRUE);
		}
	}
	
	if ((s_recv_buff[0] == 'R') && (s_recv_buff[1] == 'S')) {                  // ��Ļ��ʼ��
		SetDlgItemText(IDC_RICHEDIT_DISP, "");
	}

	if ((s_recv_buff[0] == 'A') && (s_recv_buff[1] == 'C')) {                  // ������ʾ��

		switch (s_recv_buff[2])                                                // GSM�ź�ǿ��ָʾ
		{
			case 1:                                                            // 1��
				m_Picture_GSM0.ShowWindow(TRUE);
				m_Picture_GSM1.ShowWindow(FALSE);
				m_Picture_GSM2.ShowWindow(FALSE);
				m_Picture_GSM3.ShowWindow(FALSE);
				m_Picture_GSM4.ShowWindow(FALSE);
				break;

			case 2:                                                            // 2��
				m_Picture_GSM0.ShowWindow(FALSE);
				m_Picture_GSM1.ShowWindow(TRUE);
				m_Picture_GSM2.ShowWindow(FALSE);
				m_Picture_GSM3.ShowWindow(FALSE);
				m_Picture_GSM4.ShowWindow(FALSE);
				break;

			case 3:                                                            // 3��
				m_Picture_GSM0.ShowWindow(FALSE);
				m_Picture_GSM1.ShowWindow(FALSE);
				m_Picture_GSM2.ShowWindow(TRUE);
				m_Picture_GSM3.ShowWindow(FALSE);
				m_Picture_GSM4.ShowWindow(FALSE);
				break;

			case 4:                                                            // 4��
				m_Picture_GSM0.ShowWindow(FALSE);
				m_Picture_GSM1.ShowWindow(FALSE);
				m_Picture_GSM2.ShowWindow(FALSE);
				m_Picture_GSM3.ShowWindow(TRUE);
				m_Picture_GSM4.ShowWindow(FALSE);
				break;

			case 5:                                                            // 5��
				m_Picture_GSM0.ShowWindow(FALSE);
				m_Picture_GSM1.ShowWindow(FALSE);
				m_Picture_GSM2.ShowWindow(FALSE);
				m_Picture_GSM3.ShowWindow(FALSE);
				m_Picture_GSM4.ShowWindow(TRUE);
				break;

			case 0x0F:                                                         // ά���ϴ�״̬
				break;

			default:                                                           // ������ʾ
				m_Picture_GSM0.ShowWindow(FALSE);
				m_Picture_GSM1.ShowWindow(FALSE);
				m_Picture_GSM2.ShowWindow(FALSE);
				m_Picture_GSM3.ShowWindow(FALSE);
				m_Picture_GSM4.ShowWindow(FALSE);
				break;
		}

		switch (s_recv_buff[3])                                                // δ�ӵ绰
		{
			case 1:                                                            // ��ʾͼ��
				m_Picture_Phone.ShowWindow(TRUE);
				break;

			case 0x0F:                                                         // ά���ϴ�״̬
				break;

			default:                                                           // ������ʾ
				m_Picture_Phone.ShowWindow(FALSE);
				break;
		}

		switch (s_recv_buff[4])                                                // δ������
		{
			case 1:                                                            // ��ʾͼ��
				m_Picture_SMS.ShowWindow(TRUE);
				break;

			case 0x0F:                                                         // ά���ϴ�״̬
				break;

			default:                                                           // ������ʾ
				m_Picture_SMS.ShowWindow(FALSE);
				break;
		}

		switch (s_recv_buff[5])                                                // GPS��λͼ��
		{
			case 1:                                                            // ��ʾͼ��
				m_Picture_GPS.ShowWindow(TRUE);
				break;

			case 0x0F:                                                         // ά���ϴ�״̬
				break;

			default:                                                           // ������ʾ
				m_Picture_GPS.ShowWindow(FALSE);
				break;
		}

		switch (s_recv_buff[6])                                                // ���ͼ��
		{
			case 1:                                                            // ��ʾͼ��
		    case 2:
		    case 3:
		    case 4:
		    case 5:
				m_Picture_BAT.ShowWindow(TRUE);
				break;

			case 0x0F:                                                         // ά���ϴ�״̬
				break;

			default:                                                           // ������ʾ
				m_Picture_BAT.ShowWindow(FALSE);
				break;
		}
	}

	if ((s_recv_buff[0] == 'M') && (s_recv_buff[1] == 'V')) {                  // �ƶ���ʾָ��
		;
	}
	
	if ((s_recv_buff[0] == 'E') && (s_recv_buff[1] == 'R')) {                  // �����ַ���ʾ
		;
	}

	if ((s_recv_buff[0] == 'C') && (s_recv_buff[1] == 'C')) {                  // ������
		;
	}
}

/**************************************************************************************************
**  ��������:  HandleUSARTData
**  ��������:  ����������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogHandset::HandleUSARTData(char *ptr, DWORD len)
{
	DWORD i;
	unsigned char temp;

	if (IsWindowVisible() == FALSE) return;                                    // ���岻�ɼ�ʱ������Э������

	for (i = 0; i < len; i++) {
		temp = ptr[i];                                                         // ע������һ��Ҫ��һ��ǿ��ת��
		if (temp == 0xFF) {                                                    // ����յ���֡ͷ֡β�ֽ�
			if (s_recv_head == FALSE) {                                        // �����δ�յ�֡ͷ
				s_recv_head = TRUE;                                            // ����Ѿ��յ�֡ͷ
			} else {							                               // ����Ѿ��յ���֡ͷ
			    s_recv_buff[s_recv_dlen] = '\0';                               // ����Ѿ���ȫ����֡����
				HandleHstProtcol();
				s_recv_head = FALSE;
			}
			s_recv_dlen = 0;                                                   // ����Ҫ�ǵð����ݻ��������
			memset(s_recv_buff, 0, sizeof(s_recv_buff));
		} else {                                                               // ����յ�����ͨ�ֽ�
			if (s_recv_head == TRUE) {                                         // ����֡��ʽʱ���仺������
				s_recv_buff[s_recv_dlen++] = temp;
			}
		}
	}
}

/**************************************************************************************************
**  ��������:  ShowHideHstWindow
**  ��������:  ��ʾ�����ر����ڣ�������ȡ�ʹ洢����λ�ò���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
void CDialogHandset::ShowHideHstWindow(bool show)
{
	CRect rect;
	CMySScomDlg *pDlg;

	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;
	
	GetWindowRect(&rect);

	if (show == TRUE) {                                                        // �������ʾ����

		SetWindowPos(NULL, pDlg->s_HstDlgXPos, pDlg->s_HstDlgYPos, rect.Width(), rect.Height(), SWP_NOSIZE);

		ShowWindow(SW_SHOW);

		SendHstData('m');                                                      // ���Ϳ�����֪

		s_recv_head = FALSE;
		s_recv_dlen = 0;
		memset(s_recv_buff, 0, sizeof(s_recv_buff));

		CFont g_font;
		g_font.CreatePointFont(200, "Fixedsys");
		m_RichEdit.SetFont(&g_font);

		SetTimer(Timer_No_HstLink, 10000, NULL);                               // ������ʱ����������
	
		m_Picture_Line1.ShowWindow(FALSE);
		m_Picture_Line2.ShowWindow(FALSE);
		m_Picture_GPS.ShowWindow(FALSE);
		m_Picture_GSM0.ShowWindow(FALSE);
		m_Picture_GSM1.ShowWindow(FALSE);
		m_Picture_GSM2.ShowWindow(FALSE);
		m_Picture_GSM3.ShowWindow(FALSE);
		m_Picture_GSM4.ShowWindow(FALSE);
		m_Picture_BAT.ShowWindow(FALSE);
		m_Picture_Phone.ShowWindow(FALSE);
		m_Picture_SMS.ShowWindow(FALSE);

	} else {                                                                   // ��������ش���

		pDlg->s_HstDlgXPos = rect.left;                                        // ���ݴ���λ�ò���
		pDlg->s_HstDlgYPos = rect.top;

		ShowWindow(SW_HIDE);

		KillTimer(Timer_No_HstLink);                                           // �ر�������ʱ��

		SendHstData('q');                                                      // ���͹ػ���֪
	}
}

/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== ��˵�л����ķָ��� ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== ����Ϊϵͳ��Ϣ���� ===================================== */

BOOL CDialogHandset::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

void CDialogHandset::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
		case Timer_No_HstLink:                                                 // ��ʱ������������
			SendHstData('o');
			break;
		
		default:
			return;
	}

	CDialog::OnTimer(nIDEvent);
}

void CDialogHandset::OnClose()
{
	CMySScomDlg *pDlg;
	
	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;
	
	pDlg->InformHstDlgClose();                                                 /* ֪ͨ�����洰���ѱ��ر� */
	
	ShowHideHstWindow(FALSE);

	CDialog::OnClose();
}

void CDialogHandset::OnOK()
{
	;
}

void CDialogHandset::OnCancel()
{
	;
}

void CDialogHandset::OnBnClickedButtonc()
{
	SendHstData('l');
}

void CDialogHandset::OnBnClickedButtonok()
{
	SendHstData('e');
}

void CDialogHandset::OnBnClickedButtonup()
{
	SendHstData('f');
}

void CDialogHandset::OnBnClickedButtondown()
{
	SendHstData('g');
}

void CDialogHandset::OnBnClickedButtonset()
{
	SendHstData('r');
}

void CDialogHandset::OnBnClickedButtono()
{
	SendHstData('n');
}

void CDialogHandset::OnBnClickedButton1()
{
	SendHstData('1');
}

void CDialogHandset::OnBnClickedButton2()
{
	SendHstData('2');
}

void CDialogHandset::OnBnClickedButton3()
{
	SendHstData('3');
}

void CDialogHandset::OnBnClickedButton4()
{
	SendHstData('4');
}

void CDialogHandset::OnBnClickedButton5()
{
	SendHstData('5');
}

void CDialogHandset::OnBnClickedButton6()
{
	SendHstData('6');
}

void CDialogHandset::OnBnClickedButton7()
{
	SendHstData('7');
}

void CDialogHandset::OnBnClickedButton8()
{
	SendHstData('8');
}

void CDialogHandset::OnBnClickedButton9()
{
	SendHstData('9');
}

void CDialogHandset::OnBnClickedButton0()
{
	SendHstData('0');
}

void CDialogHandset::OnBnClickedButtonX()
{
	SendHstData('a');
}

void CDialogHandset::OnBnClickedButtonJ()
{
	SendHstData('b');
}

BOOL CDialogHandset::PreTranslateMessage(MSG* pMsg)
{	
	if (pMsg->message == WM_KEYDOWN) {

		switch (pMsg->wParam)
		{
			case 48:                                                           // ������0��
			case 96:
				OnBnClickedButton0();
				break;

			case 49:                                                           // ������1��
			case 97:
				OnBnClickedButton1();
				break;

			case 50:                                                           // ������2��
			case 98:
				OnBnClickedButton2();
				break;

			case 51:                                                           // ������3��
			case 99:
				OnBnClickedButton3();
				break;

			case 52:                                                           // ������4��
			case 100:
				OnBnClickedButton4();
				break;

			case 53:                                                           // ������5��
			case 101:
				OnBnClickedButton5();
				break;

			case 54:                                                           // ������6��
			case 102:
				OnBnClickedButton6();
				break;

			case 55:                                                           // ������7��
			case 103:
				OnBnClickedButton7();
				break;

			case 56:                                                           // ������8��
			case 104:
				OnBnClickedButton8();
				break;

			case 57:                                                           // ������9��
			case 105:
				OnBnClickedButton9();
				break;

			case 42:                                                           // ������*��
				OnBnClickedButtonX();
				break;

			case 107:                                                          // ������+��
				SendHstData('a');
				SendHstData('p');
				break;

			case 8:                                                            // ������c��
				OnBnClickedButtonc();
				break;

			case 13:                                                           // ������ok��
				OnBnClickedButtonok();
				break;

			case 38:                                                           // ���������ϼ�
				OnBnClickedButtonup();
				break;

			case 40:                                                           // ���������¼�
				OnBnClickedButtondown();
				break;

			case 35:                                                           // ������#��
				OnBnClickedButtonJ();
				break;

			case 110:                                                          // ������set��
				OnBnClickedButtonset();
				break;

			default:
				break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
