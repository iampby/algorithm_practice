#ifndef BINTREETRAVERSALINF_H_H
#define  BINTREETRAVERSALINF_H_H

#include"BinTreeNode.h"
#include<queue>

/*
�������
˼·����-��-�ң���2��bool׷�ٱ���Ƿ���������Һ��ӣ�������ѷ�������ݵ�����������Ƚڵ�
*/
template<typename T>struct PreorderTraversal
{
	virtual void operator()(BTN::BinTreeNode<T>*n) {
		BTN::BinTreeNode<T>*root = n;
		bool backtrack1 = false, backtrack2 = false;//��ǵ�ǰ�ڵ����Һ����Ƿ������
		dataProcessing(n->data);//���ݴ���
		while (true)
		{
			if (n->hasLeftChild() && !backtrack1) {
				n = n->left;//�������
				backtrack1 = false, backtrack2 = false;//δ����
				dataProcessing(n->data);//���ݴ���
			}
			else if (n->hasRightChild() && !backtrack2) {
				n = n->right;//���ӷ����� �ͷ����Һ���
				backtrack1 = false, backtrack2 = false;//δ����
				dataProcessing(n->data);//���ݴ���
			}
			else {
				if (n->isLeftChild()) {
					backtrack1 = true, backtrack2 = false;
				}
				else {
					backtrack1 = true, backtrack2 = true;
				}
				if (n ==root) {
					break;//�������
				}
				n = n->parent;//����
			}
		}
}
	//�������ݴ���
	virtual void dataProcessing(T& d) {
		std::cout << d<<" ";
	}
};


/*
�������
˼·����-��-�ң����������ҵ���Сֵ��Ȼ��ͣ���ҵ����Խṹ�еĺ��λ�ã������ú�̺�������������������Ϊ�߼��ϵ�˳������С����
*/
template<typename T>struct InorderTraversal
{
	virtual void operator()(BTN::BinTreeNode<T>*n) {
		while (n->hasLeftChild())
		{
			n = n->left;//�������
			}
		while (n)
		{
			dataProcessing(n->data);
			n = n->succeed();//�Һ��λ��
		}
	}
	//�������ݴ���
	virtual void dataProcessing(T& d) {
		std::cout << d << " ";
	}
};



/*
�������
˼·����-��-�У���2��bool׷�ٱ���Ƿ���������Һ��ӣ�������ѷ�������ݵ�����������Ƚڵ㣬��ʵ�������������һ����Ҫ������������ֻ�����ݴ���ʱ�䲻ͬ
������������������������ǰ���Ƿ��ʼ��������ݣ���������ݴ�����ڻ���ʱ�򼴿���ɺ������
*/
template<typename T>struct PostorderTraversal
{
	virtual void operator()(BTN::BinTreeNode<T>*n) {
		BTN::BinTreeNode<T>*root = n;
		bool backtrack1 = false, backtrack2 = false;//��ǵ�ǰ�ڵ����Һ����Ƿ������
		while (true)
		{
			if (n->hasLeftChild() && !backtrack1) {
				n = n->left;//�������
				backtrack1 = false, backtrack2 = false;//δ����
			}
			else if (n->hasRightChild() && !backtrack2) {
				n = n->right;//���ӷ����� �ͷ����Һ���
				backtrack1 = false, backtrack2 = false;//δ����
			}
			else {
				if (n->isLeftChild()) {
					backtrack1 = true, backtrack2 = false;
				}
				else {
					backtrack1 = true, backtrack2 = true;
				}
				dataProcessing(n->data);//���ݴ���
				if (n == root) {
					break;//�������
				}
				n = n->parent;//����
			}
		}
	}
};


/*
��α���
˼·������α������ȷ��ʵ�0�㣬Ȼ����ʵ�1�㣬�ö��м�¼n��νڵ㣬ͬʱ����һ��Ľڵ�ɾ��������Ϊÿ���ڵ������Һ�������У�Ȼ��ɾ������ѷ��ʵĽڵ�
*/
template<typename T>struct LevelTraversal
{
	virtual void operator()(BTN::BinTreeNode<T>*n) {
		std::queue< BTN::BinTreeNode<T>*>Q;//���븨������
		Q.push(n);//���ڵ������
		while (!Q.empty())
		{
			BTN::BinTreeNode<T>*p = Q.front();//���ö�ͷ
			dataProcessing(p->data);//�����ѷ��ʵĽڵ�
			Q.pop();//ɾ���ѷ��ʽڵ�
			if (p->hasLeftChild()) {
				Q.push(p->left);
			}
			if (p->hasRightChild()) {
				Q.push(p->right);
			}
		}
	}
	//�������ݴ���
	virtual void dataProcessing(T& d) {
		std::cout << d << " ";
	}
};

#endif // !BINTREETRAVERSALINF_H_H