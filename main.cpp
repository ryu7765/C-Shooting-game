//main.cpp

// Shooting Game
//		800x600x32bpp RGB game

#define WIN32_LEAN_AND_MEAN	// 컴파일러에게 외부 mfc 오버헤더를 포함하지 말도록 지시한다

#include <windows.h>	// 윈도우즈 관련 헤더 파일
#include <windowsx.h>
#include <winsock2.h>	// 네트워크 관련 헤더

#include <ddraw.h>		// 다이렉트 드로우 관련 헤더 파일
#include <dinput.h>		// 다이렉트 인풋 관련 헤더파일

#include "bmp.h"		// bmp관련 헤더 파일
#include "timer.h"		// 시간 관련 헤더 파일
#include "enemy.h"		// 적 관련 헤더 파일
#include "sprite.h"		// 스프라이트 그리기 관련 헤더파일
#include "myship.h"		// 플레이어 관련 헤더 파일
#include "mymissile.h"	//  내 미사일 관련 헤더 파일
#include "exploding.h"		// 폭파 관련 헤더 파일
#include "enemymissile.h"	// 적 미사일 관련 헤더파일
#include "boss.h"		// 보스관련 헤더파일
#include "bossmissile.h"	// 보스 미사일 관련 헤더파일
#include "assistmissile.h"
#include "object.h"

#include "define.h"	// 디파인헤더 
// 함수 원형 선언 //
LRESULT CALLBACK WinProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);	// 윈도우 프록
DWORD WINAPI ClientMain(LPVOID arg);
bool InitializeDirectX(void);		// 다이렉트 x 초기화 
void GameMain(void);		// 게임 메인
void MainMenu(void); 
void InitGame();		// 게임 초기화
bool LoadBMPandInitSurface();	// 비트맵 불러오고 초기화 해주는 함수
bool InitObject();	// 오브젝트 초기화?..
void err_quit(char *msg);
void err_display(char *msg);
void Coordinate(int variable, char* buf);


// 전역 변수 정의 //
// 모든 전역 변수 앞에는 g_를 앞에 붙여서 사용하였다.
HWND			g_hwnd;		// 윈도우 핸들
HANDLE			hReadEvent, hWriteEvent;
HINSTANCE		g_hInstance;		// 인스턴스 핸들
char buf[BUFSIZE+1];

LPDIRECTDRAW7				g_lpDirectDrawObject = NULL;	// 다이렉트 드로우 객체 생성
LPDIRECTDRAWSURFACE7		g_lpPrimarySurface = NULL;		// 1차 표면	생성
LPDIRECTDRAWSURFACE7		g_lpSecondarySurface = NULL;	// 2차 표면 생성

LPDIRECTINPUT8				g_lpDirectInputObject = NULL;		// 입력받은 값
LPDIRECTINPUTDEVICE8		g_lpDirectInputKeyboard = NULL;		// 입력 받는 키보드값

SOCKET sock;



CSprite					g_TitleSprite;			//로딩화면 스프라이트
CSprite					g_BackgroundSprite;		// 적 스프라이트
CSprite					g_EnemySprite[10];	
CSprite					g_EnemyMissileSprite[10];	// 적 미사일 스프라이트
CSprite					g_MyShipSprite;		// 내 비행기 스프라이트
CSprite					g_MyMissileSprite[3];		// 내 미사일 스프라이트
CSprite					g_MyLifeSprite;
CSprite					g_ExplodingSprite[2];		// 폭파 스프라이트
CSprite					g_BossSprite;		// 보스 스프라이트 
CSprite					g_BossMissileSprite;	// 보스미사일 스프라이트
CSprite					g_WinSprite;		// 게임 성공시 스프라이트
CSprite					g_LoseSprite;		// 게임 실패시 스프라이트 
CSprite					g_DrawSprite;		// 게임 비겼을시 스프라이트 
CSprite					g_BoardSprite;
CSprite					g_SingleBoardSprite;
CSprite					g_State;
CSprite					g_AttackSprite;
CSprite					g_Score;
CSprite					g_InitMyShipSprite;
CSprite					g_MissileItemSprite;
CSprite					g_ItemSprite;
CSprite					g_MiniMapSprite;

CSprite					g_AssistMissileSprite[2];
CSprite					g_ShieldSprite;

CSprite					g_IslandSprite;


CSprite					g_GameMenuSprite;		
CSprite					g_SelectGameButton;	
CSprite					g_WaitC2Player;			 
CSprite					g_ConnectC2Player;		

CSprite					g_TutorialSprite;

CSprite					g_MissileExplodingSprite;
CSprite					g_AssistMissileExplodingSprite;


CTimer					g_Timer;		// 시간 클래스 객체 생성
bool					g_bActiveApp = false;	// 게임이 엑티브 한가?


CEnemy					g_Enemy[MAX_PATTERN][MAX_ENEMYS];		// 적 관련 객체 생성
CEnemyMissile			g_EnemyMissile[MAX_PATTERN][MAX_ENEMYS][MAX_ENEMY_MISSILES];	// 적 미사일 관련 객체 생성
CMyShip					g_MyShip;	// 내 비행기 관련 객체 생성
CMyShip					g_MyLife[MAX_LIFE];
CMyMissile				g_MyMissile[MAX_MISSILES];	// 내 미사일 관련 객체 생성
CBoss					g_Boss[MAX_BOSS];	// 보스관련 객체 생성
CBossMissile			g_BossMissile[MAX_BOSS_YMISSILES][MAX_BOSS_XMISSILES];	// 보스 미사일관련 객체 생성
CExploding				g_Exploding[MAX_EXPLODES];	// 폭파 관련 객체 생성
CExploding				g_Attack[2];
CAssistMissile			g_AssistMissile[MAX_ASSIST];
CItem					g_Item[8];
CObject					g_Object;

