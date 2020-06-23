//define.h
// ���� ��� ���� ���� �Ѵ�.
// ���� ����ü ����



#ifndef __define_h__
#define __define_h__

#include "bmp.h"				// ��Ʈ�� ������ �ҷ����� bmp����� �ҷ��´�.
#include "timer.h"				// Ÿ�̸�, �ð��� ������ ���� ��������� �ҷ��´�.
#include "sprite.h"				// ��������Ʈ ���� ��������� �ҷ� �´�.
#include "enemy.h"				// ������ ��� ������ �ҷ��´�.
#include "myship.h"				// �÷��̾� ���� ��� ������ �ҷ��´�.
#include "mymissile.h"			// �÷��̾� �̻��� ���� ��� ������ �ҷ��´�.
#include "exploding.h"			// ���� ���� ��������� �ҷ��´�.
#include "enemymissile.h"		// �� �̻��� ���� ��� ������ �ҷ��´�.
#include "boss.h"				// ���� ���� ��� ������ �ҷ��´�.
#include "bossmissile.h"		// ���� �̻��� ���� ��� ������ �ҷ��´�.
#include "assistmissile.h"
#include "item.h"

#define CLASS_NAME "DirectX02"

#define MAX_ENEMYS 20			// �ִ� ���� ��
#define MAX_PATTERN 30
#define MAX_ENEMY_MISSILES 60	// ���� �ִ� �̻���

#define MAX_BOSS 1				// ������ �ִ� ��
#define MAX_BOSS_XMISSILE 3		// ������ x�� �̻��� �ִ� ��
#define MAX_BOSS_YMISSILE 5		// ������ y�� �̻��� �ִ� ��
#define MAX_LIFE 3 

#define BOSS_MISSILE_INTERVAL 100	// ���� �̻����� ������

#define MAX_MISSILES 200
#define MAX_ASSIST   50
#define MAX_EXPLODES 251

#define MAX_BOSS_XMISSILES 3
#define MAX_BOSS_YMISSILES 5
#define BUFSIZE	512
#define MAX_LIFE 3

#define	GAMEMENU	1000	
#define	SINGPLAY	1001	
#define MULTYPLAY	1002	
#define	ABOUT		1003	
#define CREATOR		1004	
#define	EXIT		1005	



const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int COLOR_DEPTH = 32;

const int COLOR_KEY = 0;
const int SHIP_COLOR_KEY = 0x00F800;
const int WHITE_COLOR_KEY = 0xFFFFFF;
const int GREEN_COLOR_KEY = 0x84FF00;

struct CPlayer
{
	unsigned int GameState;
	unsigned int End;
	unsigned int GameStart;
	unsigned int MiniMapX;
	unsigned int MiniMapY;
	unsigned int score;
};

extern CPlayer Player[2];


#endif
