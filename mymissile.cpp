//mymissile.cpp
//class CMyMissile

#include "mymissile.h"

CMyMissile::CMyMissile()
{
}


CMyMissile::~CMyMissile()
{
}

void CMyMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval, int s_x, int s_y)
{
	speed_x = s_x;
	speed_y = s_y;
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval); // 초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time();	/// 게임 실행시간값을 넣는다.
	m_nMoveInterval = MoveInterval;// 움직임의 간격값을 대입한다.
}

void CMyMissile::Move()
{
	if(!m_bIsLive)  return;	// 죽어있다면 그냥 리턴

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_y -= speed_y;	// 위로 8씩 올라간다.
		m_x += speed_x;

		if(m_y<-50 || m_x<-10 || m_x > 660)	// 화면 밖으로 나가고 -100좌표를 넘어갓다면
		{
			m_bIsLive = false;// 죽여준다.
		}
	}
}

void CMyMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// 이미지를 그린다 표면을 보내준다
{
	CGObject::Draw(m_x, m_y, lpSurface);	// 해당 좌표에 이미지를 그려준다.
}

void CMyMissile::DrawMissile(int set_x, int set_y, LPDIRECTDRAWSURFACE7 lpSurface, int Frame)// 프레임값과 표면 값을 같이보내어 이미지를 그려준다.
{
	
	CGObject::DrawFrame(set_x+20, set_y, Frame, lpSurface); // 선택좌표에 이미지를 그린다.
	CGObject::DrawFrame(set_x-20, set_y, Frame, lpSurface); // 선택좌표에 이미지를 그린다.
	CGObject::DrawFrame(set_x, set_y, Frame, lpSurface); // 선택좌표에 이미지를 그린다.
}
			
void CMyMissile::Kill()
{	
	CGObject::Kill();
}