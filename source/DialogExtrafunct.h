#pragma once

/*************************************************************************************************/
/*                                     ���ֶβ������ƶ���                                        */
/*************************************************************************************************/
#define EXTRAFUNT_POSTIONX             "PostionX"
#define EXTRAFUNT_POSTIONY             "PostionY"

/*************************************************************************************************/
/*                                     ģ��궨��                                                */
/*************************************************************************************************/
#define  _DISPLAY_HEX                  0x00                                    // ��16���Ƹ�ʽ��ʾ
#define  _DISPLAY_CHAR                 0x01                                    // ���ַ���ʽ��ʾ

#define  _MODE_ASEMBLE                 0x00                                    // ��װ����ģʽ
#define  _MODE_DSAMBLE                 0x01                                    // �������ģʽ

#define  _CHKSUM_ADO                   0x00                                    // ԭ���ۼӺ�
#define  _CHKSUM_ADN                   0x01                                    // �����ۼӺ�
#define  _CHKSUM_XOR                   0x02                                    // ���У���

#define  MAX_CHKSUM_BYTE               1024                                    // ����У��͵���󳤶�
#define  MAX_FRAME_LENTH               1024                                    // ���ݷ�װ����󳤶�

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

	int     s_curdispmode;                                                     /* ��¼��ǰ����ʾģʽ */

	int     s_DialogPos_X;                                                     /* ��¼���ڵ�Xλ�� */
	int     s_DialogPos_Y;                                                     /* ��¼���ڵ�Yλ�� */

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
