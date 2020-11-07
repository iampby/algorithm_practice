#ifndef ALGORITHM_K_SELECT_H_H_H
#define ALGORITHM_K_SELECT_H_H_H

#include"Comparer.h"
#include<vector>
#include<iostream>
#include<algorithm>


/*
流程：
1 选取一个奇数Q(取5),n(长度)<Q时BF计算
2 序列划分为n/Q个长度为Q的序列
3 子序列分别计算中位数组成一个序列
4 中位数序列选取中位数作为M
5 根据M大小 将向量划分为3个子集：L、E、G
6 根据子集长度与k的大小绝对是否递归或者返回k值
T(n)=c*n+T(n/Q)+T(3n/4)=O(n),c为常数
由于常数过大，一般规模的实际应用中不占优势，小规模应用中劣势
*/
template<typename T=int, typename _Comparer = MyLess<T> >
T k_select(std::vector<T>&_dst,int k,_Comparer _comparer = MyLess<T>()) {
	try
	{
		if (k < 0 || k >= _dst.size())throw "k_select with k range of out ";
	}
	catch (const std::exception&e)
	{
		std::cerr << e.what() <<std::endl;
	}
	int Q = 25;
	return k_select(_dst, k, Q, _comparer);
}

/*
蛮力k-选择算法
O(nlogn)
*/
template<typename T = int, typename _Comparer = MyLess<T> >
T BF_select(std::vector<T>&_dst, int k, _Comparer _comparer = MyLess<T>()) {
	std::sort(_dst.begin(), _dst.end(), _comparer);
	return _dst[k];
}

template<typename T = int, typename _Comparer = MyLess<T> >
T k_select(std::vector<T>&_dst, int k,int& Q, _Comparer _comparer = MyLess<T>()) {
	int n = _dst.size();
	if (n <= Q)return BF_select(_dst, k, _comparer);
	int gc = (n-1) / Q+1;
	std::vector<T>mv;//中位数序列
	mv.reserve(gc);
	int fgc = gc - 1;
	while (fgc>0)
	{
		int e = fgc * Q; int b = e - Q;
		int mid = b + Q / 2;//中位
		std::partial_sort(_dst.begin()+b,_dst.begin()+e-1, _dst.begin() + e,_comparer);//部分排序
		mv.push_back(_dst[mid]);//中位数入队
		--fgc;
		}
	{
		int t = Q * (gc - 1);
		std::partial_sort(_dst.begin() + t, _dst.end() - 1, _dst.end(), _comparer);
		mv.push_back(_dst[(n - t - 1) / 2 + t]);
	}
	std::sort(mv.begin(), mv.end(), _comparer);
	T M = mv[(mv.size() - 1) / 2];
	std::vector<T>L, E, G;//小于 等于 大于
	L.reserve(0.75*n); G.reserve(0.75*n);//不会超过n*0.75
	E.reserve(Q);
	//划分集合
	{
		MyEqual<T>eq;
		for (int i = 0; i < n; ++i) {
			if (eq(_dst[i], M)) {
				E.push_back(_dst[i]);
			}
			else if(_comparer(_dst[i], M)) {
				L.push_back(_dst[i]);
			}
			else {
				G.push_back(_dst[i]);
			}
		}
	}
	//第6步递归部分
	if (L.size() > k)return k_select(L, k, _comparer);
	else if (L.size() + E.size() > k)return M;//返回中位数
	else return k_select(G, k - L.size() - E.size());
}

#endif // !#ifndef ALGORITHM_K_SELECT_H_H_H

