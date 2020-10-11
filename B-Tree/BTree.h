#ifndef BTREE_H_H
#define BTREE_H_H
#include"BTreeNode.h"
#include"TraversalInf.h"
#include<queue>
namespace BT {
	
#define Find(X,V) find(X,V)
	//vector����Ԥ�����С ������ֵͬ�ļ�¼���� ��������ֶ����� ��Լ��2������ 2������С
#define ReallocVector(X) {\
if(X.size()>=X.capacity()-1)X.reserve(X.capacity()*2);\
else if(X.size()<X.capacity()/2-4)X.reserve(X.capacity()/2);\
} 
#define CopyVector(N,O) (N.reserve(O.capacity());N=O ) //������������ʱ ���Ԥ�����ڴ�һ��
using namespace BTN;

/*����vector X�е�һ����V�����*/
template<typename T>
	int find(std::vector<T>&keys, T const& v) {
		int size = keys.size(), i;
			for (i = 0; i < size; ++i) {
					if (keys[i] == v)return i;
					else if (keys[i] > v)return i;
			}
				return i; 
	}

template<typename T>
	class BTree
	{
	public:
		BTree(BTree<T> const&);;//�ö��а���α�������
		BTree(BTree<T> &&);
		BTree&operator=(BTree<T> )&;//��ֵ��ֵ����
		explicit BTree(int order=2);//Ĭ��Ϊ2��,���˻�Ϊ���������� (m>=2)
		~BTree();//�ö��а���α���ɾ��
		int const order()const;//�״�
		int const size()const;//��ģ
		BTN(T)&root();//��������
		bool empty()const;//�п�
		template<typename Visist=InorderTraversal<T> >//Ĭ��Ϊ�ݹ����������
		void traversal(Visist=Visist());//����

		//�����ӿ�
		virtual BTN(T) search(T const&);//����
		virtual  bool insert(T const&);//����
		virtual bool remove(T const&);//ɾ��
	protected:
		void solveOverFlow(BTN(T) );//���������������
		void solveUnderFlow(BTN(T) );//���������������
	protected:
		int m_size;//�ؼ�������
		int m_order;//B-���Ľ״�,����Ϊ2(���˻�Ϊ����������) ����ʱָ�� һ�㲻���޸�
		BTN(T) m_root;//����
		BTN(T) m_hitParentNode;//�����ʵĽڵ���������ʵĽڵ㸸�ף�����Ϊ��ʱ ����ʺ�Ϊ��
		};

}
#include"BTree.cpp"
#endif // !BTREE_H_H


