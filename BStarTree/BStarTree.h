#ifndef BSTARTREE_H_H_H
#define BSTARTREE_H_H_H 

/*
B*��
K����,E�Ǽ�¼
E���ͱ���ʵ�ֺ�����K key()������
��B+����ͬ����ÿ���ڲ��ڵ���ָ���ֵܵ�ָ�룬�ڵ�ֻ�д���ceil(2/3*m)�ŷ�������
mȡֵ����ϲ�������Ҫ�ƶ������ͺ��ӷ�֧��Ϊ�˷��㣬��СҪ�ƶ�1,��1/3*m>=1,�����趨m>=3������B����m>=2��
�������趨��ԭ������Ϊ�˷���ѡ�����ƶ�1/3*(m-1)��������m>=4
ͬʱΪ�˼�����3�ֵܺϲ�ʱ�ֽ���������ٱ�֤�ֽ�ڵ�������������2����ceil(2/3*(m-1))-1>=2,����m>=6
ע�����������������⣬ʵ���˹��ܣ��������m>=7
ʵ��˼·��ͬB+���������ⲿ�ڵ�,���ڲ��ڵ���ⲿ�ڵ����ִ���
������ʱ�����ڵ���4/3(m-1)Ϊ�ٽ�㷢�����ѣ���ǡ�ÿ��Է���Ϊ2��2/3(m-1)��
�ڵ����ж������ֵ��Ƿ���ƶ�����������ͬһ���ֵܸ���1/3�ϲ���
������ʱ�����ֻ��2���ֵ���ϲ�Ϊ���ڵ㣬���ɵõ�4/3(m-1)����,
���ж������ֵ��Ƿ�ɽ裬������������������������������������ƻ����ƣ�����ѽڵ�ֽ⵽�����ֵܣ�
�õ��ӽ�(m-1)����ֵ�������ڲ��ڵ㣬�ᵼ��ĳ���ֵܷ������磬����һ�����紦��
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
		explicit BStarTree(int order = 256);//��С��7ʱĬ��Ϊ7��(m>=7)
		~BStarTree();

		int const order()const;//�״�
		int const size()const;//��ģ

			//�����ӿ�
		Entry find(E const&, bool&ok)const;//����
		Entry find(E const&)const;//����
		bool insert(E const&);//����
		bool remove(E const&);//ɾ��

		template<typename Visist>
		void list_traversal(Visist);//����
	private:
		BAddTreeLeafNode<K, E>*  search(E const&);//����
		void solveOverFlow(BAddTreeLeafNode<K, E>*);//��������������� ����Ϊ�ڵ�
		void solveUnderFlow(BAddTreeLeafNode<K, E>*);//��������������� ����Ϊ�ڵ�
		K updateAncestorIndex(K const&_min, K const&_max, K&_v, BAddTreeNode<K, E>*p);//����p���Ƚڵ���Ψһ����_minͬʱС�ڵ���_max������Ϊ_v�����ؾ�����

	private:
		int m_size;//�ؼ�������
		int m_order;//B-���Ľ״�,����Ϊ2(���˻�Ϊ����������) ����ʱָ�� һ�㲻���޸�
		BStarTreeNode<K, E>* m_root;//����
		BStarTreeNode<K, E>* m_hitParentNode;//���ҷ���ʱ���нڵ�ĸ��׻��ߴ�͸�ײ�����һ�����ʵĽڵ㣬����Ϊ��ʱ ����ʺ�Ϊ��
		BAddTreeLeafNode<K, E>*m_header, *m_trail;//˫��������β
	};
	template<typename K, typename E>
	inline BStarTree<K, E>::BStarTree(int order)
	{
		if (order < 7)order = 7;//Ĭ��7��
		m_order = order;
		//ע������ʼ��ΪҶ�ӽڵ�
		this->m_root = (BStarTreeNode<K, E>*)new BAddTreeLeafNode<K, E>(); m_size = 0; m_hitParentNode = nullptr;
		m_header = new BAddTreeLeafNode<K, E>();
		m_trail = new BAddTreeLeafNode<K, E>();
		BAddTreeLeafNode<K, E>*_leaf = (BAddTreeLeafNode<K, E>*)(this->m_root);
		m_header->next = _leaf; m_trail->last = _leaf;//����
		_leaf->last = m_header; _leaf->next = m_trail;
	}
	template<typename K, typename E>
	inline BStarTree<K, E>::~BStarTree()
	{
		if (!this->m_root)return;//û�и��Ͳ�ɾ��
		std::queue<BStarTreeNode<K, E>*>q;//���븨�����а���α���ɾ��
		q.push(this->m_root);//�������
		while (!q.empty())
		{
			BStarTreeNode<K, E>*p = q.front();
			q.pop();
			int count = p->child.size();
			for (int i = 0; i < count; ++i) {
				if (p->child[i]) {
					q.push(static_cast<BStarTreeNode<K, E>*>(p->child[i]));//������к������
				}
			}
			if (p->isLeaf()) {
				BAddTreeLeafNode<K, E>*_t = (BAddTreeLeafNode<K, E>*)p;
				delete _t, _t = nullptr;//����Ҷ�ӽڵ�
			}
			else {
				delete p, p = nullptr;//�ͷ�ÿ���ڲ��ڵ�
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
		BAddTreeLeafNode<K, E>*v = (BAddTreeLeafNode<K, E>*)(this->m_root);//cʽǿ��ת��
		while (!v->isLeaf())
		{
			int _s = v->key.size();
			int i = 0;
			for (; i < _s; ++i) {
				K&tk = v->key[i];
				if (tk > k)break;
			}
			v = static_cast<BAddTreeLeafNode<K, E>*>(v->child[i]);//ת����һ��
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
			v = (BAddTreeLeafNode<K, E>*)(v->child[i]);//ת����һ��
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
		//����
		K k = e.key();
		v = (BAddTreeLeafNode<K, E>*)(this->m_hitParentNode);
		int _s = v->key.size();
		int i = 0;
		for (; i < _s; ++i) {
			K&tk = v->key[i];
			if (tk > k)break;
		}
		v->key.insert(v->key.begin() + i, k);//����ؼ���
		++this->m_size;//���¹�ģ
		v->child.insert(v->child.begin() + i + 1, nullptr);//����շ�֧
		E*_e = new E();
		*_e = std::move(e);//ʹ����ֵ�ƶ�
		v->e.insert(v->e.begin() + i, _e);//�����¼
		solveOverFlow(v);//���������
		return true;
	}
	template<typename K, typename E>
	inline bool BStarTree<K, E>::remove(E const &e)
	{
		BAddTreeLeafNode<K, E>*v = search(e);
		if (!v)
			return false;
		int rank = 0; while (v->key[rank] != e.key())++rank;
		//ɾ��
		v->key.erase(v->key.begin() + rank);//ɾ���ؼ���
		E*_e = v->e[rank];
		v->e.erase(v->e.begin() + rank);//ɾ����¼
		--this->m_size;
		delete _e;//�ͷż�¼
		v->child.erase(v->child.begin() + rank + 1);//ɾ����֧
		solveUnderFlow(v);//�������
		return true;
	}

	template<typename K, typename E>
	inline BAddTreeLeafNode<K, E>* BStarTree<K, E>::search(E const &e)
	{
		this->m_hitParentNode = nullptr;
		K k = e.key();
		//std::cout << "\nsearch:\n";
		BAddTreeLeafNode<K, E>*v = (BAddTreeLeafNode<K, E>*)(this->m_root);//cʽǿ��ת��
		int x = 0;
		while (!v->isLeaf())
		{
			int _s = v->key.size();
			int i = 0;
			//printf("��%d��\n",x++);
			for (; i < _s; ++i) {
				K&tk = v->key[i];
				//std::cout <<tk <<" ";
				if (tk > k)break;
			}
			//printf("\n");
			this->m_hitParentNode = (BStarTreeNode<K, E>*)(v);
			v = static_cast<BAddTreeLeafNode<K, E>*>(v->child[i]);//ת����һ��
		}
		if (v&&v->isLeaf()) {
			//std::cout << "\nleaf��\n";
			int _s = v->key.size();
			int i = 0;
			for (; i < _s; ++i) {
				K&tk = v->key[i];
				//std::cout <<tk <<" <-leaf- ";
				if (tk == k) {
					//	std::cout << tk<<" <-����- ";
					return v;
				}
				else if (tk > k)
					break;
			}

			this->m_hitParentNode = (BStarTreeNode<K, E>*)(v);
			v = (BAddTreeLeafNode<K, E>*)(v->child[i]);//ת����һ��
		}
		//std::cout <<"\n ";
		return v;
	}

	template<typename K, typename E>
	inline void BStarTree<K, E>::solveOverFlow(BAddTreeLeafNode<K, E>*v)
	{
		while (v->key.size() > m_order - 1)//����
		{
			BStarTreeNode<K, E>*p = static_cast<BStarTreeNode<K, E>*>(v->parent);
			if (!p) {//���ڵ�
				int _verge = (2.0*(m_order - 1) + 2) / 3;//����ȡ��
				if (v->isLeaf()) {//Ҷ�ڵ����
					if ((_verge) * 2 <= v->key.size()) {//���ڵ��������Ϊ4/3*m-1��ǡ�ÿ��Է���Ϊ2��2/3*m�Ľڵ�
						//�����ֵܽڵ�
						BAddTreeLeafNode<K, E>* _right = new BAddTreeLeafNode<K, E>();
						_right->key.insert(_right->key.end(), v->key.end() - _verge, v->key.end());
						v->key.erase(v->key.end() - _verge, v->key.end());
						_right->e.insert(_right->e.end(), v->e.end() - _verge, v->e.end());
						v->e.erase(v->e.end() - _verge, v->e.end());
						_right->child.insert(_right->child.end(), v->child.end() - _verge, v->child.end());
						v->child.erase(v->child.end() - _verge, v->child.end());
						this->m_root = new BStarTreeNode<K, E>();
						this->m_root->child.insert(this->m_root->child.end(), static_cast<BAddTreeNode<K, E>*>(_right));//����ֵܷ�֧
						this->m_root->child[0] = static_cast<BAddTreeNode<K, E>*>(v);
						v->parent = this->m_root; _right->parent = this->m_root;//��������
						this->m_root->key.insert(this->m_root->key.end(), _right->key[0]);//��������
						v->next->last = _right; _right->next = v->next;
						v->next = _right; _right->last = v;
					}
				}
				else {
					if ((_verge) * 2 < v->key.size()) {//���ڵ��������Ϊ4/3*m��ǡ�ÿ��Է���Ϊ2��2/3*m�Ľڵ�
						//�����ֵܽڵ�
						BStarTreeNode<K, E>*tv = (BStarTreeNode<K, E>*)v;
						BStarTreeNode<K, E>* _right = new BStarTreeNode<K, E>();
						_right->key.insert(_right->key.end(), tv->key.end() - _verge, tv->key.end());
						tv->key.erase(tv->key.end() - _verge, tv->key.end());
						_right->child.insert(_right->child.end(), tv->child.end() - _verge, tv->child.end());
						tv->child.erase(tv->child.end() - _verge, tv->child.end());
						_right->child[0] = *--tv->child.end();
						tv->child.erase(--tv->child.end());
						this->m_root = new BStarTreeNode<K, E>();
						this->m_root->child.insert(this->m_root->child.end(), static_cast<BAddTreeNode<K, E>*>(_right));//����ֵܷ�֧
						this->m_root->child[0] = static_cast<BAddTreeNode<K, E>*>(tv);
						tv->parent = this->m_root; _right->parent = this->m_root;//��������
						this->m_root->key.insert(this->m_root->key.end(), *--tv->key.end());//��������
						tv->key.erase(--tv->key.end());
						{
							int _s = _right->child.size();
							for (int i = 0; i < _s; ++i)
								_right->child[i]->parent = static_cast<BAddTreeNode<K, E>*>(_right);//��������
						}
						if (tv->next)tv->next->last = _right;
						_right->next = tv->next;
						tv->next = _right; _right->last = tv;
					}
				}
				return;
			}

			if (v->isLeaf()) {//Ҷ�ڵ�
				if (v->last != m_header) {//�������ֵ�
					BAddTreeLeafNode<K, E>*_brother = v->last;
					if (_brother->child.size() < m_order) {//���ƶ�
						updateAncestorIndex(_brother->key[0], v->key[0], *(v->key.begin() + 1), static_cast<BAddTreeNode<K, E>*>(v));//������������
						_brother->key.insert(_brother->key.end(), *v->key.begin());;
						_brother->child.insert(_brother->child.end(), *v->child.begin());
						_brother->e.insert(_brother->e.end(), *v->e.begin());
						v->key.erase(v->key.begin()); v->child.erase(v->child.begin()); v->e.erase(v->e.begin());
						return;
					}
				}
				if (v->next != m_trail) {//�������ֵ�
					BAddTreeLeafNode<K, E>*_brother = v->next;
					if (_brother->child.size() < m_order) {//���ƶ�
						updateAncestorIndex(v->key[0], _brother->key[0], *(--v->key.end()), static_cast<BAddTreeNode<K, E>*>(_brother));//������������
						_brother->key.insert(_brother->key.begin(), *--v->key.end());;
						_brother->child.insert(_brother->child.begin(), *--v->child.end());
						_brother->e.insert(_brother->e.begin(), *--v->e.end());
						v->key.erase(--v->key.end()); v->child.erase(--v->child.end()); v->e.erase(--v->e.end());
						return;
					}
				}
				int _mc = 1.0 / 3 * (m_order - 1);
				if (v->last != m_header) {//�������ֵ� ���ɽ������1/3m�����ϲ��õ�2/3*m 
					BAddTreeLeafNode<K, E>*_brother = v->last;
					BAddTreeLeafNode<K, E>*_nbrother = new BAddTreeLeafNode<K, E>();

					K ks = _brother->key[0]; K ke = v->key[0];
					//��¼�ƶ�
					_nbrother->e.insert(_nbrother->e.end(), _brother->e.end() - _mc, _brother->e.end());
					_nbrother->e.insert(_nbrother->e.end(), v->e.begin(), v->e.begin() + _mc + 1);
					_brother->e.erase(_brother->e.end() - _mc, _brother->e.end()); v->e.erase(v->e.begin(), v->e.begin() + _mc + 1);
					//���ƶ�
					_nbrother->key.insert(_nbrother->key.end(), _brother->key.end() - _mc, _brother->key.end());
					_nbrother->key.insert(_nbrother->key.end(), v->key.begin(), v->key.begin() + _mc + 1);
					_brother->key.erase(_brother->key.end() - _mc, _brother->key.end()); v->key.erase(v->key.begin(), v->key.begin() + _mc + 1);
					//�ƶ���֧
					_nbrother->child.insert(_nbrother->child.end(), _brother->child.end() - _mc, _brother->child.end());
					_nbrother->child.insert(_nbrother->child.end(), v->child.begin(), v->child.begin() + _mc + 1);
					_brother->child.erase(_brother->child.end() - _mc, _brother->child.end()); v->child.erase(v->child.begin(), v->child.begin() + _mc + 1);
					updateAncestorIndex(ks, ke, *v->key.begin(), static_cast<BAddTreeNode<K, E>*>(v));//����Ϊv��Сֵ�������󸸽ڵ��н���
					{
						int rank = 0; while (_brother->parent->child[rank] != static_cast<BAddTreeNode<K, E>*>(_brother))++rank;
						_brother->parent->key.insert(_brother->parent->key.begin() + rank, _nbrother->key[0]);
						_brother->parent->child.insert(_brother->parent->child.begin() + rank + 1, static_cast<BAddTreeNode<K, E>*>(_nbrother));
					}
					_nbrother->parent = _brother->parent;//��������
					_brother->next = _nbrother; _nbrother->next = v;
					v->last = _nbrother; _nbrother->last = _brother;

					v = static_cast<BAddTreeLeafNode<K, E>*>(_nbrother->parent);
					continue;//���紫��
				}
				else {//�������ֵ� ���ɽ������1/3m�����ϲ��õ�2/3*m 
					BAddTreeLeafNode<K, E>*_brother = v->next;
					BAddTreeLeafNode<K, E>*_nbrother = new BAddTreeLeafNode<K, E>();

					K ks = v->key[1]; K ke = _brother->key[1];
					//��¼�ƶ�
					_nbrother->e.insert(_nbrother->e.end(), v->e.end() - _mc - 1, v->e.end());
					_nbrother->e.insert(_nbrother->e.end(), _brother->e.begin(), _brother->e.begin() + _mc);
					_brother->e.erase(_brother->e.begin(), _brother->e.begin() + _mc); v->e.erase(v->e.end() - _mc - 1, v->e.end());
					//���ƶ�
					_nbrother->key.insert(_nbrother->key.end(), v->key.end() - _mc - 1, v->key.end());
					_nbrother->key.insert(_nbrother->key.end(), _brother->key.begin(), _brother->key.begin() + _mc);
					_brother->key.erase(_brother->key.begin(), _brother->key.begin() + _mc); v->key.erase(v->key.end() - _mc - 1, v->key.end());
					//�ƶ���֧
					_nbrother->child.insert(_nbrother->child.end(), v->child.end() - _mc - 1, v->child.end());
					_nbrother->child.insert(_nbrother->child.end(), _brother->child.begin(), _brother->child.begin() + _mc);
					_brother->child.erase(_brother->child.begin(), _brother->child.begin() + _mc); v->child.erase(v->child.end() - _mc - 1, v->child.end());
					updateAncestorIndex(ks, ke, *_nbrother->key.begin(), static_cast<BAddTreeNode<K, E>*>(_brother));//����Ϊ_nbrother��Сֵ�������Ҹ��ڵ��н���
					{
						int rank = 0; while (_brother->parent->child[rank] != static_cast<BAddTreeNode<K, E>*>(_brother))++rank;
						_brother->parent->key.insert(_brother->parent->key.begin() + rank, _brother->key[0]);
						_brother->parent->child.insert(_brother->parent->child.begin() + rank, static_cast<BAddTreeNode<K, E>*>(_nbrother));
					}
					_nbrother->parent = _brother->parent;//��������
					v->next = _nbrother; _nbrother->next = _brother;
					_brother->last = _nbrother; _nbrother->last = v;

					v = static_cast<BAddTreeLeafNode<K, E>*>(_nbrother->parent);
					continue;//���紫��
				}
			}
			else {//�ڲ��ڵ�
				BStarTreeNode<K, E>*tv = (BStarTreeNode<K, E>*)v;//ת�ڲ��ڵ�����
				if (tv->last) {//�������ֵ�
					BStarTreeNode<K, E>*_brother = tv->last;
					if (_brother->child.size() < m_order) {//���ƶ�
						K k = updateAncestorIndex(_brother->key[0], tv->key[0], tv->key[0], static_cast<BAddTreeNode<K, E>*>(tv));//������������
						_brother->key.insert(_brother->key.end(), k);;//������������
						_brother->child.insert(_brother->child.end(), *tv->child.begin());
						tv->key.erase(tv->key.begin()); tv->child.erase(tv->child.begin());
						//��������
						_brother->child[_brother->child.size() - 1]->parent = _brother;
						return;
					}
				}
				if (tv->next) {//�������ֵ�
					BStarTreeNode<K, E>*_brother = tv->next;
					if (_brother->child.size() < m_order) {//���ƶ�
						K k = updateAncestorIndex(tv->key[0], _brother->key[0], *(--tv->key.end()), static_cast<BAddTreeNode<K, E>*>(_brother));//������������
						_brother->key.insert(_brother->key.begin(), k);;//������������
						_brother->child.insert(_brother->child.begin(), *--tv->child.end());
						tv->key.erase(--tv->key.end()); tv->child.erase(--tv->child.end());
						//��������
						_brother->child[0]->parent = _brother;
						return;
					}
				}
				int _mc = 1.0 / 3 * (m_order - 1);
				if (tv->last) {//�������ֵ� �����������1/3m�����ϲ��õ�2/3*m 
					BStarTreeNode<K, E>*_brother = tv->last;
					BStarTreeNode<K, E>*_nbrother = new BStarTreeNode<K, E>();
					K ks = _brother->key[0]; K ke = tv->key[0];
					K k = updateAncestorIndex(ks, ke, *(tv->key.begin() + _mc), static_cast<BAddTreeNode<K, E>*>(tv));//ѡ�����󸸽ڵ��н���
					//���ƶ�
					_nbrother->key.insert(_nbrother->key.end(), _brother->key.end() - _mc + 1, _brother->key.end());
					_nbrother->key.insert(_nbrother->key.end(), k);//������������
					_nbrother->key.insert(_nbrother->key.end(), tv->key.begin(), tv->key.begin() + _mc);
					_brother->key.erase(_brother->key.end() - _mc + 1, _brother->key.end()); tv->key.erase(tv->key.begin(), tv->key.begin() + _mc + 1);
					//�ƶ���֧
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
					_nbrother->parent = _brother->parent;//��������
					_brother->next = _nbrother; _nbrother->next = tv;
					tv->last = _nbrother; _nbrother->last = _brother;
					//��������
					{
						int _s = _nbrother->child.size();
						for (int i = 0; i < _s; ++i) {
							_nbrother->child[i]->parent = static_cast<BAddTreeNode<K, E>*>(_nbrother);
						}
					}
					v = static_cast<BAddTreeLeafNode<K, E>*>(_nbrother->parent);
					continue;//���紫��
				}
				else {//�������ֵ� �����ƶ������1/3m�����ϲ��õ�2/3*m 
					BStarTreeNode<K, E>*_brother = tv->next;
					BStarTreeNode<K, E>*_nbrother = new BStarTreeNode<K, E>();

					K ks = tv->key[0]; K ke = _brother->key[0];
					K k = updateAncestorIndex(ks, ke, *(tv->key.end() - _mc - 1), static_cast<BAddTreeNode<K, E>*>(_brother));//ѡ�����Ҹ��ڵ��н���
					//���ƶ�
					_nbrother->key.insert(_nbrother->key.end(), tv->key.end() - _mc, tv->key.end());
					_nbrother->key.insert(_nbrother->key.end(), k);//������������
					_nbrother->key.insert(_nbrother->key.end(), _brother->key.begin(), _brother->key.begin() + _mc - 1);//��Ϊ��������������������ֵ����һ������ֵ���ڰ���С��תΪ���ڵ�������������������ṹ
					_brother->key.erase(_brother->key.begin(), _brother->key.begin() + _mc - 1); tv->key.erase(tv->key.end() - _mc - 1, v->key.end());
					//�ƶ���֧
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
					_nbrother->parent = _brother->parent;//��������
					tv->next = _nbrother; _nbrother->next = _brother;
					_brother->last = _nbrother; _nbrother->last = tv;
					//��������
					{
						int _s = _nbrother->child.size();
						for (int i = 0; i < _s; ++i) {
							_nbrother->child[i]->parent = static_cast<BAddTreeNode<K, E>*>(_nbrother);
						}
					}
					v = static_cast<BAddTreeLeafNode<K, E>*>(_nbrother->parent);
					continue;//���紫��
				}
			}
		}
	}
	template<typename K, typename E>
	inline void BStarTree<K, E>::solveUnderFlow(BAddTreeLeafNode<K, E>*v)
	{
		int _verge = (2.0*(m_order - 1) + 2) / 3;//����ȡ��
		while (v->key.size() < _verge)//����
		{
			BStarTreeNode<K, E>*p = static_cast<BStarTreeNode<K, E>*>(v->parent);
			if (!p) {//���ڵ� ��Χ0-4/3*(m-1)���ؼ���
				return;
			}
			if (v->isLeaf()) {//Ҷ�ӽڵ�
				if (v->last != m_header && v->last->key.size() > _verge) {//��ɽ�
					BAddTreeLeafNode<K, E>*_last = v->last;
					v->e.insert(v->e.begin(), *--_last->e.end());
					_last->e.erase(--_last->e.end());
					auto it = --_last->key.end();
					updateAncestorIndex(_last->key[0], v->key[0], *it, v);//������������
					v->key.insert(v->key.begin(), *it);
					_last->key.erase(it);
					v->child.insert(v->child.begin(), *--_last->child.end());
					_last->child.erase(--_last->child.end());
					return;
				}
				if (v->next != m_trail && v->next->key.size() > _verge) {//�ҿɽ�
					BAddTreeLeafNode<K, E>*_next = v->next;
					v->e.insert(v->e.end(), *_next->e.begin());
					_next->e.erase(_next->e.begin());
					v->key.insert(v->key.end(), *_next->key.begin());
					_next->key.erase(_next->key.begin());
					updateAncestorIndex(v->key[0], *--v->key.end(), _next->key[0], _next);//������������
					v->child.insert(v->child.end(), *_next->child.begin());
					_next->child.erase(_next->child.begin());
					return;
				}
				if (v->last == m_header) {//���ֵܲ����� ���ֵܲ��ɽ�
					BAddTreeLeafNode<K, E>*_next = v->next;
					if (v->next->next != m_trail) {//�������ֵܵ����ֵ� ����������
						v->e.insert(v->e.end(), *_next->e.begin());
						_next->e.erase(_next->e.begin());
						v->key.insert(v->key.end(), *_next->key.begin());
						_next->key.erase(_next->key.begin());
						updateAncestorIndex(v->key[0], *--v->key.end(), _next->key[0], _next);//������������
						v->child.insert(v->child.end(), *_next->child.begin());
						_next->child.erase(_next->child.begin());
						v = _next;//��������
						continue;//���紫��
					}
					else {//ֻ��2���ֵ� ��ϲ�Ϊһ�����ڵ�
						_next->e.insert(_next->e.begin(), v->e.begin(), v->e.end());
						v->e.resize(0);//��ȫ����
						_next->key.insert(_next->key.begin(), v->key.begin(), v->key.end());
						_next->child.insert(_next->child.begin(), v->child.begin(), --v->child.end());
						BStarTreeNode<K, E>*_r = this->m_root;
						delete _r;
						this->m_root = (BStarTreeNode<K, E>*) _next;//�¸�ȷ��
						this->m_root->parent = nullptr;//���¸�����
						m_header->next = _next; _next->next = m_trail;
						m_trail->last = _next; _next->last = m_header;//ά������
						delete v, v = nullptr;
						return;
					}
				}
				if (v->next == m_trail) {//���ֵܲ����� ���ֵܲ��ɽ� 
					BAddTreeLeafNode<K, E>*_last = v->last;
					if (v->last->last != m_header) {//�������ֵܵ����ֵ� ����������
						v->e.insert(v->e.begin(), *--_last->e.end());
						_last->e.erase(--_last->e.end());
						auto it = --_last->key.end();
						updateAncestorIndex(_last->key[0], v->key[0], *it, v);//������������
						v->key.insert(v->key.begin(), *it);
						_last->key.erase(it);
						v->child.insert(v->child.begin(), *--_last->child.end());
						_last->child.erase(--_last->child.end());
						v = _last;//��������
						continue;//���紫��
					}
					else {//ֻ��2���ֵ� ��ϲ�Ϊһ�����ڵ�
						_last->e.insert(_last->e.end(), v->e.begin(), v->e.end());
						v->e.resize(0);//��ȫ����
						_last->key.insert(_last->key.end(), v->key.begin(), v->key.end());
						_last->child.insert(_last->child.end(), v->child.begin(), --v->child.end());
						BStarTreeNode<K, E>*_r = this->m_root;
						delete _r;
						this->m_root = (BStarTreeNode<K, E>*)_last;//�¸�ȷ��
						this->m_root->parent = nullptr;//���¸�����
						m_header->next = _last; _last->next = m_trail;
						m_trail->last = _last; _last->last = m_header;//ά������
						delete v, v = nullptr;
						return;
					}
				}
				//�����ֵܶ����ɽ裬���v�ֽ⵽�����ֵܺϲ�Ϊ2���ֵ� ����������ϲ�
				{
					//����ϲ�
					{
						int _mc = v->key.size() - (v->key.size()) / 2;//�����Ƶĸ���
						BAddTreeLeafNode<K, E>*_last = v->last;
						_last->e.insert(_last->e.end(), v->e.begin(), v->e.begin() + _mc);
						v->e.erase(v->e.begin(), v->e.begin() + _mc);
						updateAncestorIndex(_last->key[0], v->key[0], *(v->key.begin() + _mc), v);//������������
						_last->key.insert(_last->key.end(), v->key.begin(), v->key.begin() + _mc);
						v->key.erase(v->key.begin(), v->key.begin() + _mc);
						_last->child.insert(_last->child.end(), v->child.begin(), v->child.begin() + _mc);
						v->child.erase(v->child.begin(), v->child.begin() + _mc);
					}
					//���Һϲ�
					{
						BAddTreeLeafNode<K, E>*_next = v->next;
						_next->e.insert(_next->e.begin(), v->e.begin(), v->e.end());
						v->e.erase(v->e.begin(), v->e.end());
						updateAncestorIndex(v->key[0], _next->key[0], v->key[0], _next);//������������
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
					v->last->next = v->next; v->next->last = v->last;//ά������
					delete v, v = nullptr;
					v = (BAddTreeLeafNode<K, E>*)p;
					continue;//���紫��
					return;
				}
			}
			else {//�ڲ��ڵ�
				BStarTreeNode<K, E>*tv = (BStarTreeNode<K, E>*)v;
				if (tv->last  && tv->last->key.size() > _verge) {//��ɽ�
					BStarTreeNode<K, E>*_last = tv->last;
					auto it = --_last->key.end();
					K k = updateAncestorIndex(_last->key[0], tv->key[0], *it, tv);//������������
					tv->key.insert(tv->key.begin(), k);
					_last->key.erase(it);
					tv->child.insert(tv->child.begin(), *--_last->child.end());
					_last->child.erase(--_last->child.end());
					//��������
					tv->child[0]->parent = static_cast<BAddTreeNode<K, E>*>(tv);
					return;
				}
				if (tv->next && tv->next->key.size() > _verge) {//�ҿɽ�
					BStarTreeNode<K, E>*_next = tv->next;
					K k = updateAncestorIndex(tv->key[0], _next->key[0], _next->key[0], _next);//������������
					tv->key.insert(tv->key.end(), k);
					_next->key.erase(_next->key.begin());
					tv->child.insert(tv->child.end(), *_next->child.begin());
					_next->child.erase(_next->child.begin());
					//��������
					tv->child[tv->child.size() - 1]->parent = static_cast<BAddTreeNode<K, E>*>(tv);
					return;
				}
				if (!tv->last) {//���ֵܲ����� ���ֵܲ��ɽ�
					BStarTreeNode<K, E>*_next = tv->next;
					if (tv->next->next) {//�������ֵܵ����ֵ� ����������
						K k = updateAncestorIndex(tv->key[0], _next->key[0], _next->key[0], _next);//������������
						tv->key.insert(tv->key.end(), k);
						_next->key.erase(_next->key.begin());
						tv->child.insert(tv->child.end(), *_next->child.begin());
						_next->child.erase(_next->child.begin());
						//��������
						tv->child[tv->child.size() - 1]->parent = static_cast<BAddTreeNode<K, E>*>(tv);
						v = (BAddTreeLeafNode<K, E>*)_next;//��������
						continue;//���紫��
					}
					else {//ֻ��2���ֵ� ���ڵ㼴Ϊ�� ��ϲ�Ϊһ�����ڵ�
						BStarTreeNode<K, E>*_r = this->m_root;
						_next->key.insert(_next->key.begin(), _r->key[0]);//�������ڵ�����
						delete _r;
						_next->key.insert(_next->key.begin(), tv->key.begin(), tv->key.end());
						//��������
						{
							int _s = tv->child.size();
							for (int i = 0; i < _s; ++i)
								tv->child[i]->parent = static_cast<BAddTreeNode<K, E>*>(_next);
						}
						_next->child.insert(_next->child.begin(), tv->child.begin(), tv->child.end());
						this->m_root = _next;//�¸�ȷ��
						this->m_root->parent = nullptr;//���¸�����
						_next->last = nullptr; _next->next = nullptr;
						delete tv, tv = nullptr;
						return;
					}
				}
				if (!tv->next) {//���ֵܲ����� ���ֵܲ��ɽ� 
					BStarTreeNode<K, E>*_last = tv->last;
					if (tv->last->last) {//�������ֵܵ����ֵ� ����������
						auto it = --_last->key.end();
						K k = updateAncestorIndex(_last->key[0], tv->key[0], *it, tv);//������������
						tv->key.insert(tv->key.begin(), k);
						_last->key.erase(it);
						tv->child.insert(tv->child.begin(), *--_last->child.end());
						_last->child.erase(--_last->child.end());
						//��������
						tv->child[0]->parent = static_cast<BAddTreeNode<K, E>*>(tv);
						v = (BAddTreeLeafNode<K, E>*)_last;//��������
						continue;//���紫��
					}
					else {//ֻ��2���ֵ� ��ϲ�Ϊһ�����ڵ�
						BStarTreeNode<K, E>*_r = this->m_root;
						_last->key.insert(_last->key.end(), _r->key[0]);
						delete _r;
						_last->key.insert(_last->key.end(), tv->key.begin(), tv->key.end());
						//��������
						{
							int _s = tv->child.size();
							for (int i = 0; i < _s; ++i)
								tv->child[i]->parent = static_cast<BAddTreeNode<K, E>*>(_last);
						}
						_last->child.insert(_last->child.end(), tv->child.begin(), tv->child.end());
						this->m_root = (BStarTreeNode<K, E>*)_last;//�¸�ȷ��
						this->m_root->parent = nullptr;//���¸�����
						delete tv, tv = nullptr;
						return;
					}
				}
				//�����ֵܶ����ɽ裬���v�ֽ⵽�����ֵܺϲ�Ϊ2���ֵ� ����������ϲ�
				{
					//����ϲ�
					{
						int _mc = tv->key.size() - (tv->key.size()) / 2;//�����Ƶĸ���
						BStarTreeNode<K, E>*_last = tv->last;
						K k = updateAncestorIndex(_last->key[0], tv->key[0], *(tv->key.begin() + _mc - 1), tv);//������������
						_last->key.insert(_last->key.end(), k);//������������
						_last->key.insert(_last->key.end(), tv->key.begin(), tv->key.begin() + _mc - 1);
						tv->key.erase(tv->key.begin(), tv->key.begin() + _mc);
						//��������
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
					//���Һϲ�
					{
						BStarTreeNode<K, E>*_next = tv->next;
						//�������ҳ�Ҫ����vɾ����ɾ���ĸ��ڵ��ж�Ӧ�������滻��v�����ֵܵ�һ����ͬ���ȵĶ�Ӧ����
						int rank = 0; while (tv->parent->child[rank] != static_cast<BAddTreeNode<K, E>*>(tv))++rank;
						K k;
						if (rank == 0) {
							k = updateAncestorIndex(tv->key[0], _next->key[0], *tv->parent->key.begin(), _next);//��ȡ�游����
							tv->parent->key.erase(tv->parent->key.begin());
						}
						else {
							k = updateAncestorIndex(tv->key[0], _next->key[0], *(tv->parent->key.begin() + rank - 1), _next);//��ȡ�游����
							tv->parent->key.erase(tv->parent->key.begin() + rank - 1);
						}
						_next->key.insert(_next->key.begin(), k);//������������
						_next->key.insert(_next->key.begin(), tv->key.begin(), tv->key.end());
						//��������
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
						tv->last->next = tv->next; tv->next->last = tv->last;//ά������
						delete tv, tv = nullptr;
						//����������� 2��Ϊ2/3���������������м����Ϊ2/3����������-1��������˺ϲ����ҷ�֧�������磬����Ҫ���������
						v = (BAddTreeLeafNode<K, E>*)_next;
						solveOverFlow(v);//���紦��
						v = (BAddTreeLeafNode<K, E>*)(p);
						continue;//���紫��
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
						p->key[i] = _v;//��������;
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

