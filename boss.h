//boss.h
#ifndef __Boss_h__
#define __Boss_h__

#include "gobject.h"

class CBoss : public CGObject	// 상속
{
private:
	int		m_nLastMoveTime;	// 마지막으로 움직인 시간
	int		m_nMoveInterval;	// 움직임의 시간간격

public:
	int		m_myx;		// m_x를 받는곳,,
	int		m_speedx;	// x축 스피드
	int		m_speedy;	// y축 스피드
	int		m_Enegy;	// 에너지

public:
	CBoss();	// 생성자
	~CBoss();		// 소멸자
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
					int FrameInterval, int MoveInterval);	// 초기화 함수
	void Draw( LPDIRECTDRAWSURFACE7 lpSurface);		// 보스 그리기 함수
//	void DrawMissile( LPDIRECTDRAWSURFACE7 lpSurface);	// 보스 미사일 그리기 함수
//	void CreateMissile();	// 보스 미사일 생성 함수
	void Move();	// 보스 움직임 함수
};
#endif