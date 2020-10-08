#ifndef BINSEARCHTREE_H_H
#define BINSEARCHTREE_H_H

#include"BinTree.h"
namespace BST {
#define TREE_OUTOFLINE inline
#define TREE_NOTHROW TREE_NOEXCEPT
	using namespace BT;
	template<typename T=int>
	class BinSearchTree :
		public BT::BinTree<T>
	{
	public:
		inline BinSearchTree();
		inline BinSearchTree(BinSearchTree<T> const&);//复制整棵树 注：用的层次遍历方法分配空间 这种最快 但花费的空间最多
		inline BinSearchTree(BinSearchTree<T> &&)TREE_NOTHROW;//和合成构造函数差不多
		inline BinSearchTree&operator=(BinSearchTree<T>)&;//左值赋值函数
		inline ~BinSearchTree();

	protected:
		inline BNP(T) adjust(BNP(T), BNP(T), BNP(T),
			BNP(T), BNP(T),BNP(T),BNP(T));//3+4处理，联接3个节点及4颗子树
BNP(T) rotateAt(BNP(T));//节点祖先旋转处理 思路是按g p v 位置分4中情况处理 参数为孙辈节点v

	public://基本接口，要求所有派生类实现各自功能
		//注 : 虚函数类内调用最好用域作用符指定调用，以保持功能与类名一致
		 virtual BNP(T) search(T const&);//这里和书上不同，不要返回指针的引用，因为返回指针是复制的临时变量，失去作用域一样丢失内容，为了方便操作,就不返回指针引用了
		 virtual BNP(T) insert(T const&);//如插入相同值则作为最后一个相同值节点的后继
		 virtual bool remove(T const &);
	protected:
		BNP(T) m_hitNodeParent;//选中节点父亲
		};
};

	//扩展定义
#include"BinSearchTree.cpp"


#endif // !BINSEARCHTREE_H_H