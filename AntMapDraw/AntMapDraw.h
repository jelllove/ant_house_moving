// AntMapDraw.h : main header file for the ANTMAPDRAW application
//

#if !defined(AFX_ANTMAPDRAW_H__A03735B4_5D7D_4E11_BE04_2ED1101FACD6__INCLUDED_)
#define AFX_ANTMAPDRAW_H__A03735B4_5D7D_4E11_BE04_2ED1101FACD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAntMapDrawApp:
// See AntMapDraw.cpp for the implementation of this class
//

class CAntMapDrawApp : public CWinApp
{
public:
	CAntMapDrawApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntMapDrawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAntMapDrawApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTMAPDRAW_H__A03735B4_5D7D_4E11_BE04_2ED1101FACD6__INCLUDED_)
