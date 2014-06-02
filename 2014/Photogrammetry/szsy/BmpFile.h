/*----------------------------------------------------------------------+
|		BmpFile											 				|
|       Author:     DuanYanSong  2011/05/14								|
|            Ver 1.0													|
|       Copyright (c)2011, WHU RSGIS DPGrid Group						|
|	         All rights reserved.                                       |
|		ysduan@sohu.com													|
+----------------------------------------------------------------------*/
#ifndef BMPFILE_H_DUANYANSONG_2011_05_14_10_38_345678976543
#define BMPFILE_H_DUANYANSONG_2011_05_14_10_38_345678976543

class CBmpFile
{
public:
    CBmpFile(){	m_pImgDat=NULL; m_Cols=m_Rows=m_PxlBytes =0;
			    m_pBmpInfo   = new BYTE[ sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256 ];
				memset( m_pBmpInfo,0,sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256 );
				RGBQUAD *pColorTab = (RGBQUAD *)(m_pBmpInfo+sizeof(BITMAPINFOHEADER));
				for( int i=0;i<256;i++ ){ pColorTab[i].rgbRed=pColorTab[i].rgbGreen=pColorTab[i].rgbBlue=i;} 
			}
    virtual ~CBmpFile(){ if (m_pImgDat) delete []m_pImgDat; m_pImgDat=NULL; if( m_pBmpInfo ) delete []m_pBmpInfo; m_pBmpInfo=NULL; };
	BYTE*   operator[](int nIndex){ return (m_pImgDat+nIndex*m_Cols); };
	const	CBmpFile& operator=(CBmpFile& bmpFile){
				CreateBmp( bmpFile.m_Cols,bmpFile.m_Rows,bmpFile.m_PxlBytes);
				memcpy( m_pImgDat,bmpFile.m_pImgDat,m_Cols*m_Rows*m_PxlBytes );
				memcpy( m_pBmpInfo,bmpFile.m_pBmpInfo,sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256 );
				return (*this); 
			};
	
