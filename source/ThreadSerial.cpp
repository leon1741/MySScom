#include "stdafx.h"
#include "threadserial.h"

/*************************************************************************************************/
/*                           模块静态变量定义                                                    */
/*************************************************************************************************/
static bool                  s_PortOpened = FALSE;                             /* 串口设备是否已经打开 */
static CWinThread           *s_ListenHdle = NULL;                              /* 监听串口设备的线程句柄 */
static CWinThread           *s_SerialHdle = NULL;                              /* 收发串口数据的线程句柄 */
static volatile HANDLE       s_FileHandle = INVALID_HANDLE_VALUE;              /* 串口设备文件句柄 */
static OVERLAPPED            s_EventoRead;                                     /* 串口读取事件对象 */
static OVERLAPPED            s_EventWrite;                                     /* 串口写入事件对象 */

/**************************************************************************************************
**  函数名称:  ListenProc
**  功能描述:  串口设备监听函数
**************************************************************************************************/
static UINT SerailDevHdlProc(LPVOID pParam)
{
	HANDLE   hNotify;
	HKEY     hKeyx;

	hNotify = CreateEvent(NULL, FALSE, TRUE, NULL);                            /* 首先创建一个事件对象 */

	if (hNotify == 0) {
		MessageBox(NULL, "系统资源异常，串口设备监听线程创建失败！请检查系统运行状态！", "抱歉", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		ExitProcess(0);
	}

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_NOTIFY, &hKeyx) != ERROR_SUCCESS) {
		CloseHandle(hNotify);
		MessageBox(NULL, "串口设备信息注册失败！请确认系统存在串口设备之后重启本程序", "抱歉", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		ExitProcess(0);
	}

	while (1) {                                                                /* 申请对该注册表项的监听 */

		if (RegNotifyChangeKeyValue(hKeyx, TRUE, REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET, hNotify, TRUE) != ERROR_SUCCESS) {
			CloseHandle(hNotify);
			RegCloseKey(hKeyx);
			MessageBox(NULL, "系统资源异常，串口设备注册信息监听失败！请检查系统运行状态！", "抱歉", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
			ExitProcess(0);
		}

		if (WaitForSingleObject(hNotify, INFINITE) != WAIT_FAILED) {           /* 收到注册表项变化的通知信号 */
			if (SerialDevisOpened() == FALSE) {
				::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_COMDEVLIST, 0, 0);
			} else {
				::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_COMDEVWAIT, 0, 0);
				MessageBox(NULL, "检测到串口设备发生变化！\r\n程序将在当前串口关闭之后自动更新设备列表... ", "系统提示", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
			}
		}
	}

	CloseHandle(hNotify);
	RegCloseKey(hKeyx);

	return 0;
}

/**************************************************************************************************
**  函数名称:  ReadComm
**  功能描述:  从串口获取数据
**************************************************************************************************/
static DWORD ReadComm(unsigned char *buf, DWORD dwLength)
{
	DWORD length = 0;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	ClearCommError(s_FileHandle, &dwErrorFlags, &ComStat);                     /* 首先清除错误标志 */

	ReadFile(s_FileHandle, buf, dwLength, &length, &s_EventoRead);             /* 读取串口数据 */

	return length;
}

/**************************************************************************************************
**  函数名称:  WriteComm
**  功能描述:  向串口发送数据
**************************************************************************************************/
static DWORD WriteComm(unsigned char *buf, DWORD dwLength)
{
	DWORD length = dwLength;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	ClearCommError(s_FileHandle, &dwErrorFlags, &ComStat);                     /* 首先清除错误标志 */

	WriteFile(s_FileHandle, buf, length, &length, &s_EventWrite);              /* 写入串口数据 */

	if (GetLastError() == ERROR_IO_PENDING) {                                  /* 正在处理重叠的部分，获取其长度 */
		GetOverlappedResult(s_FileHandle, &s_EventWrite, &length, TRUE);
	} else {                                                                   /* 否则，发送失败，返回0 */
		length = 0;
	}

	return length;
}

