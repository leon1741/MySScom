#pragma once

#include "stdafx.h"

typedef struct {
	unsigned char   Flags0;                                          /* Flags0 = Middle + Flags1 */
	unsigned char   Middle;                                          /* Middle = Middle + Flags2 */
	unsigned char   Flags1;
	unsigned char   Flags2;
} ASMRULE_T;

unsigned char GetChkSum_O(unsigned char *ptr, long len);
unsigned char GetChkSum_N(unsigned char *ptr, long len);
unsigned char GetChkSum_Xor(unsigned char *ptr, long len);

unsigned int  AssembleByRules(unsigned char *dptr, unsigned char *sptr, int len, int maxlen, ASMRULE_T *rule);
unsigned int  DeassembleByRules(unsigned char *dptr, unsigned char *sptr, int len, int maxlen, ASMRULE_T *rule);

unsigned char ConvertHexChar(unsigned char ch);
CString       CharToHex(CString InStr);
CString       HexToChar(CString InStr);
bool          ParseCharIsLegal(unsigned char inchar);
bool          ParseCStrisLegal(CString str);

char    ConvertHexChar(char ch);
int     String2Hex(CString str, CByteArray &senddata);
CString TransformtoHex(CString InputStr);
bool    CharisValid(unsigned char inchar);
char    GetKeyValue(unsigned int keyvalue);

CString FormatQuotesStrRead(CString tmpstr);
CString FormatQuotesStrWrite(CString tmpstr);
