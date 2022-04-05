#include "stdafx.h"
#include "MySScom.h"
#include "MySScomDlg.h"
#include "DialogSuperSend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDialogSuperSend::CDialogSuperSend(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSuperSend::IDD, pParent)
{
	m_Radio_SendAll = 0;
}


void CDialogSuperSend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_SSHEX_01, m_Check_SSHex_01);
	DDX_Check(pDX, IDC_CHECK_SSHEX_02, m_Check_SSHex_02);
	DDX_Check(pDX, IDC_CHECK_SSHEX_03, m_Check_SSHex_03);
	DDX_Check(pDX, IDC_CHECK_SSHEX_04, m_Check_SSHex_04);
	DDX_Check(pDX, IDC_CHECK_SSHEX_05, m_Check_SSHex_05);
	DDX_Check(pDX, IDC_CHECK_SSHEX_06, m_Check_SSHex_06);
	DDX_Check(pDX, IDC_CHECK_SSHEX_07, m_Check_SSHex_07);
	DDX_Check(pDX, IDC_CHECK_SSHEX_08, m_Check_SSHex_08);
	DDX_Check(pDX, IDC_CHECK_SSHEX_09, m_Check_SSHex_09);
	DDX_Check(pDX, IDC_CHECK_SSHEX_10, m_Check_SSHex_10);
	DDX_Check(pDX, IDC_CHECK_SSHEX_11, m_Check_SSHex_11);
	DDX_Check(pDX, IDC_CHECK_SSHEX_12, m_Check_SSHex_12);
	DDX_Check(pDX, IDC_CHECK_SSHEX_13, m_Check_SSHex_13);
	DDX_Check(pDX, IDC_CHECK_SSHEX_14, m_Check_SSHex_14);
	DDX_Check(pDX, IDC_CHECK_SSHEX_15, m_Check_SSHex_15);
	DDX_Check(pDX, IDC_CHECK_SSHEX_16, m_Check_SSHex_16);
	DDX_Check(pDX, IDC_CHECK_SSHEX_17, m_Check_SSHex_17);
	DDX_Check(pDX, IDC_CHECK_SSHEX_18, m_Check_SSHex_18);
	DDX_Check(pDX, IDC_CHECK_SSHEX_19, m_Check_SSHex_19);
	DDX_Check(pDX, IDC_CHECK_SSHEX_20, m_Check_SSHex_20);
	DDX_Check(pDX, IDC_CHECK_SSHEX_21, m_Check_SSHex_21);
	DDX_Check(pDX, IDC_CHECK_SSHEX_22, m_Check_SSHex_22);
	DDX_Check(pDX, IDC_CHECK_SSHEX_23, m_Check_SSHex_23);
	DDX_Check(pDX, IDC_CHECK_SSHEX_24, m_Check_SSHex_24);
	DDX_Check(pDX, IDC_CHECK_SSHEX_25, m_Check_SSHex_25);
	DDX_Check(pDX, IDC_CHECK_SSHEX_26, m_Check_SSHex_26);
	DDX_Check(pDX, IDC_CHECK_SSHEX_27, m_Check_SSHex_27);
	DDX_Check(pDX, IDC_CHECK_SSHEX_28, m_Check_SSHex_28);
	DDX_Check(pDX, IDC_CHECK_SSHEX_29, m_Check_SSHex_29);
	DDX_Check(pDX, IDC_CHECK_SSHEX_30, m_Check_SSHex_30);
	DDX_Check(pDX, IDC_CHECK_SSHEX_31, m_Check_SSHex_31);
	DDX_Check(pDX, IDC_CHECK_SSHEX_32, m_Check_SSHex_32);
	DDX_Check(pDX, IDC_CHECK_SSHEX_33, m_Check_SSHex_33);
	DDX_Check(pDX, IDC_CHECK_SSHEX_34, m_Check_SSHex_34);
	DDX_Check(pDX, IDC_CHECK_SSHEX_35, m_Check_SSHex_35);
	DDX_Check(pDX, IDC_CHECK_SSHEX_36, m_Check_SSHex_36);
	DDX_Check(pDX, IDC_CHECK_SSHEX_37, m_Check_SSHex_37);
	DDX_Check(pDX, IDC_CHECK_SSHEX_38, m_Check_SSHex_38);
	DDX_Check(pDX, IDC_CHECK_SSHEX_39, m_Check_SSHex_39);
	DDX_Check(pDX, IDC_CHECK_SSHEX_40, m_Check_SSHex_40);
	DDX_Text(pDX, IDC_EDIT_AUTOTIME, m_Edit_AutoTime);
	DDV_MaxChars(pDX, m_Edit_AutoTime, 5);
	DDX_Radio(pDX, IDC_RADIO_SENDALL, m_Radio_SendAll);
}


