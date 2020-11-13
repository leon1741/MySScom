#include "stdafx.h"
#include "MySScomTool.h"

/**************************************************************************************************
**  ��������:  GetChkSum_O
**  ��������:  �������ݵ�ԭ��ĵ��ֽ��ۼ�У���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
unsigned char GetChkSum_O(unsigned char *ptr, long len)
{
	int i;
	unsigned char result;

	result = 0;

	for (i = 0; i < len; i++) {
		result += *ptr++;
	}

	return result;
}

/**************************************************************************************************
**  ��������:  GetChkSum_N
**  ��������:  �������ݵķ���ĵ��ֽ��ۼ�У���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
unsigned char GetChkSum_N(unsigned char *ptr, long len)
{
	int i;
	unsigned char result;

	result = 0;

	for (i = 0; i < len; i++) {
		result += ~(*ptr++);
	}

	return result;
}

/**************************************************************************************************
**  ��������:  GetChkSum_Xor
**  ��������:  �������У���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
unsigned char GetChkSum_Xor(unsigned char *ptr, long len)
{
	unsigned char sum;

	sum = *ptr++;

	while (--len) {
		sum ^= *ptr++;
	}

	return sum;
}

/**************************************************************************************************
**  ��������:  AssembleByRules
**  ��������:  ����ʽ��װ����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
unsigned int AssembleByRules(unsigned char *dptr, unsigned char *sptr, int len, int maxlen, ASMRULE_T *rule)
{
	unsigned char temp;
	int  rlen;

	if (rule == 0) return 0;

	*dptr++ = rule->Flags0;
	rlen = 1;

	for (; len > 0; len--) {
		temp = *sptr++;
		if (temp == rule->Flags0) {
			if (rlen > (maxlen + 2)) return 0;
			*dptr++ = rule->Middle;
			*dptr++ = rule->Flags1;
			rlen += 2;
		} else if (temp == rule->Middle) {
			if (rlen > (maxlen + 2)) return 0;
			*dptr++ = rule->Middle;
			*dptr++ = rule->Flags2;
			rlen += 2;
		} else {
			if (rlen >= maxlen) return 0;
			*dptr++ = temp;
			rlen++;
		}
	}

	if (rlen >= maxlen) return 0;

	*dptr = rule->Flags0;
	rlen++;

	return rlen;
}

/**************************************************************************************************
**  ��������:  DeassembleByRules
**  ��������:  ����ʽ�������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
unsigned int DeassembleByRules(unsigned char *dptr, unsigned char *sptr, int len, int maxlen, ASMRULE_T *rule)
{
	int  rlen;
	unsigned char prechar, curchar, midchar;

	if (rule == 0) return 0;

	midchar = rule->Middle;
	rlen = 0;

	prechar = (~midchar);

	for (; len > 0; len--) {
		curchar = *sptr++;
		if (len >= maxlen) return 0;
		if (prechar == midchar) {
			if (curchar == rule->Flags1) {
				prechar = (~midchar);
				*dptr++ = rule->Flags0;
				rlen++;
			} else if (curchar == rule->Flags2) {
				prechar = (~midchar);
				*dptr++ = midchar;
				rlen++;
			} else {
				return 0;
			}
		} else {
			if ((prechar = curchar) != midchar) {
				*dptr++ = curchar;
				rlen++;
			}
		}
	}
	return rlen;
}

/**************************************************************************************************
**  ��������:  ConvertHexChar
**  ��������:  ��16��������ת��Ϊ�ַ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
unsigned char ConvertHexChar(unsigned char ch) 
{
	if ((ch >= '0') && (ch <= '9')) {
		return (ch - 0x30);
	} else if ((ch >= 'A') && (ch <= 'F')) {
		return (ch - 'A' + 10);
	} else if ((ch >= 'a') && (ch <= 'f')) {
		return (ch - 'a' + 10);
	} else {
		return (0);
	}
}

/**************************************************************************************************
**  ��������:  CharToHex
**  ��������:  ���ַ�ת��Ϊ16��������
**  �������:  
**  ���ز���:  
**************************************************************************************************/
CString CharToHex(CString InStr)
{
	CString TempStr;
	CString ResultStr = "";
	int len = InStr.GetLength();

	for (int i = 0; i < len; i++) {

		TempStr.Format(_T("%.2X"), InStr[i]);

		if (TempStr.GetLength() > 2) {
			TempStr = TempStr.Right(2);
		}		

		ResultStr = ResultStr + TempStr + " ";
	}

	return ResultStr;
}

