#ifndef BINTREENODE_CPP_CPP
#define BINTREENODE_CPP_CPP
//�������ڵ�ӿ�
namespace BTN{//���ڵ������ռ�
#define BNP(T) BinTreeNode<T>* //�ڵ�ָ��������
#define Stature(p) (p?p->m_height:-1) //�ڵ�߶�
	template<typename T=int>
	class  BinTreeNode
	{
	public:
		T data;
		BNP(T)parent; BNP(T) left; BNP(T)right;//�������ҽڵ�
		int m_height;//�߶�public:
		explicit BinTreeNode(BinTreeNode<T> const&);//���ƹ��캯��
		explicit BinTreeNode(BinTreeNode<T> &) ;//���ƹ��캯��
		BinTreeNode();
		BinTreeNode<T>&operator=(BinTreeNode<T> const&)&;//��ֵ��ֵ���� ����ָ�����ռ�
		explicit BinTreeNode(T d,BNP(T) p=nullptr, BNP(T) l=nullptr, BNP(T)r=nullptr,int h=0);
		~BinTreeNode();
//�����ӿ�
		int size();//ͳ�Ƶ�ǰ�ڵ������� �����ñ�������
		virtual void swap(BNP(T));//����2���ڵ������
		//����
		BNP(T) insertAsLeft(T const&);
		BNP(T) insertAsRight(T const&);
		BNP(T) succeed();//��ȡ���
		BNP(T) zig(); //˳ʱ����ת������ �����µ���ת��ڵ�
		BNP(T) zag(); //��ʱ����ת������ �����µ���ת��ڵ�

		//�Ƚ������
		bool operator <(BinTreeNode const&);
		bool operator ==(BinTreeNode const&);
		bool operator >(BinTreeNode const&);
		bool operator !=(BinTreeNode const&);
		//״̬�������ж�
		bool isRoot();
		bool isLeftChild();
		bool isRightChild();
		bool hasParent();
		bool hasLeftChild();
		bool hasRightChild();
		bool hasChild();
		bool hasBothChild();
		bool isLeaf();
		//��ȡ�ض���ϵ�Ľڵ�
		BNP(T)& sibling();//�ֵܽڵ�
		BNP(T)& uncle();//����ڵ�
		BNP(T)& inParentNodeOf();//���ؽڵ��ڸ��ڵ��еĺ�������
	};

}


#endif // !BINTREENODE_CPP_CPP

