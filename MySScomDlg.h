#pragma once

#include "threadserial.h"
#include "DialogDisplaylFilt.h"
#include "DialogSuperSend.h"
#include "DialogExtrafunct.h"
#include "DialogKeywords.h"
#include "DialogAutoReply.h"
#include "DialogAboutMe.h"

/*************************************************************************************************/
/*                                     �汾���ƿ���                                              */
/*************************************************************************************************/
#define  VERSION_COMON                 0x01                                    /* �����汾 */
#define  VERSION_YAXON                 0x02                                    /* ��Ѹ�汾 */

#define  VERSION_CTRL                  VERSION_YAXON

#define  RELEASE_VERSION               0                                       /* �Ƿ�Ϊ��ʽ�����汾 */

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
/*                                     ���ֶβ������ƶ���                                        */
/*************************************************************************************************/
#define MAINFRAME_POSTIONX             "PostionX"
#define MAINFRAME_POSTIONY             "PostionY"
#define MAINFRAME_COMMPORT             "CommPort"
#define MAINFRAME_BAUDRATE             "BaudRate"
#define MAINFRAME_DATABITS             "DataBits"
#define MAINFRAME_CHECKBIT             "CheckBit"
#define MAINFRAME_STOPBITS             "StopBits"
#define MAINFRAME_SHOWTIME             "ShowTime"
#define MAINFRAME_HEXDISPL             "HexDispl"
#define MAINFRAME_HEXFRAME             "HexFrame"
#define MAINFRAME_PROTOACK             "ProtoAck"
#define MAINFRAME_AUTOCLER             "AutoCler"
#define MAINFRAME_AUTOSAVE             "AutoSave"
#define MAINFRAME_AUTOFILT             "AutoFilt"
#define MAINFRAME_KEYWORDS             "KeyWords"
#define MAINFRAME_HEXSSEND             "HexsSend"
#define MAINFRAME_CRLFSEND             "CRLFSend"
#define MAINFRAME_AUTOSEND             "AutoSend"
#define MAINFRAME_SENDHEXS             "SendHexs"
#define MAINFRAME_SENDSTRS             "SendStrs"
#define MAINFRAME_FILEPATH             "FilePath"
#define MAINFRAME_AUTCLRKB             "AutClrKB"
#define MAINFRAME_SENDTIME             "SendTime"

/*************************************************************************************************/
/*                                     ģ��궨��                                                */
/*************************************************************************************************/
#define  UPDATEEDIT_TIME               50                                      /* �༭��ˢ��ʱ���� (��λ: ����) */
#define  CHNGLINE_INTERVAL             100                                     /* 16����ģʽ���ж�֡���е��ӳ�ʱ�� (��λ: ����) */
#define  STATUSBAR_TIME                1000                                    /* ״̬��ˢ��ʱ���� (��λ: ����) */

#define  FILESEND_BYTE                 100                                     /* �����ļ�ʱÿ�η��͵��ֽ��� */

#define  PROGRESS_POS                  1000                                    /* ��������С���ȿ̶� */

#define  MIN_WIN_WIDTH                 860                                     /* ��������Сֵ */
#define  MIN_WIN_HIGHT                 540                                     /* ����߶���Сֵ */

#define  STATIC_LEFT                   18                                      /* ȫ����ʾʱ����ʾ��Ϣ������Ͻ����� */
#define  STATIC_TOP                    480                                     /* ȫ����ʾʱ����ʾ��Ϣ������Ͻ����� */
#define  STATIC_WIDTH                  122                                     /* ȫ����ʾʱ����ʾ��Ϣ��Ŀ�� */
#define  STATIC_HEIGHT                 85                                      /* ȫ����ʾʱ����ʾ��Ϣ��ĸ߶� */

#define  MAINWIN_HEIGHT                650                                     /* ������ʾ��ʾ��Ϣ�ĸ߶� */

