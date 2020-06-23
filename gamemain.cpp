//gamemain.cpp
#include <ddraw.h>				// 다이렉트 드로우(페인트) 헤더 파일을 불러온다.
#include <dinput.h>				// 다이렉트 인풋(입력) 헤더 파일을 불러온다.

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
#include "object.h"

#include "define.h"

#include "stdio.h"				// 문자열 입출력 관련 헤더 파일을 불러온다.
#include <windows.h>			// 윈도우즈 관련 헤더 파일을 불러온다.

#include <dsound.h>				// 다이렉트 사운드(사운드) 헤더파일을 불러온다.
#include "dsutil.h"				// 

#include <math.h>



// 함수원형 선언 ///////////////////////////////////////////////////
BOOL DirectInputKeyboardDown( LPDIRECTINPUTDEVICE8 lpKeyboard, int dikcode);	// 키보드 입력받는 함수
////////////////////////////////////////////////////////////////////

// 외부변수 선언 ///////////////////////////////////////////////////
extern LPDIRECTDRAWSURFACE7		g_lpPrimarySurface;			// 1차, 2차 표면
extern LPDIRECTDRAWSURFACE7		g_lpSecondarySurface;
extern LPDIRECTINPUT8			g_lpDirectInputObject;		// 입력을 담당하기 위한 전역 변수
extern LPDIRECTINPUTDEVICE8		g_lpDirectInputKeyboard;	// 키보드에서 받아온 값을 처리하기 위한 전역변수
extern CTimer					g_Timer;				// 타이머 변수

extern CSprite			g_BackgroundSprite;		// 배경 스프라이트
extern CSprite			g_State;
extern CBossMissile		g_BossMissile[MAX_BOSS_YMISSILE][MAX_BOSS_XMISSILE];	// 보스 미사일의 배열
extern CSprite			g_BossMissileSprite;			// 보스 미사일 과 보스
extern CBoss			g_Boss[MAX_BOSS];
extern CSprite			g_BossSprite;

extern CEnemyMissile	g_EnemyMissile[MAX_PATTERN][MAX_ENEMYS][MAX_ENEMY_MISSILES];	// 적 미사일의 배열
extern CSprite			g_EnemyMissileSprite[10];		// 적 미사일 스프라이트
extern CEnemy			g_Enemy[MAX_PATTERN][MAX_ENEMYS];	// 적기들의 배열
extern CSprite			g_EnemySprite[10];	// 적의 스프라이트

extern CMyShip			g_MyShip;		// 플레이어
extern CSprite			g_MyShipSprite;	// 플레이어 스프라이트
extern CMyMissile		g_MyMissile[MAX_MISSILES];	// 내 미사일의 배열
extern CSprite			g_MyMissileSprite[3];	// 내 미사일의 스프라이트
extern CSprite			g_MyLifeSprite;

extern CExploding		g_Exploding[MAX_EXPLODES];		// 폭파 처리 배열
extern CSprite			g_ExplodingSprite[2];		// 폭파 스프라이트

extern CSprite			g_AssistMissileSprite[2];
extern CAssistMissile	g_AssistMissile[MAX_ASSIST];

extern CSprite			g_WinSprite;		// 게임 성공시 스프라이트
extern CSprite			g_LoseSprite;		// 게임 실패시 스프라이트 
extern CSprite			g_DrawSprite;		// 게임 비겼을시 스프라이트 
extern CSprite			g_BoardSprite;
extern CSprite			g_SingleBoardSprite;

extern CSprite			g_AttackSprite;
extern CExploding		g_Attack[2];
extern CSprite			g_Score;
extern CSprite			g_InitMyShipSprite;
extern CSprite			g_MissileItemSprite;
extern CSprite			g_ItemSprite;
extern CItem			g_Item[8];
extern CObject			g_Object;

extern CSprite			g_MissileExplodingSprite;
extern CSprite			g_AssistMissileExplodingSprite;

extern CSprite			g_GameMenuSprite;	
extern CSprite			g_SelectGameButton;		 
extern CSprite			g_WaitC2Player;	
extern CSprite			g_ConnectC2Player;	
extern CSprite			g_MiniMapSprite;

extern CSprite			g_ShieldSprite;
extern CSprite			g_TutorialSprite;

extern CSprite			g_IslandSprite;

extern HSNDOBJ Sound[10];			// 사운드 배열
extern void _Play(int num);			// 사운드 플레이 함수

extern int				attack_item;

static BOOL m_bGameFirst = TRUE;		// 게임 초기 
static BOOL m_bGameDead  = FALSE;		// 게임 실패
//static BOOL m_bGameClear = FALSE;		// 게임 성공
static BOOL m_bBoss		 = FALSE;		// 보스
static BOOL m_bInitMyShip = true;		// 뱅기 죽고나서 체크

CPlayer Player[2];


int flag = 0, bgflag = 0;	// 적 패턴
int item[3];
extern int lazer_x;
extern int GameStart;
//char wtime[1];	// 시작부터 맵끝까지가는 시간

static char szReplay[] = "You Dead... Replay? (y/n)";	// 졌을때 메시지
static char szWin[]	   = "You Win... Replay? (y/n)";	// 이겼을때 메시지

void InitGame();		// 게임 초기화 함수
void InitInterface();	// 인터페이스 초기화
void MyShipItemCheck();	//아이템 체크
void MyShipCheck();
void IntToArray(int num,int ar[],int s);
void MyMissile(bool flag);
void MyShipInit();
int MissileCheck(bool assist = false);
int ExplodingCheck();
int ItemCheck(bool move = false);
int MissileAttack_Check(int m);
bool TimerCheck(int &timer, int time, int type);
void AssistMissile(bool flag);
void InitEnemy(int m);
void EnemyRotate(int i, int j);
int EnemyMissileCheck(int i, int j);
void GameEnd();



//extern void MainMenu();
void InputKey();	
void Draw();
void Collision();
typedef enum
{
	DEFAULT,	//일반
	SLOW,	//느리게
	FAST,	//빠르게
	SHIELD,	//쉴드
	CHANGE,	//적의 움직임을 반대로
	MISSILE,	//자신과 같은 위치에 미사일 폭격
	STOP,	//일시정지
	ENEMY,	//적 랜덤 생성
	POWER_D,	//상대방 파워 다운
	POWER_U
}ITEM_U;

typedef enum
{	
	RED,	//범위 일직 미사일 약한거
	GREEN,	//범위와 일직 사이정도 유도미사일 아주 약한거 딜레이 많음
	BLUE,	//일직선 일직 미사일 강한거
	LIFE	//라이프
}ITEM_D;



int nItemTime[10];
static int nMissileTime = g_Timer.time();
static int A_nMissileTime = g_Timer.time();
int MY_MISSILE_INTERVAL[3];		// 내 미사일의 딜레이
int A_MY_MISSILE_INTERVAL[2];
int MAX_MISSILE[3];				// 내 미사일 최대
int MISSILE_DELAY[3];			// 미사일 쏘고 나서 멈추는 딜레이

int A_MAX_MISSILE[2];
int A_MISSILE_DELAY[2];

int single;
extern int wow;

int EnemyLife[MAX_PATTERN];

bool bItem[10];
bool bItemMissile = true;
int ScoreArray[5];
int item_check=0;

extern int SelectGameX, SelectTemp;
extern int AboutTemp;
extern int g_GameMunu;

extern int MyShipFrame;
extern int isMyMissile;


int STAGE = 1;
int STAGEEXP = 0;

int TimerCheck_item[5];
int TimerCheck_temp = 0;

int timevar=0;
int attack_check = 0;
void MainMenu(void)		//게임 메인
{
	static int inputkey = g_Timer.time();

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,300))
		{
			SelectTemp++;
			if(SelectTemp==5)
				SelectTemp=0;
			switch(SelectTemp)
			{
			case 0:	SelectGameX=283;	break;
			case 1:	SelectGameX=343;	break;
			case 2:	SelectGameX=403;	break;
			case 3:	SelectGameX=463;	break;
			case 4:	SelectGameX=523;	break;
			}
		}
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP))		// 위쪽으로
	{
		if(g_Timer.elapsed(inputkey,300))
		{
			SelectTemp--;
			if(SelectTemp==-1)
				SelectTemp=4;
			switch(SelectTemp)
			{
			case 0:	SelectGameX=283;	break;
			case 1:	SelectGameX=343;	break;
			case 2:	SelectGameX=403;	break;
			case 3:	SelectGameX=463;	break;
			case 4:	SelectGameX=523;	break;
			}
		}
	}


	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,300))
		{
			AboutTemp--;
			if(AboutTemp==0)
				AboutTemp=4;
		}
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT))		// 위쪽으로
	{
		if(g_Timer.elapsed(inputkey,300))
		{
			AboutTemp++;
			if(AboutTemp==5)
				AboutTemp=1;
		}
	}


	switch(g_GameMunu)
	{
	case GAMEMENU:
		g_GameMenuSprite.Drawing( 0, 400,300, g_lpSecondarySurface, false);
		g_SelectGameButton.Drawing( SelectTemp, 280, SelectGameX, g_lpSecondarySurface, false);
		break;
	case SINGPLAY:
		single = true;
		GameStart = 1;
		m_bGameFirst=TRUE;
		break;
	case MULTYPLAY:
		single = false;
		m_bGameFirst=TRUE;
		if(Player[1].GameState==1)
			g_ConnectC2Player.Drawing( 0, 400,300, g_lpSecondarySurface, false);
		else if(Player[1].GameState==0)
			g_WaitC2Player.Drawing( 0, 400,300, g_lpSecondarySurface, false);
		
		break;
	case ABOUT:
		g_TutorialSprite.Drawing( AboutTemp-1, 400,300, g_lpSecondarySurface, false);		
		break;
	case CREATOR:
		break;
	case EXIT:
		break;
	}

	HRESULT hResult;				// 플리핑 관련
	if(FAILED(hResult = g_lpPrimarySurface->Flip(NULL,DDFLIP_WAIT)))	
	{
		if(hResult == DDERR_SURFACELOST)	// 다이렉트 드로우가 에러가 나면 다시 
			g_lpPrimarySurface->Restore();
	}
}

void GameMain(void)		//게임 메인
{
//	wtime[1] = g_Timer.time();



	

	if(m_bGameFirst==TRUE) InitGame();	// 게임초기 초기화 함수 호출

	int i, j, m, m2;	// 제어 변수
	


	static int time = 0;		// 타임을 0으로
	static int nLastMissileTime = g_Timer.time();
	static int nLastMissileTime2 = g_Timer.time();

	static int A_nLastMissileTime = g_Timer.time();



	if(bgflag == 0)
		g_BackgroundSprite.Drawing2( 0, 0, g_lpSecondarySurface, false);  // 배경 스프라이트를 그린다
	if(bgflag == 1)
		g_BackgroundSprite.Drawing2( 0, 1, g_lpSecondarySurface, false);

	if(rand()%700 == 0 && !g_Object.IsLive())
	{
		g_Object.Initialize(&g_IslandSprite, 115 + rand()%530, -100, &g_Timer, 0, 50);
	}

	if(g_Object.IsLive())
	{
		g_Object.m_y++;
		g_Object.DrawFrame(g_lpSecondarySurface, 0);
		if(g_Object.m_y > 700)
			g_Object.Kill();
	}



	
	

	
	Draw();
	Collision();	
	InputKey();	
	MyShipItemCheck();		//아이템 체크 
	MyShipCheck();			//체크한 아이템 수행
	MyMissile(false);
	AssistMissile(false);	

	if(m_bInitMyShip)
		MyShipInit();
	


	if(bItem[MISSILE] && g_MyShip.IsLive() && !bItem[SHIELD])	
	{
		if( abs(g_MyShip.GetX() - g_Attack[1].GetX()) < 15 )	
		{
			g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_MyShip.GetX(),	// 폭파 초기화 
				g_MyShip.GetY(), &g_Timer, 0, 10);		// 위치설정
		
			

			if(g_MyShip.life>0)	
			{
				g_MyShip.life--;
				m_bInitMyShip = true;

				if(g_MyShip.life==0)
				{
					m_bInitMyShip = false;
				}
			}			

			g_MyShip.Kill();

			
			_Play(2);		// 2번 사운드 출력
		}
	}
	
	

