#ifndef BADDTREE_H_H_H
#define BADDTREE_H_H_H

/*
B+��
K����,E�Ǽ�¼
E���ͱ���ʵ�ֺ�����K key()������
*/


#include"BAddTreeNode.h"
#include<queue>

namespace BAT {
	using namespace BATN;
	template<typename K, typename E>
	class BAddTree
	{
	public:
		explicit BAddTree(int order);//��С��2ʱĬ��Ϊ2��,���˻�Ϊ���������� (m>=2);���ﲻ��Ĭ��ֵ�����ڼ̳�
		~BAddTree();

		int const order()const;//�״�
		int const size()const;//��ģ

			//�����ӿ�
		virtual BAddTreeNode<K,E>*  search(E const&);//����
		virtual  bool insert(E const&);//����
		virtual bool remove(E const&);//ɾ��

		template<typename Visist>
		void list_traversal(Visist );//����
	protected:
		BAddTree();//�ɼ̳�
		void solveOverFlow(BAddTreeNode<K,E>*);//���������������
		void solveUnderFlow(BAddTreeNode<K,E>*);//���������������
	protected:
		int m_size;//�ؼ�������
		int m_order;//B-���Ľ״�,����Ϊ2(���˻�Ϊ����������) ����ʱָ�� һ�㲻���޸�
		BAddTreeNode<K,E>* m_root;//����
		BAddTreeNode<K,E>* m_hitParentNode;//���ҷ���ʱ���нڵ�ĸ��׻��ߴ�͸�ײ�����һ�����ʵĽڵ㣬����Ϊ��ʱ ����ʺ�Ϊ��
		BAddTreeNode<K,E>*m_header, *m_trail;//˫��������β
	};

	template<typename K, typename E>
	inline BAddTree<K, E>::BAddTree(int order)
	{
		if (order < 2)order = 2;//Ĭ��2��
		m_order = order;
		this->m_root = new BAddTreeNode<K,E>(m_order); m_size = 0; m_hitParentNode = nullptr;
		m_header = new BAddTreeNode<K,E>();
		m_trail = new BAddTreeNode<K,E>();
		m_header->next = this->m_root; m_trail->last = this->m_root;//����
		this->m_root->last = m_header; this->m_root->next = m_trail;
	}

	template<typename K, typename E>
	inline BAddTree<K, E>::~BAddTree()
	{
		if (!this->m_root)return;//û�и��Ͳ�ɾ��
		std::queue<BAddTreeNode<K,E>*>q;//���븨�����а���α���ɾ��
		q.push(this->m_root);//�������
		while (!q.empty())
		{
			BAddTreeNode<K,E>*p = q.front();
			q.pop();
			int count = p->child.size();
			for (int i = 0; i < count; ++i) {
				if (p->child[i]) {
					q.push(p->child[i]);//������к������
				}
			}
			delete p, p = nullptr;//�ͷ�ÿ���ڵ�
		}
		delete m_header, m_header = nullptr;
		delete m_trail, m_trail = nullptr;
		this->m_root = nullptr;
		this->m_size = 0;
	}

	template<typename K, typename E>
	inline int const BAddTree<K, E>::order() const
	{
		return m_order;
	}

	template<typename K, typename E>
	inline int const BAddTree<K, E>::size() const
	{
		return m_size;
	}

	template<typename K, typename E>
	inline BAddTreeNode<K,E>* BAddTree<K, E>::search(E const &e)
	{
		this->m_hitParentNode = nullptr;
		K k = e.key();
		BAddTreeNode<K,E>*v = this->m_root;
		while (!v->isLeaf())
		{
			int _s = v->key.size();
			int i = 0;
			for (; i < _s; ++i) {
				K&tk = v->key[i];
				if (tk > k)break;
			}
			this->m_hitParentNode = v;
			v = v->child[i];//ת����һ��
		}
		if (v&&v->isLeaf()) {
			int _s = v->key.size();
			int i = 0;
			for (; i < _s; ++i) {
				K&tk = v->key[i];
				if (tk == k) {
					return v;
				}
				else if (tk > k) 
					break;
              }
			this->m_hitParentNode = v;
			v = v->child[i];//ת����һ��
		}
		return v;
	}

