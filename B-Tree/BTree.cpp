#ifndef BTREE_CPP_CPP
#define BTREE_CPP_CPP

#include"BTree.h"
namespace BT {

	template<typename T>
	TREE_OUTOFLINE BTree<T>::BTree(int order):
		m_order((order>2?order:2)),m_size(0),m_root(new BTreeNode<T>(m_order)),m_hitParentNode(nullptr)
	{

	}

	template<typename T>
	TREE_OUTOFLINE BTree<T>::BTree(BTree<T> const &t)
	{
		this->m_hitParentNode =t.m_hitParentNode; this->m_order = t.m_order; this->m_size = t.m_size;//��ʼ������
		if (!t.m_root) {//�и��ſ�������
			this->m_root = nullptr;
			return;
		}
		this->m_root = new BTreeNode<T>(m_order);//��������
		this->m_root->child.clear();//���������Ŀպ���
		std::queue<BTN(T)>q;//���븨�����а���α�������
		std::queue<BTN(T)>tq;//���븨�����а���α�������
		q.push(t.m_root);//�������
		tq.push(this->m_root);//�����������
this->m_root->key = t.m_root->key;//���Ƹ��Ĺؼ���
this->m_root->same = t.m_root->same;//��ֵ������ֵͬ����
		while (!q.empty())
		{
			BTN(T)p = q.front();
			q.pop();
			BTN(T)tp = tq.front();
			tq.pop();
		int count = p->child.size();
			for (int i = 0; i < count; ++i) {
				if (p->child[i]) {
					q.push(p->child[i]);//������к������
					BTN(T)n = new BTreeNode<T>(m_order);
					n->child.clear();//���������Ŀպ���
					n->key = p->child[i]->key;//���ƹؼ���
					n->same = p->child[i]->same;//������ֵͬ
					n->parent = tp;//��������
					tq.push(n);//�����������
					tp->child.insert(tp->child.end(),n);//��Ӻ���;��������
				}
				else {
					tp->child.insert(tp->child.end(), nullptr);//��ӿպ���
				}
			}
			}
	}

	template<typename T>
	TREE_OUTOFLINE BTree<T>::BTree(BTree<T>&&t)
	{
		this->m_hitParentNode =std::move(t.m_hitParentNode); this->m_order = std::move(t.m_order); this->m_size = std::move(t.m_size);//��ʼ������
		this->m_root = std::move(t.m_root);//�����ƶ�
		t.m_hitParentNode = nullptr; t.m_order = -1; t.m_size = -1; t.m_root = nullptr;//������ȫ
	}

	template<typename T>
	TREE_OUTOFLINE BTree<T> & BTree<T>::operator=(BTree<T> t) &
	{
		// TODO: �ڴ˴����� return ���
		this->m_hitParentNode = std::move(t.m_hitParentNode); this->m_order = std::move(t.m_order); this->m_size = std::move(t.m_size);//��ʼ������
		this->m_root = std::move(t.m_root);//�����ƶ�
		t.m_hitParentNode = nullptr; t.m_order = -1; t.m_size = -1; t.m_root = nullptr;//������ȫ
		return *this;
	}