extern BOOL _InitDirectSound();	// 다이렉트 사운드 초기화 값을 받아온다.

bool serverconnect = false;
int g_GameMunu=GAMEMENU;
int SelectGameX=283;
int SelectTemp=0;
int AboutTemp = 0;


//늅 변수
int attack_item = 0;
int lazer_x;
int score=0;
bool	g_bMenu = false;
int GameStart;
int wow;

int MyShipFrame;
int isMyMissile;

extern CPlayer Player[2];

// 전역 변수 정의 끝 //

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//WindowClass 등록
	WNDCLASSEX wndclass;	// 윈도우 클래스 객체 생성
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;	// 스타일
	wndclass.lpfnWndProc = WinProc;	// 윈도우 프록
	wndclass.cbClsExtra = wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;	// 인스턴스 핸들러
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));  //아이콘 등록
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);	// 커서 등록
	wndclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);	// 배경 색 
	wndclass.lpszMenuName = NULL;	// 메뉴 
	wndclass.lpszClassName = CLASS_NAME;	// 클래스 이름
	wndclass.hIconSm = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	
	if( RegisterClassEx(&wndclass) == 0)
		return 0;
	// window를 creation  // 우선순위!! 화면전환이 불가능 해진다.
	g_hwnd = CreateWindowEx(WS_EX_TOPMOST, CLASS_NAME, CLASS_NAME, WS_POPUP | WS_VISIBLE,
					0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),	// 모니터의 x,y 크기를 구해온다.
					NULL, NULL, hInstance, NULL);

	if(g_hwnd == NULL) return 0;	// g_hwnd는 MessageBox() 호출 시 필요하다.
	g_hInstance = hInstance;		// DirectInput초기화때 필요하다

	SetFocus(g_hwnd);		// 현재의 포커스를 가져온다.
	ShowCursor(FALSE);		// false로 마우스 포인터를 숨긴다.

	// DirectDraw 초기화
	if( !InitializeDirectX())	//다이렉트 x를 초기화 
		return 0;		// 초기화 하지 못했을때 0을 리턴한다.

	if( !_InitDirectSound())	// 다이렉트 사운드를 초기화
		return 0;	// 최기화 하지 못했을때 0을 리턴

	g_Timer.start();	// 타이머 시작

	if( !LoadBMPandInitSurface())	// 비트맵 파일을 불러오고 초기화한다.
		return 0;

	if( !InitObject())	// 오브젝트 초기화..?  true를 반환
		return 0;


	//Message loop
	MSG msg;
	while (true)
	{
		if( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))	//메시지의 존재여부를 확인함
		{
			if( !GetMessage(&msg,NULL, 0, 0))	// 메시지를 얻어온다. 얻지못하면
				return (int)msg.wParam;	// 키보드 메시지값을 정수형으로 변환하여 보낸다.
			TranslateMessage(&msg);		// 키보드관련 메시지
			DispatchMessage(&msg);		// Window procdure 호출
		}
		else if(g_bActiveApp)	// 게임의 실행여부를 판단하여
		{
			if(GameStart==1)
				GameMain();	// 게임 메인을 호출
			if(GameStart==0)
				MainMenu();

			if(g_GameMunu == MULTYPLAY)
				SetEvent(hWriteEvent);
		}
		else 
			WaitMessage();	// 메시지가 들어올때까지 기다린다.
	}
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)		// 윈도우 프록
{
	switch( message )		
	{

	case WM_ACTIVATEAPP:		// 프로그램의 활성, 비활성 여부를 얻어온다.
		if(wParam)
			g_bActiveApp = true;	// 활동중이면 트루
		else
			g_bActiveApp = false;	// 아니면 펄스
		break;

	case WM_KEYUP:
		if(wParam=='X')
		{
			isMyMissile=0;
			wow=0;
		}
		break;

	case WM_KEYDOWN:		// 키가 눌렷을때
		if(wParam=='Y') 
		{
			Player[0].End=0;
			g_bActiveApp=true;
			InitGame();	// y라면 게임 초기화
		}
		if(wParam=='N') DestroyWindow(hwnd);	//n이라면 게임 종료
		if(wParam == VK_ESCAPE)
		{
			if(g_GameMunu == MULTYPLAY)
			{
				closesocket(sock);
				WSACleanup();
			}

			InitGame();
			GameStart = 0;
			g_GameMunu = GAMEMENU;
			SelectGameX=283;
			SelectTemp = 0;
			AboutTemp = 0;
			Player[0].End=0;

			serverconnect = false;
		}

		if(wParam == 'C')
			if(AboutTemp)
			{
				AboutTemp = 0;
				g_GameMunu = GAMEMENU;
				SelectGameX=283;
				SelectTemp = 0;
			}
			
		if(wParam == VK_RETURN)		//수정 
		{
			switch(SelectTemp)
			{
			case 0: g_GameMunu=SINGPLAY; break;
			case 1:
				if(!serverconnect)
				{
					DWORD ThreadId; 
					CreateThread(NULL,0,ClientMain,NULL,0,&ThreadId);
					serverconnect=true;
				}
				Player[0].GameState=1;
				g_GameMunu=MULTYPLAY;
				break;

			case 2: g_GameMunu=ABOUT;
				AboutTemp = 1;
				break;

			case 3: g_GameMunu=CREATOR;
				break;

			case 4: g_GameMunu=EXIT; 
				DestroyWindow(hwnd);
				break;
			}

			if(Player[0].End == 1)
			{
				if(g_GameMunu == MULTYPLAY)
				{
					closesocket(sock);
					WSACleanup();
				}
				
				InitGame();
				GameStart = 0;
				g_GameMunu = GAMEMENU;
				SelectGameX=283;
				SelectTemp = 0;
				AboutTemp = 0;
				Player[0].End=0;
				
				serverconnect = false;
			}
			

			if(g_GameMunu==MULTYPLAY)
			{
				if(Player[1].GameState==1)
				{
					Player[0].GameStart=1;
					Player[0].End=0;
					Player[0].score=0;
				}

			}
			
		}
		break;
			
	case WM_DESTROY:		// 프로그램 종료시
		if(g_lpDirectDrawObject)
		{
			if(g_lpSecondarySurface)		// 2차버퍼 소멸
				g_lpSecondarySurface->Release();
			if(g_lpPrimarySurface)				// 1차 버퍼 소멸
				g_lpPrimarySurface->Release();
			g_WinSprite.ReleaseAll();		// 게임 성공시 스프라이트
			g_LoseSprite.ReleaseAll();		// 게임 실패시 스프라이트 
			g_DrawSprite.ReleaseAll();		// 게임 비겼을시 스프라이트 
			g_BossMissileSprite.ReleaseAll();	// 보스 미사일 스프라이트 내의 모든 Surface를 메모리 해제 
			g_BossSprite.ReleaseAll();	// 보스 스프라이트 내의 모든 Surface를 메모리 해제 
			g_EnemyMissileSprite[0].ReleaseAll();	// 적미사일 스프라이트 내의 모든 Surface를 메모리 해제 
			g_EnemySprite[0].ReleaseAll();	// 적 스프라이트 내의 모든 Surface를 메모리 해제 
			g_BackgroundSprite.ReleaseAll();	// 배경 스프라이트 내의 모든 Surface를 메모리 해제 
			g_TitleSprite.ReleaseAll();		// 타이틀(로딩화면) 스프라이트 내의 모든 Surface를 메모리 해제 
			
			g_lpDirectDrawObject->Release();	// 
		}
		if( g_lpDirectInputObject)
		{
			if(g_lpDirectInputKeyboard)
			{
				g_lpDirectInputKeyboard -> Unacquire();  // 접근 권한을 준다..??
				g_lpDirectInputKeyboard -> Release();	// 키보드값 소멸
			}
			g_lpDirectInputObject->Release();	// 입력값 소멸
		}
		
		ShowCursor(TRUE);	//커서를 보이게 설정
		PostQuitMessage(0);	// 종료
		break;
		
	default:
		return DefWindowProc(hwnd, message, wParam, lParam); 
				// 만약에 위에서 처리를 하지 못했다면 기본값 설정
	}
	return 0;
}

