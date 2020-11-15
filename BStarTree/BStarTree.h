#ifndef BSTARTREE_H_H_H
#define BSTARTREE_H_H_H 

/*
B*树
K是码,E是记录
E类型必须实现函数（K key()）定义
与B+树不同的是每个内部节点有指向兄弟的指针，节点只有大于ceil(2/3*m)才发生上溢
m取值：因合并操作需要移动索引和孩子分支，为了方便，最小要移动1,有1/3*m>=1,所以设定m>=3而不是B树的m>=2，
又由于设定的原因，这里为了方便选择了移动1/3*(m-1)索引，即m>=4
同时为了简化下溢3兄弟合并时分解操作，至少保证分解节点索引数不少于2，即ceil(2/3*(m-1))-1>=2,最终m>=5
注：可能是哪里有问题，实现了功能，但结果是m>=7
实现思路：同B+树，查找外部节点,对内部节点和外部节点区分处理
当上溢时，根节点以4/3(m-1)为临界点发生分裂，则恰好可以分裂为2个2/3(m-1)，
节点先判断左右兄弟是否可移动，不可移则同一个兄弟各拿1/3合并，
当下溢时，如果只有2个兄弟则合并为根节点，即可得到4/3(m-1)个码,
先判断左右兄弟是否可借，如果是最左子树或者最右子树，则下溢左移或右移，否则把节点分解到左右兄弟，
得到接近(m-1)的码值，对于内部节点，会导致某个兄弟发生上溢，则做一次上溢处理
*/


#include<deque>
#include<queue>
#include"BStarTreeNode.h"

namespace BST {
	using namespace BATN;
	template<typename K, typename E>
	class BStarTree
	{
	public:
		explicit BStarTree(int order = 256);//当小于7时默认为7阶(m>=7)
		~BStarTree();

		int const order()const;//阶次
		int const size()const;//规模

			//操作接口
		Entry find(E const&, bool&ok)const;//查找
		Entry find(E const&)const;//查找
		bool insert(E const&);//插入
		bool remove(E const&);//删除

		template<typename Visist>
		void list_traversal(Visist);//遍历
	private:
		BAddTreeLeafNode<K, E>*  search(E const&);//查找
		void solveOverFlow(BAddTreeLeafNode<K, E>*);//解决插入上溢现象 参数为节点
		void solveUnderFlow(BAddTreeLeafNode<K, E>*);//解决插入下溢现象 参数为节点
		K updateAncestorIndex(K const&_min, K const&_max, K&_v, BAddTreeNode<K, E>*p);//更新p祖先节点中唯一大于_min同时小于等于_max的索引为_v，返回旧索引

	private:
		int m_size;//关键码总数
		int m_order;//B-树的阶次,至少为2(即退化为二叉搜索树) 创建时指定 一般不做修改
		BStarTreeNode<K, E>* m_root;//树根
		BStarTreeNode<K, E>* m_hitParentNode;//查找访问时命中节点的父亲或者穿透底层后最后一个访问的节点，当树为空时 其访问后为空
		BAddTreeLeafNode<K, E>*m_header, *m_trail;//双向链表首尾
	};
	template<typename K, typename E>
	inline BStarTree<K, E>::BStarTree(int order)
	{
		if (order < 7)order = 7;//默认7阶
		m_order = order;
		//注：根初始化为叶子节点
		this->m_root = (BStarTreeNode<K, E>*)new BAddTreeLeafNode<K, E>(); m_size = 0; m_hitParentNode = nullptr;
		m_header = new BAddTreeLeafNode<K, E>();
		m_trail = new BAddTreeLeafNode<K, E>();
		BAddTreeLeafNode<K, E>*_leaf = (BAddTreeLeafNode<K, E>*)(this->m_root);
		m_header->next = _leaf; m_trail->last = _leaf;//链表
		_leaf->last = m_header; _leaf->next = m_trail;
	}
	template<typename K, typename E>
	inline BStarTree<K, E>::~BStarTree()
	{
		if (!this->m_root)return;//没有根就不删除
		std::queue<BStarTreeNode<K, E>*>q;//引入辅助队列按层次遍历删除
		q.push(this->m_root);//树根入队
		while (!q.empty())
		{
			BStarTreeNode<K, E>*p = q.front();
			q.pop();
			int count = p->child.size();
			for (int i = 0; i < count; ++i) {
				if (p->child[i]) {
					q.push(static_cast<BStarTreeNode<K, E>*>(p->child[i]));//添加所有孩子入队
				}
			}
			if (p->isLeaf()) {
				BAddTreeLeafNode<K, E>*_t = (BAddTreeLeafNode<K, E>*)p;
				delete _t, _t = nullptr;//析构叶子节点
			}
			else {
				delete p, p = nullptr;//释放每个内部节点
			}
		}
		delete m_header, m_header = nullptr;
		delete m_trail, m_trail = nullptr;
		this->m_root = nullptr;
		this->m_size = 0;
	}
	template<typename K, typename E>
	inline int const BStarTree<K, E>::order() const
	{
		return m_order;
	}
	template<typename K, typename E>
	inline int const BStarTree<K, E>::size() const
	{
		return m_size;
	}

