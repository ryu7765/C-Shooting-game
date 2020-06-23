//enemy.h
// class CEnemy
#ifndef __enemy_h__
#define __enemy_h__

#include "gobject.h"
#include "define.h"

class CEnemy : public CGObject
{
private:
	int		m_nLastMoveTime; // 마지막으로 움직인 시간
	int		m_nMoveInterval; // 움직임의 시간 간격
public:
	int		m_speedx;	// x축 스피드
	int		m_speedy;	// y축 스피드
	bool	kill;

	int		life;
	int		score;

public:
	CEnemy();	// 생성자
	~CEnemy();	// 소멸자
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
					int FrameInterval, int MoveInterval, int enemy); // 초기화
	void Draw( LPDIRECTDRAWSURFACE7 lpSurface);	// 적 그리기
//	void DrawMissile( LPDIRECTDRAWSURFACE7 lpSurface);	// 적 미사일 그리기
//	void CreateMissile();	// 적 미사일 생성
	void Move(int flag);	// 적 이동 함수
	void Kill();

	int after_x, after_y;
	int drawframe;
	int sprite;

	int check_x, check_y;
	int m_position;

	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface);

	

};
#endif