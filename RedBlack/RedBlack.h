#ifndef REDBLACK_H_H
#define REDBLACK_H_H
/*
�����
*/
#include"BinSearchTree.h"
namespace RBT {
	using namespace BST;
	//����ͳһ�滮�սڵ�Ϊ-1�ͺڸ߶�Ҷ�ڵ�Ϊ0��������������������������и�
	template<typename T>
	int stature(BNP(T)p)
	{
		return (p ? p->m_height : 0); //�ڵ�ڸ߶� �ڸ߶�Ҷ�ڵ�Ϊ0
	}
	template<typename T>
		class RedBlcak :public BinSearchTree<T> 
		{
		public:

			bool test(BNP(T)p) { return isNeedUpdateBlackHeight(p); }
			RedBlcak() = default;//ʹ��Ĭ�ϵĹ��캯��
			RedBlcak(RedBlcak<T> const&);
			RedBlcak(RedBlcak<T> &&)TREE_NOTHROW;
			RedBlcak&operator=(RedBlcak<T>)&;//��ֵ��ֵ����
			int height()const;//���ڸ߶�
		 //�����ӿ�
			using BinSearchTree<T>::search;//ʹ�û����
			virtual BNP(T) insert(T const&);
			virtual bool remove(T const &);
			protected:
				//������������
				void reviseDoubleRed(BNP(T));
				void reviseDoubleBlack(BNP(T));
				virtual int updateHeight(BNP(T) n)override;//���½ڵ�n�ڸ߶�

				//�ض���������ת��3+4��������ȥ��˫�ں�˫������ʱ�����Ҳ���ȷ�ĸ߶ȸ���
				inline BNP(T) adjust(BNP(T), BNP(T), BNP(T),
					BNP(T), BNP(T), BNP(T), BNP(T));//3+4��������3���ڵ㼰4������
				BNP(T) rotateAt(BNP(T));//�ڵ�������ת���� ˼·�ǰ�g p v λ�÷�4��������� ����Ϊ�ﱲ�ڵ�v

