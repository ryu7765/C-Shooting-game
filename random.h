//random.h
//������ �߻�
#ifndef __random_h__
#define __random_h__

class CRandom
{
private:
	int			m_nCount;	// ��� Random number�� �߻��ߴ°��� ����
	void sowseed();		//seed�� �ش�.

public:
	CRandom();
	~CRandom();
	int number(int m, int n);	//m�� n ������ ������ �߻��ϴ� �Լ�.
};

#endif