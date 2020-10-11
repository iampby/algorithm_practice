#ifndef TRAVERSALINF_H_H
#define TRAVERSALINF_H_H

#include"BTreeNode.h"
#include<iostream>
#include<stack>
//ע��B-��������Խ�ǳ�������￼�ǲ��õݹ�ķ�ʽ���� �����㣬�ڴ�����Ҳ����

//�������
template<typename T>
class InorderTraversal
{
public:
	virtual void operator()(BTN::BTN(T)n);
protected:
	void visit(T const&);
};

template<typename T>
inline void InorderTraversal<T>::operator()(BTN::BTN(T)n)
{
	int size = n->key.size();//��ȡ����
	int i = 0;
	for (; i < size; ++i) {
		BTN::BTN(T)p = n->child[i];
		if (p)//�ȱ������
			InorderTraversal::operator()(p);//�麯������ָ������һ��
		visit(n->key[i]);//����ǰ����ֵ
		if (n->same[i].size() != 0) {
			int ts = n->same[i].size();
			for (int j = 0; j < ts; ++j) {
				visit(n->same[i][j]);//����ÿһ����ֵͬ
			}
		}
	}
	BTN::BTN(T)p = n->child[i];
	if (p)//�ڵ����ұ߷�֧����
		InorderTraversal::operator()(p);//�麯������ָ������һ��
}

template<typename T>
inline void InorderTraversal<T>::visit(T const &d)
{
	std::cout << d << " ";
}


#endif // !TRAVERSALINF_H_H