//	bgflag = 1;

	if(m_bBoss == TRUE)		// 보스 트루시
	{
		//Boss
		for( i=0 ; i<MAX_BOSS ; i++ ) // 최대 보스 만큼
		{
			if(g_Boss[i].IsLive())		// 보스가 살아있다면
			{
				//g_Boss[i].Move();
				if( (g_MyShip.GetX() - g_Boss[i].GetX()) >  30 ) g_Boss[i].m_speedx = 2;	// 보스가 플레이어 보다 왼쪽에 있다면 스피드를 오른쪽으로
				if( (g_MyShip.GetX() - g_Boss[i].GetX()) < -30 ) g_Boss[i].m_speedx = -2;	// 오른쪽에 있다면 스피드를 왼쪽으로
				g_Boss[i].m_x += g_Boss[i].m_speedx;	// 보스의 x좌표를 speed값을 더해 움직인다.

				g_Boss[i].Draw( g_lpSecondarySurface);		// 보스를 그린다.
			}

			for( m=0 ; m<MAX_BOSS_YMISSILE ; m++)		// 보스 미사일의 y축만큼
			{
				if( time % 51 == 0)	// 타임을 나눈 나머지 값이 0이라면 ( 일종의 딜레이 )
				{
					for( m2=0 ; m2<MAX_BOSS_XMISSILE ; m2++ )	// 보스 미사일의 x축만큼
					{


						if( !g_BossMissile[m][m2].IsLive()   &&   g_Boss[i].IsLive() )	// 보스 미사일이 없고 보스가 살아있을때
						{
							g_BossMissile[m][m2].Initialize( &g_BossMissileSprite, g_Boss[i].GetX(),	// 보스 미사일 을 초기화 보스의 위치를 보내 출력할곳의 위치를 잡아준다.
								g_Boss[i].GetY()+80, &g_Timer, 0, 10, 5 );
							g_BossMissile[m][0].m_speedx = 2;	// 총알 하나는 왼쪽으로 
							g_BossMissile[m][1].m_speedx = 0;	// 총알 하나는 그냥 아래로
							g_BossMissile[m][2].m_speedx = -2;	// 총알 하나는 오른쪽으로 
						}
					}
				}
				time++;	// 딜레이값 증가
			}
		}
	}

	//총알 발사
	if( DirectInputKeyboardDown (g_lpDirectInputKeyboard, DIK_X) )	// 스페이스를 눌렀다면
	{
		if(g_MyShip.IsLive() || g_MyShip.InitMyShip_y < 610)	//플레이어가 살아있다면
		{
			if(g_Timer.elapsed( nLastMissileTime, MY_MISSILE_INTERVAL[g_MyShip.type]))	// 미사일 쏘는 조건이 만족 됬다면
			{
				isMyMissile=1;
				if(g_Timer.missile_check >= MAX_MISSILE[g_MyShip.type])	// m이 최대 미사일 수까지 올랐다면
				{
					if(g_Timer.elapsed(nMissileTime, MISSILE_DELAY[g_MyShip.type]))
					{
						g_Timer.missile_check=0;
						
					}
								
				}
				
				else
				{
					

					g_Timer.missile_check++;

					MyMissile(true);			
					
					_Play(1);		// 1번 사운드 출력
				}
			}


			if(g_MyShip.missiletype>0)
			{
				if(g_Timer.elapsed( A_nLastMissileTime, A_MY_MISSILE_INTERVAL[g_MyShip.missiletype-1]))	// 미사일 쏘는 조건이 만족 됬다면
				{
					if(g_Timer.assist_missile_check >= A_MAX_MISSILE[g_MyShip.missiletype-1])	// m이 최대 미사일 수까지 올랐다면
					{
						if(g_Timer.elapsed(A_nMissileTime, A_MISSILE_DELAY[g_MyShip.missiletype-1]))
						{
							g_Timer.assist_missile_check=0;
							
						}
						
					}
					
					else
					{
						
						g_Timer.assist_missile_check++;
						
						AssistMissile(true);				
						
					}
				}
			}
			

			if(g_MyShip.type == 2 && g_MyShip.level == 4)
				wow++;
		}
	}

	
	for(i=0 ; i<MAX_PATTERN ; i++)
	{
		for(j=0; j<MAX_ENEMYS; j++)
		{
			if(g_Enemy[i][j].kill)
			{		
				g_Enemy[i][j].kill = false;
				
				if(!g_Item[ItemCheck(true)].IsLive() && rand()%5==0)
				{
					g_Item[ItemCheck(true)].type = rand()%15;
					if(g_Item[ItemCheck(true)].type < 11)
						g_Item[ItemCheck(true)].Initialize(&g_ItemSprite, g_Enemy[i][j].m_x, g_Enemy[i][j].m_y, &g_Timer, g_Item[ItemCheck(true)].type, 25, 5 , rand()%4+1);
					else if(g_Item[ItemCheck(true)].type < 14)
						g_Item[ItemCheck(true)].Initialize(&g_MissileItemSprite, g_Enemy[i][j].m_x, g_Enemy[i][j].m_y, &g_Timer, g_Item[ItemCheck(true)].type-10, 25, 5 , rand()%4+1);
					else
						g_Item[ItemCheck(true)].Initialize(&g_MyLifeSprite, g_Enemy[i][j].m_x, g_Enemy[i][j].m_y, &g_Timer, g_Item[ItemCheck(true)].type-10, 25, 5 , rand()%4+1);
					
					
				}

				if(i>5 && i<10)
				{
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=0;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=0;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=0;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=0;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
				}

				if(i>14 && i<19 && g_Enemy[i][j].sprite == 2)
				{
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
				}
			}
		}
	}
	


	
	for(i=0;i<5;i++)
	{
		if(rand()%300==1 && !g_Enemy[0][i].IsLive() && Player[0].End != 1)
		{
			InitEnemy(0);
			g_Enemy[0][i].Initialize(&g_EnemySprite[0], rand()%430+60, -100, &g_Timer, 0, 25, 5, 0);
			break;
		}
	}

	switch(STAGE)
	{
	case 1:
		timevar++;
		if(timevar==300)
		{
			InitEnemy(2);
			InitEnemy(3);
			for(i=0; i<5; i++)
			{
				g_Enemy[2][i].Initialize(&g_EnemySprite[0], 100, 650+(i*50), &g_Timer, 0, 25, 5, 0);
				g_Enemy[3][i].Initialize(&g_EnemySprite[0], 550, 650+(i*50), &g_Timer, 0, 25, 5, 0);
			}
		}
		else if(timevar==600)
		{
			InitEnemy(4);
			InitEnemy(5);
			for(i=0; i<5; i++)
			{
				g_Enemy[4][i].Initialize(&g_EnemySprite[1], -50-(i*80), 200, &g_Timer, 0, 25, 5, 1);
				g_Enemy[5][i].Initialize(&g_EnemySprite[1], 550+(i*80), 300, &g_Timer, 0, 25, 5, 1);
			}
		}
		else if(timevar==900)
		{
			InitEnemy(1);
			for(i=0; i<5; i++)
			{
				g_Enemy[1][i].Initialize(&g_EnemySprite[1], 200, -50-(i*50), &g_Timer, 0, 25, 5, 1);
				g_Enemy[1][i].m_position = 1;
				g_Enemy[1][i].m_speedy = 5;
				g_Enemy[1][i+5].Initialize(&g_EnemySprite[1], 420, -50-(i*50), &g_Timer, 0, 25, 5, 1);
				g_Enemy[1][i+5].m_position = 1;
				g_Enemy[1][i+5].m_speedy = 5;
			}
		}
		else if(timevar==1200)
		{
			InitEnemy(6);
			InitEnemy(7);
			for(i=0; i<5; i++)
			{
				g_Enemy[6][i].Initialize(&g_EnemySprite[2], 100, -50-(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[7][i].Initialize(&g_EnemySprite[2], 550, -50-(i*50), &g_Timer, 0, 25, 5, 2);
			}
		}
		else if(timevar==1500)
		{
			InitEnemy(1);
			for(i=0; i<5; i++)
			{
				g_Enemy[1][i].Initialize(&g_EnemySprite[7], 200, 650+(i*50), &g_Timer, 0, 25, 5, 7);
				g_Enemy[1][i].m_position = 2;
				g_Enemy[1][i].m_speedy = 5;
				g_Enemy[1][i+5].Initialize(&g_EnemySprite[7], 420, 650+(i*50), &g_Timer, 0, 25, 5, 7);
				g_Enemy[1][i+5].m_position = 2;
				g_Enemy[1][i+5].m_speedy = 5;
			}
		}
		else if(timevar==1800)
		{
			InitEnemy(8);
			InitEnemy(9);
			for(i=0; i<5; i++)
			{
				g_Enemy[8][i].Initialize(&g_EnemySprite[2], 100, 650+(i*80), &g_Timer, 0, 25, 5, 2);
				g_Enemy[9][i].Initialize(&g_EnemySprite[2], 550, 650+(i*80), &g_Timer, 0, 25, 5, 2);
			}
		}
		else if(timevar==2100)
		{
			InitEnemy(1);
			for(i=0; i<5; i++)
			{
				g_Enemy[1][i].Initialize(&g_EnemySprite[1], 200, -50-(i*50), &g_Timer, 0, 25, 5, 1);
				g_Enemy[1][i].m_position = 1;
				g_Enemy[1][i].m_speedy = 5;
			}
		}
		else if(timevar==2200)
		{
			InitEnemy(1);
			for(i=0; i<5; i++)
			{
				g_Enemy[1][i+5].Initialize(&g_EnemySprite[7], 300, 650+(i*50), &g_Timer, 0, 25, 5, 7);
				g_Enemy[1][i+5].m_position = 2;
				g_Enemy[1][i+5].m_speedy = 5;
			}
		}
		else if(timevar==2300)
		{
			InitEnemy(1);
			for(i=0; i<5; i++)
			{
				g_Enemy[1][i].Initialize(&g_EnemySprite[1], 400, -50-(i*50), &g_Timer, 0, 25, 5, 1);
				g_Enemy[1][i].m_position = 1;
				g_Enemy[1][i].m_speedy = 5;
			}
		}
		else if(timevar==2400)
		{
			InitEnemy(1);
			for(i=0; i<5; i++)
			{
				g_Enemy[1][i+5].Initialize(&g_EnemySprite[7], 500, 650+(i*50), &g_Timer, 0, 25, 5, 7);
				g_Enemy[1][i+5].m_position = 2;
				g_Enemy[1][i+5].m_speedy = 5;
			}
		}
		else if(timevar==2700)
		{
			InitEnemy(12);
			InitEnemy(13);
			for(i=0; i<5; i++)
			{
				g_Enemy[12][i].Initialize(&g_EnemySprite[2], 100, -50-(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[13][i].Initialize(&g_EnemySprite[2], 550, 650+(i*50), &g_Timer, 0, 25, 5, 2);
			}
		}
		else if(timevar==3000)
		{
			InitEnemy(6);
			InitEnemy(7);
			InitEnemy(8);
			InitEnemy(9);
			for(i=0; i<5; i++)
			{
				g_Enemy[6][i].Initialize(&g_EnemySprite[2], 100, -50-(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[7][i].Initialize(&g_EnemySprite[2], 550, -50-(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[9][i].Initialize(&g_EnemySprite[2], 250, 650+(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[8][i].Initialize(&g_EnemySprite[2], 400, 650+(i*50), &g_Timer, 0, 25, 5, 2);
			}
		}
		else if(timevar==3500)
		{
			InitEnemy(14);
			for(i=0; i<5; i++)
			{
				g_Enemy[14][i].Initialize(&g_EnemySprite[4], 90+(i*1*110), -50, &g_Timer, 0, 25, 5, 4);
			}

			g_Enemy[14][0].m_position = 1;
			g_Enemy[14][1].m_position = 2;
			g_Enemy[14][2].m_position = 3;
			g_Enemy[14][3].m_position = 2;
			g_Enemy[14][4].m_position = 1;
		}
		else if(timevar>3500)
			timevar=3502;
		break;



	case 2:
		timevar++;
		if(timevar==500)
		{
			InitEnemy(17);
			InitEnemy(18);
			for(i=0; i<5; i++)
			{
				g_Enemy[17][i].Initialize(&g_EnemySprite[1], 100, 0-(i*50), &g_Timer, 0, 25, 5, 1);
				g_Enemy[18][i].Initialize(&g_EnemySprite[1], 550, 0-(i*50), &g_Timer, 0, 25, 5, 1);
			}
		}
		else if(timevar==800)
		{
			InitEnemy(11);
			for(i=0; i<5; i++)
				g_Enemy[11][i].Initialize(&g_EnemySprite[1], 90+(i*1*110), 0, &g_Timer, 0, 25, 5, 1);
			g_Enemy[11][0].m_position = 3;
			g_Enemy[11][1].m_position = 2;
			g_Enemy[11][2].m_position = 1;
			g_Enemy[11][3].m_position = 2;
			g_Enemy[11][4].m_position = 3;
		}
		else if(timevar==1400)
		{
			InitEnemy(15);
			InitEnemy(16);
			for(i=0; i<5; i++)
			{
				g_Enemy[17][i].Initialize(&g_EnemySprite[2], 90, 0-(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[18][i].Initialize(&g_EnemySprite[2], 530, 0-(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[15][i].Initialize(&g_EnemySprite[2], 200, 0-(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[16][i].Initialize(&g_EnemySprite[2], 420,0-(i*50), &g_Timer, 0, 25, 5, 2);
			}
		}
		else if(timevar==1700)
		{
			InitEnemy(14);
			for(i=0; i<3; i++)
			{
				g_Enemy[14][i].Initialize(&g_EnemySprite[4], 90+(i*1*220), 0, &g_Timer, 0, 25, 5, 4);
				g_Enemy[14][i].m_position = 0;
			}
		}
		
		else if(timevar==1750)
		{
			for(i=0; i<2; i++)
			{
				g_Enemy[14][i+3].Initialize(&g_EnemySprite[4], 200+(i*1*220), 0, &g_Timer, 0, 25, 5, 4);
				g_Enemy[14][i+3].m_position = 0;
			}
		}
		else if(timevar==1800)
		{
			for(i=0; i<3; i++)
			{
				g_Enemy[14][i+5].Initialize(&g_EnemySprite[4], 90+(i*1*220), 0, &g_Timer, 0, 25, 5, 4);
				g_Enemy[14][i+5].m_position = 0;
			}
		}
		else if(timevar==2100)
		{
			InitEnemy(1);
			for(i=0; i<5; i++)
			{
				g_Enemy[1][i].m_position = 1;
				g_Enemy[1][i+5].m_position = 2;
				g_Enemy[1][i+10].m_position = 1;
				g_Enemy[1][i+15].m_position = 2;
				g_Enemy[1][i].Initialize(&g_EnemySprite[1], 145, 0-(i*50), &g_Timer, 0, 25, 5, 1);
				g_Enemy[1][i+5].Initialize(&g_EnemySprite[1], 255, 650+(i*50), &g_Timer, 0, 25, 5, 1);
				g_Enemy[1][i+10].Initialize(&g_EnemySprite[1], 365, 0-(i*50), &g_Timer, 0, 25, 5, 1);
				g_Enemy[1][i+15].Initialize(&g_EnemySprite[1], 475, 650+(i*50), &g_Timer, 0, 25, 5, 1);
			}
		}
		else if(timevar==2400)
		{
			InitEnemy(20);
			for(i=0; i<5; i++)
			{
				g_Enemy[20][i].m_position = i+1;
				g_Enemy[20][i].Initialize(&g_EnemySprite[2], 0, 0+(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[21][i].m_position = i+1;
				g_Enemy[21][i].Initialize(&g_EnemySprite[2], 650, 0+(i*50), &g_Timer, 0, 25, 5, 2);
			}
		}
		else if(timevar==2700)
		{
			InitEnemy(15);
			InitEnemy(16);
			InitEnemy(17);
			InitEnemy(18);
			for(i=0; i<5; i++)
			{
				g_Enemy[15][i].Initialize(&g_EnemySprite[2], 145, 0-(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[17][i].Initialize(&g_EnemySprite[2], 255, 0-(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[18][i].Initialize(&g_EnemySprite[2], 365, 0-(i*50), &g_Timer, 0, 25, 5, 2);
				g_Enemy[16][i].Initialize(&g_EnemySprite[2], 475, 0-(i*50), &g_Timer, 0, 25, 5, 2);
			}
		}
	
		else if(timevar==3000)
		{
			InitEnemy(14);
			g_Enemy[14][0].Initialize(&g_EnemySprite[5], 310, 0, &g_Timer, 0, 25, 5, 5);
			g_Enemy[14][0].m_position = 0;
			g_Enemy[14][0].m_speedy=3;
			
		}

		else if(timevar==3600)
		{
			InitEnemy(22);
			g_Enemy[22][0].Initialize(&g_EnemySprite[8], 310, 0, &g_Timer, 0, 25, 5, 5);
		}
		else if(timevar >= 3700)
		{
			timevar = 3700;
		}
		break;
	}
	
	

	



/*
	if(m_bGameClear == TRUE) g_ClearSprite.Drawing(0, 400, 300, g_lpSecondarySurface, true);	// 게임 이겻을때 이미지 출력
	if(m_bGameDead  == TRUE) g_DeadSprite.Drawing(0, 400, 300, g_lpSecondarySurface, true);		// 게임 졌을때 이미지 출력
*/

	GameEnd();


	//Flipping
	HRESULT hResult;				// 플리핑 관련
	if(FAILED(hResult = g_lpPrimarySurface->Flip(NULL,DDFLIP_WAIT)))	
	{
		if(hResult == DDERR_SURFACELOST)	// 다이렉트 드로우가 에러가 나면 다시 
			g_lpPrimarySurface->Restore();
	}
}


void Draw()
{
	static int time = 0;
	int i, j, m, m2, k;

	for(i=0;i<8;i++)
	{
		g_Item[i].Move();
		if(g_Item[i].type < 11)
			g_Item[i].DrawFrame(g_lpSecondarySurface, g_Item[i].type);
		else
			g_Item[i].DrawFrame(g_lpSecondarySurface, g_Item[i].type-11);
	}

	// 적 미사일 그리기
	for( i=0 ; i<MAX_PATTERN ; i++)
		for( j=0 ; j<MAX_ENEMYS ; j++)	// 적의 수만큼
			for(k=0; k<MAX_ENEMY_MISSILES ; k++)
				if(g_EnemyMissile[i][j][k].IsLive())	// 적의 미사일이 있을때
				{
				
					g_EnemyMissile[i][j][k].Move(g_MyShip.m_x, g_MyShip.m_y, i, j, k);	// 움직인후
				
					if(i != 23)
						g_EnemyMissile[i][j][k].Draw(g_lpSecondarySurface);	// 그린다.
					else
						g_EnemyMissile[i][j][k].DrawFrame(g_lpSecondarySurface);	// 그린다.
				}
				


	//적의 움직임 처리와 그리기
	for(i=0; i<MAX_PATTERN; i++)
	{
		for(j=0; j<MAX_ENEMYS; j++)
		{
			if(g_Enemy[i][j].IsLive())
			{
				g_Enemy[i][j].Move(i);
				if(g_Enemy[i][j].sprite == 0 || g_Enemy[i][j].sprite == 1 || g_Enemy[i][j].sprite == 2 || g_Enemy[i][j].sprite == 6)
					EnemyRotate(i,j);

				if( i != 23)
					g_Enemy[i][j].DrawFrame(g_lpSecondarySurface);
				else 
					g_Enemy[i][j].Draw(g_lpSecondarySurface);
			}

			if(i==0 || i==2 || i==3 || i==4 || i==5 )
			{
				int nansu = rand()%120;	// 랜덤으로 100까지의 수를 발생
				if(nansu == 1)		// 그수가 1이라면
				{
					if( !g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].IsLive()   &&   g_Enemy[i][j].IsLive() )	// 적미사일이 없고 적이 살아있다면
					{
						g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy = 6;
						g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[0], g_Enemy[i][j].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
							g_Enemy[i][j].GetY()+20, &g_Timer, 0, 100, 5);
						

					}
				}
			}
			else if(i==14)
			{
				if(STAGE==1)
				{
					int nansu = rand()%800;	// 랜덤으로 100까지의 수를 발생
					if(nansu == 1)		// 그수가 1이라면
					{/*
						for(m=0; m<5; m++)
						{
							if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive()   &&    g_Enemy[14][m].IsLive() )	// 적미사일이 없고 적이 살아있다면
							{
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = -2;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 4;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX()-20,	// 적 미사일 초기화 하고 위치를 잡아준다.
									g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
							}
							if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive()   &&    g_Enemy[14][m].IsLive() )	
							{
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = 0;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 4;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
									g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
							}
							if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive()   &&    g_Enemy[14][m].IsLive() )	
							{
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = 2;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 4;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX()+20,	// 적 미사일 초기화 하고 위치를 잡아준다.
									g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
							}
						}*/
					}
				}
				else if(STAGE==2)
				{
					int nansu = rand()%800;	// 랜덤으로 100까지의 수를 발생

					if(g_Enemy[14][8].IsLive())		// 그수가 1이라면
					{
						if(nansu == 1)
						{
							if( !g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].IsLive())	// 적미사일이 없고 적이 살아있다면
							{
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedx = -2;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedy = 6;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][0].GetX()-20,	// 적 미사일 초기화 하고 위치를 잡아준다.
									g_Enemy[14][0].GetY()+20, &g_Timer, 0, 100, 5);							
							}
							if( !g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].IsLive())	
							{
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedx = 0;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedy = 6;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][0].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
									g_Enemy[14][0].GetY()+20, &g_Timer, 0, 100, 5);
								
							}
							if( !g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].IsLive())	
							{
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedx = 2;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedy = 6;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][0].GetX()+20,	// 적 미사일 초기화 하고 위치를 잡아준다.
									g_Enemy[14][0].GetY()+20, &g_Timer, 0, 100, 5);							
							}
						}
						
					}

				

					if(g_Enemy[22][0].IsLive() && g_Enemy[22][0].m_y > 150 && attack_check == 0)
					{
						InitEnemy(23);
						attack_check = 1;

						g_Enemy[23][0].Initialize(&g_EnemySprite[9], g_Enemy[22][0].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
									g_Enemy[22][0].GetY()+60,  &g_Timer, 0, 100, 5, 0);	
					}

					
				}
			}
		}
	}
	

	if(g_Enemy[23][0].IsLive() && g_Enemy[23][0].m_y > 150)
	{
		attack_check++;
		
		if(attack_check == 15 + (  EnemyMissileCheck(23,0)))
		{
			g_EnemyMissile[23][0][EnemyMissileCheck(23,0)].Initialize( &g_EnemyMissileSprite[5], g_Enemy[23][0].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
				g_Enemy[23][0].GetY(), &g_Timer, EnemyMissileCheck(23,0)%12, 100, 5);	
		}


		

		if(g_Enemy[23][0].m_y > 700)
		{
			attack_check = 0;
		}
		
	}
	else if(!g_Enemy[23][0].IsLive())
	{
		attack_check++;

		if(attack_check > 800)
		{
			attack_check = 0;
		}		
	}

	
	

	

	int temp;
	
	if(attack_check < 650)
	{
		temp = 80;		
	}
	else
	{
		temp = 40;
		if(attack_check > 800)
			attack_check = 0;
	}

	if(time%temp == 0)	// 타임을 나눈 나머지 값이 0이라면 ( 일종의 딜레이 )
	{
		for(m=0; m<5 ;m++)
		{
			if(g_Enemy[14][m].IsLive() && g_Enemy[14][m].m_y > 80 )
			{
				if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive())	// 적미사일이 없고 적이 살아있다면
				{
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = -2;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 3;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX()-20,	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
				}
				if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive())	
				{
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = 1;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 4;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
				}
				if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive())	
				{
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = -1;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 4;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX(),	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
				}
				if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive())	
				{
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = 2;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 3;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX()+20,	// 적 미사일 초기화 하고 위치를 잡아준다.
						g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
				}	
			}
		}
	}
	if(STAGE == 1)
	{
		time++;	// 딜레이값 증가
		attack_check++;
	}
	



	


	//Boss Missile Draw
	for( m=0 ; m<MAX_BOSS_YMISSILE ; m++)	// 보스 미사일의 y축 만큼
	{
		for( m2=0 ; m2<MAX_BOSS_XMISSILE ; m2++)		// 보스미사일의 x축 만큼
		{
			if( g_BossMissile[m][m2].IsLive() )	// 보스미사일이 있다면
			{
				g_BossMissile[m][m2].Move();	// 움직인후
				g_BossMissile[m][m2].Draw(g_lpSecondarySurface);	// 그려준다.
			}
		}
	}
 
	//My 미사일 그리기

		
	for( m=0 ; m<MAX_MISSILES ; m++)	// 미사일의 최대 수만큼
	{
		if(g_MyMissile[m].IsLive())		// 플레이어 미사일이 있다면
		{
			g_MyMissile[m].Move();		// 움직인후 
			
			if(g_MyMissile[m].type == BLUE && g_MyShip.level == 4)
			{
				if(wow > 80)
				{
					if(wow >= 150)
					{
						wow=150;
						g_MyMissile[m].ItemDrawing(0, g_MyMissile[m].m_x, g_MyMissile[m].m_y, 20, -8, g_lpSecondarySurface, true);
					}
					else
						g_MyMissile[m].ItemDrawing(0, g_MyMissile[m].m_x, g_MyMissile[m].m_y, 10, 0, g_lpSecondarySurface, true);
				}
				else
					g_MyMissile[m].ItemDrawing(0, g_MyMissile[m].m_x, g_MyMissile[m].m_y, 0, 0, g_lpSecondarySurface, true);
			}
			else
				g_MyMissile[m].Draw(g_lpSecondarySurface);		
		}
	}


	for( m=0 ; m<MAX_ASSIST ; m++)	// 미사일의 최대 수만큼
	{
		if(g_AssistMissile[m].IsLive())		// 플레이어 미사일이 있다면
		{
			if(g_AssistMissile[m].type == 1)
			{
				g_AssistMissile[m].Move();		// 움직인후 
			}
			else if(g_AssistMissile[m].type == 2)
			{
				if(!g_Enemy[g_AssistMissile[m].i][g_AssistMissile[m].j].IsLive())
				{
					g_AssistMissile[m].targetOn = false;
				}

				g_AssistMissile[m].Move(MissileAttack_Check(m));				
			//	g_AssistMissile[m].Move(g_AssistMissile[m].m_x);				
			}
			g_AssistMissile[m].Draw(g_lpSecondarySurface);
			
		}
	}
	
	


	


	
	

	g_State.Drawing(0, 725, 300, g_lpSecondarySurface, false);

	// MyLife Init
	for(i=0;i<g_MyShip.life;i++)
	{
		g_MyLifeSprite.Drawing(0, 767-(i*29), 144, g_lpSecondarySurface, true);
	}

	g_MissileItemSprite.Drawing(g_MyShip.type, 800-150+47, 265, g_lpSecondarySurface, true);

	if(g_MyShip.missiletype > 0)
		g_ItemSprite.Drawing(g_MyShip.missiletype + 8, 800-150+100, 265, g_lpSecondarySurface, true);


	

	for(i=0 ; i<2 ; i++)
	{
		if(g_Attack[i].IsLive())
		{
			if(i==0)
			{
				if(g_MyShip.IsLive())
					g_Attack[i].Draw(g_lpSecondarySurface, g_MyShip.m_x, g_MyShip.m_y-300-20);
			}
			else if(i==1)
				g_Attack[i].Draw(g_lpSecondarySurface, lazer_x, 300);
		}
	}

	for(i=0 ; i<MAX_EXPLODES ;i++)
	{
		if(g_Exploding[i].IsLive())
		{
			g_Exploding[i].Draw(g_lpSecondarySurface, g_Exploding[i].m_x, g_Exploding[i].m_y);
		}
	}

	
	IntToArray(Player[0].score, ScoreArray, 5);
	for(i=0 ; i<5; i++)
	{
		g_Score.Drawing(ScoreArray[i], 700+(i*15), 210, g_lpSecondarySurface, true);
	}

	for(i=0 ; i<3 ; i++)
	{
		if(item[i] != DEFAULT)
			g_ItemSprite.Drawing(item[i]-1, 650+76, 327 + (i*52), g_lpSecondarySurface, true);

	}

	g_MiniMapSprite.Drawing(0, Player[0].MiniMapX/6+672, Player[0].MiniMapY/6+478, g_lpSecondarySurface, true);
//	g_MiniMapSprite.Drawing(0, g_MyShip.GetX()/6+672, g_MyShip.GetY()/6+478, g_lpSecondarySurface, true);
}

void InputKey()
{
	int i;

	
	//내 비행선의 움직임 처리와 그리기
	int nMyShipFrame = 0; //center
	
	if(Player[0].End != 1)
	{
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP) &&
			DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT))	// 오른쪽위로
		{
			g_MyShip.Upright();
			if(bItem[CHANGE])
				nMyShipFrame = 2;
			else
				nMyShipFrame = 1;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP) &&
			DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT))		// 왼쪽위로
		{
			g_MyShip.Upleft();
			if(bItem[CHANGE])
				nMyShipFrame = 1;
			else
				nMyShipFrame = 2;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN) &&
			DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT))	// 오른쪽아래로
		{
			g_MyShip.Downright();
			if(bItem[CHANGE])
				nMyShipFrame = 1;
			else
				nMyShipFrame = 2;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN) &&
			DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT))		// 왼쪽위로
		{
			g_MyShip.Downleft();
			if(bItem[CHANGE])
				nMyShipFrame = 2;
			else
				nMyShipFrame = 1;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT))		// 왼쪽으로
		{
			g_MyShip.Left();	// 왼쪽으로 움직인다.
			if(bItem[CHANGE])
				nMyShipFrame = 2;
			else
				nMyShipFrame = 1;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT))		// 오른쪽으로
		{
			g_MyShip.Right();	// 오른쪽으로 움직인다.
			if(bItem[CHANGE])
				nMyShipFrame = 1;
			else
				nMyShipFrame = 2;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP))		// 위쪽으로
		{
			g_MyShip.Up();
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN))		// 아래쪽으로
		{
			g_MyShip.Down();
		}
		
		if(g_MyShip.m_y<30)
		{
			g_MyShip.m_y=30;
		}
		if(g_MyShip.m_x<30)
		{		
			g_MyShip.m_x=30;
		}
		if(g_MyShip.m_y>570)
		{
			g_MyShip.m_y=570;
		}
		if(g_MyShip.m_x>620)
		{
			g_MyShip.m_x=620;
		}
		
		
	}
	g_MyShip.DrawFrame(g_lpSecondarySurface, nMyShipFrame);

	
	static int inputkey = g_Timer.time();

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_1))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = SLOW;
	}
	
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_2))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = FAST;
	}
	
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_3))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = SHIELD;
	}
	
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_4))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = CHANGE;
	}
	
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_5))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = MISSILE;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_6))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = STOP;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_7))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = ENEMY;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_8))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = POWER_D;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_9))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = POWER_U;
	}



	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_Q))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
		{
			g_MyShip.type = RED;
			g_Timer.missile_check=0;
		}
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_W))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
		{
			g_MyShip.type = GREEN;
			g_Timer.missile_check=0;
		}
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_E))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
		{
			g_MyShip.type = BLUE;
			g_Timer.missile_check=0;
		}
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_A))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
		g_MyShip.missiletype = 1;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_S))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
		g_MyShip.missiletype = 2;
	}
	
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_P))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			if(g_MyShip.level < 4)
				g_MyShip.level++;
	}


	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_O))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			if(g_MyShip.level > 0)
				g_MyShip.level--;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_L))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			if(g_MyShip.assistlevel < 2)
				g_MyShip.assistlevel++;
		g_Timer.assist_missile_check = 0;
	}


	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_K))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
			if(g_MyShip.assistlevel > 0)
				g_MyShip.assistlevel--;
		g_Timer.assist_missile_check = 0;
	}


	


	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_C))		// 아래쪽으로
	{
		if(g_Timer.elapsed(inputkey,500))
		{
			if(item[0] != DEFAULT)
			{
				attack_item = item[0];
				for(i=1; i<3; i++)
				{
					item[i-1] = item[i];
					item[i] = DEFAULT;
				}
			}
		}
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_D))		// 아래쪽으로
	{
		STAGE = 2;
		attack_check = 0;
	}
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_F))		// 아래쪽으로
	{
		timevar = 3450;
	}


}

