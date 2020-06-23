//gobject.h
//class CGObject

#ifndef __gobject_h__	// 무조건 헤더파일로만 쓴다고 함
#define __gobject_h__	// 백업파일을 만들지 않는다.

#include "sprite.h"	// 스프라이트 헤더 를 가져온다.
#include "timer.h"	// 타이머 헤더를 가져온다.
#include <ddraw.h>	// 다이렉트 드로우 헤더를 가져온다.

class CGObject	// 클래스 선언
{
public:
	int			m_x;  // 오브젝트의 중심 x좌표
	int			m_y;  // 오브젝트의 중심 y좌표
protected:
	CSprite		*m_pSprite;		// 스프라이트의 주소값를 나타냄
	int			m_nFrameInterval;	// 프레임 시간 간격
	int			m_nCurrentFrame;	// 현재 화면상에 나타난 프레임 번호
	int			m_nLastFrameTime;	// 마지막으로 프레임을 그린 시간
	CTimer		*m_pTimer;		// 전역 타이머의 주소
	bool		m_bIsLive;		// 오브젝트가 살아있는가를 나타냄
public:
	CGObject();	// 생성자
	~CGObject();	// 소멸자
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer,	// 초기화 함수 타이머의 시작과 프레임을 설정
					int CurrentFrame, int FrameInterval);
	void Draw( int x, int y, LPDIRECTDRAWSURFACE7 lpSurface);		// 
	void DrawFrame( int x, int y, int nFrame, LPDIRECTDRAWSURFACE7 lpSurface);	// 
	bool IsLive();	// 개체가 살아있나?
	void Kill();	// 개체를 죽임
	int GetX();	// x좌표 반환
	int GetY();	// y좌표 반환

	void ChangeSprite(CSprite *pSprite);
	void ItemDrawing(int nFrame, int x, int y, int p_x, int s_x, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey);
		//아이템 드로우
};

#endif
