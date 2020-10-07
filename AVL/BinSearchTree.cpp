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
		std::queue<BinTreeNode<T>*>Q;//引入辅助队列
		std::queue<BinTreeNode<T>*>P;//引入辅助队列 记录新树父亲节点
		Q.push(t.m_root);//根节点先入队
		BinTreeNode<T>*r = new BinTreeNode<T>(t.m_root->data);//new树根
		this->m_root = r;
		r->m_height = t.m_root->m_height;//高度更新
		this->m_hitNodeParent = nullptr;//命中节点的父亲初始化为nullptr
		P.push(r);
		while (!Q.empty())
		{
			BinTreeNode<T>*q = Q.front();//引用队头
			BinTreeNode<T>*p = P.front();
			Q.pop();//删除已访问节点
			P.pop();//删除已访问节点

			if (t.m_hitNodeParent == q)this->m_hitNodeParent = p;//命中节点的父亲更新
			if (q->hasLeftChild()) {
				Q.push(q->left);
				BinTreeNode<T>*t = new BinTreeNode<T>(q->left->data, p);
				t->m_height = q->left->m_height;//高度更新
				p->left = t;
				P.push(t);
			}
			if (q->hasRightChild()) {
				Q.push(q->right);
				BinTreeNode<T>*t = new BinTreeNode<T>(q->right->data, p);
				t->m_height = q->right->m_height;//高度更新
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
		*tp =std::move(*static_cast<BinTree<T>*>(&t));//调用基类的赋值函数
		this->m_hitNodeParent = std::move(t.m_hitNodeParent);
		t.m_hitNodeParent = nullptr;
}

	template<typename T>
	TREE_OUTOFLINE BinSearchTree<T> & BinSearchTree<T>::operator=(BinSearchTree<T> t) &
	{
		// TODO: 在此处插入 return 语句
		BinTree<T>*tp = static_cast<BinTree<T>*>(this);
		*tp = std::move(*static_cast<BinTree<T>*>(&t));//调用基类的赋值函数
		this->m_hitNodeParent = std::move(t.m_hitNodeParent);
		t.m_hitNodeParent = nullptr;
		return *this;
	}

	template<typename T>
	TREE_OUTOFLINE BinSearchTree<T>::~BinSearchTree()
	{
	}
	//3+4统一重构结构的中序排序是T0 a T1 b T2 c T3 
	template<typename T>
	TREE_OUTOFLINE BNP(T) BinSearchTree<T>::adjust(BNP(T)a, BNP(T)b, BNP(T)c,
		BNP(T)t0, BNP(T)t1,BNP(T)t2, BNP(T)t3) {
		b->left = a; b->right = c;
		a->parent = b; c->parent = b;//0 1层关联
		a->left = t0; a->right = t1;
		c->left = t2; c->right = t3;
		if (t0)t0->parent = a; if (t1)t1->parent = a;
		if (t2)t2->parent = c; if (t3)t3->parent = c;//1 2层关联
		//更新树高
		this->updateheight(a); this->updateheight(c); this->updateheight(b);
		return b;
	}
	template<typename T>
	TREE_OUTOFLINE BNP(T) BinSearchTree<T>::rotateAt(BNP(T)v)
	{
		BNP(T)p = v->parent; BNP(T)g = p->parent;//找出 g p祖先 得到g p v
		BNP(T)&t = this->inParentNodeOf(g);//逆向更新用
		//g p v 位置有4中情况  进行分别处理即可
		if (v->isLeftChild()) {
			if (p->isLeftChild()) {//p v同向说明执行单旋操作 根据方向为右旋
				p->parent = g->parent;//新的子树逆向联接
				adjust(v,p,g,v->left,v->right,p->right,g->right);//3+4联接
				t = p;//更新树根或者在父类中的位置
				return p;
			}
			else {//zig(p)-zag(g)
				v->parent = g->parent;//新的子树逆向联接
adjust(g, v, p, g->left, v->left, v->right, p->right);//3+4联接
t = v;//更新树根或者在父类中的位置
			return v;
			}
		}
		else {
			if (p->isRightChild()) {//p v同向说明执行单旋操作 根据方向为左旋
				p->parent = g->parent;//新的子树逆向联接
				adjust(g, p, v, g->left, p->left, v->left, v->right);//3+4联接
				t = p;//更新树根或者在父类中的位置
				return p;
			}
			else {//zag(p)-zig(g)
				v->parent = g->parent;//新的子树逆向联接
adjust(p, v, g, p->left, v->left, v->right, g->right);//3+4联接
t = v;//更新树根或者在父类中的位置
				return v;
			}
		}
	}

	template<typename T>
	TREE_OUTOFLINE BNP(T) BinSearchTree<T>::search(T const& d)
	{
		BNP(T) p=this-> m_root;
		m_hitNodeParent = nullptr;//命中节点父亲初始化
		while (p)
		{
			if (d >p->data ) {
				m_hitNodeParent = p;//记录
				p = p->right;//大于就在右边
			}
			else if (d < p->data) {
				m_hitNodeParent = p;//记录
				p = p->left;
			}
			else
			{
				m_hitNodeParent = p->parent;//记录
				break;
			}
		}
		return p;
	}
	template<typename T>
	TREE_OUTOFLINE BNP(T) BinSearchTree<T>::insert(T const &d)
	{
		BNP(T) p = search(d);
		if (p) {//如果已存在，让他作为后继插入或者最后一个值为d的后继
			BNP(T)forerunner = p;
			BNP(T)parent = nullptr;//父亲节点初始化0
			bool isLeft =false;
			while (true)
			{
				if (forerunner->data == d) {
					if (forerunner->hasRightChild()) {
						forerunner = forerunner->right;//后继必然位于右边
					}else{
						parent = forerunner;//找到父节点
						isLeft = false;
						break;
					}
				}
				else {
					if(forerunner->hasLeftChild())
					forerunner = forerunner->left;//后继必在左孩子方向上
					else {
						parent = forerunner;//找到父节点
						isLeft = true;
						break;
					}
}
			}
			if (parent) {//如果p有右孩子
				++BinTree<T>::m_size;
				BNP(T)n = new BinTreeNode<T>(d, parent);//新建一个节点 指向父亲节点
				if (isLeft) {
					parent->left=n;//和当点节点建立联系
				}else parent->right = n;
				BinTree<T>::updateAncestorheight(parent);//更新高度
				return n;
			}
			else {//叶节点情况
				++BinTree<T>::m_size;
				BNP(T)n = new BinTreeNode<T>(d, p);//新建一个节点 指向父亲节点
				p->right = n;
				BinTree<T>::updateAncestorheight(p);//更新高度
				return n;
			}
		}
		else {
			++BinTree<T>::m_size; 
			p = new BinTreeNode<T>(d, this->m_hitNodeParent);
			if (this->m_hitNodeParent) {
				if (this->m_hitNodeParent->data > d)this->m_hitNodeParent->left = p;
				else this->m_hitNodeParent->right = p;//重建关系 
				BinTree<T>::updateAncestorheight(this->m_hitNodeParent);//更新高度
			}else this->m_root = p;
			return p;
		}
	}

	template<typename T>
TREE_OUTOFLINE bool BinSearchTree<T>::remove(T const &d)
	{

		BNP(T)p = search(d);//要删除的节点
		if (!p)return false;//不存在直接返回
		BNP(T)succ = nullptr;//实际被删除节点的替换者
		BNP(T)del = p;//实际被删除的节点(注意不是要删除的节点)
		if (!p->hasLeftChild()) {
			succ=  p->right;//直接更新节点为右孩子
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
			p->swap(del);//要删除的节点和后继交换数据
			BNP(T)t = del->parent;
			if (t == p) {
				t->right = succ = del->right;//特殊情况，即右孩子为后继，直接更新右孩子为右孩子的后继
			}
			else {
				t->left = succ = del->right;//一般情况，后继必然为左孩子，更新左孩子为左孩子的右孩子或者空
			}
			}
		m_hitNodeParent = del->parent;//记录实际被删除节点父亲
		if (succ) {
			succ->parent = m_hitNodeParent;//替换者的父亲为要删除节点的父亲 至此已建立了节点之间的联系
			}
		
		delete del, del = nullptr;//释放实际删除的节点
		this->m_size -= 1;//大小变化
		BinTree<T>::updateAncestorheight(m_hitNodeParent);
return true;
	}
};

#endif // ! BINSEARCHTREE_CPP_CPP