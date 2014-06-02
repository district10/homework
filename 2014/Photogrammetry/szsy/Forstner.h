#if !defined(AFX_FORSTNER_H__B7BFAEEC_E25F_4929_AC6D_9CF11E239322__INCLUDED_)
#define AFX_FORSTNER_H__B7BFAEEC_E25F_4929_AC6D_9CF11E239322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Forstner.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CForstner dialog

class CForstner : public CDialog
{
// Construction
public:
	CForstner(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CForstner)
	enum { IDD = IDD_DIALOG_Forstner };
	int		m_l1;

	int		m_l2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CForstner)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CForstner)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORSTNER_H__B7BFAEEC_E25F_4929_AC6D_9CF11E239322__INCLUDED_)
