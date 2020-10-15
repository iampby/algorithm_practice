#ifndef AVL_H_H
#define AVL_H_H
#include"BinSearchTree.h"
namespace N_AVL{
	using namespace BST;//ʹ�ö����������������ռ�
	template<typename T>
	class AVL : public BinSearchTree<T> {
	
	public:
		AVL() {};
		inline AVL(AVL<T>const&);
		inline AVL(AVL<T>&&)TREE_NOTHROW;
		inline AVL&operator=(AVL<T>)&;
		~AVL() {};
		virtual	BNP(T) insert(T const&)override;
		virtual	bool remove(T const &)override;
		virtual BNP(T) search(T const&d)override {
		return BinSearchTree<T>::search(d);
	};
	//�ж��Ƿ�������ƽ������
		 bool balanced(BNP(T)n) {
		 return Stature(n->left) == Stature(n->right);
	};
	 //ƽ�����ӻ�ȡ
		 int balancedFactor(BNP(T)n) {
	 return Stature(n->left)- Stature(n->right);
	 };
	  //AVL�Ƿ�ƽ��
		 bool AVLBalanced(BNP(T)n) {
		  return -2 < balancedFactor(n) && 2 > balancedFactor(n);
	  }
	  //��ȡ�ϸߵĺ��ӣ�����ȸ��򷵻غ͸���ͬ��ĺ���
		 BNP(T)&tallerChild(BNP(T)n) {
		  return Stature(n->left) > Stature(n->right) ? n->left :
			  (Stature(n->left) < Stature(n->right)) ? n->right :
			  (n->isLeftChild()) ? n->left : n->right;
	  }
	};
	template<typename T>
	TREE_OUTOFLINE AVL<T>::AVL(AVL<T> const &avl)
	{
		BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
		*tp = *static_cast<BinSearchTree<T>*>(const_cast<AVL<T>*>(&avl));//ȥ��const����û���ĸ�ֵ����
	}

	template<typename T>
	TREE_OUTOFLINE AVL<T>::AVL(AVL<T>&&avl)TREE_NOTHROW
	{
		BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
		*tp = std::move(*static_cast<BinSearchTree<T>*>(&avl));//���û���ĸ�ֵ����
	}

	template<typename T>
	TREE_OUTOFLINE AVL<T> & AVL<T>::operator=(AVL<T> avl) &
	{
		// TODO: �ڴ˴����� return ���
		BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
		*tp = std::move(*static_cast<BinSearchTree<T>*>(&avl));//���û���ĸ�ֵ����
		return *this;
	}
	template<typename T>
	TREE_OUTOFLINE BNP(T) AVL<T>::insert(T const &d)
	{ 
		BNP(T) p = search(d);
		BNP(T)parent = nullptr;//���׽ڵ��ʼ��0
		if (p) {//����Ѵ��ڣ�������Ϊ��̲���������һ��ֵΪd�ĺ��
			BNP(T)forerunner = p;
			bool isLeft = false;
			while (true)
			{
				if (forerunner->data == d) {
					if (forerunner->hasRightChild()) {
						forerunner = forerunner->right;//��̱�Ȼλ���ұ�
					}
					else {
						parent = forerunner;//�ҵ����ڵ�
						isLeft = false;
						break;
					}
				}
				else {
					if (forerunner->hasLeftChild())
						forerunner = forerunner->left;//��̱������ӷ�����
					else {
						parent = forerunner;//�ҵ����ڵ�
						isLeft = true;
						break;
					}
				}
			}
				++BinTree<T>::m_size;
				BNP(T)n = new BinTreeNode<T>(d, parent);//�½�һ���ڵ� ָ���׽ڵ�
				if (isLeft) {
					parent->left = n;//�͵���ڵ㽨����ϵ
				}
				else parent->right = n;
				p = n;
			}
		else {
			++BinTree<T>::m_size;
			parent = this->m_hitNodeParent;
			p = new BinTreeNode<T>(d, parent);
			if (parent) {
				if (parent->data > d)parent->left = p;
				else parent->right = p;//�ؽ���ϵ 
			}else this -> m_root = p;
		}
		//����ֻ��һ�ε���,���û�з�����������ʱ�临�Ӷ�ΪO��1��,������������
		for(BNP(T)g=parent;g;g=g->parent)
			if (!AVLBalanced(g)) {//һ��ʧ�⣬������v�ڵ�����ת���� ����g�ڵ����3+4�ع��㷨
				this->rotateAt(tallerChild(tallerChild(g)));
				break;//
			}
			else {
					this->updateHeight(g);//��ʹƽ��߶�Ҳ���ܱ仯
			}
		return p;
	}

	template<typename T>
	TREE_OUTOFLINE bool AVL<T>::remove(T const &d)
	{
		if (!BinSearchTree<T>::remove(d)){
			std::cout << "remove false\n";
			return false;//ɾ��ʧ��
		}
			//ɾ���ᷢ����ʧ�⴫����,��Ҫ��ε���,ʱ�临�Ӷ�Ϊ��h����
		for (BNP(T)g = this->m_hitNodeParent; g; g = g->parent)
			if (!AVLBalanced(g)) {//һ��ʧ�⣬������v�ڵ�����ת���� ����g�ڵ����3+4�ع��㷨
				g  = this->rotateAt(tallerChild(tallerChild(g)));
				this->updateHeight(g);//��ʹƽ��߶�Ҳ���ܱ仯
				}
		return true;
	}

}

#endif // !AVL_H_H



