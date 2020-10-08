#ifndef BINTREE_H_H
#define BINTREE_H_H

#include "BinTree.cpp"
#include<algorithm>
namespace BT {
	template<typename T>
	inline  int BinTree<T>::updateHeight(BNP(T) n)
	{
return n->m_height=1+std::max(Stature(n->left),Stature(n->right));
	}
	 template<typename T>
	 inline void BinTree<T>::updateAncestorheight(BNP(T) n)
	 {
		 while (n&&n->m_height != 1 + __max(Stature(n->left), Stature(n->right))) {
			 BinTree<T>::updateHeight(n); n = n->parent;
			  };//纠正到平衡或树根为止
	 }
	template<typename T>
	inline BinTree<T>::BinTree():
		m_size(0),m_root(nullptr)
	{

	}
	template<typename T>
	inline BinTree<T>::BinTree(BinTree<T>const &n) 
	{
		std::queue<BinTreeNode<T>*>Q;//引入辅助队列
		std::queue<BinTreeNode<T>*>P;//引入辅助队列 记录新树父亲节点
		Q.push(n.m_root);//根节点先入队
		BinTreeNode<T>*r = new BinTreeNode<T>(n.m_root->data);//new树根
		this->m_root = r;
		r->m_height = n.m_root->m_height;//高度更新
		P.push(r);
		while (!Q.empty())
		{
			BinTreeNode<T>*q = Q.front();//引用队头
			BinTreeNode<T>*p = P.front();
			Q.pop();//删除已访问节点
			P.pop();//删除已访问节点
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
		this->m_size = n.m_size;
	}
	template<typename T>
	inline BinTree<T>::BinTree(BinTree<T> &&t)TREE_NOEXCEPT
	{
		this->m_size =std::move(t.m_size);//
		this->m_root =std::move(t.m_root);
		t.m_root = nullptr; t.m_size = -1;//标记为失常
	}
	template<typename T>
	inline BinTree<T> & BinTree<T>::operator=(BinTree<T> t)& 
	{
		// TODO: 在此处插入 return 语句
		this->m_root =std::move( t.m_root); this->m_size = std::move(t.m_size);//交换数据
		t.m_root = nullptr; t.m_size = -1;
		return *this;
	}
	template<typename T>
	inline  BinTree<T>::~BinTree()
	{
		 if (m_size > 0)remove(m_root);
	}
	 template<typename T>
	 inline int BinTree<T>::size() const
	 {
		 return m_size;
	 }
	 template<typename T>
	 inline  bool BinTree<T>::empty() const
	 {
		 return (!m_root);
	 }
	  template<typename T>
	  inline  BNP(T) BinTree<T>::root() const
	  {
		  return m_root;
	  }
	   template<typename T>
	   inline  BNP(T) BinTree<T>::insertAsRoot(T const &d)
	   {
			m_size = 1;
			m_root = new BinTreeNode<T>(d);
			m_root->parent = nullptr;//联系节点
		   return m_root;
	   }
		template<typename T>
		inline  BNP(T) BinTree<T>::insertAsLeft(BNP(T) n, T const & d)
		{
			 ++m_size;
			 n->insertAsLeft(d);
			 updateAncestorheight(n);
			return n->left;
		}
		 template<typename T>
		 inline  BNP(T) BinTree<T>::insertAsRight(BNP(T) n, T const & d)
		 {
			  ++m_size;
			  n->insertAsRight(d);
			  updateAncestorheight(n);
			  return n->right;
			 }
		  template<typename T>
		  inline   BNP(T) BinTree<T>::attachAsLeft(BNP(T) n, BinTree<T>*& t)
		  {
			  n->left = t->m_root;
			  n->left->parent = n;//接入
			  m_size += t->m_size; updateAncestorheight(n);
			  t->m_root = nullptr; 
			  delete t, t = nullptr;
			  return n;
		  }
		  template<typename T>
		  inline BNP(T) BinTree<T>::attachAsRight(BNP(T) n, BinTree<T>*& t)
		  {
			  n->right = t->m_root;
			  n->right->parent = n;//接入
			  m_size += t->m_size; updateAncestorheight(n);
			  t->m_root = nullptr;
			  delete t, t = nullptr;
			  return n;
		  }
		  template<typename T>
		  inline  int BinTree<T>::remove(BNP(T) n)
		  {
			  inParentNodeOf(n) = nullptr;//父类指向或者根节点归零
			  updateAncestorheight(n->parent);
			  int count = removeAt(n); m_size -= count;
			  return count;
		  }
		 template<typename T>
		 inline  BinTree<T>* BinTree<T>::secede(BNP(T) n)
		 {
			 inParentNodeOf(n) = nullptr;//切断当前树与n节点联系
			  updateAncestorheight(n->parent);//更新当前树高度
			  n->parent = nullptr;//切断树间联系
			  BinTree<T>* nt = new  BinTree<T>;
			  nt->m_root = n;//新树树根
			  nt->m_size = n->size();
			  m_size -= nt->size();
			 return nt;
		 }

		 template<typename T>
		 inline BNP(T)&  BinTree<T>::inParentNodeOf(BNP(T)n)
		 {
			 // TODO: 在此处插入 return 语句
			 BNP(T)&p = n->inParentNodeOf();
			 return  (p?p:m_root);
		 }
	
		  template<typename T>
		  template<typename VST>
		  inline  void BinTree<T>::levelTraversal(VST visist)
		  {
			  if (m_root)visist(m_root);
		  }
		  template<typename T>
		  template<typename VST>
		  void BinTree<T>::preorderTraversal(VST visist)
		  {
			  if (m_root)visist(m_root);
		  }
		  template<typename T>
		  template<typename VST>
		  inline   void BinTree<T>::inorderTraversal(VST visist)
		  {
			   if (m_root)visist(m_root);
		  }
		   template<typename T>
		   template<typename VST>
		   inline   void BinTree<T>::postorderTraversal(VST visist)
		   {
				if (m_root)visist(m_root);
		   }
		 template<typename T>
		 inline   bool BinTree<T>::operator<(BinTree<T> const & t)
		 {
			 return  m_root&&t.m_root&&std::max(m_root->data,t.m_root->data);
		 }
		 template<typename T>
		 inline  bool BinTree<T>::operator>(BinTree<T> const & t)
		 {
			 return  m_root && t.m_root&&(m_root->data>t.m_root->data);
		 }
		 template<typename T>
		 inline  bool BinTree<T>::operator==(BinTree<T> const & t)
		 {
			 return  m_root && t.m_root && (m_root->data == t.m_root->data);
		 }
		 template<typename T>
		 inline bool BinTree<T>::operator!=(BinTree<T> const & t)
		 {
			 return  m_root && t.m_root && (m_root->data != t.m_root->data);
		 }
		  template<typename T>
		  inline   int BinTree<T>::removeAt(BNP(T) n)
		  {
			   BNP(T)p = n;
			   bool backtrack1 = false, backtrack2 = false;//标记左右子树是否已经访问
			   int sum = 0;
			   while (true)
			   {
				   if (p->left && !backtrack1) {
					   p = p->left;
					   backtrack1 = false;//标记为未访问
					   backtrack2 = false;
				   }
				   else if (p->right && !backtrack2) {
					   p = p->right;
					   backtrack1 = false;//标记为未访问
					   backtrack2 = false;
				   }
				   else {
					   if (p->isLeftChild()) {
						   backtrack1 = true;//标记为已访问
						   backtrack2 = false;//右孩子可以访问
					   }
					   else {
						   backtrack1 = true;//标记为已访问
						   backtrack2 = true;
					   }
					   BNP(T)temp = p;
					   p = p->parent;//节点向树根移动
					  if (p == n->parent) {
						  delete temp, temp = nullptr;
						  ++sum;
						   break;//计数完成
					  }
					  else {
						  delete temp, temp = nullptr;
						  ++sum;
					  }
				   }
			   }
			   return sum;
		  }
}
#endif // !BINTREE_H_H
