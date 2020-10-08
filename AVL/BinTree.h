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
			  };//������ƽ�������Ϊֹ
	 }
	template<typename T>
	inline BinTree<T>::BinTree():
		m_size(0),m_root(nullptr)
	{

	}
	template<typename T>
	inline BinTree<T>::BinTree(BinTree<T>const &n) 
	{
		std::queue<BinTreeNode<T>*>Q;//���븨������
		std::queue<BinTreeNode<T>*>P;//���븨������ ��¼�������׽ڵ�
		Q.push(n.m_root);//���ڵ������
		BinTreeNode<T>*r = new BinTreeNode<T>(n.m_root->data);//new����
		this->m_root = r;
		r->m_height = n.m_root->m_height;//�߶ȸ���
		P.push(r);
		while (!Q.empty())
		{
			BinTreeNode<T>*q = Q.front();//���ö�ͷ
			BinTreeNode<T>*p = P.front();
			Q.pop();//ɾ���ѷ��ʽڵ�
			P.pop();//ɾ���ѷ��ʽڵ�
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
		this->m_size = n.m_size;
	}
	template<typename T>
	inline BinTree<T>::BinTree(BinTree<T> &&t)TREE_NOEXCEPT
	{
		this->m_size =std::move(t.m_size);//
		this->m_root =std::move(t.m_root);
		t.m_root = nullptr; t.m_size = -1;//���Ϊʧ��
	}
	template<typename T>
	inline BinTree<T> & BinTree<T>::operator=(BinTree<T> t)& 
	{
		// TODO: �ڴ˴����� return ���
		this->m_root =std::move( t.m_root); this->m_size = std::move(t.m_size);//��������
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
			m_root->parent = nullptr;//��ϵ�ڵ�
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
			  n->left->parent = n;//����
			  m_size += t->m_size; updateAncestorheight(n);
			  t->m_root = nullptr; 
			  delete t, t = nullptr;
			  return n;
		  }
		  template<typename T>
		  inline BNP(T) BinTree<T>::attachAsRight(BNP(T) n, BinTree<T>*& t)
		  {
			  n->right = t->m_root;
			  n->right->parent = n;//����
			  m_size += t->m_size; updateAncestorheight(n);
			  t->m_root = nullptr;
			  delete t, t = nullptr;
			  return n;
		  }
		  template<typename T>
		  inline  int BinTree<T>::remove(BNP(T) n)
		  {
			  inParentNodeOf(n) = nullptr;//����ָ����߸��ڵ����
			  updateAncestorheight(n->parent);
			  int count = removeAt(n); m_size -= count;
			  return count;
		  }
		 template<typename T>
		 inline  BinTree<T>* BinTree<T>::secede(BNP(T) n)
		 {
			 inParentNodeOf(n) = nullptr;//�жϵ�ǰ����n�ڵ���ϵ
			  updateAncestorheight(n->parent);//���µ�ǰ���߶�
			  n->parent = nullptr;//�ж�������ϵ
			  BinTree<T>* nt = new  BinTree<T>;
			  nt->m_root = n;//��������
			  nt->m_size = n->size();
			  m_size -= nt->size();
			 return nt;
		 }

		 template<typename T>
		 inline BNP(T)&  BinTree<T>::inParentNodeOf(BNP(T)n)
		 {
			 // TODO: �ڴ˴����� return ���
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
			   bool backtrack1 = false, backtrack2 = false;//������������Ƿ��Ѿ�����
			   int sum = 0;
			   while (true)
			   {
				   if (p->left && !backtrack1) {
					   p = p->left;
					   backtrack1 = false;//���Ϊδ����
					   backtrack2 = false;
				   }
				   else if (p->right && !backtrack2) {
					   p = p->right;
					   backtrack1 = false;//���Ϊδ����
					   backtrack2 = false;
				   }
				   else {
					   if (p->isLeftChild()) {
						   backtrack1 = true;//���Ϊ�ѷ���
						   backtrack2 = false;//�Һ��ӿ��Է���
					   }
					   else {
						   backtrack1 = true;//���Ϊ�ѷ���
						   backtrack2 = true;
					   }
					   BNP(T)temp = p;
					   p = p->parent;//�ڵ��������ƶ�
					  if (p == n->parent) {
						  delete temp, temp = nullptr;
						  ++sum;
						   break;//�������
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
