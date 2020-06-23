//enemymissile.h
#ifndef __EnemyMissile_h__
#define __EnemyMissile_h__

#include "gobject.h"

class CEnemyMissile : public CGObject
{
private:
	int		m_nLastMoveTime;	// ���������� ������ �ð�
	int		m_nMoveInterval;		// �������� �ð� ����

public:
	int m_speedx;
	int m_speedy;

public:
	CEnemyMissile();	// ������
	~CEnemyMissile();	// �Ҹ���
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
						int FrameInterval, int MoveInterval); // �ʱ�ȭ
	void Draw( LPDIRECTDRAWSURFACE7	 lpSurface);	// �׸��� �Լ�
	void Move(int s_x, int s_y, int i, int j, int k);	//�̻��� �̵� �Լ�
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface);

	int drawframe;
};
#endif