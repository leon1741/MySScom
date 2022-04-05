#include "stdafx.h"
#include "MySScomTool.h"

/**************************************************************************************************
**  函数名称:  GetChkSum_O
**  功能描述:  计算数据的原码的单字节累加校验和
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
**  函数名称:  GetChkSum_N
**  功能描述:  计算数据的反码的单字节累加校验和
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
**  函数名称:  GetChkSum_Xor
**  功能描述:  计算异或校验和
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
**  函数名称:  AssembleByRules
**  功能描述:  按格式封装数据
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
**  函数名称:  DeassembleByRules
**  功能描述:  按格式解封数据
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
**  函数名称:  ConvertHexChar
**  功能描述:  将16进制数据转换为字符
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
**  函数名称:  CharToHex
**  功能描述:  将字符转换为16进制数据
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
**  函数名称:  HexToChar
**  功能描述:  将16进制数组转换为字符串
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
**  函数名称:  String2Hex
**  功能描述:  字符串转换为16进制数据
**  注意事项:  由于这个转换函数的格式限制，在发送框中的十六制字符应该每两个字符之间插入一个空隔
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
**  函数名称:  ParseCharIsLegal
**  功能描述:  判断字符是否合法
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
**  函数名称:  ParseCStrisLegal
**  功能描述:  判断字符串是否合法
**************************************************************************************************/
bool ParseCStrisLegal(CString str)
{
	int           i;
	unsigned char tchar;

	if (str.GetLength() == 0) {                                                /* 字符串内容为空 */
		return TRUE;
	}

	if (((str.GetLength() % 3) == 0) && (str.Right(1) != ' ')) {               /* 最后一个字符只能是空格，或者不填 */
		return FALSE;
	}

	for (i = 0; i <= str.GetLength(); ) {                                      /* 本循环体用于判断数据内容是否合法 */

		if ((str.GetLength() % 3) == 1) {                                      /* 数据长度非法 */
			return FALSE;
		}

		tchar = str[i++];                                                      /* 判断第1个字符是否有效 */
		if (!ParseCharIsLegal(tchar)) {
			return FALSE;
		}

		tchar = str[i++];                                                      /* 判断第2个字符是否有效 */
		if (!ParseCharIsLegal(tchar)) {
			return FALSE;
		}

		if (i >= str.GetLength() - 1) {                                        /* 如果是最后一个数据，则不需要判断其空格 */
			return TRUE;
		}

		tchar = str[i++];                                                      /* 判断第3个字符是否为空格 */
		if (tchar != ' ') {
			return FALSE;
		}
	}

	return TRUE;
}

/**************************************************************************************************
**  函数名称:  ConvertHexChar
**  功能描述:  若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1
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
**  函数名称:  TransformtoHex
**  功能描述:  字符串转换为16进制
**************************************************************************************************/
CString TransformtoHex(CString InputStr)
{
	unsigned char temp1, temp2;
	CString TempCStr, ResultCStr;

	ResultCStr = "";

	for (int i = 0; i < InputStr.GetLength(); i++) {

		temp1 = InputStr[i];

		if (temp1 == 0xFF) {                                                   /* 收到了FF字符，则需要进行反转义判断 */

			temp2 = InputStr[i + 1];

			if (temp2 == 0x01) {                                               /* FF 01，表示原字符为00 */
				TempCStr.Format("%.2X ", 0x00);
				i++;
			} else if (temp2 == 0x02) {                                        /* FF 02，表示原字符为FF */
				TempCStr.Format("%.2X ", 0xFF);
				i++;
			} else {                                                           /* 其他组合，表示原字符未经过转义，直接处理即可 */
				TempCStr.Format("%.2X ", temp1);
			}
		} else {                                                               /* 其他字符，表示原字符未经过转义，直接处理即可 */
			TempCStr.Format("%.2X ", temp1);
		}

		TempCStr = TempCStr.Right(3);                                          /* 截取右边有效位 */
		ResultCStr += TempCStr;
	}

	return ResultCStr;
}

