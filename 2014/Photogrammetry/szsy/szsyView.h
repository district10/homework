// szsyView.h : interface of the CSzsyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SZSYVIEW_H__CC2E79D1_AA5E_4358_BE83_72A3B0032CF7__INCLUDED_)
#define AFX_SZSYVIEW_H__CC2E79D1_AA5E_4358_BE83_72A3B0032CF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSzsyView : public CScrollView
{
protected: // create from serialization only
	CSzsyView();
	DECLARE_DYNCREATE(CSzsyView)

// Attributes
public:
	CSzsyDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSzsyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSzsyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSzsyView)
	afx_msg void OnMoravec();
	afx_msg void Onrgbtohui();
	afx_msg void OnForstner();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in szsyView.cpp
inline CSzsyDoc* CSzsyView::GetDocument()
   { return (CSzsyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SZSYVIEW_H__CC2E79D1_AA5E_4358_BE83_72A3B0032CF7__INCLUDED_)