	template<typename T>
	TREE_OUTOFLINE BTree<T>::~BTree()
	{
		if (!this->m_root)return;//û�и��Ͳ�ɾ��
		std::queue<BTN(T)>q;//���븨�����а���α���ɾ��
		q.push(this->m_root);//�������
		while (!q.empty())
		{
			BTN(T)p = q.front();
			q.pop();
			int count = p->child.size();
			for (int i = 0; i < count; ++i) {
				if (p->child[i]) {
					q.push(p->child[i]);//������к������
				}
			}
			delete p, p = nullptr;//�ͷ�ÿ���ڵ�
		}
	}
	template<typename T>
	TREE_OUTOFLINE int const BTree<T>::order() const
	{
		return m_order;
	}
	template<typename T>
	TREE_OUTOFLINE int const BTree<T>::size() const
	{
		return m_size;
	}
	template<typename T>
	TREE_OUTOFLINE BTN(T)& BTree<T>::root()
	{
		// TODO: �ڴ˴����� return ���
		return m_root;
	}
	template<typename T>
	TREE_OUTOFLINE bool BTree<T>::empty() const
	{
		return m_size == 0;
	}
	template<typename T>
	template<typename Visist>
	TREE_OUTOFLINE void BTree<T>::traversal(Visist visist)
	{
		if (this->m_root)visist(this->m_root);
	}
template<typename T>
TREE_OUTOFLINE BTN(T) BTree<T>::search(T const &d)
	{
		BTN(T)v = this->m_root; this->m_hitParentNode = nullptr;//�Ӹ��ڵ㿪ʼ���� 
		while (v)
		{
			int rank = Find(v->key, d);
			if (rank < v->key.size() && v->key[rank] == d)return v;//�ҵ��ؼ��룬�������нڵ�
			this->m_hitParentNode = v;//��¼���нڵ�ĸ���
			v = v->child[rank];//�ƶ�����һ��
		}
		return v;
	}
	template<typename T>
	TREE_OUTOFLINE bool BTree<T>::insert(T const &d)
	{
		BTN(T)v = BTree<T>::search(d);
		if (v) {//�����ظ�ֵ ����ѡ���ڶ�ά�����м�¼=�������ϵ���ֵͬ 
			int rank = Find(v->key, d);//��ѯ�ʺϲ����λ��
			ReallocVector(v->same[rank]);//��ֵͬ�������ܴܺ�,Ԥ�����ڴ� ����ʹ��Ĭ��Ԥ�������
			v->same[rank].insert(v->same[rank].end(), d);//���뵽����ĩβ
			++m_size;//��ģ����;
		}else {
			int rank = Find(this->m_hitParentNode->key, d);//��ѯ�ʺϲ����λ��
			auto it1 = this->m_hitParentNode->key.begin();
			std::advance(it1, rank);
			auto it2 = this->m_hitParentNode->child.begin();
			std::advance(it2, rank+1);//����λ��Ϊ�ؼ�����ұ߼���Ҫ��1
			this->m_hitParentNode->key.insert(it1, d);//�ٺ���λ�ò���
			this->m_hitParentNode->same.insert(this->m_hitParentNode->same.begin()+rank,std::vector<T>());//�ٺ���λ�ò������ֵͬ
			this->m_hitParentNode->child.insert(it2, nullptr);//�ٺ���λ�ò���պ���
			++m_size;//��ģ����;
			solveOverFlow(this->m_hitParentNode);//�緢��������������
		}
		return true;
	}
	template<typename T>
	TREE_OUTOFLINE bool BTree<T>::remove(T const &d)
	{
		BTN(T)v = BTree<T>::search(d); if (!v)return false;//�����ڷ���
		int rank = Find(v->key, d);//���ҹؼ������
		if (v->same[rank].size() > 0) {
			v->key[rank] = v->same[rank][0];//��ֵͬ���Ƴ���
			v->same[rank].erase(v->same[rank].begin());//ɾ���ؼ���
			--this->m_size;//���¹�ģ
		}
		else {
			if (v->child[0]) {//��Ҷ���Һ��
				BTN(T)succ = v->child[rank + 1];
				while (succ->child[0])
				{
					succ = succ->child[0];//һֱ����
				}
				//��������
				v->key[rank] = succ->key[0]; rank = 0; v = succ;
			}
			BTN(T)p = v->child[rank + 1];//��ȡʵ��ɾ��Ŀ��
			v->key.erase(v->key.begin() + rank); v->child.erase(v->child.begin() + rank + 1);v->same.erase(v->same.begin()+rank);//��������
			delete p, p = nullptr;//�ͷ��ڴ�
			--this->m_size;//���¹�ģ
			solveUnderFlow(v);//����Ƿ������磬���� ���кϲ�����
		}
		return true;
	}
	template<typename T>
	TREE_OUTOFLINE void BTree<T>::solveOverFlow(BTN(T)v)
	{
		while (v->child.size() > m_order) {//�������� 
			int rank = m_order / 2;//Ҫ���ѵ���
			BTN(T)u = new BTreeNode<T>(m_order);//���ѽڵ� ע��Ĭ�Ϲ��캯����0���ؼ���һ����֧
			{//�ƶ�v�ұߵĹؼ������ֵͬ������u
				{
					auto it = v->key.begin();
					std::advance(it, rank + 1);
					u->key.insert(u->key.begin(), it, v->key.end());//�����ұߵ�u
					v->key.erase(it, v->key.end());//�Ƴ��ұ�
					}
				{
					auto it = v->same.begin();
					std::advance(it, rank + 1);
					u->same.insert(u->same.begin(), it, v->same.end());//�����ұߵ�u
					v->same.erase(it, v->same.end());//�Ƴ��ұ�
				}
			}
			{//�ƶ�v�ұߵķ�֧��u
				auto it = v->child.begin();
				std::advance(it, rank + 1);
				u->child.insert(u->child.begin(), it, v->child.end()-1);//�����ұߵ�u
				v->child.erase(it, v->child.end()-1);//�Ƴ��ұ�
			}
			u->child[u->child.size()-1] = v->child[v->child.size()-1];//���һ����֧�ƶ���u
			v->child.erase(v->child.end()-1);//�Ƴ����һ����֧
			//ע��Ҷ�ڵ㼰�ڲ��ڵ��״̬��ͳһ��
			if (u->child[0])
			for (int i = 0; i < m_order - rank; ++i) {
				u->child[i]->parent = u;//����u���ӵĸ��ڵ�Ϊu
			}
			BTN(T)p = v->parent;
			if (!p) {//�����ڵ������򴴽��µĸ��ڵ㴦����������
				this->m_root = p = new BTreeNode<T>(m_order); p->child[0]=v; v->parent = p;//ע��0���ؼ���Ĭ��һ����֧���滻�����캯���Ŀշ�֧
			}
			auto it = v->key.begin();
			std::advance(it, rank);
			auto its = v->same.begin();
			std::advance(its, rank);
			T& key = *it;//��ȡ����ؼ���
			std::vector<T> sames;sames.swap(*its);//��ȡ����ؼ�����ֵͬ����
			rank = Find(p->key, v->key[0]);//�ҵ�����ڵ�����һ���еķ�֧λ��
			v->key.erase(it);
			v->same.erase(its);
			it = p->key.begin(); std::advance(it, rank);
			p->key.insert(it, key);//�����ڸ����еĹؼ���
			p->same.insert(p->same.begin()+rank, sames);//�����ڸ����еĹؼ�����ֵͬ����
			auto itc = p->child.begin(); std::advance(itc, rank + 1);
			p->child.insert(itc, u);//���ѽڵ㸸����������
			u->parent = p;//���ѽڵ���������
			v=p;//���紫�����
		}
 	}

