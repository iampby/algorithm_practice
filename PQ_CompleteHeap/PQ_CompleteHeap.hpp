#ifndef PQ_COMPLETEHEAP_H_H
#define PQ_COMPLETEHEAP_H_H

#include<vector>
#include"PriorityQueue.h"
#include"Comparer.h"
/*
���ȼ�����֮��ȫ����ѣ���������vectorΪ�ײ�����, Ĭ��Ϊ�󶥶�
*/

template<typename T, typename _Comparer = myLess<T> >
class PQ_CompleteHeap :public PriorityQueue<T>, public std::vector<T>
{
public:
	PQ_CompleteHeap();
	PQ_CompleteHeap(std::vector<T>&&set);
	//�ӿ�
	 void push(T const&);//�������
	 const T& top();//�����Ѷ�
	 void pop();//ɾ���Ѷ�
	 int size()const;
protected:
	 //��������
	int left(int i)const;//��������
	int right(int i)const;//�Һ�������
	int parent(int i)const;//��������
	bool hasParent(int i)const;
	bool isVaildIndex(int i)const;//�ж������Ƿ�Ϸ�
protected:
	void percolateDown(int i);//����
	void percolateUp(int i);//����
	void heapify();//Floyd����
protected:
	_Comparer f_comparer;//�Ƚ���
};

#include"PQ_CompleteHeap.cpp"

#endif // !PQ_COMPLETEHEAP_H_H