/**************************************************************************************************
**  ��������:  HexToChar
**  ��������:  ��16��������ת��Ϊ�ַ���
**  �������:  
**  ���ز���:  
**************************************************************************************************/
CString HexToChar(CString InStr)
{
	CString TempStr;
	CString ResultStr = "";
	int len = InStr.GetLength();

	for (int i = 0; i < len; i++) {

		char TempSW = InStr[i++];
		char TempGW = InStr[i++];

		TempSW = ConvertHexChar(TempSW);
		TempGW = ConvertHexChar(TempGW);

		char TempChar = TempSW % 0x10 * 0x10 + TempGW % 0x10;

		ResultStr = ResultStr + TempChar;
	}

	return ResultStr;
}

/**************************************************************************************************
**  ��������:  String2Hex
**  ��������:  �ַ���ת��Ϊ16��������
**  �������:  
**  ���ز���:  
**  ע������:  �������ת�������ĸ�ʽ���ƣ��ڷ��Ϳ��е�ʮ�����ַ�Ӧ��ÿ�����ַ�֮�����һ���ո�
**************************************************************************************************/
int String2Hex(CString str, CByteArray &senddata)
{
	int hexdata, lowhexdata;
	int hexdatalen = 0;
	int len = str.GetLength();

	senddata.SetSize(len / 2);

	for (int i = 0; i < len; ) {

		char lstr, hstr = str[i];

		if (hstr == ' ') {
			i++;
			continue;
		}

		i++;

		if (i >= len) {
			break;
		}

		lstr       = str[i];
		hexdata    = ConvertHexChar(hstr);
		lowhexdata = ConvertHexChar(lstr);

		if ((hexdata == 16) || (lowhexdata == 16)) {
			break;
		} else {
			hexdata = hexdata * 16 + lowhexdata;
		}

		i++;
		senddata[hexdatalen] = (char)hexdata;
		hexdatalen++;
	}

	senddata.SetSize(hexdatalen);

	return hexdatalen;
}

/**************************************************************************************************
**  ��������:  ParseCharIsLegal
**  ��������:  �ж��ַ��Ƿ�Ϸ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool ParseCharIsLegal(unsigned char inchar)
{
	if ((inchar >= '0') && (inchar <= '9')) {
		return TRUE;
	} else if ((inchar >= 'a') && (inchar <= 'f')) {
		return TRUE;
	} else if ((inchar >= 'A') && (inchar <= 'F')) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/**************************************************************************************************
**  ��������:  ParseCStrisLegal
**  ��������:  �ж��ַ����Ƿ�Ϸ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool ParseCStrisLegal(CString str)
{
	int           i;
	unsigned char tchar;

	if (str.GetLength() == 0) {                                                /* �ַ�������Ϊ�� */
		return TRUE;
	}

	if (((str.GetLength() % 3) == 0) && (str.Right(1) != ' ')) {               /* ���һ���ַ�ֻ���ǿո񣬻��߲��� */
		return FALSE;
	}

	for (i = 0; i <= str.GetLength(); ) {                                      /* ��ѭ���������ж����������Ƿ�Ϸ� */

		if ((str.GetLength() % 3) == 1) {                                      /* ���ݳ��ȷǷ� */
			return FALSE;
		}

		tchar = str[i++];                                                      /* �жϵ�1���ַ��Ƿ���Ч */
		if (!ParseCharIsLegal(tchar)) {
			return FALSE;
		}

		tchar = str[i++];                                                      /* �жϵ�2���ַ��Ƿ���Ч */
		if (!ParseCharIsLegal(tchar)) {
			return FALSE;
		}

		if (i >= str.GetLength() - 1) {                                        /* ��������һ�����ݣ�����Ҫ�ж���ո� */
			return TRUE;
		}

		tchar = str[i++];                                                      /* �жϵ�3���ַ��Ƿ�Ϊ�ո� */
		if (tchar != ' ') {
			return FALSE;
		}
	}

	return TRUE;
}

