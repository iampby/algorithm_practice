#ifndef BINTREEH_CPP_CPP
#define BINTREEH_CPP_CPP
#include<stack>
#include "BinTreeNode.cpp"
#include"BinTreeTraversalInf.h"
namespace BT {
#define TREE_NOEXCEPT noexcept
	using namespace BTN;
	template<typename T = int>
	class BinTree
	{
	protected:
		int m_size; BNP(T) m_root;
		virtual int updatem_height(BNP(T) n);//���½ڵ�n�߶�
		void updateAncestorm_height(BNP(T) n);//���¼���n���ȸ߶�
public:
		 BinTree(); 
	 BinTree(BinTree<T> const&);//���������� ע���õĲ�α�����������ռ� ������� �����ѵĿռ����
	 BinTree(BinTree<T>&&)TREE_NOEXCEPT;//������Ĭ�ϸ��ƹ��캯��
	BinTree&operator=(BinTree<T> )&;//��ֵ�������ƶ���ֵ����
		~BinTree();
		int size()const;//��ȡ����ģ
		bool empty()const;
		BNP(T) root()const;//��ȡ����
		BNP(T) insertAsRoot(T const &d);
		BNP(T) insertAsLeft(BNP(T) n, T const &d);
		BNP(T) insertAsRight(BNP(T) n, T const &d);
		BNP(T) attachAsLeft(BNP(T) n, BinTree<T>*&t);//t��Ϊn������������
		BNP(T) attachAsRight(BNP(T) n, BinTree<T>*&t);//t��Ϊn������������
		int remove(BNP(T) n);//ɾ��n���������ɾ������
		BinTree<T>* secede(BNP(T) n);//������n���뵱ǰ������������Ϊһ�Ŷ�������
		BNP(T)& inParentNodeOf(BNP(T)n);//���ؽڵ�n�ڸ��ڵ��еĺ�������
		//��α���
		template <typename VST=LevelTraversal<T>> //������
		void levelTraversal(VST = VST());
		//ǰ�����
		template <typename VST=PreorderTraversal<T>> //������
		void preorderTraversal(VST = VST());
		//�������
		template <typename VST=InorderTraversal<T>> //������
		void inorderTraversal(VST = VST());
		//�������
		template <typename VST=PostorderTraversal<T>> //������
		void postorderTraversal(VST=VST());
		//�Ƚ���
		bool operator< (BinTree<T> const& t);
		bool operator> (BinTree<T> const& t);
		bool operator== (BinTree<T> const& t); //�е���
bool operator!= (BinTree<T> const& t); 

	private:
		int removeAt(BNP(T) n);//ɾ��n���������ɾ������
	};

	
}
#endif // !BINTREE_CPP_CPP

