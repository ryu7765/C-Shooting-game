//boss.h
#ifndef __Boss_h__
#define __Boss_h__

#include "gobject.h"

class CBoss : public CGObject	// ���
{
private:
	int		m_nLastMoveTime;	// ���������� ������ �ð�
	int		m_nMoveInterval;	// �������� �ð�����

public:
	int		m_myx;		// m_x�� �޴°�,,
	int		m_speedx;	// x�� ���ǵ�
	int		m_speedy;	// y�� ���ǵ�
	int		m_Enegy;	// ������

public:
	CBoss();	// ������
	~CBoss();		// �Ҹ���
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
					int FrameInterval, int MoveInterval);	// �ʱ�ȭ �Լ�
	void Draw( LPDIRECTDRAWSURFACE7 lpSurface);		// ���� �׸��� �Լ�
//	void DrawMissile( LPDIRECTDRAWSURFACE7 lpSurface);	// ���� �̻��� �׸��� �Լ�
//	void CreateMissile();	// ���� �̻��� ���� �Լ�
	void Move();	// ���� ������ �Լ�
};
#endif