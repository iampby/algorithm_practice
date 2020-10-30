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
	// O(n) �������� floyd�㷨 ����ֵָʾֵ�ᶪʧ ע��һ����ȫ������Ҳ��һ���������ʽ�� ���ܱ�ֱ�Ӳ��������Լ�����룬Ҳ���ܿ죨�������ർ��nplԽ��Խ��,�ȱ���ɾ����2���� 
	//�����Զ���1ǧ��+���ݽ��ѱȱ����㷨ʤ��
	PQ_LeftHeap(std::vector<T>&&);
	PQ_LeftHeap(std::vector<T>&);//��������  ò��ƽ��O��N��������O��nlogn��
	~PQ_LeftHeap();
	//�ӿ�
	 void push(T const&);//�������
	 const T& top();//�����Ѷ�
	 void pop();//ɾ���Ѷ� 
	 int NPL()const;//root null path length
	 static BTN::BNP(T)merge(BTN::BNP(T) a, BTN::BNP(T) b);//���ٶѺϲ�
protected:
	static int NPL(BTN::BNP(T));//null path length
	static int updateNPL(BTN::BNP(T));
	BTN::BNP(T) heapify(std::vector<T>&);//Floyd�㷨 �����¹�ģ �����¸߶�(��ת��Ϊnpl) ����ΪҪ���������Ĵ���
protected:
	_Comparer f_comparer;//�Ƚ���
};

#include"PQ_LeftHeap.cpp"

#endif // !PQ_LEFTHEAP_HPP_HPP
