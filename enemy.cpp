//enemy.cpp
//class CEnemy

#include "enemy.h"

CEnemy::CEnemy()
{
	m_speedy = 3;// 스피드 초기를 2로
	kill = false;
}

CEnemy::~CEnemy()
{
}

void CEnemy::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval, int enemy)
{
	after_x = x;
	after_y = y;
	sprite = enemy;

	switch(sprite)
	{
		case 0:
			check_x = 45;
			check_y = 40;
			break;

		case 1:
			check_x = 50;
			check_y = 45;
			break;

		case 2:
			check_x = 60;
			check_y = 30;
			break;

		case 3:
			check_x = 60;
			check_y = 30;
			break;
			
		case 4:
			check_x = 109;
			check_y = 35;
			break;
			
		case 5:
			check_x = 167;
			check_y = 110;
			break;
			
		case 6:
			check_x = 30;
			check_y = 45;
			break;
			
		case 7:
			check_x = 46;
			check_y = 45;
			break;
	}




	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);// 초기화 함수 타이머의 시작과 프레임을 설정
	m_nLastMoveTime = timer->time();// 게임 실행시간값을 넣는다.
	m_nMoveInterval = MoveInterval;// 움직임의 간격값을 대입한다.
}

void CEnemy::Move(int flag)	
{
	int temp=0;
	if(!m_bIsLive) return;	// 죽어있다면 그냥 리턴
	
	if(m_x<-500 || m_x>1000 || m_y<-500 || m_y>1300)
		m_bIsLive = false;

	switch(flag)	// 적패턴
	{
	case 0:		// 그냥 위에서 내려오기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedy=3;
			m_y+=m_speedy;		// 아래로 쭈욱
			/*
			if(m_y>=660) 
			{
				m_x=rand()%430+60;
				m_y=rand()%300-320;	// 450좌표가 넘는다면 다시 위로 올려준다.
				m_speedy=4;
			}*/
		}
		break;

	case 1:		// 그냥 위에서 내려오거나 아래에서 올라가기
		
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			switch(m_position)
			{
			case 1:
				m_y+=m_speedy;		// 아래로 쭈욱
				break;
			case 2:
				m_y-=m_speedy;		// 위로 쭈욱
				break;
			}
		}
		break;

	case 2:		//왼쪽 밑에서 올라 오다가 오른쪽으로 꺽기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;

			if(m_y<300)
			{
				m_x += 1;
				m_y -= 2;
			}
			else
				m_y -= 3;

		}
		break;
	case 3:		//오른쪽 밑에서 올라오다가 왼쪽으로 꺽기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;

			if(m_y<300)
			{
				m_x -= 1;
				m_y -= 2;
			}
			else
				m_y -= 3;

		}
		break;
	case 4:		//왼쪽 위에서 내려오다가 오른쪽으로 꺽기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;

			m_x += 3;


		}
		break;
	case 5:		//오른쪽 위에서 내려오다가 왼쪽으로 꺽기 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;

			m_x -= 3;

		}
		break;
	case 6:		//왼쪽 위에서 내려오다가 오른쪽으로 꺽어서 오른쪽 위로  올라가기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 3;

			if(m_y>400)
			{
				m_x += m_speedx;
				m_y += m_speedy;
			}
		//	if(m_x>200)
		//		m_y += m_speedy*(-1);
			else
				m_y += m_speedy;
		}
		break;
	case 7:		//오른쪽 위에서 내려오다가 왼쪽으로 꺽어서 왼쪽 위로 올라가기 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 3;

			if(m_y>400)
			{
				m_x -= m_speedx;
				m_y += m_speedy;
			}
		//	if(m_x<450)
		//		m_y += m_speedy*(-1);
			else
				m_y += m_speedy;
		}
		break;
	case 8:		//왼쪽 밑에서 올라오다가 오른쪽으로 꺽어서 오른쪽 밑으로 내려가기 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 3;

			if(m_y<100)
			{
				m_x += m_speedx;
				m_y += m_speedy*(-1);
			}
		//	if(m_x>200)
		//		m_y += m_speedy;
			else
				m_y += m_speedy*(-1);
		}
		break;
	case 9:		//오른쪽 밑에서 올라오다가 왼쪽으로 꺽어서 왼쪽 밑으로 내려가기 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 3;

			if(m_y<100)
			{
				m_x -= m_speedx;
				m_y += m_speedy*(-1);
			}
		//	if(m_x<450)
		//		m_y += m_speedy;
			else
				m_y += m_speedy*(-1);
		}
		break;
	case 10:		// 오른쪽위에서 대각선으로 내려와 반대로 내려가기