BEGIN_MESSAGE_MAP(CDialogSuperSend, CDialog)
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
	ON_BN_CLICKED(IDC_CHECK_SSHEX_01, OnCheck01)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_02, OnCheck02)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_03, OnCheck03)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_04, OnCheck04)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_05, OnCheck05)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_06, OnCheck06)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_07, OnCheck07)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_08, OnCheck08)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_09, OnCheck09)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_10, OnCheck10)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_11, OnCheck11)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_13, OnCheck13)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_14, OnCheck14)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_15, OnCheck15)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_16, OnCheck16)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_17, OnCheck17)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_18, OnCheck18)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_19, OnCheck19)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_20, OnCheck20)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_21, OnCheck21)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_22, OnCheck22)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_23, OnCheck23)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_24, OnCheck24)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_25, OnCheck25)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_26, OnCheck26)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_27, OnCheck27)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_28, OnCheck28)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_29, OnCheck29)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_30, OnCheck30)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_31, OnCheck31)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_32, OnCheck32)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_33, OnCheck33)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_34, OnCheck34)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_35, OnCheck35)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_36, OnCheck36)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_37, OnCheck37)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_38, OnCheck38)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_39, OnCheck39)
	ON_BN_CLICKED(IDC_CHECK_SSHEX_40, OnCheck40)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_SENDALL, OnRadioSendAll)
	ON_BN_CLICKED(IDC_RADIO_SENDEACH, OnRadioSendEach)
	ON_BN_CLICKED(IDC_BUTTON_STARTSEND, OnButtonStartSend)
END_MESSAGE_MAP()


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为内部工具函数 ===================================== */


/**************************************************************************************************
**  函数名称:  EditDataValid
**  功能描述:  判断edit控件内的数据是否有效
**************************************************************************************************/
bool CDialogSuperSend::EditDataValid(CString cstr, BOOL ishex)
{
	if (ishex == TRUE) {                                                   /* 需要10进制模式，则判断数据内容 */
		if (ParseCStrisLegal(cstr) == TRUE) {
			return TRUE;
		} else {
			return FALSE;
		}
	} else {                                                               /* 仅字符模式，则判断数据长度有效即可 */
		if (cstr.GetLength() > 0) {
			return TRUE;
		} else {
			return FALSE;
		}
	}
}

/**************************************************************************************************
**  函数名称:  GetSrValidDataNo
**  功能描述:  获取高级发送区内edit控件内数据有效的控件ID
**  返回参数:  返回内容有效的编辑框的序号，全无效则返回0xFF
**************************************************************************************************/
int CDialogSuperSend::GetSrValidDataNo(void)
{
	int      range;
	BOOL     ishex;
	CString  cstr;

	range = (s_expandmode == TRUE) ? EXTMODE_NUM : SDTMODE_NUM;

	for (int i = 0; i < range; i++) {                                          /* 逐个判断每个编辑框内容是否有效 */

		GetDlgItemText(IDC_EDIT_SSDATA_01 + i, cstr);
		ishex = (IsDlgButtonChecked(IDC_CHECK_SSHEX_01 + i) == TRUE) ? TRUE : FALSE;

		if (EditDataValid(cstr, ishex) == TRUE) {                              /* 分析编辑框内容是否有效 */
			return i;
		}
	}

	return 0xFF;                                                               /* 全部无效，则返回0 */
}

/**************************************************************************************************
**  函数名称:  GetSrValidTimeNo
**  功能描述:  获取高级发送区内edit控件内时间有效的控件ID
**  返回参数:  返回内容有效的编辑框的序号，全无效则返回0xFF
**************************************************************************************************/
int CDialogSuperSend::GetSrValidTimeNo(void)
{
	int      range;
	CString  cstr;

	range = (s_expandmode == TRUE) ? EXTMODE_NUM : SDTMODE_NUM;

	for (int i = 0; i < range; i++) {                                          /* 逐个判断内容是否有效 */
		GetDlgItemText(IDC_EDIT_SSTIME_01 + i, cstr);
		if (((cstr.GetLength() > 0) && (atoi(cstr)) > 0)) {
			return i;
		}
	}

	return 0xFF;                                                               /* 全部无效，则返回0 */
}

/**************************************************************************************************
**  函数名称:  GetSrInValidTimeNo
**  功能描述:  获取高级发送区内edit控件内时间非法的控件ID
**  返回参数:  返回内容非法（不是100的倍数）的编辑框的序号，全部合法（不填也视为合法）则返回0xFF
**************************************************************************************************/
int CDialogSuperSend::GetSrInValidTimeNo(void)
{
	int      range, timer;
	CString  cstr;

	range = (s_expandmode == TRUE) ? EXTMODE_NUM : SDTMODE_NUM;

	for (int i = 0; i < range; i++) {                                          /* 逐个判断内容是否有效 */
		GetDlgItemText(IDC_EDIT_SSTIME_01 + i, cstr);
		timer = atoi(cstr);
		if (timer % SCANR_TIMER != 0) {
			return i;
		}
	}

	return 0xFF;                                                               /* 全部无效，则返回0 */
}

