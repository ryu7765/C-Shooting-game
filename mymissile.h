// mymissile.h
// class CMyMissile
#ifndef __mymissile_h__	// ����� ������ �������� �ʰٴٰ� ��
#define __mymissile_h__

#include "gobject.h"

class CMyMissile : public CGObject
{
private:
	int		m_nLastMoveTime;	//���������� ������ �ð�
	int		m_nMoveInterval;		// �������� �ð� ����

public:
	CMyMissile();
	~CMyMissile();
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
						int FrameInterval, int MoveInterval, int s_x = 0, int s_y = 10);	// �ʱ�ȭ �Լ�
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);	// �� �̻��� �׸��� �Լ�
	void Move();	// �� �̻��� �̵� �Լ�

	int type;
	void DrawMissile(int set_x, int set_y, LPDIRECTDRAWSURFACE7 lpSurface, int Frame);

	void Kill();
	int speed_x;
	int speed_y;
	
};
#endif