/**************************************************************************************************
**  ��������:  ConvertHexChar
**  ��������:  ������0-F֮����ַ�����ת��Ϊ��Ӧ��ʮ�������ַ������򷵻�-1
**  �������:  
**  ���ز���:  
**************************************************************************************************/
char ConvertHexChar(char ch)
{
	if ((ch >= '0') && (ch <= '9')) {
		return (ch - 0x30);
	} else if ((ch >= 'A') && (ch <= 'F')) {
		return (ch - 'A' + 10);
	} else if ((ch >= 'a') && (ch <= 'f')) {
		return (ch - 'a' + 10);
	} else {
		return (-1);
	}
}

/**************************************************************************************************
**  ��������:  TransformtoHex
**  ��������:  �ַ���ת��Ϊ16����
**  �������:  
**  ���ز���:  
**************************************************************************************************/
CString TransformtoHex(CString InputStr)
{
	unsigned char temp1, temp2;
	CString TempCStr, ResultCStr;

	ResultCStr = "";

	for (int i = 0; i < InputStr.GetLength(); i++) {

		temp1 = InputStr[i];

		if (temp1 == 0xFF) {                                                   /* �յ���FF�ַ�������Ҫ���з�ת���ж� */

			temp2 = InputStr[i + 1];

			if (temp2 == 0x01) {                                               /* FF 01����ʾԭ�ַ�Ϊ00 */
				TempCStr.Format("%.2X ", 0x00);
				i++;
			} else if (temp2 == 0x02) {                                        /* FF 02����ʾԭ�ַ�ΪFF */
				TempCStr.Format("%.2X ", 0xFF);
				i++;
			} else {                                                           /* ������ϣ���ʾԭ�ַ�δ����ת�壬ֱ�Ӵ����� */
				TempCStr.Format("%.2X ", temp1);
			}
		} else {                                                               /* �����ַ�����ʾԭ�ַ�δ����ת�壬ֱ�Ӵ����� */
			TempCStr.Format("%.2X ", temp1);
		}

		TempCStr = TempCStr.Right(3);                                          /* ��ȡ�ұ���Чλ */
		ResultCStr += TempCStr;
	}

	return ResultCStr;
}

