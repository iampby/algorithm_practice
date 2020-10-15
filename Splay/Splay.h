#ifndef SPLAY_H_H
#define SPLAY_H_H
#include"BinSearchTree.h"
//注：伸展树不需要维护高度，可以重构去掉高度相关
namespace ST {
	using namespace BST;
	template<typename T>
	class Splay :public BinSearchTree<T> 
	{
public:
	//定义插入方式枚举
	typedef enum {
		InsertByBSTInsert=1,
		InsertBySearch
	}InsertWay;
	Splay() = default;
	Splay(Splay<T> const&);
	Splay(Splay<T> &&)TREE_NOTHROW;
	Splay&operator=(Splay<T>)&;//左值赋值函数
	BNP(T) searchLast(T const&); // 每次访问 不管找不找到 都把最后一次访问伸展到根, 如有相同值，优先获取底层的节点
		//插入节点，并把节点伸展到树根,如果有相同值 往右方向插入 参数2 指定插入方式，1 先BST插入后伸展 2 先搜索后分离调整 default
	BNP(T) insert(T const&, InsertWay);
//基本接口，要求所有派生类实现各自功能
		virtual BNP(T) search(T const&)override;//每次访问 不管找不找到 都把最后一次访问伸展到根,如有相同值，优先获取上层的节点
		virtual bool remove(T const &)override;//通过访问伸展后移除根节点，拆分为2棵树 再次访问一棵树 这里访问右子树 导致根节点为后继
	protected:
		virtual BNP(T) insert(T const&)override;//插入方式2 先搜索后分离调整
		protected:
BNP(T) splay(BNP(T));//逐层伸展 返回新的树根
		BNP(T) insertByInsert(T const&);//插入方式1 先BST插入后伸展
	private:
		void attachAsLeft(BNP(T), BNP(T));//1参数和2参数建立父子关系，2参数可以为空
		void attachAsRight(BNP(T), BNP(T));//1参数和2参数建立父子关系，2参数可以为空
		
	};

	template<typename T>
	TREE_OUTOFLINE Splay<T>::Splay(Splay<T> const &t)
	{
		BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
		*tp = *static_cast<BinSearchTree<T>*>(const_cast<Splay<T>*>(&t));//调用基类的拷贝赋值
	}
	template<typename T>
	TREE_OUTOFLINE Splay<T>::Splay(Splay<T>&&t)TREE_NOTHROW
	{
		BinSearchTree<T>*tp= static_cast<BinSearchTree<T>*>(this);
		*tp = std::move(*static_cast<BinSearchTree<T>*>(&t));//调用基类的移动赋值
	}

	template<typename T>
	inline Splay<T> & Splay<T>::operator=(Splay<T> t) &
	{
		// TODO: 在此处插入 return 语句
		BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
		*tp = std::move(*static_cast<BinSearchTree<T>*>(&t));//调用基类的赋值函数
return *this;
	}


template<typename T>
	TREE_OUTOFLINE BNP(T) Splay<T>::search(T const &d)
	{
		BNP(T)p=  BinSearchTree<T>::search(d);
		this->m_root = splay(p ? p : this->m_hitNodeParent);
		return this->m_root;
	}
	
	template<typename T>
	TREE_OUTOFLINE  BNP(T) Splay<T>::insert(T const &d, InsertWay way)
	{
		switch (way)
		{
		case InsertWay::InsertByBSTInsert: {
			return insertByInsert(d);
			}
		case InsertWay::InsertBySearch:
			return  insert(d);
}
			return nullptr;
	}

	template<typename T>
	TREE_OUTOFLINE BNP(T) Splay<T>::insert(T const &d)
	{
		if (!this -> m_root)return ++this->m_size, this->m_root = new BinTreeNode<T>(d);//处理空树退化情况
		searchLast(d);//如有相同值 插入到最后一个后面
		BNP(T)p = this->m_root;
		BNP(T)n = new BinTreeNode<T>(d);//新建节点
		if (d < p->data) {
			attachAsLeft(n, p->left);
			attachAsRight(n, p);
			p->left = nullptr;;//更新p的左孩子
		}
		else {
			attachAsLeft(n,p);
			attachAsRight(n, p->right);
			p->right = nullptr;//更新p的右孩子
		}
		this->m_root = n;
		this->updateAncestorheight(p);
		++this->m_size;
		return this->m_root;
	}
	template<typename T>
	TREE_OUTOFLINE BNP(T) Splay<T>::insertByInsert(T const &d)
	{
		//BNP(T)p= BinSearchTree<T>::insert(d);为了多态性，这里重写一遍BST插入
		BNP(T) p = BinSearchTree<T>::search(d);
		if (p) {//如果已存在，让他作为后继插入或者最后一个值为d的后继
			BNP(T)forerunner = p;
			BNP(T)parent = nullptr;//父亲节点初始化0
			bool isLeft = false;
			while (true)
			{
				if (forerunner->data == d) {
					if (forerunner->hasRightChild()) {
						forerunner = forerunner->right;//后继必然位于右边
					}
					else {
						parent = forerunner;//找到父节点
						isLeft = false;
						break;
					}
				}
				else {
					if (forerunner->hasLeftChild())
						forerunner = forerunner->left;//后继必在左孩子方向上
					else {
						parent = forerunner;//找到父节点
						isLeft = true;
						break;
					}
				}
			}
			++BinTree<T>::m_size;
			BNP(T)n = new BinTreeNode<T>(d, parent);//新建一个节点 指向父亲节点
			if (isLeft) {
				parent->left = n;//和当点节点建立联系
			}
			else parent->right = n;
			this->updateAncestorheight(parent);//更新高度
			p = n;//记录新节点
		}
		else {
			++BinTree<T>::m_size;
			p = new BinTreeNode<T>(d, this->m_hitNodeParent);
			if (this->m_hitNodeParent) {
				if (this->m_hitNodeParent->data > d)this->m_hitNodeParent->left = p;
				else this->m_hitNodeParent->right = p;//重建关系 
				this->updateAncestorheight(this->m_hitNodeParent);//更新高度
			}
			else this->m_root = p;
		}
		this->m_root=splay(p);//逐层伸展到树根
		return this->m_root;
	}

