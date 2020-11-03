#include "KR.h"
#include"Prime.h"

//m��Ҫѡȡ���ʵ�ģ ����ѡȡ���ֵ�Ͳ�ѡȡһ��
//constexpr uint64_t M =  18446744073709551611;//32λ�������Ϊɢ�б��� 
constexpr uint64_t R= 31;//����:������ BKDR Hash

/*
BKDR Hash
*/
uint64_t BKDRHash(const char*c){
	uint64_t hash = 0;
	//ֱ���ַ�����һ��00
	while (uint64_t ch =(uint64_t)*c++)
	{
		hash = hash * 1313 + ch;//��ȡ31,131,1313...
	}
	return hash;
}

uint64_t digit(char c) {
	return c ;
}

/*
����ƥ��m���ַ��Ƿ���� O(m)
���� �ַ��� ƥ�䴮 λ�� ����
*/
bool isMatch(char*t,char*p,uint64_t pos,uint64_t m) {
	size_t i = 0;
	for (; i < m ;) {
		if (t[pos++] != p[i++])return false;
	}
	return true;
}

/*
������ O(1)
���� t:�ַ��� k:��ǰλ�� m:���� dm�����λӰ��ֵ hashCode��������
O(1)
*/
void updateHash(char*t, uint64_t&k,uint64_t m,uint64_t&dm,uint64_t&hashCode ) {
	hashCode = (hashCode - digit(t[k - 1]) * dm) ;
	hashCode = (hashCode*R+ digit(t[k+m-1]));
}

int kr_match(char * t, char * p)
{
	const uint64_t n = strlen(t);const uint64_t m = strlen(p);
	if (n < m || m == 0)return -1;//�˻�
	uint64_t dm = 1; uint64_t ht = 0, hm = 0;
	for (uint64_t i = 1; i < m; ++i) {
		dm = (dm*R);
	}
	for (uint64_t i = 0; i < m; ++i)
	{
		hm = (hm*R + digit(p[i]));
		ht = (ht*R + digit(t[i]));
	}
	int _c = n - m;
	for (uint64_t i = 0; ;) {
		if (ht == hm) {
			if (isMatch(t, p, i, m))return i;
		}
		if (++i >_c)return -1;
		updateHash(t,i,m,dm,ht);//������һ����
	}
}

