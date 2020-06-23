// bmp.cpp
//	CBMP class 의 구현 //24bits
//	DirectX  32bits
#include <windows.h>
#include <windowsx.h>
#include "bmp.h"

CBMP::CBMP()	// 생성자
{
	m_pBuffer = NULL;	// 버퍼에 값이 없도록 초기화
	m_nWidth = 0;	// 폭 값을 0으로
	m_nHeight = 0;	// 높이 값을 0으로 초기화
}
CBMP::~CBMP()		// 소멸자 
{	
	if(m_pBuffer)		// 버퍼가 있다면
		delete []m_pBuffer;	// 메모리 해제 시켜준다.
}
CBMP::GetHeight()	// 높이값을 반환한다.
{
	return (m_nHeight);	
}
CBMP::GetWidth()		// 폭값을 반환한다.
{
	return (m_nWidth);
}

//24 bits bmp file
bool CBMP::LoadBMPFile(char *filename)	// bmp 파일을 불러오는 함수
{
	HANDLE hfile;	// 파일 핸들
	DWORD actualRead;	// 파일을 불러올때 바이트 값을 받을곳

	hfile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, 
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);  // 
	// 파일 생성  파일경로와 파일 속성을 담는다.
	if(hfile == INVALID_HANDLE_VALUE)	// 실패시 리턴하는 값
		return false;
	BITMAPFILEHEADER bmpfilehead;
	if(!ReadFile(hfile, &bmpfilehead, sizeof(bmpfilehead), &actualRead, NULL))	// 파일을 불러온다.
	{
		CloseHandle(hfile);
		return false;
	}
	if(bmpfilehead.bfType != 0x4D42)	//'M' 'B' 비트맵 파일인지를 검사한다.
	{
		CloseHandle(hfile);	// 핸들을 닫는다.
		return false;
	}

	BITMAPINFOHEADER bmpinfohead;
	if(!ReadFile(hfile, &bmpinfohead, sizeof(bmpinfohead), &actualRead, NULL))	// 
	{
		CloseHandle(hfile);
		return false;
	}
	if(bmpinfohead.biBitCount != 24)	//
	{
		CloseHandle(hfile);
		return false;
	}

	int nHeight = bmpinfohead.biHeight;
	bool bBottomUp;

	if(nHeight>0)
	{
		bBottomUp = true;
	}
	else
	{
		bBottomUp = false;
		nHeight = -nHeight;
	}

	m_nHeight = nHeight;
	m_nWidth = bmpinfohead.biWidth;

	if(m_pBuffer)
		delete[] m_pBuffer;

	m_pBuffer = new unsigned char[m_nHeight * m_nWidth * 4];

	struct RGBstruct
	{
		unsigned char B;
		unsigned char G;
		unsigned char R;
	};

	struct RGBstruct rgb24;

	int nStoredLine = (m_nWidth * 3 + 3)&~3;
	unsigned char temp[4];
	int nRemainder = nStoredLine - (m_nWidth*3);

	int nDestY, nDeltaY;

	if(bBottomUp)
	{
		nDestY = nHeight-1;
		nDeltaY = -1;
	}
	else
	{
		nDestY = 0;
		nDeltaY = 1;
	}

	for( int y=0; y<nHeight;y++)
	{
		for( int x=0; x<m_nWidth;x++)
		{
			if(!ReadFile(hfile, &rgb24, 3, &actualRead, NULL))
			{
				CloseHandle(hfile);
				delete []m_pBuffer;
				return false;
			}

			CopyMemory(m_pBuffer + (x<<2) + nDestY * (m_nWidth << 2), &rgb24,3);
			*(m_pBuffer + (x<<2) + nDestY * (m_nWidth << 2)+3) = 0;

		}
		nDestY+=nDeltaY;

		if(!ReadFile(hfile, temp, nRemainder, &actualRead, NULL))
		{
			CloseHandle(hfile);
			delete []m_pBuffer;
			return false;
		}
	}

	CloseHandle(hfile);

	return true;
}

bool CBMP::CopyBufferToSurface(LPDIRECTDRAWSURFACE7 lpSurface)
{
	if(!m_pBuffer)
		return false;

	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize=sizeof(ddsd);

	if(FAILED(lpSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL)))
		return false;

	unsigned char *pDest, *pSrc;

	pDest = (unsigned char * ) ddsd.lpSurface;
	pSrc = m_pBuffer;

	for(int y=0;y<m_nHeight;y++)
	{
		CopyMemory(pDest, pSrc, m_nWidth<<2);
		pDest += ddsd.lPitch;
		pSrc += (m_nWidth<<2);
	}

	lpSurface->Unlock(NULL);

	return true;
}


