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
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);// �ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time();// ���� ����ð����� �ִ´�.
	m_nMoveInterval = MoveInterval;// �������� ���ݰ��� �����Ѵ�.
}

void CMyShip::Left()// ���� ��������
{
	if(!m_bIsLive) return;

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{
		m_x -= speed;	// x�� 5�� ����
		if(m_x<30)	// 30���� ������
		{
			m_x=30;	// �Ѿ���ʵ��� 30�� ����
		}
	}
}

void CMyShip::Right()	// ������ ��������
{
	if(!m_bIsLive) return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{
		m_x+=speed;	// x�� 5�� ����
		if(m_x>620)	// 770���� ũ�ٸ�
		{
			m_x=620;	// �Ѿ�� �ʵ��� 770�� ����
		}
	}
}

void CMyShip::Up()
{
	if(!m_bIsLive) return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	if(!m_bIsLive) return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	if(!m_bIsLive) return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	if(!m_bIsLive) return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	if(!m_bIsLive) return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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
	if(!m_bIsLive) return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer-> elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
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

void CMyShip::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame)// �����Ӱ��� ǥ�� ���� ���̺����� �̹����� �׷��ش�.
{
	
	CGObject::DrawFrame(m_x, m_y, Frame, lpSurface); // ������ǥ�� �̹����� �׸���.
}
			
