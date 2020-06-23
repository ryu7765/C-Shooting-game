//boss.cpp
//class CBoss

#include "boss.h"

CBoss::CBoss()	// ������
{
	m_speedx=2;		// ���� Ŭ���� ������ ���ǵ带 2�� ���ش�.
}

CBoss::~CBoss()	// �Ҹ���
{
}

void CBoss::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval)	// �ʱ�ȭ �Լ� ��ǥ ���� �����ϰ� 
{																// �ð��� ������ �������ش�.
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);	// �ʱ�ȭ
	m_nLastMoveTime = timer->time();	// �ð� ����
	m_nMoveInterval = MoveInterval;	// ���ݰ� ����
	m_myx= m_x; // ������Ʈ �߽��� x��ǥ�� myx�� �ִ´�.
}

void CBoss::Move()
{
	if(!m_bIsLive) return;	// ������� �ʴٸ� ����

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))	// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{
		//if(m_x<50) { m_speedx = 2;}
		//if(m_x>750) { m_speedx= -2;}
		//m_x +=m_speedx;
	}
}

void CBoss::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// �̹����� �׸��� ǥ���� �����ش�
{
	CGObject::Draw(m_x, m_y, lpSurface);	// �ش� ��ǥ�� �̹����� �׷��ش�.
}