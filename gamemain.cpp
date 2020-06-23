//gamemain.cpp
#include <ddraw.h>				// ���̷�Ʈ ��ο�(����Ʈ) ��� ������ �ҷ��´�.
#include <dinput.h>				// ���̷�Ʈ ��ǲ(�Է�) ��� ������ �ҷ��´�.

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
#include "object.h"

#include "define.h"

#include "stdio.h"				// ���ڿ� ����� ���� ��� ������ �ҷ��´�.
#include <windows.h>			// �������� ���� ��� ������ �ҷ��´�.

#include <dsound.h>				// ���̷�Ʈ ����(����) ��������� �ҷ��´�.
#include "dsutil.h"				// 

#include <math.h>



// �Լ����� ���� ///////////////////////////////////////////////////
BOOL DirectInputKeyboardDown( LPDIRECTINPUTDEVICE8 lpKeyboard, int dikcode);	// Ű���� �Է¹޴� �Լ�
////////////////////////////////////////////////////////////////////

// �ܺκ��� ���� ///////////////////////////////////////////////////
extern LPDIRECTDRAWSURFACE7		g_lpPrimarySurface;			// 1��, 2�� ǥ��
extern LPDIRECTDRAWSURFACE7		g_lpSecondarySurface;
extern LPDIRECTINPUT8			g_lpDirectInputObject;		// �Է��� ����ϱ� ���� ���� ����
extern LPDIRECTINPUTDEVICE8		g_lpDirectInputKeyboard;	// Ű���忡�� �޾ƿ� ���� ó���ϱ� ���� ��������
extern CTimer					g_Timer;				// Ÿ�̸� ����

extern CSprite			g_BackgroundSprite;		// ��� ��������Ʈ
extern CSprite			g_State;
extern CBossMissile		g_BossMissile[MAX_BOSS_YMISSILE][MAX_BOSS_XMISSILE];	// ���� �̻����� �迭
extern CSprite			g_BossMissileSprite;			// ���� �̻��� �� ����
extern CBoss			g_Boss[MAX_BOSS];
extern CSprite			g_BossSprite;

extern CEnemyMissile	g_EnemyMissile[MAX_PATTERN][MAX_ENEMYS][MAX_ENEMY_MISSILES];	// �� �̻����� �迭
extern CSprite			g_EnemyMissileSprite[10];		// �� �̻��� ��������Ʈ
extern CEnemy			g_Enemy[MAX_PATTERN][MAX_ENEMYS];	// ������� �迭
extern CSprite			g_EnemySprite[10];	// ���� ��������Ʈ

extern CMyShip			g_MyShip;		// �÷��̾�
extern CSprite			g_MyShipSprite;	// �÷��̾� ��������Ʈ
extern CMyMissile		g_MyMissile[MAX_MISSILES];	// �� �̻����� �迭
extern CSprite			g_MyMissileSprite[3];	// �� �̻����� ��������Ʈ
extern CSprite			g_MyLifeSprite;

extern CExploding		g_Exploding[MAX_EXPLODES];		// ���� ó�� �迭
extern CSprite			g_ExplodingSprite[2];		// ���� ��������Ʈ

extern CSprite			g_AssistMissileSprite[2];
extern CAssistMissile	g_AssistMissile[MAX_ASSIST];

extern CSprite			g_WinSprite;		// ���� ������ ��������Ʈ
extern CSprite			g_LoseSprite;		// ���� ���н� ��������Ʈ 
extern CSprite			g_DrawSprite;		// ���� ������� ��������Ʈ 
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

extern HSNDOBJ Sound[10];			// ���� �迭
extern void _Play(int num);			// ���� �÷��� �Լ�

extern int				attack_item;

static BOOL m_bGameFirst = TRUE;		// ���� �ʱ� 
static BOOL m_bGameDead  = FALSE;		// ���� ����
//static BOOL m_bGameClear = FALSE;		// ���� ����
static BOOL m_bBoss		 = FALSE;		// ����
static BOOL m_bInitMyShip = true;		// ��� �װ��� üũ

CPlayer Player[2];


int flag = 0, bgflag = 0;	// �� ����
int item[3];
extern int lazer_x;
extern int GameStart;
//char wtime[1];	// ���ۺ��� �ʳ��������� �ð�

static char szReplay[] = "You Dead... Replay? (y/n)";	// ������ �޽���
static char szWin[]	   = "You Win... Replay? (y/n)";	// �̰����� �޽���

void InitGame();		// ���� �ʱ�ȭ �Լ�
void InitInterface();	// �������̽� �ʱ�ȭ
void MyShipItemCheck();	//������ üũ
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
	DEFAULT,	//�Ϲ�
	SLOW,	//������
	FAST,	//������
	SHIELD,	//����
	CHANGE,	//���� �������� �ݴ��
	MISSILE,	//�ڽŰ� ���� ��ġ�� �̻��� ����
	STOP,	//�Ͻ�����
	ENEMY,	//�� ���� ����
	POWER_D,	//���� �Ŀ� �ٿ�
	POWER_U
}ITEM_U;

typedef enum
{	
	RED,	//���� ���� �̻��� ���Ѱ�
	GREEN,	//������ ���� �������� �����̻��� ���� ���Ѱ� ������ ����
	BLUE,	//������ ���� �̻��� ���Ѱ�
	LIFE	//������
}ITEM_D;



