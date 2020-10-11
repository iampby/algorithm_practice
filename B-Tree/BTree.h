#ifndef BTREE_H_H
#define BTREE_H_H
#include"BTreeNode.h"
#include"TraversalInf.h"
#include<queue>
namespace BT {
	
#define Find(X,V) find(X,V)
	//vector容器预分配过小 对于相同值的记录容器 这里采用手动分配 按约定2倍扩大 2因子缩小
#define ReallocVector(X) {\
if(X.size()>=X.capacity()-1)X.reserve(X.capacity()*2);\
else if(X.size()<X.capacity()/2-4)X.reserve(X.capacity()/2);\
} 
#define CopyVector(N,O) (N.reserve(O.capacity());N=O ) //保持容器复制时 最大预分配内存一样
using namespace BTN;

/*返回vector X中第一个比V大的序*/
template<typename T>
	int find(std::vector<T>&keys, T const& v) {
		int size = keys.size(), i;
			for (i = 0; i < size; ++i) {
					if (keys[i] == v)return i;
					else if (keys[i] > v)return i;
			}
				return i; 
	}

template<typename T>
	class BTree
	{
	public:
		BTree(BTree<T> const&);;//用队列按层次遍历拷贝
		BTree(BTree<T> &&);
		BTree&operator=(BTree<T> )&;//左值赋值函数
		explicit BTree(int order=2);//默认为2阶,即退化为二叉搜索树 (m>=2)
		~BTree();//用队列按层次遍历删除
		int const order()const;//阶次
		int const size()const;//规模
		BTN(T)&root();//引用树根
		bool empty()const;//判空
		template<typename Visist=InorderTraversal<T> >//默认为递归版的中序遍历
		void traversal(Visist=Visist());//遍历

		//操作接口
		virtual BTN(T) search(T const&);//查找
		virtual  bool insert(T const&);//插入
		virtual bool remove(T const&);//删除
	protected:
		void solveOverFlow(BTN(T) );//解决插入上溢现象
		void solveUnderFlow(BTN(T) );//解决插入下溢现象
	protected:
		int m_size;//关键码总数
		int m_order;//B-树的阶次,至少为2(即退化为二叉搜索树) 创建时指定 一般不做修改
		BTN(T) m_root;//树根
		BTN(T) m_hitParentNode;//最后访问的节点或者最后访问的节点父亲，当树为空时 其访问后为空
		};

}
#include"BTree.cpp"
#endif // !BTREE_H_H