void Collision()
{
	int i, j , m, k;


	//내 총알과 적 충돌 감지와 폭파 처리
	for( m=0 ; m<MAX_ASSIST ; m++ )	// 최대 미사일까지
	{
		for( i=0 ; i<MAX_PATTERN ; i++ )	// 가로축 적 수만큼 
		{
			for( j=0 ; j<MAX_ENEMYS ; j++)	// 세로축 적 수만큼
			{
				if(g_AssistMissile[m].IsLive()   &&   g_Enemy[i][j].IsLive() && g_Enemy[i][j].m_y > 0)  // 내미사일과 적이 있을때
				{
					if(abs(g_AssistMissile[m].GetX() - g_Enemy[i][j].GetX())<(g_Enemy[i][j].check_x/2))	// 내미사일과 적의 충돌 검사 
						if(abs(g_AssistMissile[m].GetY() - g_Enemy[i][j].GetY())<(g_Enemy[i][j].check_y/2))	// abs로 절대값 30은 이미지 크기
						{
										// 시작 위치를 구한다.
							g_AssistMissile[m].Kill();	// 내 미사일과 적을 없앤다.
							
							if(g_MyShip.missiletype == 1)
								{
									if(g_MyShip.assistlevel == 2)
										g_Enemy[i][j].life-=3;
									else
										g_Enemy[i][j].life-=2;
								}
								else if(g_MyShip.missiletype == 2)
								{
									if(g_MyShip.assistlevel == 2)
										g_Enemy[i][j].life-=2;
									else
										g_Enemy[i][j].life-=1;
								}

							
							if(g_Enemy[i][j].life>0)
							{
								g_Exploding[ExplodingCheck()].Initialize(&g_AssistMissileExplodingSprite, g_AssistMissile[m].GetX(),	// 폭파를 초기화 한다
								g_AssistMissile[m].GetY(), &g_Timer, 0, 35);
							}

							else if(g_Enemy[i][j].life<=0)
							{
								if(STAGE==1)
								{
									if(i==14)
									{
										STAGEEXP++;
										if(STAGEEXP==5)
										{
											timevar=0;
											STAGE++;
										}
									}
								}
								if(i == 14 || i == 22)
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_Enemy[i][j].GetX(),	// 폭파를 초기화 한다
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);
								else
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[1], g_Enemy[i][j].GetX(),	// 폭파를 초기화 한다
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);

								g_Enemy[i][j].Kill();
								Player[0].score += g_Enemy[i][j].score;
							}
							_Play(2);		// 2번 사운드 출력
						}
				}
			}
		}
	}
	
	//내 미사일과 적 충돌 감지와 폭파 처리
	for( m=0 ; m<MAX_MISSILES ; m++ )	// 최대 미사일까지
	{
		for( i=0 ; i<MAX_PATTERN ; i++ )	// 가로축 적 수만큼 
		{
			for( j=0 ; j<MAX_ENEMYS ; j++)	// 세로축 적 수만큼
			{
				if(g_MyMissile[m].IsLive()   &&   g_Enemy[i][j].IsLive() && g_Enemy[i][j].m_y > 0)   // 내미사일과 적이 있을때
				{
					if(abs(g_MyMissile[m].GetX() - g_Enemy[i][j].GetX())<(g_Enemy[i][j].check_x/2))	// 내미사일과 적의 충돌 검사 
						if(abs(g_MyMissile[m].GetY() - g_Enemy[i][j].GetY())<(g_Enemy[i][j].check_y/2))	// abs로 절대값 30은 이미지 크기
						{
										// 시작 위치를 구한다.
							g_MyMissile[m].Kill();	// 내 미사일과 적을 없앤다.

							g_Enemy[i][j].life--;
							
							if(g_Enemy[i][j].life>0)
							{
								g_Exploding[ExplodingCheck()].Initialize(&g_MissileExplodingSprite, g_MyMissile[m].GetX(),	// 폭파를 초기화 한다
								g_MyMissile[m].GetY(), &g_Timer, 0, 35);
							}

							else if(g_Enemy[i][j].life<=0)
							{
								if(STAGE==1)
								{
									if(i==14)
									{
										STAGEEXP++;
										if(STAGEEXP==5)
										{
											timevar=0;
											attack_check = 0;
											STAGE++;
										}
									}
								}
								if(i == 14 || i == 22)
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_Enemy[i][j].GetX(),	// 폭파를 초기화 한다
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);
								else
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[1], g_Enemy[i][j].GetX(),	// 폭파를 초기화 한다
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);

								g_Enemy[i][j].Kill();
								Player[0].score += g_Enemy[i][j].score;
							}
							

							_Play(2);		// 2번 사운드 출력
						}
				}
			}
		}
	}
	
	for( i=0 ; i<MAX_PATTERN ; i++ )	// 가로축 적 수만큼 
	{
		for( j=0 ; j<MAX_ENEMYS ; j++)	// 세로축 적 수만큼
		{
			for(m =0 ;m <2 ; m++)
			{
				if(g_Attack[m].IsLive()   &&   g_Enemy[i][j].IsLive() && g_Enemy[i][j].m_y > 0)  // 내미사일과 적이 있을때
				{
					if(abs(g_Enemy[i][j].GetX() - g_Attack[m].GetX())<(g_Enemy[i][j].check_x/2))	// 내미사일과 적의 충돌 검사 
						if(abs(g_Enemy[i][j].GetY() - g_Attack[m].GetY())<300)	// abs로 절대값 30은 이미지 크기
						{						
							g_Enemy[i][j].life-=1;						
							
							if(g_Enemy[i][j].life>0)
							{
								g_Exploding[ExplodingCheck()].Initialize(&g_MissileExplodingSprite, g_Attack[m].GetX(),	// 폭파를 초기화 한다
									g_Enemy[i][j].GetY(), &g_Timer, 0, 35);
							}
							
							else if(g_Enemy[i][j].life<=0)
							{
								if(STAGE==1)
								{
									if(i==14)
									{
										STAGEEXP++;
										if(STAGEEXP==5)
										{
											timevar=0;
											attack_check = 0;
											STAGE = 2;
										}
									}
								}
								if(i == 14 || i == 22)
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_Enemy[i][j].GetX(),	// 폭파를 초기화 한다
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);
								else
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[1], g_Enemy[i][j].GetX(),	// 폭파를 초기화 한다
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);

								g_Enemy[i][j].Kill();
								Player[0].score += g_Enemy[i][j].score;
							}
							_Play(2);		// 2번 사운드 출력
						}
				}
				
				for( k =0; k<MAX_ENEMY_MISSILES ; k++)
				{
					if(g_EnemyMissile[i][j][k].IsLive()   &&   g_Attack[m].IsLive())		// 적미사일과 플레이어가 있다면
					{ 
						if(abs(g_EnemyMissile[i][j][k].GetX() - g_Attack[m].GetX())<15)		// 적 미사일과 플레이어의 충돌검사
							if(abs(g_EnemyMissile[i][j][k].GetY() - g_Attack[m].GetY())<300)
							{
								g_EnemyMissile[i][j][k].Kill();
							}
					}
				}
			}
		}
	}

	for(i=0;i<8;i++)
	{
		if(g_Item[i].IsLive() && g_MyShip.IsLive())
		{
			if(abs(g_Item[i].GetX() - g_MyShip.GetX())<30)
				if(abs(g_Item[i].GetY() - g_MyShip.GetY())<30)
				{
					if(g_Item[i].type<9)
					{
						if(item[ItemCheck()]<2)
							item[ItemCheck()] = g_Item[i].type+1;
					}
					else if(g_Item[i].type<11)
					{
						if(g_MyShip.missiletype == g_Item[i].type-8)
						{
							if(g_MyShip.assistlevel < 2)
								g_MyShip.assistlevel++;
						}
						else
						{
							g_MyShip.missiletype = g_Item[i].type-8;
						}						
						g_Timer.assist_missile_check=0;
					}
					else if(g_Item[i].type<14)
					{
						if(g_MyShip.type == g_Item[i].type-11)
						{
							if(g_MyShip.level < 4)
								g_MyShip.level++;
						}
						else
						{
							g_MyShip.type = g_Item[i].type-11;
						}						
						g_Timer.missile_check=0;

					}
					else
					{
						if(g_MyShip.life < 3)
							g_MyShip.life++;
					}
					g_Item[i].Kill();
				}
		}
	}
	
	if(!bItem[SHIELD])
	{
		
		// 적의 총알과 내 비행기 충돌 감지 및 폭파 처리
	
		for( i=0 ; i<MAX_PATTERN ; i++ )		// 가로줄 적수 만큼
		{
			for( j=0 ; j<MAX_ENEMYS ; j++ )	// 세로줄 적수 만큼
			{
				for( k =0; k<MAX_ENEMY_MISSILES ; k++)
				{
					if(g_EnemyMissile[i][j][k].IsLive()   &&   g_MyShip.IsLive())		// 적미사일과 플레이어가 있다면
					{
						if(abs(g_EnemyMissile[i][j][k].GetX() - g_MyShip.GetX())<15)		// 적 미사일과 플레이어의 충돌검사
							if(abs(g_EnemyMissile[i][j][k].GetY() - g_MyShip.GetY())<20)		// 이미지 크기
							{
								g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_MyShip.GetX(),	// 폭파 초기화 
									g_MyShip.GetY(), &g_Timer, 0, 10);		// 위치설정
								g_EnemyMissile[i][j][k].Kill();		// 적 미사일과 플레이어를 없앤다
								
								
								if(g_MyShip.life>0)	
								{
									g_MyShip.life--;
									m_bInitMyShip = true;
									
									if(g_MyShip.life==0)
									{
										m_bInitMyShip = false;
									}
								}			
								
								g_MyShip.Kill();
								
								
								_Play(2);		// 2번 사운드 출력
							}
					}
				}
			}
		}
		
		
		// 적과 내 비행기 충돌 감지 및 폭파 처리
		for( i=0 ; i<MAX_PATTERN ; i++ )		// 가로줄 적수 만큼
		{
			for( j=0 ; j<MAX_ENEMYS ; j++ )	// 세로줄 적수 만큼
			{
				if(g_Enemy[i][j].IsLive()   &&   g_MyShip.IsLive())		// 적과 플레이어가 있다면
				{
					if(abs(g_Enemy[i][j].GetX() - g_MyShip.GetX())<(g_Enemy[i][j].check_x/2))		// 적과 플레이어의 충돌검사
						if(abs(g_Enemy[i][j].GetY() - g_MyShip.GetY())<(g_Enemy[i][j].check_y/2))
						{
							g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_Enemy[i][j].GetX(),	// 폭파 초기화 
								g_Enemy[i][j].GetY(), &g_Timer, 0, 10);		// 위치설정
							g_Enemy[i][j].Kill();		// 적 미사일과 플레이어를 없앤다

							Player[0].score += g_Enemy[i][j].score;
							
							
							if(g_MyShip.life>0)	
							{
								g_MyShip.life--;
								m_bInitMyShip = true;
								
								if(g_MyShip.life==0)
								{
									m_bInitMyShip = false;
								}
							}			
							
							g_MyShip.Kill();
							
							_Play(2);		// 2번 사운드 출력
						}
				}
			}
		}
		
		/*
		// My 총알과 Boss 충돌 감지 및 폭파 처리
		for( m=0 ; m<MAX_MISSILES ; m++ )		//  최대 미사일 수만큼
		{	
		for( i=0 ; i<MAX_BOSS ; i++ )		// 보스 수만큼
		{
		if( g_MyMissile[m].IsLive()   &&   g_Boss[i].IsLive()   &&   m_bBoss == TRUE )	// 보스가 나왓고 보스가 살아있고 미사일이 있다면
		{
		if( abs(g_MyMissile[m].GetX() - g_Boss[i].GetX()) < 100 )		// 보스와 미사일의 충돌체크
		if( abs(g_MyMissile[m].GetY() - g_Boss[i].GetY()) <70 )		// 이미지 크기
		{
		g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(),	// 폭파 초기화
		g_MyMissile[m].GetY(), &g_Timer, 0, 10);		// 폭파 위치 설정
		g_MyMissile[m].Kill();		// 미사일을 없앤다.
		g_Boss[i].m_Enegy -= 1;		// 보스 에너지 -1 총 30
		
		  g_Exploding[m].Draw(g_lpSecondarySurface);	// 폭파이미지를 그린다.
		  _Play(2);	// 2번사운드 출력
		  
			if(g_Boss[i].m_Enegy == 0)	// 보스피가 0일때
			{
			g_Boss[i].Kill();	// 보스를 없앤다.
			MyShipWin();		// 게임성공 함수 호출
			}
			}
			}
			}
			}
		
		
		//Boss총알과 내 비행기 충돌 감지 및 폭파 처리
		for( i=0 ; i<MAX_EXPLODES ; i++ )	
		{
			for( m=0 ; m<MAX_BOSS_YMISSILE ; m++ )	// 보스의 세로 미사일만큼
			{
				for( m2=0 ; m2<MAX_BOSS_XMISSILE ; m2++ )	// 보스의 가로 미사일 만큼
				{
					if(g_BossMissile[m][m2].IsLive()   &&   g_MyShip.IsLive())	// 보스의 미사일이 있고 플레이어가 있을때
					{
						if(abs(g_BossMissile[m][m2].GetX() - g_MyShip.GetX())<30)	// 보스 미사일과 플레이어 충돌검사
							if(abs(g_BossMissile[m][m2].GetY() - g_MyShip.GetY())<20)	// 이미지 크기
							{
								g_Exploding[i].Initialize(&g_ExplodingSprite, g_BossMissile[m][m2].GetX(),	// 폭파 초기화
									g_BossMissile[m][m2].GetY(), &g_Timer, 0, 10);	// 위치,프레임 설정
								g_BossMissile[m][m2].Kill();	// 보스미사일 삭제
								
								if(g_MyShip.life>0)	
								{
									g_MyShip.life--;
									m_bInitMyShip = true;
									
									if(g_MyShip.life==0)
									{
										MyShipDead();	// 플레이어가 죽었다는 함수 호출
										m_bInitMyShip = false;
									}
								}			
								
								g_MyShip.Kill();
								
								g_Exploding[i].Draw(g_lpSecondarySurface);	// 폭파이미지 출력
								_Play(2);	// 2번 사운드 출력
							}
					}
				}
			}
		}
		*/
		
	}
	
}




