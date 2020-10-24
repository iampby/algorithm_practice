#ifndef PRIME_H_H
#define PRIME_H_H
#include<iostream>
//#include<deque>
/*
������ 
����һ:(�˷����轨�������ã���Ϊ������������)
����������ķ�ʽ����
(1) �趨����P=0, ��Ϊ��־����, P=0��ʾNΪ����, P=1��ʾN��������;�趨����K, KΪN��λ��.���K=1, ��T1={3, 7}.
(2) ���TK-1������, �ȼ�������TK-2;���TK-1����, M��������TK-1������ȡֵѭ��ִ�� (3) ;
(3) ���MС�ڵ��ڸ���N, ��N����M;������Ϊ��, ��P=1, ���� (5) ;
(4) ȡTK-1�е���һ��ֵ�ص� (3) .��ȫ��ȡ��, �� (5) ;
(5) ���P=0, ��N������, ����N��������.
������
���������������������ɵģ����������ʽ�ж�
N0=4k1*k2��2k1��2k2��1  �������ʽ
�� k2=((N0-1)/2-k1)/(2k1+1)
k2Ϊ����
1=<k1<(N0-1)/6-1/3
*/
/*
Ч�� O(2sqrt(number)/5)
*/
static bool isPrime(const uint32_t & number)
{
	//����һ ������
	/*
	if (number == 0)return false;//�������
	bool p = true;//��Ǳ���
	
	uint32_t k =(uint32_t)log10(number)+1;//λ��
if (k == 1) {
	if ( number != 2 && number != 3 && number != 5 && number != 7)p = false;
	return p;
	}
uint32_t _1 = number - number / 10 * 10;
if (_1 == 1 || _1 == 7 || _1 == 3 || _1 == 9) {//���� ִ�м��
	std::deque<uint32_t>T;//����
	T.push_back(3); T.push_back(7);//T1
	if (k == 2) {
		uint32_t _s = T.size();

		for (uint32_t i = 0; i < _s; ++i) {
			if (number%T[i] == 0) {
				p = false;
				break;
			}
}
		return p;
	}
	else {//����Tk-1 
		uint16_t _max = (uint32_t)pow(10, k - 1);
		uint32_t _1 = 1;//��λ��
		for (uint32_t i = 11; i < _max; ) {
			uint32_t _range = sqrt(i);
			switch (_1)//����������������������
			{
			case 1:
			{
				bool p = true;//��Ǳ���
				for (uint32_t j = 3; j <= _range; j += 10) {
					if (i%j == 0 || i % (j + 6) == 0 || (i % (j + 8) == 0 && (j + 8) != i)) {//�п������Ϊi ����һ��
						p = false;
						break;
					}
				}
				if (p) T.push_back(i);
				_1 = 3;//��һ��Ϊ3
				i += 2;//��2��
			}
			break;
			case 3:
			{
				bool p = true;//��Ǳ���
				for (uint32_t j = 3; j <= _range; j += 10) {
					if (i%j == 0 || i % (j + 4) == 0) {
						p = false;
						break;
					}
				}
				if (p) T.push_back(i);
				_1 = 7;//��һ��Ϊ7
				i += 4;//��4��
			}
			break;
			case 7:
			{
				bool p = true;//��Ǳ���
				for (uint32_t j = 3; j <= _range; j += 10) {
					if (i%j == 0 || i % (j + 4) == 0) {
						p = false;
						break;
					}
				}
				if (p) T.push_back(i);
				_1 = 9;//��һ��Ϊ9
				i += 2;//��2��
			}
			break;
			case 9:
			{
				bool p = true;//��Ǳ���
				for (uint32_t j = 3; j <= _range; j += 10) {
					if (i%j == 0 || i % (j + 4) == 0 || i % (j + 6) == 0) {
						p = false;
						break;
					}
				}
				if (p) T.push_back(i);
				_1 = 1;//��һ��Ϊ1
				i += 2;//��2��
			}
			break;
			default://�߼�����
				std::cerr << "error:finding prime logic is't normal!!!\n";
				exit(-1);
			}
		}
		//Tk-1ȡֵ�ж�
		{
			uint32_t _s = T.size();
			uint32_t _range = sqrt(number);
				for (uint32_t i = 0; i < _s; ++i) {
					if (T[i] > _range) break;
					if (number%T[i] == 0)
					{
						p = false;
						break;
					}
				}
			return p;
		}
	}
}
return false;
*/
//����һ ������������
bool p = true;//��Ǳ���
if (number < 12) {//���˵�����ֵ11,��������������������ִ��
	if (number != 2 && number != 3 && number != 5 && number != 7&&number!=11)p = false;
	return p;
}
uint32_t _1 = number - number / 10 * 10;
if (_1 == 1 || _1 == 7 || _1 == 3 || _1 == 9) {//���� ִ�м��
	//����������������������
	uint32_t _range = sqrt(number);
		for (uint32_t j = 3; j <= _range; j += 10) {
			if (number%j == 0 || number % (j + 6) == 0 || number % (j + 8) == 0||number%(j+4)==0) {
				p = false;
				break;
			}
		}
		return p;
}
return false;
};
/*
������ Ч�ʵ��� O��number/6��
N0 = 4k1*k2��2k1��2k2��1  �������ʽ
�� k2 = ((N0 - 1) / 2 - k1) / (2k1 + 1)
k2Ϊ����
1 = < k1 < (N0 - 1) / 6 - 1 / 3
*/
static bool isPrime_Formula(const uint32_t & number) {
	bool p = true;
	if (number<10) {
		if (number != 2 && number != 3 && number != 5 && number != 7)p = false;
		return p;
	}
	uint32_t _1 = number - number / 10 * 10;
	if (_1 == 1 || _1 == 7 || _1 == 3 || _1 == 9) {//���� ִ��Tk-1���
		uint32_t _mk1 = (double)(number - 1) / 6 - (double)1 / 3 + 1;
		for (int i = 1; i < _mk1; ++i) {
			double k2 = ((double)(number - 1) / 2 - i) / (2 * i + 1);
			if (k2 == (uint32_t)k2) {//�����
				p = false;
				break;
			}
		}
		return p;
	}
	return false;
}
#endif // !PRIME_H_H

