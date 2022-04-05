#include "stdafx.h"
#include "threadserial.h"

/*************************************************************************************************/
/*                           ģ�龲̬��������                                                    */
/*************************************************************************************************/
static bool                  s_PortOpened = FALSE;                             /* �����豸�Ƿ��Ѿ��� */
static CWinThread           *s_ListenHdle = NULL;                              /* ���������豸���߳̾�� */
static CWinThread           *s_SerialHdle = NULL;                              /* �շ��������ݵ��߳̾�� */
static volatile HANDLE       s_FileHandle = INVALID_HANDLE_VALUE;              /* �����豸�ļ���� */
static OVERLAPPED            s_EventoRead;                                     /* ���ڶ�ȡ�¼����� */
static OVERLAPPED            s_EventWrite;                                     /* ����д���¼����� */

/**************************************************************************************************
**  ��������:  ListenProc
**  ��������:  �����豸��������
**************************************************************************************************/
static UINT SerailDevHdlProc(LPVOID pParam)
{
	HANDLE   hNotify;
	HKEY     hKeyx;

	hNotify = CreateEvent(NULL, FALSE, TRUE, NULL);                            /* ���ȴ���һ���¼����� */

	if (hNotify == 0) {
		MessageBox(NULL, "ϵͳ��Դ�쳣�������豸�����̴߳���ʧ�ܣ�����ϵͳ����״̬��", "��Ǹ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		ExitProcess(0);
	}

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_NOTIFY, &hKeyx) != ERROR_SUCCESS) {
		CloseHandle(hNotify);
		MessageBox(NULL, "�����豸��Ϣע��ʧ�ܣ���ȷ��ϵͳ���ڴ����豸֮������������", "��Ǹ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		ExitProcess(0);
	}

	while (1) {                                                                /* ����Ը�ע�����ļ��� */

		if (RegNotifyChangeKeyValue(hKeyx, TRUE, REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET, hNotify, TRUE) != ERROR_SUCCESS) {
			CloseHandle(hNotify);
			RegCloseKey(hKeyx);
			MessageBox(NULL, "ϵͳ��Դ�쳣�������豸ע����Ϣ����ʧ�ܣ�����ϵͳ����״̬��", "��Ǹ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
			ExitProcess(0);
		}

		if (WaitForSingleObject(hNotify, INFINITE) != WAIT_FAILED) {           /* �յ�ע�����仯��֪ͨ�ź� */
			if (SerialDevisOpened() == FALSE) {
				::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_COMDEVLIST, 0, 0);
			} else {
				::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USERMSG_COMDEVWAIT, 0, 0);
				MessageBox(NULL, "��⵽�����豸�����仯��\r\n�����ڵ�ǰ���ڹر�֮���Զ������豸�б�... ", "ϵͳ��ʾ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
			}
		}
	}

	CloseHandle(hNotify);
	RegCloseKey(hKeyx);

	return 0;
}

/**************************************************************************************************
**  ��������:  ReadComm
**  ��������:  �Ӵ��ڻ�ȡ����
**************************************************************************************************/
static DWORD ReadComm(unsigned char *buf, DWORD dwLength)
{
	DWORD length = 0;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	ClearCommError(s_FileHandle, &dwErrorFlags, &ComStat);                     /* ������������־ */

	ReadFile(s_FileHandle, buf, dwLength, &length, &s_EventoRead);             /* ��ȡ�������� */

	return length;
}

/**************************************************************************************************
**  ��������:  WriteComm
**  ��������:  �򴮿ڷ�������
**************************************************************************************************/
static DWORD WriteComm(unsigned char *buf, DWORD dwLength)
{
	DWORD length = dwLength;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	ClearCommError(s_FileHandle, &dwErrorFlags, &ComStat);                     /* ������������־ */

	WriteFile(s_FileHandle, buf, length, &length, &s_EventWrite);              /* д�봮������ */

	if (GetLastError() == ERROR_IO_PENDING) {                                  /* ���ڴ����ص��Ĳ��֣���ȡ�䳤�� */
		GetOverlappedResult(s_FileHandle, &s_EventWrite, &length, TRUE);
	} else {                                                                   /* ���򣬷���ʧ�ܣ�����0 */
		length = 0;
	}

	return length;
}

/**************************************************************************************************
**  ��������:  ReadHandleUartData
**  ��������:  ���������յ�������
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
**  ��������:  SerailDataHdlProc
**  ��������:  �����̴߳�����
**************************************************************************************************/
static UINT SerailDataHdlProc(LPVOID pParam)
{
	OVERLAPPED os;
	DWORD dwMask, dwTrans;

	dwMask = 0;
	memset(&os, 0, sizeof(OVERLAPPED));

	os.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);                          /* �����¼��ں˶��� */

	if (os.hEvent == NULL) {                                                   /* ����ʧ�� */
		MessageBox(NULL, "���������շ��̴߳���ʧ�ܣ�����������", "��Ǹ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	while (SerialDevisOpened()) {

		ReadHandleUartData();

		if (WaitCommEvent(s_FileHandle, &dwMask, &os) == FALSE) {              /* �жϴ���ͨ���¼��Ƿ��Ѿ����� */

			if (GetLastError() == ERROR_IO_PENDING) {                          /* �ж��Ƿ�������ݵȴ����� */
				GetOverlappedResult(s_FileHandle, &os, &dwTrans, TRUE);
			} else {                                                           /* �ر��¼��ں˶��� */
				CloseHandle(os.hEvent);
				return -1;
			}
		}
	}

	CloseHandle(os.hEvent);                                                    /* �ر��¼��ں˶��� */

	return 0;
}