/**************************************************************************************************
**  函数名称:  CharisValid
**  功能描述:  判断字符是否合法
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
**  函数名称:  GetKeyValue
**  功能描述:  转换按键键值
**************************************************************************************************/
char GetKeyValue(unsigned int keyvalue)
{
	char result;

	if ((keyvalue >= 48) && (keyvalue <= 57)) {                                /* 大键盘的数字键 */

		if (GetKeyState(VK_SHIFT) < 0) {                                       /* Shift键有效 */

			switch (keyvalue)
			{
				case 49:                                                       /* "!"键 */
					return '!';

				case 50:                                                       /* "@"键 */
					return '@';

				case 51:                                                       /* "#"键 */
					return '#';

				case 52:                                                       /* "$"键 */
					return '$';

				case 53:                                                       /* "%"键 */
					return '%';

				case 54:                                                       /* "^"键 */
					return '^';

				case 55:                                                       /* "&"键 */
					return '&';

				case 56:                                                       /* "*"键 */
					return '*';

				case 57:                                                       /* "("键 */
					return '(';

				case 48:                                                       /* ")"键 */
					return ')';
			}

		} else {                                                               /* Shift键无效 */
			return (keyvalue - 48 + '0');
		}
	}

	if ((keyvalue >= 96) && (keyvalue <= 105)) {                               /* 小键盘的数字键 */
		return (keyvalue - 96 + '0');
	}

	if ((keyvalue >= 65) && (keyvalue <= 90)) {                                /* 按下了字母键 */

		if (GetKeyState(VK_CAPITAL) > 0) {                                     /* 大写键有效 */
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* Shift键有效 */
				result = keyvalue - 65 + 'a';
			} else {                                                           /* Shift键无效 */
				result = keyvalue - 65 + 'A';
			}
		} else {                                                               /* 大写键无效 */
			if (::GetKeyState(VK_SHIFT) < 0) {                                 /* Shift键有效 */
				result = keyvalue - 65 + 'A';
			} else {                                                           /* Shift键无效 */
				result = keyvalue - 65 + 'a';
			}
		}

		return result;
	}

	switch (keyvalue)
	{
		case 13:                                                               /* 回车键键 */
			return 0x0D;

		case 32:                                                               /* 空格键 */
			return ' ';

		case 106:                                                              /* 小键盘"*"键 */
			return '*';

		case 107:                                                              /* 小键盘"+"键 */
			return '+';

		case 109:                                                              /* 小键盘"-"键 */
			return '-';

		case 110:                                                              /* 小键盘"."键 */
			return '.';

		case 111:                                                              /* 小键盘"/"键 */
			return '/';

		case 186:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* ":"键 */
				return ':';
			} else {                                                           /* ";"键 */
				return ';';
			}
			break;

		case 187:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "+"键 */
				return '+';
			} else {                                                           /* "="键 */
				return '=';
			}
			break;

		case 188:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "<"键 */
				return '<';
			} else {                                                           /* ","键 */
				return ',';
			}
			break;

		case 189:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "_"键 */
				return '_';
			} else {                                                           /* "-"键 */
				return '-';
			}
			break;

		case 190:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* ">"键 */
				return '>';
			} else {                                                           /* "."键 */
				return '.';
			}
			break;

		case 191:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "?"键 */
				return '?';
			} else {                                                           /* "/"键 */
				return '/';
			}
			break;

		case 192:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "~"键 */
				return '~';
			} else {                                                           /* "`"键 */
				return '`';
			}
			break;

		case 219:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "{"键 */
				return '{';
			} else {                                                           /* "["键 */
				return '[';
			}
			break;

		case 220:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "|"键 */
				return '|';
			} else {                                                           /* "\"键 */
				return '\\';
			}
			break;

		case 221:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* "}"键 */
				return '}';
			} else {                                                           /* "]"键 */
				return ']';
			}
			break;

		case 222:
			if (GetKeyState(VK_SHIFT) < 0) {                                   /* """键 */
				return '\"';
			} else {                                                           /* "'"键 */
				return '\'';
			}
			break;
	}

	return 0;
}

/**************************************************************************************************
**  函数名称:  FormatQuotesStrRead
**  功能描述:  将读取出来的字符串进行格式化
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
**  函数名称:  FormatQuotesStrWrite
**  功能描述:  将要写入的字符串进行格式化 [主要是增加转义字符的处理，以免"字符丢失]
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

