//bossmissile.h
#ifndef __BossMissile_h__
#define __BossMissile_h__

#include "gobject.h"

class CBossMissile : public CGObject
{
private:
	int		m_nLastMoveTime;		// 마지막으로 움직인 시간
	int		m_nMoveInterval;		/// 움직임의 시간 간격

public:
	int		m_speedx;	// 스피드값

public:
	CBossMissile();	// 생성자
	~CBossMissile();	// 소멸자
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
					int FrameInterval, int MoveInterval);	// 초기화 함수
	void Draw( LPDIRECTDRAWSURFACE7 lpSurface);	// 이미지 그리기
	void Move();	// 이동 함수
};
#endif