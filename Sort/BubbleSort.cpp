#include<vector>
#include<list>
#include"Comparer.h"


/*
起泡排序 实现了常规版和跳跃版
O(n^2)
*/

/*
向量版
*/
template<typename T=int, typename _Comparer = MyLess<T> >
void bubbleSort(std::vector<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	switch (rand() % 2)
	{
	case 0: {//常规版
		bool sorted = false;
		int _s = _dst.size();
		while (!sorted)
		{
			sorted = true;
			for (int i = 0; i < _s - 1; ++i) {
				if (_comparer(_dst[i + 1], _dst[i])) {
					std::swap(_dst[i + 1], _dst[i]);
					sorted = false;
				}
			}
			--_s;
		}
	}
			break;
	case 1: {//跳跃版
		int _s = _dst.size();
		for (int sorted = --_s; _s>0; _s = sorted)//跳跃式更新已固定排序的后缀长度起始位置
			for (int i = sorted=0; i < _s; ++i)
				if (_comparer(_dst[i + 1], _dst[i])) //若逆序，则
					std::swap(_dst[i + 1], _dst[sorted=i]);; //经交换使局部有序
	}
			break;
	}
};

/*
列表版
*/
template<typename T=int, typename _Comparer = MyLess<T> >
void bubbleSort(std::list<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	switch (rand() % 2)
	{
	case 0: {//常规版
		auto its = --_dst.end();
		bool sorted = false;
		while (!sorted)
		{
			sorted = true;
			for (auto it = _dst.begin(); it != its; ++it) {
				auto t = it;
				std::advance(t, 1);
				if (_comparer(*t, *it)) {
					std::swap(*t, *it);
					sorted = false;
				}
			}
			--its;
		}
	}
		break;
	case 1: {//跳跃版
		auto its = --_dst.end();
		auto sorted=its;
		while ((its=sorted)!= _dst.begin())
		{
			for (auto it =sorted= _dst.begin(); it != its; ++it) {
				auto t = it;
				std::advance(t, 1);
				if (_comparer(*t, *it)) {
					std::swap(*t, *it);
					sorted = it;
				}
			}
		}
	}
			break;
	};
};
