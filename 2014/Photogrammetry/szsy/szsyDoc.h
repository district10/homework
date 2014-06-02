// szsyDoc.h : interface of the CSzsyDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SZSYDOC_H__371F11C9_9883_4E63_8608_95BA38CCB1FB__INCLUDED_)
#define AFX_SZSYDOC_H__371F11C9_9883_4E63_8608_95BA38CCB1FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BmpFile.h"


class CSzsyDoc : public CDocument
{
protected: // create from serialization only
	CSzsyDoc();
	DECLARE_DYNCREATE(CSzsyDoc)

// Attributes
public:
public: CBmpFile m_bmpfile;   


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSzsyDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSzsyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSzsyDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SZSYDOC_H__371F11C9_9883_4E63_8608_95BA38CCB1FB__INCLUDED_)