	template<typename K, typename E>
	inline Entry BStarTree<K, E>::find(E const &e, bool & ok)const
	{
		K k = e.key();
		ok = false;
		BAddTreeLeafNode<K, E>*v = (BAddTreeLeafNode<K, E>*)(this->m_root);//c式强制转换
		while (!v->isLeaf())
		{
			int _s = v->key.size();
			int i = 0;
			for (; i < _s; ++i) {
				K&tk = v->key[i];
				if (tk > k)break;
			}
			v = static_cast<BAddTreeLeafNode<K, E>*>(v->child[i]);//转到下一层
		}
		if (v&&v->isLeaf()) {
			int _s = v->key.size();
			int i = 0;
			for (; i < _s; ++i) {
				K&tk = v->key[i];
				if (tk == k) {
					ok = true;
					return *(v->e[i]);
				}
			}
			v = (BAddTreeLeafNode<K, E>*)(v->child[i]);//转到下一层
		}
		return Entry();
	}
	template<typename K, typename E>
	inline Entry BStarTree<K, E>::find(E const &e) const
	{
		bool ok;
		return find(e, ok);
	}
	template<typename K, typename E>
	inline bool BStarTree<K, E>::insert(E const &e)
	{
		BAddTreeLeafNode<K, E>*v = search(e);
		if (v)
			return false;
		//插入
		K k = e.key();
		v = (BAddTreeLeafNode<K, E>*)(this->m_hitParentNode);
		int _s = v->key.size();
		int i = 0;
		for (; i < _s; ++i) {
			K&tk = v->key[i];
			if (tk > k)break;
		}
		v->key.insert(v->key.begin() + i, k);//插入关键字
		++this->m_size;//更新规模
		v->child.insert(v->child.begin() + i + 1, nullptr);//插入空分支
		E*_e = new E();
		*_e = std::move(e);//使用右值移动
		v->e.insert(v->e.begin() + i, _e);//插入记录
		solveOverFlow(v);//上溢则分裂
		return true;
	}
	template<typename K, typename E>
	inline bool BStarTree<K, E>::remove(E const &e)
	{
		BAddTreeLeafNode<K, E>*v = search(e);
		if (!v)
			return false;
		int rank = 0; while (v->key[rank] != e.key())++rank;
		//删除
		v->key.erase(v->key.begin() + rank);//删除关键字
		E*_e = v->e[rank];
		v->e.erase(v->e.begin() + rank);//删除记录
		--this->m_size;
		delete _e;//释放记录
		v->child.erase(v->child.begin() + rank + 1);//删除分支
		solveUnderFlow(v);//检测下溢
		return true;
	}

	template<typename K, typename E>
	inline BAddTreeLeafNode<K, E>* BStarTree<K, E>::search(E const &e)
	{
		this->m_hitParentNode = nullptr;
		K k = e.key();
		//std::cout << "\nsearch:\n";
		BAddTreeLeafNode<K, E>*v = (BAddTreeLeafNode<K, E>*)(this->m_root);//c式强制转换
		int x = 0;
		while (!v->isLeaf())
		{
			int _s = v->key.size();
			int i = 0;
			//printf("层%d：\n",x++);
			for (; i < _s; ++i) {
				K&tk = v->key[i];
				//std::cout <<tk <<" ";
				if (tk > k)break;
			}
			//printf("\n");
			this->m_hitParentNode = (BStarTreeNode<K, E>*)(v);
			v = static_cast<BAddTreeLeafNode<K, E>*>(v->child[i]);//转到下一层
		}
		if (v&&v->isLeaf()) {
			//std::cout << "\nleaf：\n";
			int _s = v->key.size();
			int i = 0;
			for (; i < _s; ++i) {
				K&tk = v->key[i];
				//std::cout <<tk <<" <-leaf- ";
				if (tk == k) {
					//	std::cout << tk<<" <-命中- ";
					return v;
				}
				else if (tk > k)
					break;
			}

			this->m_hitParentNode = (BStarTreeNode<K, E>*)(v);
			v = (BAddTreeLeafNode<K, E>*)(v->child[i]);//转到下一层
		}
		//std::cout <<"\n ";
		return v;
	}

