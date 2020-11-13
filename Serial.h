// Serial.h: interface for the CSerial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIAL_H__7522BCB7_A45C_4ADC_9F97_22DFE84F05BF__INCLUDED_)
#define AFX_SERIAL_H__7522BCB7_A45C_4ADC_9F97_22DFE84F05BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DATA_READ_TIMEOUT	      100   // Milliseconds
#define STATUS_CHECK_TIMEOUT      100   // Milliseconds

class CSerial  
{
public:
	CSerial();
	virtual ~CSerial();
public:	
	bool SendData(char szData[],int len);
	bool ReadData(char szData[],int&len);
	BOOL Close();
	BOOL	Open(HWND hWnd,UINT Msg,BYTE nCom, DWORD dwBaudRate,
					BYTE byByteSize,BYTE byParity,BYTE byStopBits);
private:
	bool	m_bOpened;
	HANDLE	m_hCommPort;

	HANDLE  m_start_data_thread;
	HANDLE  m_start_analysis_thread;
	HANDLE  m_start_event_thread;

	HANDLE  m_end_event_thread;
	HANDLE  m_end_analysis_thread;
	HANDLE  m_end_data_thread;

	HANDLE  m_event_thread_end;
	HANDLE  m_analysis_thread_end;
	HANDLE  m_data_thread_end;

	HANDLE  m_data_come_event;
	HANDLE  m_event_come_event;

	HANDLE  m_end_send_thread;
	HANDLE  m_send_thread_end;
	HANDLE  m_send_data_event;

	HWND	m_h_father_wnd;
	UINT	m_u_message;
private:
	static	UINT SendDataProc(LPVOID lpParam);
	void	ClearSysReadBufferContent();
	void	NotifyWriteData(void *lpdata);
	void	NotifyReadData();
	void	Init();
	void	UnInit();
	void	CloseAndCleanHandle(HANDLE&handle);
	static	UINT ReadEventProc(LPVOID lpParam);
	static	UINT AnalysisEventProc(LPVOID lpParam);
	static	UINT ReadDataProc(LPVOID lpParam);
};

#endif // !defined(AFX_SERIAL_H__7522BCB7_A45C_4ADC_9F97_22DFE84F05BF__INCLUDED_)
