#include"Comparer.h"
#include<vector>

/*
��������
���ͨ�����β��ԣ���ͣ��ѡȡ��㻮�ֿռ䣬�õ��������У��������S�������ΪS'���������mi��loΪ���Ϊ��hiΪ���λ,��:
1 S[mi]=S'[mi]
2 S[lo,mi)=S'[lo,min)ȫ���Ա��ͬ
3 S(mi,hi)=S'(mi,hi)ȫ���Ա��ͬ
O(nlogn)
*/

/*
��ȡ���
����3Ԫ����λ����
O(n)
*/
template<typename T = int, typename _Comparer = MyLess<T> >
int partition(std::vector<T>&_dst, int lo, int hi , _Comparer _comparer = MyLess<T>()) {
	//ȡ3Ԫ�ص���λ��
	{
		srand(lo);
		int l = rand() % (hi - lo + 1)+lo,m= rand() % (hi - lo + 1) + lo,h= rand() % (hi - lo + 1) + lo;
		if (_comparer(_dst[l], _dst[h])) {
			if (_comparer(_dst[h], _dst[m]))
				std::swap(_dst[h], _dst[lo]);
			else {
				if (_comparer(_dst[l], _dst[m]))
					std::swap(_dst[m], _dst[lo]);
				else std::swap(_dst[l], _dst[lo]);
			}
		}
		else {
			if (!_comparer(_dst[h], _dst[m]))
				std::swap(_dst[h], _dst[lo]);
			else {
				if (!_comparer(_dst[l], _dst[m]))
					std::swap(_dst[m], _dst[lo]);
				else std::swap(_dst[l], _dst[lo]);
			}
		}
	}
	T m = _dst[lo];//���ֵ
	while (lo<hi)
	{
		while (lo<hi)
		{
			//��ΪloΪ���ֵ���������ұ�
			if (m < _dst[hi])--hi;
			else {
				_dst[lo++] = _dst[hi];
				break;//����ֵת���ұߣ����������
			}
		}
		while (lo < hi) {
			if (m > _dst[lo])++lo;
			else {
				_dst[hi--] = _dst[lo];
				break;//����ֵת����ߣ��������ұ�
			}
		}
	}
	_dst[lo] = m;//���ֵ
	return lo;//���
}

template<typename T = int, typename _Comparer = MyLess<T> >
void quickSort(std::vector<T>&_dst,int lo,int hi ,_Comparer _comparer = MyLess<T>()) {
	if (hi - lo < 2)return;//�ݹ��
	int mi = partition(_dst, lo, hi - 1, _comparer);
	quickSort(_dst, lo, mi, _comparer); quickSort(_dst, mi+1, hi, _comparer);
}

/*
������ ����
����3Ԫ����λ����
O(nlogn)
*/
template<typename T = int, typename _Comparer = MyLess<T> >
void quickSort(std::vector<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	quickSort(_dst, 0, _dst.size(), _comparer);
}