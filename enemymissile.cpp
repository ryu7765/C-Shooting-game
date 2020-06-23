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
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);	// �ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time();// ���� ����ð����� �ִ´�.
	m_nMoveInterval = MoveInterval;// �������� ���ݰ��� �����Ѵ�.
}

void CEnemyMissile::Move(int s_x, int s_y, int i, int j, int k)	// enemy_x, enemy_y, myship_x, myship_y
{
	if(!m_bIsLive)  return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
			m_bIsLive = false;	// ���ش�.

		if(m_x<-50 || m_x>700 || m_y<-50 || m_y>650)
			m_bIsLive = false;
	}
}

void CEnemyMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// �̹����� �׸��� ǥ���� �����ش�
{
	CGObject::Draw(m_x, m_y, lpSurface);	// �ش� ��ǥ�� �̹����� �׷��ش�.
}

void CEnemyMissile::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface)// �̹����� �׸��� ǥ���� �����ش�
{
	CGObject::DrawFrame(m_x, m_y, drawframe, lpSurface);	// �ش� ��ǥ�� �̹����� �׷��ش�.
}
/*
void CEnemyMissile::Direction(int myshipX, int myshipY, int targetX, int targetY)
{
	int m_direction;
	
	if(targetX > myshipX)
	{
		if(targetY > myshipY)
			m_direction = 4; // ���ΰ��� ������ �Ʒ�
		else
			m_direction = 2; // ���ΰ��� ������ ��
	}
	else
	{
		if(targetY > myshipY)
			m_direction = 3; // ���ΰ��� ���� �Ʒ�
		else
			m_direction = 1; // ���ΰ��� ���� ��
	}

	if(targetX >= myshipX) 
		directionX = targetX - myshipX;	// ���� �ִ� ��ġ�� ã�� �Ÿ��� ���
	else if(targetX <  myshipX) 
		directionX = myshipX - targetX;
	if(targetY >= myshipY) 
		directionY = targetY - myshipY;
	else if(targetY <  myshipY) 
		directionY = myshipY - targetY;
	


	if(directionX > directionY)	// �ӵ� ����
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