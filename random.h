//random.h
//난수를 발생
#ifndef __random_h__
#define __random_h__

class CRandom
{
private:
	int			m_nCount;	// 몇번 Random number를 발생했는가를 저장
	void sowseed();		//seed를 준다.

public:
	CRandom();
	~CRandom();
	int number(int m, int n);	//m과 n 사이의 난수를 발생하는 함수.
};

#endif