/**************************************************************************************************
**  函数名称:  TrytoSendData
**  功能描述:  尝试发送数据
**************************************************************************************************/
void CDialogSuperSend::TrytoSendData(int index)
{	
	int           dlen;
	BOOL          ishex;
	CString       TempStr;
	unsigned char buff[MAX_SEND_BYTE];

	GetDlgItemText(IDC_EDIT_SSDATA_01 + index, TempStr);
	ishex = (IsDlgButtonChecked(IDC_CHECK_SSHEX_01 + index) == TRUE) ? TRUE : FALSE;

	if (EditDataValid(TempStr, ishex) == FALSE) {                              /* 编辑框内容无效 */
		MessageBox("编辑框内容为空，或者格式不符合要求，请确认...   ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}

	if (ishex == TRUE) {                                                       /* 16进制的数据要先转换成字符 */
		TempStr = HexToChar(TempStr);
	}

	if (TempStr.GetLength() > MAX_SEND_BYTE) {                                 /* 编辑框内容过长 */
		MessageBox("您输入的内容太长，超出系统允许范围，请重新输入...   ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}

	dlen = TempStr.GetLength();
	strncpy_s((char *)buff, MAX_SEND_BYTE, (LPCTSTR)TempStr, TempStr.GetLength());

	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_DATATOSEND, dlen, (LPARAM)(&buff));
}

/**************************************************************************************************
**  函数名称:  TrytoContinueSend
**  功能描述:  尝试继续连发数据
**************************************************************************************************/
void CDialogSuperSend::TrytoContinueSend(void)
{
	int      range;
	BOOL     ishex;
	CString  TempStr;

	range = (s_expandmode == TRUE) ? EXTMODE_NUM : SDTMODE_NUM;

	for (int i = s_curdatacnt; i < range; i++) {                               /* 以前次为起点，接着判断 */

		GetDlgItemText(IDC_EDIT_SSDATA_01 + i, TempStr);
		ishex = (IsDlgButtonChecked(IDC_CHECK_SSHEX_01 + i) == TRUE) ? TRUE : FALSE;

		if (EditDataValid(TempStr, ishex) == TRUE) {                           /* 编辑框内容有效 */
			TrytoSendData(i);                                                  /* 发送内容 */
			s_curdatacnt = i + 1;                                              /* 保存本次的位置 */
			return;
		}
	}

	s_curdatacnt = 0;                                                          /* 重新回到起点 */
}

/**************************************************************************************************
**  函数名称:  TrytoSendEachData
**  功能描述:  尝试连发单条数据
**************************************************************************************************/
void CDialogSuperSend::TrytoSendEachData(void)
{
	int     range, timer;
	BOOL    ishex;
	CString TempStr;

	range = (s_expandmode == TRUE) ? EXTMODE_NUM : SDTMODE_NUM;

	for (int i = 0; i < range; i++) {                                          /* 逐条分析每一个编辑框 */

		GetDlgItemText(IDC_EDIT_SSTIME_01 + i, TempStr);
		timer = atoi((LPSTR)(LPCTSTR)TempStr);
		
		if (timer == 0) {                                                      /* 发送时间无效，判断下一条 */
			continue;
		} else {                                                               /* 发送时间有效，则进行累加 */
			s_sendcnt[i] += SCANR_TIMER;
		}
		
		if (s_sendcnt[i] < timer) {                                            /* 时间尚未到点，待下次继续判断 */
			continue;
		}
		
		s_sendcnt[i] = 0;                                                      /* 发送时间到点，计数器重新归零 */

		GetDlgItemText(IDC_EDIT_SSDATA_01 + i, TempStr);
		ishex = (IsDlgButtonChecked(IDC_CHECK_SSHEX_01 + i) == TRUE) ? TRUE : FALSE;

		if (EditDataValid(TempStr, ishex) == TRUE) {                           /* 编辑框内容有效 */
			TrytoSendData(i);                                                  /* 发送内容 */
		}
	}
}

/**************************************************************************************************
**  函数名称:  ShowHideTimeEdit
**  功能描述:  显示或隐藏时间编辑框
**************************************************************************************************/
void CDialogSuperSend::ShowHideTimeEdit(bool enanble)
{
	GetDlgItem(IDC_EDIT_AUTOTIME)->EnableWindow(!enanble);
	
	for (int i = 0; i < EXTMODE_NUM; i++) {
		GetDlgItem(IDC_EDIT_SSTIME_01 + i)->EnableWindow(enanble);
	}
}

/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为控件消息处理 ===================================== */


/**************************************************************************************************
**  函数名称:  OnButtonStartSend
**  功能描述:  开始启动发送流程
**************************************************************************************************/
void CDialogSuperSend::OnButtonStartSend() 
{
	int     Timer;
	CString TempStr;
	
	if (s_issenddata == FALSE) {                                               /* 如果当前没有在发送数据 */

		if (GetSrValidDataNo() == 0xFF) {                                      /* 判断数据区是否有效 */
			MessageBox("这么多的编辑框，您至少选一个输入点内容吧\r\n否则，叫我发送什么呢？~~~  ", "提示", MB_OK + MB_ICONINFORMATION);
			UpdateData(FALSE);                                                 /* 取消复选框被选中的状态 */
			return;
		}
		
		if (s_cirsendall == TRUE) {                                            /* 全部数据统一连发 */

			GetDlgItemText(IDC_EDIT_AUTOTIME, TempStr);
			Timer = atoi((LPSTR)(LPCTSTR)TempStr);
			
			if (Timer == 0) {                                                  /* 时间非法 */

				MessageBox("发送时间间隔不能为0，请确认！  ", "提示", MB_OK + MB_ICONEXCLAMATION);
				SetDlgItemText(IDC_EDIT_AUTOTIME, m_Edit_AutoTime);            /* 还原编辑框内容 */
				UpdateData(FALSE);                                             /* 取消复选框被选中的状态 */
				return;

			} else {
				
				SetTimer(Timer_No_SrAllSend, Timer, NULL);                     /* 启动定时器 */
				s_curdatacnt = 0;
				s_issenddata = TRUE;
				SetDlgItemText(IDC_BUTTON_STARTSEND, "停止发送");

				GetDlgItem(IDC_RADIO_SENDALL)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDIT_AUTOTIME)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_SENDEACH)->EnableWindow(FALSE);
			}
		} else {                                                               /* 单条数据各自连发 */

			if (GetSrValidTimeNo() == 0xFF) {                                  /* 判断定时区是否有效 */
				MessageBox("您尚未指定任何一个有效的发送间隔，系统无法执行您的命令！  ", "提示", MB_OK + MB_ICONINFORMATION);
				UpdateData(FALSE);                                             /* 取消复选框被选中的状态 */
				return;
			}

			Timer = GetSrInValidTimeNo();
			if (Timer != 0xFF) {                                               /* 判断定时区是否有效 */
				TempStr.Format("第%d项条目的时间设置非法，请确认！\r\n说明：系统只支持100ms的倍数  ", Timer + 1);
				MessageBox(TempStr, "提示", MB_OK + MB_ICONINFORMATION);
				return;
			}

			SetTimer(Timer_No_SrEachSend, SCANR_TIMER, NULL);                  /* 启动定时器 */
			memset(s_sendcnt, 0, sizeof(s_sendcnt));
			s_issenddata = TRUE;
			SetDlgItemText(IDC_BUTTON_STARTSEND, "停止发送");
			
			GetDlgItem(IDC_RADIO_SENDALL)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_AUTOTIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_SENDEACH)->EnableWindow(FALSE);
		}
		
	} else {                                                                   /* 如果当前正在发送数据 */
		s_issenddata = FALSE;
		SetDlgItemText(IDC_BUTTON_STARTSEND, "开始发送");

		if (s_cirsendall == TRUE) {                                            /* 关闭定时器，取消自动发送功能 */
			KillTimer(Timer_No_SrAllSend);
		} else {
			KillTimer(Timer_No_SrEachSend);
		}
		
		GetDlgItem(IDC_RADIO_SENDALL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_AUTOTIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_SENDEACH)->EnableWindow(TRUE);
	}
}

