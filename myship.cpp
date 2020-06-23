//myship.cpp
//class CMyShip

#include "myship.h"

CMyShip::CMyShip()
{
	life = 3;
	speed = 5;
	item = 0;
	level = 0;
	type = 0;

	InitMyShip_y = 620;
	InitMyShip_x = (800-150)/2;
}

CMyShip::~CMyShip()
{
}

void CMyShip::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);// 초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time();// 게임 실행시간값을 넣는다.
	m_nMoveInterval = MoveInterval;// 움직임의 간격값을 대입한다.
}

void CMyShip::Left()// 왼쪽 눌럿을때
{
	if(!m_bIsLive) return;

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_x -= speed;	// x를 5씩 감소
		if(m_x<30)	// 30보다 작으면
		{
			m_x=30;	// 넘어가지않도록 30을 유지
		}
	}
}

void CMyShip::Right()	// 오른쪽 눌렀을때
{
	if(!m_bIsLive) return;	// 죽어있다면 그냥 리턴

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_x+=speed;	// x를 5씩 증가
		if(m_x>620)	// 770보다 크다면
		{
			m_x=620;	// 넘어가지 않도록 770을 유지
		}
	}
}

void CMyShip::Up()
{
	if(!m_bIsLive) return;	// 죽어있다면 그냥 리턴

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_y-=speed;
		if(m_y<30)
		{
			m_y=30;
		}
	}
}

void CMyShip::Down()
{
	if(!m_bIsLive) return;	// 죽어있다면 그냥 리턴

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_y += speed;
		if(m_y>570)
		{
			m_y=570;
		}
	}
}

void CMyShip::Upright()
{
	if(!m_bIsLive) return;	// 죽어있다면 그냥 리턴

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_y-=speed;		m_x+=speed;
		if(m_y<30)
		{
			m_y=30;
		}
		if(m_x>620)
		{
			m_x=620;
		}
	}
}

void CMyShip::Upleft()
{
	if(!m_bIsLive) return;	// 죽어있다면 그냥 리턴

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_y-=speed;			m_x -= speed;
		if(m_y<30)
		{
			m_y=30;
		}
		if(m_x<30)
		{

			m_x=30;
		}

	}
}

void CMyShip::Downright()
{
	if(!m_bIsLive) return;	// 죽어있다면 그냥 리턴

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_y += speed;		m_x+=speed;
		if(m_y>570)
		{
			m_y=570;
		}
		if(m_x>620)
		{
			m_x=620;
		}
	}
}

void CMyShip::Downleft()
{
	if(!m_bIsLive) return;	// 죽어있다면 그냥 리턴

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_y += speed;		m_x -= speed;
		if(m_y>570)
		{
			m_y=570;
		}
		if(m_x<30)
		{
			m_x=30;
		}
	}
}

void CMyShip::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame)// 프레임값과 표면 값을 같이보내어 이미지를 그려준다.
{
	
	CGObject::DrawFrame(m_x, m_y, Frame, lpSurface); // 선택좌표에 이미지를 그린다.
}
			
