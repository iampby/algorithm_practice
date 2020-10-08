#ifndef BINSEARCHTREE_H_H
#define BINSEARCHTREE_H_H

#include"BinTree.h"
namespace BST {
#define TREE_OUTOFLINE inline
#define TREE_NOTHROW TREE_NOEXCEPT
	using namespace BT;
	template<typename T=int>
	class BinSearchTree :
		public BT::BinTree<T>
	{
	public:
		inline BinSearchTree();
		inline BinSearchTree(BinSearchTree<T> const&);//���������� ע���õĲ�α�����������ռ� ������� �����ѵĿռ����
		inline BinSearchTree(BinSearchTree<T> &&)TREE_NOTHROW;//�ͺϳɹ��캯�����
		inline BinSearchTree&operator=(BinSearchTree<T>)&;//��ֵ��ֵ����
		inline ~BinSearchTree();

	protected:
		inline BNP(T) adjust(BNP(T), BNP(T), BNP(T),
			BNP(T), BNP(T),BNP(T),BNP(T));//3+4��������3���ڵ㼰4������
BNP(T) rotateAt(BNP(T));//�ڵ�������ת���� ˼·�ǰ�g p v λ�÷�4��������� ����Ϊ�ﱲ�ڵ�v

	public://�����ӿڣ�Ҫ������������ʵ�ָ��Թ���
		//ע : �麯�����ڵ�������������÷�ָ�����ã��Ա��ֹ���������һ��
		 virtual BNP(T) search(T const&);//��������ϲ�ͬ����Ҫ����ָ������ã���Ϊ����ָ���Ǹ��Ƶ���ʱ������ʧȥ������һ����ʧ���ݣ�Ϊ�˷������,�Ͳ�����ָ��������
		 virtual BNP(T) insert(T const&);//�������ֵͬ����Ϊ���һ����ֵͬ�ڵ�ĺ��
		 virtual bool remove(T const &);
	protected:
		BNP(T) m_hitNodeParent;//ѡ�нڵ㸸��
		};
};

	//��չ����
#include"BinSearchTree.cpp"


#endif // !BINSEARCHTREE_H_H