class CMySScomDlg : public CDialog
{
DECLARE_EASYSIZE

public:
	CMySScomDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_MYSSCOM_DIALOG };

	CProgressCtrl	    m_Progs_SendFile;                                      /* �����ļ��Ľ����� */

	CComboBox		    m_Combo_CommPort;                                      /* ���ں� */
	CComboBox		    m_Combo_BaudRate;                                      /* ������ */
	CComboBox		    m_Combo_DataBits;                                      /* ����λ */
	CComboBox		    m_Combo_CheckBit;                                      /* У��λ */
	CComboBox		    m_Combo_StopBits;                                      /* ����λ */

	BOOL			    m_Check_ShowTime;                                      /* �Ƿ���ʾʱ�� */
	BOOL			    m_Check_HexDispl;                                      /* �Ƿ�16������ʾ */
	BOOL			    m_Check_HexFrame;                                      /* �Ƿ���֡��ʽ��ʾ */
	BOOL			    m_Check_ProtoACK;                                      /* �Ƿ��Զ�Ӧ��Э�� */
	BOOL			    m_Check_AutoCler;                                      /* �Ƿ��Զ���� */
	BOOL			    m_Check_AutoSave;                                      /* �Ƿ��Զ����� */
	BOOL			    m_Check_AutoFilt;                                      /* �Ƿ��Զ����� */
	BOOL			    m_Check_Keywords;                                      /* �Ƿ�ؼ���ƥ�� */
	BOOL			    m_Check_HexsSend;                                      /* �Ƿ�16���Ƹ�ʽ���� */
	BOOL			    m_Check_CRLFSend;                                      /* �Ƿ��ͻس����з� */
	BOOL			    m_Check_AutoSend;	                                   /* �Ƿ��Զ����� */

	CString			    m_Edit_RecvCstr;                                       /* ���ձ༭�� */
	CString			    m_Edit_SendCstr;                                       /* ���ͱ༭�� */

	CString			    m_Edit_SendTime;                                       /* �Զ����͵�ʱ�� */
	CString			    m_Edit_AutClrKB;                                       /* �Զ���յ��ֽ�������λKB�� */
	CString			    m_Edit_FilePath;                                       /* �����ļ���·�� */

	CRichEditCtrl       m_RichEdit_Recv;                                       /* ���ձ༭���ctrl�ؼ� */

	int                 s_DialogPos_X;                                         /* ��¼���ڵ�Xλ�� */
	int                 s_DialogPos_Y;                                         /* ��¼���ڵ�Yλ�� */

	CEdit              *s_Edit_Recv;                                           /* ���ձ༭����ָ�� */
	CEdit              *s_Edit_Send;                                           /* ���ͱ༭����ָ�� */

	CDialogDsplFilt    *s_PDlgDsplFilt;                                        /* ��ʾ���ݹ���  ���ھ��ָ�� */
	CDialogSuperSend   *s_PDlgSuprSend;                                        /* �߼����͹���  ���ھ��ָ�� */
	CDialogExtrafunct  *s_PDlgExtrfunc;                                        /* ���Ӽ��㹦��  ���ھ��ָ�� */
	CDialogAutoReply   *s_PDlgAutoRply;                                        /* �Զ��ظ�����  ���ھ��ָ�� */
	CDialogKeywords    *s_PDlgKeyWords;                                        /* �ؼ��ַ�����  ���ھ��ָ�� */

	CStringArray        s_PortNumber;                                          /* ����ö�ٵ����ϴ��ڵĴ��� */
	CString             s_RecvString;                                          /* ���������Ѿ����յ��������� */

	CString             s_SendStr_Chr;                                         /* ��������������ַ��� */
	CString             s_SendStr_Hex;                                         /* �������������16���� */
	
	bool                s_RecvPaused;                                          /* �ж��Ƿ���Ҫ��ͣ���� */
	bool                s_NeedChgLne;                                          /* ����Ƿ���Ҫ������ʾ */
	bool                s_DataRecved;                                          /* �Ƿ��Ѿ��յ��������� */
	bool                s_DevNeedUpd;                                          /* �����豸�Ƿ���Ҫ���� */

	int                 s_LopSendCnt;                                          /* ѭ���������ݵļ����� */
	int                 s_RecvedByte;                                          /* �Ѿ����յ��ֽ��� */
	int                 s_SendedByte;                                          /* �Ѿ����͵��ֽ��� */

	unsigned long       s_FileDatPos;                                          /* �ļ���ǰ���͵�λ�� */
	
	CStatusBar          s_CStatusBar;                                          /* ����״̬������ */

	LONGLONG            s_StartdTcik;

	CStatic            *s_MainStatic;                                          /* �����������ڵľ�̬�ؼ� */

	BOOL  EnumCommPortList(void);
	CString GetProgramVersion(void);

	void SetControlStatus(bool Enable);
	void SetSendCtrlArea(bool Enable);

    bool KeyWordMatchOK(CString showstr);
	void ShakeMainWindow(void);
	void AttractAttention(void);
	void CloseAllChildWin(void);
	bool UserFnKeyHdl(WPARAM key);
	void ExcuteAutoReply(CString instr);

	void InformAutoReplyDlgClose(void);
	void InformDsplFiltDlgClose(void);
	void InformExtrFuncDlgClose(void);
	void InformSuprSendDlgClose(void);

	CString GetHighExactTime(void);
	bool SaveEditContent(void);
	void UpdateEditStr(CString showstr);
	void HandleUSARTData(unsigned char *sbuf, DWORD len);
    void ReadHandleUartData(void);
	void NeedAutoSendData(void);
	void UpdateStatusBarNow(void);
	bool SendDatatoComm(unsigned char *sbuf, int slen, BOOL needhex);
	bool SendFileDatatoComm(void);

	bool ConfigFileCanUse(CString target);
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
	void InitiateMainStatic(void);
	void UpdateMainStatic(void);
	void UpdateComboComs(void);

	BOOL TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip);
	BOOL TaskBarDeleteIcon(HWND hwnd, UINT uID);

protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);

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
	afx_msg void OnButtonConfigKeywords();
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
	afx_msg void OnCheckKeyword();

	afx_msg void OnChangeEditSendcstr();

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
	afx_msg LRESULT OnUsrMsgHdlComDevWait(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDataRecved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDatatoSend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlARDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlDFDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlEFDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlSSDlgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUsrMsgHdlKWDlgClose(WPARAM wParam, LPARAM lParam);

	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()
};




