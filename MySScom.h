// MySScom.h : main header file for the MYSSCOM application
//

#if !defined(AFX_MYSSCOM_H__2A7E1B92_2C43_4CF6_B2BC_290029D8F316__INCLUDED_)
#define AFX_MYSSCOM_H__2A7E1B92_2C43_4CF6_B2BC_290029D8F316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMySScomApp:
// See MySScom.cpp for the implementation of this class
//

class CMySScomApp : public CWinApp
{
public:
	CMySScomApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySScomApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMySScomApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSSCOM_H__2A7E1B92_2C43_4CF6_B2BC_290029D8F316__INCLUDED_)
