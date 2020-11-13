// Serial.cpp: implementation of the CSerial class.
// download by http://www.codefans.net
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Serial.h"

#include "DataStruct.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUm_NEW
#endif


#define MSG_READ	0
#define MSG_WRITE	1
//ȫ�ֱ�������ʱ�洢�����õ�
DATA_GROUP	g_read_data_group;
DATA_GROUP	g_send_data_group;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerial::CSerial()
{
	Init();
}

CSerial::~CSerial()
{
	UnInit();
}
/******************************************************************************
*���ܣ���ʼ��
*˵����
*������
*���أ�
******************************************************************************/
void CSerial::Init()
{
	m_h_father_wnd=NULL;
	m_u_message=0;

	m_bOpened = false;
	m_hCommPort=INVALID_HANDLE_VALUE;

	m_start_data_thread=CreateEvent(0,true,0,0);
	m_start_analysis_thread=CreateEvent(0,true,0,0);
	m_start_event_thread=CreateEvent(0,true,0,0);

	m_end_event_thread=CreateEvent(0,true,0,0);
	m_end_analysis_thread=CreateEvent(0,true,0,0);
	m_end_data_thread=CreateEvent(0,true,0,0);

	m_event_thread_end=CreateEvent(0,true,0,0);
	m_analysis_thread_end=CreateEvent(0,true,0,0);
	m_data_thread_end=CreateEvent(0,true,0,0);

	m_data_come_event=CreateEvent(0,true,0,0);
	m_event_come_event=CreateEvent(0,true,0,0);

	m_end_send_thread=CreateEvent(0,true,0,0);
	m_send_thread_end=CreateEvent(0,true,0,0);
	m_send_data_event=CreateEvent(0,true,0,0);
}
/******************************************************************************
*���ܣ��ͷ���Դ
*˵����
*������
*���أ�
******************************************************************************/
void CSerial::UnInit()
{
	Close();

	//�ر�һֱ�����¼�����
	CloseAndCleanHandle(m_start_event_thread);
	CloseAndCleanHandle(m_start_data_thread);
	CloseAndCleanHandle(m_start_analysis_thread);
	CloseAndCleanHandle(m_end_event_thread);
	CloseAndCleanHandle(m_end_analysis_thread);
	CloseAndCleanHandle(m_end_data_thread);
	CloseAndCleanHandle(m_event_thread_end);
	CloseAndCleanHandle(m_analysis_thread_end);
	CloseAndCleanHandle(m_data_thread_end);
	CloseAndCleanHandle(m_data_come_event);
	CloseAndCleanHandle(m_event_come_event);

	CloseAndCleanHandle(m_end_send_thread);
	CloseAndCleanHandle(m_send_thread_end);
	CloseAndCleanHandle(m_send_data_event);
}
/******************************************************************************
*���ܣ��رմ���
*˵����
*������
*���أ�
******************************************************************************/
BOOL CSerial::Close()
{
	if(!m_bOpened)return TRUE;

	m_bOpened=false;

	HANDLE handle[4];
	handle[0]=m_event_thread_end;
	handle[1]=m_analysis_thread_end;
	handle[2]=m_data_thread_end;
	handle[3]=m_send_thread_end;

	SetEvent(m_end_event_thread);
	SetEvent(m_end_send_thread);

	::WaitForMultipleObjects(4,handle,TRUE,INFINITE);

	TRACE("�Ѿ��ر����ĸ��̣߳�\n");
	Sleep(100);

	CloseAndCleanHandle(m_hCommPort);

	//�رմ���ʱ��Ҫ����һ������ź�
	ResetEvent(m_start_event_thread);
	ResetEvent(m_start_data_thread);
	ResetEvent(m_start_analysis_thread);
	ResetEvent(m_end_event_thread);
	ResetEvent(m_end_analysis_thread);
	ResetEvent(m_end_data_thread);
	ResetEvent(m_event_thread_end);
	ResetEvent(m_analysis_thread_end);
	ResetEvent(m_data_thread_end);
	ResetEvent(m_data_come_event);
	ResetEvent(m_event_come_event);

	ResetEvent(m_end_send_thread);
	ResetEvent(m_send_thread_end);
	ResetEvent(m_send_data_event);

	return TRUE;
}
/******************************************************************************
*���ܣ��رղ��Ƿ������
*˵����
*������
*���أ�
******************************************************************************/
void CSerial::CloseAndCleanHandle(HANDLE &handle)
{
	ASSERT(handle);
	if(handle==INVALID_HANDLE_VALUE)return;
	BOOL bRet=CloseHandle(handle);

	if(!bRet)
	{
		TRACE0( "close handle fail!\n" );
		ASSERT(0);
	}
	else
	{
		handle = INVALID_HANDLE_VALUE;
	}
}
/******************************************************************************
*���ܣ��򿪴���
*˵����
*������	nCom		������һ������--------1,2
		dwBaudRate	��������----------------9600?
		byByteSize	������λ----------------8
		byParity	����ż����λ------------0
		byStopBits	��ֹͣλ----------------1
*���أ� ���֮ǰ�Ѿ��򿪣�TRUE�������������������õģ������ϴδ򿪴���ʱ����ֵ��
		���֮ǰû�д򿪴��ڣ�
			�ɹ���TRUE��ʧ�ܣ�FALSE
******************************************************************************/
BOOL CSerial::Open(HWND hWnd,UINT Msg,BYTE nCom, DWORD dwBaudRate,
					BYTE byByteSize,BYTE byParity,BYTE byStopBits)
{
	if(m_bOpened)return TRUE;

	m_h_father_wnd=hWnd;
	m_u_message=Msg;

	CString szPortName;
	szPortName.Format("COM%d",nCom);

	try
	{
		//�򿪴���
		m_hCommPort = ::CreateFile(
			szPortName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			0,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED,
			0);
		if(m_hCommPort==INVALID_HANDLE_VALUE)
		{
			TRACE("open com port failed!\n");
			CloseAndCleanHandle(m_hCommPort);
			return FALSE;
		}
		TRACE("open com port success!\n");

		//���ù����¼�
		if(!::SetCommMask(m_hCommPort,EV_RXCHAR | EV_ERR))//| EV_TXEMPTY 
		{
			TRACE("setcommmask fail!\n");
			CloseAndCleanHandle(m_hCommPort);
			return FALSE;
		}
		TRACE("SetCommMask success!\n");

		//����DCB�ṹ
		DCB dcb;
		memset(&dcb,0,sizeof(DCB));
		
		if(!::GetCommState(m_hCommPort,&dcb))
		{
			TRACE("GetCommState(m_hCommPort,&dcb) failed!\n");
			CloseAndCleanHandle(m_hCommPort);
			return FALSE;
		}
		TRACE("GetCommState success!\n");
		
		dcb.BaudRate	= dwBaudRate;
		dcb.ByteSize	= byByteSize;
		dcb.Parity		= byParity;
		if(byStopBits==1)
		{
			dcb.StopBits = ONESTOPBIT;
		}
		else if(byStopBits==2)
		{
			dcb.StopBits = TWOSTOPBITS;
		}
		else
		{
			dcb.StopBits = ONE5STOPBITS;
		}
//*���ڲ����������ô�ã������Ȳ�д�ˣ�Ĭ�Ͼ�����
//		dcb.fDsrSensitivity = 0;
//		dcb.fDtrControl		= DTR_CONTROL_ENABLE;
//		dcb.fOutxDsrFlow	= 0;
//*/		
		if(!::SetCommState(m_hCommPort,&dcb))
		{
			TRACE("SetCommState(m_hCommPort,&dcb)) failed!\n");
			CloseAndCleanHandle(m_hCommPort);
			return FALSE;
		}
		TRACE("SetCommState success!\n");

		//���ó�ʱ,��׼�����¼��жϽ��յ������ַ������Գ�ʱ��������
		COMMTIMEOUTS timeouts;
		memset(&timeouts,0,sizeof(COMMTIMEOUTS));
		timeouts.ReadIntervalTimeout		= MAXDWORD;
		timeouts.ReadTotalTimeoutConstant	= 0;
		timeouts.ReadTotalTimeoutMultiplier	= 0;
		timeouts.WriteTotalTimeoutConstant	= 0;
		timeouts.WriteTotalTimeoutMultiplier= 0;

		if(!::SetCommTimeouts(m_hCommPort,&timeouts))
		{
			TRACE("SetCommTimeouts(m_hCommPort,&timeouts) failed!\n");
			CloseAndCleanHandle(m_hCommPort);
			return FALSE;
		}
		TRACE("SetCommTimeouts success!\n");

//		m_end_read_thread	= CreateEvent(0,true,0,0);	//�ֶ��ָ��ź�

		AfxBeginThread(ReadEventProc,(LPVOID)this);
		AfxBeginThread(AnalysisEventProc,(LPVOID)this);
		AfxBeginThread(ReadDataProc,(LPVOID)this);
		AfxBeginThread(SendDataProc,(LPVOID)this);

		//����������ȡ�����̣߳������̻߳����α�������
		//�˳�ʱ�����˳������¼��̣߳�Ȼ���¼������̣߳���������ݽ����߳�
		SetEvent(m_start_data_thread);	

		m_bOpened = TRUE;
	}
	catch(...)
	{
		ASSERT(0);
		CloseAndCleanHandle(m_hCommPort);
	}

	return TRUE;
}
/******************************************************************************
*���ܣ���ȡ�����߳�
*˵����	ÿ���յ�һ���ַ����������¼�����������̰߳ѽ��յ��ĵڸ��ַ���Ϣ����
		���͸���Ϣ�����̡߳�
*������lpParam������CSerial�������
*���أ�0
******************************************************************************/
UINT CSerial::ReadEventProc(LPVOID lpParam)
{
	CSerial * pSerial = (CSerial *)lpParam;

	bool bQuit=false;

	DWORD dwEventMask=0;

	//���յ���Ϣ�ص�
	OVERLAPPED ov;
	memset(&ov,0,sizeof(OVERLAPPED));
	ov.hEvent	= CreateEvent(0,true,0,0);

	//��ȡ�����¼����˳��߳��ź�
	HANDLE mask_handle[2];
	mask_handle[0] = pSerial->m_end_event_thread;
	mask_handle[1] = ov.hEvent;
	
	//�����û����Ϣ�ı�־��
	DWORD dwRet;
	BOOL  bRet;
	bool  bHasMessage  =false;
	bool  bMaskOverlapping = false;

	//������
	DWORD dwErrors=0;
	COMSTAT comstate;
	memset(&comstate,0,sizeof(COMSTAT));

	//�ȵȴ������ź�,���ݴ����߳������󣬾ͻ�֪ͨ�����¼���Ϣ�߳�����
	::WaitForSingleObject(pSerial->m_start_event_thread,INFINITE);
	TRACE("get event thread start!\n");

	//���ϵͳ������
	pSerial->ClearSysReadBufferContent();

	while(!bQuit)
	{
		dwEventMask=0;
		bRet=::WaitCommEvent(pSerial->m_hCommPort,&dwEventMask,&ov);
		if(bRet)	//���õõ�һ��������Ϣ
		{
			bHasMessage=true;
		}
		else		//û�еõ�������Ϣ,�����Ƿ��ڽ����ص�������
		{
			if(GetLastError()==ERROR_IO_PENDING)//���ڽ����ص�����...
			{
				bMaskOverlapping=true;//���ڽ����ص�����,ֱ�����������±ߵĴ������
//				TRACE("�Ѿ����뵽���ص�������errorcode=[%d][%d]\n",GetLastError(),dwEventMask);
			}
			else
			{
				TRACE("WaitCommEvent��������errorcode=[%d][%d]\n",GetLastError(),dwEventMask);
				continue;
			}
		}
		if(bMaskOverlapping)	//������ڽ��е�����,�͵ȴ�...
		{
			bMaskOverlapping=false;
			dwRet=::WaitForMultipleObjects(2,mask_handle,false,INFINITE);
			switch(dwRet-WAIT_OBJECT_0)
			{
			case 0://�˳��߳�
				{
					bQuit=true;
				}
				break;
			case 1://���յ���Ϣ
				{
					ResetEvent(ov.hEvent);//�ָ������¼��ź�
					bRet=::GetOverlappedResult(pSerial->m_hCommPort,&ov,&dwErrors,false);
					if(bRet)
					{
						bHasMessage=true;
					}
				}
				break;
			default://δ֪�ź�
				{
				}
				break;
			}
		}
		if(bHasMessage)//���գ��������Ϣ����
		{
			bHasMessage=false;
/*			dwEventMask=0;
			bRet=::GetCommMask(pSerial->m_hCommPort,&dwEventMask);
			if(!bRet)
			{
				ResetEvent(ov.hEvent);//�ָ������¼��ź�
				TRACE0("GetCommMask(pSerial->m_hCommPort,&dwEventMask)\n");
				continue;
			}
			//����ģ�ԭ�����ô��ˣ�GetCommMaskֻ��ȡ��SetCommMask���õ��¼���
*/
			//����Ϣ���������ҳɹ��õ�����Ϣ
			if(EV_ERR == (dwEventMask & EV_ERR) )				//��������˴��󣬾�ֻ�������
			{
				//���������ˣ�Ҫ�ܹ��ָ�����
				::ClearCommError(pSerial->m_hCommPort,&dwErrors,&comstate);
				TRACE("�����˴���\n");
			}
/*			else if(EV_TXEMPTY == (dwEventMask & EV_TXEMPTY) )	//��ɷ�����������
			{
				TRACE("���ݷ�����ϣ�\n");
				pSerial->NotifyWriteData();
			}
*/
			else if(EV_RXCHAR == (dwEventMask & EV_RXCHAR) )	//��ȡ����
			{
				static unsigned long l=0;
//				TRACE("�¼������߳̽��յ����ַ��������Ϣ��nIndex=[%ld]\n",l++);
				SetEvent(pSerial->m_event_come_event);
			}
		}
	}

	pSerial->CloseAndCleanHandle(ov.hEvent);

	TRACE("get event thread end!\n");
//AfxMessageBox("get event thread end!");
	//֪ͨ���������̹߳ر�
	SetEvent(pSerial->m_end_analysis_thread);
	SetEvent(pSerial->m_event_thread_end);
	return 0;
}
/******************************************************************************
*���ܣ������Ƿ�ɹ����յ�һ�����ݰ�
*˵����ÿ���յ�һ���ַ���������һ����Ϣ���͹��������������ַ����Ƿ�ʱ���ж��Ƿ�ɹ����յ�һ�����ݰ�
*������
*���أ�
******************************************************************************/
UINT CSerial::AnalysisEventProc(LPVOID lpParam)
{
	CSerial * pSerial = (CSerial *)lpParam;

	bool bQuit=false;

	//��ȡ�����¼����˳��߳��ź�
	HANDLE handle[2];
	handle[0] = pSerial->m_end_analysis_thread;
	handle[1] = pSerial->m_event_come_event;

	//����WaitForMultipleObjects����ֵ
	DWORD dwRet;

	//�����ж�֮ǰ�Ƿ��й��ַ���Ϣ�������ַ���Ϣ֮���Ƿ�ʱ
	bool bHasMessageBefore		 = false;

	::WaitForSingleObject(pSerial->m_start_analysis_thread,INFINITE);

	TRACE("analysis event thread start!\n");

	SetEvent(pSerial->m_start_event_thread);//���������¼��߳�

	while(!bQuit)
	{
//		bHasMessageBefore=false;//���±��Ѿ���ΪFALSE��
		dwRet=::WaitForMultipleObjects(2,handle,false,INFINITE);
		
		switch(dwRet-WAIT_OBJECT_0)
		{
		case 0://�˳�
			{
				bQuit=true;
			}
			continue;
		case 1://���ݵ���,������һ��ѭ��
			{
				TRACE0("һ�����ݰ��ĵ�һ���ַ����\n");
				ResetEvent(handle[1]);
				if(!bHasMessageBefore)bHasMessageBefore=true;
			}
			break;
		default:
			{
				ResetEvent(handle[0]);
				ResetEvent(handle[1]);
			}
			continue;
		}
		while(!bQuit && bHasMessageBefore )
		{
			dwRet=::WaitForMultipleObjects(2,handle,false,DATA_READ_TIMEOUT);
			if(dwRet==WAIT_TIMEOUT)//�ɹ����յ�һ�����ݰ�
			{
				if(bHasMessageBefore)
				{
					TRACE0("�����ؽ��յ���һ�����ݰ���֪ͨ���ݽ����߳̽��н��գ�\n");
					bHasMessageBefore=false;
					SetEvent(pSerial->m_data_come_event);//֪ͨ���ݽ����߳̽�������
				}
				continue;
			}
			switch(dwRet-WAIT_OBJECT_0)
			{
			case 0://�˳�
				{
					bQuit=true;
				}
				break;
			case 1://���ݵ���
				{
//					TRACE0("�¼������߳̽��յ���һ���ַ���\n");
					ResetEvent(handle[1]);
				}
				break;
			default://������
				{
					ResetEvent(handle[0]);
					ResetEvent(handle[1]);
				}
				break;
			}
		}
	}

	TRACE("analysis event thread end\n");
//AfxMessageBox("analysis event thread end");
	SetEvent(pSerial->m_end_data_thread);
	SetEvent(pSerial->m_analysis_thread_end);
	return 1;
}
/******************************************************************************
*���ܣ���ȡ�����߳�
*˵����	�ɹ��յ�һ�����ݰ�������̻߳�õ���Ϣ����ʼ��ȡ������ݰ�
		�ɹ���ȡһ�����ݺ󣬻�����ݷŵ�g_read_data_group�У�ͬʱ������߷���һ����Ϣ
		����Ϣ�ɵ����߳�ʼ��ʱ����.
*������lpParam������CSerial�������
*���أ�0
******************************************************************************/
UINT CSerial::ReadDataProc(LPVOID lpParam)
{
	CSerial * pSerial = (CSerial *)lpParam;

	bool bQuit=false;

	DWORD dwEventMask=0;

	//���յ��ص���Ϣ
	OVERLAPPED ov;
	memset(&ov,0,sizeof(OVERLAPPED));
	ov.hEvent	= CreateEvent(0,true,0,0);

	//��ȡ�����¼����˳��߳��ź�
	HANDLE event_handle[2];
	event_handle[0] = pSerial->m_end_data_thread;
	event_handle[1] = pSerial->m_data_come_event;
	HANDLE read_handle[2];
	read_handle[0] = pSerial->m_end_data_thread;
	read_handle[1] = ov.hEvent;

	//��Ҫ��ȡ���ֽ���
	BOOL  bRet;
	DWORD dwBytesWantRead;
	DWORD dwBytesRead;
	char  temp_buf[2*MAX_COMM_BUF_LEN];
	bool bReadOverlapping = false;
	bool bReadDataSuccess = false;

	//��֪��ϵͳ���������ﹲ�ж����ֽ�
	DWORD   dwErrors=0;//��Ҫ������������Ǹ���û��ʹ�����ķ���ֵ�����ǲ��������ķ���ֵ.
	COMSTAT comstate;
	memset(&comstate,0,sizeof(COMSTAT));

	//����WaitForMultipleObjects����ֵ
	DWORD dwRet;

	::WaitForSingleObject(pSerial->m_start_data_thread,INFINITE);

	TRACE("read data thread start\n");

	SetEvent(pSerial->m_start_analysis_thread);//���������߳�

	while(!bQuit)
	{
		dwRet=::WaitForMultipleObjects(2,event_handle,false,INFINITE);
		switch(dwRet-WAIT_OBJECT_0)
		{
		case 0://�˳�
			{
				bQuit=true;
			}
			break;
		case 1://���ݵ���
			{
				ResetEvent(event_handle[1]);//ÿ�ζ����Ȼָ��ź�
				//�õ��ܼ��ж����ֽ���ϵͳ���ջ�������
				bRet=::ClearCommError(pSerial->m_hCommPort,&dwErrors,&comstate);
				if(!bRet)
				{
					continue;//ʧ�ܾͶ�����
				}
				dwBytesWantRead=comstate.cbInQue;//�õ���ϵͳ���������й��ж����ֽڡ�
				bRet=::ReadFile(pSerial->m_hCommPort,temp_buf,dwBytesWantRead,&dwBytesRead,&ov);
				if(bRet)	//�ɹ���ȡ����
				{
					bReadDataSuccess=true;
				}
				else		//�����Ƿ�ʼ���ص�����?
				{
					if(GetLastError()==ERROR_IO_PENDING)
					{
						bReadOverlapping=true;
					}
					else//��������
					{
						TRACE("ReadFile(pSerial->m_hCommPort,temp_buf,dwBytesWantRead,&dwBytesRead,&ov);\n");
						continue;
					}
				}
				if(bReadOverlapping)
				{
					bReadOverlapping=false;
					dwRet=::WaitForMultipleObjects(2,read_handle,false,DATA_READ_TIMEOUT);
					if(dwRet==WAIT_TIMEOUT)
					{
						continue;//�����ȡ���ݳ�ʱ������Ϊ�Ǵ������ݣ�������
					}
					switch(dwRet-WAIT_OBJECT_0)
					{
					case 0://�˳�
						{
							bQuit=true;
						}
						break;
					case 1://�������ص��������
						{
//							ResetEvent(read_handle[1]);//�ָ���ȡ�����ź�
							//��Ҫ�ж��Ƿ�ɹ���ȡ������
							bRet=::GetOverlappedResult(pSerial->m_hCommPort,&ov,&dwBytesRead,false);
							if(!bRet)//���ص�����ʧ�ܣ�
							{
								TRACE0("���ص�����ʧ�ܣ�\n");
							}
							else
							{
								bReadDataSuccess=true;//�ɹ���ȡ������
							}
						}
						break;
					default:
						{
						}
						break;
					}
				}
				if(bReadDataSuccess)//����ɹ���ȡ������
				{
					bReadDataSuccess=false;//�ָ�״̬
					if(dwBytesWantRead==dwBytesRead)//���û���ٶ�ȡ�����ֽ�����������������ȷ��ȡ������
					{
						LPDATA lpdata=g_read_data_group.GetBlank();

						//�����ȡ���ֽ���������MAX_COMM_BUF_LEN-1,��ֻ�ܽ��յ�MAX_COMM_BUF_LEN-1���ֽ���
						lpdata->m_n_len=dwBytesRead>MAX_COMM_BUF_LEN-1?MAX_COMM_BUF_LEN-1:dwBytesRead;
						memcpy(lpdata->m_sz_buf,temp_buf,lpdata->m_n_len);
						lpdata->m_sz_buf[lpdata->m_n_len]=0;
						pSerial->NotifyReadData();

						TRACE("���ݽ����߳̽��յ���һ�����ݰ���len=[%d]\n",lpdata->m_n_len);
					}
					else
					{
						TRACE0("�ٶ�ȡ�����ֽ���\n");
					}
				}
				continue;//�ɹ���ȡ������
			}
			break;
		default:
			{
			}
			break;
		}	
	}
	pSerial->CloseAndCleanHandle(ov.hEvent);

	TRACE("read data thread end\n");
//	AfxMessageBox("read data thread end");
	SetEvent(pSerial->m_data_thread_end);

	return 2;
}
/******************************************************************************
*���ܣ�֪ͨ���ö����ɹ���ȡ��һ�����ݰ�
*˵����
*������
*���أ�
******************************************************************************/
void CSerial::NotifyReadData()
{
	::PostMessage(m_h_father_wnd,m_u_message,MSG_READ,0);
}
/******************************************************************************
*���ܣ�֪ͨ���ö����ɹ�������һ�����ݰ�
*˵����
*������
*���أ�
******************************************************************************/
void CSerial::NotifyWriteData(void*lpdata)
{
	::PostMessage(m_h_father_wnd,m_u_message,MSG_WRITE,(LPARAM)lpdata);
}