int nItemTime[10];
static int nMissileTime = g_Timer.time();
static int A_nMissileTime = g_Timer.time();
int MY_MISSILE_INTERVAL[3];		// �� �̻����� ������
int A_MY_MISSILE_INTERVAL[2];
int MAX_MISSILE[3];				// �� �̻��� �ִ�
int MISSILE_DELAY[3];			// �̻��� ��� ���� ���ߴ� ������

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
void MainMenu(void)		//���� ����
{
	static int inputkey = g_Timer.time();

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN))		// �Ʒ�������
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

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP))		// ��������
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


	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,300))
		{
			AboutTemp--;
			if(AboutTemp==0)
				AboutTemp=4;
		}
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT))		// ��������
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

	HRESULT hResult;				// �ø��� ����
	if(FAILED(hResult = g_lpPrimarySurface->Flip(NULL,DDFLIP_WAIT)))	
	{
		if(hResult == DDERR_SURFACELOST)	// ���̷�Ʈ ��ο찡 ������ ���� �ٽ� 
			g_lpPrimarySurface->Restore();
	}
}

void GameMain(void)		//���� ����
{
//	wtime[1] = g_Timer.time();



	

	if(m_bGameFirst==TRUE) InitGame();	// �����ʱ� �ʱ�ȭ �Լ� ȣ��

	int i, j, m, m2;	// ���� ����
	


	static int time = 0;		// Ÿ���� 0����
	static int nLastMissileTime = g_Timer.time();
	static int nLastMissileTime2 = g_Timer.time();

	static int A_nLastMissileTime = g_Timer.time();



	if(bgflag == 0)
		g_BackgroundSprite.Drawing2( 0, 0, g_lpSecondarySurface, false);  // ��� ��������Ʈ�� �׸���
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
	MyShipItemCheck();		//������ üũ 
	MyShipCheck();			//üũ�� ������ ����
	MyMissile(false);
	AssistMissile(false);	

	if(m_bInitMyShip)
		MyShipInit();
	


	if(bItem[MISSILE] && g_MyShip.IsLive() && !bItem[SHIELD])	
	{
		if( abs(g_MyShip.GetX() - g_Attack[1].GetX()) < 15 )	
		{
			g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_MyShip.GetX(),	// ���� �ʱ�ȭ 
				g_MyShip.GetY(), &g_Timer, 0, 10);		// ��ġ����
		
			

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

			
			_Play(2);		// 2�� ���� ���
		}
	}
	
	

