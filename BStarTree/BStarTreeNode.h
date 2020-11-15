#ifndef BSTARTREENODE_H_H_H
#define BSTARTREENODE_H_H_H

/*
B*树节点内部节点
*/


#include"BAddTreeNode.h"

namespace BATN {
	using namespace BATN;
	template<typename K, typename E>
	class BStarTreeNode :public BAddTreeNode<K, E>
	{
	public:
		//只能作为根节点创建 
		explicit BStarTreeNode();//默认构造函数 创建一个空B-tree，初始化时有0个关键码及1个空孩子分支 
		~BStarTreeNode();//注：析构不释放孩子内存仅仅释放e内存
	public:
		BStarTreeNode*last, *next;//兄弟节点
	};
	template<typename K, typename E>
	inline BStarTreeNode<K, E>::BStarTreeNode()
	{
		last = nullptr; next = nullptr;
	}
	template<typename K, typename E>
	inline BStarTreeNode<K, E>::~BStarTreeNode()
	{
      }
}


#endif // !BSTARTREENODE_H_H_H

