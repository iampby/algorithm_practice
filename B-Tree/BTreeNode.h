#ifndef BTREENODE_H_H
#define BTREENODE_H_H

#include<vector>
namespace BTN {
#define TREE_OUTOFLINE inline
#define NOEXCEPT noexcept
#define BTN(T) BTreeNode<T>*
template<typename T>
class BTreeNode {
public:
	//只能作为根节点创建 注：析构不释放孩子内存
	explicit  BTreeNode(int  order);//默认构造函数 创建一个空B-tree，初始化时有0个关键码及1个空孩子分支 参数预示vector预分配内存大小
	BTreeNode(T const&, const int &order, BTN(T)lc = nullptr, BTN(T)rc = nullptr);//创建一个非空B-tree，即至少一个关键码和至少2个分支
	BTN(T)parent;//父节点
	std::vector< std::vector<T> >same;//相同值容器 注：这里采用一个容器来保存相同值，由于左右插入有点麻烦，建表的方式很方便，这样对于相等的值，我们在对应键值位置记录数据但不更新树结构,删除也一样
	std::vector<T>key;//关键码
	std::vector<BTN(T)>child;//孩子分支，总比关键码多1
};
template<typename T>
TREE_OUTOFLINE BTreeNode<T>::BTreeNode(int order)
{
	parent = nullptr; 
	same.reserve(order); key.reserve(order); child.reserve(order + 1);//预分配容器空间 注：关键码个数可能由于插入的暂时上溢，所以关键码预分配为阶数
	child.insert(child.end(), nullptr);//默认孩子为空
}
template<typename T>
TREE_OUTOFLINE BTreeNode<T>::BTreeNode(T const &d, const int& order, BTN(T) lc, BTN(T) rc)
{
	parent = nullptr;//树根
	same.reserve(order); key.reserve(order); child.reserve(order+1);//预分配容器空间 注：关键码个数可能由于插入的暂时上溢，所以关键码预分配为阶数
	key.insert(key.end(),d);//一个关键码
	child.insert(child.end(),lc); child.insert(child.end(),rc);
	if (lc)lc->parent = this; if (rc)rc->parent = this;
}
}

#endif //!BTREENODE_H_H