	template<typename K, typename E>
	inline bool BAddTree<K, E>::insert(E const &e)
	{
		BAddTreeNode<K,E>*v = this->search(e);
		if (v) {//����������ظ�ֵ ��Ϊ����Ҫ����������ܵ���һ���ڵ��2�߶������ظ�ֵ�����²���̫������
			return false;
		}
		else {
			K k = e.key();
			v = this->m_hitParentNode;
			int _s = v->key.size();
			int i = 0;
			for (; i < _s; ++i) {
				K&tk = v->key[i];
				if (tk > k)break;
			}
			v->key.insert(v->key.begin()+i,k);//����ؼ���
			++this->m_size;//���¹�ģ
			v->child.insert(v->child.begin() + i + 1, nullptr);//����շ�֧
			E*_e = new E();
			*_e =std::move(e);//ʹ����ֵ�ƶ�
			v->e.insert(v->e.begin() + i, _e);//�����¼
			solveOverFlow(v);//���������
			return true;
		}
	}

	template<typename K, typename E>
	inline bool BAddTree<K, E>::remove(E const &e)
	{
		BAddTreeNode<K,E>*v = this->search(e);
		if (!v) {
			return false;
		}
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
	template<typename Visist>
	inline void BAddTree<K, E>::list_traversal(Visist visit)
	{
	//	tt();
		BAddTreeNode<K,E>*p = m_header;
		while ((p=p->next) != m_trail) {
			visit(p->e);
		}
	}

	template<typename K, typename E>
	inline BAddTree<K, E>::BAddTree()
	{
		m_size = -1; m_order = -1; m_root = nullptr; m_hitParentNode = nullptr; m_header = nullptr; m_trail = nullptr;
	}

	template<typename K, typename E>
	inline void BAddTree<K, E>::solveOverFlow(BAddTreeNode<K,E>*v)
	{
		while (v->child.size()>m_order)//����
		{
			int mid =m_order / 2;//���ѳ�ȥ�ĸ���
			BAddTreeNode<K,E>*_r = new BAddTreeNode<K,E>(m_order);//ע��Ĭ����һ���շ�֧
			if (v->isLeaf()) {//���һ Ҷ�ڵ㸴������㲿�ֲ���������
				//��¼����
				{
					_r->e.insert(_r->e.begin(), v->e.begin() + mid, v->e.end());
					v->e.erase(v->e.begin() + mid, v->e.end());
				}
				//�ؼ��ִ���
				{
					_r->key.insert(_r->key.begin(), v->key.begin() + mid, v->key.end());
					v->key.erase(v->key.begin() + mid+1, v->key.end());
				}
				//��֧����
				{
					_r->child.insert(_r->child.begin(), v->child.begin() + mid, v->child.end() - 1);
					v->child.erase(v->child.begin() + mid + 1, v->child.end() - 1);
					_r->child[_r->child.size() - 1] = v->child[v->child.size() - 1];
					v->child.erase(v->child.end()-1);
				}
				//�������� 
				v->next->last = _r; _r->next = v->next;
				_r->last = v; v->next = _r;
			}
			else {//����� �ڲ��ڵ㲻��������㲿�� ��û�м�¼
				//�ؼ��ִ���
				{
					_r->key.insert(_r->key.begin(), v->key.begin() + mid+1, v->key.end());
					v->key.erase(v->key.begin() + mid+1, v->key.end());
				}
				//��֧����
				{
					_r->child.insert(_r->child.begin(), v->child.begin() + mid + 1, v->child.end() - 1);
					v->child.erase(v->child.begin() + mid + 1, v->child.end() - 1);
					_r->child[_r->child.size() - 1] = v->child[v->child.size() - 1];
					v->child.erase(v->child.end()-1);
				}
			}
			//��ͬ���� ���¸��ڵ�
			{
				if (_r->child[0])//�ӵ���״̬ͳһ
					for (int i = 0; i < _r->child.size(); ++i)
						_r->child[i]->parent = _r;
				BAddTreeNode<K, E>*p = v->parent;
				if (!p) {
					this->m_root = p = new BAddTreeNode<K, E>(m_order); p->child[0] = v; v->parent = p;//�����Ϊ���������¸�
				}
				K& k = v->key[v->key.size() - 1];//������
				int i = 0; while (p->child[i] != v)++i;
				p->key.insert(p->key.begin()+i, k);//���ڵ������
				p->child.insert(p->child.begin()+ i + 1, _r);//���ڵ��֧����
				_r->parent = p;//��������
				v->key.erase(v->key.end() - 1);//������ɾ��
				v = p;//���紫��
			}
		}
	}

	template<typename K, typename E>
	inline void BAddTree<K, E>::solveUnderFlow(BAddTreeNode<K,E>*v)
	{
		//��B��һ������ͬ����Ҷ�ӽڵ㲻���������ڵ�ؼ���
		size_t sep = (m_order+1) / 2;//�����ٽ��
		while (v->child.size()<sep)//����
		{
			BAddTreeNode<K,E>*p = v->parent;
			if (!p) {//���ڵ���С�ؼ���Ϊ1
				if (v->key.empty()&&v->child[0]) {//���絽������Ψһ�ǿսڵ�����
					if (v->isLeaf()) {//Ҷ�ӽڵ����������
						v->next->last = v->last; v->last->next = v->next;
					}
					this->m_root = v->child[0];
					this->m_root->parent = nullptr;
					delete v, v = nullptr;     
				}
				return;
			}

			int rank = 0;
			while (p->child[rank] != v)++rank;

			//��2�� Ҷ�ӽڵ㼰�ڲ��ڵ� �ڲ��ڵ�ͬB�� Ҷ�ӽڵ���ɾ��B���е�����ֵ���һ��ͬʱ�滻�����ڵ�(ע���滻)
			if (v->isLeaf()) {
				//���1����ɽ�
				if (rank > 0) {
					BAddTreeNode<K,E>*_left = p->child[rank - 1];//���ֵ�
					if (_left->child.size() > sep) {
						v->child.insert(v->child.begin(), _left->child[_left->child.size() - 1]);//��һ����֧
						if (v->child[0])v->child[0]->parent = v;//��������
						_left->child.erase(_left->child.end() - 1);//ɾ��
						{
							auto it = --_left->key.end();
							p->key[rank - 1] = *(it);//���ڵ�ؼ����滻
							v->key.insert(v->key.begin(), *it);//��һ���ؼ���
							_left->key.erase(it);//ɾ��
						}
						{
							auto it = --_left->e.end();
							v->e.insert(v->e.begin(), *it);//��һ����¼
							_left->e.erase(it);//ɾ��
						}
						return;
					}
				}
				//���2���ҿɽ�
				if (rank < p->child.size() - 1) {
					BAddTreeNode<K,E>*_right = p->child[rank+1];//���ֵ�
					if (_right->child.size() > sep) {
						v->child.insert(v->child.end(), _right->child[0]);//��һ����֧
						if (v->child[v->child.size() - 1])v->child[v->child.size() - 1]->parent = v;//��������
						_right->child.erase(_right->child.begin());//ɾ��
						{
							auto it =_right->key.begin()+1;
							p->key[rank ] = (it!=_right->key.end()?*(it--):*(--it)+1);//���ڵ�ؼ����滻
							v->key.insert(v->key.end(), *it);//��һ���ؼ���
							_right->key.erase(it);//ɾ��
						}
						{
							auto it = _right->e.begin();
							v->e.insert(v->e.end(), *it);//��һ����¼
							_right->e.erase(it);//ɾ��
						}
						return;
					}
				}
				//���3:��������Һϲ�
				if (rank > 0) {//��������ϲ� ������ȫ��������
					BAddTreeNode<K,E>*_left = p->child[rank - 1];//���ֵ�
					v->child.erase(v->child.begin());//����ɾ��һ�������֧����������ҹ�����֧ԭ��ɾ������ȻҲ�������ɾ��
					_left->child.insert(_left->child.end(), v->child.begin(), v->child.end());;//�ϲ���֧
					_left->key.insert(_left->key.end(), v->key.begin(), v->key.end());//�ϲ��ؼ���
					//ɾ�����ؼ���(������)
					p->child.erase(p->child.begin()+rank);
					p->key.erase(p->key.begin() + rank - 1);
					//�ϲ���¼
					_left->e.insert(_left->e.end(), v->e.begin(), v->e.end());
					v->e.resize(0);//��ȫ����
					//�ؽ�����
					v->last->next = v->next; v->next->last = v->last;
					delete v, v = nullptr;
					v = p;//���紫��
					continue;
				}
				else {
					BAddTreeNode<K,E>*_right = p->child[rank +1];//���ֵ�
					_right->child.erase(_right->child.begin());//����ɾ��һ�������֧����������ҹ�����֧ԭ��ɾ������ȻҲ�������ɾ��
					_right->child.insert(_right->child.begin(), v->child.begin(), v->child.end());;//�ϲ���֧
					_right->key.insert(_right->key.begin(), v->key.begin(), v->key.end());//�ϲ��ؼ���
					//ɾ�����ؼ���(������)
					p->child.erase(p->child.begin() + rank);
					p->key.erase(p->key.begin() + rank );
					//�ϲ���¼
					_right->e.insert(_right->e.begin(), v->e.begin(), v->e.end());
					v->e.resize(0);//��ȫ����
					//�ؽ�����
					v->last->next = v->next; v->next->last = v->last;
					delete v, v = nullptr;
					v = p;//���紫��
					continue;
				}
			}
			else {//�ڲ��ڵ�
				//��������ϲ� ������ȫ��������
					//���1����ɽ�
				if (rank > 0) {
					BAddTreeNode<K,E>*_left = p->child[rank - 1];//���ֵ�
					if (_left->child.size() > sep) {
						v->child.insert(v->child.begin(), _left->child[_left->child.size() - 1]);//��һ����֧
						if (v->child[0])v->child[0]->parent = v;//��������
						_left->child.erase(_left->child.end() - 1);//ɾ��
							auto it = --_left->key.end();
                            v->key.insert(v->key.begin(), p->key[rank - 1]);//��һ���ؼ���
							p->key[rank - 1] = *(it);//���ڵ�ؼ����滻
							_left->key.erase(it);//ɾ��
						return;
					}
				}
				//���2���ҿɽ�
				if (rank < p->child.size() - 1) {
					BAddTreeNode<K,E>*_right = p->child[rank + 1];//���ֵ�
					if (_right->child.size() > sep) {
						v->child.insert(v->child.end(), _right->child[0]);//��һ����֧
						if (v->child[v->child.size()-1])v->child[v->child.size() - 1]->parent = v;//��������
						_right->child.erase(_right->child.begin());//ɾ��
							auto it = _right->key.begin();
							v->key.insert(v->key.end(), p->key[rank]);//��һ���ؼ���
							p->key[rank] = *(it);//���ڵ�ؼ����滻
							_right->key.erase(it);//ɾ��
						return;
					}
				}
				//���3:��������Һϲ�
				if (rank > 0) {//��������ϲ� ������ȫ��������
					BAddTreeNode<K,E>*_left = p->child[rank - 1];//���ֵ�
					_left->child.insert(_left->child.end(), v->child.begin(), v->child.end());;//�ϲ���֧
					//��������
					{
						auto it = _left->child.end() - v->child.size();
						auto ite = _left->child.end();
						while (it!=ite)
						{
							if(*it)(*it)->parent = _left;
							++it;
						}
					}
					_left->key.insert(_left->key.end(),p->key[rank-1]);
					_left->key.insert(_left->key.end(), v->key.begin(), v->key.end());//�ϲ��ؼ���
					p->child.erase(p->child.begin() + rank);
					p->key.erase(p->key.begin() + rank - 1);
					delete v, v = nullptr;
					v = p;//���紫��
					continue;
				}
				else {
					BAddTreeNode<K,E>*_right = p->child[rank + 1];//���ֵ�
					_right->child.insert(_right->child.begin(), v->child.begin(), v->child.end());;//�ϲ���֧
						//��������
					{
						auto it = _right->child.begin();
						auto ite = _right->child.begin()+v->child.size();
						while (it != ite)
						{
							if(*it)(*it)->parent = _right;
							++it;
						}
					}
					_right->key.insert(_right->key.begin(), p->key[rank]);
					_right->key.insert(_right->key.begin(), v->key.begin(), v->key.end());//�ϲ��ؼ���
					p->child.erase(p->child.begin() + rank);
					p->key.erase(p->key.begin() + rank);
					delete v, v = nullptr;
					v = p;//���紫��
					continue;
				}
			}
		}
	}

}

#endif // !BADDTREE_H_H_H

