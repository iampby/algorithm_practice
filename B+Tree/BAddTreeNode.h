#ifndef BADDTREENODE_H_H_H
#define BADDTREENODE_H_H_H

/*
B+tree节点
K是码,E是记录 
E类型必须实现函数（K key()）定义
*/



#include<deque>

namespace BATN {
	template<typename K, typename E>
	class BAddTreeNode {
	public:
		BAddTreeNode();
		//只能作为根节点创建 注：析构不释放孩子内存仅仅释放e内存
		explicit BAddTreeNode(int  order);//默认构造函数 创建一个空B-tree，初始化时有0个关键码及1个空孩子分支 参数预示deque预分配内存大小
		BAddTreeNode(K const&, const int &order, BAddTreeNode<K, E>*lc = nullptr, BAddTreeNode<K, E>*rc = nullptr);//创建一个非空B-tree，即至少一个关键码和至少2个分支
		~BAddTreeNode();
		bool isLeaf()const;
	public:
		std::deque <E*>e;//记录
		BAddTreeNode<K, E>* parent;//父节点
		std::deque<K>key;//关键码
		std::deque<BAddTreeNode<K, E>*>child;//孩子分支，总比关键码多1
		BAddTreeNode<K, E>*last, *next;//链表前后
};

	template<typename K, typename E>
	inline BAddTreeNode<K, E>::BAddTreeNode()
	{
		parent = nullptr; last = nullptr; next = nullptr;
	}

	template<typename K, typename E>
	inline BAddTreeNode<K, E>::BAddTreeNode(int order)
	{
		parent = nullptr;
		child.insert(child.end(), nullptr);//默认孩子为空
		 last = nullptr; next = nullptr;
	}

	template<typename K, typename E>
	inline BAddTreeNode<K, E>::BAddTreeNode(K const &index, const int & order, BAddTreeNode<K, E>* lc, BAddTreeNode<K, E>* rc)
	{
		parent = nullptr;//树根
		key.insert(key.end(), index);//一个关键码
		child.insert(child.end(), lc); child.insert(child.end(), rc);
		if (lc)lc->parent = this; if (rc)rc->parent = this;
		last = nullptr; next = nullptr;
	}

	template<typename K, typename E>
	inline BAddTreeNode<K, E>::~BAddTreeNode()
	{
		int _s = e.size();
		for (int i = 0; i < _s; ++i) {
			delete e[i], e[i] = nullptr;
		}
		e.resize(0);
	}

	template<typename K, typename E>
	inline bool BAddTreeNode<K, E>::isLeaf() const
	{
		return last&&next;
	}

}
#endif // !BADDTREENODE_H_H_H