//	bgflag = 1;

	if(m_bBoss == TRUE)		// ���� Ʈ���
	{
		//Boss
		for( i=0 ; i<MAX_BOSS ; i++ ) // �ִ� ���� ��ŭ
		{
			if(g_Boss[i].IsLive())		// ������ ����ִٸ�
			{
				//g_Boss[i].Move();
				if( (g_MyShip.GetX() - g_Boss[i].GetX()) >  30 ) g_Boss[i].m_speedx = 2;	// ������ �÷��̾� ���� ���ʿ� �ִٸ� ���ǵ带 ����������
				if( (g_MyShip.GetX() - g_Boss[i].GetX()) < -30 ) g_Boss[i].m_speedx = -2;	// �����ʿ� �ִٸ� ���ǵ带 ��������
				g_Boss[i].m_x += g_Boss[i].m_speedx;	// ������ x��ǥ�� speed���� ���� �����δ�.

				g_Boss[i].Draw( g_lpSecondarySurface);		// ������ �׸���.
			}

			for( m=0 ; m<MAX_BOSS_YMISSILE ; m++)		// ���� �̻����� y�ุŭ
			{
				if( time % 51 == 0)	// Ÿ���� ���� ������ ���� 0�̶�� ( ������ ������ )
				{
					for( m2=0 ; m2<MAX_BOSS_XMISSILE ; m2++ )	// ���� �̻����� x�ุŭ
					{


						if( !g_BossMissile[m][m2].IsLive()   &&   g_Boss[i].IsLive() )	// ���� �̻����� ���� ������ ���������
						{
							g_BossMissile[m][m2].Initialize( &g_BossMissileSprite, g_Boss[i].GetX(),	// ���� �̻��� �� �ʱ�ȭ ������ ��ġ�� ���� ����Ұ��� ��ġ�� ����ش�.
								g_Boss[i].GetY()+80, &g_Timer, 0, 10, 5 );
							g_BossMissile[m][0].m_speedx = 2;	// �Ѿ� �ϳ��� �������� 
							g_BossMissile[m][1].m_speedx = 0;	// �Ѿ� �ϳ��� �׳� �Ʒ���
							g_BossMissile[m][2].m_speedx = -2;	// �Ѿ� �ϳ��� ���������� 
						}
					}
				}
				time++;	// �����̰� ����
			}
		}
	}

	//�Ѿ� �߻�
	if( DirectInputKeyboardDown (g_lpDirectInputKeyboard, DIK_X) )	// �����̽��� �����ٸ�
	{
		if(g_MyShip.IsLive() || g_MyShip.InitMyShip_y < 610)	//�÷��̾ ����ִٸ�
		{
			if(g_Timer.elapsed( nLastMissileTime, MY_MISSILE_INTERVAL[g_MyShip.type]))	// �̻��� ��� ������ ���� ��ٸ�
			{
				isMyMissile=1;
				if(g_Timer.missile_check >= MAX_MISSILE[g_MyShip.type])	// m�� �ִ� �̻��� ������ �ö��ٸ�
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
					
					_Play(1);		// 1�� ���� ���
				}
			}


			if(g_MyShip.missiletype>0)
			{
				if(g_Timer.elapsed( A_nLastMissileTime, A_MY_MISSILE_INTERVAL[g_MyShip.missiletype-1]))	// �̻��� ��� ������ ���� ��ٸ�
				{
					if(g_Timer.assist_missile_check >= A_MAX_MISSILE[g_MyShip.missiletype-1])	// m�� �ִ� �̻��� ������ �ö��ٸ�
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
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=0;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=0;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=0;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
				}

				if(i>14 && i<19 && g_Enemy[i][j].sprite == 2)
				{
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[i][j].GetY(), &g_Timer, 0, 100, 5);
					
					
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedx=-3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy=3;
					g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[3], g_Enemy[i][j].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
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
	if(m_bGameClear == TRUE) g_ClearSprite.Drawing(0, 400, 300, g_lpSecondarySurface, true);	// ���� �̰����� �̹��� ���
	if(m_bGameDead  == TRUE) g_DeadSprite.Drawing(0, 400, 300, g_lpSecondarySurface, true);		// ���� ������ �̹��� ���
*/

	GameEnd();


	//Flipping
	HRESULT hResult;				// �ø��� ����
	if(FAILED(hResult = g_lpPrimarySurface->Flip(NULL,DDFLIP_WAIT)))	
	{
		if(hResult == DDERR_SURFACELOST)	// ���̷�Ʈ ��ο찡 ������ ���� �ٽ� 
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

	// �� �̻��� �׸���
	for( i=0 ; i<MAX_PATTERN ; i++)
		for( j=0 ; j<MAX_ENEMYS ; j++)	// ���� ����ŭ
			for(k=0; k<MAX_ENEMY_MISSILES ; k++)
				if(g_EnemyMissile[i][j][k].IsLive())	// ���� �̻����� ������
				{
				
					g_EnemyMissile[i][j][k].Move(g_MyShip.m_x, g_MyShip.m_y, i, j, k);	// ��������
				
					if(i != 23)
						g_EnemyMissile[i][j][k].Draw(g_lpSecondarySurface);	// �׸���.
					else
						g_EnemyMissile[i][j][k].DrawFrame(g_lpSecondarySurface);	// �׸���.
				}
				


	//���� ������ ó���� �׸���
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
				int nansu = rand()%120;	// �������� 100������ ���� �߻�
				if(nansu == 1)		// �׼��� 1�̶��
				{
					if( !g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].IsLive()   &&   g_Enemy[i][j].IsLive() )	// ���̻����� ���� ���� ����ִٸ�
					{
						g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].m_speedy = 6;
						g_EnemyMissile[i][j][EnemyMissileCheck(i,j)].Initialize( &g_EnemyMissileSprite[0], g_Enemy[i][j].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
							g_Enemy[i][j].GetY()+20, &g_Timer, 0, 100, 5);
						

					}
				}
			}
			else if(i==14)
			{
				if(STAGE==1)
				{
					int nansu = rand()%800;	// �������� 100������ ���� �߻�
					if(nansu == 1)		// �׼��� 1�̶��
					{/*
						for(m=0; m<5; m++)
						{
							if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive()   &&    g_Enemy[14][m].IsLive() )	// ���̻����� ���� ���� ����ִٸ�
							{
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = -2;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 4;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX()-20,	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
									g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
							}
							if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive()   &&    g_Enemy[14][m].IsLive() )	
							{
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = 0;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 4;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
									g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
							}
							if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive()   &&    g_Enemy[14][m].IsLive() )	
							{
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = 2;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 4;
								g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX()+20,	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
									g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
							}
						}*/
					}
				}
				else if(STAGE==2)
				{
					int nansu = rand()%800;	// �������� 100������ ���� �߻�

					if(g_Enemy[14][8].IsLive())		// �׼��� 1�̶��
					{
						if(nansu == 1)
						{
							if( !g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].IsLive())	// ���̻����� ���� ���� ����ִٸ�
							{
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedx = -2;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedy = 6;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][0].GetX()-20,	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
									g_Enemy[14][0].GetY()+20, &g_Timer, 0, 100, 5);							
							}
							if( !g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].IsLive())	
							{
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedx = 0;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedy = 6;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][0].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
									g_Enemy[14][0].GetY()+20, &g_Timer, 0, 100, 5);
								
							}
							if( !g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].IsLive())	
							{
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedx = 2;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].m_speedy = 6;
								g_EnemyMissile[14][0][EnemyMissileCheck(14,0)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][0].GetX()+20,	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
									g_Enemy[14][0].GetY()+20, &g_Timer, 0, 100, 5);							
							}
						}
						
					}

				

					if(g_Enemy[22][0].IsLive() && g_Enemy[22][0].m_y > 150 && attack_check == 0)
					{
						InitEnemy(23);
						attack_check = 1;

						g_Enemy[23][0].Initialize(&g_EnemySprite[9], g_Enemy[22][0].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
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
			g_EnemyMissile[23][0][EnemyMissileCheck(23,0)].Initialize( &g_EnemyMissileSprite[5], g_Enemy[23][0].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
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

	if(time%temp == 0)	// Ÿ���� ���� ������ ���� 0�̶�� ( ������ ������ )
	{
		for(m=0; m<5 ;m++)
		{
			if(g_Enemy[14][m].IsLive() && g_Enemy[14][m].m_y > 80 )
			{
				if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive())	// ���̻����� ���� ���� ����ִٸ�
				{
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = -2;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 3;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX()-20,	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
				}
				if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive())	
				{
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = 1;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 4;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
				}
				if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive())	
				{
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = -1;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 4;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX(),	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
				}
				if( !g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].IsLive())	
				{
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedx = 2;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].m_speedy = 3;
					g_EnemyMissile[14][m][EnemyMissileCheck(14,m)].Initialize( &g_EnemyMissileSprite[1], g_Enemy[14][m].GetX()+20,	// �� �̻��� �ʱ�ȭ �ϰ� ��ġ�� ����ش�.
						g_Enemy[14][m].GetY()+20, &g_Timer, 0, 100, 5);								
				}	
			}
		}
	}
	if(STAGE == 1)
	{
		time++;	// �����̰� ����
		attack_check++;
	}
	



	


	//Boss Missile Draw
	for( m=0 ; m<MAX_BOSS_YMISSILE ; m++)	// ���� �̻����� y�� ��ŭ
	{
		for( m2=0 ; m2<MAX_BOSS_XMISSILE ; m2++)		// �����̻����� x�� ��ŭ
		{
			if( g_BossMissile[m][m2].IsLive() )	// �����̻����� �ִٸ�
			{
				g_BossMissile[m][m2].Move();	// ��������
				g_BossMissile[m][m2].Draw(g_lpSecondarySurface);	// �׷��ش�.
			}
		}
	}
 
	//My �̻��� �׸���

		
	for( m=0 ; m<MAX_MISSILES ; m++)	// �̻����� �ִ� ����ŭ
	{
		if(g_MyMissile[m].IsLive())		// �÷��̾� �̻����� �ִٸ�
		{
			g_MyMissile[m].Move();		// �������� 
			
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


	for( m=0 ; m<MAX_ASSIST ; m++)	// �̻����� �ִ� ����ŭ
	{
		if(g_AssistMissile[m].IsLive())		// �÷��̾� �̻����� �ִٸ�
		{
			if(g_AssistMissile[m].type == 1)
			{
				g_AssistMissile[m].Move();		// �������� 
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

	
	//�� ���༱�� ������ ó���� �׸���
	int nMyShipFrame = 0; //center
	
	if(Player[0].End != 1)
	{
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP) &&
			DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT))	// ����������
		{
			g_MyShip.Upright();
			if(bItem[CHANGE])
				nMyShipFrame = 2;
			else
				nMyShipFrame = 1;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP) &&
			DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT))		// ��������
		{
			g_MyShip.Upleft();
			if(bItem[CHANGE])
				nMyShipFrame = 1;
			else
				nMyShipFrame = 2;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN) &&
			DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT))	// �����ʾƷ���
		{
			g_MyShip.Downright();
			if(bItem[CHANGE])
				nMyShipFrame = 1;
			else
				nMyShipFrame = 2;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN) &&
			DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT))		// ��������
		{
			g_MyShip.Downleft();
			if(bItem[CHANGE])
				nMyShipFrame = 2;
			else
				nMyShipFrame = 1;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_LEFT))		// ��������
		{
			g_MyShip.Left();	// �������� �����δ�.
			if(bItem[CHANGE])
				nMyShipFrame = 2;
			else
				nMyShipFrame = 1;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_RIGHT))		// ����������
		{
			g_MyShip.Right();	// ���������� �����δ�.
			if(bItem[CHANGE])
				nMyShipFrame = 1;
			else
				nMyShipFrame = 2;
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_UP))		// ��������
		{
			g_MyShip.Up();
		}
		
		if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_DOWN))		// �Ʒ�������
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

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_1))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = SLOW;
	}
	
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_2))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = FAST;
	}
	
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_3))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = SHIELD;
	}
	
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_4))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = CHANGE;
	}
	
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_5))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = MISSILE;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_6))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = STOP;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_7))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = ENEMY;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_8))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = POWER_D;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_9))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			item[ItemCheck()] = POWER_U;
	}



	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_Q))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
		{
			g_MyShip.type = RED;
			g_Timer.missile_check=0;
		}
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_W))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
		{
			g_MyShip.type = GREEN;
			g_Timer.missile_check=0;
		}
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_E))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
		{
			g_MyShip.type = BLUE;
			g_Timer.missile_check=0;
		}
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_A))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
		g_MyShip.missiletype = 1;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_S))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
		g_MyShip.missiletype = 2;
	}
	
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_P))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			if(g_MyShip.level < 4)
				g_MyShip.level++;
	}


	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_O))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			if(g_MyShip.level > 0)
				g_MyShip.level--;
	}

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_L))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			if(g_MyShip.assistlevel < 2)
				g_MyShip.assistlevel++;
		g_Timer.assist_missile_check = 0;
	}


	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_K))		// �Ʒ�������
	{
		if(g_Timer.elapsed(inputkey,500))
			if(g_MyShip.assistlevel > 0)
				g_MyShip.assistlevel--;
		g_Timer.assist_missile_check = 0;
	}


	


	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_C))		// �Ʒ�������
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

	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_D))		// �Ʒ�������
	{
		STAGE = 2;
		attack_check = 0;
	}
	if(DirectInputKeyboardDown(g_lpDirectInputKeyboard, DIK_F))		// �Ʒ�������
	{
		timevar = 3450;
	}


}

