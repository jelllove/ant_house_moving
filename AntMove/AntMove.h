// AntMove.h : main header file for the ANTMOVE application
//

#if !defined(AFX_ANTMOVE_H__8690CCF3_379B_45E9_B896_A6D234575387__INCLUDED_)
#define AFX_ANTMOVE_H__8690CCF3_379B_45E9_B896_A6D234575387__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAntMoveApp:
// See AntMove.cpp for the implementation of this class
//

class CAntMoveApp : public CWinApp
{
public:
	CAntMoveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntMoveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAntMoveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTMOVE_H__8690CCF3_379B_45E9_B896_A6D234575387__INCLUDED_)
