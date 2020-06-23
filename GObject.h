//gobject.h
//class CGObject

#ifndef __gobject_h__	// ������ ������Ϸθ� ���ٰ� ��
#define __gobject_h__	// ��������� ������ �ʴ´�.

#include "sprite.h"	// ��������Ʈ ��� �� �����´�.
#include "timer.h"	// Ÿ�̸� ����� �����´�.
#include <ddraw.h>	// ���̷�Ʈ ��ο� ����� �����´�.

class CGObject	// Ŭ���� ����
{
public:
	int			m_x;  // ������Ʈ�� �߽� x��ǥ
	int			m_y;  // ������Ʈ�� �߽� y��ǥ
protected:
	CSprite		*m_pSprite;		// ��������Ʈ�� �ּҰ��� ��Ÿ��
	int			m_nFrameInterval;	// ������ �ð� ����
	int			m_nCurrentFrame;	// ���� ȭ��� ��Ÿ�� ������ ��ȣ
	int			m_nLastFrameTime;	// ���������� �������� �׸� �ð�
	CTimer		*m_pTimer;		// ���� Ÿ�̸��� �ּ�
	bool		m_bIsLive;		// ������Ʈ�� ����ִ°��� ��Ÿ��
public:
	CGObject();	// ������
	~CGObject();	// �Ҹ���
	void Initialize(CSprite *pSprite, int x, int y, CTimer *timer,	// �ʱ�ȭ �Լ� Ÿ�̸��� ���۰� �������� ����
					int CurrentFrame, int FrameInterval);
	void Draw( int x, int y, LPDIRECTDRAWSURFACE7 lpSurface);		// 
	void DrawFrame( int x, int y, int nFrame, LPDIRECTDRAWSURFACE7 lpSurface);	// 
	bool IsLive();	// ��ü�� ����ֳ�?
	void Kill();	// ��ü�� ����
	int GetX();	// x��ǥ ��ȯ
	int GetY();	// y��ǥ ��ȯ

	void ChangeSprite(CSprite *pSprite);
	void ItemDrawing(int nFrame, int x, int y, int p_x, int s_x, LPDIRECTDRAWSURFACE7 pSurface, bool bUsingColorKey);
		//������ ��ο�
};

#endif
