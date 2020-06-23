//assistMissile.cpp
//class CAssistMissile

#include "assistmissile.h"

CAssistMissile::CAssistMissile()
{
	speed_x = 0;
	speed_y = 1;

	targetOn = false;
}


CAssistMissile::~CAssistMissile()
{
}

void CAssistMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval, int t_x, bool b_change)
{
//	target_x = t_x;
	speed_x = 0;
	speed_y = 1;
	change = b_change;
	targetOn = false;
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval); // 초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time();	/// 게임 실행시간값을 넣는다.
	m_nMoveInterval = MoveInterval;// 움직임의 간격값을 대입한다.
}

void CAssistMissile::Move(int t_x)
{
	if(!m_bIsLive)  return;	// 죽어있다면 그냥 리턴

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
		if(type == 1)
		{
			m_y -= ((speed_y++)/3);	// 위로 8씩 올라간다.
			
			if(change)
			{
				m_y -= ((speed_y)/30);
			}
			else
			{
				if(init_x < m_x )		
					m_x += ((speed_x++)/20);
				else
					m_x -= ((speed_x++)/20);
			}
		}
		else if(type == 2)
		{
			m_y -= ((speed_y++)/4);
			speed_x = 7;
			
			if(!targetOn)
			{
				target_x = t_x;
				targetOn = true;
			}

			if(abs(target_x-m_x) < 7)
				speed_x = 1;

			if(target_x > m_x )		
				m_x += speed_x;
			else if(target_x < m_x)
				m_x -= speed_x;
			else
				;
		}

		if(m_y<-15 || m_x<-5 || m_x > 655)	// 화면 밖으로 나가고 -100좌표를 넘어갓다면
		{
			m_bIsLive = false;// 죽여준다.
		}
	}
}

void CAssistMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// 이미지를 그린다 표면을 보내준다
{
	CGObject::Draw(m_x, m_y, lpSurface);	// 해당 좌표에 이미지를 그려준다.
}

void CAssistMissile::DrawMissile(int set_x, int set_y, LPDIRECTDRAWSURFACE7 lpSurface, int Frame)// 프레임값과 표면 값을 같이보내어 이미지를 그려준다.
{
	CGObject::DrawFrame(set_x, set_y, Frame, lpSurface); // 선택좌표에 이미지를 그린다.
}
			
void CAssistMissile::Kill()
{	
	targetOn = false;
	CGObject::Kill();
}