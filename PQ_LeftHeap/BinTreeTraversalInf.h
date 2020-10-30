#ifndef BINTREETRAVERSALINF_H_H
#define  BINTREETRAVERSALINF_H_H

#include"BinTreeNode.h"
#include<queue>

/*
先序遍历
思路：中-左-右，用2个bool追踪标记是否访问了左右孩子，如果都已访问则回溯到最近的真祖先节点
*/
template<typename T>struct PreorderTraversal
{
	virtual void operator()(BTN::BinTreeNode<T>*n) {
		BTN::BinTreeNode<T>*root = n;
		bool backtrack1 = false, backtrack2 = false;//标记当前节点左右孩子是否访问完
		dataProcessing(n->data);//数据处理
		while (true)
		{
			if (n->hasLeftChild() && !backtrack1) {
				n = n->left;//往左遍历
				backtrack1 = false, backtrack2 = false;//未访问
				dataProcessing(n->data);//数据处理
			}
			else if (n->hasRightChild() && !backtrack2) {
				n = n->right;//左孩子访问完 就访问右孩子
				backtrack1 = false, backtrack2 = false;//未访问
				dataProcessing(n->data);//数据处理
			}
			else {
				if (n->isLeftChild()) {
					backtrack1 = true, backtrack2 = false;
				}
				else {
					backtrack1 = true, backtrack2 = true;
				}
				if (n ==root) {
					break;//访问完成
				}
				n = n->parent;//回溯
			}
		}
}
	//遍历数据处理
	virtual void dataProcessing(T& d) {
		std::cout << d<<" ";
	}
};


/*
中序遍历
思路：左-中-右，先往左孩子找到最小值，然后不停地找到线性结构中的后继位置，即利用后继函数遍历整个树，表现为逻辑上的顺序排序（小到大）
*/
template<typename T>struct InorderTraversal
{
	virtual void operator()(BTN::BinTreeNode<T>*n) {
		while (n->hasLeftChild())
		{
			n = n->left;//往左遍历
			}
		while (n)
		{
			dataProcessing(n->data);
			n = n->succeed();//找后继位置
		}
	}
	//遍历数据处理
	virtual void dataProcessing(T& d) {
		std::cout << d << " ";
	}
};



/*
后序遍历
思路：左-右-中，用2个bool追踪标记是否访问了左右孩子，如果都已访问则回溯到最近的真祖先节点，其实与先序、中序遍历一样需要遍历整根树，只是数据处理时间不同
后序遍历更贴近于先序遍历，前者是访问即处理数据，这里把数据处理放在回溯时候即可完成后序遍历
*/
template<typename T>struct PostorderTraversal
{
	virtual void operator()(BTN::BinTreeNode<T>*n) {
		BTN::BinTreeNode<T>*root = n;
		bool backtrack1 = false, backtrack2 = false;//标记当前节点左右孩子是否访问完
		while (true)
		{
			if (n->hasLeftChild() && !backtrack1) {
				n = n->left;//往左遍历
				backtrack1 = false, backtrack2 = false;//未访问
			}
			else if (n->hasRightChild() && !backtrack2) {
				n = n->right;//左孩子访问完 就访问右孩子
				backtrack1 = false, backtrack2 = false;//未访问
			}
			else {
				if (n->isLeftChild()) {
					backtrack1 = true, backtrack2 = false;
				}
				else {
					backtrack1 = true, backtrack2 = true;
				}
				dataProcessing(n->data);//数据处理
				if (n == root) {
					break;//访问完成
				}
				n = n->parent;//回溯
			}
		}
	}
};


/*
层次遍历
思路：按层次遍历，先访问第0层，然后访问第1层，用队列记录n层次节点，同时把上一层的节点删除，表现为每个节点找左右孩子入队列，然后删除这个已访问的节点
*/
template<typename T>struct LevelTraversal
{
	virtual void operator()(BTN::BinTreeNode<T>*n) {
		std::queue< BTN::BinTreeNode<T>*>Q;//引入辅助队列
		Q.push(n);//根节点先入队
		while (!Q.empty())
		{
			BTN::BinTreeNode<T>*p = Q.front();//引用队头
			dataProcessing(p->data);//处理已访问的节点
			Q.pop();//删除已访问节点
			if (p->hasLeftChild()) {
				Q.push(p->left);
			}
			if (p->hasRightChild()) {
				Q.push(p->right);
			}
		}
	}
	//遍历数据处理
	virtual void dataProcessing(T& d) {
		std::cout << d << " ";
	}
};

#endif // !BINTREETRAVERSALINF_H_H