				//�����жϺ���
				bool isBlack(BNP(T));//�жϽڵ��Ƿ��ɫ
				bool isRed(BNP(T));//�жϽڵ��Ƿ��ɫ
				//�Ƿ���Ҫ���ºڸ߶� ע���������߶�ת��Ϊ�ڸ߶�
				bool isNeedUpdateBlackHeight(BNP(T));
		};
		template<typename T>
		TREE_OUTOFLINE RedBlcak<T>::RedBlcak(RedBlcak<T> const &rbt)
		{
			BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
			*tp = *static_cast<BinSearchTree<T>*>(const_cast<RedBlcak<T>*>(&rbt));//���û���ĸ�ֵ����
		}
		template<typename T>
		TREE_OUTOFLINE RedBlcak<T>::RedBlcak(RedBlcak<T>&&rbt)TREE_NOTHROW
		{
			BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
			*tp = std::move(*static_cast<BinSearchTree<T>*>(&rbt));
		//���û���ĸ�ֵ����
}
		template<typename T>
		TREE_OUTOFLINE RedBlcak<T> & RedBlcak<T>::operator=(RedBlcak<T> rbt) &
		{
			// TODO: �ڴ˴����� return ���
			BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
			*tp = std::move(*static_cast<BinSearchTree<T>*>(&rbt));
			return *this;
		}
		template<typename T>
		TREE_OUTOFLINE int RedBlcak<T>::height() const
		{
			return (this->m_root? this->m_root->m_height:-1);
		}
		template<typename T>
		TREE_OUTOFLINE BNP(T) RedBlcak<T>::insert(T const &d)
		{
			BNP(T)x = search(d);
			if (x) {//��ֵͬ������Ϊ��̣��粻��Ҫɾ��
				BNP(T)forerunner = x;
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
					++this->m_size;
					BNP(T)n = new BinTreeNode<T>(d, parent);//�½�һ���ڵ� ָ���׽ڵ� �ڸ߶�Ϊ0
					if (isLeft) {
						parent->left = n;//�͵���ڵ㽨����ϵ
					}
					else parent->right = n;
					reviseDoubleRed(n);//˫������
					return n ;
}	else {
				++this->m_size;
				x = new BinTreeNode<T>(d,this->m_hitNodeParent);//�����Ҷ�ڵ�ڸ߶�һ��
				if (this->m_hitNodeParent) {//��������
					if (this->m_hitNodeParent->data > d) {
						this->m_hitNodeParent->left = x;
					}
					else {
						this->m_hitNodeParent->right = x;
					}
				}
				reviseDoubleRed(x);//˫������ ͬʱ��ȷ����
				return x;
			}
		}
		template<typename T>
		TREE_OUTOFLINE bool RedBlcak<T>::remove(T const &d)
		{
			BNP(T)x = RedBlcak<T>::search(d); if (!x) {
				return false;
			}
			BNP(T)r;//ʵ�ʱ�ɾ���ڵ���滻��
			{
				r= nullptr;
				BNP(T)del = x;//ʵ�ʱ�ɾ���Ľڵ�(ע�ⲻ��Ҫɾ���Ľڵ�)
				if (!x->hasLeftChild()) {
					r = x->right;//ֱ�Ӹ��½ڵ�Ϊ�Һ���
					if (del->isLeftChild())
						del->parent->left = r;
					else if(del->parent) del->parent->right = r;
				}
				else if (!x->hasRightChild()) {
					r = x->left;
					if (del->isLeftChild())
						del->parent->left = r;
					else if (del->parent)del->parent->right = r;
				}
				else {
					del = del->succeed();
					x->swap(del);//Ҫɾ���Ľڵ�ͺ�̽�������
					BNP(T)t = del->parent;
					if (t == x) {
						t->right =r = del->right;//������������Һ���Ϊ��̣�ֱ�Ӹ����Һ���Ϊ�Һ��ӵĺ��
					}
					else {
						t->left = r = del->right;//һ���������̱�ȻΪ���ӣ���������Ϊ���ӵ��Һ��ӻ��߿�
					}
				}
				this->m_hitNodeParent = del->parent;//��¼ʵ�ʱ�ɾ���ڵ㸸��
				if (r) {
					r->parent = this->m_hitNodeParent;//�滻�ߵĸ���ΪҪɾ���ڵ�ĸ��� �����ѽ����˽ڵ�֮�����ϵ
				}

				delete del, del = nullptr;//�ͷ�ʵ��ɾ���Ľڵ�
				this->m_size -= 1;//��С�仯
				if (!this->m_hitNodeParent) {//���ɾ���˸��ڵ㣬�����Ϊ������
					this->m_root = r;
				}
			}
			if (this->m_size<1)return true;//��������
			//ע��x���ֵ�wʼ��ΪҶ�ڵ㼴��ɫ ������Ϊx��wһ��ɾ�� ֻ��r������x���
			if (!this->m_hitNodeParent) {//���1�� ����ո�ɾ���˸��ڵ㣬�������ɫ�͸߶�
				this->m_root->m_color =BinTreeNode<T>::RBColor::Black;//����Ϊ��ɫ
				updateHeight(this->m_root);
				return true;
			}
			if (!isNeedUpdateBlackHeight(this->m_hitNodeParent))return true;//���2 ɾ����xΪ��ɫ �ڸ߶���Ӱ��
			if (isRed(r)) {//���3 xΪ��ɫ rΪ��ɫ rȾɫ���ڸ߶Ȼָ�
				r->m_color = BinTreeNode<T>::RBColor::Black;
				++r->m_height;//��ɫȾ�� ����ڸ߶ȵ���
				return true;
			}
			reviseDoubleBlack(r);//���4 x r��ɫ  ˫�ڽ���
			return true;
		}
		template<typename T>
		TREE_OUTOFLINE  void RedBlcak<T>::reviseDoubleRed(BNP(T)x)
		{
			while (true)
			{
				if (x->isRoot()) {
					this->m_root = x;
					this->m_root->m_color = BinTreeNode<T>::RBColor::Black;//��Ϊ��ɫ
					++this->m_root->m_height;//�߶�����
					return;
				}
				BNP(T)p = x->parent;
				if (isBlack(p))return;//��˫��
				BNP(T)g = p->parent;
				BNP(T)u = x->uncle();

				if (isBlack(u)) {//uΪ��ɫ ��3+4�ع�
					BNP(T)r = this->rotateAt(x);//3+4 
					r->m_color= BinTreeNode<T>::RBColor::Black;
					r->left->m_color = BinTreeNode<T>::RBColor::Red;
					r->right->m_color = BinTreeNode<T>::RBColor::Red;
					updateHeight(r->left); updateHeight(r->right); updateHeight(r);//���µ�����ĸ߶� ע�����ȸ�����ɫ
					return;
				}
				else {
					g->m_color= BinTreeNode<T>::RBColor::Red;//�����ڣ�2,4��-�����������������ڵ�Ϊ��ָ��ں��ӽڵ㣬���ӽڵ����һ����ڵ�x
					p->m_color = BinTreeNode<T>::RBColor::Black; ++p->m_height;//��ת�� +1
					u->m_color = BinTreeNode<T>::RBColor::Black; ++u->m_height;//�ɣ�2,4��-����֪����ʱu�ڵ��Ȼ��Ϊ��ָ��
					x = g;//���紫��
					continue;
				}
			}
		}
		template<typename T>
		TREE_OUTOFLINE  void RedBlcak<T>::reviseDoubleBlack(BNP(T)r)
		{
			while (true)
			{
			BNP(T)p = r ? r->parent : this->m_hitNodeParent;
			if (!p) {//���3 ����������������				
				return;
			}
			BNP(T)s =(p->left==r?p->right:p->left);
			//if (!s)return;
			if (isBlack(s)) {
				BNP(T)t = nullptr;//s�ĺ���t Ĭ�Ϻ�ɫ
				if (isRed(s->right))t = s->right;
				if (isRed(s->left))t = s->left;
				//���1 pΪ����ɫ sΪ��ɫ tΪ��ɫ ִ��3+4�ع�Ⱦɫ �൱�ڣ�2��4��-������ʱ��һ���ֵܵĹؼ���
				if (t) { //tΪ��ɫ
					BNP(T)b = this->rotateAt(t);//3+4
					b->m_color = p->m_color; //��������ɫ����
					if (b->left) {
						b->left->m_color = BinTreeNode<T>::RBColor::Black; updateHeight(b->left);
					}//������ɫ��Ϊ��ɫ 3+4�ع��ڸ߶Ȳ���
					if (b->right) {
						b->right->m_color = BinTreeNode<T>::RBColor::Black; updateHeight(b->right);
					};
					updateHeight(b);//�Ե����ϸ��¸߶�
                  return;//ֻ��һ���޶�
				}
				else {
					if (isRed(p)) {//���2 t Ϊ�ռ���ɫ pΪ��ɫ sΪ��ɫ  ִ��Ⱦɫ p�ڣ�s��ɫ �൱�ڣ�2��4��-������ʱ�ϲ� 
						p->m_color = BinTreeNode<T>::RBColor::Black; 
						s->m_color = BinTreeNode<T>::RBColor::Red; --s->m_height;
						return;//ֻ��һ���޶�
					}
					else {//���3 pΪ��ɫ sҲΪ��ɫ ִ��Ⱦɫ sΪ��ɫ �൱�ڣ�2��4��-������ʱ�ϲ� �ָ��ֲ��ڸ߶�ƽ�� Ȼ��������ൽ����
						s->m_color = BinTreeNode<T>::RBColor::Red; --s->m_height;//�ڱ��߶�-1
						--p->m_height;//����߶�ͳһ-1
						r = p;
						continue;//����޶�
					}
				}
			}
			else {
				/*
				���4 pΪ��ɫ sΪ��ɫ ��p���е�����zig or zag��,�����ǽ��������ڣ�2��4��-��������ϲ�������pȾΪ��ɫ��sȾΪ��ɫ
				��ʱr��תΪ1,2�������pΪ��ɫ��sΪ��ɫ ��ֻ���ٽ���һ��ѡ��Ⱦɫ���ɻָ�����ƽ��,������Ҫ���¸߶�
				  */
				BNP(T)t = s->isLeftChild() ? s->left : s->right;//ѡȡͬ�����Ϊv���ܵ���
				p->m_color = BinTreeNode<T>::RBColor::Red; --p->m_height;//��ת�� �ڸ߶ȼ�1
				s->m_color = BinTreeNode<T>::RBColor::Black; ++s->m_height;//��ת�� 
				t=this->rotateAt(t);
				this->m_hitNodeParent = p;//�������ж���ĸ��ף���r����Ϊ��
			continue;//���޶�һ��
			}
}
		}
		template<typename T>
		TREE_OUTOFLINE  int RedBlcak<T>::updateHeight(BNP(T) n)
		{
			n->m_height = __max(stature(n->left), stature(n->right));//����Ϊ����߶�
			return isBlack(n)?++n->m_height:n->m_height;//�ڵ���
		}

