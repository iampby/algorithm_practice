#ifndef BINSEARCHTREE_CPP_CPP
#define BINSEARCHTREE_CPP_CPP

#include"BinSearchTree.h"
namespace BST{
template<typename T>
	TREE_OUTOFLINE BinSearchTree<T>::BinSearchTree():
		m_hitNodeParent(nullptr)
	{
}
	template<typename T>
	TREE_OUTOFLINE BinSearchTree<T>::BinSearchTree(BinSearchTree<T> const &t)
	{
		std::queue<BinTreeNode<T>*>Q;//���븨������
		std::queue<BinTreeNode<T>*>P;//���븨������ ��¼�������׽ڵ�
		Q.push(t.m_root);//���ڵ������
		BinTreeNode<T>*r = new BinTreeNode<T>(t.m_root->data);//new����
		this->m_root = r;
		r->m_height = t.m_root->m_height;//�߶ȸ���
		this->m_hitNodeParent = nullptr;//���нڵ�ĸ��׳�ʼ��Ϊnullptr
		P.push(r);
		while (!Q.empty())
		{
			BinTreeNode<T>*q = Q.front();//���ö�ͷ
			BinTreeNode<T>*p = P.front();
			Q.pop();//ɾ���ѷ��ʽڵ�
			P.pop();//ɾ���ѷ��ʽڵ�

			if (t.m_hitNodeParent == q)this->m_hitNodeParent = p;//���нڵ�ĸ��׸���
			if (q->hasLeftChild()) {
				Q.push(q->left);
				BinTreeNode<T>*t = new BinTreeNode<T>(q->left->data, p);
				t->m_height = q->left->m_height;//�߶ȸ���
				p->left = t;
				P.push(t);
			}
			if (q->hasRightChild()) {
				Q.push(q->right);
				BinTreeNode<T>*t = new BinTreeNode<T>(q->right->data, p);
				t->m_height = q->right->m_height;//�߶ȸ���
				p->right = t;
				P.push(t);
			}
		}
		this->m_size = t.m_size;
	}

	template<typename T>
	TREE_OUTOFLINE BinSearchTree<T>::BinSearchTree(BinSearchTree<T>&&t)TREE_NOTHROW
	{
		BinTree<T>*tp = static_cast<BinTree<T>*>(this);
		*tp =std::move(*static_cast<BinTree<T>*>(&t));//���û���ĸ�ֵ����
		this->m_hitNodeParent = std::move(t.m_hitNodeParent);
		t.m_hitNodeParent = nullptr;
}

	template<typename T>
	TREE_OUTOFLINE BinSearchTree<T> & BinSearchTree<T>::operator=(BinSearchTree<T> t) &
	{
		// TODO: �ڴ˴����� return ���
		BinTree<T>*tp = static_cast<BinTree<T>*>(this);
		*tp = std::move(*static_cast<BinTree<T>*>(&t));//���û���ĸ�ֵ����
		this->m_hitNodeParent = std::move(t.m_hitNodeParent);
		t.m_hitNodeParent = nullptr;
		return *this;
	}

	template<typename T>
	TREE_OUTOFLINE BinSearchTree<T>::~BinSearchTree()
	{
	}
	//3+4ͳһ�ع��ṹ������������T0 a T1 b T2 c T3 
	template<typename T>
	TREE_OUTOFLINE BNP(T) BinSearchTree<T>::adjust(BNP(T)a, BNP(T)b, BNP(T)c,
		BNP(T)t0, BNP(T)t1,BNP(T)t2, BNP(T)t3) {
		b->left = a; b->right = c;
		a->parent = b; c->parent = b;//0 1�����
		a->left = t0; a->right = t1;
		c->left = t2; c->right = t3;
		if (t0)t0->parent = a; if (t1)t1->parent = a;
		if (t2)t2->parent = c; if (t3)t3->parent = c;//1 2�����
		//��������
		this->updateheight(a); this->updateheight(c); this->updateheight(b);
		return b;
	}
	template<typename T>
	TREE_OUTOFLINE BNP(T) BinSearchTree<T>::rotateAt(BNP(T)v)
	{
		BNP(T)p = v->parent; BNP(T)g = p->parent;//�ҳ� g p���� �õ�g p v
		BNP(T)&t = this->inParentNodeOf(g);//���������
		//g p v λ����4�����  ���зֱ�����
		if (v->isLeftChild()) {
			if (p->isLeftChild()) {//p vͬ��˵��ִ�е������� ���ݷ���Ϊ����
				p->parent = g->parent;//�µ�������������
				adjust(v,p,g,v->left,v->right,p->right,g->right);//3+4����
				t = p;//�������������ڸ����е�λ��
				return p;
			}
			else {//zig(p)-zag(g)
				v->parent = g->parent;//�µ�������������
adjust(g, v, p, g->left, v->left, v->right, p->right);//3+4����
t = v;//�������������ڸ����е�λ��
			return v;
			}
		}
		else {
			if (p->isRightChild()) {//p vͬ��˵��ִ�е������� ���ݷ���Ϊ����
				p->parent = g->parent;//�µ�������������
				adjust(g, p, v, g->left, p->left, v->left, v->right);//3+4����
				t = p;//�������������ڸ����е�λ��
				return p;
			}
			else {//zag(p)-zig(g)
				v->parent = g->parent;//�µ�������������
adjust(p, v, g, p->left, v->left, v->right, g->right);//3+4����
t = v;//�������������ڸ����е�λ��
				return v;
			}
		}
	}