BOOL DirectInputKeyboardDown(LPDIRECTINPUTDEVICE8 lpKeyboard, int dikcode)	
{
	char KeyBuffer[256];
	HRESULT hResult;
							// 키보드 받은 값이 오류라면
	if(lpKeyboard->GetDeviceState(256,(LPVOID)KeyBuffer) == DIERR_INPUTLOST)
	{
		while( hResult = lpKeyboard->Acquire() == DIERR_INPUTLOST)	// 계속 다시 해준다.
			hResult = lpKeyboard->Acquire();
		lpKeyboard->GetDeviceState(256,(LPVOID)KeyBuffer);
	}

	return (KeyBuffer[dikcode] & 0x80);
}

void InitGame()
{
	srand(timeGetTime());

	InitInterface();


	nMissileTime =g_Timer.time();
	A_nMissileTime = g_Timer.time();

	//초기화
	int i, j, k, m, m2;

	for(i = 0 ; i < 10 ; i++)
		nItemTime[i] = 0;

	timevar=0;
	attack_check = 0;

	item_check=0;
	bgflag = 0;	
	STAGE = 1;
	STAGEEXP = 0;

	Player[0].score = 0;


	g_MyShip.life = 3;
	g_MyShip.item = DEFAULT;

	m_bInitMyShip = true;
	g_MyShip.InitMyShip_y = 620;
	g_Timer.missile_check = 0;
	g_Timer.assist_missile_check = 0;

	g_MyShip.assistlevel = 0;
	g_MyShip.level = 0;

	for(i=0; i <3 ; i++)
		item[i] = DEFAULT;

	
	

	// Map Init
/*	if(bgflag == 0)
	{

		g_BackgroundSprite.destRect.top = -5400;
		g_BackgroundSprite.destRect.bottom = 600;
	}
*/
	//Explodes Init
	for( i=0 ; i<MAX_EXPLODES ; i++ )
		if(g_Exploding[i].IsLive()) g_Exploding[i].Kill();		// 폭파가 있다면 없앤다.

	//MyShip Init
	if(g_MyShip.IsLive()) g_MyShip.Kill();		// 플레이어가 살아있다면 삭제
//	g_MyShip.Initialize(&g_MyShipSprite, 390, 570, &g_Timer, 0, 25, 5);	// 플레이어 초기화 

	for(k=0; k<3 ;k++)
	{
		for( m=0 ; m<MAX_MISSILES ; m++ )		
		{
			if(g_MyMissile[m].IsLive()) g_MyMissile[m].Kill();	// 미사일이 있다면 삭제
		}
	}

	//Enemy Init
	for( i=0 ; i<MAX_PATTERN ; i++ )
		for( j=0 ; j<MAX_ENEMYS ; j++ )
		{
			if(g_Enemy[i][j].IsLive())  g_Enemy[i][j].Kill();		// 적과 적의 미사일이 있다면 삭제 

			g_Enemy[i][j].kill = false;

		}

	for( i=0 ; i<MAX_PATTERN ; i++ )
		for( j=0 ; j<MAX_ENEMYS ; j++ )
			for(k =0 ;k<MAX_ENEMY_MISSILES ; k++)
			{
				if(g_EnemyMissile[i][j][k].IsLive()) g_EnemyMissile[i][j][k].Kill();
			}
		

	for(i=0;i<1;i++)
		for(j=0;j<5;j++)
			g_Enemy[i][j].Initialize(&g_EnemySprite[0], rand()%430+60, rand()%300-320, &g_Timer, 0, 25, 5, 0);	// 적을 초기화

	for(i=0; i<8 ; i++)
		if(g_Item[i].IsLive())
			g_Item[i].Kill();


/*
		for(j=0;j<5;j++)
	g_Enemy[2][j].Initialize(&g_EnemySprite, (j*5)*(-30), 230, &g_Timer, 0, 25, 5);	// 적을 초기화
*/

	//Boss Init
	for(i=0 ; i<MAX_BOSS ; i++)		
	{
		if(g_Boss[i].IsLive())  g_Boss[i].Kill();		// 보스가 잇으면 삭제
	}

	for(i=0 ; i<MAX_BOSS ; i++)
	{
		g_Boss[i].Initialize(&g_BossSprite,(i+1)*100, 130, &g_Timer, 0, 25, 5);		// 보스 초기화
		g_Boss[i].m_speedx=2;		// 보스 스피드 설정
		g_Boss[i].m_Enegy=30;			// 보스 에너지 설정
	}

	for( m=0 ; m<MAX_BOSS_YMISSILE ; m++ )
	{
		for(m2=0 ; m2<MAX_BOSS_XMISSILE ; m2++)
		{
			if(g_BossMissile[m][m2].IsLive())  g_BossMissile[m][m2].Kill();	// 보스미사일이 있다면 삭제
		}
	}
/*	
	m_bGameDead = FALSE;		// 게임 실패 제어변수 펄스
	m_bGameClear = FALSE;		// 게임 성공 제어변수 펄스
*/
	m_bGameFirst = FALSE;		// 게임 시작 제어변수 펄스
	m_bBoss = FALSE;			// 보스 생성 제어 변수 펄스
	bgflag = 0;


	SndObjPlay(Sound[0], DSBPLAY_LOOPING);	//	사운드배열 0번째 사운드 출력
}

