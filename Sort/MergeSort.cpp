#include"Comparer.h"
#include<vector>
#include<list>


/*
�鲢����
˼�룺��2���������кϲ���һ���������У�ÿ�ε����У�ֻ��Ƚ�2�����鲢��������Ԫ�أ�
ȡ���ڻ���С�ڵ����������ĩβ��ֱ��ĳ��Ϊ�գ�����һ������Ԫ������������������
O(nlogn��
*/

template<typename T, typename _Comparer = MyLess<T> >
void merge(std::vector<T>&_dst, size_t lo, size_t hi, _Comparer _comparer = MyLess<T>());

/*
������ 
Ĭ��С����
��(nlogn)
*/
template<typename T=int, typename _Comparer=MyLess<T> >
void mergeSort(std::vector<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	size_t _hi = _dst.size();
	merge(_dst, 0, _hi, _comparer); 
}

template<typename T, typename _Comparer = MyLess<T> >
void merge(std::list<T>&_dst, _Comparer _comparer = MyLess<T>());

/*
�б�� 
 Ĭ��С����
 O(nlogn)
*/
template<typename T=int, typename _Comparer = MyLess<T> >
void mergeSort(std::list<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	merge(_dst,_comparer);
}

/*
������鲢
��(nlogn)
*/
template<typename T, typename _Comparer >
void merge(std::vector<T>&_dst,size_t lo,size_t hi, _Comparer _comparer) {
	size_t mid = (hi - lo);
	if (mid < 2)return;//�ݹ��
	mid = lo + mid / 2;
	merge(_dst, lo, mid, _comparer); merge(_dst, mid, hi, _comparer);
	std::vector<T>pre;//����ǰ������
	size_t _s = mid - lo;
	pre.reserve(_s);
	for (size_t i = lo; i < mid; ++i) {
		pre.push_back(_dst[i]);
	}
	size_t i = 0, j = mid,pos=lo;
	while (i!=_s&&j!=hi)
	{
		if (_comparer(_dst[j], pre[i])) {
			_dst[pos] = _dst[j];
			++j;
		}
		else {
			_dst[pos] = pre[i];
			++i;
		}
		++pos;
	}
	while(i != _s) {
		_dst[pos] = pre[i];
		++i; ++pos;
	}
}

/*
�б��鲢 ȡĩβ�Ƚ϶���ȡ��λ
O(nlogn)
*/
template<typename T, typename _Comparer  >
void merge(std::list<T>&_dst, _Comparer _comparer) {
	if (_dst.size() < 2)return;//�ݹ��
	std::list<T>_left, _right;
	auto it = _dst.begin();
	std::advance(it, _dst.size() / 2);
	_right.splice(_right.begin(), _dst, it,_dst.end());//��2��
	_left = std::move(_dst);//_dst�ѿ�
	merge(_left, _comparer); merge(_right, _comparer);
	while (!_left.empty()&&!_right.empty())
	{
		auto itl = --_left.end(),itr=--_right.end();
		if (!_comparer(*itr, *itl)) {
			_dst.splice(_dst.begin(),_right,itr,_right.end());
		}
		else {
			_dst.splice(_dst.begin(), _left, itl, _left.end());
		}
	}
	if (_left.empty()) {
		_dst.splice(_dst.begin(), _right);
	}
	else {
		_dst.splice(_dst.begin(), _left);
	}
}