/**************************************************************************************************
**  ��������:  OpenSerialDevice
**  ��������:  �򿪴����豸
**************************************************************************************************/
bool OpenSerialDevice(LPCSTR dname, SRL_DEV_PARA_T *spara)
{
	DCB  dcb;
	COMMTIMEOUTS TimeOuts;
	
	if ((s_SerialHdle != NULL) || (s_PortOpened == TRUE) || (s_FileHandle != INVALID_HANDLE_VALUE)) {
		MessageBox(NULL, "�����豸�Ѿ��������У���ȷ��", "��ʾ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	
	s_FileHandle = CreateFile(dname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

	if (s_FileHandle == INVALID_HANDLE_VALUE) {                                /* �����ļ���ʧ�� */
		MessageBox(NULL, "�����豸��ʧ�ܣ��ô��ڿ�������ʹ���У�", "��ʾ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		s_PortOpened = FALSE;
		return FALSE;
	}

	memset(&s_EventoRead, 0, sizeof(OVERLAPPED));
	memset(&s_EventWrite, 0, sizeof(OVERLAPPED));

	s_EventoRead.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	s_EventWrite.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

	if ((s_EventoRead.hEvent == INVALID_HANDLE_VALUE) || (s_EventWrite.hEvent == INVALID_HANDLE_VALUE)) {
		CloseSerialDevice();
		MessageBox(NULL, "�����¼�����ʧ�ܣ�������������ٳ���...", "��ʾ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	SetupComm(s_FileHandle, MAX_RECV_BYTE, MAX_SEND_BYTE);                     /* ���û����С */
	SetCommMask(s_FileHandle, EV_RXCHAR);                                      /* ���ù������� - �����ַ�ȫ���� */

	TimeOuts.ReadIntervalTimeout         = MAXDWORD;                           /* �������ʱ */
	TimeOuts.ReadTotalTimeoutConstant    = 0;                                  /* ��ʱ�䳣�� */
	TimeOuts.ReadTotalTimeoutMultiplier  = 0;                                  /* ��ʱ��ϵ�� */
	TimeOuts.WriteTotalTimeoutConstant   = 50;                                 /* дʱ�䳣�� */
	TimeOuts.WriteTotalTimeoutMultiplier = 2000;                               /* дʱ��ϵ�� */

	SetCommTimeouts(s_FileHandle, &TimeOuts);                                  /* ���ó�ʱ���� */

	if (GetCommState(s_FileHandle, &dcb) == FALSE) {                           /* ���Ȼ�ȡ��ǰ�Ĺ������� */
		CloseSerialDevice();
		MessageBox(NULL, "�����豸����������ȡʧ�ܣ���ȷ���豸�Ĺ���״̬��", "��ʾ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	dcb.fBinary      = TRUE;                                                   /* ������ģʽ */
	dcb.BaudRate     = spara->baudrate;                                        /* ���ò����� */
	dcb.ByteSize     = spara->databits;                                        /* ��������λ */
	dcb.StopBits     = spara->stopbits;                                        /* ����ֹͣλ */
	dcb.fParity      = TRUE;                                                   /* ����У�鹦�� */
	dcb.Parity       = spara->checkbit;                                        /* ����У��λ */
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

	if (SetCommState(s_FileHandle, &dcb) == FALSE) {                           /* ���ô��ڲ��� */
		CloseSerialDevice();
		MessageBox(NULL, "�����豸������������ʧ�ܣ���ȷ���豸�Ĺ���״̬��", "��ʾ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	s_SerialHdle = AfxBeginThread(SerailDataHdlProc, NULL, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);

	if (s_SerialHdle == NULL) {                                                /* ����̴߳���ʧ�� */
		CloseSerialDevice();
		MessageBox(NULL, "�����豸�����շ��̴߳���ʧ�ܣ�������������ٳ���...", "��ʾ", MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	s_PortOpened = TRUE;
	s_SerialHdle->ResumeThread();

	return TRUE;
}

/**************************************************************************************************
**  ��������:  CloseSerialDevice
**  ��������:  �رմ����豸
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
**  ��������:  SerialDevisOpened
**  ��������:  �����豸�Ƿ��Ѿ���
**************************************************************************************************/
bool SerialDevisOpened(void)
{
	return s_PortOpened;
}

/**************************************************************************************************
**  ��������:  SendSerialData
**  ��������:  ���Է��ʹ�������
**************************************************************************************************/
int SendSerialData(unsigned char *sbuf, int slen)
{
	if (SerialDevisOpened() == FALSE) {                                        /* �����豸��δ�� */
		return 0;
	}

	if (slen > MAX_SEND_BYTE) {                                                /* �������ݳ��ȳ��� */
		return 0;
	}

	return WriteComm(sbuf, slen);
}

/**************************************************************************************************
**  ��������:  CreateDeviceThread
**  ��������:  ���������豸�����߳�
**************************************************************************************************/
bool CreateDeviceThread(void)
{
	s_ListenHdle = AfxBeginThread(SerailDevHdlProc, NULL, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);

	if (s_ListenHdle == NULL) {                                                /* ����̴߳���ʧ�� */
		return FALSE;
	} else {                                                                   /* ��ʼ�������� */
		s_ListenHdle->ResumeThread();
		return TRUE;
	}
}

