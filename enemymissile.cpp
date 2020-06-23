//enemymissile.cpp
//class CEnemyMissile

#include "enemymissile.h"

CEnemyMissile::CEnemyMissile()
{
	m_speedx = 0;
}

CEnemyMissile::~CEnemyMissile()
{
}

void CEnemyMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);	// 초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time();// 게임 실행시간값을 넣는다.
	m_nMoveInterval = MoveInterval;// 움직임의 간격값을 대입한다.
}

void CEnemyMissile::Move(int s_x, int s_y, int i, int j, int k)	// enemy_x, enemy_y, myship_x, myship_y
{
	if(!m_bIsLive)  return;	// 죽어있다면 그냥 리턴

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
	{
//		if(s_x>e_x)	m_x+=5;		else	m_x-=5;
//		if(s_y>e_y)	m_y+=5;		else	m_y-=5;
		

		if(i == 23)
		{
			drawframe = k % 12;
			switch(k%12)
			{
				case 0:
					m_speedx = 3;
					m_speedy = 0;
					break;

				case 1:
					m_speedx = 2;
					m_speedy = 1;
					break;

				case 2:
					m_speedx = 1;
					m_speedy = 2;
					break;

				case 3:
					m_speedx = 0;
					m_speedy = 3;
					break;

				case 4:
					m_speedx = -1;
					m_speedy = 2;
					break;

				case 5:
					m_speedx = -2;
					m_speedy = 1;
					break;

				case 6:
					m_speedx = -3;
					m_speedy = 0;
					break;

				case 7:
					m_speedx = -2;
					m_speedy = -1;
					break;

				case 8:
					m_speedx = -1;
					m_speedy = -2;
					break;

				case 9:
					m_speedx = 0;
					m_speedy = -3;
					break;

				case 10:
					m_speedx = 1;
					m_speedy = -2;
					break;

				case 11:
					m_speedx = 2;
					m_speedy = -1;
					break;
			}

			m_speedx*=2;
			m_speedy*=2;
		}
		
		m_x += m_speedx;
		m_y+= m_speedy;

		if(m_y>650)
			m_bIsLive = false;	// 없앤다.

		if(m_x<-50 || m_x>700 || m_y<-50 || m_y>650)
			m_bIsLive = false;
	}
}

void CEnemyMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// 이미지를 그린다 표면을 보내준다
{
	CGObject::Draw(m_x, m_y, lpSurface);	// 해당 좌표에 이미지를 그려준다.
}

void CEnemyMissile::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface)// 이미지를 그린다 표면을 보내준다
{
	CGObject::DrawFrame(m_x, m_y, drawframe, lpSurface);	// 해당 좌표에 이미지를 그려준다.
}
/*
void CEnemyMissile::Direction(int myshipX, int myshipY, int targetX, int targetY)
{
	int m_direction;
	
	if(targetX > myshipX)
	{
		if(targetY > myshipY)
			m_direction = 4; // 주인공이 오른쪽 아래
		else
			m_direction = 2; // 주인공이 오른쪽 위
	}
	else
	{
		if(targetY > myshipY)
			m_direction = 3; // 주인공이 왼쪽 아래
		else
			m_direction = 1; // 주인공이 왼쪽 위
	}

	if(targetX >= myshipX) 
		directionX = targetX - myshipX;	// 적이 있는 위치를 찾아 거리를 재고
	else if(targetX <  myshipX) 
		directionX = myshipX - targetX;
	if(targetY >= myshipY) 
		directionY = targetY - myshipY;
	else if(targetY <  myshipY) 
		directionY = myshipY - targetY;
	


	if(directionX > directionY)	// 속도 조정
	{
		directionY = 10 * (directionY / directionX); 
		directionX = 10;
	}
	else if(directionX < directionY) 
	{
		directionX = 10 * (directionX / directionY);
		directionY = 10;
	}
	else
	{
		directionX = 10;
		directionY = 10;
	}

	switch(m_direction)
	{
	case 1:
		directionX *= -1;
		directionY *= -1;
		break;
	case 2:
		directionY *= -1;
		break;
	case 3:
		directionX *= -1;
		break;
	}

	directionX += ((rand())%3)-1;
	directionY += ((rand())%3)-1;
			
}*/