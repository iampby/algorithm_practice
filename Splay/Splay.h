#ifndef SPLAY_H_H
#define SPLAY_H_H
#include"BinSearchTree.h"
//ע����չ������Ҫά���߶ȣ������ع�ȥ���߶����
namespace ST {
	using namespace BST;
	template<typename T>
	class Splay :public BinSearchTree<T> 
	{
public:
	//������뷽ʽö��
	typedef enum {
		InsertByBSTInsert=1,
		InsertBySearch
	}InsertWay;
	Splay() = default;
	Splay(Splay<T> const&);
	Splay(Splay<T> &&)TREE_NOTHROW;
	Splay&operator=(Splay<T>)&;//��ֵ��ֵ����
	BNP(T) searchLast(T const&); // ÿ�η��� �����Ҳ��ҵ� �������һ�η�����չ����, ������ֵͬ�����Ȼ�ȡ�ײ�Ľڵ�
		//����ڵ㣬���ѽڵ���չ������,�������ֵͬ ���ҷ������ ����2 ָ�����뷽ʽ��1 ��BST�������չ 2 �������������� default
	BNP(T) insert(T const&, InsertWay);
//�����ӿڣ�Ҫ������������ʵ�ָ��Թ���
		virtual BNP(T) search(T const&)override;//ÿ�η��� �����Ҳ��ҵ� �������һ�η�����չ����,������ֵͬ�����Ȼ�ȡ�ϲ�Ľڵ�
		virtual bool remove(T const &)override;//ͨ��������չ���Ƴ����ڵ㣬���Ϊ2���� �ٴη���һ���� ������������� ���¸��ڵ�Ϊ���
	protected:
		virtual BNP(T) insert(T const&)override;//���뷽ʽ2 ��������������
		protected:
BNP(T) splay(BNP(T));//�����չ �����µ�����
		BNP(T) insertByInsert(T const&);//���뷽ʽ1 ��BST�������չ
	private:
		void attachAsLeft(BNP(T), BNP(T));//1������2�����������ӹ�ϵ��2��������Ϊ��
		void attachAsRight(BNP(T), BNP(T));//1������2�����������ӹ�ϵ��2��������Ϊ��
		
	};

	template<typename T>
	TREE_OUTOFLINE Splay<T>::Splay(Splay<T> const &t)
	{
		BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
		*tp = *static_cast<BinSearchTree<T>*>(const_cast<Splay<T>*>(&t));//���û���Ŀ�����ֵ
	}
	template<typename T>
	TREE_OUTOFLINE Splay<T>::Splay(Splay<T>&&t)TREE_NOTHROW
	{
		BinSearchTree<T>*tp= static_cast<BinSearchTree<T>*>(this);
		*tp = std::move(*static_cast<BinSearchTree<T>*>(&t));//���û�����ƶ���ֵ
	}

	template<typename T>
	inline Splay<T> & Splay<T>::operator=(Splay<T> t) &
	{
		// TODO: �ڴ˴����� return ���
		BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
		*tp = std::move(*static_cast<BinSearchTree<T>*>(&t));//���û���ĸ�ֵ����
return *this;
	}


template<typename T>
	TREE_OUTOFLINE BNP(T) Splay<T>::search(T const &d)
	{
		BNP(T)p=  BinSearchTree<T>::search(d);
		this->m_root = splay(p ? p : this->m_hitNodeParent);
		return this->m_root;
	}
	
	template<typename T>
	TREE_OUTOFLINE  BNP(T) Splay<T>::insert(T const &d, InsertWay way)
	{
		switch (way)
		{
		case InsertWay::InsertByBSTInsert: {
			return insertByInsert(d);
			}
		case InsertWay::InsertBySearch:
			return  insert(d);
}
			return nullptr;
	}

	template<typename T>
	TREE_OUTOFLINE BNP(T) Splay<T>::insert(T const &d)
	{
		if (!this -> m_root)return ++this->m_size, this->m_root = new BinTreeNode<T>(d);//��������˻����
		searchLast(d);//������ֵͬ ���뵽���һ������
		BNP(T)p = this->m_root;
		BNP(T)n = new BinTreeNode<T>(d);//�½��ڵ�
		if (d < p->data) {
			attachAsLeft(n, p->left);
			attachAsRight(n, p);
			p->left = nullptr;;//����p������
		}
		else {
			attachAsLeft(n,p);
			attachAsRight(n, p->right);
			p->right = nullptr;//����p���Һ���
		}
		this->m_root = n;
		this->updateAncestorheight(p);
		++this->m_size;
		return this->m_root;
	}
	template<typename T>
	TREE_OUTOFLINE BNP(T) Splay<T>::insertByInsert(T const &d)
	{
		//BNP(T)p= BinSearchTree<T>::insert(d);Ϊ�˶�̬�ԣ�������дһ��BST����
		BNP(T) p = BinSearchTree<T>::search(d);
		if (p) {//����Ѵ��ڣ�������Ϊ��̲���������һ��ֵΪd�ĺ��
			BNP(T)forerunner = p;
			BNP(T)parent = nullptr;//���׽ڵ��ʼ��0
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
			this->updateAncestorheight(parent);//���¸߶�
			p = n;//��¼�½ڵ�
		}
		else {
			++BinTree<T>::m_size;
			p = new BinTreeNode<T>(d, this->m_hitNodeParent);
			if (this->m_hitNodeParent) {
				if (this->m_hitNodeParent->data > d)this->m_hitNodeParent->left = p;
				else this->m_hitNodeParent->right = p;//�ؽ���ϵ 
				this->updateAncestorheight(this->m_hitNodeParent);//���¸߶�
			}
			else this->m_root = p;
		}
		this->m_root=splay(p);//�����չ������
		return this->m_root;
	}

