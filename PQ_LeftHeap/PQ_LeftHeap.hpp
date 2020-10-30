#ifndef PQ_LEFTHEAP_HPP_HPP
#define PQ_LEFTHEAP_HPP_HPP

#include<vector>
#include"BinTree.h" 
#include"PriorityQueue.h"
#include"Comparer.h"

template<typename T=int,typename _Comparer=myLess<T> >
class PQ_LeftHeap:public PriorityQueue<T>,public BT::BinTree<T>
{
public:
	PQ_LeftHeap();
	// O(n) 批量插入 floyd算法 用右值指示值会丢失 注：一颗完全二叉树也是一个特殊的左式堆 性能比直接插入可能慢约几毫秒，也可能快（因插入过多导致npl越来越大）,比遍历删除快2倍多 
	//经测试对于1千万+数据建堆比暴力算法胜出
	PQ_LeftHeap(std::vector<T>&&);
	PQ_LeftHeap(std::vector<T>&);//暴力插入  貌似平均O（N）而不是O（nlogn）
	~PQ_LeftHeap();
	//接口
	 void push(T const&);//插入词条
	 const T& top();//弹出堆顶
	 void pop();//删除堆顶 
	 int NPL()const;//root null path length
	 static BTN::BNP(T)merge(BTN::BNP(T) a, BTN::BNP(T) b);//基操堆合并
protected:
	static int NPL(BTN::BNP(T));//null path length
	static int updateNPL(BTN::BNP(T));
	BTN::BNP(T) heapify(std::vector<T>&);//Floyd算法 不更新规模 但更新高度(已转化为npl) 参数为要批量创建的词条
protected:
	_Comparer f_comparer;//比较器
};

#include"PQ_LeftHeap.cpp"

#endif // !PQ_LEFTHEAP_HPP_HPP
