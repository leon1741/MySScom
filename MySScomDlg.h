#pragma once

#include "threadserial.h"
#include "DialogDisplaylFilt.h"
#include "DialogSuperSend.h"
#include "DialogExtrafunct.h"
#include "DialogAutoReply.h"
#include "DialogAboutMe.h"

/*************************************************************************************************/
/*                                     �汾���ƿ���                                              */
/*************************************************************************************************/
#define  VERSION_LEON                  0x01                                    /* ����汾 */
#define  VERSION_YAXON                 0x02                                    /* ��Ѹ�汾 */

#define  VERSION_CTRL                  VERSION_YAXON

/*************************************************************************************************/
/*                                     ��ʱ��ֵ����                                              */
/*************************************************************************************************/
#define  Timer_No_UpdateDsp            0x01                                    /* ˢ����ʾ���ݶ�ʱ�� */
#define  Timer_No_StatusBar            0x02                                    /* ״̬����ʱ���¶�ʱ�� */
#define  Timer_No_AutoSend             0x03                                    /* �Զ��������ݶ�ʱ�� */
#define  Timer_No_FrameDspl            0x04                                    /* �Զ�������ʾ��ʱ�� */
#define  Timer_No_SendFile             0x05                                    /* �����ļ����ݶ�ʱ�� */
#define  Timer_No_SrAllSend            0x06                                    /* ȫ�������Զ������Ķ�ʱ�� */
#define  Timer_No_SrEachSend           0x07                                    /* ���������Զ������Ķ�ʱ�� */

/*************************************************************************************************/
/*                                     ģ��궨��                                                */
/*************************************************************************************************/
#define  MAX_DISP_BYTE                 1000000                                 /* ��ʾ�������ʾ�����ݣ��������Զ���գ� */

#define  UPDATEEDIT_TIME               50                                      /* �༭��ˢ��ʱ���� (��λ: ����) */
#define  CHNGLINE_INTERVAL             100                                     /* 16����ģʽ���ж�֡���е��ӳ�ʱ�� (��λ: ����) */
#define  STATUSBAR_TIME                1000                                    /* ״̬��ˢ��ʱ���� (��λ: ����) */

#define  FILESEND_BYTE                 100                                     /* �����ļ�ʱÿ�η��͵��ֽ��� */

#define  PROGRESS_POS                  1000                                    /* ��������С���ȿ̶� */

#define  MIN_WIN_WIDTH                 860                                     /* ��������Сֵ */
#define  MIN_WIN_HIGHT                 510                                     /* ����߶���Сֵ */

