#ifndef ALGORITHM_K_SELECT_H_H_H
#define ALGORITHM_K_SELECT_H_H_H

#include"Comparer.h"
#include<vector>
#include<iostream>
#include<algorithm>


/*
���̣�
1 ѡȡһ������Q(ȡ5),n(����)<QʱBF����
2 ���л���Ϊn/Q������ΪQ������
3 �����зֱ������λ�����һ������
4 ��λ������ѡȡ��λ����ΪM
5 ����M��С ����������Ϊ3���Ӽ���L��E��G
6 �����Ӽ�������k�Ĵ�С�����Ƿ�ݹ���߷���kֵ
T(n)=c*n+T(n/Q)+T(3n/4)=O(n),cΪ����
���ڳ�������һ���ģ��ʵ��Ӧ���в�ռ���ƣ�С��ģӦ��������
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
����k-ѡ���㷨
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
	std::vector<T>mv;//��λ������
	mv.reserve(gc);
	int fgc = gc - 1;
	while (fgc>0)
	{
		int e = fgc * Q; int b = e - Q;
		int mid = b + Q / 2;//��λ
		std::partial_sort(_dst.begin()+b,_dst.begin()+e-1, _dst.begin() + e,_comparer);//��������
		mv.push_back(_dst[mid]);//��λ�����
		--fgc;
		}
	{
		int t = Q * (gc - 1);
		std::partial_sort(_dst.begin() + t, _dst.end() - 1, _dst.end(), _comparer);
		mv.push_back(_dst[(n - t - 1) / 2 + t]);
	}
	std::sort(mv.begin(), mv.end(), _comparer);
	T M = mv[(mv.size() - 1) / 2];
	std::vector<T>L, E, G;//С�� ���� ����
	L.reserve(0.75*n); G.reserve(0.75*n);//���ᳬ��n*0.75
	E.reserve(Q);
	//���ּ���
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
	//��6���ݹ鲿��
	if (L.size() > k)return k_select(L, k, _comparer);
	else if (L.size() + E.size() > k)return M;//������λ��
	else return k_select(G, k - L.size() - E.size());
}

#endif // !#ifndef ALGORITHM_K_SELECT_H_H_H