DWORD WINAPI ClientMain(LPVOID arg)
{
	int retval;
	char *RecvData[100];
	char buf[BUFSIZE+1];
	char sendbuf[BUFSIZE+1];
	
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2),&wsa) !=0)
		return -1;
	
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==INVALID_SOCKET) err_quit("socket()");
	
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(9000);
	serveraddr.sin_addr.s_addr=inet_addr("200.1.2.77");
	retval=connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval==SOCKET_ERROR) err_quit("connect()");
	
	while(1) {
		WaitForSingleObject(hWriteEvent,INFINITE);

		*sendbuf = '1';

		itoa(Player[0].GameState, sendbuf, 10);
		itoa(Player[0].GameStart, sendbuf+1, 10);
		itoa(attack_item, sendbuf+2, 10);

		Coordinate(g_MyShip.GetX(), sendbuf+3);
		Coordinate(g_MyShip.GetY(), sendbuf+6);

		itoa(MyShipFrame, sendbuf+9, 10);
		itoa(isMyMissile, sendbuf+10, 10);
		itoa(g_MyShip.type, sendbuf+11, 10);
		itoa(g_MyShip.level, sendbuf+12, 10);
		itoa(Player[0].score, sendbuf+13, 10);
		itoa(Player[0].End, sendbuf+18, 10);
				

		retval=send(sock,sendbuf,strlen(sendbuf),0);
		if(strlen(sendbuf)==0){
			SetEvent(hReadEvent);
			continue;
		}

		
		
		retval=recv(sock,buf,512,0);
		if(retval==SOCKET_ERROR){
			err_display("recv()");
			break;
		}
		else if(retval==0)
		{
			break;
		}

		Player[1].GameState = ((int)(buf[0]))-48;
		GameStart			= ((int)(buf[1]))-48;
		g_MyShip.item		= ((int)(buf[2]))-48;
		lazer_x				= (((int)(buf[3]))-48)*100 + (((int)(buf[4]))-48)*10 + (((int)(buf[5]))-48);
		Player[0].MiniMapX	= (((int)(buf[3]))-48)*100 + (((int)(buf[4]))-48)*10 + (((int)(buf[5]))-48);
		Player[0].MiniMapY	= (((int)(buf[6]))-48)*100 + (((int)(buf[7]))-48)*10 + (((int)(buf[8]))-48);
		Player[1].score		= (((int)(buf[13]))-48)*10000 + (((int)(buf[14]))-48)*1000 + (((int)(buf[15]))-48)*100 + (((int)(buf[16]))-48)*10 + (((int)(buf[17]))-48);
		Player[1].End		= (((int)(buf[18]))-48);


		
/*
		buf[13] = '\n';

		RecvData[0] = strtok(buf,",");
		RecvData[1] = strtok(NULL,",");
		RecvData[2] = strtok(NULL,",");
		RecvData[3] = strtok(NULL,",");
		RecvData[4] = strtok(NULL,",");
		Player[1].GameState  = atoi(RecvData[0]);
		GameStart	  = atoi(RecvData[1]);
		g_MyShip.item = atoi(RecvData[2]);
		lazer_x		  = atoi(RecvData[3]);
		Player[0].MiniMapX = atoi(RecvData[3]);
		Player[0].MiniMapY = atoi(RecvData[4]);
*/
		SetEvent(hReadEvent);
	}
}




