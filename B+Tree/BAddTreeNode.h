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
		//ֻ����Ϊ���ڵ㴴�� 
		explicit BAddTreeNode(int  order);//Ĭ�Ϲ��캯�� ����һ����B-tree����ʼ��ʱ��0���ؼ��뼰1���պ��ӷ�֧ 
	~BAddTreeNode();//ע���������ͷź����ڴ�����ͷ�e�ڴ�
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
		return !child[0];
	}

}
#endif // !BADDTREENODE_H_H_H