void Collision()
{
	int i, j , m, k;


	//�� �Ѿ˰� �� �浹 ������ ���� ó��
	for( m=0 ; m<MAX_ASSIST ; m++ )	// �ִ� �̻��ϱ���
	{
		for( i=0 ; i<MAX_PATTERN ; i++ )	// ������ �� ����ŭ 
		{
			for( j=0 ; j<MAX_ENEMYS ; j++)	// ������ �� ����ŭ
			{
				if(g_AssistMissile[m].IsLive()   &&   g_Enemy[i][j].IsLive() && g_Enemy[i][j].m_y > 0)  // ���̻��ϰ� ���� ������
				{
					if(abs(g_AssistMissile[m].GetX() - g_Enemy[i][j].GetX())<(g_Enemy[i][j].check_x/2))	// ���̻��ϰ� ���� �浹 �˻� 
						if(abs(g_AssistMissile[m].GetY() - g_Enemy[i][j].GetY())<(g_Enemy[i][j].check_y/2))	// abs�� ���밪 30�� �̹��� ũ��
						{
										// ���� ��ġ�� ���Ѵ�.
							g_AssistMissile[m].Kill();	// �� �̻��ϰ� ���� ���ش�.
							
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
								g_Exploding[ExplodingCheck()].Initialize(&g_AssistMissileExplodingSprite, g_AssistMissile[m].GetX(),	// ���ĸ� �ʱ�ȭ �Ѵ�
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
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_Enemy[i][j].GetX(),	// ���ĸ� �ʱ�ȭ �Ѵ�
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);
								else
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[1], g_Enemy[i][j].GetX(),	// ���ĸ� �ʱ�ȭ �Ѵ�
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);

								g_Enemy[i][j].Kill();
								Player[0].score += g_Enemy[i][j].score;
							}
							_Play(2);		// 2�� ���� ���
						}
				}
			}
		}
	}
	
	//�� �̻��ϰ� �� �浹 ������ ���� ó��
	for( m=0 ; m<MAX_MISSILES ; m++ )	// �ִ� �̻��ϱ���
	{
		for( i=0 ; i<MAX_PATTERN ; i++ )	// ������ �� ����ŭ 
		{
			for( j=0 ; j<MAX_ENEMYS ; j++)	// ������ �� ����ŭ
			{
				if(g_MyMissile[m].IsLive()   &&   g_Enemy[i][j].IsLive() && g_Enemy[i][j].m_y > 0)   // ���̻��ϰ� ���� ������
				{
					if(abs(g_MyMissile[m].GetX() - g_Enemy[i][j].GetX())<(g_Enemy[i][j].check_x/2))	// ���̻��ϰ� ���� �浹 �˻� 
						if(abs(g_MyMissile[m].GetY() - g_Enemy[i][j].GetY())<(g_Enemy[i][j].check_y/2))	// abs�� ���밪 30�� �̹��� ũ��
						{
										// ���� ��ġ�� ���Ѵ�.
							g_MyMissile[m].Kill();	// �� �̻��ϰ� ���� ���ش�.

							g_Enemy[i][j].life--;
							
							if(g_Enemy[i][j].life>0)
							{
								g_Exploding[ExplodingCheck()].Initialize(&g_MissileExplodingSprite, g_MyMissile[m].GetX(),	// ���ĸ� �ʱ�ȭ �Ѵ�
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
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_Enemy[i][j].GetX(),	// ���ĸ� �ʱ�ȭ �Ѵ�
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);
								else
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[1], g_Enemy[i][j].GetX(),	// ���ĸ� �ʱ�ȭ �Ѵ�
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);

								g_Enemy[i][j].Kill();
								Player[0].score += g_Enemy[i][j].score;
							}
							

							_Play(2);		// 2�� ���� ���
						}
				}
			}
		}
	}
	
	for( i=0 ; i<MAX_PATTERN ; i++ )	// ������ �� ����ŭ 
	{
		for( j=0 ; j<MAX_ENEMYS ; j++)	// ������ �� ����ŭ
		{
			for(m =0 ;m <2 ; m++)
			{
				if(g_Attack[m].IsLive()   &&   g_Enemy[i][j].IsLive() && g_Enemy[i][j].m_y > 0)  // ���̻��ϰ� ���� ������
				{
					if(abs(g_Enemy[i][j].GetX() - g_Attack[m].GetX())<(g_Enemy[i][j].check_x/2))	// ���̻��ϰ� ���� �浹 �˻� 
						if(abs(g_Enemy[i][j].GetY() - g_Attack[m].GetY())<300)	// abs�� ���밪 30�� �̹��� ũ��
						{						
							g_Enemy[i][j].life-=1;						
							
							if(g_Enemy[i][j].life>0)
							{
								g_Exploding[ExplodingCheck()].Initialize(&g_MissileExplodingSprite, g_Attack[m].GetX(),	// ���ĸ� �ʱ�ȭ �Ѵ�
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
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_Enemy[i][j].GetX(),	// ���ĸ� �ʱ�ȭ �Ѵ�
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);
								else
									g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[1], g_Enemy[i][j].GetX(),	// ���ĸ� �ʱ�ȭ �Ѵ�
										g_Enemy[i][j].GetY(), &g_Timer, 0, 10);

								g_Enemy[i][j].Kill();
								Player[0].score += g_Enemy[i][j].score;
							}
							_Play(2);		// 2�� ���� ���
						}
				}
				
				for( k =0; k<MAX_ENEMY_MISSILES ; k++)
				{
					if(g_EnemyMissile[i][j][k].IsLive()   &&   g_Attack[m].IsLive())		// ���̻��ϰ� �÷��̾ �ִٸ�
					{ 
						if(abs(g_EnemyMissile[i][j][k].GetX() - g_Attack[m].GetX())<15)		// �� �̻��ϰ� �÷��̾��� �浹�˻�
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
		
		// ���� �Ѿ˰� �� ����� �浹 ���� �� ���� ó��
	
		for( i=0 ; i<MAX_PATTERN ; i++ )		// ������ ���� ��ŭ
		{
			for( j=0 ; j<MAX_ENEMYS ; j++ )	// ������ ���� ��ŭ
			{
				for( k =0; k<MAX_ENEMY_MISSILES ; k++)
				{
					if(g_EnemyMissile[i][j][k].IsLive()   &&   g_MyShip.IsLive())		// ���̻��ϰ� �÷��̾ �ִٸ�
					{
						if(abs(g_EnemyMissile[i][j][k].GetX() - g_MyShip.GetX())<15)		// �� �̻��ϰ� �÷��̾��� �浹�˻�
							if(abs(g_EnemyMissile[i][j][k].GetY() - g_MyShip.GetY())<20)		// �̹��� ũ��
							{
								g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_MyShip.GetX(),	// ���� �ʱ�ȭ 
									g_MyShip.GetY(), &g_Timer, 0, 10);		// ��ġ����
								g_EnemyMissile[i][j][k].Kill();		// �� �̻��ϰ� �÷��̾ ���ش�
								
								
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
								
								
								_Play(2);		// 2�� ���� ���
							}
					}
				}
			}
		}
		
		
		// ���� �� ����� �浹 ���� �� ���� ó��
		for( i=0 ; i<MAX_PATTERN ; i++ )		// ������ ���� ��ŭ
		{
			for( j=0 ; j<MAX_ENEMYS ; j++ )	// ������ ���� ��ŭ
			{
				if(g_Enemy[i][j].IsLive()   &&   g_MyShip.IsLive())		// ���� �÷��̾ �ִٸ�
				{
					if(abs(g_Enemy[i][j].GetX() - g_MyShip.GetX())<(g_Enemy[i][j].check_x/2))		// ���� �÷��̾��� �浹�˻�
						if(abs(g_Enemy[i][j].GetY() - g_MyShip.GetY())<(g_Enemy[i][j].check_y/2))
						{
							g_Exploding[ExplodingCheck()].Initialize(&g_ExplodingSprite[0], g_Enemy[i][j].GetX(),	// ���� �ʱ�ȭ 
								g_Enemy[i][j].GetY(), &g_Timer, 0, 10);		// ��ġ����
							g_Enemy[i][j].Kill();		// �� �̻��ϰ� �÷��̾ ���ش�

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
							
							_Play(2);		// 2�� ���� ���
						}
				}
			}
		}
		
		/*
		// My �Ѿ˰� Boss �浹 ���� �� ���� ó��
		for( m=0 ; m<MAX_MISSILES ; m++ )		//  �ִ� �̻��� ����ŭ
		{	
		for( i=0 ; i<MAX_BOSS ; i++ )		// ���� ����ŭ
		{
		if( g_MyMissile[m].IsLive()   &&   g_Boss[i].IsLive()   &&   m_bBoss == TRUE )	// ������ ���Ӱ� ������ ����ְ� �̻����� �ִٸ�
		{
		if( abs(g_MyMissile[m].GetX() - g_Boss[i].GetX()) < 100 )		// ������ �̻����� �浹üũ
		if( abs(g_MyMissile[m].GetY() - g_Boss[i].GetY()) <70 )		// �̹��� ũ��
		{
		g_Exploding[m].Initialize(&g_ExplodingSprite, g_MyMissile[m].GetX(),	// ���� �ʱ�ȭ
		g_MyMissile[m].GetY(), &g_Timer, 0, 10);		// ���� ��ġ ����
		g_MyMissile[m].Kill();		// �̻����� ���ش�.
		g_Boss[i].m_Enegy -= 1;		// ���� ������ -1 �� 30
		
		  g_Exploding[m].Draw(g_lpSecondarySurface);	// �����̹����� �׸���.
		  _Play(2);	// 2������ ���
		  
			if(g_Boss[i].m_Enegy == 0)	// �����ǰ� 0�϶�
			{
			g_Boss[i].Kill();	// ������ ���ش�.
			MyShipWin();		// ���Ӽ��� �Լ� ȣ��
			}
			}
			}
			}
			}
		
		
		//Boss�Ѿ˰� �� ����� �浹 ���� �� ���� ó��
		for( i=0 ; i<MAX_EXPLODES ; i++ )	
		{
			for( m=0 ; m<MAX_BOSS_YMISSILE ; m++ )	// ������ ���� �̻��ϸ�ŭ
			{
				for( m2=0 ; m2<MAX_BOSS_XMISSILE ; m2++ )	// ������ ���� �̻��� ��ŭ
				{
					if(g_BossMissile[m][m2].IsLive()   &&   g_MyShip.IsLive())	// ������ �̻����� �ְ� �÷��̾ ������
					{
						if(abs(g_BossMissile[m][m2].GetX() - g_MyShip.GetX())<30)	// ���� �̻��ϰ� �÷��̾� �浹�˻�
							if(abs(g_BossMissile[m][m2].GetY() - g_MyShip.GetY())<20)	// �̹��� ũ��
							{
								g_Exploding[i].Initialize(&g_ExplodingSprite, g_BossMissile[m][m2].GetX(),	// ���� �ʱ�ȭ
									g_BossMissile[m][m2].GetY(), &g_Timer, 0, 10);	// ��ġ,������ ����
								g_BossMissile[m][m2].Kill();	// �����̻��� ����
								
								if(g_MyShip.life>0)	
								{
									g_MyShip.life--;
									m_bInitMyShip = true;
									
									if(g_MyShip.life==0)
									{
										MyShipDead();	// �÷��̾ �׾��ٴ� �Լ� ȣ��
										m_bInitMyShip = false;
									}
								}			
								
								g_MyShip.Kill();
								
								g_Exploding[i].Draw(g_lpSecondarySurface);	// �����̹��� ���
								_Play(2);	// 2�� ���� ���
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
							// Ű���� ���� ���� �������
	if(lpKeyboard->GetDeviceState(256,(LPVOID)KeyBuffer) == DIERR_INPUTLOST)
	{
		while( hResult = lpKeyboard->Acquire() == DIERR_INPUTLOST)	// ��� �ٽ� ���ش�.
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

	//�ʱ�ȭ
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
		if(g_Exploding[i].IsLive()) g_Exploding[i].Kill();		// ���İ� �ִٸ� ���ش�.

	//MyShip Init
	if(g_MyShip.IsLive()) g_MyShip.Kill();		// �÷��̾ ����ִٸ� ����
//	g_MyShip.Initialize(&g_MyShipSprite, 390, 570, &g_Timer, 0, 25, 5);	// �÷��̾� �ʱ�ȭ 

	for(k=0; k<3 ;k++)
	{
		for( m=0 ; m<MAX_MISSILES ; m++ )		
		{
			if(g_MyMissile[m].IsLive()) g_MyMissile[m].Kill();	// �̻����� �ִٸ� ����
		}
	}

	//Enemy Init
	for( i=0 ; i<MAX_PATTERN ; i++ )
		for( j=0 ; j<MAX_ENEMYS ; j++ )
		{
			if(g_Enemy[i][j].IsLive())  g_Enemy[i][j].Kill();		// ���� ���� �̻����� �ִٸ� ���� 

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
			g_Enemy[i][j].Initialize(&g_EnemySprite[0], rand()%430+60, rand()%300-320, &g_Timer, 0, 25, 5, 0);	// ���� �ʱ�ȭ

	for(i=0; i<8 ; i++)
		if(g_Item[i].IsLive())
			g_Item[i].Kill();


/*
		for(j=0;j<5;j++)
	g_Enemy[2][j].Initialize(&g_EnemySprite, (j*5)*(-30), 230, &g_Timer, 0, 25, 5);	// ���� �ʱ�ȭ
*/

	//Boss Init
	for(i=0 ; i<MAX_BOSS ; i++)		
	{
		if(g_Boss[i].IsLive())  g_Boss[i].Kill();		// ������ ������ ����
	}

	for(i=0 ; i<MAX_BOSS ; i++)
	{
		g_Boss[i].Initialize(&g_BossSprite,(i+1)*100, 130, &g_Timer, 0, 25, 5);		// ���� �ʱ�ȭ
		g_Boss[i].m_speedx=2;		// ���� ���ǵ� ����
		g_Boss[i].m_Enegy=30;			// ���� ������ ����
	}

	for( m=0 ; m<MAX_BOSS_YMISSILE ; m++ )
	{
		for(m2=0 ; m2<MAX_BOSS_XMISSILE ; m2++)
		{
			if(g_BossMissile[m][m2].IsLive())  g_BossMissile[m][m2].Kill();	// �����̻����� �ִٸ� ����
		}
	}
/*	
	m_bGameDead = FALSE;		// ���� ���� ����� �޽�
	m_bGameClear = FALSE;		// ���� ���� ����� �޽�
*/
	m_bGameFirst = FALSE;		// ���� ���� ����� �޽�
	m_bBoss = FALSE;			// ���� ���� ���� ���� �޽�
	bgflag = 0;


	SndObjPlay(Sound[0], DSBPLAY_LOOPING);	//	����迭 0��° ���� ���
}

void InitInterface()
{
	//srand(timeGetTime());
	
	// ���� ��� 
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


void _Play(int num)		// ���� �Լ�
{
	SndObjPlay(Sound[num], NULL);	// �ش��ȣ ���带 ����Ѵ�.
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
		case FAST:	//������
		case CHANGE:	//���� �������� �ݴ��
		case MISSILE:	//�ڽŰ� ���� ��ġ�� �̻��� ����
		case STOP:	//�Ͻ�����
		case ENEMY:	//�� ���� ����
		case POWER_D:	//���� �Ŀ� �ٿ�
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

		

		case SHIELD:	//����
		{
			bItem[SHIELD] = true;
			attack_item = DEFAULT;		
			item_check = 0;	
			nItemTime[SHIELD] = 0;
		}
		break;

		

		case POWER_U:	//�� �Ŀ� ��
		{
			bItem[POWER_U] = true;
			attack_item = DEFAULT;		
			item_check = 0;
		}
		break;
	}

	switch(g_MyShip.item)
	{
		
		case DEFAULT:	//�Ϲ�
		{
		}
		break;

		case SLOW:	//������
		{
			nItemTime[SLOW] = 0;
			g_MyShip.speed = 1;
			bItem[SLOW] = true;

		}
		break;

		case FAST:	//������
		{
			nItemTime[FAST] = 0;
			g_MyShip.speed = 10;
			bItem[FAST] = true;

			
		}
		break;

		

		case SHIELD:	//����
		{
		
		}
		break;

		case CHANGE:	//���� �������� �ݴ��
		{
			nItemTime[CHANGE] = 0;
			bItem[CHANGE] = true;


			
		}
		break;

		case MISSILE:	//�ڽŰ� ���� ��ġ�� �̻��� ����
		{

			if(!bItem[MISSILE])
				g_Attack[1].Initialize(&g_AttackSprite, lazer_x,
							300, &g_Timer, 0, 40);

			bItem[MISSILE] = true;			
			g_MyShip.item = DEFAULT;


		}
		break;

		case STOP:	//�Ͻ�����
		{
			nItemTime[STOP] = 0;
			bItem[STOP] = true;
			g_MyShip.speed = 0;


			
		}
		break;

		case ENEMY:	//�� ���� ����
		{
			bItem[ENEMY] = true;

			
		}
		break;

		case POWER_D:	//���� �Ŀ� �ٿ�
		{
			bItem[POWER_D] = true;

			
		}
		break;

		case POWER_U:	//���� �Ŀ� �ٿ�
		{
			
		}
		break;
	}
}


void IntToArray(int num,int ar[],int s) //�������� ���ڸ� �ϳ��� ����
{
	int div=(int)pow(10,s-1);  //pow�� ������   
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

	if(bItem[SLOW])	//������
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
	
	
	if(bItem[FAST])	//������
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
	
	
	
	
	if(bItem[SHIELD])	//����
	{
		if(TimerCheck( nItemTime[SHIELD], 300, SHIELD))
		{
			if(g_MyShip.item == SHIELD)
				g_MyShip.item = DEFAULT;
			bItem[SHIELD] = false;
			nItemTime[SHIELD] = 0;
		}		
	}
	
	
	if(bItem[CHANGE])	//���� �������� �ݴ��
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
	
	
	if(bItem[MISSILE])	//�ڽŰ� ���� ��ġ�� �̻��� ����
	{
		
		
		if(!g_Attack[1].IsLive())
		{
			bItem[MISSILE] = false;
			if(g_MyShip.item == MISSILE)
				g_MyShip.item = DEFAULT;
		}

	}
	
	
	if(bItem[STOP])	//�Ͻ�����
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
	
	
	if(bItem[ENEMY])	//�� ���� ����
	{
		bItem[ENEMY] = false;
		
		
	}
	
	
	if(bItem[POWER_D])	//���� �Ŀ� �ٿ�
	{
		bItem[POWER_D] = false;
		
		if(g_MyShip.level>0)
			g_MyShip.level--;
	}

	if(bItem[POWER_U])	//���� �Ŀ� �ٿ�
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
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX(),		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-6,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+6,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-5,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, -1, 11 );

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+5,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 1, 11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, -2, 10);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX(),		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5,0,12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+6,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 3, 11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-6,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, -3,11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-12,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, -6, 10);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+12,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX(),		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 0, 13);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+6,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 3, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-6,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, -3, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-12,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, -6, 11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+12,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, 6, 11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()-18,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, -9, 10);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[RED], g_MyShip.GetX()+18,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
					g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[BLUE], g_MyShip.GetX(),		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX(),		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-5,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, -1, 11);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+5,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX(),		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, 0, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-12,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 0, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+12,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+8,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 0, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-8,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, 0 ,12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5, -1, 13);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX(),		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-20, &g_Timer, 0, 10, 5,0,13);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-12,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-18, &g_Timer, 0, 10, 5,0 , 13);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+12,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-18, &g_Timer, 0, 10, 5,0, 13);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()-12,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
									g_MyShip.GetY()-15, &g_Timer, 0, 10, 5, -1, 12);

								g_MyMissile[MissileCheck()].Initialize( &g_MyMissileSprite[GREEN], g_MyShip.GetX()+12,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
		g_MyShip.Initialize(&g_MyShipSprite, g_MyShip.m_x, g_MyShip.InitMyShip_y, &g_Timer, 0, 25, 5);	// �÷��̾� �ʱ�ȭ 
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
		for(int m=0 ; m<MAX_ASSIST ; m++ )	// �ִ� �̻��� ��ŭ
		{
			if( !g_AssistMissile[m].IsLive())	// �������� ���ٸ� ���� Ż��
			{
				g_AssistMissile[m].init_x = g_MyShip.m_x;
				g_AssistMissile[m].type = g_MyShip.missiletype;
				return m;
			}
		}
	}
	else
	{
		for(int m=0 ; m<MAX_MISSILES ; m++ )	// �ִ� �̻��� ��ŭ
		{
			if( !g_MyMissile[m].IsLive())	// �������� ���ٸ� ���� Ż��
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
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY()-5, &g_Timer, 0, 10, 5);		
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY()-5, &g_Timer, 0, 10, 5);	
					}
					break;

				case 1:
					A_MAX_MISSILE[g_MyShip.missiletype-1] = 2;
					A_MISSILE_DELAY[g_MyShip.missiletype-1] = 700;
					A_MY_MISSILE_INTERVAL[g_MyShip.missiletype-1] =175;

					if(flag)
					{
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY()-5, &g_Timer, 0, 10, 5, 0, true);		
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY()-5, &g_Timer, 0, 10, 5, 0, true);	

						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-6,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY(), &g_Timer, 0, 10, 5);
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+6,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY(), &g_Timer, 0, 10, 5);
					}
					break;

				case 2:
					A_MAX_MISSILE[g_MyShip.missiletype-1] = 2;
					A_MISSILE_DELAY[g_MyShip.missiletype-1] = 600;
					A_MY_MISSILE_INTERVAL[g_MyShip.missiletype-1] = 150;

					if(flag)
					{
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY()+5, &g_Timer, 0, 10, 5);		
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY()+5, &g_Timer, 0, 10, 5);	

						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+1,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY(), &g_Timer, 0, 10, 5);		
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-1,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY(), &g_Timer, 0, 10, 5);

						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()-10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
							g_MyShip.GetY()+5, &g_Timer, 0, 10, 5, 0, true);		
						g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[0], g_MyShip.GetX()+10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
				
				g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[1], g_MyShip.GetX()-10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
					g_MyShip.GetY()-5, &g_Timer, 0, 10, 5);	
				g_AssistMissile[MissileCheck(true)].Initialize( &g_AssistMissileSprite[1], g_MyShip.GetX()+10,		// �̻��� �ʱ�ȭ ��ġ�� ����ش�.
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
	if(g_Enemy[i][j].after_x < g_Enemy[i][j].m_x) //���������� �̵�
	{
		if(g_Enemy[i][j].after_y < g_Enemy[i][j].m_y)	// ������ �Ʒ��� �̵�
		{
			if(g_Enemy[i][j].drawframe == 4)
				g_Enemy[i][j].drawframe = 5;
			else if(g_Enemy[i][j].drawframe == 7)
				g_Enemy[i][j].drawframe = 8;
			else
				g_Enemy[i][j].drawframe = 8;
		}
		else if(g_Enemy[i][j].after_y > g_Enemy[i][j].m_y)	// ������ ���� �̵�
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
	else if(g_Enemy[i][j].after_x > g_Enemy[i][j].m_x) //�������� �̵�
	{
		if(g_Enemy[i][j].after_y < g_Enemy[i][j].m_y) // ���� �Ʒ����̵�
		{
			if(g_Enemy[i][j].drawframe==10)
				g_Enemy[i][j].drawframe = 9;
			else if(g_Enemy[i][j].drawframe == 7)
				g_Enemy[i][j].drawframe = 8;
			else 
				g_Enemy[i][j].drawframe = 8;
		}
		else if(g_Enemy[i][j].after_y > g_Enemy[i][j].m_y)	// ���� ���� �̵�
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
		if(g_Enemy[i][j].after_y < g_Enemy[i][j].m_y)	// �Ʒ��� �̵�
		{
			g_Enemy[i][j].drawframe = 7;			
		}
		else if(g_Enemy[i][j].after_y > g_Enemy[i][j].m_y)	// ���� �̵�
		{
			g_Enemy[i][j].drawframe = 1;
		}
		else	// ����
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
