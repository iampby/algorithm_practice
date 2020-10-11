#ifndef TRAVERSALINF_H_H
#define TRAVERSALINF_H_H

#include"BTreeNode.h"
#include<iostream>
#include<stack>
//注：B-树树高相对较浅，故这里考虑采用递归的方式遍历 即方便，内存消耗也不高

//中序遍历
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
	int size = n->key.size();//获取码数
	int i = 0;
	for (; i < size; ++i) {
		BTN::BTN(T)p = n->child[i];
		if (p)//先遍历左边
			InorderTraversal::operator()(p);//虚函数调用指定类名一致
		visit(n->key[i]);//处理当前访问值
		if (n->same[i].size() != 0) {
			int ts = n->same[i].size();
			for (int j = 0; j < ts; ++j) {
				visit(n->same[i][j]);//遍历每一个相同值
			}
		}
	}
	BTN::BTN(T)p = n->child[i];
	if (p)//节点最右边分支遍历
		InorderTraversal::operator()(p);//虚函数调用指定类名一致
}

template<typename T>
inline void InorderTraversal<T>::visit(T const &d)
{
	std::cout << d << " ";
}


#endif // !TRAVERSALINF_H_H