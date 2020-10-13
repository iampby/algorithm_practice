#ifndef BINTREENODE_H_H
#define BINTREENODE_H_H

#include "BinTreeNode.cpp"
#include<stack>
#include<iostream>
namespace BTN {
	template<typename T>
	inline BinTreeNode<T>::BinTreeNode(BinTreeNode<T> &n)
	{
		this->data = n.data; this->m_height = n.m_height;
		this->left = n.left; this->right = n.right; this->parent = n.parent;
	}
	template<typename T>
	inline BinTreeNode<T>::BinTreeNode(BinTreeNode<T>const &n)
	{
		this->data = n.data; this->m_height = n.m_height;
		this->left = n.left; this->right = n.right; this->parent = n.parent;
	}
	template<typename T>
	inline void BinTreeNode<T>::swap(BNP(T) n)
	{
		T d = this->data; int h = this->m_height;
		this->data = n->data; this->m_height = n->m_height;
		n->data = d; n->m_height = h;
	}

	template<typename T>
	inline BinTreeNode<T>::BinTreeNode():
		parent(nullptr),left(nullptr),right(nullptr),m_height(0)
	{
	}

	template<typename T>
	inline BinTreeNode<T> & BinTreeNode<T>::operator=(BinTreeNode<T> const &n)& 
	{
		// TODO: 在此处插入 return 语句
		this->data = n.data; this->m_height = n.m_height;
		this->parent = n.parent; this->left = n.left; this->right = n.right;
		return *this;
	}

	template<typename T>
	inline BinTreeNode<T>::BinTreeNode(T d, BNP(T) p, BNP(T) l, BNP(T) r,int h):
		data(d),parent(p),left(l),right(r),m_height(h)
	{
	}
//这里不要去重置在父亲和后代中的状态
	template<typename T>
	inline BinTreeNode<T>::~BinTreeNode()
	{
	}
	template<typename T>
	inline  int BinTreeNode<T>::size()
	{
		 int sum = 1;
		 BNP(T)p = this;
		 bool backtrack1=false, backtrack2 = false;//标记左右子树是否已经访问
		
		 while (true)
		 {
			if (p->left&&!backtrack1) {
				 p = p->left;
				 ++sum;//计数加1
				 backtrack1 = false;//标记为未访问
				 backtrack2 =false;
					 }
			 else if (p->right&&!backtrack2) {
				 p = p->right;
				 ++sum;//计数加1
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
				if (p == this) {
					break;//计数完成
				}
				p = p->parent;//节点向树根移动
				}
		 }
		return sum;
	}
	template<typename T>
	inline  BNP(T) BinTreeNode<T>::insertAsLeft(T const &d)
	{
		return left = new BinTreeNode(d, this);
}
	 template<typename T>
	 inline BNP(T) BinTreeNode<T>::insertAsRight(T const &d)
	 {
		 return right= new BinTreeNode(d, this);
	 }
	 template<typename T>
	 inline  BNP(T) BinTreeNode<T>::succeed()
	 {
		 BNP(T)succ = this;
		 if (right) {//有右孩子，直接后继位于右子树中
			 succ = right;
			 while (succ->hasLeftChild())
			 {
				 succ = succ->left;//找最小的左孩子否则直接后继为当前节点
			 }
		 }
		 else {
			 while (succ->isRightChild()) {
				 succ = succ->parent;
			 }
			 succ = succ->parent;//如果存在往左上方一步就是后继位置
		 }
		 return succ;
	 }
	 //由于后面树实现问题，这里不对旋转轴节点做更改，仅仅交换数据，即只换皮
	 template<typename T>
	 inline BNP(T) BinTreeNode<T>::zig()
	 {
		 BNP(T) v = this;
		 BNP(T) lChild = v->left;//c必须存在
		 BNP(T) rChild = v->right;
		 BNP(T)rl = lChild->right;
		 v->BinTreeNode<T>::swap(lChild);//先换皮也就是把v的数据和c交换
		 v->left = lChild->left;
		 v->right = lChild;
		 if(v->left)
		 v->left->parent = v;
		 v->right->parent = v;//这里已经完成c移动到v,并建立了其节点双向关系
		 v = lChild;//现在v节点视为原来的左孩子
		 v->right = rChild;
		 if(rChild)
		 rChild->parent = v;
		 v->left =rl;
		 if (rl)rl->parent = v;//这里v已经作为了右孩子，并建立了节点双向关系

		 this->right->m_height = 1 + __max(Stature(this->right->left), Stature(this->right->right));
		 m_height = 1 + __max(Stature(left), Stature(right));
		 for (BNP(T) x = parent; x; x = x->parent)
			 if ((*x).m_height == 1 + __max(Stature((*x).left), Stature((*x).right)))
				 break;
			 else
				 x->m_height = 1 + __max(Stature(x->left), Stature(x->right));
				
		 return this;
		 }
	 //由于后面树实现问题，这里不对旋转轴节点做更改，仅仅交换数据，即只换皮
	 template<typename T>
	 inline BNP(T) BinTreeNode<T>::zag()
	 {
		 BNP(T) v = this;
		 BNP(T) lChild = v->left;
		 BNP(T) rChild = v->right;//c必须存在
		 BNP(T)lr = rChild->left;
		 v->BinTreeNode<T>::swap(rChild);//先换皮也就是把v的数据和c交换
		 v->left = rChild;
		 v->right = rChild->right;
		 v->left->parent = v;
		 if(v->right)
		 v->right->parent = v;//这里已经完成c移动到v,并建立了其节点双向关系
		 v = rChild;//现在v节点视为原来的右孩子
		 v->left = lChild;
		 if (lChild)
			 lChild->parent = v;
		 v->right = lr;
		 if (lr)lr->parent = v;//这里v已经作为了右孩子，并建立了节点双向关系

		 this->left->m_height = 1 + __max(Stature(this->left->left), Stature(this->left->right));
		 m_height = 1 + __max(Stature(left), Stature(right));
		 for (BNP(T) x = parent; x; x = x->parent)
			 if ((*x).m_height == 1 + __max(Stature((*x).left), Stature((*x).right)))
				 break;
			 else
				 x->m_height = 1 + __max(Stature(x->left), Stature(x->right));
		 return this;
	 }
	
