//GObject.cpp
//class CGObject

#include "gobject.h"		// ������ �Ǿ��ִ� ��� ���� ����


CGObject::CGObject()		// ������
{
	m_nCurrentFrame = 0;	// �����ɶ� ���� ������ 0����
	m_bIsLive = false;		// ��ü�� �׾��ִٰ� ����
}

CGObject::~CGObject()	// �Ҹ���
{
}

void CGObject::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval)	// �ʱ�ȭ �Լ� 
{
	m_pSprite = pSprite;		// ��������Ʈ�� �ʱ�ȭ
	m_nCurrentFrame = CurrentFrame;	// ���� ������ �ʱ�ȭ
	m_x = x;		// x���� �ʱ�ȭ
	m_y = y;		// y���� �ʱ�ȭ
	m_nFrameInterval = FrameInterval;	// ������ ������ �ʱ�ȭ
	m_bIsLive = true;	// ��ü�� ����ִٰ� �ʱ�ȭ
	m_pTimer = timer;	// �ð��� �ʱ�ȭ
	m_nLastFrameTime = m_pTimer->time();	// ������ ����ð��� �ʱ�ȭ �Ѵ�.
}

bool CGObject::IsLive()		// �ʱ�ȭ �� ����ִٰ� ������
{
	return m_bIsLive;		// ���� ��Ȳ�� ��ȯ
}

void CGObject::Kill()		// �ɸ��͸� ���δ�.
{
	m_bIsLive = false;		// ���� ���� �޽���
}

void CGObject::Draw( int x, int y, LPDIRECTDRAWSURFACE7 lpSurface)	// �̹��� �׸���
{
	if(!m_bIsLive) return;		// ��ü�� �׾������� �ٽ� �ǵ��ư���.

	if(m_pTimer->elapsed(m_nLastFrameTime, m_nFrameInterval))	// ���ӽ���ð��� ������ ���� ��ŭ �����ٸ� ���������� �׳� �̹���..
		m_nCurrentFrame = ++m_nCurrentFrame % m_pSprite->GetNumberOfFrame();	// ����ð��� ������Ű�� �������Ӽ� ��ŭ �������� �����Ѵ�.
	m_pSprite->Drawing(m_nCurrentFrame, m_x, m_y, lpSurface);// �̹����� �׷��ش�.
}

void CGObject::DrawFrame( int x, int y, int nFrame, LPDIRECTDRAWSURFACE7 lpSurface)	
{
	if(!m_bIsLive) return;		// ��ü�� �׾������� �ٽ� �ǵ��ư���.

	if(nFrame >= m_pSprite->GetNumberOfFrame())	  //nFrame�� �� ������ ������ ũ�ų� ���ٸ�
		nFrame = m_pSprite->GetNumberOfFrame()-1;	// nFrmae�� �������� -1;
	if(nFrame < 0)	//�ƴϸ�
		nFrame = 0;	// 0����..   �ִ��ּҸ� �Ѿ�� �ʵ���

	m_pSprite->Drawing(nFrame, m_x, m_y, lpSurface);	// �̹����� �׸���.
}

int CGObject::GetX()	// ���� x���� ��ȯ
{
	return m_x;
}

int CGObject::GetY()	// ���� y���� ��ȯ
{
	return m_y;
}

void CGObject::ChangeSprite(CSprite *pSprite)
{
	m_pSprite = pSprite;
}

void CGObject::ItemDrawing(int nFrame, int x, int y, int p_x, int s_x, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey)
{
	m_pSprite->ItemDrawing(nFrame, x, y, p_x, s_x, pSurface, bUsingColorKey);	// �̹����� �׸���.
}