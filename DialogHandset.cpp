// DialogHandset.cpp : 实现文件
//

#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogHandset.h"
#include "afxdialogex.h"

// CDialogHandset 对话框

IMPLEMENT_DYNAMIC(CDialogHandset, CDialog)

CDialogHandset::CDialogHandset(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogHandset::IDD, pParent)
{
	AfxInitRichEdit();                                                         /* 初始化RichEdit控件 */
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
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为对外接口函数 ===================================== */

/**************************************************************************************************
**  函数名称:  SendHstData
**  功能描述:  发送串口数据
**  输入参数:  
**  返回参数:  
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
**  函数名称:  HandleHstProtcol
**  功能描述:  处理手柄协议数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogHandset::HandleHstProtcol(void)
{
	char dispbuf[27];

	if ((s_recv_buff[0] == 'D') && (s_recv_buff[1] == 'H')) {                  // 更新显示内容
		memcpy(&dispbuf[0], &s_recv_buff[2], 12);
		dispbuf[12] = '\r';
		dispbuf[13] = '\n';
		memcpy(&dispbuf[14], &s_recv_buff[14], 12);
		dispbuf[26] = '\0';

		SetDlgItemText(IDC_RICHEDIT_DISP, dispbuf);
		m_Picture_Line1.ShowWindow(FALSE);
		m_Picture_Line2.ShowWindow(FALSE);
	} 
	
	if ((s_recv_buff[0] == 'S') && (s_recv_buff[1] == 'R')) {                  // 反显
		if (s_recv_buff[2] == 0) {
			m_Picture_Line1.ShowWindow(TRUE);
			m_Picture_Line2.ShowWindow(FALSE);
		} else {
			m_Picture_Line1.ShowWindow(FALSE);
			m_Picture_Line2.ShowWindow(TRUE);
		}
	}
	
	if ((s_recv_buff[0] == 'R') && (s_recv_buff[1] == 'S')) {                  // 屏幕初始化
		SetDlgItemText(IDC_RICHEDIT_DISP, "");
	}

	if ((s_recv_buff[0] == 'A') && (s_recv_buff[1] == 'C')) {                  // 辅助显示区

		switch (s_recv_buff[2])                                                // GSM信号强度指示
		{
			case 1:                                                            // 1格
				m_Picture_GSM0.ShowWindow(TRUE);
				m_Picture_GSM1.ShowWindow(FALSE);
				m_Picture_GSM2.ShowWindow(FALSE);
				m_Picture_GSM3.ShowWindow(FALSE);
				m_Picture_GSM4.ShowWindow(FALSE);
				break;

			case 2:                                                            // 2格
				m_Picture_GSM0.ShowWindow(FALSE);
				m_Picture_GSM1.ShowWindow(TRUE);
				m_Picture_GSM2.ShowWindow(FALSE);
				m_Picture_GSM3.ShowWindow(FALSE);
				m_Picture_GSM4.ShowWindow(FALSE);
				break;

			case 3:                                                            // 3格
				m_Picture_GSM0.ShowWindow(FALSE);
				m_Picture_GSM1.ShowWindow(FALSE);
				m_Picture_GSM2.ShowWindow(TRUE);
				m_Picture_GSM3.ShowWindow(FALSE);
				m_Picture_GSM4.ShowWindow(FALSE);
				break;

			case 4:                                                            // 4格
				m_Picture_GSM0.ShowWindow(FALSE);
				m_Picture_GSM1.ShowWindow(FALSE);
				m_Picture_GSM2.ShowWindow(FALSE);
				m_Picture_GSM3.ShowWindow(TRUE);
				m_Picture_GSM4.ShowWindow(FALSE);
				break;

			case 5:                                                            // 5格
				m_Picture_GSM0.ShowWindow(FALSE);
				m_Picture_GSM1.ShowWindow(FALSE);
				m_Picture_GSM2.ShowWindow(FALSE);
				m_Picture_GSM3.ShowWindow(FALSE);
				m_Picture_GSM4.ShowWindow(TRUE);
				break;

			case 0x0F:                                                         // 维持上次状态
				break;

			default:                                                           // 隐藏显示
				m_Picture_GSM0.ShowWindow(FALSE);
				m_Picture_GSM1.ShowWindow(FALSE);
				m_Picture_GSM2.ShowWindow(FALSE);
				m_Picture_GSM3.ShowWindow(FALSE);
				m_Picture_GSM4.ShowWindow(FALSE);
				break;
		}

		switch (s_recv_buff[3])                                                // 未接电话
		{
			case 1:                                                            // 显示图标
				m_Picture_Phone.ShowWindow(TRUE);
				break;

			case 0x0F:                                                         // 维持上次状态
				break;

			default:                                                           // 隐藏显示
				m_Picture_Phone.ShowWindow(FALSE);
				break;
		}

		switch (s_recv_buff[4])                                                // 未读短信
		{
			case 1:                                                            // 显示图标
				m_Picture_SMS.ShowWindow(TRUE);
				break;

			case 0x0F:                                                         // 维持上次状态
				break;

			default:                                                           // 隐藏显示
				m_Picture_SMS.ShowWindow(FALSE);
				break;
		}

		switch (s_recv_buff[5])                                                // GPS定位图标
		{
			case 1:                                                            // 显示图标
				m_Picture_GPS.ShowWindow(TRUE);
				break;

			case 0x0F:                                                         // 维持上次状态
				break;

			default:                                                           // 隐藏显示
				m_Picture_GPS.ShowWindow(FALSE);
				break;
		}

		switch (s_recv_buff[6])                                                // 电池图标
		{
			case 1:                                                            // 显示图标
		    case 2:
		    case 3:
		    case 4:
		    case 5:
				m_Picture_BAT.ShowWindow(TRUE);
				break;

			case 0x0F:                                                         // 维持上次状态
				break;

			default:                                                           // 隐藏显示
				m_Picture_BAT.ShowWindow(FALSE);
				break;
		}
	}

	if ((s_recv_buff[0] == 'M') && (s_recv_buff[1] == 'V')) {                  // 移动显示指针
		;
	}
	
	if ((s_recv_buff[0] == 'E') && (s_recv_buff[1] == 'R')) {                  // 擦除字符显示
		;
	}

	if ((s_recv_buff[0] == 'C') && (s_recv_buff[1] == 'C')) {                  // 光标控制
		;
	}
}

/**************************************************************************************************
**  函数名称:  HandleUSARTData
**  功能描述:  处理串口数据
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogHandset::HandleUSARTData(char *ptr, DWORD len)
{
	DWORD i;
	unsigned char temp;

	if (IsWindowVisible() == FALSE) return;                                    // 窗体不可见时不处理协议数据

	for (i = 0; i < len; i++) {
		temp = ptr[i];                                                         // 注意这里一定要做一个强制转换
		if (temp == 0xFF) {                                                    // 如果收到了帧头帧尾字节
			if (s_recv_head == FALSE) {                                        // 如果尚未收到帧头
				s_recv_head = TRUE;                                            // 标记已经收到帧头
			} else {							                               // 如果已经收到了帧头
			    s_recv_buff[s_recv_dlen] = '\0';                               // 标记已经收全了整帧数据
				HandleHstProtcol();
				s_recv_head = FALSE;
			}
			s_recv_dlen = 0;                                                   // 这里要记得把数据缓冲区清空
			memset(s_recv_buff, 0, sizeof(s_recv_buff));
		} else {                                                               // 如果收到了普通字节
			if (s_recv_head == TRUE) {                                         // 符合帧格式时将其缓存起来
				s_recv_buff[s_recv_dlen++] = temp;
			}
		}
	}
}

/**************************************************************************************************
**  函数名称:  ShowHideHstWindow
**  功能描述:  显示和隐藏本窗口，包括读取和存储窗口位置参数
**  输入参数:  
**  返回参数:  
**************************************************************************************************/
void CDialogHandset::ShowHideHstWindow(bool show)
{
	CRect rect;
	CMySScomDlg *pDlg;

	pDlg = (CMySScomDlg *)AfxGetApp()->m_pMainWnd;
	
	GetWindowRect(&rect);

	if (show == TRUE) {                                                        // 如果是显示窗体

		SetWindowPos(NULL, pDlg->s_HstDlgXPos, pDlg->s_HstDlgYPos, rect.Width(), rect.Height(), SWP_NOSIZE);

		ShowWindow(SW_SHOW);

		SendHstData('m');                                                      // 发送开机告知

		s_recv_head = FALSE;
		s_recv_dlen = 0;
		memset(s_recv_buff, 0, sizeof(s_recv_buff));

		CFont g_font;
		g_font.CreatePointFont(200, "Fixedsys");
		m_RichEdit.SetFont(&g_font);

		SetTimer(Timer_No_HstLink, 10000, NULL);                               // 开启定时器发送心跳
	
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

	} else {                                                                   // 如果是隐藏窗体

		pDlg->s_HstDlgXPos = rect.left;                                        // 传递窗体位置参数
		pDlg->s_HstDlgYPos = rect.top;

		ShowWindow(SW_HIDE);

		KillTimer(Timer_No_HstLink);                                           // 关闭心跳定时器

		SendHstData('q');                                                      // 发送关机告知
	}
}

/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */

BOOL CDialogHandset::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

void CDialogHandset::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
		case Timer_No_HstLink:                                                 // 定时发送心跳数据
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
	
	pDlg->InformHstDlgClose();                                                 /* 通知主界面窗口已被关闭 */
	
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
			case 48:                                                           // 按下了0键
			case 96:
				OnBnClickedButton0();
				break;

			case 49:                                                           // 按下了1键
			case 97:
				OnBnClickedButton1();
				break;

			case 50:                                                           // 按下了2键
			case 98:
				OnBnClickedButton2();
				break;

			case 51:                                                           // 按下了3键
			case 99:
				OnBnClickedButton3();
				break;

			case 52:                                                           // 按下了4键
			case 100:
				OnBnClickedButton4();
				break;

			case 53:                                                           // 按下了5键
			case 101:
				OnBnClickedButton5();
				break;

			case 54:                                                           // 按下了6键
			case 102:
				OnBnClickedButton6();
				break;

			case 55:                                                           // 按下了7键
			case 103:
				OnBnClickedButton7();
				break;

			case 56:                                                           // 按下了8键
			case 104:
				OnBnClickedButton8();
				break;

			case 57:                                                           // 按下了9键
			case 105:
				OnBnClickedButton9();
				break;

			case 42:                                                           // 按下了*键
				OnBnClickedButtonX();
				break;

			case 107:                                                          // 按下了+键
				SendHstData('a');
				SendHstData('p');
				break;

			case 8:                                                            // 按下了c键
				OnBnClickedButtonc();
				break;

			case 13:                                                           // 按下了ok键
				OnBnClickedButtonok();
				break;

			case 38:                                                           // 按下了向上键
				OnBnClickedButtonup();
				break;

			case 40:                                                           // 按下了向下键
				OnBnClickedButtondown();
				break;

			case 35:                                                           // 按下了#键
				OnBnClickedButtonJ();
				break;

			case 110:                                                          // 按下了set键
				OnBnClickedButtonset();
				break;

			default:
				break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
