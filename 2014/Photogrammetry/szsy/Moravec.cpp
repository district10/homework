// Moravec.cpp : implementation file
//

#include "stdafx.h"
#include "szsy.h"
#include "Moravec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoravec dialog


CMoravec::CMoravec(CWnd* pParent /*=NULL*/)
	: CDialog(CMoravec::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMoravec)
	m_size = 0;
	m_value = 0;
	//}}AFX_DATA_INIT
}


void CMoravec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoravec)
	DDX_Text(pDX, IDC_EDIT_size, m_size);
	DDV_MinMaxInt(pDX, m_size, 0, 15);
	DDX_Text(pDX, IDC_EDIT_value, m_value);
	DDV_MinMaxInt(pDX, m_value, 0, 500000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoravec, CDialog)
	//{{AFX_MSG_MAP(CMoravec)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoravec message handlers
