// szsy.h : main header file for the SZSY application
//

#if !defined(AFX_SZSY_H__D659026D_D466_4E6F_BFD9_128D8B939D16__INCLUDED_)
#define AFX_SZSY_H__D659026D_D466_4E6F_BFD9_128D8B939D16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSzsyApp:
// See szsy.cpp for the implementation of this class
//

class CSzsyApp : public CWinApp
{
public:
	CSzsyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSzsyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSzsyApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SZSY_H__D659026D_D466_4E6F_BFD9_128D8B939D16__INCLUDED_)
