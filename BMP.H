//BMP.h
//	CBMP class
//	24bits Bitmap file 을 읽는 기능을 수행한다.
//	32bits DirectDrawSurface에 복사할 수 있는 기능이 있음.

#ifndef __BMP_H__
#define __BMP_H__

#include <ddraw.h>
class CBMP
{
private:
	int			m_nWidth;	//이미지의 폭
	int			m_nHeight;	// 이미지의 높이
	unsigned char *m_pBuffer; // 픽셀 데이터 버퍼

public:
	CBMP();
	~CBMP();
	int GetWidth();
	int GetHeight();
	bool LoadBMPFile( char *filename);
	bool CopyBufferToSurface(LPDIRECTDRAWSURFACE7 lpSurface);
};

#endif