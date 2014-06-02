// Forstner.cpp : implementation file
//

#include "stdafx.h"
#include "szsy.h"
#include "Forstner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CForstner dialog


CForstner::CForstner(CWnd* pParent /*=NULL*/)
	: CDialog(CForstner::IDD, pParent)
{
	//{{AFX_DATA_INIT(CForstner)
	m_l1 = 0;
	m_l2 = 0;
	//}}AFX_DATA_INIT
}


void CForstner::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CForstner)
	DDX_Text(pDX, IDC_EDIT_l1, m_l1);
	DDV_MinMaxInt(pDX, m_l1, 0, 200);
	DDX_Text(pDX, IDC_EDIT_l2, m_l2);
	DDV_MinMaxInt(pDX, m_l2, 0, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CForstner, CDialog)
	//{{AFX_MSG_MAP(CForstner)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CForstner message handlers