void InitInterface()
{
	//srand(timeGetTime());
	
	// 상태 배경 
	g_State.Drawing(0, 750, 300, g_lpSecondarySurface, false);

	// MyLife Init
	/*
	for(int i=0;i<g_MyShip.life;i++)
	{
		g_MyLife[i].Initialize(&g_MyLifeSprite, 760, i*25+60, &g_Timer, 0, 25, 5);
		g_MyLife[i].DrawFrame(g_lpSecondarySurface, 0);
	}
	*/
}


void _Play(int num)		// 사운드 함수
{
	SndObjPlay(Sound[num], NULL);	// 해당번호 사운드를 출력한다.
}



void MyShipItemCheck()
{


	
	switch(attack_item)
	{
		case DEFAULT:
		{

		}
		break;

		case SLOW:
		case FAST:	//빠르게
		case CHANGE:	//적의 움직임을 반대로
		case MISSILE:	//자신과 같은 위치에 미사일 폭격
		case STOP:	//일시정지
		case ENEMY:	//적 랜덤 생성
		case POWER_D:	//상대방 파워 다운
			if(item_check>5)
			{
				attack_item = DEFAULT;			
				item_check = 0;
			}
			else
			{
				item_check++;
				if(item_check == 1 && attack_item == MISSILE)
					g_Attack[0].Initialize(&g_AttackSprite, g_MyShip.m_x,
							g_MyShip.m_y-300, &g_Timer, 0, 40);
			}
			break;

		

		case SHIELD:	//쉴드
		{
			bItem[SHIELD] = true;
			attack_item = DEFAULT;		
			item_check = 0;	
			nItemTime[SHIELD] = 0;
		}
		break;

		

		case POWER_U:	//내 파워 업
		{
			bItem[POWER_U] = true;
			attack_item = DEFAULT;		
			item_check = 0;
		}
		break;
	}

	switch(g_MyShip.item)
	{
		
		case DEFAULT:	//일반
		{
		}
		break;

		case SLOW:	//느리게
		{
			nItemTime[SLOW] = 0;
			g_MyShip.speed = 1;
			bItem[SLOW] = true;

		}
		break;

		case FAST:	//빠르게
		{
			nItemTime[FAST] = 0;
			g_MyShip.speed = 10;
			bItem[FAST] = true;

			
		}
		break;

		

		case SHIELD:	//쉴드
		{
		
		}
		break;

		case CHANGE:	//적의 움직임을 반대로
		{
			nItemTime[CHANGE] = 0;
			bItem[CHANGE] = true;


			
		}
		break;

		case MISSILE:	//자신과 같은 위치에 미사일 폭격
		{

			if(!bItem[MISSILE])
				g_Attack[1].Initialize(&g_AttackSprite, lazer_x,
							300, &g_Timer, 0, 40);

			bItem[MISSILE] = true;			
			g_MyShip.item = DEFAULT;


		}
		break;

		case STOP:	//일시정지
		{
			nItemTime[STOP] = 0;
			bItem[STOP] = true;
			g_MyShip.speed = 0;


			
		}
		break;

		case ENEMY:	//적 랜덤 생성
		{
			bItem[ENEMY] = true;

			
		}
		break;

		case POWER_D:	//상대방 파워 다운
		{
			bItem[POWER_D] = true;

			
		}
		break;

		case POWER_U:	//상대방 파워 다운
		{
			
		}
		break;
	}
}


