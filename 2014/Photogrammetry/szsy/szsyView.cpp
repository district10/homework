// szsyView.cpp : implementation of the CSzsyView class
//

#include "stdafx.h"
#include "szsy.h"
#include "Moravec.h"
#include "szsyDoc.h"
#include "szsyView.h"
#include "BmpFile.h"
#include "math.h"
#include "Forstner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSzsyView

IMPLEMENT_DYNCREATE(CSzsyView, CScrollView)

BEGIN_MESSAGE_MAP(CSzsyView, CScrollView)
//{{AFX_MSG_MAP(CSzsyView)
ON_COMMAND(ID_Moravec, OnMoravec)
ON_COMMAND(ID_rgbtohui, Onrgbtohui)
ON_COMMAND(ID_Forstner, OnForstner)
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSzsyView construction/destruction

CSzsyView::CSzsyView()
{
	// TODO: add construction code here
	
}

CSzsyView::~CSzsyView()
{
}

BOOL CSzsyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSzsyView drawing

void CSzsyView::OnDraw(CDC* pDC)
{
	CSzsyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_bmpfile.Draw2DC(pDC->m_hDC,0,0);
	// TODO: add draw code for native data here
}

void CSzsyView::OnInitialUpdate()
{   CSzsyDoc* pDoc = GetDocument();
CScrollView::OnInitialUpdate();
CSize sizeTotal;
sizeTotal.cx = pDoc->m_bmpfile.m_Cols;
sizeTotal.cy = pDoc->m_bmpfile.m_Rows;
SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CSzsyView printing

BOOL CSzsyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSzsyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSzsyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSzsyView diagnostics

#ifdef _DEBUG
void CSzsyView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSzsyView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSzsyDoc* CSzsyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSzsyDoc)));
	return (CSzsyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSzsyView message handlers



void CSzsyView::OnMoravec() 
{
	CSzsyDoc*pDoc=GetDocument();
	CMoravec dlg;
	dlg.DoModal();
	int cols=pDoc->m_bmpfile.m_Cols;
	int rows=pDoc->m_bmpfile.m_Rows;
	int s=dlg.m_size;
	int interesvalue=dlg.m_value;
	int *p;//开辟空间用来存储兴趣值
	int i;
	p= new int [cols*rows];
	for ( i=0;i<cols*rows;i++)
	{	
		p[i]=0;
	}
	//计算各方向分量的v
	
	for ( int r=int(s/2);r<rows-int(s/2);r++){  
		for(int c=int(s/2);c<cols-int(s/2);c++)
		{   
			int v[4]={0,0,0,0};
			int k;
			for (k=-(int(s/2));k<int(s/2)-1;k++)
			{
				v[0]+=(pDoc->m_bmpfile.m_pImgDat[r*cols+c+k]-pDoc->m_bmpfile.m_pImgDat[r*cols+c+k+1])*(pDoc->m_bmpfile.m_pImgDat[r*cols+c+k]-pDoc->m_bmpfile.m_pImgDat[r*cols+c+k+1]);
				v[1]+=(pDoc->m_bmpfile.m_pImgDat[(r+k)*cols+c+k]-pDoc->m_bmpfile.m_pImgDat[(r+k+1)*cols+c+k+1])*(pDoc->m_bmpfile.m_pImgDat[(r+k)*cols+c+k]-pDoc->m_bmpfile.m_pImgDat[(r+k+1)*cols+c+k+1]);
				v[2]+=(pDoc->m_bmpfile.m_pImgDat[(r+k)*cols+c]-pDoc->m_bmpfile.m_pImgDat[(r+k+1)*cols+c])*(pDoc->m_bmpfile.m_pImgDat[(r+k)*cols+c]-pDoc->m_bmpfile.m_pImgDat[(r+k+1)*cols+c]);
				v[3]+=(pDoc->m_bmpfile.m_pImgDat[(r-k)*cols+c+k]-pDoc->m_bmpfile.m_pImgDat[(r-k-1)*cols+c+k+1])*(pDoc->m_bmpfile.m_pImgDat[(r-k)*cols+c+k]-pDoc->m_bmpfile.m_pImgDat[(r-k-1)*cols+c+k+1]);
			}
			p[r*cols+c]=min(min(v[0],v[1]),min(v[2],v[3])); 			
		}
	}
	
	int mx=0;
	int maxsize=30;
	//抑制局部最大，
	for (r=int(maxsize/2);r<rows-int(maxsize/2);r=r+maxsize)
	{   
		for( int c=int(maxsize/2);c<cols-int(maxsize/2);c=c+maxsize)
		{   
			int maxvalue=0;
			for(int m=0;m<maxsize+1;m++){
				for(int n=0;n<maxsize+1;n++)//选取最大值
				{	   				
					if (p[(r+m-int(maxsize/2))*cols+c+n-int(maxsize/2)]>maxvalue)
					{ 
						maxvalue=p[(r+m-int(maxsize/2))*cols+c+n-int(maxsize/2)];
						mx=(r+m-int(maxsize/2))*cols+c+n-int(maxsize/2);
					}
					
				}
			}
			if (p[mx]>interesvalue)
			{   
				for (int q=-5;q<5;q++)
				{
					pDoc->m_bmpfile.m_pImgDat[mx+q]=255;
					pDoc->m_bmpfile.m_pImgDat[mx+q*cols]=255;
				}
				
			}
			
		}
	}
	Invalidate();
}

void CSzsyView::Onrgbtohui() 
{
	CSzsyDoc* pDoc = GetDocument();
	double R,G,B,I;
	CBmpFile bmpFile;
	int cols=pDoc->m_bmpfile.m_Cols;
	int rows=pDoc->m_bmpfile.m_Rows;
	bmpFile.CreateBmp(cols,rows,1);
	for (int r=0;r<rows;r++){
		for (int c=0;c<cols;c++){
			R=pDoc->m_bmpfile.m_pImgDat[(r*cols+c)*3+0];
			G=pDoc->m_bmpfile.m_pImgDat[(r*cols+c)*3+1];
			B=pDoc->m_bmpfile.m_pImgDat[(r*cols+c)*3+2];//获取grb三个分量的值
			I=(R+G+B)/3;//rgb转化为灰度
			if(I<0) I=0;
			if(I>255) I=255;
			bmpFile.m_pImgDat[r*cols+c+0] =(BYTE)I;
		}
	}
	pDoc->m_bmpfile = bmpFile;
	
	Invalidate();
	
}


void CSzsyView::OnForstner() 
{
	CSzsyDoc*pDoc=GetDocument();
	CForstner dlg;
    dlg.DoModal();
	int cols=pDoc->m_bmpfile.m_Cols;
	int rows=pDoc->m_bmpfile.m_Rows;
    int l1=dlg.m_l1;

	int maxsize=dlg.m_l2;
	int *q,*w;//开辟空间用来存储权和圆度
	int i;
	q= new int [cols*rows];
	w= new int [cols*rows];
	for ( i=0;i<cols*rows;i++)
	{	
		q[i]=0;
		w[i]=0;
	}
   	for ( int r=int(l1/2);r<rows-int(l1/2);r++){  
		for(int c=int(l1/2);c<cols-int(l1/2);c++)
		{  int v[3]={0,0,0};
		int m,n;
		m=0;n=0;
		
		for (m=c-(int(l1/2));m<c+int(l1/2)-1;m++){
			for (n=r-(int(l1/2));n<r+int(l1/2)-1;n++){
				v[0]+=(pDoc->m_bmpfile.m_pImgDat[(n+1)*cols+m+1]-pDoc->m_bmpfile.m_pImgDat[n*cols+m])*(pDoc->m_bmpfile.m_pImgDat[(n+1)*cols+m+1]-pDoc->m_bmpfile.m_pImgDat[n*cols+m]);
				v[1]+=(pDoc->m_bmpfile.m_pImgDat[(n+1)*cols+m]-pDoc->m_bmpfile.m_pImgDat[n*cols+m+1])*(pDoc->m_bmpfile.m_pImgDat[(n+1)*cols+m]-pDoc->m_bmpfile.m_pImgDat[n*cols+m+1]);
				v[2]+=(pDoc->m_bmpfile.m_pImgDat[(n+1)*cols+m+1]-pDoc->m_bmpfile.m_pImgDat[n*cols+m])*(pDoc->m_bmpfile.m_pImgDat[(n+1)*cols+m]-pDoc->m_bmpfile.m_pImgDat[n*cols+m+1]);
				
			}//统计协方差矩阵的各个值
		}
		if (v[0]==0&&v[1]==0)
		{
			q[r*cols+c]=0;
			w[r*cols+c]=0;
		}
		else{
			q[r*cols+c]=(v[0]*v[1]-v[2]*v[2])/(v[0]+v[1]);
			w[r*cols+c]=4*(v[0]*v[1]-v[2]*v[2])/(v[0]+v[1]);//算出每个点的q,w，赋予开辟的空间
		}
		}
	}
		int mx=0;
		int averagew=0;
		int sum=0;
		for ( r=0;r<rows-int(l1/2);r++){  
			for(int c=0;c<cols-int(l1/2);c++)
			{
				sum+=w[r*cols+c];
			}
		}
		int maxvalue=sum/(rows-(int(l1/2)))*(cols-(int(l1/2)));
		//抑制局部最大，
		for (r=int(maxsize/2);r<rows-int(maxsize/2);r=r+maxsize)
		{   
			for( int c=int(maxsize/2);c<cols-int(maxsize/2);c=c+maxsize)
			{   
				int maxvalue=0;
				for(int m=0;m<maxsize;m++){
					for(int n=0;n<maxsize;n++)//选取最大值
					{	   				
						if (w[(r+m-int(maxsize/2))*cols+c+n-int(maxsize/2)]>maxvalue)
						{ 
							maxvalue=w[(r+m-int(maxsize/2))*cols+c+n-int(maxsize/2)];
							mx=(r+m-int(maxsize/2))*cols+c+n-int(maxsize/2);
						}
						
					}
			}
				if (w[mx]>0.9*averagew&&q[mx]>0.75)//与阈值相比较
				{   for (int q=-5;q<5;q++)
				{
					pDoc->m_bmpfile.m_pImgDat[mx+q]=255;
					pDoc->m_bmpfile.m_pImgDat[mx+q*cols]=255;
				}
				
				}
				
				
			}
		}
		
	
	Invalidate();
}
