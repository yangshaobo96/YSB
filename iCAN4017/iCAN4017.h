// iCAN4017.h : main header file for the ICAN4017 application
//

#if !defined(AFX_ICAN4017_H__E9719400_172C_4182_99F7_57B93A1C4265__INCLUDED_)
#define AFX_ICAN4017_H__E9719400_172C_4182_99F7_57B93A1C4265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CICAN4017App:
// See iCAN4017.cpp for the implementation of this class
//

class CICAN4017App : public CWinApp
{
public:
	CICAN4017App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CICAN4017App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CICAN4017App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICAN4017_H__E9719400_172C_4182_99F7_57B93A1C4265__INCLUDED_)