//		m_x = -50;	m_y = -50;
		
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 2;
			
			if(m_y>350)		// 방향 바꾸기
				m_speedx *= -1;
			
			m_x+=m_speedx;	
			m_y+=m_speedy;

			if(m_y>=660) 
			{
				m_x=-20;
				m_y=-20;
			}
		}
		break;
	case 11:	//위에서 밑으로 내려오다가 멈추기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 3;

			switch(m_position)
			{
			case 0:
				m_y += m_speedy;
				break;
			case 1:
				if(m_y<50)
					m_y += m_speedy;
				break;
			case 2:
				if(m_y<150)
					m_y += m_speedy;
				break;
			case 3:
				if(m_y<200)
					m_y += m_speedy;
				break;
			}
		}
		break;
	case 12:	//왼쪽위에서 시작해서 한반퀴 돌기 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 3;

			if(m_y>300)
				m_x += m_speedx;
			if(m_x>350)
				m_y += m_speedy*(-1);
		//	else
		//		m_y += m_speedy;
		}
		break;
	case 13:	//오른족 밑에서 시작해서 한바퀴 돌기 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 3;

			if(m_y<300)
				m_x -= m_speedx;
			if(m_x<300)
				m_y += m_speedy;
		//	else
		//		m_y += m_speedy*(-1);
		}
		break;
	case 14:	//위에서 밑으로 내려오다가 멈추기 (보스 전용)
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 3;

			switch(m_position)
			{
			case 0:
				m_y += m_speedy;
				break;
			case 1:
				if(m_y<100)
					m_y += m_speedy;
				break;
			case 2:
				if(m_y<150)
					m_y += m_speedy;
				break;
			case 3:
				if(m_y<200)
					m_y += m_speedy;
				break;
			}
		}
		break;
	case 15:	//왼쪽위에서 내려오다가 왼쪽 대각선으로 올라가기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;


			if(m_y>150)
			{
				m_x -= 3;
				m_y += 3;
			}
			else
				m_y += 3;

		}
		break;
	case 16:	//오른쪽위에서 내려오다가 오른쪽 대각선으로 올라가기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;

			
			if(m_y>150)
			{
				m_x += 3;
				m_y += 3;
			}
			else
				m_y += 3;
				

		}
		break;
	case 17:		//왼쪽 위에서 내려오다가 오른쪽 대각선 으로 꺽기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;

			if(m_y>150)
			{
				m_x += 3;
				m_y += 3;
			}
			else
				m_y += 3;

		}
		break;
	case 18:		//오른쪽 위에서 내려오다가 왼쪽대각선 으로 꺽기 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;

			if(m_y>150)
			{
				m_x -= 3;
				m_y += 3;
			}
			else
				m_y += 3;

		}
		break;
	case 19:
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;

			if(m_y>150)
				m_y -= 2;
		}
		break;
	case 20:	//왼쪽 대각선에서 오다가 아래로 내려가기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;

			switch(m_position)
			{
			case 1:
				if(m_y<150)
				{
					m_x += 3;
					m_y += 3;
				}
				else
					m_y += 3;
				break;
			case 2:
				if(m_y<200)
				{
					m_x += 3;
					m_y += 3;
				}
				else
					m_y += 3;
				break;
			case 3:
				if(m_y<250)
				{
					m_x += 3;
					m_y += 3;
				}
				else
					m_y += 3;
				break;
			case 4:
				if(m_y<300)
				{
					m_x += 3;
					m_y += 3;
				}
				else
					m_y += 3;
				break;
			case 5:
				if(m_y<350)
				{
					m_x += 3;
					m_y += 3;
				}
				else
					m_y += 3;
				break;

			}

		}
		break;
	case 21:	//왼쪽 대각선에서 오다가 아래로 내려가기
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
		//	m_speedx = 3;
			m_speedy = 2;

			switch(m_position)
			{
			case 1:
				if(m_y<150)
				{
					m_x -= 3;
					m_y += 3;
				}
				else
					m_y += 3;
				break;
			case 2:
				if(m_y<200)
				{
					m_x -= 3;
					m_y += 3;
				}
				else
					m_y += 3;
				break;
			case 3:
				if(m_y<250)
				{
					m_x -= 3;
					m_y += 3;
				}
				else
					m_y += 3;
				break;
			case 4:
				if(m_y<300)
				{
					m_x -= 3;
					m_y += 3;
				}
				else
					m_y += 3;
				break;
			case 5:
				if(m_y<350)
				{
					m_x -= 3;
					m_y += 3;
				}
				else
					m_y += 3;
				break;
			}

		}
		break;
	case 22:	//위에서 밑으로 내려오다가 멈추기 (보스 전용)
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 3;

			
			if(m_y<=150)
				m_y += m_speedy;
		}
		break;

	case 23:	// 보스 보조 미사일용
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// 게임실행시간이 프레임 간격 만큼 지났을때
		{
			m_speedx = 3;
			m_speedy = 2;
			
			m_y += m_speedy;
		}
		break;





	}
}

void CEnemy::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// 이미지를 그린다 표면을 보내준다
{
	CGObject::Draw(m_x, m_y, lpSurface);	// 해당 좌표에 이미지를 그려준다.
}

void CEnemy::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface)// 이미지를 그린다 표면을 보내준다
{
	CGObject::DrawFrame(m_x, m_y, drawframe, lpSurface);	// 해당 좌표에 이미지를 그려준다.
}

void CEnemy::Kill()
{	
	kill = true;
	CGObject::Kill();
}