class CMySScomDlg : public CDialog
{
DECLARE_EASYSIZE

public:
	CMySScomDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_MYSSCOM_DIALOG };
	CProgressCtrl	m_Progress_SendFile;
	CComboBox		m_Combo_Check;
	CComboBox		m_Combo_Stop;
	CComboBox		m_Combo_Data;
	CComboBox		m_Combo_Baud;
	CComboBox		m_Combo_ComNo;
	BOOL			m_Check_AutoSave;
	BOOL			m_Check_AutoSend;
	BOOL			m_Check_HexDspl;
	BOOL			m_Check_HexSend;
	BOOL			m_Check_AutoClear;
	CString			m_Edit_Recv;
	CString			m_Edit_Send;
	CString			m_Edit_AutoTimer;
	CString			m_Edit_Lines;
	BOOL			m_Check_Return;
	BOOL			m_Check_ShowTime;
	BOOL			m_Check_FrameDspl;
	BOOL			m_Check_AutoReply;
	BOOL			m_Check_Filter;
	CString			m_Edit_FilePath;
	CRichEditCtrl   m_RichEdit_Recv;

	int                 s_DialogPos_X;                                         /* ��¼���ڵ�Xλ�� */
	int                 s_DialogPos_Y;                                         /* ��¼���ڵ�Yλ�� */

	CEdit              *s_Edit_Recv;                                           /* ���ձ༭����ָ�� */
	CEdit              *s_Edit_Send;                                           /* ���ͱ༭����ָ�� */

	CDialogDsplFilt    *s_PDlgDsplFilt;                                        /* �������ô��ھ��ָ�� */
	CDialogSuperSend   *s_PDlgSuprSend;                                        /* �߼����ʹ��ھ��ָ�� */
	CDialogExtrafunct  *s_PDlgExtrfunc;                                        /* ���ӹ��ܴ��ھ��ָ�� */
	CDialogAutoReply   *s_PDlgAutoRply;                                        /* �Զ��ظ����ھ��ָ�� */

	CStringArray        s_PortNumber;                                          /* ����ö�ٵ����ϴ��ڵĴ��� */
	CString             s_RecvString;                                          /* ���������Ѿ����յ��������� */

	CString             s_SendStr_Chr;                                         /* ��������������ַ��� */
	CString             s_SendStr_Hex;                                         /* �������������16���� */
	
	bool                s_RecvPaused;                                          /* �ж��Ƿ���Ҫ��ͣ���� */
	bool                s_NeedChgLne;                                          /* ����Ƿ���Ҫ������ʾ */
	bool                s_DataRecved;                                          /* �Ƿ��Ѿ��յ��������� */

	int                 s_LopSendCnt;                                          /* ѭ���������ݵļ����� */
	int                 s_RecvedLine;                                          /* �Ѿ����յ����� */
	int                 s_RecvedByte;                                          /* �Ѿ����յ��ֽ��� */
	int                 s_SendedByte;                                          /* �Ѿ����͵��ֽ��� */

	unsigned long       s_FileDatPos;                                          /* �ļ���ǰ���͵�λ�� */
	
	CStatusBar          s_CStatusBar;                                          /* ����״̬������ */

	BOOL  EnumCommPortList();

	void SetControlStatus(bool Enable);
	void SetSendCtrlArea(bool Enable);

    void CloseAllChildWin(void);

	void InformAutoReplyDlgClose(void);
	void InformDsplFiltDlgClose(void);
	void InformExtrFuncDlgClose(void);
	void InformSuprSendDlgClose(void);

	bool SaveEditContent(void);
	void UpdateEditStr(CString showstr);
	void UpdateEditDisplay(void);
	void HandleUSARTData(unsigned char *sbuf, DWORD len);
    void ReadHandleUartData(void);
	void NeedAutoSendData(void);
	void UpdateStatusBarNow(void);
	bool SendDatatoComm(unsigned char *sbuf, int slen, BOOL needhex);
	bool SendFileDatatoComm(void);

	void CreateSettingFile(void);
	void InitiateAllParas(void);
	void RecordAllParas(void);
	
	void InitiateStatusBar(void);
	void InitiateComboComs(void);
	void InitiateComboBaud(void);
	void InitiateComboData(void);
	void InitiateComboCheck(void);
	void InitiateComboStop(void);
	bool InitiateChildWins(void);
	void InitiateToolsTip(void);
	void UpdateComboComs(void);

	BOOL TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip);
	BOOL TaskBarDeleteIcon(HWND hwnd, UINT uID);

protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnClose();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	afx_msg void OnButtonPortCtrl();
	afx_msg void OnButtonRecvPause();
	afx_msg void OnButtonClearAll();
	afx_msg void OnButtonSaveFile();
	afx_msg void OnButtonSendData();
	afx_msg void OnButtonSuperSend();
	afx_msg void OnButtonExtrafunc();
	afx_msg void OnButtonOpenFile();
	afx_msg void OnButtonSendFile();
	afx_msg void OnButtonConfigDsplFilt();
	afx_msg void OnButtonConfigAutoReply();

	afx_msg void OnCheckHexDisplay();
	afx_msg void OnCheckAutoSave();
	afx_msg void OnCheckHexSend();
	afx_msg void OnCheckAutoSend();
	afx_msg void OnCheckAutoClear();
	afx_msg void OnCheckAddReturn();
	afx_msg void OnCheckShowTime();
	afx_msg void OnCheckFrameDspl();
	afx_msg void OnCheckDsplFilt();
	afx_msg void OnCheckAutoReply();

	afx_msg void OnMenuTrayAbout();
	afx_msg void OnMenuTrayHide();
	afx_msg void OnMenuTrayShow();
	afx_msg void OnMenuTrayExit();

	afx_msg void OnMenuEditCopy();
	afx_msg void OnMenuEditClear();
	afx_msg void OnMenuEditFont();
	afx_msg void OnMenuEditAbout();
	afx_msg void OnMenuEditColorWhite();
	afx_msg void OnMenuEditColorGray();
	afx_msg void OnMenuEditColorGreen();
	afx_msg void OnMenuEditColorBlue();
	afx_msg void OnMenuEditColorPink();
	afx_msg void OnMenuEditColorPurple();

	afx_msg LRESULT OnUsrMsgHdlIconNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlComDevList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDataRecved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDatatoSend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlARDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDFDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlEFDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlSSDlgClose(WPARAM wParam, LPARAM lParam);

	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()
};




