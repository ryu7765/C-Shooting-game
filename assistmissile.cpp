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
	CGObject::Initialize(pSprite, x, y, timer, CurrentFrame, FrameInterval); // �ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
	m_nLastMoveTime = timer->time();	/// ���� ����ð����� �ִ´�.
	m_nMoveInterval = MoveInterval;// �������� ���ݰ��� �����Ѵ�.
}

void CAssistMissile::Move(int t_x)
{
	if(!m_bIsLive)  return;	// �׾��ִٸ� �׳� ����

	if(m_pTimer->elapsed(m_nLastMoveTime, m_nMoveInterval))// ���ӽ���ð��� ������ ���� ��ŭ ��������
	{
		if(type == 1)
		{
			m_y -= ((speed_y++)/3);	// ���� 8�� �ö󰣴�.
			
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

		if(m_y<-15 || m_x<-5 || m_x > 655)	// ȭ�� ������ ������ -100��ǥ�� �Ѿ�ٸ�
		{
			m_bIsLive = false;// �׿��ش�.
		}
	}
}

void CAssistMissile::Draw(LPDIRECTDRAWSURFACE7 lpSurface)// �̹����� �׸��� ǥ���� �����ش�
{
	CGObject::Draw(m_x, m_y, lpSurface);	// �ش� ��ǥ�� �̹����� �׷��ش�.
}

void CAssistMissile::DrawMissile(int set_x, int set_y, LPDIRECTDRAWSURFACE7 lpSurface, int Frame)// �����Ӱ��� ǥ�� ���� ���̺����� �̹����� �׷��ش�.
{
	CGObject::DrawFrame(set_x, set_y, Frame, lpSurface); // ������ǥ�� �̹����� �׸���.
}
			
void CAssistMissile::Kill()
{	
	targetOn = false;
	CGObject::Kill();
}