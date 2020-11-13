#if !defined(AFX_DIALOGEXFUNCT_H__006A9560_37A5_426F_9193_E4EF22A3C458__INCLUDED_)
#define AFX_DIALOGEXFUNCT_H__006A9560_37A5_426F_9193_E4EF22A3C458__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogExfunct.h : header file
//

typedef struct {
    unsigned char   Flags0;                                          /* Flags0 = Middle + Flags1 */
    unsigned char   Middle;                                          /* Middle = Middle + Flags2 */
    unsigned char   Flags1;
    unsigned char   Flags2;
} ASMRULE_T;

#define  _DISPLAY_HEX                  0x00                          // 以16进制格式显示
#define  _DISPLAY_CHAR                 0x01                          // 以字符格式显示

#define  _MODE_ASEMBLE                 0x00                          // 封装数据模式
#define  _MODE_DSAMBLE                 0x01                          // 解封数据模式

#define  _CHKSUM_ADO                   0x00                          // 原码累加和
#define  _CHKSUM_ADN                   0x01                          // 反码累加和
#define  _CHKSUM_XOR                   0x02                          // 异或校验和

#define  MAX_CHKSUM_BYTE               1024                          // 计算校验和的最大长度
#define  MAX_FRAME_LENTH               1024                          // 数据封装的最大长度

class CDialogExfunct : public CDialog
{
// Construction
public:
	CDialogExfunct(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogExfunct)
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
	//}}AFX_DATA

	int     s_curdispmode;                                                     // 记录当前的显示模式

	unsigned char GetChkSum_O(unsigned char *ptr, long len);
	unsigned char GetChkSum_N(unsigned char *ptr, long len);
	unsigned char GetChkSum_Xor(unsigned char *ptr, long len);

	unsigned int  AssembleByRules(unsigned char *dptr, unsigned char *sptr, int len, int maxlen, ASMRULE_T *rule);
	unsigned int  DeassembleByRules(unsigned char *dptr, unsigned char *sptr, int len, int maxlen, ASMRULE_T *rule);

	unsigned char ConvertHexChar(unsigned char ch);
	CString       CharToHex(CString InStr);
	CString       HexToChar(CString InStr);
	int           String2Hex(CString str, CByteArray &senddata);
	bool          ParseCharIsLegal(unsigned char inchar);
	bool          ParseCStrisLegal(CString str, long len);

	void ShowHideExDlgWindow(bool show);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogExfunct)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;

	// Generated message map functions
	//{{AFX_MSG(CDialogExfunct)
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGEXFUNCT_H__006A9560_37A5_426F_9193_E4EF22A3C458__INCLUDED_)