void CSerial::ClearSysReadBufferContent()
{
	int nRet;
	DWORD dwErrors=0;
	COMSTAT comstate;
	memset(&comstate,0,sizeof(COMSTAT));

	nRet=::ClearCommError(m_hCommPort,&dwErrors,&comstate);
	if(!nRet)return;
	
	char buf[4096];
	DWORD dwBytesRead;
	::ReadFile(m_hCommPort,buf,comstate.cbInQue,&dwBytesRead,NULL);

	TRACE("�Ѿ������ϵͳ���ջ�������len=[%ld]\n",comstate.cbInQue);

	//Ҳ���һ�±������ݵĻ�����
	g_read_data_group.PutToBlank();
	g_send_data_group.PutToBlank();
}

UINT CSerial::SendDataProc(LPVOID lpParam)
{
	CSerial * pSerial = (CSerial *)lpParam;

	//һЩ����ֵ
	BOOL  bRet;
	DWORD dwError=0;
	DWORD dwRet;

	//�ص��ṹ
	OVERLAPPED ov;
	memset(&ov,0,sizeof(OVERLAPPED));
	ov.hEvent=CreateEvent(0,true,0,0);

	HANDLE event_handle[2],handle[2];
	event_handle[0]=pSerial->m_end_send_thread;
	event_handle[1]=pSerial->m_send_data_event;
	handle[0]=pSerial->m_end_send_thread;
	handle[1]=ov.hEvent;

	//�������õ�
	COMSTAT comstate;
	memset(&comstate,0,sizeof(COMSTAT));

	//�Ƿ�ʼ���ص�������
	bool bWantToSendSomething=false;
	bool bHasOverlapped=false;
	bool bHasFinishedOverlapped=false;

	//һ��д�˶����ֽڣ�
	DWORD dwBytesWrite=0;

	bool bQuit=false;
	
	TRACE0("send data thread start!!!!!\n");

	while(!bQuit)
	{
		dwRet=::WaitForMultipleObjects(2,event_handle,false,INFINITE);
		switch(dwRet-WAIT_OBJECT_0)
		{
		case 0:
			{
				bQuit=true;
			}
			continue;
		case 1:
			{
				bWantToSendSomething=true;
			}
			break;
		default:
			{
			}
			continue;
		}
		if(!bWantToSendSomething)continue;
		bWantToSendSomething=false;
		//�õ�Ҫ���͵����ݽ��
		LPDATA lpdata=g_send_data_group.GetNext();
		
		//һֱ��������Ҫ���͵�����ȫ��������
		while(lpdata!=NULL)
		{
			bRet=::WriteFile(pSerial->m_hCommPort,lpdata->m_sz_buf,lpdata->m_n_len,&dwBytesWrite,&ov);
			
			if(!bRet)
			{
				if(GetLastError()==ERROR_IO_PENDING)
				{
					bHasOverlapped=true;
				}
				else//���������룬��������IO�������ᱻ����!
				{
					::ClearCommError(pSerial->m_hCommPort,&dwError,&comstate);
				}
			}
			if(bHasOverlapped)
			{
				bHasOverlapped=false;
				dwRet=::WaitForMultipleObjects(2,handle,false,INFINITE);
				switch(dwRet-WAIT_OBJECT_0)
				{
				case 0://�˳�
					{
						bQuit=true;
					}
					continue;
				case 1://���ݵ���
					{
						TRACE0("���������ص��������\n");
						bHasFinishedOverlapped=true;
					}
					break;
				default://������
					{
					}
					continue;
				}
			}
			if(bHasFinishedOverlapped)
			{
				bHasFinishedOverlapped=false;
				bRet=::GetOverlappedResult(pSerial->m_hCommPort,&ov,&dwBytesWrite,false);
				if(bRet)
				{
					TRACE("�ص�������ɣ�������[%d]�ֽ�����\n",dwBytesWrite);
					pSerial->NotifyWriteData(lpdata->m_sz_buf);
				}
				else
				{
					TRACE("û�еõ��ص����������\n");
				}
			}
			//��ȡû�з��͵�����
			lpdata=g_send_data_group.GetNext();
		}
		//�ָ��������ݵ��źţ��Ա��ٽ��շ������ݵ���Ϣ
		ResetEvent(event_handle[1]);
	}

	pSerial->CloseAndCleanHandle(ov.hEvent);
	TRACE0("send data thread end!\n");
	SetEvent(pSerial->m_send_thread_end);

	return 3;
}

bool CSerial::ReadData(char szData[], int &len)
{
	LPDATA lpdata=g_read_data_group.GetNext();
	if(lpdata==NULL)return false;
	
	len=len>lpdata->m_n_len+1?lpdata->m_n_len+1:len;
	memcpy(szData,lpdata->m_sz_buf,len);
	szData[len]=0;

	return true;
}

bool CSerial::SendData(char szData[], int len)
{
	LPDATA lpdata=g_send_data_group.GetBlank();

	lpdata->m_n_len=len;
	memcpy(lpdata->m_sz_buf,szData,len);
	lpdata->m_sz_buf[len]=0;

	SetEvent(m_send_data_event);
	return true;
}