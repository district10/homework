#if !defined(AFX_MORAVEC_H__BB434D89_2180_4775_8F28_3A5444D0AD1C__INCLUDED_)
#define AFX_MORAVEC_H__BB434D89_2180_4775_8F28_3A5444D0AD1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Moravec.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoravec dialog

class CMoravec : public CDialog
{
// Construction
public:
	CMoravec(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMoravec)
	enum { IDD = IDD_DIALOG_moravec };
	int		m_size;
	int		m_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoravec)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMoravec)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MORAVEC_H__BB434D89_2180_4775_8F28_3A5444D0AD1C__INCLUDED_)
