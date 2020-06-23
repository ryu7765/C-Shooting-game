// sprite.h
// CSprite class
//		DirectX 7.0 �̻�

#ifndef __sprite_h__
#define __sprite_h__

#include <ddraw.h>
#include "bmp.h"

class CSprite
{

private:
	int			m_nFrame;		//�����Ӽ�
	int			m_nWidth;		//��
	int			m_nHeight;		// ����
	LPDIRECTDRAWSURFACE7 *m_ppSurface;
	CBMP		*m_pBMPArray;
public:
	CSprite();
	~CSprite();
	int	  GetNumberOfFrame();// �������� ���� ��´�.
	bool	InitSprite( int nFrame, int nWidth, int nHeight, int nColorKey, LPDIRECTDRAW7 pDirectDraw);
	bool	LoadFrame( int nFrame, char *filename);	//�����������*.bmpȭ�̷� ���� �о��.
	bool	Drawing( int nFrame, int x, int y, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey = true);
	bool	Drawing2( int nFrame, int bgflag, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey = true);	// ���
	bool	Restore();	// Sprite ���� ��� Surface�� ���� ��Ű�� ����� ������.
	bool	ReleaseAll();	// Sprite ���� ��� Surface�� Release ��Ų��.

	bool CSprite::ItemDrawing(int nFrame, int x, int y, int p_x, int s_x, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey);
		//������ ��ο�

	int		speed;

};

#endif
