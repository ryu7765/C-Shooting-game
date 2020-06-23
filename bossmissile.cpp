//bossmissile.cpp
//Class BossMissile

#include "bossmissile.h"

CBossMissile::CBossMissile()
{
	m_speedx=2;	// ���������� speed�� 2��
}

CBossMissile::~CBossMissile()
{
}

void CBossMissile::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, 
						int FrameInterval, int MoveInterval)
{
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval);// �ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time();// ���� ����ð����� �ִ´�.
	m_nMoveInterval = MoveInterval; // �������� ���ݰ��� �����Ѵ�.
}

void CBossMissile::Move()
{
	if(!m_bIsLive) return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))	// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{
		m_x += m_speedx;	// ���ǵ常ŭ x���� ������Ų��.
		m_y += 5;		// y���� 5�� ������Ų��.

		if(m_y>600)// ������Ʈ�� 600 �� �Ѿ��
		{
			m_bIsLive = false;// ���δ�.
		}
	}
}

void CBossMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// �̹����� �׸��� ǥ���� �����ش�
{
	CGObject::Draw(m_x, m_y, lpSurface);	// �ش� ��ǥ�� �̹����� �׷��ش�.
}