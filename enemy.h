//enemy.h
// class CEnemy
#ifndef __enemy_h__
#define __enemy_h__

#include "gobject.h"
#include "define.h"

class CEnemy : public CGObject
{
private:
	int		m_nLastMoveTime; // ���������� ������ �ð�
	int		m_nMoveInterval; // �������� �ð� ����
public:
	int		m_speedx;	// x�� ���ǵ�
	int		m_speedy;	// y�� ���ǵ�
	bool	kill;

	int		life;
	int		score;

public:
	CEnemy();	// ������
	~CEnemy();	// �Ҹ���
	void Initialize( CSprite *pSprite, int x, int y, CTimer *timer, int CurrentFrame,
					int FrameInterval, int MoveInterval, int enemy); // �ʱ�ȭ
	void Draw( LPDIRECTDRAWSURFACE7 lpSurface);	// �� �׸���
//	void DrawMissile( LPDIRECTDRAWSURFACE7 lpSurface);	// �� �̻��� �׸���
//	void CreateMissile();	// �� �̻��� ����
	void Move(int flag);	// �� �̵� �Լ�
	void Kill();

	int after_x, after_y;
	int drawframe;
	int sprite;

	int check_x, check_y;
	int m_position;

	void DrawFrame(LPDIRECTDRAWSURFACE7 lpSurface);

	

};
#endif