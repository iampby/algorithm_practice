#ifndef BSTARTREENODE_H_H_H
#define BSTARTREENODE_H_H_H

/*
B*���ڵ��ڲ��ڵ�
*/


#include"BAddTreeNode.h"

namespace BATN {
	using namespace BATN;
	template<typename K, typename E>
	class BStarTreeNode :public BAddTreeNode<K, E>
	{
	public:
		//ֻ����Ϊ���ڵ㴴�� 
		explicit BStarTreeNode();//Ĭ�Ϲ��캯�� ����һ����B-tree����ʼ��ʱ��0���ؼ��뼰1���պ��ӷ�֧ 
		~BStarTreeNode();//ע���������ͷź����ڴ�����ͷ�e�ڴ�
	public:
		BStarTreeNode*last, *next;//�ֵܽڵ�
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

