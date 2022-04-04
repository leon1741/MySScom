#include "stdafx.h"
#include "afxinet.h"
#include "updatemanage.h"

/*************************************************************************************************/
/*                           ģ�龲̬��������                                                    */
/*************************************************************************************************/
static CWinThread           *s_UpdateHdle = NULL;                              /* ������̨���������̵߳ľ�� */
static CString               s_newver_info;                                    /* �������ϵ��³���汾ֵ */
static CString               s_update_link;                                    /* �������ϵ��������ӵ�ַ */

/**************************************************************************************************
**  ��������:  CompareVerData
**  ��������:  �Ƚ�2������汾�ŵĴ�С[ǰ�ߴ��򷵻�1��ǰ��С�򷵻�-1����������򷵻�0���ж��쳣�򷵻�-2]
**  ����˵��:  ����"x.y.z.t"�ĸ�ʽ������x/y/z/t��Ϊ���֣���֧�ֶ�λ
**************************************************************************************************/
static int CompareVerData(CString ver1, CString ver2)
{
	int pos_dot1, pos_dot2, pos_dot3;
	int ver1_array[4], ver2_array[4];
	CString tempstr;

	/* ��������ʵ�ֶ԰汾1�����ݽ��������ַ�������ȡ���������ݣ��洢����Ӧ�������� */

	pos_dot1 = ver1.Find(".", 0);
	pos_dot2 = ver1.Find(".", pos_dot1 + 1);
	pos_dot3 = ver1.Find(".", pos_dot2 + 1);

	if ((pos_dot1 == -1) || (pos_dot2 == -1) || (pos_dot3 == -1)) {
		tempstr.Format("�汾1(%s)��ʽ������Ҫ��", ver1);
		MessageBox(NULL, ver1, "��ʾ", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return -2;
	}

	ver1_array[3] = atoi(ver1.Left(pos_dot1));
	ver1_array[2] = atoi((ver1.Left(pos_dot2)).Right((ver1.Left(pos_dot2)).GetLength() - pos_dot1 - 1));
	ver1_array[1] = atoi((ver1.Left(pos_dot3)).Right((ver1.Left(pos_dot3)).GetLength() - pos_dot2 - 1));
	ver1_array[0] = atoi(ver1.Right(ver1.GetLength() - pos_dot3 - 1));

	/* ��������ʵ�ֶ԰汾2�����ݽ��������ַ�������ȡ���������ݣ��洢����Ӧ�������� */

	pos_dot1 = ver2.Find(".", 0);
	pos_dot2 = ver2.Find(".", pos_dot1 + 1);
	pos_dot3 = ver2.Find(".", pos_dot2 + 1);

	if ((pos_dot1 == -1) || (pos_dot2 == -1) || (pos_dot3 == -1)) {
		tempstr.Format("�汾2(%s)��ʽ������Ҫ��", ver2);
		MessageBox(NULL, ver1, "��ʾ", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return -2;
	}

	ver2_array[3] = atoi(ver2.Left(pos_dot1));
	ver2_array[2] = atoi((ver2.Left(pos_dot2)).Right((ver2.Left(pos_dot2)).GetLength() - pos_dot1 - 1));
	ver2_array[1] = atoi((ver2.Left(pos_dot3)).Right((ver2.Left(pos_dot3)).GetLength() - pos_dot2 - 1));
	ver2_array[0] = atoi(ver2.Right(ver2.GetLength() - pos_dot3 - 1));
	
	/* ��������ʵ�ֶ԰汾1�Ͱ汾2�����ݵıȽ� */

	if (ver1_array[3] > ver2_array[3]) {
		return 1;
	} else if (ver1_array[3] < ver2_array[3]) {
		return -1;
	} else {
		if (ver1_array[2] > ver2_array[2]) {
			return 1;
		} else if (ver1_array[2] < ver2_array[2]) {
			return -1;
		} else {
			if (ver1_array[1] > ver2_array[1]) {
				return 1;
			} else if (ver1_array[1] < ver2_array[1]) {
				return -1;
			} else {
				if (ver1_array[0] > ver2_array[0]) {
					return 1;
				} else if (ver1_array[0] < ver2_array[0]) {
					return -1;
				} else {
					return 0;
				}
			}
		}
	}
}

/**************************************************************************************************
**  ��������:  ParseUpdateFile
**  ��������:  ���������ļ�������
**************************************************************************************************/
static bool ParseUpdateFile(CString filestr)
{
	int pos_head_start, pos_head_end;
	int pos_tail_start, pos_tail_end;
	CString tempstr, versstr, linkstr;

	versstr = "<NewVerInfo>";
	linkstr = "<UpdateLink>";

	/* �������为��������°汾���ֶε���ϸ���� */

	tempstr = filestr;                                                         /* ������2�Σ��³���汾�� */

	pos_head_start = tempstr.Find(versstr, 0);
	if (pos_head_start == -1) {
		MessageBox(NULL, "û���ҵ�NewVerInfoͷ�겿��", "��ʾ", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	pos_head_end = pos_head_start + strlen(versstr);

	pos_tail_start = tempstr.Find(versstr, pos_head_end);
	if (pos_tail_start == -1) {
		MessageBox(NULL, "û���ҵ�NewVerInfoβ�겿��", "��ʾ", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	pos_tail_end = pos_tail_start + strlen(versstr);

	s_newver_info = tempstr.Left(pos_tail_start);
	s_newver_info = s_newver_info.Right(s_newver_info.GetLength() - pos_head_end);

	/* �������为����������ظ��µ�ַ���ӵ���ϸ���� */

	tempstr = filestr.Right(filestr.GetLength() - pos_tail_end);               /* ������2�Σ��������ӵ�ַ */

	pos_head_start = tempstr.Find(linkstr, 0);
	if (pos_head_start == -1) {
		MessageBox(NULL, "û���ҵ�UpdateLinkͷ�겿��", "��ʾ", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	pos_head_end = pos_head_start + strlen(linkstr);

	pos_tail_start = tempstr.Find(linkstr, pos_head_end);
	if (pos_tail_start == -1) {
		MessageBox(NULL, "û���ҵ�UpdateLinkβ�겿��", "��ʾ", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	pos_tail_end = pos_tail_start + strlen(linkstr);

	s_update_link = tempstr.Left(pos_tail_start);
	s_update_link = s_update_link.Right(s_update_link.GetLength() - pos_head_end);

	return true;
}

/**************************************************************************************************
**  ��������:  UpdateManageProc
**  ��������:  ��̨����������
**************************************************************************************************/
static UINT UpdateManageProc(LPVOID pParam)
{
	bool success = false;
	CInternetSession Session;
	CHttpFile *pfile{};
	DWORD dwStatusCode;
	CString tempstr, filestr;

	#if RELEASE_VERSION == 1
	Sleep(30 * 1000);
	#else
	Sleep(3 * 1000);
	#endif

	while (1) {

		success = false;

		pfile = (CHttpFile *)Session.OpenURL("https://gitee.com/leon1741/MySScom/raw/main/update/update.ini");

		if (pfile != NULL) {

			pfile->QueryInfoStatusCode(dwStatusCode);

			if (dwStatusCode == HTTP_STATUS_OK) {

				while (pfile->ReadString(tempstr) != NULL) {                   /* ������ȡ�ļ����ݣ����������� */
					filestr += tempstr;
				}
				
				if (ParseUpdateFile(filestr) == true) {                        /* ���ļ����ݽ��н�������ȡ��Ч��Ϣ */
					if (CompareVerData(s_newver_info, GetProgramVersion()) == 1) {
						success = true;
					}
				}
			}
		}

		Session.Close();
		pfile->Close();
		delete pfile;
		pfile = NULL;

		if (success == true) {                                                 /* �����ɹ������˳�������ѭ������ */
			break;
		}

		Sleep(30 * 60 * 1000);                                                 /* ���30���Ӽ��һ�� */
	}

	tempstr.Format("��⵽�°汾[V%s]�Ѿ��������Ƿ��Զ���ת�����ص�ַ��", s_newver_info);
	if (MessageBox(NULL, tempstr, "������ʾ", MB_SYSTEMMODAL | MB_YESNO | MB_ICONQUESTION) == IDYES) {
		ShellExecute(NULL, _T("open"), s_update_link, NULL, NULL, SW_SHOW);
	}

	s_UpdateHdle->SuspendThread();

	return 0;
}

/**************************************************************************************************
**  ��������:  CreateUpdateThread
**  ��������:  ������̨���������߳�
**************************************************************************************************/
bool CreateUpdateThread(void)
{
	s_UpdateHdle = AfxBeginThread(UpdateManageProc, NULL, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);

	if (s_UpdateHdle == NULL) {                                                /* ����̴߳���ʧ�� */
		return FALSE;
	} else {                                                                   /* ��ʼ�������� */
		s_UpdateHdle->ResumeThread();
		return TRUE;
	}
}

/**************************************************************************************************
**  ��������:  GetProgramVersion
**  ��������:  ��ȡ������İ汾��
**************************************************************************************************/
CString GetProgramVersion(void)
{
	TCHAR szFullPath[MAX_PATH];
	DWORD dwVerInfoSize = 0;
	DWORD dwVerHnd;
	VS_FIXEDFILEINFO * pFileInfo;
	HANDLE  hMem;
	LPVOID  lpvMem;
	unsigned int uInfoSize = 0;
	CString strVersion;
	WORD m_nProdVersion[4];

	GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
	dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);

	if (dwVerInfoSize) {

		hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
		lpvMem = GlobalLock(hMem);
		GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpvMem);

		::VerQueryValue(lpvMem, (LPTSTR)_T("\\"), (void**)&pFileInfo, &uInfoSize);

		m_nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS);
		m_nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
		m_nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
		m_nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS);

		strVersion.Format(_T("%d.%d.%d.%d"), m_nProdVersion[0], m_nProdVersion[1], m_nProdVersion[2], m_nProdVersion[3]);

		GlobalUnlock(hMem);
		GlobalFree(hMem);
	}

	return strVersion;
}