/**************************************************************************************************
**  函数名称:  ReadHandleUartData
**  功能描述:  处理所接收到的数据
**************************************************************************************************/
static void ReadHandleUartData(void)
{
	unsigned char buf[MAX_RECV_BYTE];
	DWORD length = 0;

	length = ReadComm(buf, MAX_RECV_BYTE);

	if (length > 0) {
		::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_DATARECVED, length, (LPARAM)(&buf));
	}
}

/**************************************************************************************************
**  函数名称:  SerailDataHdlProc
**  功能描述:  串口线程处理函数
**************************************************************************************************/
static UINT SerailDataHdlProc(LPVOID pParam)
{
	OVERLAPPED os;
	DWORD dwMask, dwTrans;

	dwMask = 0;
	memset(&os, 0, sizeof(OVERLAPPED));

	os.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);                          /* 创建事件内核对象 */

	if (os.hEvent == NULL) {                                                   /* 创建失败 */
		MessageBox(NULL, "串口数据收发线程创建失败！请重启程序！", "抱歉", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	while (SerialDevisOpened()) {

		ReadHandleUartData();

		if (WaitCommEvent(s_FileHandle, &dwMask, &os) == FALSE) {              /* 判断串口通信事件是否已经发生 */

			if (GetLastError() == ERROR_IO_PENDING) {                          /* 判断是否存在数据等待操作 */
				GetOverlappedResult(s_FileHandle, &os, &dwTrans, TRUE);
			} else {                                                           /* 关闭事件内核对象 */
				CloseHandle(os.hEvent);
				return -1;
			}
		}
	}

	CloseHandle(os.hEvent);                                                    /* 关闭事件内核对象 */

	return 0;
}

/**************************************************************************************************
**  函数名称:  OpenSerialDevice
**  功能描述:  打开串口设备
**************************************************************************************************/
bool OpenSerialDevice(LPCSTR dname, SRL_DEV_PARA_T *spara)
{
	DCB  dcb;
	COMMTIMEOUTS TimeOuts;
	
	if ((s_SerialHdle != NULL) || (s_PortOpened == TRUE) || (s_FileHandle != INVALID_HANDLE_VALUE)) {
		MessageBox(NULL, "串口设备已经在运行中，请确认", "提示", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	
	s_FileHandle = CreateFile(dname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

	if (s_FileHandle == INVALID_HANDLE_VALUE) {                                /* 串口文件打开失败 */
		MessageBox(NULL, "串口设备打开失败！该串口可能正在使用中！", "提示", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		s_PortOpened = FALSE;
		return FALSE;
	}

	memset(&s_EventoRead, 0, sizeof(OVERLAPPED));
	memset(&s_EventWrite, 0, sizeof(OVERLAPPED));

	s_EventoRead.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	s_EventWrite.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

	if ((s_EventoRead.hEvent == INVALID_HANDLE_VALUE) || (s_EventWrite.hEvent == INVALID_HANDLE_VALUE)) {
		CloseSerialDevice();
		MessageBox(NULL, "监听事件创建失败！请重启程序后再尝试...", "提示", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	SetupComm(s_FileHandle, MAX_RECV_BYTE, MAX_SEND_BYTE);                     /* 设置缓存大小 */
	SetCommMask(s_FileHandle, EV_RXCHAR);                                      /* 设置过滤掩码 - 所有字符全接收 */

	TimeOuts.ReadIntervalTimeout         = MAXDWORD;                           /* 读间隔超时 */
	TimeOuts.ReadTotalTimeoutConstant    = 0;                                  /* 读时间常量 */
	TimeOuts.ReadTotalTimeoutMultiplier  = 0;                                  /* 读时间系数 */
	TimeOuts.WriteTotalTimeoutConstant   = 50;                                 /* 写时间常量 */
	TimeOuts.WriteTotalTimeoutMultiplier = 2000;                               /* 写时间系数 */

	SetCommTimeouts(s_FileHandle, &TimeOuts);                                  /* 设置超时参数 */

	if (GetCommState(s_FileHandle, &dcb) == FALSE) {                           /* 首先获取当前的工作参数 */
		CloseSerialDevice();
		MessageBox(NULL, "串口设备工作参数读取失败，请确认设备的工作状态！", "提示", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	dcb.fBinary      = TRUE;                                                   /* 二进制模式 */
	dcb.BaudRate     = spara->baudrate;                                        /* 设置波特率 */
	dcb.ByteSize     = spara->databits;                                        /* 设置数据位 */
	dcb.StopBits     = spara->stopbits;                                        /* 设置停止位 */
	dcb.fParity      = TRUE;                                                   /* 开启校验功能 */
	dcb.Parity       = spara->checkbit;                                        /* 设置校验位 */
	dcb.XonChar      = XON;
	dcb.XoffChar     = XOFF;
	dcb.fOutxCtsFlow = 0;
	dcb.fRtsControl  = 0;
	dcb.fInX         = 0;
	dcb.fOutX        = 0;

	if (dcb.XoffLim = 50) {
		dcb.XonLim = 1;
	} else {
		dcb.XonLim = 0;
	}

	if (SetCommState(s_FileHandle, &dcb) == FALSE) {                           /* 配置串口参数 */
		CloseSerialDevice();
		MessageBox(NULL, "串口设备工作参数配置失败，请确认设备的工作状态！", "提示", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	s_SerialHdle = AfxBeginThread(SerailDataHdlProc, NULL, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);

	if (s_SerialHdle == NULL) {                                                /* 如果线程创建失败 */
		CloseSerialDevice();
		MessageBox(NULL, "串口设备数据收发线程创建失败！请重启程序后再尝试...", "提示", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	s_PortOpened = TRUE;
	s_SerialHdle->ResumeThread();

	return TRUE;
}

/**************************************************************************************************
**  函数名称:  CloseSerialDevice
**  功能描述:  关闭串口设备
**************************************************************************************************/
bool CloseSerialDevice(void)
{
	if (s_SerialHdle != NULL) {
		WaitForSingleObject(s_SerialHdle->m_hThread, IGNORE);
		s_SerialHdle = NULL;
	}

	if (s_FileHandle != INVALID_HANDLE_VALUE) {
		CloseHandle(s_FileHandle);
		s_FileHandle = INVALID_HANDLE_VALUE;
	}

	if (s_EventWrite.hEvent != INVALID_HANDLE_VALUE) {
		CloseHandle(s_EventWrite.hEvent);
		s_EventWrite.hEvent = INVALID_HANDLE_VALUE;
	}

	if (s_EventoRead.hEvent != INVALID_HANDLE_VALUE) {
		CloseHandle(s_EventoRead.hEvent);
		s_EventoRead.hEvent = INVALID_HANDLE_VALUE;
	}

	if (s_PortOpened == TRUE) {
		s_PortOpened = FALSE;
	}

	return TRUE;
}

/**************************************************************************************************
**  函数名称:  SerialDevisOpened
**  功能描述:  串口设备是否已经打开
**************************************************************************************************/
bool SerialDevisOpened(void)
{
	return s_PortOpened;
}

/**************************************************************************************************
**  函数名称:  SendSerialData
**  功能描述:  尝试发送串口数据
**************************************************************************************************/
int SendSerialData(unsigned char *sbuf, int slen)
{
	if (SerialDevisOpened() == FALSE) {                                        /* 串口设备尚未打开 */
		return 0;
	}

	if (slen > MAX_SEND_BYTE) {                                                /* 待发数据长度超长 */
		return 0;
	}

	return WriteComm(sbuf, slen);
}

/**************************************************************************************************
**  函数名称:  CreateDeviceThread
**  功能描述:  创建串口设备监听线程
**************************************************************************************************/
bool CreateDeviceThread(void)
{
	s_ListenHdle = AfxBeginThread(SerailDevHdlProc, NULL, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);

	if (s_ListenHdle == NULL) {                                                /* 如果线程创建失败 */
		return FALSE;
	} else {                                                                   /* 开始正常工作 */
		s_ListenHdle->ResumeThread();
		return TRUE;
	}
}

