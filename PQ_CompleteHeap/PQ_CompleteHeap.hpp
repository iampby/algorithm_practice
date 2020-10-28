#ifndef PQ_COMPLETEHEAP_H_H
#define PQ_COMPLETEHEAP_H_H

#include<vector>
#include"PriorityQueue.h"
#include"Comparer.h"
/*
优先级队列之完全二叉堆，采用向量vector为底层容器, 默认为大顶堆
*/

template<typename T, typename _Comparer = myLess<T> >
class PQ_CompleteHeap :public PriorityQueue<T>, public std::vector<T>
{
public:
	PQ_CompleteHeap();
	PQ_CompleteHeap(std::vector<T>&&set);
	//接口
	 void push(T const&);//插入词条
	 const T& top();//弹出堆顶
	 void pop();//删除堆顶
	 int size()const;
protected:
	 //辅助函数
	int left(int i)const;//左孩子索引
	int right(int i)const;//右孩子索引
	int parent(int i)const;//父亲索引
	bool hasParent(int i)const;
	bool isVaildIndex(int i)const;//判断索引是否合法
protected:
	void percolateDown(int i);//下滤
	void percolateUp(int i);//上滤
	void heapify();//Floyd建堆
protected:
	_Comparer f_comparer;//比较器
};

#include"PQ_CompleteHeap.cpp"

#endif // !PQ_COMPLETEHEAP_H_H


