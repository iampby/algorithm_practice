#include"Comparer.h"
#include<queue>

/*
选择排序
概念:序列分为无序的前缀和有序的后缀，不断从前缀选出最大值作为后缀的首元素
O(nlogn)
*/

/*
向量版
*/
template<typename T = int, typename _Comparer = MyLess<T> >
void selectSort(std::vector<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	std::priority_queue<T>q;//辅助优先级队列
	int _s = _dst.size();
	//O(nlogn)构建
	for (int i = 0; i < _s; ++i) {
		q.push(_dst[i]);
	}
	//O(n)排序
	for (int i = _s - 1; i >= 0; --i) {
		_dst[i] = q.top();
		q.pop();
	}
}