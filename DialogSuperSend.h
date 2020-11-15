#pragma once

#include "mysscomtool.h"

/*************************************************************************************************/
/*                                     各字段参数名称定义                                        */
/*************************************************************************************************/
#define SUPERSEND_POSTIONX             "PostionX"
#define SUPERSEND_POSTIONY             "PostionY"

#define SUPERSEND_LOOPTIME             "LoopTime"

/*************************************************************************************************/
/*                                     模块宏定义                                                */
/*************************************************************************************************/
#define SDTMODE_NUM                    20                                      /* 普通模式下的条目个数 */
#define EXTMODE_NUM                    40                                      /* 扩展模式下的条目个数 */

#define SCANR_TIMER                    100                                     /* 多条轮发的扫描间隔 */

class CDialogSuperSend : public CDialog
{
public:
	CDialogSuperSend(CWnd* pParent = NULL);

	enum { IDD = IDD_DIALOG_SUPERSEND };
	
	int            s_DialogPos_X;                                              /* 记录窗口的X位置 */
	int            s_DialogPos_Y;                                              /* 记录窗口的Y位置 */

	bool           s_expandmode;                                               /* 是否处于扩展发送模式 */
	unsigned int   s_curdatacnt;                                               /* 当前发送到第几个数据 */
	bool           s_cirsendall;                                               /* 是否需要轮回发送全部数据 */
	bool           s_issenddata;                                               /* 是否正处于发送数据中 */

	int            s_sendcnt[EXTMODE_NUM];                                     /* 记录每一条数据的发送计数 */

	bool EditDataValid(CString cstr, BOOL ishex);
	int  GetSrValidDataNo(void);
	int  GetSrValidTimeNo(void);
	int  GetSrInValidTimeNo(void);
	void TrytoSendData(int index);
	void TrytoContinueSend(void);
	void TrytoSendEachData(void);
	void ShowHideTimeEdit(bool enanble);
	void InitateSrDlgPos(void);
	void ShowHideDlgWindow(bool show);
	void InitiateAllParas(void);
	void RecordAllParas(void);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:

	BOOL	m_Check_SSHex_01;
	BOOL	m_Check_SSHex_02;
	BOOL	m_Check_SSHex_03;
	BOOL	m_Check_SSHex_04;
	BOOL	m_Check_SSHex_05;
	BOOL	m_Check_SSHex_06;
	BOOL	m_Check_SSHex_07;
	BOOL	m_Check_SSHex_08;
	BOOL	m_Check_SSHex_09;
	BOOL	m_Check_SSHex_10;
	BOOL	m_Check_SSHex_11;
	BOOL	m_Check_SSHex_12;
	BOOL	m_Check_SSHex_13;
	BOOL	m_Check_SSHex_14;
	BOOL	m_Check_SSHex_15;
	BOOL	m_Check_SSHex_16;
	BOOL	m_Check_SSHex_17;
	BOOL	m_Check_SSHex_18;
	BOOL	m_Check_SSHex_19;
	BOOL	m_Check_SSHex_20;
	BOOL	m_Check_SSHex_21;
	BOOL	m_Check_SSHex_22;
	BOOL	m_Check_SSHex_23;
	BOOL	m_Check_SSHex_24;
	BOOL	m_Check_SSHex_25;
	BOOL	m_Check_SSHex_26;
	BOOL	m_Check_SSHex_27;
	BOOL	m_Check_SSHex_28;
	BOOL	m_Check_SSHex_29;
	BOOL	m_Check_SSHex_30;
	BOOL	m_Check_SSHex_31;
	BOOL	m_Check_SSHex_32;
	BOOL	m_Check_SSHex_33;
	BOOL	m_Check_SSHex_34;
	BOOL	m_Check_SSHex_35;
	BOOL	m_Check_SSHex_36;
	BOOL	m_Check_SSHex_37;
	BOOL	m_Check_SSHex_38;
	BOOL	m_Check_SSHex_39;
	BOOL	m_Check_SSHex_40;
	CString	m_Edit_AutoTime;
	int		m_Radio_SendAll;

	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonExpand();
	afx_msg void OnButtonSend01();
	afx_msg void OnButtonSend02();
	afx_msg void OnButtonSend03();
	afx_msg void OnButtonSend04();
	afx_msg void OnButtonSend05();
	afx_msg void OnButtonSend06();
	afx_msg void OnButtonSend07();
	afx_msg void OnButtonSend08();
	afx_msg void OnButtonSend09();
	afx_msg void OnButtonSend10();
	afx_msg void OnButtonSend11();
	afx_msg void OnButtonSend12();
	afx_msg void OnButtonSend13();
	afx_msg void OnButtonSend14();
	afx_msg void OnButtonSend15();
	afx_msg void OnButtonSend16();
	afx_msg void OnButtonSend17();
	afx_msg void OnButtonSend18();
	afx_msg void OnButtonSend19();
	afx_msg void OnButtonSend20();
	afx_msg void OnButtonSend21();
	afx_msg void OnButtonSend22();
	afx_msg void OnButtonSend23();
	afx_msg void OnButtonSend24();
	afx_msg void OnButtonSend25();
	afx_msg void OnButtonSend26();
	afx_msg void OnButtonSend27();
	afx_msg void OnButtonSend28();
	afx_msg void OnButtonSend29();
	afx_msg void OnButtonSend30();
	afx_msg void OnButtonSend31();
	afx_msg void OnButtonSend32();
	afx_msg void OnButtonSend33();
	afx_msg void OnButtonSend34();
	afx_msg void OnButtonSend35();
	afx_msg void OnButtonSend36();
	afx_msg void OnButtonSend37();
	afx_msg void OnButtonSend38();
	afx_msg void OnButtonSend39();
	afx_msg void OnButtonSend40();
	afx_msg void OnCheck01();
	afx_msg void OnCheck02();
	afx_msg void OnCheck03();
	afx_msg void OnCheck04();
	afx_msg void OnCheck05();
	afx_msg void OnCheck06();
	afx_msg void OnCheck07();
	afx_msg void OnCheck08();
	afx_msg void OnCheck09();
	afx_msg void OnCheck10();
	afx_msg void OnCheck11();
	afx_msg void OnCheck12();
	afx_msg void OnCheck13();
	afx_msg void OnCheck14();
	afx_msg void OnCheck15();
	afx_msg void OnCheck16();
	afx_msg void OnCheck17();
	afx_msg void OnCheck18();
	afx_msg void OnCheck19();
	afx_msg void OnCheck20();
	afx_msg void OnCheck21();
	afx_msg void OnCheck22();
	afx_msg void OnCheck23();
	afx_msg void OnCheck24();
	afx_msg void OnCheck25();
	afx_msg void OnCheck26();
	afx_msg void OnCheck27();
	afx_msg void OnCheck28();
	afx_msg void OnCheck29();
	afx_msg void OnCheck30();
	afx_msg void OnCheck31();
	afx_msg void OnCheck32();
	afx_msg void OnCheck33();
	afx_msg void OnCheck34();
	afx_msg void OnCheck35();
	afx_msg void OnCheck36();
	afx_msg void OnCheck37();
	afx_msg void OnCheck38();
	afx_msg void OnCheck39();
	afx_msg void OnCheck40();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnRadioSendAll();
	afx_msg void OnRadioSendEach();
	afx_msg void OnButtonStartSend();
	DECLARE_MESSAGE_MAP()
};


