// Item.h
// class CItem
#ifndef __item_h__	// 디버그 파일을 생성하지 않겟다고 함
#define __item_h__

#include "gobject.h"

class CItem : public CGObject
{
private:
	int		m_nLastMoveTime;	//마지막으로 움직인 시간
	int		m_nMoveInterval;		// 움직임의 시간 간격

public:
	CItem();
	~CItem();
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
						int FrameInterval, int MoveInterval, int nMove);	// 초기화 함수
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);	// 내 미사일 그리기 함수
	void Move();	// 내 미사일 이동 함수

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