		template<typename T>
		TREE_OUTOFLINE BNP(T) RedBlcak<T>::rotateAt(BNP(T)v)
		{
			BNP(T)p = v->parent; BNP(T)g = p->parent;//�ҳ� g p���� �õ�g p v
			BNP(T)&t = this->inParentNodeOf(g);//���������
			//g p v λ����4�����  ���зֱ�����
			if (v->isLeftChild()) {
				if (p->isLeftChild()) {//p vͬ��˵��ִ�е������� ���ݷ���Ϊ����
					p->parent = g->parent;//�µ�������������
					adjust(v, p, g, v->left, v->right, p->right, g->right);//3+4����
					t = p;//�������������ڸ����е�λ��
					return p;
				}
				else {//zig(p)-zag(g)
					v->parent = g->parent;//�µ�������������
					adjust(g, v, p, g->left, v->left, v->right, p->right);//3+4����
					t = v;//�������������ڸ����е�λ��
					return v;
				}
			}
			else {
				if (p->isRightChild()) {//p vͬ��˵��ִ�е������� ���ݷ���Ϊ����
					p->parent = g->parent;//�µ�������������
					adjust(g, p, v, g->left, p->left, v->left, v->right);//3+4����
					t = p;//�������������ڸ����е�λ��
					return p;
				}
				else {//zag(p)-zig(g)
					v->parent = g->parent;//�µ�������������
					adjust(p, v, g, p->left, v->left, v->right, g->right);//3+4����
					t = v;//�������������ڸ����е�λ��
					return v;
				}
			}
		}