	template<typename T>
	TREE_OUTOFLINE bool Splay<T>::remove(T const &d)
	{
		if (!this->m_root|| search(d)->data != d)return false;
		BNP(T)p= this->m_root;//Ҫɾ���Ľڵ�
		if (!p->hasLeftChild()) {
			this->m_root = p->right; if (this->m_root)this->m_root->parent = nullptr;
		}
		else if(!p->hasRightChild()){
			this->m_root = p->left; this->m_root->parent = nullptr;
		}
		else {//�ָ�2�������������������ںϲ��������õ��Ժ��Ϊ��������
			BNP(T)lc = p->left; BNP(T) rc = p->right;
			p->left = nullptr; p->right = nullptr;
			lc->parent = nullptr; rc->parent = nullptr;//�ָ����
			this->m_root = rc;//����Ϊ�Һ���
			this->search(p->data);//ʹ��̳�Ϊ����
			//��λ�ָ������
			BNP(T)t = this->m_root;
			//������ֵͬ���� ���������ܲ��ǵ����� ���������������������������ϲ��ٽ���
			if (t->left) {
				while (t->hasLeftChild())
				{
					t = t->left;
				}
			}
				t->left = lc; lc->parent = t;
			}
		delete p, p = nullptr;//�ͷŽڵ�
		--this->m_size;//��ģ��1
		if(this->m_root)
		this->updateHeight(this->m_root);//ֻ���������
		return true;
	}

	
	template<typename T>
	TREE_OUTOFLINE  BNP(T) Splay<T>::searchLast(T const &d)
	{
		BNP(T)p = BinSearchTree<T>::search(d);
		if (p) {//����Ѵ��ڣ������Һ��
			BNP(T)forerunner = p;
			while (true)
			{
				if (forerunner->data == d) {
					p = forerunner;//��¼Ŀ��ڵ�
					if (forerunner->hasRightChild()) {
						forerunner = forerunner->right;//��̱�Ȼλ���ұ�
					}
					else {
						//ȷ��Ŀ��ڵ�
						this->m_hitNodeParent = p->parent;//ȷ�����нڵ�ĸ���
						break;
					}
				}
				else {
					if (forerunner->hasLeftChild())
						forerunner = forerunner->left;//��̱������ӷ�����
					else {
						this->m_hitNodeParent = p->parent;//ȷ�����нڵ�ĸ���
						break;//�������ֵ��̣�����
					}
				}
			}
		}
		this->m_root = splay(p ? p : this->m_hitNodeParent);//��չ�ڵ�
		return this->m_root;
	}
	template<typename T>
	TREE_OUTOFLINE BNP(T) Splay<T>::splay(BNP(T)v)
	{
		if (!v)return nullptr; BNP(T)p,*g;//����v���׺��游
		while ((p=v->parent)&&(g=p->parent))
		{
			BNP(T)gg = g->parent;
			//g p v λ����4�����  ���зֱ����� Ŀ������vΪ��ת����ĸ� ע������pv����һ�µİ���avl������˫������,����һ�µĶԵ�ǰ������������ת������avl˫����һ��
			if (v->isLeftChild()) {
				if (p->isLeftChild()) {//zig(g)-zig(p) ��� v->p->g�ҷ���
					attachAsLeft(g, p->right);//g��������������ع�
					attachAsLeft(p, v->right); attachAsRight(p, g);//�ڶ�������ع�
					attachAsRight(v, p);//g������һ������ع�
				}
				else {//zig(p)-zag(g)
					this->adjust(g, v, p, g->left, v->left, v->right, p->right);//3+4����
					}
			}
			else {
				if (p->isRightChild()) {//zag(g)-zag(p) ��� v->p->g ����
					attachAsRight(g, p->left);//g��������������ع�
					attachAsRight(p, v->left); attachAsLeft(p, g);//�ڶ�������ع�
					attachAsLeft(v, p);//g������һ������ع�
				}
				else {//zag(p)-zig(g)
					this->adjust(p, v, g, p->left, v->left, v->right, g->right);//3+4����
					}
			}
			if (!gg) {
				v->parent =gg;
		}else if (g==gg->left)attachAsLeft(gg,v); //�������ӻ��������
			else attachAsRight(gg,v);
			this->updateHeight(g); this->updateHeight(p); this->updateHeight(v);//���¸߶� �Ե�����
		}
		//˫����չ���� gΪ�գ�p���ܲ�Ϊ��,��ʱ��p��һ�ε���,�ԴﵽĿ��
		if (p) {
			if (v->isLeftChild()) {
				attachAsLeft(p, v->right);//��һ������ع�
				attachAsRight(v, p);//��������
			}
			else {
				attachAsRight(p, v->left);//��һ������ع�
				attachAsLeft(v, p);//��������
			}
			v->parent = nullptr;
			}
	return v;
	}
	template<typename T>
	TREE_OUTOFLINE void Splay<T>::attachAsLeft(BNP(T) p, BNP(T)lc)
	{
		p->left = lc; if (lc)lc->parent = p;
	}
	template<typename T>
	TREE_OUTOFLINE void Splay<T>::attachAsRight(BNP(T)p, BNP(T)rc)
	{
		p->right = rc; if (rc)rc->parent = p;
	}
}

#endif // !SPLAY_H_H