/**************************************************************************************************
**  函数名称:  OnButtonExpand
**  功能描述:  收缩/展开 扩展面板
**************************************************************************************************/
void CDialogSuperSend::OnButtonExpand() 
{
	CRect rect;
	
	GetWindowRect(&rect);

	if (s_expandmode == TRUE) {
		SetWindowPos(NULL, 0, 0, (rect.Width() / 2) + 5, rect.Height(), SWP_NOMOVE);
		SetDlgItemText(IDC_BUTTON_EXPAND, ">> 扩展至40条数据 >>");
		s_expandmode = FALSE;
	} else {
		SetWindowPos(NULL, 0, 0, (rect.Width() - 5) * 2, rect.Height(), SWP_NOMOVE);
		SetDlgItemText(IDC_BUTTON_EXPAND, "<< 精简至20条数据 <<");
		s_expandmode = TRUE;
	}
}

/**************************************************************************************************
**  函数名称:  OnRadioSendAll
**  功能描述:  选择统一定时发送所有数据
**************************************************************************************************/
void CDialogSuperSend::OnRadioSendAll() 
{
	s_cirsendall = TRUE;
	ShowHideTimeEdit(!s_cirsendall);
}

/**************************************************************************************************
**  函数名称:  OnRadioSendEach
**  功能描述:  选择分开定时发送各条数据
**************************************************************************************************/
void CDialogSuperSend::OnRadioSendEach() 
{
	s_cirsendall = FALSE;
	ShowHideTimeEdit(!s_cirsendall);
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为对外接口函数 ===================================== */


/**************************************************************************************************
**  函数名称:  InitateSrDlgPos
**  功能描述:  初始化本窗口的位置和显示尺寸
**************************************************************************************************/
void CDialogSuperSend::InitateSrDlgPos(void)
{
	CRect rect;
	
	GetWindowRect(&rect);
	
	SetWindowPos(NULL, s_DialogPos_X, s_DialogPos_Y, rect.Width() / 2 + 5, rect.Height(), SWP_NOZORDER);	
	ShowWindow(SW_HIDE);
}

/**************************************************************************************************
**  函数名称:  ShowHideDlgWindow
**  功能描述:  显示和隐藏本窗口，包括读取和存储窗口位置参数
**************************************************************************************************/
void CDialogSuperSend::ShowHideDlgWindow(bool show)
{
	CRect rect;
		
	GetWindowRect(&rect);

	if (show == TRUE) {
		SetWindowPos(NULL, s_DialogPos_X, s_DialogPos_Y, rect.Width(), rect.Height(), SWP_NOSIZE);	
		ShowWindow(SW_SHOW);
		ShowHideTimeEdit(!s_cirsendall);
	} else {
		s_DialogPos_X = rect.left;
		s_DialogPos_Y = rect.top;
		ShowWindow(SW_HIDE);
	}
}

/**************************************************************************************************
**  函数名称:  InitiateAllParas
**  功能描述:  初始化各个参数
**************************************************************************************************/
void CDialogSuperSend::InitiateAllParas(void)
{
	char TempChar[MAX_SEND_BYTE];
	CString TempStr;

	m_Check_SSHex_01 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa01", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_02 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa02", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_03 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa03", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_04 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa04", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_05 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa05", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_06 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa06", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_07 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa07", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_08 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa08", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_09 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa09", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_10 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa10", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_11 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa11", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_12 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa12", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_13 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa13", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_14 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa14", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_15 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa15", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_16 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa16", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_17 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa17", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_18 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa18", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_19 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa19", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_20 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa20", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_21 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa21", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_22 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa22", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_23 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa23", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_24 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa24", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_25 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa25", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_26 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa26", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_27 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa27", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_28 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa28", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_29 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa29", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_30 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa30", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_31 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa31", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_32 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa32", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_33 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa33", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_34 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa34", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_35 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa35", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_36 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa36", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_37 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa37", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_38 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa38", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_39 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa39", 0, CONFIGFILENAME)) ? TRUE : FALSE;
	m_Check_SSHex_40 = (::GetPrivateProfileInt(FLAG_SUPERSEND, "SrHexa40", 0, CONFIGFILENAME)) ? TRUE : FALSE;

	for (int tt = 0, idc_edit_data = IDC_EDIT_SSDATA_01, idc_edit_time = IDC_EDIT_SSTIME_01; tt < EXTMODE_NUM; tt++) {

		TempStr.Format("SrData%.2d", tt);
		memset(TempChar, 0, MAX_SEND_BYTE);
		::GetPrivateProfileString(FLAG_SUPERSEND, TempStr, "", TempChar, MAX_SEND_BYTE, CONFIGFILENAME);
		TempStr.Format("%s", TempChar);
		TempStr = FormatQuotesStrRead(TempStr);
		SetDlgItemText(idc_edit_data + tt, TempStr);

		TempStr.Format("SrTime%.2d", tt);
		::GetPrivateProfileString(FLAG_SUPERSEND, TempStr, "", TempChar, 5, CONFIGFILENAME);
		TempStr.Format("%s", TempChar);
		SetDlgItemText(idc_edit_time + tt, TempStr);
	}

	::GetPrivateProfileString(FLAG_SUPERSEND, SUPERSEND_LOOPTIME, "", TempChar, 5, CONFIGFILENAME);
	m_Edit_AutoTime.Format("%s", TempChar);
	SetDlgItemText(IDC_EDIT_AUTOTIME, m_Edit_AutoTime);

	s_DialogPos_X = (::GetPrivateProfileInt(FLAG_SUPERSEND, SUPERSEND_POSTIONX, 0, CONFIGFILENAME));
	s_DialogPos_Y = (::GetPrivateProfileInt(FLAG_SUPERSEND, SUPERSEND_POSTIONY, 0, CONFIGFILENAME));

	UpdateData(FALSE);                                                         /* 更新编辑框内容 */
}

/**************************************************************************************************
**  函数名称:  RecordAllParas
**  功能描述:  保存各个参数
**************************************************************************************************/
void CDialogSuperSend::RecordAllParas(void)
{
	CString ParaStr, TempStr;

	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa01",  m_Check_SSHex_01 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa02",  m_Check_SSHex_02 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa03",  m_Check_SSHex_03 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa04",  m_Check_SSHex_04 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa05",  m_Check_SSHex_05 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa06",  m_Check_SSHex_06 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa07",  m_Check_SSHex_07 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa08",  m_Check_SSHex_08 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa09",  m_Check_SSHex_09 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa10",  m_Check_SSHex_10 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa11",  m_Check_SSHex_11 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa12",  m_Check_SSHex_12 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa13",  m_Check_SSHex_13 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa14",  m_Check_SSHex_14 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa15",  m_Check_SSHex_15 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa16",  m_Check_SSHex_16 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa17",  m_Check_SSHex_17 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa18",  m_Check_SSHex_18 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa19",  m_Check_SSHex_19 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa20",  m_Check_SSHex_20 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa21",  m_Check_SSHex_21 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa22",  m_Check_SSHex_22 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa23",  m_Check_SSHex_23 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa24",  m_Check_SSHex_24 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa25",  m_Check_SSHex_25 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa26",  m_Check_SSHex_26 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa27",  m_Check_SSHex_27 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa28",  m_Check_SSHex_28 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa29",  m_Check_SSHex_29 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa30",  m_Check_SSHex_30 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa31",  m_Check_SSHex_31 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa32",  m_Check_SSHex_32 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa33",  m_Check_SSHex_33 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa34",  m_Check_SSHex_34 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa35",  m_Check_SSHex_35 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa36",  m_Check_SSHex_36 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa37",  m_Check_SSHex_37 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa38",  m_Check_SSHex_38 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa39",  m_Check_SSHex_39 ? "1" : "0", CONFIGFILENAME);
	::WritePrivateProfileString(FLAG_SUPERSEND, "SrHexa40",  m_Check_SSHex_40 ? "1" : "0", CONFIGFILENAME);

	for (int tt = 0, idc_edit_data = IDC_EDIT_SSDATA_01, idc_edit_time = IDC_EDIT_SSTIME_01; tt < EXTMODE_NUM; tt++) {

		GetDlgItemText(idc_edit_data + tt, ParaStr);
		ParaStr = FormatQuotesStrWrite(ParaStr);
		TempStr.Format("SrData%.2d", tt);
		::WritePrivateProfileString(FLAG_SUPERSEND, TempStr, ParaStr, CONFIGFILENAME);

		GetDlgItemText(idc_edit_time + tt, ParaStr);
		TempStr.Format("SrTime%.2d", tt);
		::WritePrivateProfileString(FLAG_SUPERSEND, TempStr, ParaStr, CONFIGFILENAME);
	}

	GetDlgItemText(IDC_EDIT_AUTOTIME, ParaStr);
	::WritePrivateProfileString(FLAG_SUPERSEND, SUPERSEND_LOOPTIME, ParaStr, CONFIGFILENAME);

	if ((s_DialogPos_X < 0) || (s_DialogPos_X > MAX_WIN_POS)) {                /* 防止边界异常 */
		s_DialogPos_X = 0;
	}

	if ((s_DialogPos_Y < 0) || (s_DialogPos_Y > MAX_WIN_POS)) {                /* 防止边界异常 */
		s_DialogPos_Y = 0;
	}
	
	ParaStr.Format("%d", s_DialogPos_X);
	::WritePrivateProfileString(FLAG_SUPERSEND, SUPERSEND_POSTIONX, ParaStr, CONFIGFILENAME);
	ParaStr.Format("%d", s_DialogPos_Y);
	::WritePrivateProfileString(FLAG_SUPERSEND, SUPERSEND_POSTIONY, ParaStr, CONFIGFILENAME);
}

/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */

/**************************************************************************************************
**  函数名称:  OnInitDialog
**  功能描述:  窗体初始化
**************************************************************************************************/
BOOL CDialogSuperSend::OnInitDialog() 
{
	CDialog::OnInitDialog();

	s_expandmode = FALSE;
	s_issenddata = FALSE;
	s_cirsendall = TRUE;
	
	return TRUE;
}

/**************************************************************************************************
**  函数名称:  OnTimer
**  功能描述:  定时器消息处理
**************************************************************************************************/
void CDialogSuperSend::OnTimer(UINT nIDEvent) 
{
	switch (nIDEvent)
	{
		case Timer_No_SrAllSend:                                               /* 按照统一间隔，逐条发送数据 */
			TrytoContinueSend();
			break;
			
		case Timer_No_SrEachSend:                                              /* 按照各自间隔，逐条发送数据 */
			TrytoSendEachData();
			break;
		
		default:
			return;
	}
	
	CDialog::OnTimer(nIDEvent);
}

/**************************************************************************************************
**  函数名称:  OnClose
**  功能描述:  窗体关闭消息处理
**************************************************************************************************/
void CDialogSuperSend::OnClose() 
{
	if (s_issenddata == TRUE) {
		MessageBox("请先停止自动循环发送功能，再尝试关闭高级发送窗口......   ", "提示", MB_OK + MB_ICONINFORMATION);
		return;
	}

	ShowHideDlgWindow(FALSE);

	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_SSDLGCLOSE, 0, 0);
	
	CDialog::OnClose();
}