	template<typename T>
	TREE_OUTOFLINE void BTree<T>::solveUnderFlow(BTN(T)v)
	{
		const int _m2 = (m_order + 1) / 2;//��¼��֧����
		while (v->child.size()<(m_order+1)/2)//�������磬���кϲ�����
		{
			BTN(T)p = v->parent;
			if (!p) {//�Ǹ��ڵ� 
				if (v->key.empty() && v->child[0]) {//��Ψһ�ǿսڵ㼴�������磬��Ҫɾ���ڵ㣬�����ƶ����ڵ�
					this->m_root = v->child[0]; this->m_root ->parent= nullptr;
					v->child[0] = nullptr;
					delete v, v = nullptr;//�ͷ��ڴ�
				}
				return;
			}
			int rank = 0; while (p->child[rank] != v)++rank;//����v�ڸ����е���(��Ȼ�ҵ�)
			//��������������������
			//1 ���ֵܽ�һ�����ֵ��Ϊ����Ĺؼ��룬����Ĺؼ�����Ϊv����С�ؼ��룬Ȼ��������Һ��ӷ�֧
			if (rank > 0) {
				BTN(T)lb = p->child[rank - 1];//���ֵܱ�Ȼ����
					if (lb->child.size() > _m2) {//�ֵ��㹻
						v->key.insert(v->key.begin(), p->key[rank - 1]);//���׵Ľڵ��ƶ���v��Ϊ��Сֵ
						v->same.insert(v->same.begin(), p->same[rank - 1]);//�ƶ��ؼ����Ӧ��ֵͬ����
						p->key[rank-1]= lb->key[lb->key.size() - 1];//���ֵ����ֵ���Ƶ�parent
						p->same[rank - 1] = lb->same[lb->same.size() - 1];//�ƶ��ؼ����Ӧ��ֵͬ����
						v->child.insert(v->child.begin(), lb->child[lb->child.size() - 1]);//���ֵ����Һ�����Ϊv������
						if (v->child[0])v->child[0]->parent = v;
						lb->key.erase(lb->key.end() - 1); lb->child.erase(lb->child.end() - 1),lb->same.erase(lb->same.end()-1);//���ֵ�ɾ���ƶ��Ķ���
						return;//���������
					}
			}//���˴���û�����ֵ� �����ֵܲ��ܽ�
			//2 ���ֵܽ�һ����Сֵ��Ϊparent�Ĺؼ��룬parent�Ĺؼ�����Ϊv�����ؼ��� Ȼ��������Һ��ӷ�֧
			if (rank + 2 < p->child.size()) {
				BTN(T)rb = p->child[rank + 1];//���ֵܱ�Ȼ����
					if (rb->child.size() > _m2) {//�ֵ��㹻
						v->key.insert(v->key.end(), p->key[rank]);//���׵Ľڵ��ƶ���v��Ϊ���ֵ
						v->same.insert(v->same.end(), p->same[rank]);//�ƶ��ؼ����Ӧ��ֵͬ����
						p->key[rank]=rb->key[0];//���ֵ���Сֵ���Ƶ�parent
						p->same[rank] = rb->same[0];//�ƶ��ؼ����Ӧ��ֵͬ����
						v->child.insert(v->child.end(), rb->child[0]);//���ֵ����Һ�����Ϊv������
						if (v->child[v->child.size()-1])v->child[v->child.size() - 1]->parent = v;
						rb->key.erase(rb->key.begin()); rb->child.erase(rb->child.begin());rb->same.erase(rb->same.begin());//���ֵ�ɾ���ƶ��Ķ���
						return;//���������
					}
			}//���˴���û�����ֵ� �����ֵܲ��ܽ�
			//3 ���ֵܻ������ֵܲ����� ����������Ĺؼ��붼����m/2������ȡֵ���� ���кϲ�����
			if (0 < rank) {
				BTN(T)lb = p->child[rank - 1]; //���ֵܱ�Ȼ����
				lb->key.insert(lb->key.end(), p->key[rank - 1]);//parent�Ĺؼ������
				lb->same.insert(lb->same.end(), p->same[rank - 1]);//�ƶ��ؼ����Ӧ��ֵͬ����
				p->child.erase(p->child.begin() + rank); p->key.erase(p->key.begin() + rank - 1);p->same.erase(p->same.begin()+rank-1);//�����Ƴ�parent�Ĺؼ��ֺͺ��� �ؼ����Ӧ��ֵͬ����
				lb->child.insert(lb->child.end(), v->child[0]); v->child.erase(v->child.begin());
				if (lb->child[lb->child.size() - 1])lb->child[lb->child.size() - 1]->parent = lb;//���ƶ�v������ൽ���ֵܵ��Ҳ�
				while (!v->key.empty()) {
					lb->key.insert(lb->key.end(), v->key[0]); v->key.erase(v->key.begin());//�ƶ�v�Ĺؼ��ֵ����ֵ���
					lb->same.insert(lb->same.end(), v->same[0]); v->same.erase(v->same.begin());//�ƶ��ؼ����Ӧ��ֵͬ����
					lb->child.insert(lb->child.end(), v->child[0]); v->child.erase(v->child.begin());
					if (lb->child[lb->child.size() - 1])lb->child[lb->child.size() - 1]->parent = lb;//�����ƶ�vʣ�µĺ���
				}
				delete v, v = nullptr;//�ͷ�����ڵ��ڴ�
				v = p;//ʧ�⴫������
				continue;
			}else {
				BTN(T)rb = p->child[rank + 1];//���ֵܱ�Ȼ����
				rb->key.insert(rb->key.begin(), p->key[rank ]);//parent�Ĺؼ������
				rb->same.insert(rb->same.begin(), p->same[rank]);//�ƶ��ؼ����Ӧ��ֵͬ����
				p->child.erase(p->child.begin() + rank); p->key.erase(p->key.begin() + rank ); p->same.erase(p->same.begin() + rank);//�����Ƴ�parent�Ĺؼ��ֺͺ��� �ؼ����Ӧ��ֵͬ����
				rb->child.insert(rb->child.begin(), v->child[v->child.size()-1]); v->child.erase(v->child.end()-1);
				if (rb->child[0])rb->child[0]->parent = rb;//���ƶ�v�����Ҳൽ���ֵܵ����
				while (!v->key.empty()) {
					rb->key.insert(rb->key.begin(), v->key[v->key.size()-1]); v->key.erase(v->key.end()-1);//�ƶ�v�Ĺؼ��ֵ����ֵ���
					rb->same.insert(rb->same.begin(), v->same[v->same.size() - 1]); v->same.erase(v->same.end() - 1);//�ƶ��ؼ����Ӧ��ֵͬ����
					rb->child.insert(rb->child.begin(), v->child[v->child.size()-1]); v->child.erase(v->child.end() - 1);
					if (rb->child[0])rb->child[0]->parent = rb;//�����ƶ�vʣ�µĺ���
				}
				delete v, v = nullptr;//�ͷ�����ڵ��ڴ�
				v = p;//ʧ�⴫������
				continue;
			}
			}
	}

};

#endif // !BTREE_CPP_CPP

