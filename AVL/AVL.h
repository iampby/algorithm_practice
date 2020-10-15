#ifndef AVL_H_H
#define AVL_H_H
#include"BinSearchTree.h"
namespace N_AVL{
	using namespace BST;//使用二叉搜索树的命名空间
	template<typename T>
	class AVL : public BinSearchTree<T> {
	
	public:
		AVL() {};
		inline AVL(AVL<T>const&);
		inline AVL(AVL<T>&&)TREE_NOTHROW;
		inline AVL&operator=(AVL<T>)&;
		~AVL() {};
		virtual	BNP(T) insert(T const&)override;
		virtual	bool remove(T const &)override;
		virtual BNP(T) search(T const&d)override {
		return BinSearchTree<T>::search(d);
	};
	//判断是否是理想平衡条件
		 bool balanced(BNP(T)n) {
		 return Stature(n->left) == Stature(n->right);
	};
	 //平衡因子获取
		 int balancedFactor(BNP(T)n) {
	 return Stature(n->left)- Stature(n->right);
	 };
	  //AVL是否平衡
		 bool AVLBalanced(BNP(T)n) {
		  return -2 < balancedFactor(n) && 2 > balancedFactor(n);
	  }
	  //获取较高的孩子，如果等高则返回和父亲同向的孩子
		 BNP(T)&tallerChild(BNP(T)n) {
		  return Stature(n->left) > Stature(n->right) ? n->left :
			  (Stature(n->left) < Stature(n->right)) ? n->right :
			  (n->isLeftChild()) ? n->left : n->right;
	  }
	};
	template<typename T>
	TREE_OUTOFLINE AVL<T>::AVL(AVL<T> const &avl)
	{
		BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
		*tp = *static_cast<BinSearchTree<T>*>(const_cast<AVL<T>*>(&avl));//去掉const后调用基类的赋值函数
	}

	template<typename T>
	TREE_OUTOFLINE AVL<T>::AVL(AVL<T>&&avl)TREE_NOTHROW
	{
		BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
		*tp = std::move(*static_cast<BinSearchTree<T>*>(&avl));//调用基类的赋值函数
	}

	template<typename T>
	TREE_OUTOFLINE AVL<T> & AVL<T>::operator=(AVL<T> avl) &
	{
		// TODO: 在此处插入 return 语句
		BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
		*tp = std::move(*static_cast<BinSearchTree<T>*>(&avl));//调用基类的赋值函数
		return *this;
	}
	template<typename T>
	TREE_OUTOFLINE BNP(T) AVL<T>::insert(T const &d)
	{ 
		BNP(T) p = search(d);
		BNP(T)parent = nullptr;//父亲节点初始化0
		if (p) {//如果已存在，让他作为后继插入或者最后一个值为d的后继
			BNP(T)forerunner = p;
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
				p = n;
			}
		else {
			++BinTree<T>::m_size;
			parent = this->m_hitNodeParent;
			p = new BinTreeNode<T>(d, parent);
			if (parent) {
				if (parent->data > d)parent->left = p;
				else parent->right = p;//重建关系 
			}else this -> m_root = p;
		}
		//至多只需一次调整,如果没有发生调整，则时间复杂度为O（1）,即正比与树高
		for(BNP(T)g=parent;g;g=g->parent)
			if (!AVLBalanced(g)) {//一旦失衡，对孙子v节点做旋转操作 即对g节点采用3+4重构算法
				this->rotateAt(tallerChild(tallerChild(g)));
				break;//
			}
			else {
					this->updateHeight(g);//即使平衡高度也可能变化
			}
		return p;
	}

	template<typename T>
	TREE_OUTOFLINE bool AVL<T>::remove(T const &d)
	{
		if (!BinSearchTree<T>::remove(d)){
			std::cout << "remove false\n";
			return false;//删除失败
		}
			//删除会发生“失衡传播”,需要多次调整,时间复杂度为与h正比
		for (BNP(T)g = this->m_hitNodeParent; g; g = g->parent)
			if (!AVLBalanced(g)) {//一旦失衡，对孙子v节点做旋转操作 即对g节点采用3+4重构算法
				g  = this->rotateAt(tallerChild(tallerChild(g)));
				this->updateHeight(g);//即使平衡高度也可能变化
				}
		return true;
	}

}

#endif // !AVL_H_H



