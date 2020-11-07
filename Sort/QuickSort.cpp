#include"Comparer.h"
#include<vector>

/*
快速排序
概念：通过分治策略，不停地选取轴点划分空间，得到有序序列，如果序列S经排序后为S'，如有轴点mi，lo为最低为，hi为最高位,则:
1 S[mi]=S'[mi]
2 S[lo,mi)=S'[lo,min)全体成员相同
3 S(mi,hi)=S'(mi,hi)全体成员相同
O(nlogn)
*/

/*
获取轴点
采用3元素中位数法
O(n)
*/
template<typename T = int, typename _Comparer = MyLess<T> >
int partition(std::vector<T>&_dst, int lo, int hi , _Comparer _comparer = MyLess<T>()) {
	//取3元素的中位数
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
	T m = _dst[lo];//轴点值
	while (lo<hi)
	{
		while (lo<hi)
		{
			//因为lo为轴点值，先整理右边
			if (m < _dst[hi])--hi;
			else {
				_dst[lo++] = _dst[hi];
				break;//多余值转到右边，现整理左边
			}
		}
		while (lo < hi) {
			if (m > _dst[lo])++lo;
			else {
				_dst[hi--] = _dst[lo];
				break;//多余值转到左边，现整理右边
			}
		}
	}
	_dst[lo] = m;//轴点值
	return lo;//轴点
}

template<typename T = int, typename _Comparer = MyLess<T> >
void quickSort(std::vector<T>&_dst,int lo,int hi ,_Comparer _comparer = MyLess<T>()) {
	if (hi - lo < 2)return;//递归基
	int mi = partition(_dst, lo, hi - 1, _comparer);
	quickSort(_dst, lo, mi, _comparer); quickSort(_dst, mi+1, hi, _comparer);
}

/*
向量版 快排
采用3元素中位数法
O(nlogn)
*/
template<typename T = int, typename _Comparer = MyLess<T> >
void quickSort(std::vector<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	quickSort(_dst, 0, _dst.size(), _comparer);
}