//Item.cpp
//class CItem

#include "Item.h"
#include "math.h"

CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval, int nMove)
{
	life = 0;
	move = nMove;
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval); // 초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time();	/// 게임 실행시간값을 넣는다.
	m_nMoveInterval = MoveInterval;// 움직임의 간격값을 대입한다.
}

void CItem::Move()
{
	if(!m_bIsLive)  return;	// 죽어있다면 그냥 리턴

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		m_y += speed_y;	// 위로 8씩 올라간다.
		m_x += speed_x;

		life++;

		if(life  > 700)
			m_bIsLive = false;



		switch(move)
		{
			case 1: //오른쪽 위 대각선

				speed_x = 2;
				speed_y = -2;

				if(m_y <= 0 + 21)
				{
					move = 2;
				}

				if(m_x >=650 - 21)
				{
					move = 4;
				}
				break;

			case 2:
				speed_x = 2;
				speed_y = 2;

				if(m_y >= 400 - 21)
				{
					move = 1;
				}

				if(m_x >=650 - 21)
				{
					move = 3;
				}
				break;

			case 3:
				speed_x = -2;
				speed_y = 2;

				if(m_y >= 400 - 21)
				{
					move = 4;
				}

				if(m_x <= 0 + 21)
				{
					move = 2;
				}
				break;

			case 4:
				speed_x = -2;
				speed_y = -2;

				if(m_y <= 0 + 21)
				{
					move = 3;
				}

				if(m_x <= 0 + 21)
				{
					move = 1;
				}
				break;
		}
		

		

		

		if(m_y>600 || m_y<-50 || m_x<-10 || m_x > 660)	// 화면 밖으로 나가고 -100좌표를 넘어갓다면
		{
			m_bIsLive = false;// 죽여준다.
		}
	}
}

void CItem::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// 이미지를 그린다 표면을 보내준다
{
	CGObject::Draw(m_x, m_y, lpSurface);	// 해당 좌표에 이미지를 그려준다.
}

void CItem::DrawMissile(int set_x, int set_y, LPDIRECTDRAWSURFACE7 lpSurface, int Frame)// 프레임값과 표면 값을 같이보내어 이미지를 그려준다.
{
	
	CGObject::DrawFrame(set_x, set_y, Frame, lpSurface); // 선택좌표에 이미지를 그린다.
}
			
void CItem::Kill()
{	
	CGObject::Kill();
}

void CItem::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame)
{
	CGObject::DrawFrame(m_x, m_y, Frame, lpSurface); 
}
