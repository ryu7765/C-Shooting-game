// mymissile.h
// class CMyMissile
#ifndef __mymissile_h__	// 디버그 파일을 생성하지 않겟다고 함
#define __mymissile_h__

#include "gobject.h"

class CMyMissile : public CGObject
{
private:
	int		m_nLastMoveTime;	//마지막으로 움직인 시간
	int		m_nMoveInterval;		// 움직임의 시간 간격

public:
	CMyMissile();
	~CMyMissile();
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
						int FrameInterval, int MoveInterval, int s_x = 0, int s_y = 10);	// 초기화 함수
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);	// 내 미사일 그리기 함수
	void Move();	// 내 미사일 이동 함수

	int type;
	void DrawMissile(int set_x, int set_y, LPDIRECTDRAWSURFACE7 lpSurface, int Frame);

	void Kill();
	int speed_x;
	int speed_y;
	
};
#endif