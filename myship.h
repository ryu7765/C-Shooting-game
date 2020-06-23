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
	int		m_nLastMoveTime;	// 마지막으로 움직인 시간
	int		m_nMoveInterval; // 움직임의 시간 간겨

public:
	CMyShip();
	~CMyShip();
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval);	// 초기화
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame);	// 플레이어 그리기
	void Left();	// 왼쪽 이동
	void Right();	// 오른쪽 이동
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
