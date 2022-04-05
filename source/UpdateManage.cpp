#include "stdafx.h"
#include "afxinet.h"
#include "updatemanage.h"

/*************************************************************************************************/
/*                           模块静态变量定义                                                    */
/*************************************************************************************************/
static CWinThread           *s_UpdateHdle = NULL;                              /* 监听后台升级管理线程的句柄 */
static CString               s_newver_info;                                    /* 服务器上的新程序版本值 */
static CString               s_update_link;                                    /* 服务器上的下载链接地址 */

/**************************************************************************************************
**  函数名称:  CompareVerData
**  功能描述:  比较2个程序版本号的大小[前者大则返回1，前者小则返回-1，两者相等则返回0，判断异常则返回-2]
**  特殊说明:  按照"x.y.z"的格式，其中x/y/z均为数字，可支持多位
**************************************************************************************************/
static int CompareVerData(CString ver1, CString ver2)
{
	int pos_dot1, pos_dot2;
	int ver1_array[3], ver2_array[3];
	CString tempstr;

	/* 下面的语句实现对版本1的内容解析，从字符串中提取出数字内容，存储到对应的数组中 */

	pos_dot1 = ver1.Find(".", 0);
	pos_dot2 = ver1.Find(".", pos_dot1 + 1);

	if ((pos_dot1 == -1) || (pos_dot2 == -1)) {
		tempstr.Format("版本1(%s)格式不符合要求", ver1);
		MessageBox(NULL, ver1, "提示", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return -2;
	}

	ver1_array[2] = atoi(ver1.Left(pos_dot1));
	ver1_array[1] = atoi((ver1.Left(pos_dot2)).Right((ver1.Left(pos_dot2)).GetLength() - pos_dot1 - 1));
	ver1_array[0] = atoi(ver1.Right(ver1.GetLength() - pos_dot2 - 1));

	/* 下面的语句实现对版本2的内容解析，从字符串中提取出数字内容，存储到对应的数组中 */

	pos_dot1 = ver2.Find(".", 0);
	pos_dot2 = ver2.Find(".", pos_dot1 + 1);

	if ((pos_dot1 == -1) || (pos_dot2 == -1)) {
		tempstr.Format("版本2(%s)格式不符合要求", ver2);
		MessageBox(NULL, ver1, "提示", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return -2;
	}

	ver2_array[2] = atoi(ver2.Left(pos_dot1));
	ver2_array[1] = atoi((ver2.Left(pos_dot2)).Right((ver2.Left(pos_dot2)).GetLength() - pos_dot1 - 1));
	ver2_array[0] = atoi(ver2.Right(ver2.GetLength() - pos_dot2 - 1));
	
	/* 下面的语句实现对版本1和版本2的内容的比较 */

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

/**************************************************************************************************
**  函数名称:  ParseUpdateFile
**  功能描述:  解析升级文件的内容
**************************************************************************************************/
static bool ParseUpdateFile(CString filestr)
{
	int pos_head_start, pos_head_end;
	int pos_tail_start, pos_tail_end;
	CString tempstr;

	/* 下面的语句负责解析出新版本号字段的详细内容 */

	tempstr = filestr;                                                         /* 解析第2段：新程序版本号 */

	pos_head_start = tempstr.Find(UPDCTRL_HEAD_FLAG, 0);
	if (pos_head_start == -1) {
		MessageBox(NULL, "没有找到NewVerInfo头标部分", "提示", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	pos_head_end = pos_head_start + strlen(UPDCTRL_HEAD_FLAG);

	pos_tail_start = tempstr.Find(UPDCTRL_HEAD_FLAG, pos_head_end);
	if (pos_tail_start == -1) {
		MessageBox(NULL, "没有找到NewVerInfo尾标部分", "提示", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	pos_tail_end = pos_tail_start + strlen(UPDCTRL_HEAD_FLAG);

	s_newver_info = tempstr.Left(pos_tail_start);
	s_newver_info = s_newver_info.Right(s_newver_info.GetLength() - pos_head_end);

	/* 下面的语句负责解析出下载更新地址链接的详细内容 */

	tempstr = filestr.Right(filestr.GetLength() - pos_tail_end);               /* 解析第2段：下载链接地址 */

	pos_head_start = tempstr.Find(UPDCTRL_TAIL_FLAG, 0);
	if (pos_head_start == -1) {
		MessageBox(NULL, "没有找到UpdateLink头标部分", "提示", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	pos_head_end = pos_head_start + strlen(UPDCTRL_TAIL_FLAG);

	pos_tail_start = tempstr.Find(UPDCTRL_TAIL_FLAG, pos_head_end);
	if (pos_tail_start == -1) {
		MessageBox(NULL, "没有找到UpdateLink尾标部分", "提示", MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	pos_tail_end = pos_tail_start + strlen(UPDCTRL_TAIL_FLAG);

	s_update_link = tempstr.Left(pos_tail_start);
	s_update_link = s_update_link.Right(s_update_link.GetLength() - pos_head_end);

	return true;
}

/**************************************************************************************************
**  函数名称:  UpdateManageProc
**  功能描述:  后台升级管理函数
**************************************************************************************************/
static UINT UpdateManageProc(LPVOID pParam)
{
	bool success = false;
	CInternetSession Session;
	CHttpFile *pfile{};
	DWORD dwStatusCode;
	CString tempstr, filestr;

	#if RELEASE_VERSION == 1                                                   /* 先延时一段，以免影响用户其他操作 */
	Sleep(30 * 1000);
	#else
	Sleep(3 * 1000);
	#endif

	while (1) {

		success = false;

		pfile = (CHttpFile *)Session.OpenURL(UPDCTRL_FILE_PATH);               /* 打开网址链接的文件 */

		if (pfile != NULL) {

			pfile->QueryInfoStatusCode(dwStatusCode);

			if (dwStatusCode == HTTP_STATUS_OK) {

				while (pfile->ReadString(tempstr) != NULL) {                   /* 反复读取文件内容，保存至本地 */
					filestr += tempstr;
				}
				
				if (ParseUpdateFile(filestr) == true) {                        /* 对文件内容进行解析，获取有效信息 */
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

		if (success == true) {                                                 /* 解析成功，则退出。否则循环处理 */
			break;
		}

		Sleep(30 * 60 * 1000);                                                 /* 间隔30分钟检测一次 */
	}

	tempstr.Format("检测到新版本[V%s]已经发布，是否自动跳转至下载地址？\r\n下载地址如果无法打开，请尝试反复刷新几次\r\n可能会被系统或杀毒软件误报为病毒，请放心使用", s_newver_info);
	if (MessageBox(NULL, tempstr, "友情提示", MB_SYSTEMMODAL | MB_YESNO | MB_ICONQUESTION) == IDYES) {
		ShellExecute(NULL, _T("open"), s_update_link, NULL, NULL, SW_SHOW);
	}

	s_UpdateHdle->SuspendThread();

	return 0;
}

/**************************************************************************************************
**  函数名称:  CreateUpdateThread
**  功能描述:  创建后台升级管理线程
**************************************************************************************************/
bool CreateUpdateThread(void)
{
	s_UpdateHdle = AfxBeginThread(UpdateManageProc, NULL, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);

	if (s_UpdateHdle == NULL) {                                                /* 如果线程创建失败 */
		return FALSE;
	} else {                                                                   /* 开始正常工作 */
		s_UpdateHdle->ResumeThread();
		return TRUE;
	}
}

/**************************************************************************************************
**  函数名称:  GetProgramVersion
**  功能描述:  获取本程序的版本号
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
	WORD m_nProdVersion[3];

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

		strVersion.Format(_T("%d.%d.%d"), m_nProdVersion[0], m_nProdVersion[1], m_nProdVersion[2]);

		GlobalUnlock(hMem);
		GlobalFree(hMem);
	}

	return strVersion;
}
