#ifndef BINTREEH_CPP_CPP
#define BINTREEH_CPP_CPP
#include<stack>
#include "BinTreeNode.cpp"
#include"BinTreeTraversalInf.h"
namespace BT {
#define TREE_NOEXCEPT noexcept
	using namespace BTN;
	template<typename T = int>
	class BinTree
	{
	protected:
		int m_size; BNP(T) m_root;
		virtual int updatem_height(BNP(T) n);//更新节点n高度
		void updateAncestorm_height(BNP(T) n);//更新绩点n祖先高度
public:
		 BinTree(); 
	 BinTree(BinTree<T> const&);//复制整棵树 注：用的层次遍历方法分配空间 这种最快 但花费的空间最多
	 BinTree(BinTree<T>&&)TREE_NOEXCEPT;//类似于默认复制构造函数
	BinTree&operator=(BinTree<T> )&;//左值拷贝或移动赋值函数
		~BinTree();
		int size()const;//获取树规模
		bool empty()const;
		BNP(T) root()const;//获取树根
		BNP(T) insertAsRoot(T const &d);
		BNP(T) insertAsLeft(BNP(T) n, T const &d);
		BNP(T) insertAsRight(BNP(T) n, T const &d);
		BNP(T) attachAsLeft(BNP(T) n, BinTree<T>*&t);//t作为n的左子树接入
		BNP(T) attachAsRight(BNP(T) n, BinTree<T>*&t);//t作为n的右子树接入
		int remove(BNP(T) n);//删除n后代并返回删除个数
		BinTree<T>* secede(BNP(T) n);//将子树n脱离当前树，并返回作为一颗独立子树
		BNP(T)& inParentNodeOf(BNP(T)n);//返回节点n在父节点中的孩子引用
		//层次遍历
		template <typename VST=LevelTraversal<T>> //操作器
		void levelTraversal(VST = VST());
		//前序遍历
		template <typename VST=PreorderTraversal<T>> //操作器
		void preorderTraversal(VST = VST());
		//中序遍历
		template <typename VST=InorderTraversal<T>> //操作器
		void inorderTraversal(VST = VST());
		//后序遍历
		template <typename VST=PostorderTraversal<T>> //操作器
		void postorderTraversal(VST=VST());
		//比较器
		bool operator< (BinTree<T> const& t);
		bool operator> (BinTree<T> const& t);
		bool operator== (BinTree<T> const& t); //判等器
bool operator!= (BinTree<T> const& t); 

	private:
		int removeAt(BNP(T) n);//删除n后代并返回删除个数
	};

	
}
#endif // !BINTREE_CPP_CPP