/**************************************************************************************************
**  ��������:  CharisValid
**  ��������:  �ж��ַ��Ƿ�Ϸ�
**  �������:  
**  ���ز���:  
**************************************************************************************************/
bool CharisValid(unsigned char inchar)
{
	if ((inchar >= '0') && (inchar <= '9')) {
		return TRUE;
	} else if ((inchar >= 'a') && (inchar <= 'f')) {
		return TRUE;
	} else if ((inchar >= 'A') && (inchar <= 'F')) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/**************************************************************************************************
**  ��������:  GetKeyValue
**  ��������:  ת��������ֵ
**  �������:  
**  ���ز���:  
**************************************************************************************************/
char GetKeyValue(unsigned int keyvalue)
{
	char result;

	if ((keyvalue >= 48) && (keyvalue <= 57)) {                                /* ����̵����ּ� */

		if (GetKeyState(VK_SHIFT) < 0) {                                       /* Shift����Ч */

			switch (keyvalue)
			{
			case 49:                                                       /* "!"�� */
				return '!';

			case 50:                                                       /* "@"�� */
				return '@';

			case 51:                                                       /* "#"�� */
				return '#';

			case 52:                                                       /* "$"�� */
				return '$';

			case 53:                                                       /* "%"�� */
				return '%';

			case 54:                                                       /* "^"�� */
				return '^';

			case 55:                                                       /* "&"�� */
				return '&';

			case 56:                                                       /* "*"�� */
				return '*';

			case 57:                                                       /* "("�� */
				return '(';

			case 48:                                                       /* ")"�� */
				return ')';
			}

		} else {                                                               /* Shift����Ч */
			return (keyvalue - 48 + '0');
		}
	}

	if ((keyvalue >= 96) && (keyvalue <= 105)) {                               /* С���̵����ּ� */
		return (keyvalue - 96 + '0');
	}

	if ((keyvalue >= 65) && (keyvalue <= 90)) {                                /* ��������ĸ�� */

		if (GetKeyState(VK_CAPITAL) > 0) {                                     /* ��д����Ч */
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* Shift����Ч */
				result = keyvalue - 65 + 'a';
			} else {                                                           /* Shift����Ч */
				result = keyvalue - 65 + 'A';
			}
		} else {                                                               /* ��д����Ч */
			if (::GetKeyState(VK_SHIFT) < 0) {                                 /* Shift����Ч */
				result = keyvalue - 65 + 'A';
			} else {                                                           /* Shift����Ч */
				result = keyvalue - 65 + 'a';
			}
		}

		return result;
	}

	switch (keyvalue)
	{
		case 13:                                                               /* �س����� */
			return 0x0D;

		case 32:                                                               /* �ո�� */
			return ' ';

		case 106:                                                              /* С����"*"�� */
			return '*';

		case 107:                                                              /* С����"+"�� */
			return '+';

		case 109:                                                              /* С����"-"�� */
			return '-';

		case 110:                                                              /* С����"."�� */
			return '.';

		case 111:                                                              /* С����"/"�� */
			return '/';

		case 186:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* ":"�� */
				return ':';
			} else {                                                           /* ";"�� */
				return ';';
			}
			break;

		case 187:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "+"�� */
				return '+';
			} else {                                                           /* "="�� */
				return '=';
			}
			break;

		case 188:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "<"�� */
				return '<';
			} else {                                                           /* ","�� */
				return ',';
			}
			break;

		case 189:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "_"�� */
				return '_';
			} else {                                                           /* "-"�� */
				return '-';
			}
			break;

		case 190:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* ">"�� */
				return '>';
			} else {                                                           /* "."�� */
				return '.';
			}
			break;

		case 191:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "?"�� */
				return '?';
			} else {                                                           /* "/"�� */
				return '/';
			}
			break;

		case 192:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "~"�� */
				return '~';
			} else {                                                           /* "`"�� */
				return '`';
			}
			break;

		case 219:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "{"�� */
				return '{';
			} else {                                                           /* "["�� */
				return '[';
			}
			break;

		case 220:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "|"�� */
				return '|';
			} else {                                                           /* "\"�� */
				return '\\';
			}
			break;

		case 221:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "}"�� */
				return '}';
			} else {                                                           /* "]"�� */
				return ']';
			}
			break;

		case 222:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* """�� */
				return '\"';
			} else {                                                           /* "'"�� */
				return '\'';
			}
			break;
	}

	return 0;
}

/**************************************************************************************************
**  ��������:  FormatQuotesStrRead
**  ��������:  ����ȡ�������ַ������и�ʽ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
CString FormatQuotesStrRead(CString tmpstr)
{
	int i, j;
	CString fmtstr;

	fmtstr = "";

	for (i = 0, j = 0; i < tmpstr.GetLength(); i++) {
		if ((tmpstr[i] == '\\') && (tmpstr[i + 1] == '"')) {
			fmtstr += '"';
			i++;
		} else {
			fmtstr += tmpstr[i];
		}
	}

	return fmtstr;
}

/**************************************************************************************************
**  ��������:  FormatQuotesStrWrite
**  ��������:  ��Ҫд����ַ������и�ʽ��
**  �������:  
**  ���ز���:  
**************************************************************************************************/
CString FormatQuotesStrWrite(CString tmpstr)
{
	int i, j;
	CString fmtstr;

	fmtstr = "";

	for (i = 0, j = 0; i < tmpstr.GetLength(); i++) {
		if (tmpstr[i] == '"') {
			fmtstr += '\\';
		}
		fmtstr += tmpstr[i];
	}

	return fmtstr;
}
