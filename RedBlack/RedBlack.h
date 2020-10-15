#ifndef REDBLACK_H_H
#define REDBLACK_H_H
/*
红黑树
*/
#include"BinSearchTree.h"
namespace RBT {
	using namespace BST;
	//由于统一规划空节点为-1和黑高度叶节点为0不符，所以这里用这个函数来判高
	template<typename T>
	int stature(BNP(T)p)
	{
		return (p ? p->m_height : 0); //节点黑高度 黑高度叶节点为0
	}
	template<typename T>
		class RedBlcak :public BinSearchTree<T> 
		{
		public:

			bool test(BNP(T)p) { return isNeedUpdateBlackHeight(p); }
			RedBlcak() = default;//使用默认的构造函数
			RedBlcak(RedBlcak<T> const&);
			RedBlcak(RedBlcak<T> &&)TREE_NOTHROW;
			RedBlcak&operator=(RedBlcak<T>)&;//左值赋值函数
			int height()const;//树黑高度
		 //操作接口
			using BinSearchTree<T>::search;//使用基类的
			virtual BNP(T) insert(T const&);
			virtual bool remove(T const &);
			protected:
				//辅助操作函数
				void reviseDoubleRed(BNP(T));
				void reviseDoubleBlack(BNP(T));
				virtual int updateHeight(BNP(T) n)override;//更新节点n黑高度

				//重定义基类的旋转和3+4调整，以去掉双黑和双红修正时多余且不正确的高度更新
				inline BNP(T) adjust(BNP(T), BNP(T), BNP(T),
					BNP(T), BNP(T), BNP(T), BNP(T));//3+4处理，联接3个节点及4颗子树
				BNP(T) rotateAt(BNP(T));//节点祖先旋转处理 思路是按g p v 位置分4中情况处理 参数为孙辈节点v

