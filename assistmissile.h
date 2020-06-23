// assist.h
// class CAssistMissile
#ifndef __assistmissile_h__	// 디버그 파일을 생성하지 않겟다고 함
#define __assistmissile_h__

#include "gobject.h"

class CAssistMissile : public CGObject
{
private:
	int		m_nLastMoveTime;	//마지막으로 움직인 시간
	int		m_nMoveInterval;		// 움직임의 시간 간격

public:
	CAssistMissile();
	~CAssistMissile();
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
						int FrameInterval, int MoveInterval, int t_x = 0, bool b_change = false);	// 초기화 함수
	void Draw(LPDIRECTDRAWSURFACE7 lpSurface);	// 내 미사일 그리기 함수
	void Move(int t_x =0);	// 내 미사일 이동 함수

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