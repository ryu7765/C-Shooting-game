// myship.h
// class CMyShip
#ifndef __myship_h__
#define __myship_h__

#include "gobject.h"

class CMyShip : public CGObject
{
public:
	int			life;
	int			speed;
	int			item;
	int			type;
	int			level;
	int			missiletype;
	int			assistlevel;
private:
	int		m_nLastMoveTime;	// ���������� ������ �ð�
	int		m_nMoveInterval; // �������� �ð� ����

public:
	CMyShip();
	~CMyShip();
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval);	// �ʱ�ȭ
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame);	// �÷��̾� �׸���
	void Left();	// ���� �̵�
	void Right();	// ������ �̵�
	void Up();
	void Down();
	void Upleft();
	void Upright();
	void Downleft();
	void Downright();

	int InitMyShip_y;
	int InitMyShip_x;
	

};
#endif
