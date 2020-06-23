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
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval); // �ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time();	/// ���� ����ð����� �ִ´�.
	m_nMoveInterval = MoveInterval;// �������� ���ݰ��� �����Ѵ�.
}

void CMyMissile::Move()
{
	if(!m_bIsLive)  return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{
		m_y -= speed_y;	// ���� 8�� �ö󰣴�.
		m_x += speed_x;

		if(m_y<-50 || m_x<-10 || m_x > 660)	// ȭ�� ������ ������ -100��ǥ�� �Ѿ�ٸ�
		{
			m_bIsLive = false;// �׿��ش�.
		}
	}
}

void CMyMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// �̹����� �׸��� ǥ���� �����ش�
{
	CGObject::Draw(m_x, m_y, lpSurface);	// �ش� ��ǥ�� �̹����� �׷��ش�.
}

void CMyMissile::DrawMissile(int set_x, int set_y, LPDIRECTDRAWSURFACE7 lpSurface, int Frame)// �����Ӱ��� ǥ�� ���� ���̺����� �̹����� �׷��ش�.
{
	
	CGObject::DrawFrame(set_x+20, set_y, Frame, lpSurface); // ������ǥ�� �̹����� �׸���.
	CGObject::DrawFrame(set_x-20, set_y, Frame, lpSurface); // ������ǥ�� �̹����� �׸���.
	CGObject::DrawFrame(set_x, set_y, Frame, lpSurface); // ������ǥ�� �̹����� �׸���.
}
			
void CMyMissile::Kill()
{	
	CGObject::Kill();
}