void IntToArray(int num,int ar[],int s) //전광판의 숫자를 하나씩 저장
{
	int div=(int)pow(10,s-1);  //pow는 제곱승   
	int count=0;
	while(count<s)
	{
		ar[count]=num/div;
		num -=div*ar[count];
		div /=10;
		count++;
	}
}

void MyShipCheck()
{	

	if(bItem[SLOW])	//느리게
	{
		g_MyShip.speed = 1;	
		if(TimerCheck( nItemTime[SLOW], 300, SLOW))
		{
			
			g_MyShip.speed=5;
			if(g_MyShip.item == SLOW)
				g_MyShip.item = DEFAULT;
			bItem[SLOW] = false;
			nItemTime[SLOW] = 0;
		}
	}
	
	
	if(bItem[FAST])	//빠르게
	{
		g_MyShip.speed = 10;
		
		if(TimerCheck( nItemTime[FAST], 300, FAST))
		{
			g_MyShip.speed=5;
			if(g_MyShip.item == FAST)
				g_MyShip.item = DEFAULT;
			bItem[FAST] = false;
			nItemTime[FAST] = 0;
		}
		
		
	}
	
	
	
	
	if(bItem[SHIELD])	//쉴드
	{
		if(TimerCheck( nItemTime[SHIELD], 300, SHIELD))
		{
			if(g_MyShip.item == SHIELD)
				g_MyShip.item = DEFAULT;
			bItem[SHIELD] = false;
			nItemTime[SHIELD] = 0;
		}		
	}
	
	
	if(bItem[CHANGE])	//적의 움직임을 반대로
	{
		
		if(g_MyShip.speed > 0)
			g_MyShip.speed *= -1;
		if(TimerCheck( nItemTime[CHANGE], 300, CHANGE))
		{
			
			g_MyShip.speed *= -1;
			if(g_MyShip.item == CHANGE)
				g_MyShip.item = DEFAULT;
			bItem[CHANGE] = false;
			nItemTime[CHANGE] = 0;
		}
		
		
	}
	
	
	if(bItem[MISSILE])	//자신과 같은 위치에 미사일 폭격
	{
		
		
		if(!g_Attack[1].IsLive())
		{
			bItem[MISSILE] = false;
			if(g_MyShip.item == MISSILE)
				g_MyShip.item = DEFAULT;
		}

	}
	
	
	if(bItem[STOP])	//일시정지
	{
		
		g_MyShip.speed = 0;

		if(TimerCheck( nItemTime[STOP], 50, STOP))
		{
			g_MyShip.speed=5;
			if(g_MyShip.item == STOP)
				g_MyShip.item = DEFAULT;
			bItem[STOP] = false;
			nItemTime[STOP] = 0;
		}
		
		
	}
	
	
	if(bItem[ENEMY])	//적 랜덤 생성
	{
		bItem[ENEMY] = false;
		
		
	}
	
	
	if(bItem[POWER_D])	//상대방 파워 다운
	{
		bItem[POWER_D] = false;
		
		if(g_MyShip.level>0)
			g_MyShip.level--;
	}

	if(bItem[POWER_U])	//상대방 파워 다운
	{
		if(g_MyShip.level<4)
				g_MyShip.level++;
		bItem[POWER_U] = false;
	}
}

