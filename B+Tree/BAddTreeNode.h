#ifndef BADDTREENODE_H_H_H
#define BADDTREENODE_H_H_H

/*
B+tree�ڵ�
K����,E�Ǽ�¼ 
E���ͱ���ʵ�ֺ�����K key()������
*/



#include<deque>

namespace BATN {
	template<typename K, typename E>
	class BAddTreeNode {
	public:
		BAddTreeNode();
		//ֻ����Ϊ���ڵ㴴�� ע���������ͷź����ڴ�����ͷ�e�ڴ�
		explicit BAddTreeNode(int  order);//Ĭ�Ϲ��캯�� ����һ����B-tree����ʼ��ʱ��0���ؼ��뼰1���պ��ӷ�֧ ����ԤʾdequeԤ�����ڴ��С
		BAddTreeNode(K const&, const int &order, BAddTreeNode<K, E>*lc = nullptr, BAddTreeNode<K, E>*rc = nullptr);//����һ���ǿ�B-tree��������һ���ؼ��������2����֧
		~BAddTreeNode();
		bool isLeaf()const;
	public:
		std::deque <E*>e;//��¼
		BAddTreeNode<K, E>* parent;//���ڵ�
		std::deque<K>key;//�ؼ���
		std::deque<BAddTreeNode<K, E>*>child;//���ӷ�֧���ܱȹؼ����1
		BAddTreeNode<K, E>*last, *next;//����ǰ��
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
		child.insert(child.end(), nullptr);//Ĭ�Ϻ���Ϊ��
		 last = nullptr; next = nullptr;
	}

	template<typename K, typename E>
	inline BAddTreeNode<K, E>::BAddTreeNode(K const &index, const int & order, BAddTreeNode<K, E>* lc, BAddTreeNode<K, E>* rc)
	{
		parent = nullptr;//����
		key.insert(key.end(), index);//һ���ؼ���
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

