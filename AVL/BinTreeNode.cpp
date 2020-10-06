#ifndef BINTREENODE_CPP_CPP
#define BINTREENODE_CPP_CPP
//二叉树节点接口
namespace BTN{//树节点命名空间
#define BNP(T) BinTreeNode<T>* //节点指针声明宏
#define Stature(p) (p?p->m_height:-1) //节点高度
	template<typename T=int>
	class  BinTreeNode
	{
	public:
		T data;
		BNP(T)parent; BNP(T) left; BNP(T)right;//父及左右节点
		int m_height;//高度public:
		explicit BinTreeNode(BinTreeNode<T> const&);//复制构造函数
		explicit BinTreeNode(BinTreeNode<T> &) ;//复制构造函数
		BinTreeNode();
		BinTreeNode<T>&operator=(BinTreeNode<T> const&)&;//左值赋值函数 不对指针分配空间
		explicit BinTreeNode(T d,BNP(T) p=nullptr, BNP(T) l=nullptr, BNP(T)r=nullptr,int h=0);
		~BinTreeNode();
//操作接口
		int size();//统计当前节点后代总数 这里用暴力计数
		virtual void swap(BNP(T));//交换2个节点的数据
		//插入
		BNP(T) insertAsLeft(T const&);
		BNP(T) insertAsRight(T const&);
		BNP(T) succeed();//获取后继
		BNP(T) zig(); //顺时针旋转即右旋 返回新的旋转轴节点
		BNP(T) zag(); //逆时针旋转即左旋 返回新的旋转轴节点

		//比较运算符
		bool operator <(BinTreeNode const&);
		bool operator ==(BinTreeNode const&);
		bool operator >(BinTreeNode const&);
		bool operator !=(BinTreeNode const&);
		//状态与性质判断
		bool isRoot();
		bool isLeftChild();
		bool isRightChild();
		bool hasParent();
		bool hasLeftChild();
		bool hasRightChild();
		bool hasChild();
		bool hasBothChild();
		bool isLeaf();
		//获取特定关系的节点
		BNP(T)& sibling();//兄弟节点
		BNP(T)& uncle();//叔叔节点
		BNP(T)& inParentNodeOf();//返回节点在父节点中的孩子引用
	};

}


#endif // !BINTREENODE_CPP_CPP

