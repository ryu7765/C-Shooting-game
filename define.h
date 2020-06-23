//define.h
// 각종 상수 값을 정의 한다.
// 각종 구조체 정의



#ifndef __define_h__
#define __define_h__

#include "bmp.h"				// 비트맵 파일을 불러오는 bmp헤더를 불러온다.
#include "timer.h"				// 타이머, 시간과 딜레이 역할 헤더파일을 불러온다.
#include "sprite.h"				// 스프라이트 관련 헤더파일을 불러 온다.
#include "enemy.h"				// 적관련 헤더 파일을 불러온다.
#include "myship.h"				// 플레이어 관련 헤더 파일을 불러온다.
#include "mymissile.h"			// 플레이어 미사일 관련 헤더 파일을 불러온다.
#include "exploding.h"			// 폭파 관련 헤더파일을 불러온다.
#include "enemymissile.h"		// 적 미사일 관련 헤더 파일을 불러온다.
#include "boss.h"				// 보스 관련 헤더 파일을 불러온다.
#include "bossmissile.h"		// 보스 미사일 관련 헤더 파일을 불러온다.
#include "assistmissile.h"
#include "item.h"

#define CLASS_NAME "DirectX02"

#define MAX_ENEMYS 20			// 최대 적의 수
#define MAX_PATTERN 30
#define MAX_ENEMY_MISSILES 60	// 적의 최대 미사일

#define MAX_BOSS 1				// 보스의 최대 수
#define MAX_BOSS_XMISSILE 3		// 보스의 x축 미사일 최대 수
#define MAX_BOSS_YMISSILE 5		// 보스의 y축 미사일 최대 수
#define MAX_LIFE 3 

#define BOSS_MISSILE_INTERVAL 100	// 보스 미사일의 딜레이

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
