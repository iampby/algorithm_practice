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
	//ֻ����Ϊ���ڵ㴴�� ע���������ͷź����ڴ�
	explicit  BTreeNode(int  order);//Ĭ�Ϲ��캯�� ����һ����B-tree����ʼ��ʱ��0���ؼ��뼰1���պ��ӷ�֧ ����ԤʾvectorԤ�����ڴ��С
	BTreeNode(T const&, const int &order, BTN(T)lc = nullptr, BTN(T)rc = nullptr);//����һ���ǿ�B-tree��������һ���ؼ��������2����֧
	BTN(T)parent;//���ڵ�
	std::vector< std::vector<T> >same;//��ֵͬ���� ע���������һ��������������ֵͬ���������Ҳ����е��鷳������ķ�ʽ�ܷ��㣬����������ȵ�ֵ�������ڶ�Ӧ��ֵλ�ü�¼���ݵ����������ṹ,ɾ��Ҳһ��
	std::vector<T>key;//�ؼ���
	std::vector<BTN(T)>child;//���ӷ�֧���ܱȹؼ����1
};
template<typename T>
TREE_OUTOFLINE BTreeNode<T>::BTreeNode(int order)
{
	parent = nullptr; 
	same.reserve(order); key.reserve(order); child.reserve(order + 1);//Ԥ���������ռ� ע���ؼ�������������ڲ������ʱ���磬���Թؼ���Ԥ����Ϊ����
	child.insert(child.end(), nullptr);//Ĭ�Ϻ���Ϊ��
}
template<typename T>
TREE_OUTOFLINE BTreeNode<T>::BTreeNode(T const &d, const int& order, BTN(T) lc, BTN(T) rc)
{
	parent = nullptr;//����
	same.reserve(order); key.reserve(order); child.reserve(order+1);//Ԥ���������ռ� ע���ؼ�������������ڲ������ʱ���磬���Թؼ���Ԥ����Ϊ����
	key.insert(key.end(),d);//һ���ؼ���
	child.insert(child.end(),lc); child.insert(child.end(),rc);
	if (lc)lc->parent = this; if (rc)rc->parent = this;
}
}

#endif //!BTREENODE_H_H