	BOOL	CreateBmp(int cols,int rows,int pixelPytes){
				if (m_pImgDat) delete []m_pImgDat;
				m_pImgDat = new BYTE[cols*rows*pixelPytes];
				memset( m_pImgDat,0,cols*rows*pixelPytes );
				m_Cols=cols; m_Rows=rows; m_PxlBytes =pixelPytes;
				return TRUE;
			};
    BOOL    Load4File( LPCSTR lpstrPathName ){
                BITMAPFILEHEADER  bmFileHdr; BITMAPINFOHEADER bmInfoHdr; DWORD rw;
                HANDLE hFile = ::CreateFile( lpstrPathName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL );
                if ( hFile == INVALID_HANDLE_VALUE ) return FALSE;
                ::ReadFile( hFile,&bmFileHdr,sizeof(bmFileHdr),&rw,NULL );
                if ( bmFileHdr.bfType != ((WORD)('M'<<8)|'B') ){ ::CloseHandle(hFile); return FALSE; }
                ::ReadFile( hFile,&bmInfoHdr ,sizeof(bmInfoHdr ),&rw,NULL );
                if ( (bmInfoHdr.biBitCount!=8)&&(bmInfoHdr.biBitCount!=24) ){ ::CloseHandle(hFile); ::MessageBox( ::GetFocus(),"Just read 8 or 24 bits Bitmap File.","Error",MB_OK ); return FALSE; }
                
                m_Cols      = bmInfoHdr.biWidth;
                m_Rows      = bmInfoHdr.biHeight;
                m_PxlBytes  = int(bmInfoHdr.biBitCount/8);

				if ( m_PxlBytes==1 ) // Read Color Table
					::ReadFile( hFile,m_pBmpInfo+sizeof(BITMAPINFOHEADER),256*sizeof(RGBQUAD),&rw,NULL );

                if ( m_pImgDat ) delete m_pImgDat; m_pImgDat = new BYTE[ m_Cols*m_Rows*m_PxlBytes +8 ];
                ::SetFilePointer( hFile,bmFileHdr.bfOffBits,NULL,FILE_BEGIN );
                int rowBytes = ( ( bmInfoHdr.biWidth*(bmInfoHdr.biBitCount)+31)& ~31 )/8 ;
                for ( int i=0;i<m_Rows;i++ ) ::ReadFile( hFile,m_pImgDat+i*m_Cols*m_PxlBytes,rowBytes,&rw,NULL );
                ::CloseHandle(hFile);
                return TRUE;
            };
    BOOL    Save2File( LPCSTR lpstrPathName ){
				BITMAPFILEHEADER  bmFileHdr; BITMAPINFOHEADER bmInfoHdr;   DWORD rw;
				HANDLE hFile    = ::CreateFile( lpstrPathName,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL );
				if ( !hFile && hFile==INVALID_HANDLE_VALUE ) return FALSE;
				
				memset( &bmInfoHdr,0,sizeof(bmInfoHdr) );
				bmInfoHdr.biSize	  = sizeof(bmInfoHdr);
				bmInfoHdr.biPlanes    = 1;
				bmInfoHdr.biWidth     = m_Cols      ;
				bmInfoHdr.biHeight    = m_Rows      ;
				bmInfoHdr.biBitCount  = m_PxlBytes*8;
				
				memset( &bmFileHdr,0,sizeof(bmFileHdr) );
				bmFileHdr.bfType      = ((WORD)('M'<<8)|'B');
				bmFileHdr.bfOffBits   = sizeof(bmFileHdr)+sizeof(bmInfoHdr)+1024;
				int rowBytes = ( (bmInfoHdr.biWidth*(bmInfoHdr.biBitCount)+31)& ~31 )/8 ;
				bmFileHdr.bfSize      = bmFileHdr.bfOffBits + rowBytes*bmInfoHdr.biHeight ;
				
				RGBQUAD pColTab[256];
				for ( int i=0;i<256;i++ ) pColTab[i].rgbRed=pColTab[i].rgbGreen=pColTab[i].rgbBlue=i;
				::WriteFile( hFile,&bmFileHdr,sizeof(bmFileHdr),&rw,NULL );
				::WriteFile( hFile,&bmInfoHdr,sizeof(bmInfoHdr),&rw,NULL );                
				::WriteFile( hFile,pColTab,sizeof(pColTab ),&rw,NULL );
				
				if ( rowBytes==m_Cols*m_PxlBytes )
					::WriteFile( hFile,m_pImgDat,bmFileHdr.bfSize-bmFileHdr.bfOffBits,&rw,NULL );
				else{
					for (int i=0;i<bmInfoHdr.biHeight-1;i++ )
						::WriteFile( hFile,m_pImgDat+i*m_Cols*m_PxlBytes,rowBytes,&rw,NULL );
					::WriteFile( hFile,m_pImgDat+i*m_Cols*m_PxlBytes,m_Cols*m_PxlBytes,&rw,NULL );
					::WriteFile( hFile,m_pImgDat,rowBytes-m_Cols*m_PxlBytes,&rw,NULL );
				}
				::CloseHandle(hFile);
				return TRUE;
			};
	void	Draw2DC( HDC hDC,int x,int y ){
				BITMAPINFO *pBmInf = (BITMAPINFO*)m_pBmpInfo;
				pBmInf->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
				pBmInf->bmiHeader.biCompression = BI_RGB;
				pBmInf->bmiHeader.biPlanes      = 1;
				pBmInf->bmiHeader.biBitCount    = m_PxlBytes*8;
				pBmInf->bmiHeader.biWidth       = m_Cols;
				pBmInf->bmiHeader.biHeight      = m_Rows; 
				
				BYTE *pBuf = m_pImgDat;
				int rowBytes = ( (pBmInf->bmiHeader.biWidth*(pBmInf->bmiHeader.biBitCount)+31)& ~31 )/8;
				if ( rowBytes!=m_Cols*m_PxlBytes ){
					pBuf = new BYTE[m_Rows*rowBytes];
					for (int i=0;i<m_Rows;i++ ) memcpy( pBuf+i*rowBytes,m_pImgDat+i*m_Cols*m_PxlBytes,m_Cols*m_PxlBytes );					
				}
				int oldMod = ::SetStretchBltMode( hDC,STRETCH_DELETESCANS );
				::StretchDIBits( hDC,
								 x,y,pBmInf->bmiHeader.biWidth,pBmInf->bmiHeader.biHeight,
								 0,0,pBmInf->bmiHeader.biWidth,pBmInf->bmiHeader.biHeight,
								 pBuf,(CONST BITMAPINFO *)pBmInf,
								 DIB_RGB_COLORS,SRCCOPY );
				::SetStretchBltMode( hDC,oldMod );

				if ( pBuf!=m_pImgDat ) delete []pBuf;
			};
public:
    BYTE*    m_pImgDat;
    int      m_Cols,m_Rows,m_PxlBytes;

	BYTE*    m_pBmpInfo;

};

#endif