				//辅助判断函数
				bool isBlack(BNP(T));//判断节点是否黑色
				bool isRed(BNP(T));//判断节点是否红色
				//是否需要更新黑高度 注：这里树高度转化为黑高度
				bool isNeedUpdateBlackHeight(BNP(T));
		};
		template<typename T>
		TREE_OUTOFLINE RedBlcak<T>::RedBlcak(RedBlcak<T> const &rbt)
		{
			BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
			*tp = *static_cast<BinSearchTree<T>*>(const_cast<RedBlcak<T>*>(&rbt));//调用基类的赋值函数
		}
		template<typename T>
		TREE_OUTOFLINE RedBlcak<T>::RedBlcak(RedBlcak<T>&&rbt)TREE_NOTHROW
		{
			BinSearchTree<T>*tp = static_cast<BinSearchTree<T>*>(this);
			*tp = std::move(*static_cast<BinSearchTree<T>*>(&rbt));
		//调用基类的赋值函数
}
		template<typename T>
		TREE_OUTOFLINE RedBlcak<T> & RedBlcak<T>::operator=(RedBlcak<T> rbt) &
		{
			// TODO: 在此处插入 return 语句
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
			if (x) {//相同值插入作为后继，如不需要删除
				BNP(T)forerunner = x;
				BNP(T)parent = nullptr;//父亲节点初始化0
				bool isLeft = false;
				while (true)
				{
					if (forerunner->data == d) {
						if (forerunner->hasRightChild()) {
							forerunner = forerunner->right;//后继必然位于右边
						}
						else {
							parent = forerunner;//找到父节点
							isLeft = false;
							break;
						}
					}
					else {
						if (forerunner->hasLeftChild())
							forerunner = forerunner->left;//后继必在左孩子方向上
						else {
							parent = forerunner;//找到父节点
							isLeft = true;
							break;
						}
					}
				}
					++this->m_size;
					BNP(T)n = new BinTreeNode<T>(d, parent);//新建一个节点 指向父亲节点 黑高度为0
					if (isLeft) {
						parent->left = n;//和当点节点建立联系
					}
					else parent->right = n;
					reviseDoubleRed(n);//双红修正
					return n ;
}	else {
				++this->m_size;
				x = new BinTreeNode<T>(d,this->m_hitNodeParent);//这里和叶节点黑高度一样
				if (this->m_hitNodeParent) {//向下联接
					if (this->m_hitNodeParent->data > d) {
						this->m_hitNodeParent->left = x;
					}
					else {
						this->m_hitNodeParent->right = x;
					}
				}
				reviseDoubleRed(x);//双红修正 同时明确树根
				return x;
			}
		}
		template<typename T>
		TREE_OUTOFLINE bool RedBlcak<T>::remove(T const &d)
		{
			BNP(T)x = RedBlcak<T>::search(d); if (!x) {
				return false;
			}
			BNP(T)r;//实际被删除节点的替换者
			{
				r= nullptr;
				BNP(T)del = x;//实际被删除的节点(注意不是要删除的节点)
				if (!x->hasLeftChild()) {
					r = x->right;//直接更新节点为右孩子
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
					x->swap(del);//要删除的节点和后继交换数据
					BNP(T)t = del->parent;
					if (t == x) {
						t->right =r = del->right;//特殊情况，即右孩子为后继，直接更新右孩子为右孩子的后继
					}
					else {
						t->left = r = del->right;//一般情况，后继必然为左孩子，更新左孩子为左孩子的右孩子或者空
					}
				}
				this->m_hitNodeParent = del->parent;//记录实际被删除节点父亲
				if (r) {
					r->parent = this->m_hitNodeParent;//替换者的父亲为要删除节点的父亲 至此已建立了节点之间的联系
				}

				delete del, del = nullptr;//释放实际删除的节点
				this->m_size -= 1;//大小变化
				if (!this->m_hitNodeParent) {//如果删除了根节点，则更新为接替者
					this->m_root = r;
				}
			}
			if (this->m_size<1)return true;//空树返回
			//注：x的兄弟w始终为叶节点即黑色 即可视为x与w一起删除 只看r子树与x情况
			if (!this->m_hitNodeParent) {//情况1： 如果刚刚删除了根节点，则更新颜色和高度
				this->m_root->m_color =BinTreeNode<T>::RBColor::Black;//重置为黑色
				updateHeight(this->m_root);
				return true;
			}
			if (!isNeedUpdateBlackHeight(this->m_hitNodeParent))return true;//情况2 删除的x为红色 黑高度无影响
			if (isRed(r)) {//情况3 x为黑色 r为红色 r染色即黑高度恢复
				r->m_color = BinTreeNode<T>::RBColor::Black;
				++r->m_height;//颜色染黑 本身黑高度递增
				return true;
			}
			reviseDoubleBlack(r);//情况4 x r黑色  双黑矫正
			return true;
		}
		template<typename T>
		TREE_OUTOFLINE  void RedBlcak<T>::reviseDoubleRed(BNP(T)x)
		{
			while (true)
			{
				if (x->isRoot()) {
					this->m_root = x;
					this->m_root->m_color = BinTreeNode<T>::RBColor::Black;//根为黑色
					++this->m_root->m_height;//高度上升
					return;
				}
				BNP(T)p = x->parent;
				if (isBlack(p))return;//非双红
				BNP(T)g = p->parent;
				BNP(T)u = x->uncle();

				if (isBlack(u)) {//u为黑色 则3+4重构
					BNP(T)r = this->rotateAt(x);//3+4 
					r->m_color= BinTreeNode<T>::RBColor::Black;
					r->left->m_color = BinTreeNode<T>::RBColor::Red;
					r->right->m_color = BinTreeNode<T>::RBColor::Red;
					updateHeight(r->left); updateHeight(r->right); updateHeight(r);//更新调整后的高度 注：需先更新颜色
					return;
				}
				else {
					g->m_color= BinTreeNode<T>::RBColor::Red;//类似于（2,4）-树上溢情况，新上溢节点为红指向黑孩子节点，孩子节点可配一个红节点x
					p->m_color = BinTreeNode<T>::RBColor::Black; ++p->m_height;//红转黑 +1
					u->m_color = BinTreeNode<T>::RBColor::Black; ++u->m_height;//由（2,4）-树可知上溢时u节点必然不为空指针
					x = g;//上溢传播
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
			if (!p) {//情况3 迭代到树根即结束				
				return;
			}
			BNP(T)s =(p->left==r?p->right:p->left);
			//if (!s)return;
			if (isBlack(s)) {
				BNP(T)t = nullptr;//s的孩子t 默认黑色
				if (isRed(s->right))t = s->right;
				if (isRed(s->left))t = s->left;
				//情况1 p为不定色 s为黑色 t为红色 执行3+4重构染色 相当于（2—4）-树下溢时借一个兄弟的关键码
				if (t) { //t为红色
					BNP(T)b = this->rotateAt(t);//3+4
					b->m_color = p->m_color; //子树根颜色不变
					if (b->left) {
						b->left->m_color = BinTreeNode<T>::RBColor::Black; updateHeight(b->left);
					}//孩子颜色变为黑色 3+4重构黑高度不变
					if (b->right) {
						b->right->m_color = BinTreeNode<T>::RBColor::Black; updateHeight(b->right);
					};
					updateHeight(b);//自底向上更新高度
                  return;//只需一次修订
				}
				else {
					if (isRed(p)) {//情况2 t 为空即黑色 p为红色 s为黑色  执行染色 p黑，s红色 相当于（2—4）-树下溢时合并 
						p->m_color = BinTreeNode<T>::RBColor::Black; 
						s->m_color = BinTreeNode<T>::RBColor::Red; --s->m_height;
						return;//只需一次修订
					}
					else {//情况3 p为黑色 s也为黑色 执行染色 s为红色 相当于（2—4）-树下溢时合并 恢复局部黑高度平衡 然后迭代至多到根部
						s->m_color = BinTreeNode<T>::RBColor::Red; --s->m_height;//黑变红高度-1
						--p->m_height;//父类高度统一-1
						r = p;
						continue;//多次修订
					}
				}
			}
			else {
				/*
				情况4 p为黑色 s为红色 对p进行单旋（zig or zag）,而不是进行类似于（2—4）-树的下溢合并处理，对p染为红色，s染为黑色
				这时r已转为1,2情况，即p为红色，s为黑色 即只需再进行一次选择染色即可恢复整体平衡,并不需要更新高度
				  */
				BNP(T)t = s->isLeftChild() ? s->left : s->right;//选取同向的作为v才能单旋
				p->m_color = BinTreeNode<T>::RBColor::Red; --p->m_height;//黑转红 黑高度减1
				s->m_color = BinTreeNode<T>::RBColor::Black; ++s->m_height;//红转黑 
				t=this->rotateAt(t);
				this->m_hitNodeParent = p;//更新命中对象的父亲，因r可能为空
			continue;//再修订一次
			}
}
		}
		template<typename T>
		TREE_OUTOFLINE  int RedBlcak<T>::updateHeight(BNP(T) n)
		{
			n->m_height = __max(stature(n->left), stature(n->right));//更新为子类高度
			return isBlack(n)?++n->m_height:n->m_height;//黑递增
		}

		template<typename T>
		TREE_OUTOFLINE BNP(T) RedBlcak<T>::rotateAt(BNP(T)v)
		{
			BNP(T)p = v->parent; BNP(T)g = p->parent;//找出 g p祖先 得到g p v
			BNP(T)&t = this->inParentNodeOf(g);//逆向更新用
			//g p v 位置有4中情况  进行分别处理即可
			if (v->isLeftChild()) {
				if (p->isLeftChild()) {//p v同向说明执行单旋操作 根据方向为右旋
					p->parent = g->parent;//新的子树逆向联接
					adjust(v, p, g, v->left, v->right, p->right, g->right);//3+4联接
					t = p;//更新树根或者在父类中的位置
					return p;
				}
				else {//zig(p)-zag(g)
					v->parent = g->parent;//新的子树逆向联接
					adjust(g, v, p, g->left, v->left, v->right, p->right);//3+4联接
					t = v;//更新树根或者在父类中的位置
					return v;
				}
			}
			else {
				if (p->isRightChild()) {//p v同向说明执行单旋操作 根据方向为左旋
					p->parent = g->parent;//新的子树逆向联接
					adjust(g, p, v, g->left, p->left, v->left, v->right);//3+4联接
					t = p;//更新树根或者在父类中的位置
					return p;
				}
				else {//zag(p)-zig(g)
					v->parent = g->parent;//新的子树逆向联接
					adjust(p, v, g, p->left, v->left, v->right, g->right);//3+4联接
					t = v;//更新树根或者在父类中的位置
					return v;
				}
			}
		}

		template<typename T>
		TREE_OUTOFLINE BNP(T) RedBlcak<T>::adjust(BNP(T)a, BNP(T)b, BNP(T)c,
			BNP(T)t0, BNP(T)t1, BNP(T)t2, BNP(T)t3) {
			b->left = a; b->right = c;
			a->parent = b; c->parent = b;//0 1层关联
			a->left = t0; a->right = t1;
			c->left = t2; c->right = t3;
			if (t0)t0->parent = a; if (t1)t1->parent = a;
			if (t2)t2->parent = c; if (t3)t3->parent = c;//1 2层关联
			//更新树高
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
		3种情况需要更新 
		1 左右孩子的黑高度不等 
		2 作为红节点 黑高度与其孩子不相等
		3 作为黑节点 黑高度不等于孩子的黑高度+1
		*/
		template<typename T>
		TREE_OUTOFLINE bool  RedBlcak<T>::isNeedUpdateBlackHeight(BNP(T)n)
		{
			return  (stature(n->left)!= stature(n->right))//条件1
				||(n->m_height != (isRed(n) ? stature(n->left) : (stature(n->left) + 1)));//条件2 3
		}
};

#endif // !REDBLACK_H_H

