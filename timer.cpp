//timer.cpp

#include <windows.h>

#include "timer.h"

CTimer::CTimer()	// ������ �ð� �ʱⰪ�� 0���� �ʱ�ȭ
{
	m_nStartTime = 0;
}

CTimer::~CTimer()	// �Ҹ���
{
}

void CTimer::start()
{
	m_nStartTime = timeGetTime();	//timeGetTime()�� Win32 API �Լ�
							// ��� ���� ���� �� ��� �ð�(ms)
}

int CTimer::time()		// ���� ����ð�
{
	return (timeGetTime() - m_nStartTime);	// ������ ���� �ð����� start�Լ��� �ҷ��������� ���� �׻��� ����ð��� �����ش�.
}

bool CTimer::elapsed(int &stime, int interval)
{
	int current_time = time();	// ���� ����ð�
	if(current_time >= stime + interval)	//���� ����ð��� �޾ƿ� �ð��� ������ ���Ѱͺ��� ũ�ٸ�
	{
		stime = current_time;	// �޾ƿ� �ð��� ����ð����� �ٲ��ְ�
		return true;	// ������ ��ȯ
	}
	else	//�ƴϸ�
		return false;// �޽��� ��ȯ
}
