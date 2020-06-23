// assist.h
// class CAssistMissile
#ifndef __assistmissile_h__	// ����� ������ �������� �ʰٴٰ� ��
#define __assistmissile_h__

#include "gobject.h"

class CAssistMissile : public CGObject
{
private:
	int		m_nLastMoveTime;	//���������� ������ �ð�
	int		m_nMoveInterval;		// �������� �ð� ����

public:
	CAssistMissile();
	~CAssistMissile();
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
						int FrameInterval, int MoveInterval, int t_x = 0, bool b_change = false);	// �ʱ�ȭ �Լ�
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);	// �� �̻��� �׸��� �Լ�
	void Move(int t_x =0);	// �� �̻��� �̵� �Լ�

	int type;
	void DrawMissile(int set_x, int set_y, LPDIRECTDRAWSURFACE7 lpSurface, int Frame);

	void Kill();
	int speed_x;
	int speed_y;

	int init_x;
	int target_x;
	
	bool change;
	bool targetOn;

	int i,j;
};
#endif