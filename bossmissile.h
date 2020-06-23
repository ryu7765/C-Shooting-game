//bossmissile.h
#ifndef __BossMissile_h__
#define __BossMissile_h__

#include "gobject.h"

class CBossMissile : public CGObject
{
private:
	int		m_nLastMoveTime;		// ���������� ������ �ð�
	int		m_nMoveInterval;		/// �������� �ð� ����

public:
	int		m_speedx;	// ���ǵ尪

public:
	CBossMissile();	// ������
	~CBossMissile();	// �Ҹ���
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
					int FrameInterval, int MoveInterval);	// �ʱ�ȭ �Լ�
	void Draw( LPDIRECTDRAWSURFACE7 lpSurface);	// �̹��� �׸���
	void Move();	// �̵� �Լ�
};
#endif