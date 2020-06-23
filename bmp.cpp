// bmp.cpp
//	CBMP class �� ���� //24bits
//	DirectX  32bits
#include <windows.h>
#include <windowsx.h>
#include "bmp.h"

CBMP::CBMP()	// ������
{
	m_pBuffer = NULL;	// ���ۿ� ���� ������ �ʱ�ȭ
	m_nWidth = 0;	// �� ���� 0����
	m_nHeight = 0;	// ���� ���� 0���� �ʱ�ȭ
}
CBMP::~CBMP()		// �Ҹ��� 
{	
	if(m_pBuffer)		// ���۰� �ִٸ�
		delete []m_pBuffer;	// �޸� ���� �����ش�.
}
CBMP::GetHeight()	// ���̰��� ��ȯ�Ѵ�.
{
	return (m_nHeight);	
}
CBMP::GetWidth()		// ������ ��ȯ�Ѵ�.
{
	return (m_nWidth);
}

//24 bits bmp file
bool CBMP::LoadBMPFile(char *filename)	// bmp ������ �ҷ����� �Լ�
{
	HANDLE hfile;	// ���� �ڵ�
	DWORD actualRead;	// ������ �ҷ��ö� ����Ʈ ���� ������

	hfile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, 
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);  // 
	// ���� ����  ���ϰ�ο� ���� �Ӽ��� ��´�.
	if(hfile == INVALID_HANDLE_VALUE)	// ���н� �����ϴ� ��
		return false;
	BITMAPFILEHEADER bmpfilehead;
	if(!ReadFile(hfile, &bmpfilehead, sizeof(bmpfilehead), &actualRead, NULL))	// ������ �ҷ��´�.
	{
		CloseHandle(hfile);
		return false;
	}
	if(bmpfilehead.bfType != 0x4D42)	//'M' 'B' ��Ʈ�� ���������� �˻��Ѵ�.
	{
		CloseHandle(hfile);	// �ڵ��� �ݴ´�.
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


