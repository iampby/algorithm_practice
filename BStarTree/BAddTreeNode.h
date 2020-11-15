#ifndef BADDTREENODE_H_H_H
#define BADDTREENODE_H_H_H

/*
B+tree节点
K是码,E是记录 
E类型必须实现函数（K key()）定义
*/



#include<deque>

namespace BATN {

	//内部节点
	template<typename K, typename E>
	class BAddTreeNode {
	public:
		//只能作为根节点创建 
		explicit BAddTreeNode();//默认构造函数 创建一个空B-tree，初始化时有0个关键码及1个空孩子分支 
	   ~BAddTreeNode();//注：析构不释放孩子内存仅仅释放e内存
	    bool isLeaf()const;//通过孩子是否为空判断是否为底层节点
	public:
		BAddTreeNode<K, E>* parent;//父节点
		std::deque<K>key;//关键码
		std::deque<BAddTreeNode<K, E>*>child;//孩子分支，总比关键码多1
};


	template<typename K, typename E>
	inline BAddTreeNode<K, E>::BAddTreeNode()
	{
		parent = nullptr;
		child.insert(child.end(), nullptr);//默认孩子为空
	}


	template<typename K, typename E>
	inline BAddTreeNode<K, E>::~BAddTreeNode()
	{
	
	}

	template<typename K, typename E>
	inline bool BAddTreeNode<K, E>::isLeaf() const
	{
		return !child[0];
	}



	//叶子节点
	template<typename K, typename E>
	class BAddTreeLeafNode :public BAddTreeNode<K,E>
	{
	public:
		//只能作为根节点创建 
		explicit BAddTreeLeafNode();//默认构造函数 创建一个空B-tree，初始化时有0个关键码及1个空孩子分支 
		~BAddTreeLeafNode();
	public:
		std::deque <E*>e;//记录
		BAddTreeLeafNode<K, E>*last, *next;//链表前后
	};

	
	template<typename K, typename E>
	inline BAddTreeLeafNode<K, E>::BAddTreeLeafNode()
	{
		last = nullptr; next = nullptr;
	}
	template<typename K, typename E>
	inline BAddTreeLeafNode<K, E>::~BAddTreeLeafNode()
	{
		int _s = e.size();
		for (int i = 0; i < _s; ++i) {
			delete e[i], e[i] = nullptr;
		}
		e.resize(0);
	}
}
#endif // !BADDTREENODE_H_H_H

