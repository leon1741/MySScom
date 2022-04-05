#pragma once

/*************************************************************************************************/
/*                                     各字段参数名称定义                                        */
/*************************************************************************************************/
#define AUTOREPLY_POSTIONX             "PostionX"
#define AUTOREPLY_POSTIONY             "PostionY"

/*************************************************************************************************/
/*                                     模块宏定义                                                */
/*************************************************************************************************/
#define MAX_STR_NUM                    8                                       /* 最多支持的字符串个数 */
#define MAX_STR_LEN                    512                                     /* 最多支持的字符串长度 */


class CDialogAutoReply : public CDialog
{
	DECLARE_DYNAMIC(CDialogAutoReply)

public:
	CDialogAutoReply(CWnd* pParent = NULL);
	virtual ~CDialogAutoReply();

	void ShowHideDlgWindow(bool show);
	void InitiateAllParas(void);
	void RecordAllParas(void);

	int GetTotalStringNo(void);
	CString GetRecvString(int index);
	CString GetSendString(int index);

	int      s_DialogPos_X;                                                    /* 记录窗口的X位置 */
	int      s_DialogPos_Y;                                                    /* 记录窗口的Y位置 */

	CString  s_RecvStrList[MAX_STR_NUM];                                       /* 接收字符串列表 */
	CString  s_SendStrList[MAX_STR_NUM];                                       /* 应答字符串列表 */

	enum { IDD = IDD_DIALOG_AUTOREPLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	void SetEditControlEnble(bool enable);
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonClearall();
	afx_msg void OnBnClickedButtonSavestr();
};


