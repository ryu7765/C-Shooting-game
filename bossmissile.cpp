//bossmissile.cpp
//Class BossMissile

#include "bossmissile.h"

CBossMissile::CBossMissile()
{
	m_speedx=2;	// 생성됬을때 speed를 2로
}

CBossMissile::~CBossMissile()
{
}

void CBossMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);// 초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time();// 게임 실행시간값을 넣는다.
	m_nMoveInterval = MoveInterval; // 움직임의 간격값을 대입한다.
}

void CBossMissile::Move()
{
	if(!m_bIsLive) return;	// 죽어있다면 그냥 리턴

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))	// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_x += m_speedx;	// 스피드만큼 x값을 증가시킨다.
		m_y += 5;		// y값을 5씩 증가시킨다.

		if(m_y>600)// 오브젝트가 600 을 넘어가면
		{
			m_bIsLive = false;// 죽인다.
		}
	}
}

void CBossMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// 이미지를 그린다 표면을 보내준다
{
	CGObject::Draw(m_x, m_y, lpSurface);	// 해당 좌표에 이미지를 그려준다.
}