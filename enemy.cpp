//enemy.cpp
//class CEnemy

#include "enemy.h"

CEnemy::CEnemy()
{
	m_speedy = 3;// ���ǵ� �ʱ⸦ 2��
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




	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);// �ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time();// ���� ����ð����� �ִ´�.
	m_nMoveInterval = MoveInterval;// �������� ���ݰ��� �����Ѵ�.
}

void CEnemy::Move(int flag)	
{
	int temp=0;
	if(!m_bIsLive) return;	// �׾��ִٸ� �׳� ����
	
	if(m_x<-500 || m_x>1000 || m_y<-500 || m_y>1300)
		m_bIsLive = false;

	switch(flag)	// ������
	{
	case 0:		// �׳� ������ ��������
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
		{
			m_speedy=3;
			m_y+=m_speedy;		// �Ʒ��� �޿�
			/*
			if(m_y>=660) 
			{
				m_x=rand()%430+60;
				m_y=rand()%300-320;	// 450��ǥ�� �Ѵ´ٸ� �ٽ� ���� �÷��ش�.
				m_speedy=4;
			}*/
		}
		break;

	case 1:		// �׳� ������ �������ų� �Ʒ����� �ö󰡱�
		
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
		{
			switch(m_position)
			{
			case 1:
				m_y+=m_speedy;		// �Ʒ��� �޿�
				break;
			case 2:
				m_y-=m_speedy;		// ���� �޿�
				break;
			}
		}
		break;

	case 2:		//���� �ؿ��� �ö� ���ٰ� ���������� ����
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 3:		//������ �ؿ��� �ö���ٰ� �������� ����
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 4:		//���� ������ �������ٰ� ���������� ����
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
		{
		//	m_speedx = 3;
			m_speedy = 2;

			m_x += 3;


		}
		break;
	case 5:		//������ ������ �������ٰ� �������� ���� 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
		{
		//	m_speedx = 3;
			m_speedy = 2;

			m_x -= 3;

		}
		break;
	case 6:		//���� ������ �������ٰ� ���������� ��� ������ ����  �ö󰡱�
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 7:		//������ ������ �������ٰ� �������� ��� ���� ���� �ö󰡱� 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 8:		//���� �ؿ��� �ö���ٰ� ���������� ��� ������ ������ �������� 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 9:		//������ �ؿ��� �ö���ٰ� �������� ��� ���� ������ �������� 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 10:		// ������������ �밢������ ������ �ݴ�� ��������
//		m_x = -50;	m_y = -50;
		
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
		{
			m_speedx = 3;
			m_speedy = 2;
			
			if(m_y>350)		// ���� �ٲٱ�
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
	case 11:	//������ ������ �������ٰ� ���߱�
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 12:	//���������� �����ؼ� �ѹ��� ���� 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 13:	//������ �ؿ��� �����ؼ� �ѹ��� ���� 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 14:	//������ ������ �������ٰ� ���߱� (���� ����)
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 15:	//���������� �������ٰ� ���� �밢������ �ö󰡱�
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 16:	//������������ �������ٰ� ������ �밢������ �ö󰡱�
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 17:		//���� ������ �������ٰ� ������ �밢�� ���� ����
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 18:		//������ ������ �������ٰ� ���ʴ밢�� ���� ���� 
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
		{
		//	m_speedx = 3;
			m_speedy = 2;

			if(m_y>150)
				m_y -= 2;
		}
		break;
	case 20:	//���� �밢������ ���ٰ� �Ʒ��� ��������
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 21:	//���� �밢������ ���ٰ� �Ʒ��� ��������
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	case 22:	//������ ������ �������ٰ� ���߱� (���� ����)
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
		{
			m_speedx = 3;
			m_speedy = 3;

			
			if(m_y<=150)
				m_y += m_speedy;
		}
		break;

	case 23:	// ���� ���� �̻��Ͽ�
		if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
		{
			m_speedx = 3;
			m_speedy = 2;
			
			m_y += m_speedy;
		}
		break;





	}
}

void CEnemy::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// �̹����� �׸��� ǥ���� �����ش�
{
	CGObject::Draw(m_x, m_y, lpSurface);	// �ش� ��ǥ�� �̹����� �׷��ش�.
}

void CEnemy::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface)// �̹����� �׸��� ǥ���� �����ش�
{
	CGObject::DrawFrame(m_x, m_y, drawframe, lpSurface);	// �ش� ��ǥ�� �̹����� �׷��ش�.
}

void CEnemy::Kill()
{	
	kill = true;
	CGObject::Kill();
}