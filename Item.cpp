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
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval); // �ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time();	/// ���� ����ð����� �ִ´�.
	m_nMoveInterval = MoveInterval;// �������� ���ݰ��� �����Ѵ�.
}

void CItem::Move()
{
	if(!m_bIsLive)  return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{
		m_y += speed_y;	// ���� 8�� �ö󰣴�.
		m_x += speed_x;

		life++;

		if(life  > 700)
			m_bIsLive = false;



		switch(move)
		{
			case 1: //������ �� �밢��

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
		

		

		

		if(m_y>600 || m_y<-50 || m_x<-10 || m_x > 660)	// ȭ�� ������ ������ -100��ǥ�� �Ѿ�ٸ�
		{
			m_bIsLive = false;// �׿��ش�.
		}
	}
}

void CItem::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// �̹����� �׸��� ǥ���� �����ش�
{
	CGObject::Draw(m_x, m_y, lpSurface);	// �ش� ��ǥ�� �̹����� �׷��ش�.
}

void CItem::DrawMissile(int set_x, int set_y, LPDIRECTDRAWSURFACE7 lpSurface, int Frame)// �����Ӱ��� ǥ�� ���� ���̺����� �̹����� �׷��ش�.
{
	
	CGObject::DrawFrame(set_x, set_y, Frame, lpSurface); // ������ǥ�� �̹����� �׸���.
}
			
void CItem::Kill()
{	
	CGObject::Kill();
}

void CItem::DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface, int Frame)
{
	CGObject::DrawFrame(m_x, m_y, Frame, lpSurface); 
}