	template<typename T>
	TREE_OUTOFLINE bool Splay<T>::remove(T const &d)
	{
		if (!this->m_root|| search(d)->data != d)return false;
		BNP(T)p= this->m_root;//要删除的节点
		if (!p->hasLeftChild()) {
			this->m_root = p->right; if (this->m_root)this->m_root->parent = nullptr;
		}
		else if(!p->hasRightChild()){
			this->m_root = p->left; this->m_root->parent = nullptr;
		}
		else {//分割2个子树，访问右子树在合并树这样得到以后继为根的新树
			BNP(T)lc = p->left; BNP(T) rc = p->right;
			p->left = nullptr; p->right = nullptr;
			lc->parent = nullptr; rc->parent = nullptr;//分割完成
			this->m_root = rc;//树根为右孩子
			this->search(p->data);//使后继成为树根
			//复位分割的子树
			BNP(T)t = this->m_root;
			//由于相同值存在 右子树可能不是单调的 ，把左子树和右子树的左子树合并再接入
			if (t->left) {
				while (t->hasLeftChild())
				{
					t = t->left;
				}
			}
				t->left = lc; lc->parent = t;
			}
		delete p, p = nullptr;//释放节点
		--this->m_size;//规模减1
		if(this->m_root)
		this->updateHeight(this->m_root);//只需更新树根
		return true;
	}

	
	template<typename T>
	TREE_OUTOFLINE  BNP(T) Splay<T>::searchLast(T const &d)
	{
		BNP(T)p = BinSearchTree<T>::search(d);
		if (p) {//如果已存在，尝试找后继
			BNP(T)forerunner = p;
			while (true)
			{
				if (forerunner->data == d) {
					p = forerunner;//记录目标节点
					if (forerunner->hasRightChild()) {
						forerunner = forerunner->right;//后继必然位于右边
					}
					else {
						//确定目标节点
						this->m_hitNodeParent = p->parent;//确定命中节点的父亲
						break;
					}
				}
				else {
					if (forerunner->hasLeftChild())
						forerunner = forerunner->left;//后继必在左孩子方向上
					else {
						this->m_hitNodeParent = p->parent;//确定命中节点的父亲
						break;//不是相等值后继，结束
					}
				}
			}
		}
		this->m_root = splay(p ? p : this->m_hitNodeParent);//伸展节点
		return this->m_root;
	}
	template<typename T>
	TREE_OUTOFLINE BNP(T) Splay<T>::splay(BNP(T)v)
	{
		if (!v)return nullptr; BNP(T)p,*g;//声明v父亲和祖父
		while ((p=v->parent)&&(g=p->parent))
		{
			BNP(T)gg = g->parent;
			//g p v 位置有4中情况  进行分别处理即可 目的是让v为旋转结果的根 注：对于pv方向不一致的按照avl树进行双旋即可,方向一致的对当前子树根进行旋转，这与avl双旋不一样
			if (v->isLeftChild()) {
				if (p->isLeftChild()) {//zig(g)-zig(p) 结果 v->p->g右方向
					attachAsLeft(g, p->right);//g子树第三层完成重构
					attachAsLeft(p, v->right); attachAsRight(p, g);//第二层完成重构
					attachAsRight(v, p);//g子树第一层完成重构
				}
				else {//zig(p)-zag(g)
					this->adjust(g, v, p, g->left, v->left, v->right, p->right);//3+4联接
					}
			}
			else {
				if (p->isRightChild()) {//zag(g)-zag(p) 结果 v->p->g 左方向
					attachAsRight(g, p->left);//g子树第三层完成重构
					attachAsRight(p, v->left); attachAsLeft(p, g);//第二层完成重构
					attachAsLeft(v, p);//g子树第一层完成重构
				}
				else {//zag(p)-zig(g)
					this->adjust(p, v, g, p->left, v->left, v->right, g->right);//3+4联接
					}
			}
			if (!gg) {
				v->parent =gg;
		}else if (g==gg->left)attachAsLeft(gg,v); //向下联接或更新树根
			else attachAsRight(gg,v);
			this->updateHeight(g); this->updateHeight(p); this->updateHeight(v);//更新高度 自底向上
		}
		//双层伸展结束 g为空，p可能不为空,这时对p补一次单旋,以达到目的
		if (p) {
			if (v->isLeftChild()) {
				attachAsLeft(p, v->right);//第一层完成重构
				attachAsRight(v, p);//第零层完成
			}
			else {
				attachAsRight(p, v->left);//第一层完成重构
				attachAsLeft(v, p);//第零层完成
			}
			v->parent = nullptr;
			}
	return v;
	}
	template<typename T>
	TREE_OUTOFLINE void Splay<T>::attachAsLeft(BNP(T) p, BNP(T)lc)
	{
		p->left = lc; if (lc)lc->parent = p;
	}
	template<typename T>
	TREE_OUTOFLINE void Splay<T>::attachAsRight(BNP(T)p, BNP(T)rc)
	{
		p->right = rc; if (rc)rc->parent = p;
	}
}

#endif // !SPLAY_H_H