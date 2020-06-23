//boss.cpp
//class CBoss

#include "boss.h"

CBoss::CBoss()	// 생성자
{
	m_speedx=2;		// 보스 클래스 생성이 스피드를 2로 해준다.
}

CBoss::~CBoss()	// 소멸자
{
}

void CBoss::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval)	// 초기화 함수 좌표 값을 설정하고 
{																// 시간과 간격을 설정해준다.
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);	// 초기화
	m_nLastMoveTime = timer->time();	// 시간 설정
	m_nMoveInterval = MoveInterval;	// 간격값 설정
	m_myx= m_x; // 오브젝트 중심의 x좌표를 myx에 넣는다.
}

void CBoss::Move()
{
	if(!m_bIsLive) return;	// 살아있지 않다면 리턴

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))	// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		//if(m_x<50) { m_speedx = 2;}
		//if(m_x>750) { m_speedx= -2;}
		//m_x +=m_speedx;
	}
}

void CBoss::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// 이미지를 그린다 표면을 보내준다
{
	CGObject::Draw(m_x, m_y, lpSurface);	// 해당 좌표에 이미지를 그려준다.
}