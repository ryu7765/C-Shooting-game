//timer.cpp

#include <windows.h>

#include "timer.h"

CTimer::CTimer()	// 생성자 시간 초기값을 0으로 초기화
{
	m_nStartTime = 0;
}

CTimer::~CTimer()	// 소멸자
{
}

void CTimer::start()
{
	m_nStartTime = timeGetTime();	//timeGetTime()은 Win32 API 함수
							// 결과 값은 부팅 후 경과 시간(ms)
}

int CTimer::time()		// 게임 실행시간
{
	return (timeGetTime() - m_nStartTime);	// 부팅후 현재 시간에서 start함수가 불러졋을때를 빼서 그사이 실행시간을 구해준다.
}

bool CTimer::elapsed(int &stime, int interval)
{
	int current_time = time();	// 게임 실행시간
	if(current_time >= stime + interval)	//게임 실행시간이 받아온 시간과 간격을 더한것보다 크다면
	{
		stime = current_time;	// 받아온 시간을 실행시간으로 바꿔주고
		return true;	// 투르를 반환
	}
	else	//아니면
		return false;// 펄스를 반환
}