/**************************************************************************************************
**  函数名称:  PreTranslateMessage
**  功能描述:  预处理消息
**************************************************************************************************/
BOOL CDialogSuperSend::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg -> message == WM_KEYDOWN) {

		if (pMsg -> wParam == VK_ESCAPE)
			return true;
		if (pMsg -> wParam == VK_RETURN)
			return true;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为发送按钮处理 ===================================== */


void CDialogSuperSend::OnButtonSend01() 
{
	TrytoSendData(0);
}

void CDialogSuperSend::OnButtonSend02() 
{
	TrytoSendData(1);
}

void CDialogSuperSend::OnButtonSend03() 
{
	TrytoSendData(2);
}

void CDialogSuperSend::OnButtonSend04() 
{
	TrytoSendData(3);
}

void CDialogSuperSend::OnButtonSend05() 
{
	TrytoSendData(4);
}

void CDialogSuperSend::OnButtonSend06() 
{
	TrytoSendData(5);
}

void CDialogSuperSend::OnButtonSend07() 
{
	TrytoSendData(6);
}

void CDialogSuperSend::OnButtonSend08() 
{
	TrytoSendData(7);
}

void CDialogSuperSend::OnButtonSend09() 
{
	TrytoSendData(8);
}

void CDialogSuperSend::OnButtonSend10() 
{
	TrytoSendData(9);
}

void CDialogSuperSend::OnButtonSend11() 
{
	TrytoSendData(10);
}

void CDialogSuperSend::OnButtonSend12() 
{
	TrytoSendData(11);
}

void CDialogSuperSend::OnButtonSend13() 
{
	TrytoSendData(12);
}

void CDialogSuperSend::OnButtonSend14() 
{
	TrytoSendData(13);
}

void CDialogSuperSend::OnButtonSend15() 
{
	TrytoSendData(14);
}

void CDialogSuperSend::OnButtonSend16() 
{
	TrytoSendData(15);
}

void CDialogSuperSend::OnButtonSend17() 
{
	TrytoSendData(16);
}

void CDialogSuperSend::OnButtonSend18() 
{
	TrytoSendData(17);
}

void CDialogSuperSend::OnButtonSend19() 
{
	TrytoSendData(18);
}

void CDialogSuperSend::OnButtonSend20() 
{
	TrytoSendData(19);
}

void CDialogSuperSend::OnButtonSend21() 
{
	TrytoSendData(20);
}

void CDialogSuperSend::OnButtonSend22() 
{
	TrytoSendData(21);
}

void CDialogSuperSend::OnButtonSend23() 
{
	TrytoSendData(22);
}

void CDialogSuperSend::OnButtonSend24() 
{
	TrytoSendData(23);
}

void CDialogSuperSend::OnButtonSend25() 
{
	TrytoSendData(24);
}

void CDialogSuperSend::OnButtonSend26() 
{
	TrytoSendData(25);
}

void CDialogSuperSend::OnButtonSend27() 
{
	TrytoSendData(26);
}

void CDialogSuperSend::OnButtonSend28() 
{
	TrytoSendData(27);
}

void CDialogSuperSend::OnButtonSend29() 
{
	TrytoSendData(28);
}

void CDialogSuperSend::OnButtonSend30() 
{
	TrytoSendData(29);
}

void CDialogSuperSend::OnButtonSend31() 
{
	TrytoSendData(30);
}

void CDialogSuperSend::OnButtonSend32() 
{
	TrytoSendData(31);
}

void CDialogSuperSend::OnButtonSend33() 
{
	TrytoSendData(32);
}

void CDialogSuperSend::OnButtonSend34() 
{
	TrytoSendData(33);
}

void CDialogSuperSend::OnButtonSend35() 
{
	TrytoSendData(34);
}

void CDialogSuperSend::OnButtonSend36() 
{
	TrytoSendData(35);
}

void CDialogSuperSend::OnButtonSend37() 
{
	TrytoSendData(36);
}

void CDialogSuperSend::OnButtonSend38() 
{
	TrytoSendData(37);
}

void CDialogSuperSend::OnButtonSend39() 
{
	TrytoSendData(38);
}

void CDialogSuperSend::OnButtonSend40() 
{
	TrytoSendData(39);
}


/* ============================================================================================= */
/* ====================================                    ===================================== */
/* ==================================== 传说中华丽的分割线 ===================================== */
/* ====================================                    ===================================== */
/* ============================================================================================= */


/* ==================================== 以下为系统消息处理 ===================================== */


void CDialogSuperSend::OnCheck01() 
{
	m_Check_SSHex_01 = !m_Check_SSHex_01;
}

void CDialogSuperSend::OnCheck02() 
{
	m_Check_SSHex_02 = !m_Check_SSHex_02;
}

void CDialogSuperSend::OnCheck03() 
{
	m_Check_SSHex_03 = !m_Check_SSHex_03;
}

void CDialogSuperSend::OnCheck04() 
{
	m_Check_SSHex_04 = !m_Check_SSHex_04;
}

void CDialogSuperSend::OnCheck05() 
{
	m_Check_SSHex_05 = !m_Check_SSHex_05;
}

void CDialogSuperSend::OnCheck06() 
{
	m_Check_SSHex_06 = !m_Check_SSHex_06;
}

void CDialogSuperSend::OnCheck07() 
{
	m_Check_SSHex_07 = !m_Check_SSHex_07;
}

void CDialogSuperSend::OnCheck08() 
{
	m_Check_SSHex_08 = !m_Check_SSHex_08;
}

void CDialogSuperSend::OnCheck09() 
{
	m_Check_SSHex_09 = !m_Check_SSHex_09;
}

void CDialogSuperSend::OnCheck10() 
{
	m_Check_SSHex_10 = !m_Check_SSHex_10;
}

void CDialogSuperSend::OnCheck11() 
{
	m_Check_SSHex_11 = !m_Check_SSHex_11;
}

void CDialogSuperSend::OnCheck12() 
{
	m_Check_SSHex_12 = !m_Check_SSHex_12;
}

void CDialogSuperSend::OnCheck13() 
{
	m_Check_SSHex_13 = !m_Check_SSHex_13;
}

void CDialogSuperSend::OnCheck14() 
{
	m_Check_SSHex_14 = !m_Check_SSHex_14;
}

void CDialogSuperSend::OnCheck15() 
{
	m_Check_SSHex_15 = !m_Check_SSHex_15;
}

void CDialogSuperSend::OnCheck16() 
{
	m_Check_SSHex_16 = !m_Check_SSHex_16;
}

void CDialogSuperSend::OnCheck17() 
{
	m_Check_SSHex_17 = !m_Check_SSHex_17;
}

void CDialogSuperSend::OnCheck18() 
{
	m_Check_SSHex_18 = !m_Check_SSHex_18;
}

void CDialogSuperSend::OnCheck19() 
{
	m_Check_SSHex_19 = !m_Check_SSHex_19;
}

void CDialogSuperSend::OnCheck20() 
{
	m_Check_SSHex_20 = !m_Check_SSHex_20;
}

void CDialogSuperSend::OnCheck21() 
{
	m_Check_SSHex_21 = !m_Check_SSHex_21;
}

void CDialogSuperSend::OnCheck22() 
{
	m_Check_SSHex_22 = !m_Check_SSHex_22;
}

void CDialogSuperSend::OnCheck23() 
{
	m_Check_SSHex_23 = !m_Check_SSHex_23;
}

void CDialogSuperSend::OnCheck24() 
{
	m_Check_SSHex_24 = !m_Check_SSHex_24;
}

void CDialogSuperSend::OnCheck25() 
{
	m_Check_SSHex_25 = !m_Check_SSHex_25;
}

void CDialogSuperSend::OnCheck26() 
{
	m_Check_SSHex_26 = !m_Check_SSHex_26;
}

void CDialogSuperSend::OnCheck27() 
{
	m_Check_SSHex_27 = !m_Check_SSHex_27;
}

void CDialogSuperSend::OnCheck28() 
{
	m_Check_SSHex_28 = !m_Check_SSHex_28;
}

void CDialogSuperSend::OnCheck29() 
{
	m_Check_SSHex_29 = !m_Check_SSHex_29;
}

void CDialogSuperSend::OnCheck30() 
{
	m_Check_SSHex_30 = !m_Check_SSHex_30;
}

void CDialogSuperSend::OnCheck31() 
{
	m_Check_SSHex_31 = !m_Check_SSHex_31;
}

void CDialogSuperSend::OnCheck32() 
{
	m_Check_SSHex_32 = !m_Check_SSHex_32;
}

void CDialogSuperSend::OnCheck33() 
{
	m_Check_SSHex_33 = !m_Check_SSHex_33;
}

void CDialogSuperSend::OnCheck34() 
{
	m_Check_SSHex_34 = !m_Check_SSHex_34;
}

void CDialogSuperSend::OnCheck35() 
{
	m_Check_SSHex_35 = !m_Check_SSHex_35;
}

void CDialogSuperSend::OnCheck36() 
{
	m_Check_SSHex_36 = !m_Check_SSHex_36;
}

void CDialogSuperSend::OnCheck37() 
{
	m_Check_SSHex_37 = !m_Check_SSHex_37;
}

void CDialogSuperSend::OnCheck38() 
{
	m_Check_SSHex_38 = !m_Check_SSHex_38;
}

void CDialogSuperSend::OnCheck39() 
{
	m_Check_SSHex_39 = !m_Check_SSHex_39;
}

void CDialogSuperSend::OnCheck40() 
{
	m_Check_SSHex_40 = !m_Check_SSHex_40;
}