	 template<typename T>
	 inline  bool BinTreeNode<T>::operator<(BinTreeNode const &btn)
	 {
		 return (this->data < btn.data);;
	 }
	 template<typename T>
	 inline bool BinTreeNode<T>::operator==(BinTreeNode const &btn)
	 {
		 return (this->data == btn.data);;
	 }
	 template<typename T>
	 inline  bool BinTreeNode<T>::operator>(BinTreeNode const &btn)
	 {
		 return (this->data> btn.data);
	 }
	 template<typename T>
	 inline  bool BinTreeNode<T>::operator!=(BinTreeNode const &btn)
	 {
		  return (this->data!=btn.data);
	 }
	  template<typename T>
	  inline   bool BinTreeNode<T>::isRoot()
	  {
		  return !(this->parent);
	  }
	   template<typename T>
	   inline  bool BinTreeNode<T>::isLeftChild()
	   {
			return (!this->isRoot( )&&(this== this->parent->left));
	   }
		template<typename T>
		inline  bool BinTreeNode<T>::isRightChild()
		{
			return (!this->isRoot() && (this == this->parent->right));
		}
		 template<typename T>
		 inline  bool BinTreeNode<T>::hasParent()
		 {
			  return  (this->parent);
		 }
		  template<typename T>
		  inline  bool BinTreeNode<T>::hasLeftChild()
		  {
			  return  (this->left);
		  }
		  template<typename T>
		  inline   bool BinTreeNode<T>::hasRightChild()
		  {
			   return (this->right);
		  }

		   template<typename T>
		   inline   bool BinTreeNode<T>::hasChild()
		   {
			   return (this->hasLeftChild()|| this->hasRightChild());
		   }

			template<typename T>
			inline  bool BinTreeNode<T>::hasBothChild()
			{
				 return (this->hasLeftChild() && this->hasRightChild());
			}

			 template<typename T>
			 inline  bool BinTreeNode<T>::isLeaf()
			 {
				 return  (!this->hasChild());
			 }

			  template<typename T>
			  inline   BNP(T)& BinTreeNode<T>::sibling()
			  {
				  return (this->isLeftChild()? this->parent->right:this->parent->left);
			  }

			   template<typename T>
			   inline   BNP(T)& BinTreeNode<T>::uncle()
			   {
				   return (this->parent->isLeftChild()? this->parent->parent->right: this->parent->parent->left);
			   }

			   template<typename T>
			   inline  BNP(T)& BinTreeNode<T>::inParentNodeOf()
			   {
				   return (this->isRoot()? this->parent: this->isLeftChild()? this->parent->left: this->parent->right);
			   }

}
#endif // !BINTREENODE_H_H