		template<typename T>
		TREE_OUTOFLINE BNP(T) RedBlcak<T>::adjust(BNP(T)a, BNP(T)b, BNP(T)c,
			BNP(T)t0, BNP(T)t1, BNP(T)t2, BNP(T)t3) {
			b->left = a; b->right = c;
			a->parent = b; c->parent = b;//0 1�����
			a->left = t0; a->right = t1;
			c->left = t2; c->right = t3;
			if (t0)t0->parent = a; if (t1)t1->parent = a;
			if (t2)t2->parent = c; if (t3)t3->parent = c;//1 2�����
			//��������
			//this->updateHeight(a); this->updateHeight(c); this->updateHeight(b);
			return b;
		}
	
		template<typename T>
		TREE_OUTOFLINE bool RedBlcak<T>::isBlack(BNP(T) n)
		{
			return (!n) || n->m_color ==BinTreeNode<T>::RBColor::Black;
		}
		template<typename T>
		TREE_OUTOFLINE bool  RedBlcak<T>::isRed(BNP(T)n)
		{
			return (n) && n->m_color == BinTreeNode<T>::RBColor::Red;
		}
		/*
		3�������Ҫ���� 
		1 ���Һ��ӵĺڸ߶Ȳ��� 
		2 ��Ϊ��ڵ� �ڸ߶����亢�Ӳ����
		3 ��Ϊ�ڽڵ� �ڸ߶Ȳ����ں��ӵĺڸ߶�+1
		*/
		template<typename T>
		TREE_OUTOFLINE bool  RedBlcak<T>::isNeedUpdateBlackHeight(BNP(T)n)
		{
			return  (stature(n->left)!= stature(n->right))//����1
				||(n->m_height != (isRed(n) ? stature(n->left) : (stature(n->left) + 1)));//����2 3
		}
};

#endif // !REDBLACK_H_H

