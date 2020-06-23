// sprite.h
// CSprite class
//		DirectX 7.0 이상

#ifndef __sprite_h__
#define __sprite_h__

#include <ddraw.h>
#include "bmp.h"

class CSprite
{

private:
	int			m_nFrame;		//프레임수
	int			m_nWidth;		//폭
	int			m_nHeight;		// 높이
	LPDIRECTDRAWSURFACE7 *m_ppSurface;
	CBMP		*m_pBMPArray;
public:
	CSprite();
	~CSprite();
	int	  GetNumberOfFrame();// 총프레임 수를 얻는다.
	bool	InitSprite( int nFrame, int nWidth, int nHeight, int nColorKey, LPDIRECTDRAW7 pDirectDraw);
	bool	LoadFrame( int nFrame, char *filename);	//몇번프레임을*.bmp화이로 부터 읽어옴.
	bool	Drawing( int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey = true);
	bool	Drawing2( int nFrame, int bgflag, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey = true);	// 배경
	bool	Restore();	// Sprite 내의 모든 Surface를 복구 시키는 기능을 수행함.
	bool	ReleaseAll();	// Sprite 내의 모든 Surface를 Release 시킨다.

	bool CSprite::ItemDrawing(int nFrame, int x, int y, int p_x, int s_x, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey);
		//아이템 드로우

	int		speed;

};

#endif