	template<typename K, typename E>
	inline void BStarTree<K, E>::solveOverFlow(BAddTreeLeafNode<K, E>*v)
	{
		while (v->key.size() > m_order - 1)//上溢
		{
			BStarTreeNode<K, E>*p = static_cast<BStarTreeNode<K, E>*>(v->parent);
			if (!p) {//根节点
				int _verge = (2.0*(m_order - 1) + 2) / 3;//向上取整
				if (v->isLeaf()) {//叶节点情况
					if ((_verge) * 2 <= v->key.size()) {//根节点包含索引为4/3*m-1则恰好可以分裂为2个2/3*m的节点
						//构造兄弟节点
						BAddTreeLeafNode<K, E>* _right = new BAddTreeLeafNode<K, E>();
						_right->key.insert(_right->key.end(), v->key.end() - _verge, v->key.end());
						v->key.erase(v->key.end() - _verge, v->key.end());
						_right->e.insert(_right->e.end(), v->e.end() - _verge, v->e.end());
						v->e.erase(v->e.end() - _verge, v->e.end());
						_right->child.insert(_right->child.end(), v->child.end() - _verge, v->child.end());
						v->child.erase(v->child.end() - _verge, v->child.end());
						this->m_root = new BStarTreeNode<K, E>();
						this->m_root->child.insert(this->m_root->child.end(), static_cast<BAddTreeNode<K, E>*>(_right));//添加兄弟分支
						this->m_root->child[0] = static_cast<BAddTreeNode<K, E>*>(v);
						v->parent = this->m_root; _right->parent = this->m_root;//向上联接
						this->m_root->key.insert(this->m_root->key.end(), _right->key[0]);//建立索引
						v->next->last = _right; _right->next = v->next;
						v->next = _right; _right->last = v;
					}
				}
				else {
					if ((_verge) * 2 < v->key.size()) {//根节点包含索引为4/3*m则恰好可以分裂为2个2/3*m的节点
						//构造兄弟节点
						BStarTreeNode<K, E>*tv = (BStarTreeNode<K, E>*)v;
						BStarTreeNode<K, E>* _right = new BStarTreeNode<K, E>();
						_right->key.insert(_right->key.end(), tv->key.end() - _verge, tv->key.end());
						tv->key.erase(tv->key.end() - _verge, tv->key.end());
						_right->child.insert(_right->child.end(), tv->child.end() - _verge, tv->child.end());
						tv->child.erase(tv->child.end() - _verge, tv->child.end());
						_right->child[0] = *--tv->child.end();
						tv->child.erase(--tv->child.end());
						this->m_root = new BStarTreeNode<K, E>();
						this->m_root->child.insert(this->m_root->child.end(), static_cast<BAddTreeNode<K, E>*>(_right));//添加兄弟分支
						this->m_root->child[0] = static_cast<BAddTreeNode<K, E>*>(tv);
						tv->parent = this->m_root; _right->parent = this->m_root;//向上联接
						this->m_root->key.insert(this->m_root->key.end(), *--tv->key.end());//建立索引
						tv->key.erase(--tv->key.end());
						{
							int _s = _right->child.size();
							for (int i = 0; i < _s; ++i)
								_right->child[i]->parent = static_cast<BAddTreeNode<K, E>*>(_right);//向下联接
						}
						if (tv->next)tv->next->last = _right;
						_right->next = tv->next;
						tv->next = _right; _right->last = tv;
					}
				}
				return;
			}

			if (v->isLeaf()) {//叶节点
				if (v->last != m_header) {//存在左兄弟
					BAddTreeLeafNode<K, E>*_brother = v->last;
					if (_brother->child.size() < m_order) {//可移动
						updateAncestorIndex(_brother->key[0], v->key[0], *(v->key.begin() + 1), static_cast<BAddTreeNode<K, E>*>(v));//更新祖先索引
						_brother->key.insert(_brother->key.end(), *v->key.begin());;
						_brother->child.insert(_brother->child.end(), *v->child.begin());
						_brother->e.insert(_brother->e.end(), *v->e.begin());
						v->key.erase(v->key.begin()); v->child.erase(v->child.begin()); v->e.erase(v->e.begin());
						return;
					}
				}
				if (v->next != m_trail) {//存在右兄弟
					BAddTreeLeafNode<K, E>*_brother = v->next;
					if (_brother->child.size() < m_order) {//可移动
						updateAncestorIndex(v->key[0], _brother->key[0], *(--v->key.end()), static_cast<BAddTreeNode<K, E>*>(_brother));//更新祖先索引
						_brother->key.insert(_brother->key.begin(), *--v->key.end());;
						_brother->child.insert(_brother->child.begin(), *--v->child.end());
						_brother->e.insert(_brother->e.begin(), *--v->e.end());
						v->key.erase(--v->key.end()); v->child.erase(--v->child.end()); v->e.erase(--v->e.end());
						return;
					}
				}
				int _mc = 1.0 / 3 * (m_order - 1);
				if (v->last != m_header) {//存在左兄弟 不可借则各拿1/3m出来合并得到2/3*m 
					BAddTreeLeafNode<K, E>*_brother = v->last;
					BAddTreeLeafNode<K, E>*_nbrother = new BAddTreeLeafNode<K, E>();

					K ks = _brother->key[0]; K ke = v->key[0];
					//记录移动
					_nbrother->e.insert(_nbrother->e.end(), _brother->e.end() - _mc, _brother->e.end());
					_nbrother->e.insert(_nbrother->e.end(), v->e.begin(), v->e.begin() + _mc + 1);
					_brother->e.erase(_brother->e.end() - _mc, _brother->e.end()); v->e.erase(v->e.begin(), v->e.begin() + _mc + 1);
					//码移动
					_nbrother->key.insert(_nbrother->key.end(), _brother->key.end() - _mc, _brother->key.end());
					_nbrother->key.insert(_nbrother->key.end(), v->key.begin(), v->key.begin() + _mc + 1);
					_brother->key.erase(_brother->key.end() - _mc, _brother->key.end()); v->key.erase(v->key.begin(), v->key.begin() + _mc + 1);
					//移动分支
					_nbrother->child.insert(_nbrother->child.end(), _brother->child.end() - _mc, _brother->child.end());
					_nbrother->child.insert(_nbrother->child.end(), v->child.begin(), v->child.begin() + _mc + 1);
					_brother->child.erase(_brother->child.end() - _mc, _brother->child.end()); v->child.erase(v->child.begin(), v->child.begin() + _mc + 1);
					updateAncestorIndex(ks, ke, *v->key.begin(), static_cast<BAddTreeNode<K, E>*>(v));//更新为v最小值，因向左父节点中接入
					{
						int rank = 0; while (_brother->parent->child[rank] != static_cast<BAddTreeNode<K, E>*>(_brother))++rank;
						_brother->parent->key.insert(_brother->parent->key.begin() + rank, _nbrother->key[0]);
						_brother->parent->child.insert(_brother->parent->child.begin() + rank + 1, static_cast<BAddTreeNode<K, E>*>(_nbrother));
					}
					_nbrother->parent = _brother->parent;//向上联接
					_brother->next = _nbrother; _nbrother->next = v;
					v->last = _nbrother; _nbrother->last = _brother;

					v = static_cast<BAddTreeLeafNode<K, E>*>(_nbrother->parent);
					continue;//上溢传播
				}
				else {//存在右兄弟 不可借则各拿1/3m出来合并得到2/3*m 
					BAddTreeLeafNode<K, E>*_brother = v->next;
					BAddTreeLeafNode<K, E>*_nbrother = new BAddTreeLeafNode<K, E>();

					K ks = v->key[1]; K ke = _brother->key[1];
					//记录移动
					_nbrother->e.insert(_nbrother->e.end(), v->e.end() - _mc - 1, v->e.end());
					_nbrother->e.insert(_nbrother->e.end(), _brother->e.begin(), _brother->e.begin() + _mc);
					_brother->e.erase(_brother->e.begin(), _brother->e.begin() + _mc); v->e.erase(v->e.end() - _mc - 1, v->e.end());
					//码移动
					_nbrother->key.insert(_nbrother->key.end(), v->key.end() - _mc - 1, v->key.end());
					_nbrother->key.insert(_nbrother->key.end(), _brother->key.begin(), _brother->key.begin() + _mc);
					_brother->key.erase(_brother->key.begin(), _brother->key.begin() + _mc); v->key.erase(v->key.end() - _mc - 1, v->key.end());
					//移动分支
					_nbrother->child.insert(_nbrother->child.end(), v->child.end() - _mc - 1, v->child.end());
					_nbrother->child.insert(_nbrother->child.end(), _brother->child.begin(), _brother->child.begin() + _mc);
					_brother->child.erase(_brother->child.begin(), _brother->child.begin() + _mc); v->child.erase(v->child.end() - _mc - 1, v->child.end());
					updateAncestorIndex(ks, ke, *_nbrother->key.begin(), static_cast<BAddTreeNode<K, E>*>(_brother));//更新为_nbrother最小值，因向右父节点中接入
					{
						int rank = 0; while (_brother->parent->child[rank] != static_cast<BAddTreeNode<K, E>*>(_brother))++rank;
						_brother->parent->key.insert(_brother->parent->key.begin() + rank, _brother->key[0]);
						_brother->parent->child.insert(_brother->parent->child.begin() + rank, static_cast<BAddTreeNode<K, E>*>(_nbrother));
					}
					_nbrother->parent = _brother->parent;//向上联接
					v->next = _nbrother; _nbrother->next = _brother;
					_brother->last = _nbrother; _nbrother->last = v;

					v = static_cast<BAddTreeLeafNode<K, E>*>(_nbrother->parent);
					continue;//上溢传播
				}
			}
			else {//内部节点
				BStarTreeNode<K, E>*tv = (BStarTreeNode<K, E>*)v;//转内部节点类型
				if (tv->last) {//存在左兄弟
					BStarTreeNode<K, E>*_brother = tv->last;
					if (_brother->child.size() < m_order) {//可移动
						K k = updateAncestorIndex(_brother->key[0], tv->key[0], tv->key[0], static_cast<BAddTreeNode<K, E>*>(tv));//更新祖先索引
						_brother->key.insert(_brother->key.end(), k);;//下拉祖先索引
						_brother->child.insert(_brother->child.end(), *tv->child.begin());
						tv->key.erase(tv->key.begin()); tv->child.erase(tv->child.begin());
						//向上联接
						_brother->child[_brother->child.size() - 1]->parent = _brother;
						return;
					}
				}
				if (tv->next) {//存在右兄弟
					BStarTreeNode<K, E>*_brother = tv->next;
					if (_brother->child.size() < m_order) {//可移动
						K k = updateAncestorIndex(tv->key[0], _brother->key[0], *(--tv->key.end()), static_cast<BAddTreeNode<K, E>*>(_brother));//更新祖先索引
						_brother->key.insert(_brother->key.begin(), k);;//下拉祖先索引
						_brother->child.insert(_brother->child.begin(), *--tv->child.end());
						tv->key.erase(--tv->key.end()); tv->child.erase(--tv->child.end());
						//向上联接
						_brother->child[0]->parent = _brother;
						return;
					}
				}
				int _mc = 1.0 / 3 * (m_order - 1);
				if (tv->last) {//存在左兄弟 不可移则各拿1/3m出来合并得到2/3*m 
					BStarTreeNode<K, E>*_brother = tv->last;
					BStarTreeNode<K, E>*_nbrother = new BStarTreeNode<K, E>();
					K ks = _brother->key[0]; K ke = tv->key[0];
					K k = updateAncestorIndex(ks, ke, *(tv->key.begin() + _mc), static_cast<BAddTreeNode<K, E>*>(tv));//选择向左父节点中接入
					//码移动
					_nbrother->key.insert(_nbrother->key.end(), _brother->key.end() - _mc + 1, _brother->key.end());
					_nbrother->key.insert(_nbrother->key.end(), k);//下拉祖先索引
					_nbrother->key.insert(_nbrother->key.end(), tv->key.begin(), tv->key.begin() + _mc);
					_brother->key.erase(_brother->key.end() - _mc + 1, _brother->key.end()); tv->key.erase(tv->key.begin(), tv->key.begin() + _mc + 1);
					//移动分支
					_nbrother->child.insert(_nbrother->child.end() - 1, _brother->child.end() - _mc, _brother->child.end());
					_nbrother->child.insert(_nbrother->child.end() - 1, tv->child.begin(), tv->child.begin() + _mc);
					_brother->child.erase(_brother->child.end() - _mc, _brother->child.end()); tv->child.erase(tv->child.begin(), tv->child.begin() + _mc);
					_nbrother->child[_nbrother->child.size() - 1] = tv->child[0];
					tv->child.erase(tv->child.begin());
					{
						int rank = 0; while (_brother->parent->child[rank] != static_cast<BAddTreeNode<K, E>*>(_brother))++rank;
						_brother->parent->key.insert(_brother->parent->key.begin() + rank, *--_brother->key.end());
						_brother->key.erase(--_brother->key.end());
						_brother->parent->child.insert(_brother->parent->child.begin() + rank + 1, static_cast<BAddTreeNode<K, E>*>(_nbrother));
					}
					_nbrother->parent = _brother->parent;//向上联接
					_brother->next = _nbrother; _nbrother->next = tv;
					tv->last = _nbrother; _nbrother->last = _brother;
					//向下联接
					{
						int _s = _nbrother->child.size();
						for (int i = 0; i < _s; ++i) {
							_nbrother->child[i]->parent = static_cast<BAddTreeNode<K, E>*>(_nbrother);
						}
					}
					v = static_cast<BAddTreeLeafNode<K, E>*>(_nbrother->parent);
					continue;//上溢传播
				}
				else {//存在右兄弟 不可移动则各拿1/3m出来合并得到2/3*m 
					BStarTreeNode<K, E>*_brother = tv->next;
					BStarTreeNode<K, E>*_nbrother = new BStarTreeNode<K, E>();

					K ks = tv->key[0]; K ke = _brother->key[0];
					K k = updateAncestorIndex(ks, ke, *(tv->key.end() - _mc - 1), static_cast<BAddTreeNode<K, E>*>(_brother));//选择向右父节点中接入
					//码移动
					_nbrother->key.insert(_nbrother->key.end(), tv->key.end() - _mc, tv->key.end());
					_nbrother->key.insert(_nbrother->key.end(), k);//下拉祖先索引
					_nbrother->key.insert(_nbrother->key.end(), _brother->key.begin(), _brother->key.begin() + _mc - 1);//因为刚满，所以用祖先索引值代替一个插入值，在把最小的转为父节点的索引，即符合索引结构
					_brother->key.erase(_brother->key.begin(), _brother->key.begin() + _mc - 1); tv->key.erase(tv->key.end() - _mc - 1, v->key.end());
					//移动分支
					_nbrother->child.insert(_nbrother->child.end(), tv->child.end() - _mc, tv->child.end());
					_nbrother->child.insert(_nbrother->child.end(), _brother->child.begin(), _brother->child.begin() + _mc);
					_brother->child.erase(_brother->child.begin(), _brother->child.begin() + _mc); tv->child.erase(tv->child.end() - _mc, v->child.end());
					{
						auto it = --tv->child.end();
						_nbrother->child[0] = *it;
						tv->child.erase(it);
					}
					{
						int rank = 0; while (_brother->parent->child[rank] != static_cast<BAddTreeNode<K, E>*>(_brother))++rank;
						_brother->parent->key.insert(_brother->parent->key.begin() + rank, _brother->key[0]);
						_brother->key.erase(_brother->key.begin());
						_brother->parent->child.insert(_brother->parent->child.begin() + rank, static_cast<BAddTreeNode<K, E>*>(_nbrother));
					}
					_nbrother->parent = _brother->parent;//向上联接
					tv->next = _nbrother; _nbrother->next = _brother;
					_brother->last = _nbrother; _nbrother->last = tv;
					//向下联接
					{
						int _s = _nbrother->child.size();
						for (int i = 0; i < _s; ++i) {
							_nbrother->child[i]->parent = static_cast<BAddTreeNode<K, E>*>(_nbrother);
						}
					}
					v = static_cast<BAddTreeLeafNode<K, E>*>(_nbrother->parent);
					continue;//上溢传播
				}
			}
		}
	}
	template<typename K, typename E>
	inline void BStarTree<K, E>::solveUnderFlow(BAddTreeLeafNode<K, E>*v)
	{
		int _verge = (2.0*(m_order - 1) + 2) / 3;//向上取整
		while (v->key.size() < _verge)//下溢
		{
			BStarTreeNode<K, E>*p = static_cast<BStarTreeNode<K, E>*>(v->parent);
			if (!p) {//根节点 范围0-4/3*(m-1)个关键字
				return;
			}
			if (v->isLeaf()) {//叶子节点
				if (v->last != m_header && v->last->key.size() > _verge) {//左可借
					BAddTreeLeafNode<K, E>*_last = v->last;
					v->e.insert(v->e.begin(), *--_last->e.end());
					_last->e.erase(--_last->e.end());
					auto it = --_last->key.end();
					updateAncestorIndex(_last->key[0], v->key[0], *it, v);//更新祖先索引
					v->key.insert(v->key.begin(), *it);
					_last->key.erase(it);
					v->child.insert(v->child.begin(), *--_last->child.end());
					_last->child.erase(--_last->child.end());
					return;
				}
				if (v->next != m_trail && v->next->key.size() > _verge) {//右可借
					BAddTreeLeafNode<K, E>*_next = v->next;
					v->e.insert(v->e.end(), *_next->e.begin());
					_next->e.erase(_next->e.begin());
					v->key.insert(v->key.end(), *_next->key.begin());
					_next->key.erase(_next->key.begin());
					updateAncestorIndex(v->key[0], *--v->key.end(), _next->key[0], _next);//更新祖先索引
					v->child.insert(v->child.end(), *_next->child.begin());
					_next->child.erase(_next->child.begin());
					return;
				}
				if (v->last == m_header) {//左兄弟不存在 右兄弟不可借
					BAddTreeLeafNode<K, E>*_next = v->next;
					if (v->next->next != m_trail) {//存在右兄弟的右兄弟 则问题右移
						v->e.insert(v->e.end(), *_next->e.begin());
						_next->e.erase(_next->e.begin());
						v->key.insert(v->key.end(), *_next->key.begin());
						_next->key.erase(_next->key.begin());
						updateAncestorIndex(v->key[0], *--v->key.end(), _next->key[0], _next);//更新祖先索引
						v->child.insert(v->child.end(), *_next->child.begin());
						_next->child.erase(_next->child.begin());
						v = _next;//问题右移
						continue;//下溢传播
					}
					else {//只有2个兄弟 则合并为一个根节点
						_next->e.insert(_next->e.begin(), v->e.begin(), v->e.end());
						v->e.resize(0);//安全析构
						_next->key.insert(_next->key.begin(), v->key.begin(), v->key.end());
						_next->child.insert(_next->child.begin(), v->child.begin(), --v->child.end());
						BStarTreeNode<K, E>*_r = this->m_root;
						delete _r;
						this->m_root = (BStarTreeNode<K, E>*) _next;//新根确认
						this->m_root->parent = nullptr;//更新根性质
						m_header->next = _next; _next->next = m_trail;
						m_trail->last = _next; _next->last = m_header;//维护链表
						delete v, v = nullptr;
						return;
					}
				}
				if (v->next == m_trail) {//右兄弟不存在 左兄弟不可借 
					BAddTreeLeafNode<K, E>*_last = v->last;
					if (v->last->last != m_header) {//存在左兄弟的左兄弟 则问题左移
						v->e.insert(v->e.begin(), *--_last->e.end());
						_last->e.erase(--_last->e.end());
						auto it = --_last->key.end();
						updateAncestorIndex(_last->key[0], v->key[0], *it, v);//更新祖先索引
						v->key.insert(v->key.begin(), *it);
						_last->key.erase(it);
						v->child.insert(v->child.begin(), *--_last->child.end());
						_last->child.erase(--_last->child.end());
						v = _last;//问题左移
						continue;//下溢传播
					}
					else {//只有2个兄弟 则合并为一个根节点
						_last->e.insert(_last->e.end(), v->e.begin(), v->e.end());
						v->e.resize(0);//安全析构
						_last->key.insert(_last->key.end(), v->key.begin(), v->key.end());
						_last->child.insert(_last->child.end(), v->child.begin(), --v->child.end());
						BStarTreeNode<K, E>*_r = this->m_root;
						delete _r;
						this->m_root = (BStarTreeNode<K, E>*)_last;//新根确认
						this->m_root->parent = nullptr;//更新根性质
						m_header->next = _last; _last->next = m_trail;
						m_trail->last = _last; _last->last = m_header;//维护链表
						delete v, v = nullptr;
						return;
					}
				}
				//左右兄弟都不可借，则把v分解到左右兄弟合并为2个兄弟 这里先向左合并
				{
					//往左合并
					{
						int _mc = v->key.size() - (v->key.size()) / 2;//往左移的个数
						BAddTreeLeafNode<K, E>*_last = v->last;
						_last->e.insert(_last->e.end(), v->e.begin(), v->e.begin() + _mc);
						v->e.erase(v->e.begin(), v->e.begin() + _mc);
						updateAncestorIndex(_last->key[0], v->key[0], *(v->key.begin() + _mc), v);//更新祖先索引
						_last->key.insert(_last->key.end(), v->key.begin(), v->key.begin() + _mc);
						v->key.erase(v->key.begin(), v->key.begin() + _mc);
						_last->child.insert(_last->child.end(), v->child.begin(), v->child.begin() + _mc);
						v->child.erase(v->child.begin(), v->child.begin() + _mc);
					}
					//往右合并
					{
						BAddTreeLeafNode<K, E>*_next = v->next;
						_next->e.insert(_next->e.begin(), v->e.begin(), v->e.end());
						v->e.erase(v->e.begin(), v->e.end());
						updateAncestorIndex(v->key[0], _next->key[0], v->key[0], _next);//更新祖先索引
						_next->key.insert(_next->key.begin(), v->key.begin(), v->key.end());
						v->key.erase(v->key.begin(), v->key.end());
						_next->child.insert(_next->child.begin(), v->child.begin(), --v->child.end());
					}
					int rank = 0; while (v->parent->child[rank] != static_cast<BAddTreeNode<K, E>*>(v))++rank;
					if (rank == 0) {
						v->parent->key.erase(v->parent->key.begin());
					}
					else {
						v->parent->key.erase(v->parent->key.begin() + rank - 1);
					}
					v->parent->child.erase(v->parent->child.begin() + rank);
					v->last->next = v->next; v->next->last = v->last;//维护链表
					delete v, v = nullptr;
					v = (BAddTreeLeafNode<K, E>*)p;
					continue;//下溢传播
					return;
				}
			}
			else {//内部节点
				BStarTreeNode<K, E>*tv = (BStarTreeNode<K, E>*)v;
				if (tv->last  && tv->last->key.size() > _verge) {//左可借
					BStarTreeNode<K, E>*_last = tv->last;
					auto it = --_last->key.end();
					K k = updateAncestorIndex(_last->key[0], tv->key[0], *it, tv);//更新祖先索引
					tv->key.insert(tv->key.begin(), k);
					_last->key.erase(it);
					tv->child.insert(tv->child.begin(), *--_last->child.end());
					_last->child.erase(--_last->child.end());
					//向下联接
					tv->child[0]->parent = static_cast<BAddTreeNode<K, E>*>(tv);
					return;
				}
				if (tv->next && tv->next->key.size() > _verge) {//右可借
					BStarTreeNode<K, E>*_next = tv->next;
					K k = updateAncestorIndex(tv->key[0], _next->key[0], _next->key[0], _next);//更新祖先索引
					tv->key.insert(tv->key.end(), k);
					_next->key.erase(_next->key.begin());
					tv->child.insert(tv->child.end(), *_next->child.begin());
					_next->child.erase(_next->child.begin());
					//向下联接
					tv->child[tv->child.size() - 1]->parent = static_cast<BAddTreeNode<K, E>*>(tv);
					return;
				}
				if (!tv->last) {//左兄弟不存在 右兄弟不可借
					BStarTreeNode<K, E>*_next = tv->next;
					if (tv->next->next) {//存在右兄弟的右兄弟 则问题右移
						K k = updateAncestorIndex(tv->key[0], _next->key[0], _next->key[0], _next);//更新祖先索引
						tv->key.insert(tv->key.end(), k);
						_next->key.erase(_next->key.begin());
						tv->child.insert(tv->child.end(), *_next->child.begin());
						_next->child.erase(_next->child.begin());
						//向下联接
						tv->child[tv->child.size() - 1]->parent = static_cast<BAddTreeNode<K, E>*>(tv);
						v = (BAddTreeLeafNode<K, E>*)_next;//问题右移
						continue;//下溢传播
					}
					else {//只有2个兄弟 父节点即为根 则合并为一个根节点
						BStarTreeNode<K, E>*_r = this->m_root;
						_next->key.insert(_next->key.begin(), _r->key[0]);//下拉根节点索引
						delete _r;
						_next->key.insert(_next->key.begin(), tv->key.begin(), tv->key.end());
						//向下联接
						{
							int _s = tv->child.size();
							for (int i = 0; i < _s; ++i)
								tv->child[i]->parent = static_cast<BAddTreeNode<K, E>*>(_next);
						}
						_next->child.insert(_next->child.begin(), tv->child.begin(), tv->child.end());
						this->m_root = _next;//新根确认
						this->m_root->parent = nullptr;//更新根性质
						_next->last = nullptr; _next->next = nullptr;
						delete tv, tv = nullptr;
						return;
					}
				}
				if (!tv->next) {//右兄弟不存在 左兄弟不可借 
					BStarTreeNode<K, E>*_last = tv->last;
					if (tv->last->last) {//存在左兄弟的左兄弟 则问题左移
						auto it = --_last->key.end();
						K k = updateAncestorIndex(_last->key[0], tv->key[0], *it, tv);//更新祖先索引
						tv->key.insert(tv->key.begin(), k);
						_last->key.erase(it);
						tv->child.insert(tv->child.begin(), *--_last->child.end());
						_last->child.erase(--_last->child.end());
						//向下联接
						tv->child[0]->parent = static_cast<BAddTreeNode<K, E>*>(tv);
						v = (BAddTreeLeafNode<K, E>*)_last;//问题左移
						continue;//下溢传播
					}
					else {//只有2个兄弟 则合并为一个根节点
						BStarTreeNode<K, E>*_r = this->m_root;
						_last->key.insert(_last->key.end(), _r->key[0]);
						delete _r;
						_last->key.insert(_last->key.end(), tv->key.begin(), tv->key.end());
						//向下联接
						{
							int _s = tv->child.size();
							for (int i = 0; i < _s; ++i)
								tv->child[i]->parent = static_cast<BAddTreeNode<K, E>*>(_last);
						}
						_last->child.insert(_last->child.end(), tv->child.begin(), tv->child.end());
						this->m_root = (BStarTreeNode<K, E>*)_last;//新根确认
						this->m_root->parent = nullptr;//更新根性质
						delete tv, tv = nullptr;
						return;
					}
				}
				//左右兄弟都不可借，则把v分解到左右兄弟合并为2个兄弟 这里先向左合并
				{
					//往左合并
					{
						int _mc = tv->key.size() - (tv->key.size()) / 2;//往左移的个数
						BStarTreeNode<K, E>*_last = tv->last;
						K k = updateAncestorIndex(_last->key[0], tv->key[0], *(tv->key.begin() + _mc - 1), tv);//更新祖先索引
						_last->key.insert(_last->key.end(), k);//下拉祖先索引
						_last->key.insert(_last->key.end(), tv->key.begin(), tv->key.begin() + _mc - 1);
						tv->key.erase(tv->key.begin(), tv->key.begin() + _mc);
						//向下联接
						{
							auto it = tv->child.begin();
							auto ite = tv->child.begin() + _mc;
							while (it != ite)
							{
								(*it)->parent = static_cast<BAddTreeNode<K, E>*>(_last);
								++it;
							}
						}
						_last->child.insert(_last->child.end(), tv->child.begin(), tv->child.begin() + _mc);
						tv->child.erase(tv->child.begin(), tv->child.begin() + _mc);
					}
					//往右合并
					{
						BStarTreeNode<K, E>*_next = tv->next;
						//首先先找出要随着v删除而删除的父节点中对应索引来替换掉v和右兄弟第一个共同祖先的对应索引
						int rank = 0; while (tv->parent->child[rank] != static_cast<BAddTreeNode<K, E>*>(tv))++rank;
						K k;
						if (rank == 0) {
							k = updateAncestorIndex(tv->key[0], _next->key[0], *tv->parent->key.begin(), _next);//获取祖父索引
							tv->parent->key.erase(tv->parent->key.begin());
						}
						else {
							k = updateAncestorIndex(tv->key[0], _next->key[0], *(tv->parent->key.begin() + rank - 1), _next);//获取祖父索引
							tv->parent->key.erase(tv->parent->key.begin() + rank - 1);
						}
						_next->key.insert(_next->key.begin(), k);//下拉祖先索引
						_next->key.insert(_next->key.begin(), tv->key.begin(), tv->key.end());
						//向下联接
						{
							auto it = tv->child.begin();
							auto ite = tv->child.end();
							while (it != ite)
							{
								(*it)->parent = static_cast<BAddTreeNode<K, E>*>(_next);
								++it;
							}
						}
						_next->child.insert(_next->child.begin(), tv->child.begin(), tv->child.end());
						tv->parent->child.erase(tv->parent->child.begin() + rank);
						tv->last->next = tv->next; tv->next->last = tv->last;//维护链表
						delete tv, tv = nullptr;
						//由于设计问题 2边为2/3的索引最大个数，中间个数为2/3索引最大个数-1，索引如此合并，右分支发生上溢，则需要做上溢调整
						v = (BAddTreeLeafNode<K, E>*)_next;
						solveOverFlow(v);//上溢处理
						v = (BAddTreeLeafNode<K, E>*)(p);
						continue;//下溢传播
					}
					return;
				}
			}
		}
	}
	template<typename K, typename E>
	inline K BStarTree<K, E>::updateAncestorIndex(K const & _min, K const & _max, K&_v, BAddTreeNode<K, E>* p)
	{
		while ((p = p->parent))
		{
			if (p->key[0] <= _max) {
				int _s = p->key.size();
				for (int i = 0; i < _s; ++i) {
					K k = p->key[i];
					if (_min < k&&k <= _max) {
						p->key[i] = _v;//更新索引;
						return k;
					}
				}
			}
		}
		return K();
	}

	template<typename K, typename E>
	template<typename Visist>
	inline void BStarTree<K, E>::list_traversal(Visist visit)
	{
		BAddTreeLeafNode<K, E>*p = m_header;
		while ((p = p->next) != m_trail) {
			visit(p->e);
		}
	}
}

#endif // !BSTARTREE_H_H_H