void MyMissile(bool flag)
{
	

	switch(g_MyShip.type)
	{
		case RED:
			{
				

				switch(g_MyShip.level)
				{
					case 0:
						{
							MAX_MISSILE[RED] = 1;	
							MY_MISSILE_INTERVAL[RED] = 150; 
							MISSILE_DELAY[RED] = 270; 
							
							if(flag)
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX(),		// 미사일 초기화 위치를 잡아준다.
								g_MyShip.GetY()-20, &g_Timer, 0, 10, 5);
						}
						break;
					case 1:
						{
							MAX_MISSILE[RED] = 2;
							MY_MISSILE_INTERVAL[RED] = 140;
							MISSILE_DELAY[RED] = 260;
							
							if(flag)
							{
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-6,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+6,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5);
							}
						}
						break;
					case 2:
						{
							MAX_MISSILE[RED] = 3;
							MY_MISSILE_INTERVAL[RED] = 130;
							MISSILE_DELAY[RED] = 250;
							if(flag)
							{
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-5,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, -1, 11 );

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+5,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 1, 11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-10,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, -2, 10);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+10,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, 2, 10);
							}
						}
						break;
					case 3:
						{
							MAX_MISSILE[RED] = 4;
							MY_MISSILE_INTERVAL[RED] = 120;
							MISSILE_DELAY[RED] = 240;
							if(flag)
							{

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX(),		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5,0,12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+6,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 3, 11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-6,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, -3,11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-12,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, -6, 10);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+12,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, 6, 10);
							}
						}
						break;
					case 4:
						{
							MAX_MISSILE[RED] = 5;
							MY_MISSILE_INTERVAL[RED] = 110;
							MISSILE_DELAY[RED] = 230;

							if(flag)
							{

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX(),		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 0, 13);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+6,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 3, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-6,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, -3, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-12,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, -6, 11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+12,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, 6, 11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-18,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, -9, 10);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+18,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, 9, 10);
							}
						}
						break;
				}
				
				
			}
			break;

		case BLUE:
			{
				switch(g_MyShip.level)
				{
					case 0:
						{
							MAX_MISSILE[BLUE] = 3;
							MY_MISSILE_INTERVAL[BLUE] = 70;
							MISSILE_DELAY[BLUE] = 300;
						}
						break;
					case 1:
						{
							MAX_MISSILE[BLUE] = 6;
							MY_MISSILE_INTERVAL[BLUE] = 60;
							MISSILE_DELAY[BLUE] = 275;
						}
						break;
					case 2:
						{
							MAX_MISSILE[BLUE] = 9;
							MY_MISSILE_INTERVAL[BLUE] = 40;
							MISSILE_DELAY[BLUE] = 250;
						}
						break;
					case 3:
						{
							MAX_MISSILE[BLUE] = 12;
							MY_MISSILE_INTERVAL[BLUE] = 20;
							MISSILE_DELAY[BLUE] = 200;
						}
						break;
					case 4:
						{
							MAX_MISSILE[BLUE] = 15;
							MY_MISSILE_INTERVAL[BLUE] = 5;
							MISSILE_DELAY[BLUE] = 50;
						}
						break;
				}
				
				if(flag)
					g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[BLUE], g_MyShip.GetX(),		// 미사일 초기화 위치를 잡아준다.
					g_MyShip.GetY()-20, &g_Timer, 0, 10, 5);
				
			}
			break;
			
		case GREEN:
			{
				switch(g_MyShip.level)
				{
					case 0:
						{
							MAX_MISSILE[GREEN] = 2;
							MY_MISSILE_INTERVAL[GREEN] = 90;
							MISSILE_DELAY[GREEN] = 255;

							if(flag)
							{
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX(),		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5,0 ,12);
							}
						}
						break;

					case 1:
						{
							MAX_MISSILE[GREEN] = 3;
							MY_MISSILE_INTERVAL[GREEN] = 85;
							MISSILE_DELAY[GREEN] = 250;
							
							if(flag)
							{
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-5,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, -1, 11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+5,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 1, 11);
							}
						}
						break;

					case 2:
						{
							MAX_MISSILE[GREEN] = 4;
							MY_MISSILE_INTERVAL[GREEN] = 80;
							MISSILE_DELAY[GREEN] = 245;

							if(flag)
							{
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX(),		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, 0, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-12,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 0, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+12,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 0, 12);
							}
						}
						break;

					case 3:
						{
							MAX_MISSILE[GREEN] = 5;
							MY_MISSILE_INTERVAL[GREEN] = 75;
							MISSILE_DELAY[GREEN] = 240;

							if(flag)
							{
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+8,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 0, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-8,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 0 ,12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-10,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, -1, 13);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+10,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 1, 13);
							}
						}
						break;

					case 4:
						{
							MAX_MISSILE[GREEN] = 6;
							MY_MISSILE_INTERVAL[GREEN] = 70;
							MISSILE_DELAY[GREEN] = 235;

							if(flag)
							{
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX(),		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5,0,13);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-12,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-18, &g_Timer, 0, 10, 5,0 , 13);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+12,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-18, &g_Timer, 0, 10, 5,0, 13);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-12,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, -1, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+12,		// 미사일 초기화 위치를 잡아준다.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, 1, 12);
							}
						}
						break;

				}
			}
			break;
	}
}

void MyShipInit()
{
	int i;
	

	for(i=0; i<g_MyShip.level ; i++)
	{
		g_Item[ItemCheck(true)].type = (rand()%3) +11;
		g_Item[ItemCheck(true)].Initialize(&g_MissileItemSprite,  g_MyShip.m_x - 25 + (rand()%3 * 25), g_MyShip.m_y - 25 + (rand()%3 * 25), &g_Timer, g_Item[ItemCheck(true)].type-10, 25, 5 , rand()%4+1);
	}

	for(i=0; i<g_MyShip.assistlevel ; i++)
	{
		g_Item[ItemCheck(true)].type = (rand()%2) +9;
		g_Item[ItemCheck(true)].Initialize(&g_ItemSprite, g_MyShip.m_x - 25 + (rand()%3 * 25), g_MyShip.m_y - 25 + (rand()%3 * 25), &g_Timer, g_Item[ItemCheck(true)].type, 25, 5 , rand()%4+1);
	}

	g_MyShip.m_x = (800-150)/2;
	g_MyShip.m_y = g_MyShip.InitMyShip_y;
	g_InitMyShipSprite.Drawing(g_MyShip.InitMyShip_y%4, g_MyShip.m_x, g_MyShip.InitMyShip_y, g_lpSecondarySurface, true);

	g_MyShip.speed = 5;
	attack_item = DEFAULT;
	g_MyShip.item = DEFAULT;
	g_MyShip.level = 0;
	g_MyShip.type = GREEN;
	g_MyShip.missiletype = 0;
	g_MyShip.assistlevel = 0;

	TimerCheck_temp = 0;
	for(i=0; i<5; i++)
		TimerCheck_item[i] = 0;

	for(i=0; i<10 ; i++)
		nItemTime[i] = 0;

	g_Attack[0].Kill();

	

	for(i = 0 ; i<8 ; i++)
		bItem[i] = false;


		
	if(g_MyShip.InitMyShip_y <= 540)
	{
		g_MyShip.Initialize(&g_MyShipSprite, g_MyShip.m_x, g_MyShip.InitMyShip_y, &g_Timer, 0, 25, 5);	// 플레이어 초기화 
		m_bInitMyShip = false;
		g_MyShip.InitMyShip_y = 650;
		g_Timer.missile_check = 0;
		g_Timer.assist_missile_check = 0;
		bItem[SHIELD] = true;
		nItemTime[SHIELD] = 100;
	}
	else
		g_MyShip.InitMyShip_y-=1;	

	


}

int MissileCheck(bool assist)
{
	if(assist)
	{
		for(int m=0 ; m<MAX_ASSIST ; m++ )	// 최대 미사일 만큼
		{
			if( !g_AssistMissile[m].IsLive())	// 마사일이 없다면 포문 탈출
			{
				g_AssistMissile[m].init_x = g_MyShip.m_x;
				g_AssistMissile[m].type = g_MyShip.missiletype;
				return m;
			}
		}
	}
	else
	{
		for(int m=0 ; m<MAX_MISSILES ; m++ )	// 최대 미사일 만큼
		{
			if( !g_MyMissile[m].IsLive())	// 마사일이 없다면 포문 탈출
			{
				g_MyMissile[m].type = g_MyShip.type;
				return m;
			}
		}
	}
}

int ItemCheck(bool move)
{
	int i;

	if(move)
	{
		for(i=0 ; i<8 ; i++)
		{
			if( !g_Item[i].IsLive() )
				return i;
		}
	}
	else
	{
		for(i=0 ; i<3 ; i++)
		{
			if( item[i] == DEFAULT )
				return i;
		}
	}
}

int MissileAttack_Check(int m)
{
	int check_x = 2000;
	int temp_x=0, temp_y=0;
	int result;
	int i=0,j=0;
	//int k,l;

	int k[MAX_PATTERN];
	int l[MAX_ENEMYS];

	for(i=0; i<MAX_PATTERN; i++)
		k[i] = 0;

	for(i=0; i<MAX_ENEMYS; i++)
		l[i] = 0;

	int temp = 0;

	for(i = 0 ; i<MAX_PATTERN ; i++)
	{
		for(j=0; j < MAX_ENEMYS; j++)
		{
			if(g_Enemy[i][j].IsLive() && g_Enemy[i][j].m_y > 0 && g_Enemy[i][j].m_x > 0 && g_Enemy[i][j].m_x < 650 )
			{
				if(g_AssistMissile[m].IsLive() && g_AssistMissile[m].targetOn == false)
				{ 
					if(g_AssistMissile[m].m_y > g_Enemy[i][j].m_y)
					{
						k[temp] = i;
						l[temp] = j;
						temp++;
					}
				}
			}
		}
	}

	if(temp != 0 && g_AssistMissile[m].targetOn == false)
	{
		result = rand()%temp;

		g_AssistMissile[m].i = k[result];
		g_AssistMissile[m].j = l[result];

		return g_Enemy[k[result]][l[result]].m_x; 
	}
	else if(g_AssistMissile[m].targetOn == true)
	{
		if(g_Enemy[g_AssistMissile[m].i][g_AssistMissile[m].j].IsLive())
			return g_Enemy[g_AssistMissile[m].i][g_AssistMissile[m].j].m_x; 
	}
	else if(temp == 0)
	{
		return g_AssistMissile[m].m_x;
	}


	return g_AssistMissile[m].m_x;

}


bool TimerCheck(int &timer, int time, int type)
{
	int i, j=0;

	if(timer >= time)
	{
		timer = 0;

		for(i=0; i<TimerCheck_temp ; i++)
		{	
			if(TimerCheck_temp != 5)
				TimerCheck_item[i] = TimerCheck_item[i+1];
			else
				TimerCheck_item[i] = 0;

		}
		if(TimerCheck_temp != 0)
			TimerCheck_temp--;
		return true;
	}
	else
	{
		timer++;

		for(i=0; i <5 ; i++)
			if(TimerCheck_item[i] == type && type != 0)
			{
				j++;
			}

		if(j==0 && type != 0)
		{
			TimerCheck_item[TimerCheck_temp] = type;
			TimerCheck_temp++;
		}


		for(i=0; i<TimerCheck_temp; i++)			
			if(timer > time - 100)
			{
				if((timer % 12)<6)
				{
					g_ItemSprite.Drawing(TimerCheck_item[i]-1, 650-30, 30 + (i*45), g_lpSecondarySurface, true);

					if(bItem[SHIELD])
						g_ShieldSprite.Drawing( 0, g_MyShip.m_x, g_MyShip.m_y, g_lpSecondarySurface, true);
				}
			}
			else if(timer > 0)
			{
				if(bItem[SHIELD])
						g_ShieldSprite.Drawing( 0, g_MyShip.m_x, g_MyShip.m_y, g_lpSecondarySurface, true);
				g_ItemSprite.Drawing(TimerCheck_item[i]-1, 650-30, 30 + (i*45), g_lpSecondarySurface, true);
			}


		return false;
	}
}


