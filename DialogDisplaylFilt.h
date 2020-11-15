#pragma once

/*************************************************************************************************/
/*                                     各字段参数名称定义                                        */
/*************************************************************************************************/
#define DISPLYFLT_POSTIONX             "PostionX"
#define DISPLYFLT_POSTIONY             "PostionY"

#define DISPLYFLT_FILTMODE             "FiltMode"
#define DISPLYFLT_FILTSTR1             "FiltStr1"
#define DISPLYFLT_FILTSTR2             "FiltStr2"
#define DISPLYFLT_FILTSTR3             "FiltStr3"
#define DISPLYFLT_FILTSTR4             "FiltStr4"
#define DISPLYFLT_FILTSTR5             "FiltStr5"

/*************************************************************************************************/
/*                                     模块宏定义                                                */
/*************************************************************************************************/
#define  _OPEN_MODE                    0x00                                    // 全开模式
#define  _FILT_MODE                    0x01                                    // 过滤模式
#define  _MATH_MODE                    0x02                                    // 匹配模式

class CDialogDsplFilt : public CDialog
{
	DECLARE_DYNAMIC(CDialogDsplFilt)

public:
	CDialogDsplFilt(CWnd* pParent = NULL);
	virtual ~CDialogDsplFilt();

	int     m_Radio_FilterMode;
	CString m_Edit_Str1;
	CString m_Edit_Str2;
	CString m_Edit_Str3;
	CString m_Edit_Str4;
	CString m_Edit_Str5;

	int     s_DialogPos_X;                                                     /* 记录窗口的X位置 */
	int     s_DialogPos_Y;                                                     /* 记录窗口的Y位置 */

	void ShowHideDlgWindow(bool show);
	void InitiateAllParas(void);
	void RecordAllParas(void);
	bool StringCanDisplay(CString inputstr);

	enum { IDD = IDD_DIALOG_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	bool FilterEditValid(void);
	void SetEditControlEnble(bool enable);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioOpenmode();
	afx_msg void OnBnClickedRadioFiltmode();
	afx_msg void OnBnClickedRadioDsplmode();
};