void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);

	LocalFree(lpMsgBuf);
	exit(-1);
}

void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	LocalFree(lpMsgBuf);
}

void Coordinate(int variable, char* buf)
{
	if(variable<100)
	{
		itoa(0, buf, 10);
		itoa(variable, buf+1, 10);
	}
	else if(variable<10)
	{
		itoa(0, buf, 10);
		itoa(0, buf+1, 10);
		itoa(variable, buf+2, 10);
	}
	else
	{
		itoa(variable, buf, 10);
	}
}
		

bool LoadBMPandInitSurface() // 비트맵 불러오는 함수
{
	//타이틀 화면 출력
	if(!g_TitleSprite.InitSprite( 1, 800, 600, COLOR_KEY, g_lpDirectDrawObject))	//타이틀 화면 초기화
		return false;
	if(!g_TitleSprite.LoadFrame(0, "data\\loding.bmp"))	// 타이틀화면 설정 성공시 그냥 넘어가고 실패시 리턴 펄스
		return false;
	g_TitleSprite.Drawing(0, 400, 300, g_lpSecondarySurface, false);	// 타이틀 화면을 그린다.

	if(!g_State.InitSprite(1, 150, 600, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if(!g_State.LoadFrame(0, "data\\Interface.bmp"))
		return false;

	//Flipping
	HRESULT hResult;
	if( FAILED(hResult = g_lpPrimarySurface->Flip(NULL, DDFLIP_WAIT)))	// 플리핑 처리
	{
		if( hResult == DDERR_SURFACELOST )	// 플리핑을 참조해서 Restore()에 연결해준다.
			g_lpPrimarySurface->Restore();
	}

	//백그라운드 스프라이트
	if(!g_BackgroundSprite.InitSprite( 1, 800, 1200, COLOR_KEY, g_lpDirectDrawObject))	// 1개의 프레임의 800*1200 크기의 배경스프라이트를 초기화
		return false;
	if(!g_BackgroundSprite.LoadFrame(0, "data\\background.bmp"))	// 0번째 프레임에 해당 파일경로에서 불러온다.
		return false;

	//적 스프라이트					// 적의 스프라이트의 크기 만큼 초기화 한후
	if(!g_EnemySprite[0].InitSprite(12, 45, 45, WHITE_COLOR_KEY, g_lpDirectDrawObject))
		return false;				// 각 프레임에 각 파일을 불러온다. 불러오기 실패하면 리턴 펄스
	if(!g_EnemySprite[0].LoadFrame(0, "data\\Enemy0\\Enemy0_0.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(1, "data\\Enemy0\\Enemy0_1.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(2, "data\\Enemy0\\Enemy0_2.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(3, "data\\Enemy0\\Enemy0_3.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(4, "data\\Enemy0\\Enemy0_4.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(5, "data\\Enemy0\\Enemy0_5.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(6, "data\\Enemy0\\Enemy0_6.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(7, "data\\Enemy0\\Enemy0_7.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(8, "data\\Enemy0\\Enemy0_8.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(9, "data\\Enemy0\\Enemy0_9.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(10, "data\\Enemy0\\Enemy0_10.bmp"))
		return false;
	if(!g_EnemySprite[0].LoadFrame(11, "data\\Enemy0\\Enemy0_11.bmp"))
		return false;

	if(!g_EnemySprite[1].InitSprite(12, 50, 50, WHITE_COLOR_KEY, g_lpDirectDrawObject))
		return false;				// 각 프레임에 각 파일을 불러온다. 불러오기 실패하면 리턴 펄스
	if(!g_EnemySprite[1].LoadFrame(0, "data\\Enemy1\\Enemy1_0.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(1, "data\\Enemy1\\Enemy1_1.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(2, "data\\Enemy1\\Enemy1_2.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(3, "data\\Enemy1\\Enemy1_3.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(4, "data\\Enemy1\\Enemy1_4.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(5, "data\\Enemy1\\Enemy1_5.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(6, "data\\Enemy1\\Enemy1_6.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(7, "data\\Enemy1\\Enemy1_7.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(8, "data\\Enemy1\\Enemy1_8.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(9, "data\\Enemy1\\Enemy1_9.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(10, "data\\Enemy1\\Enemy1_10.bmp"))
		return false;
	if(!g_EnemySprite[1].LoadFrame(11, "data\\Enemy1\\Enemy1_11.bmp"))
		return false;

	if(!g_EnemySprite[2].InitSprite(12, 60, 35, COLOR_KEY, g_lpDirectDrawObject))
		return false;				// 각 프레임에 각 파일을 불러온다. 불러오기 실패하면 리턴 펄스
	if(!g_EnemySprite[2].LoadFrame(0, "data\\Enemy2\\Enemy2_0.bmp"))
		return false;
	if(!g_EnemySprite[2].LoadFrame(1, "data\\Enemy2\\Enemy2_1.bmp"))
		return false;
	if(!g_EnemySprite[2].LoadFrame(2, "data\\Enemy2\\Enemy2_2.bmp"))
		return false;
	if(!g_EnemySprite[2].LoadFrame(6, "data\\Enemy2\\Enemy2_6.bmp"))
		return false;
	if(!g_EnemySprite[2].LoadFrame(7, "data\\Enemy2\\Enemy2_7.bmp"))
		return false;
	if(!g_EnemySprite[2].LoadFrame(8, "data\\Enemy2\\Enemy2_8.bmp"))
		return false;


	if(!g_EnemySprite[3].InitSprite(1, 62, 34, COLOR_KEY, g_lpDirectDrawObject))
		return false;				// 각 프레임에 각 파일을 불러온다. 불러오기 실패하면 리턴 펄스
	if(!g_EnemySprite[3].LoadFrame(0, "data\\Enemy4.bmp"))
		return false;

	if(!g_EnemySprite[4].InitSprite(1, 109, 61, COLOR_KEY, g_lpDirectDrawObject))
		return false;				// 각 프레임에 각 파일을 불러온다. 불러오기 실패하면 리턴 펄스
	if(!g_EnemySprite[4].LoadFrame(0, "data\\Enemy5.bmp"))
		return false;

	if(!g_EnemySprite[5].InitSprite(1, 167, 121, COLOR_KEY, g_lpDirectDrawObject))
		return false;				// 각 프레임에 각 파일을 불러온다. 불러오기 실패하면 리턴 펄스
	if(!g_EnemySprite[5].LoadFrame(0, "data\\Enemy6.bmp"))
		return false;

	if(!g_EnemySprite[6].InitSprite(12, 50, 50, COLOR_KEY, g_lpDirectDrawObject))
		return false;				// 각 프레임에 각 파일을 불러온다. 불러오기 실패하면 리턴 펄스
	if(!g_EnemySprite[6].LoadFrame(0, "data\\Enemy7\\Eship7.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(1, "data\\Enemy7\\Eship0.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(2, "data\\Enemy7\\Eship1.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(3, "data\\Enemy7\\Eship1.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(4, "data\\Enemy7\\Eship2.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(5, "data\\Enemy7\\Eship3.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(6, "data\\Enemy7\\Eship3.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(7, "data\\Enemy7\\Eship4.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(8, "data\\Enemy7\\Eship5.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(9, "data\\Enemy7\\Eship5.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(10, "data\\Enemy7\\Eship6.bmp"))
		return false;
	if(!g_EnemySprite[6].LoadFrame(11, "data\\Enemy7\\Eship7.bmp"))
		return false;


	if(!g_EnemySprite[7].InitSprite(1, 46, 50, WHITE_COLOR_KEY, g_lpDirectDrawObject))
		return false;				// 각 프레임에 각 파일을 불러온다. 불러오기 실패하면 리턴 펄스
	if(!g_EnemySprite[7].LoadFrame(0, "data\\Enemy8.bmp"))
		return false;

	if(!g_EnemySprite[8].InitSprite(1, 179, 165, COLOR_KEY, g_lpDirectDrawObject))
		return false;				// 각 프레임에 각 파일을 불러온다. 불러오기 실패하면 리턴 펄스
	if(!g_EnemySprite[8].LoadFrame(0, "data\\Enemy9.bmp"))
		return false;

	if(!g_EnemySprite[9].InitSprite(1, 40, 40, COLOR_KEY, g_lpDirectDrawObject))
		return false;				// 각 프레임에 각 파일을 불러온다. 불러오기 실패하면 리턴 펄스
	if(!g_EnemySprite[9].LoadFrame(0, "data\\boss2\\shooting.bmp"))
		return false;



	

	//내 비행선 스프라이트			//내 비행기의 스프라이트 초기화
	if(!g_MyShipSprite.InitSprite(3, 56, 50, GREEN_COLOR_KEY, g_lpDirectDrawObject))
		return false;
	// 그냥 갈때 왼쪽, 오른쪽 이미지를  해당 프레임에 불러온다.
	if(!g_MyShipSprite.LoadFrame(0, "data\\MyShip\\MyShip_center.bmp"))
		return false;
	if(!g_MyShipSprite.LoadFrame(1, "data\\MyShip\\MyShip_left.bmp"))
		return false;
	if(!g_MyShipSprite.LoadFrame(2, "data\\MyShip\\MyShip_right.bmp"))
		return false;


	
	if(!g_InitMyShipSprite.InitSprite(4, 56, 50, GREEN_COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if(!g_InitMyShipSprite.LoadFrame(0, "data\\MyShip\\MyShip_center.bmp"))
		return false;
	if(!g_InitMyShipSprite.LoadFrame(1, "data\\MyShip\\MyShip_center.bmp"))
		return false;
	if(!g_InitMyShipSprite.LoadFrame(2, "data\\MyShip\\MyShip_h_center.bmp"))
		return false;	
	if(!g_InitMyShipSprite.LoadFrame(3, "data\\MyShip\\MyShip_h_center.bmp"))
		return false;

	// 내 목숨
	if(!g_MyLifeSprite.InitSprite(1, 23, 20, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if(!g_MyLifeSprite.LoadFrame(0, "data\\Life_icon.bmp"))
		return false;

	// score
	if(!g_Score.InitSprite(10, 15, 18, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if(!g_Score.LoadFrame(0, "data\\number0.bmp"))
		return false;
	if(!g_Score.LoadFrame(1, "data\\number1.bmp"))
		return false;
	if(!g_Score.LoadFrame(2, "data\\number2.bmp"))
		return false;
	if(!g_Score.LoadFrame(3, "data\\number3.bmp"))
		return false;
	if(!g_Score.LoadFrame(4, "data\\number4.bmp"))
		return false;
	if(!g_Score.LoadFrame(5, "data\\number5.bmp"))
		return false;
	if(!g_Score.LoadFrame(6, "data\\number6.bmp"))
		return false;
	if(!g_Score.LoadFrame(7, "data\\number7.bmp"))
		return false;
	if(!g_Score.LoadFrame(8, "data\\number8.bmp"))
		return false;
	if(!g_Score.LoadFrame(9, "data\\number9.bmp"))
		return false;

	/*
	// 레이저
	if(!g_AttackSprite.InitSprite(8, 80, 975, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if(!g_AttackSprite.LoadFrame(0, "data\\Lazer\\Lazer000.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(1, "data\\Lazer\\Lazer001.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(2, "data\\Lazer\\Lazer002.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(3, "data\\Lazer\\Lazer003.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(4, "data\\Lazer\\Lazer000.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(5, "data\\Lazer\\Lazer001.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(6, "data\\Lazer\\Lazer002.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(7, "data\\Lazer\\Lazer003.bmp"))
		return false;
		*/

	// 레이저
	if(!g_AttackSprite.InitSprite(27, 37, 600, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if(!g_AttackSprite.LoadFrame(0, "data\\Lazer\\Lazer11.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(1, "data\\Lazer\\Lazer12.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(2, "data\\Lazer\\Lazer13.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(3, "data\\Lazer\\Lazer14.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(4, "data\\Lazer\\Lazer16.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(5, "data\\Lazer\\Lazer17.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(6, "data\\Lazer\\Lazer18.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(7, "data\\Lazer\\Lazer19.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(8, "data\\Lazer\\Lazer20.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(9, "data\\Lazer\\Lazer11.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(10, "data\\Lazer\\Lazer12.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(11, "data\\Lazer\\Lazer13.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(12, "data\\Lazer\\Lazer14.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(13, "data\\Lazer\\Lazer16.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(14, "data\\Lazer\\Lazer17.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(15, "data\\Lazer\\Lazer18.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(16, "data\\Lazer\\Lazer19.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(17, "data\\Lazer\\Lazer20.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(18, "data\\Lazer\\Lazer11.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(19, "data\\Lazer\\Lazer12.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(20, "data\\Lazer\\Lazer13.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(21, "data\\Lazer\\Lazer14.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(22, "data\\Lazer\\Lazer16.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(23, "data\\Lazer\\Lazer17.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(24, "data\\Lazer\\Lazer18.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(25, "data\\Lazer\\Lazer19.bmp"))
		return false;
	if(!g_AttackSprite.LoadFrame(26, "data\\Lazer\\Lazer20.bmp"))
		return false;


	//내 미사일 스프라이트		// 내 미사일을 초기화
	if( !g_MyMissileSprite[0].InitSprite(1, 9, 24, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_MyMissileSprite[0].LoadFrame(0, "data\\Missile\\missile_red.bmp"))
		return false;

	if( !g_MyMissileSprite[1].InitSprite(4, 5, 30, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_MyMissileSprite[1].LoadFrame(0, "data\\Missile\\missile_green0.bmp"))
		return false;
	if( !g_MyMissileSprite[1].LoadFrame(1, "data\\Missile\\missile_green1.bmp"))
		return false;
	if( !g_MyMissileSprite[1].LoadFrame(2, "data\\Missile\\missile_green2.bmp"))
		return false;
	if( !g_MyMissileSprite[1].LoadFrame(3, "data\\Missile\\missile_green3.bmp"))
		return false;
	
	if( !g_MyMissileSprite[2].InitSprite(1, 6, 25, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_MyMissileSprite[2].LoadFrame(0, "data\\Missile\\missile_blue.bmp"))
		return false;

	//폭파장면 스프라이트		// 폭파장면 스프라이트 초기화
	if(!g_ExplodingSprite[0].InitSprite(18, 128, 128, SHIP_COLOR_KEY, g_lpDirectDrawObject))
		return false;
								// 폭파장면의 이미지들을 각각의 프레임에 불러온다.
	if(!g_ExplodingSprite[0].LoadFrame(0, "data\\exploding\\exp00.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(1, "data\\exploding\\exp01.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(2, "data\\exploding\\exp02.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(3, "data\\exploding\\exp03.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(4, "data\\exploding\\exp04.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(5, "data\\exploding\\exp05.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(6, "data\\exploding\\exp06.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(7, "data\\exploding\\exp07.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(8, "data\\exploding\\exp08.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(9, "data\\exploding\\exp09.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(10, "data\\exploding\\exp10.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(11, "data\\exploding\\exp11.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(12, "data\\exploding\\exp12.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(13, "data\\exploding\\exp13.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(14, "data\\exploding\\exp14.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(15, "data\\exploding\\exp15.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(16, "data\\exploding\\exp16.bmp"))
		return false;
	if(!g_ExplodingSprite[0].LoadFrame(17, "data\\exploding\\exp17.bmp"))
		return false;

	if(!g_ExplodingSprite[1].InitSprite(16, 64, 64, SHIP_COLOR_KEY, g_lpDirectDrawObject))
		return false;
								// 폭파장면의 이미지들을 각각의 프레임에 불러온다.
	if(!g_ExplodingSprite[1].LoadFrame(0, "data\\exploding\\expl00.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(1, "data\\exploding\\expl01.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(2, "data\\exploding\\expl02.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(3, "data\\exploding\\expl03.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(4, "data\\exploding\\expl04.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(5, "data\\exploding\\expl05.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(6, "data\\exploding\\expl06.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(7, "data\\exploding\\expl07.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(8, "data\\exploding\\expl08.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(9, "data\\exploding\\expl09.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(10, "data\\exploding\\expl10.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(11, "data\\exploding\\expl11.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(12, "data\\exploding\\expl12.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(13, "data\\exploding\\expl13.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(14, "data\\exploding\\expl14.bmp"))
		return false;
	if(!g_ExplodingSprite[1].LoadFrame(15, "data\\exploding\\expl15.bmp"))
		return false;


	if(!g_MissileExplodingSprite.InitSprite(12, 16, 16, SHIP_COLOR_KEY, g_lpDirectDrawObject))
		return false;								// 폭파장면의 이미지들을 각각의 프레임에 불러온다.
	if(!g_MissileExplodingSprite.LoadFrame(0, "data\\missile_exploding\\smallEx00.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(1, "data\\missile_exploding\\smallEx01.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(2, "data\\missile_exploding\\smallEx02.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(3, "data\\missile_exploding\\smallEx03.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(4, "data\\missile_exploding\\smallEx04.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(5, "data\\missile_exploding\\smallEx05.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(6, "data\\missile_exploding\\smallEx06.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(7, "data\\missile_exploding\\smallEx07.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(8, "data\\missile_exploding\\smallEx08.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(9, "data\\missile_exploding\\smallEx09.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(10, "data\\missile_exploding\\smallEx10.bmp"))
		return false;
	if(!g_MissileExplodingSprite.LoadFrame(11, "data\\missile_exploding\\smallEx11.bmp"))
		return false;

	if(!g_AssistMissileExplodingSprite.InitSprite(12, 48, 48, SHIP_COLOR_KEY, g_lpDirectDrawObject))
		return false;								// 폭파장면의 이미지들을 각각의 프레임에 불러온다.
	if(!g_AssistMissileExplodingSprite.LoadFrame(0, "data\\assist_missile_exploding\\ex0.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(1, "data\\assist_missile_exploding\\ex1.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(2, "data\\assist_missile_exploding\\ex2.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(3, "data\\assist_missile_exploding\\ex3.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(4, "data\\assist_missile_exploding\\ex4.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(5, "data\\assist_missile_exploding\\ex5.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(6, "data\\assist_missile_exploding\\ex6.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(7, "data\\assist_missile_exploding\\ex7.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(8, "data\\assist_missile_exploding\\ex8.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(9, "data\\assist_missile_exploding\\ex9.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(10, "data\\assist_missile_exploding\\ex10.bmp"))
		return false;
	if(!g_AssistMissileExplodingSprite.LoadFrame(11, "data\\assist_missile_exploding\\ex11.bmp"))
		return false;

	


	

	//Enemy 미사일 스프라이트		// 적 미사일의 스프라이트를 초기화하고 프레임에 이미지를 불러온다.
	if( !g_EnemyMissileSprite[0].InitSprite(1, 11, 11, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_EnemyMissileSprite[0].LoadFrame(0, "data\\small_attack.bmp"))
		return false;

	if( !g_EnemyMissileSprite[1].InitSprite(1, 26, 26, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_EnemyMissileSprite[1].LoadFrame(0, "data\\centerBoss_Missile.bmp"))
		return false;

	if( !g_EnemyMissileSprite[2].InitSprite(1, 12, 12, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_EnemyMissileSprite[2].LoadFrame(0, "data\\Enemy_Missile_yellow.bmp"))
		return false;

	if( !g_EnemyMissileSprite[3].InitSprite(1, 12, 12, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_EnemyMissileSprite[3].LoadFrame(0, "data\\Enemy_Missile_red.bmp"))
		return false;

	if( !g_EnemyMissileSprite[4].InitSprite(1, 12, 12, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_EnemyMissileSprite[4].LoadFrame(0, "data\\Enemy_Missile_green.bmp"))
		return false;

	if( !g_EnemyMissileSprite[5].InitSprite(12, 36, 36, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(0, "data\\boss2\\2B_blue3.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(1, "data\\boss2\\2B_blue4.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(2, "data\\boss2\\2B_blue5.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(3, "data\\boss2\\2B_blue6.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(4, "data\\boss2\\2B_blue7.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(5, "data\\boss2\\2B_blue8.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(6, "data\\boss2\\2B_blue9.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(7, "data\\boss2\\2B_blue10.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(8, "data\\boss2\\2B_blue11.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(9, "data\\boss2\\2B_blue12.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(10, "data\\boss2\\2B_blue1.bmp"))
		return false;
	if( !g_EnemyMissileSprite[5].LoadFrame(11, "data\\boss2\\2B_blue2.bmp"))
		return false;

	//boss sprite		// 보스의 스프라이트를 초기화하고 프레임에 이미지를 불러온다.
	if( !g_BossSprite.InitSprite(1,300,225, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_BossSprite.LoadFrame(0, "data\\Boss_0000.bmp"))
		return false;

	//boss Missile sprite		// 보스 미사일의 스프라이트를 초기화하고 프레임에 이미지를 불러온다.
	if( !g_BossMissileSprite.InitSprite(1,30,30, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_BossMissileSprite.LoadFrame(0, "data\\Boss_Missile.bmp"))
		return false;

	if( !g_WinSprite.InitSprite(1, 390, 52, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_WinSprite.LoadFrame(0, "data\\winner.bmp"))
		return false;
	if( !g_LoseSprite.InitSprite(1, 390, 52, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_LoseSprite.LoadFrame(0, "data\\loser.bmp"))
		return false;
	if( !g_DrawSprite.InitSprite(1, 390, 52, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_DrawSprite.LoadFrame(0, "data\\draw.bmp"))
		return false;
	if( !g_BoardSprite.InitSprite(1, 396, 272, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_BoardSprite.LoadFrame(0, "data\\score board.bmp"))
		return false;
	if( !g_SingleBoardSprite.InitSprite(1, 395, 170, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_SingleBoardSprite.LoadFrame(0, "data\\singleScore.bmp"))
		return false;

	if(!g_GameMenuSprite.InitSprite( 1, 800, 600, COLOR_KEY, g_lpDirectDrawObject))	
		return false;
	if(!g_GameMenuSprite.LoadFrame(0, "data\\Menu\\title.bmp"))	
		return false;

	if(!g_SelectGameButton.InitSprite( 5, 540, 60, COLOR_KEY, g_lpDirectDrawObject))	
		return false;
	if(!g_SelectGameButton.LoadFrame(0, "data\\Menu\\singlemode.bmp"))	
		return false;
	if(!g_SelectGameButton.LoadFrame(1, "data\\Menu\\networkmode.bmp"))	
		return false;
	if(!g_SelectGameButton.LoadFrame(2, "data\\Menu\\tutorial.bmp"))	
		return false;
	if(!g_SelectGameButton.LoadFrame(3, "data\\Menu\\creator.bmp"))	
		return false;
	if(!g_SelectGameButton.LoadFrame(4, "data\\Menu\\exit.bmp"))	
		return false;

	if(!g_WaitC2Player.InitSprite( 1, 396, 272, COLOR_KEY, g_lpDirectDrawObject))	
		return false;
	if(!g_WaitC2Player.LoadFrame(0, "data\\wait.bmp"))	
		return false;

	if(!g_ConnectC2Player.InitSprite( 1, 396, 272, COLOR_KEY, g_lpDirectDrawObject))	
		return false;
	if(!g_ConnectC2Player.LoadFrame(0, "data\\connect.bmp"))	
		return false;



	if( !g_MissileItemSprite.InitSprite(3, 40, 40, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_MissileItemSprite.LoadFrame(0, "data\\item\\red.bmp"))
		return false;
	if( !g_MissileItemSprite.LoadFrame(1, "data\\item\\green.bmp"))
		return false;
	if( !g_MissileItemSprite.LoadFrame(2, "data\\item\\blue.bmp"))
		return false;

	if( !g_ItemSprite.InitSprite(11, 42, 42, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_ItemSprite.LoadFrame(0, "data\\item\\item00.bmp"))
		return false;
	if( !g_ItemSprite.LoadFrame(1, "data\\item\\item01.bmp"))
		return false;
	if( !g_ItemSprite.LoadFrame(2, "data\\item\\item02.bmp"))
		return false;
	if( !g_ItemSprite.LoadFrame(3, "data\\item\\item03.bmp"))
		return false;
	if( !g_ItemSprite.LoadFrame(4, "data\\item\\item04.bmp"))
		return false;
	if( !g_ItemSprite.LoadFrame(5, "data\\item\\item05.bmp"))
		return false;
	if( !g_ItemSprite.LoadFrame(6, "data\\item\\item06.bmp"))
		return false;
	if( !g_ItemSprite.LoadFrame(7, "data\\item\\item07.bmp"))
		return false;
	if( !g_ItemSprite.LoadFrame(8, "data\\item\\item08.bmp"))
		return false;
	if( !g_ItemSprite.LoadFrame(9, "data\\item\\item09.bmp"))
		return false;
	if( !g_ItemSprite.LoadFrame(10, "data\\item\\item10.bmp"))
		return false;


	if( !g_AssistMissileSprite[0].InitSprite(4, 8, 40, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_AssistMissileSprite[0].LoadFrame(0, "data\\Missile\\straightMissile00.bmp"))
		return false;
	if( !g_AssistMissileSprite[0].LoadFrame(1, "data\\Missile\\straightMissile01.bmp"))
		return false;
	if( !g_AssistMissileSprite[0].LoadFrame(2, "data\\Missile\\straightMissile02.bmp"))
		return false;
	if( !g_AssistMissileSprite[0].LoadFrame(3, "data\\Missile\\straightMissile03.bmp"))
		return false;

	if( !g_AssistMissileSprite[1].InitSprite(1, 9, 24, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_AssistMissileSprite[1].LoadFrame(0, "data\\Missile\\inductionMissile.bmp"))
		return false;

	if( !g_ShieldSprite.InitSprite(1, 64, 64, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_ShieldSprite.LoadFrame(0, "data\\shield.bmp"))
		return false;

	if( !g_MiniMapSprite.InitSprite(1, 10, 10, WHITE_COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_MiniMapSprite.LoadFrame(0, "data\\pixel.bmp"))
		return false;

	if( !g_TutorialSprite.InitSprite(4, 800, 600, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_TutorialSprite.LoadFrame(0, "data\\Menu\\tutorial1.bmp"))
		return false;
	if( !g_TutorialSprite.LoadFrame(1, "data\\Menu\\tutorial2.bmp"))
		return false;
	if( !g_TutorialSprite.LoadFrame(2, "data\\Menu\\tutorial3.bmp"))
		return false;
	if( !g_TutorialSprite.LoadFrame(3, "data\\Menu\\tutorial4.bmp"))
		return false;

	if( !g_IslandSprite.InitSprite(1, 230, 180, COLOR_KEY, g_lpDirectDrawObject))
		return false;
	if( !g_IslandSprite.LoadFrame(0, "data\\ob.bmp"))
		return false;

	return true;
}

bool InitObject()	// 호출시 true를 반환
{
	return true;
}

	