void AssistMissile(bool flag)
{

	switch(g_MyShip.missiletype)
	{
		case 1:
			switch(g_MyShip.assistlevel)
			{
				case 0:
					A_MAX_MISSILE[g_MyShip.missiletype-1] = 2;
					A_MISSILE_DELAY[g_MyShip.missiletype-1] = 800;
					A_MY_MISSILE_INTERVAL[g_MyShip.missiletype-1] = 200;

					if(flag)
					{
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-10,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY()-5, &g_Timer, 0, 10, 5);		
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+10,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY()-5, &g_Timer, 0, 10, 5);	
					}
					break;

				case 1:
					A_MAX_MISSILE[g_MyShip.missiletype-1] = 2;
					A_MISSILE_DELAY[g_MyShip.missiletype-1] = 700;
					A_MY_MISSILE_INTERVAL[g_MyShip.missiletype-1] =175;

					if(flag)
					{
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-10,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY()-5, &g_Timer, 0, 10, 5, 0, true);		
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+10,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY()-5, &g_Timer, 0, 10, 5, 0, true);	

						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-6,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY(), &g_Timer, 0, 10, 5);
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+6,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY(), &g_Timer, 0, 10, 5);
					}
					break;

				case 2:
					A_MAX_MISSILE[g_MyShip.missiletype-1] = 2;
					A_MISSILE_DELAY[g_MyShip.missiletype-1] = 600;
					A_MY_MISSILE_INTERVAL[g_MyShip.missiletype-1] = 150;

					if(flag)
					{
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-10,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY()+5, &g_Timer, 0, 10, 5);		
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+10,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY()+5, &g_Timer, 0, 10, 5);	

						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+1,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY(), &g_Timer, 0, 10, 5);		
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-1,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY(), &g_Timer, 0, 10, 5);

						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-10,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY()+5, &g_Timer, 0, 10, 5, 0, true);		
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+10,		// 미사일 초기화 위치를 잡아준다.
							g_MyShip.GetY()+5, &g_Timer, 0, 10, 5, 0, true);
					}
					break;
			}
			break;

		case 2:
			switch(g_MyShip.assistlevel)
			{
				case 0:
					A_MAX_MISSILE[g_MyShip.missiletype-1] = 1;
					A_MISSILE_DELAY[g_MyShip.missiletype-1] = 1000;
					A_MY_MISSILE_INTERVAL[g_MyShip.missiletype-1] = 150;
					break;

				case 1:
					A_MAX_MISSILE[g_MyShip.missiletype-1] = 2;
					A_MISSILE_DELAY[g_MyShip.missiletype-1] = 900;
					A_MY_MISSILE_INTERVAL[g_MyShip.missiletype-1] = 120;
					break;

				case 2:
					A_MAX_MISSILE[g_MyShip.missiletype-1] = 3;
					A_MISSILE_DELAY[g_MyShip.missiletype-1] = 800;
					A_MY_MISSILE_INTERVAL[g_MyShip.missiletype-1] = 80;
					break;

				
			}
			if(flag)
			{
				
				g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[1], g_MyShip.GetX()-10,		// 미사일 초기화 위치를 잡아준다.
					g_MyShip.GetY()-5, &g_Timer, 0, 10, 5);	
				g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[1], g_MyShip.GetX()+10,		// 미사일 초기화 위치를 잡아준다.
					g_MyShip.GetY()-5, &g_Timer, 0, 10, 5);	
			}
			break;
	}
}

int ExplodingCheck()
{
	int i;

	for(i=0 ; i<MAX_EXPLODES; i++)
	{
		if(!g_Exploding[i].IsLive())
		{
			return i;
		}
	}
}

void InitEnemy(int m)
{
	int i;

	switch(STAGE)
	{
		case 1:
			{
				EnemyLife[0] = 1;
				EnemyLife[1] = 1;
				EnemyLife[2] = 1;
				EnemyLife[3] = 1;
				EnemyLife[4] = 1;
				EnemyLife[5] = 1;
				EnemyLife[6] = 1;
				EnemyLife[7] = 1;
				EnemyLife[8] = 1;
				EnemyLife[9] = 1;
				EnemyLife[10] = 1;
				EnemyLife[11] = 1;
				EnemyLife[12] = 1;
				EnemyLife[13] = 1;	
				EnemyLife[14] = 40;
				EnemyLife[15] = 1;
				EnemyLife[16] = 1;
				EnemyLife[17] = 1;
				EnemyLife[18] = 1;
				EnemyLife[19] = 1;
				EnemyLife[20] = 1;
				EnemyLife[21] = 1;
				EnemyLife[22] = 1;
				EnemyLife[23] = 1;
			}
			break;

		case 2:
			{
				EnemyLife[0] = 1;
				EnemyLife[1] = 2;
				EnemyLife[2] = 2;
				EnemyLife[3] = 2;
				EnemyLife[4] = 2;
				EnemyLife[5] = 2;
				EnemyLife[6] = 2;
				EnemyLife[7] = 2;
				EnemyLife[8] = 2;
				EnemyLife[9] = 2;
				EnemyLife[10] = 2;
				EnemyLife[11] = 2;
				EnemyLife[12] = 2;
				EnemyLife[13] = 2;	
				EnemyLife[14] = 70;
				EnemyLife[15] = 2;
				EnemyLife[16] = 2;
				EnemyLife[17] = 2;
				EnemyLife[18] = 2;
				EnemyLife[19] = 2;
				EnemyLife[20] = 2;
				EnemyLife[21] = 1;
				EnemyLife[22] = 180;
				EnemyLife[23] = 70;
			}
			break;

		case 3:
			{
				EnemyLife[0] = 2;
				EnemyLife[1] = 2;
				EnemyLife[2] = 2;
				EnemyLife[3] = 2;
				EnemyLife[4] = 2;
				EnemyLife[5] = 2;
				EnemyLife[6] = 2;
				EnemyLife[7] = 2;
				EnemyLife[8] = 2;
				EnemyLife[9] = 2;
				EnemyLife[10] = 2;
				EnemyLife[11] = 2;
				EnemyLife[12] = 2;
				EnemyLife[13] = 2;	
				EnemyLife[14] = 20;
				EnemyLife[15] = 2;
				EnemyLife[16] = 2;
				EnemyLife[17] = 2;
				EnemyLife[18] = 2;
				EnemyLife[19] = 2;
				EnemyLife[20] = 2;
				EnemyLife[21] = 1;
				EnemyLife[22] = 1;
				EnemyLife[23] = 1;
			}
			break;
	}

		

	for(i=0; i<MAX_ENEMYS ; i++)
	{
		g_Enemy[m][i].life = EnemyLife[m];
		g_Enemy[m][i].score = EnemyLife[m] * 5;
	}
	
}

void EnemyRotate(int i, int j)
{
	if(g_Enemy[i][j].after_x < g_Enemy[i][j].m_x) //오른쪽으로 이동
	{
		if(g_Enemy[i][j].after_y < g_Enemy[i][j].m_y)	// 오른쪽 아래로 이동
		{
			if(g_Enemy[i][j].drawframe == 4)
				g_Enemy[i][j].drawframe = 5;
			else if(g_Enemy[i][j].drawframe == 7)
				g_Enemy[i][j].drawframe = 8;
			else
				g_Enemy[i][j].drawframe = 8;
		}
		else if(g_Enemy[i][j].after_y > g_Enemy[i][j].m_y)	// 오른쪽 위로 이동
		{
			if(g_Enemy[i][j].drawframe == 4)
				g_Enemy[i][j].drawframe = 3;
			else if(g_Enemy[i][j].drawframe == 1)
				g_Enemy[i][j].drawframe = 2;
			else 
				g_Enemy[i][j].drawframe = 2;
		}
		else
		{
			g_Enemy[i][j].drawframe = 4;
		}
		
	}
	else if(g_Enemy[i][j].after_x > g_Enemy[i][j].m_x) //왼쪽으로 이동
	{
		if(g_Enemy[i][j].after_y < g_Enemy[i][j].m_y) // 왼쪽 아래로이동
		{
			if(g_Enemy[i][j].drawframe==10)
				g_Enemy[i][j].drawframe = 9;
			else if(g_Enemy[i][j].drawframe == 7)
				g_Enemy[i][j].drawframe = 8;
			else 
				g_Enemy[i][j].drawframe = 8;
		}
		else if(g_Enemy[i][j].after_y > g_Enemy[i][j].m_y)	// 왼쪽 위로 이동
		{
			if(g_Enemy[i][j].drawframe == 10)
				g_Enemy[i][j].drawframe = 11;
			else if(g_Enemy[i][j].drawframe == 1)
				g_Enemy[i][j].drawframe = 0;
			else 
				g_Enemy[i][j].drawframe = 0;
		}
		else
		{
			g_Enemy[i][j].drawframe = 10;
		}
	}
	else
	{
		if(g_Enemy[i][j].after_y < g_Enemy[i][j].m_y)	// 아래로 이동
		{
			g_Enemy[i][j].drawframe = 7;			
		}
		else if(g_Enemy[i][j].after_y > g_Enemy[i][j].m_y)	// 위로 이동
		{
			g_Enemy[i][j].drawframe = 1;
		}
		else	// 멈춤
		{
			g_Enemy[i][j].drawframe = 7;
		}
	}

	g_Enemy[i][j].after_x = g_Enemy[i][j].m_x;
	g_Enemy[i][j].after_y = g_Enemy[i][j].m_y;
}
	
int EnemyMissileCheck(int i, int j)
{
	int k;

	for(k=0; k<MAX_ENEMY_MISSILES ; k++)
	{
		if(!g_EnemyMissile[i][j][k].IsLive())
			return k;
	}
}

void GameEnd()
{
	int i;

	int score_x = 472, score_y = 300-40;

	if(g_MyShip.life <= 0 || Player[1].End == 1)
	{
		if(g_GameMunu == SINGPLAY)
		{
			g_SingleBoardSprite.Drawing(0, 400, 300, g_lpSecondarySurface, true);
			g_LoseSprite.Drawing(0, 400-2, 300+49, g_lpSecondarySurface, true);			
		}
		
		if(g_GameMunu == MULTYPLAY)
		{
			g_BoardSprite.Drawing(0, 400, 300, g_lpSecondarySurface, true);
			
			if(Player[0].score > Player[1].score)
				g_WinSprite.Drawing(0, 400-2, 300, g_lpSecondarySurface, true);	
			else if(Player[0].score < Player[1].score)
				g_LoseSprite.Drawing(0, 400-2, 300, g_lpSecondarySurface, true);
			else
				g_DrawSprite.Drawing(0, 400-2, 300, g_lpSecondarySurface, true);

			IntToArray(Player[1].score, ScoreArray, 5);
			for(i=0 ; i<5; i++)
			{
				g_Score.Drawing(ScoreArray[i], 472+(i*15), 300-40, g_lpSecondarySurface, true);
			}
			
		}

		IntToArray(Player[0].score, ScoreArray, 5);
		for(i=0 ; i<5; i++)
		{
			g_Score.Drawing(ScoreArray[i], 472+(i*15), 300-20, g_lpSecondarySurface, true);
		}
		
		Player[0].End = 1;

	}
	else if(STAGE ==2 && timevar == 3700 && !g_Enemy[22][0].IsLive())
	{
		if(g_GameMunu == SINGPLAY)
		{
			g_SingleBoardSprite.Drawing(0, 400, 300, g_lpSecondarySurface, true);
			g_WinSprite.Drawing(0, 400-2, 300+49, g_lpSecondarySurface, true);
		
		}
		
		if(g_GameMunu == MULTYPLAY)
		{
			g_BoardSprite.Drawing(0, 400-2, 300, g_lpSecondarySurface, true);
			
			if(Player[0].score > Player[1].score)
			{
				g_WinSprite.Drawing(0, 400-2, 300, g_lpSecondarySurface, true);					
			}
			else if(Player[0].score < Player[1].score)
			{
				g_LoseSprite.Drawing(0, 400-2, 300, g_lpSecondarySurface, true);

			}
			else
			{
				g_DrawSprite.Drawing(0, 400-2, 300, g_lpSecondarySurface, true);
			}

			IntToArray(Player[1].score, ScoreArray, 5);
			for(i=0 ; i<5; i++)
			{
				g_Score.Drawing(ScoreArray[i], 472+(i*15), 300-40, g_lpSecondarySurface, true);
			}
			
		}
		IntToArray(Player[0].score, ScoreArray, 5);
		for(i=0 ; i<5; i++)
		{
			g_Score.Drawing(ScoreArray[i], 472+(i*15), 300-20, g_lpSecondarySurface, true);
		}

		Player[0].End = 1;
	}
}
