//GObject.cpp
//class CGObject

#include "gobject.h"		// 선언이 되어있는 헤더 파일 선언


CGObject::CGObject()		// 생성자
{
	m_nCurrentFrame = 0;	// 생성될때 현재 프레임 0으로
	m_bIsLive = false;		// 개체가 죽어있다고 선언
}

CGObject::~CGObject()	// 소멸자
{
}

void CGObject::Initialize(CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame, int FrameInterval)	// 초기화 함수 
{
	m_pSprite = pSprite;		// 스프라이트를 초기화
	m_nCurrentFrame = CurrentFrame;	// 현재 프래임 초기화
	m_x = x;		// x값을 초기화
	m_y = y;		// y값을 초기화
	m_nFrameInterval = FrameInterval;	// 프레임 간격을 초기화
	m_bIsLive = true;	// 개체가 살아있다고 초기화
	m_pTimer = timer;	// 시간을 초기화
	m_nLastFrameTime = m_pTimer->time();	// 게임의 실행시간을 초기화 한다.
}

bool CGObject::IsLive()		// 초기화 후 살아있다고 되잇음
{
	return m_bIsLive;		// 현재 상황을 반환
}

void CGObject::Kill()		// 케릭터를 죽인다.
{
	m_bIsLive = false;		// 현재 값을 펄스로
}

void CGObject::Draw( int x, int y, LPDIRECTDRAWSURFACE7 lpSurface)	// 이미지 그리기
{
	if(!m_bIsLive) return;		// 개체가 죽어있으면 다시 되돌아간다.

	if(m_pTimer->elapsed(m_nLastFrameTime, m_nFrameInterval))	// 게임실행시간이 프레임 간격 만큼 지낫다면 안지낫으면 그냥 이미지..
		m_nCurrentFrame = ++m_nCurrentFrame % m_pSprite->GetNumberOfFrame();	// 실행시간을 증가시키고 총프레임수 만큼 나눈값을 대입한다.
	m_pSprite->Drawing(m_nCurrentFrame, m_x, m_y, lpSurface);// 이미지를 그려준다.
}

void CGObject::DrawFrame( int x, int y, int nFrame, LPDIRECTDRAWSURFACE7 lpSurface)	
{
	if(!m_bIsLive) return;		// 개체가 죽어있으면 다시 되돌아간다.

	if(nFrame >= m_pSprite->GetNumberOfFrame())	  //nFrame이 총 프레임 수보다 크거나 같다면
		nFrame = m_pSprite->GetNumberOfFrame()-1;	// nFrmae을 총프레임 -1;
	if(nFrame < 0)	//아니면
		nFrame = 0;	// 0으로..   최대최소를 넘어가지 않도록

	m_pSprite->Drawing(nFrame, m_x, m_y, lpSurface);	// 이미지를 그린다.
}

int CGObject::GetX()	// 현재 x값을 반환
{
	return m_x;
}

int CGObject::GetY()	// 현재 y값을 반환
{
	return m_y;
}

void CGObject::ChangeSprite(CSprite *pSprite)
{
	m_pSprite = pSprite;
}

void CGObject::ItemDrawing(int nFrame, int x, int y, int p_x, int s_x, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey)
{
	m_pSprite->ItemDrawing(nFrame, x, y, p_x, s_x, pSurface, bUsingColorKey);	// 이미지를 그린다.
}