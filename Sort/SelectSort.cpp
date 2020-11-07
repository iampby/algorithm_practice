#include"Comparer.h"
#include<queue>

/*
ѡ������
����:���з�Ϊ�����ǰ׺������ĺ�׺�����ϴ�ǰ׺ѡ�����ֵ��Ϊ��׺����Ԫ��
O(nlogn)
*/

/*
������
*/
template<typename T = int, typename _Comparer = MyLess<T> >
void selectSort(std::vector<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	std::priority_queue<T>q;//�������ȼ�����
	int _s = _dst.size();
	//O(nlogn)����
	for (int i = 0; i < _s; ++i) {
		q.push(_dst[i]);
	}
	//O(n)����
	for (int i = _s - 1; i >= 0; --i) {
		_dst[i] = q.top();
		q.pop();
	}
}