//enemymissile.h
#ifndef __EnemyMissile_h__
#define __EnemyMissile_h__

#include "gobject.h"

class CEnemyMissile : public CGObject
{
private:
	int		m_nLastMoveTime;	// 마지막으로 움직인 시간
	int		m_nMoveInterval;		// 움직임의 시간 간격

public:
	int m_speedx;
	int m_speedy;

public:
	CEnemyMissile();	// 생성자
	~CEnemyMissile();	// 소멸자
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
						int FrameInterval, int MoveInterval); // 초기화
	void Draw( LPDIRECTDRAWSURFACE7	 lpSurface);	// 그리기 함수
	void Move(int s_x, int s_y, int i, int j, int k);	//미사일 이동 함수
	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface);

	int drawframe;
};
#endif