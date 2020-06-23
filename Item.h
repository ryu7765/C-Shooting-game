// Item.h
// class CItem
#ifndef __item_h__	// ����� ������ �������� �ʰٴٰ� ��
#define __item_h__

#include "gobject.h"

class CItem : public CGObject
{
private:
	int		m_nLastMoveTime;	//���������� ������ �ð�
	int		m_nMoveInterval;		// �������� �ð� ����

public:
	CItem();
	~CItem();
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
						int FrameInterval, int MoveInterval, int nMove);	// �ʱ�ȭ �Լ�
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);	// �� �̻��� �׸��� �Լ�
	void Move();	// �� �̻��� �̵� �Լ�

	int type;
	void DrawMissile(int set_x, int set_y, LPDIRECTDRAWSURFACE7 lpSurface, int Frame);

	void Kill();
	int speed_x;
	int speed_y;

	int move;
	int life;
	
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame);
};
#endif