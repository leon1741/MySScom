#pragma once

/*************************************************************************************************/
/*                                     各字段参数名称定义                                        */
/*************************************************************************************************/
#define EXTRAFUNT_POSTIONX             "PostionX"
#define EXTRAFUNT_POSTIONY             "PostionY"

/*************************************************************************************************/
/*                                     模块宏定义                                                */
/*************************************************************************************************/
#define  _DISPLAY_HEX                  0x00                                    // 以16进制格式显示
#define  _DISPLAY_CHAR                 0x01                                    // 以字符格式显示

#define  _MODE_ASEMBLE                 0x00                                    // 封装数据模式
#define  _MODE_DSAMBLE                 0x01                                    // 解封数据模式

#define  _CHKSUM_ADO                   0x00                                    // 原码累加和
#define  _CHKSUM_ADN                   0x01                                    // 反码累加和
#define  _CHKSUM_XOR                   0x02                                    // 异或校验和

#define  MAX_CHKSUM_BYTE               1024                                    // 计算校验和的最大长度
#define  MAX_FRAME_LENTH               1024                                    // 数据封装的最大长度

class CDialogExtrafunct : public CDialog
{
public:
	CDialogExtrafunct(CWnd* pParent = NULL);

	enum { IDD = IDD_DIALOG_EXFUNCT };

	int		m_Radio_Assmble;
	int		m_Radio_Checksum;
	int		m_Radio_Dispmode;
	CString	m_Edit_AFrame;
	CString	m_Edit_BFrame;
	CString	m_Edit_Checksum;
	CString	m_Edit_Chksum10;
	CString	m_Edit_Chksum16;
	CString	m_Edit_Change;
	CString	m_Edit_Char1;
	CString	m_Edit_Char2;
	CString	m_Edit_Head1;
	CString	m_Edit_Head2;
	CString	m_Edit_Key;

	int     s_curdispmode;                                                     /* 记录当前的显示模式 */

	int     s_DialogPos_X;                                                     /* 记录窗口的X位置 */
	int     s_DialogPos_Y;                                                     /* 记录窗口的Y位置 */

	void ShowHideDlgWindow(bool show);
	void InitiateAllParas(void);
	void RecordAllParas(void);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	CToolTipCtrl m_tooltip;

	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnRADIODispChar();
	afx_msg void OnButtonGetChksum();
	afx_msg void OnButtonFrame();
	afx_msg void OnButtonUnframe();
	afx_msg void OnRadioDispHex();
	afx_msg void OnChangeEditHead2();
	afx_msg void OnRadioAssemble();
	afx_msg void OnRadioDisasmble();

	bool InputStrValid(CString incstr, int maxlen);

	DECLARE_MESSAGE_MAP()
};
