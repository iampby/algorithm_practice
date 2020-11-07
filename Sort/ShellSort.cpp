
#include"Comparer.h"
#include<vector>


template<typename T=int>
size_t sedk_lastIncrement(size_t n, bool&formula1, int&increment);

/*
ϣ������
�����Ч�İ�һάA[]������Ϊһ����ά����B[][],��ȡ�п�w ���ж�Ӧ��ϵ
B[i][j]=A[i*w+j]��A[k]=B[k/w][k%w] wΪ���� w={1,w1,...,wk,...},ȡ wi<n�����һ����s����ʼ���� 
ÿ�ΰ�������A����w-���� ֱ��w=1 �������
�������У�Sedgewick���� ʵ��Ӧ��Ч���ۺ����� 9*4^k-9*2^k+1(k��0��) �� 4^k-3*2^k+1(��2��) ����ִ�е�ǰ����ִ��
O��n^(4/3)�� ƽ��O(7/6)
*/
template<typename T = int, typename _Comparer = MyLess<T> >
void shellSort(std::vector<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	int n = _dst.size();  
	bool one; int increment;
	size_t k = sedk_lastIncrement(n, one, increment);
	for (; increment > 0; ) {
		for (int i = increment; i < n; i += increment) {//increment-����
			T bv = _dst[i];//��¼�� 
			int li = i - increment;//ͬһ�е���һ����
			while (li>=0&&_comparer(bv,_dst[li]))
			{
				_dst[li + increment] = _dst[li];; li -= increment;
			}
			_dst[li + increment] = bv;//��Ϊ����������ֵbv
		}
		//��������
		if (one) {
			one = !one;
			k += 1;
			increment = pow(4, k) - 3 * pow(2, k) + 1;
		}
		else {
			one = !one;
			k -= 2;
			increment = 9 * pow(4, k) - 9 * pow(2, k) + 1;
		}
	}
}

/*
����Sedgewick�������е�С��n�����һ������
formula1==trueָʾ���һ������ʹ��9 * 4 ^ k - 9 * 2 ^ k + 1�õ� ���� 4 ^ k - 3 * 2 ^ k + 1�õ�
����ֵΪk
*/
template<typename T>
size_t sedk_lastIncrement(size_t n, bool&formula1, int&increment)
{
	//9 * 4 ^ k - 9 * 2 ^ k + 1(k��0��)�� 4 ^ k - 3 * 2 ^ k + 1(��2��)
	int k = (n - 1) / 9;
	k = log2(k) / 2;
	increment = 9 * pow(4, k) - 9 * pow(2, k) + 1;
	formula1 = true;//������һ��ʹ��9 * 4 ^ k - 9 * 2 ^ k + 1��ʽ
	while (increment < n)
	{
		if (formula1) {
			k += 2;
			increment = pow(4, k) - 3 * pow(2, k) + 1;
			formula1 = false;
		}
		else {
			k -= 1;
			increment = 9 * pow(4, k) - 9 * pow(2, k) + 1;
			formula1 = true;
		}
	}
	if (formula1) {
		k += 1;
		formula1 = !formula1;
		increment = pow(4, k) - 3 * pow(2, k) + 1;
	}
	else {
		k -= 2;
		formula1 = !formula1;
		increment = 9 * pow(4, k) - 9 * pow(2, k) + 1;
	}
	return k;
}
