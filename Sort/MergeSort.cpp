#include"Comparer.h"
#include<vector>
#include<list>


/*
归并排序
思想：对2个有序序列合并成一个有序序列，每次迭代中，只需比较2个待归并向量的首元素，
取大于或者小于到输出向量的末尾，直到某个为空，则另一个向量元素依次输出到输出向量
O(nlogn）
*/

template<typename T, typename _Comparer = MyLess<T> >
void merge(std::vector<T>&_dst, size_t lo, size_t hi, _Comparer _comparer = MyLess<T>());

/*
向量版 
默认小到大
Θ(nlogn)
*/
template<typename T=int, typename _Comparer=MyLess<T> >
void mergeSort(std::vector<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	size_t _hi = _dst.size();
	merge(_dst, 0, _hi, _comparer); 
}

template<typename T, typename _Comparer = MyLess<T> >
void merge(std::list<T>&_dst, _Comparer _comparer = MyLess<T>());

/*
列表版 
 默认小到大
 O(nlogn)
*/
template<typename T=int, typename _Comparer = MyLess<T> >
void mergeSort(std::list<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	merge(_dst,_comparer);
}

/*
向量版归并
Θ(nlogn)
*/
template<typename T, typename _Comparer >
void merge(std::vector<T>&_dst,size_t lo,size_t hi, _Comparer _comparer) {
	size_t mid = (hi - lo);
	if (mid < 2)return;//递归基
	mid = lo + mid / 2;
	merge(_dst, lo, mid, _comparer); merge(_dst, mid, hi, _comparer);
	std::vector<T>pre;//复制前半向量
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
列表版归并 取末尾比较而非取首位
O(nlogn)
*/
template<typename T, typename _Comparer  >
void merge(std::list<T>&_dst, _Comparer _comparer) {
	if (_dst.size() < 2)return;//递归基
	std::list<T>_left, _right;
	auto it = _dst.begin();
	std::advance(it, _dst.size() / 2);
	_right.splice(_right.begin(), _dst, it,_dst.end());//分2半
	_left = std::move(_dst);//_dst已空
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