	template<typename T>
	TREE_OUTOFLINE BNP(T) BinSearchTree<T>::search(T const& d)
	{
		BNP(T) p=this-> m_root;
		m_hitNodeParent = nullptr;//���нڵ㸸�׳�ʼ��
		while (p)
		{
			if (d >p->data ) {
				m_hitNodeParent = p;//��¼
				p = p->right;//���ھ����ұ�
			}
			else if (d < p->data) {
				m_hitNodeParent = p;//��¼
				p = p->left;
			}
			else
			{
				m_hitNodeParent = p->parent;//��¼
				break;
			}
		}
		return p;
	}
	template<typename T>
	TREE_OUTOFLINE BNP(T) BinSearchTree<T>::insert(T const &d)
	{
		BNP(T) p = search(d);
		if (p) {//����Ѵ��ڣ�������Ϊ��̲���������һ��ֵΪd�ĺ��
			BNP(T)forerunner = p;
			BNP(T)parent = nullptr;//���׽ڵ��ʼ��0
			bool isLeft =false;
			while (true)
			{
				if (forerunner->data == d) {
					if (forerunner->hasRightChild()) {
						forerunner = forerunner->right;//��̱�Ȼλ���ұ�
					}else{
						parent = forerunner;//�ҵ����ڵ�
						isLeft = false;
						break;
					}
				}
				else {
					if(forerunner->hasLeftChild())
					forerunner = forerunner->left;//��̱������ӷ�����
					else {
						parent = forerunner;//�ҵ����ڵ�
						isLeft = true;
						break;
					}
}
			}
			if (parent) {//���p���Һ���
				++BinTree<T>::m_size;
				BNP(T)n = new BinTreeNode<T>(d, parent);//�½�һ���ڵ� ָ���׽ڵ�
				if (isLeft) {
					parent->left=n;//�͵���ڵ㽨����ϵ
				}else parent->right = n;
				BinTree<T>::updateAncestorheight(parent);//���¸߶�
				return n;
			}
			else {//Ҷ�ڵ����
				++BinTree<T>::m_size;
				BNP(T)n = new BinTreeNode<T>(d, p);//�½�һ���ڵ� ָ���׽ڵ�
				p->right = n;
				BinTree<T>::updateAncestorheight(p);//���¸߶�
				return n;
			}
		}
		else {
			++BinTree<T>::m_size; 
			p = new BinTreeNode<T>(d, this->m_hitNodeParent);
			if (this->m_hitNodeParent) {
				if (this->m_hitNodeParent->data > d)this->m_hitNodeParent->left = p;
				else this->m_hitNodeParent->right = p;//�ؽ���ϵ 
				BinTree<T>::updateAncestorheight(this->m_hitNodeParent);//���¸߶�
			}else this->m_root = p;
			return p;
		}
	}

	template<typename T>
TREE_OUTOFLINE bool BinSearchTree<T>::remove(T const &d)
	{

		BNP(T)p = search(d);//Ҫɾ���Ľڵ�
		if (!p)return false;//������ֱ�ӷ���
		BNP(T)succ = nullptr;//ʵ�ʱ�ɾ���ڵ���滻��
		BNP(T)del = p;//ʵ�ʱ�ɾ���Ľڵ�(ע�ⲻ��Ҫɾ���Ľڵ�)
		if (!p->hasLeftChild()) {
			succ=  p->right;//ֱ�Ӹ��½ڵ�Ϊ�Һ���
if (del->isLeftChild())
				del->parent->left = succ;
			else del->parent->right= succ;
		}
		else if (!p->hasRightChild()) {
			succ = p->left;
			if (del->isLeftChild())
				del->parent->left = succ;
			else del->parent->right = succ;
		}
		else {
			del = del->succeed();
			p->swap(del);//Ҫɾ���Ľڵ�ͺ�̽�������
			BNP(T)t = del->parent;
			if (t == p) {
				t->right = succ = del->right;//������������Һ���Ϊ��̣�ֱ�Ӹ����Һ���Ϊ�Һ��ӵĺ��
			}
			else {
				t->left = succ = del->right;//һ���������̱�ȻΪ���ӣ���������Ϊ���ӵ��Һ��ӻ��߿�
			}
			}
		m_hitNodeParent = del->parent;//��¼ʵ�ʱ�ɾ���ڵ㸸��
		if (succ) {
			succ->parent = m_hitNodeParent;//�滻�ߵĸ���ΪҪɾ���ڵ�ĸ��� �����ѽ����˽ڵ�֮�����ϵ
			}
		
		delete del, del = nullptr;//�ͷ�ʵ��ɾ���Ľڵ�
		this->m_size -= 1;//��С�仯
		BinTree<T>::updateAncestorheight(m_hitNodeParent);
return true;
	}
};

#endif // ! BINSEARCHTREE_CPP_CPP