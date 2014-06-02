// szsyDoc.cpp : implementation of the CSzsyDoc class
//

#include "stdafx.h"
#include "szsy.h"

#include "szsyDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSzsyDoc

IMPLEMENT_DYNCREATE(CSzsyDoc, CDocument)

BEGIN_MESSAGE_MAP(CSzsyDoc, CDocument)
	//{{AFX_MSG_MAP(CSzsyDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSzsyDoc construction/destruction

CSzsyDoc::CSzsyDoc()
{
	// TODO: add one-time construction code here

}

CSzsyDoc::~CSzsyDoc()
{
}




/////////////////////////////////////////////////////////////////////////////
// CSzsyDoc serialization

void CSzsyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSzsyDoc diagnostics

#ifdef _DEBUG
void CSzsyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSzsyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSzsyDoc commands

BOOL CSzsyDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	return m_bmpfile.Load4File(lpszPathName);
	// TODO: Add your specialized creation code here
	
	return TRUE;
}
