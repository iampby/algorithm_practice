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
		this->m_hitParentNode =t.m_hitParentNode; this->m_order = t.m_order; this->m_size = t.m_size;//初始化参数
		if (!t.m_root) {//有根才拷贝孩子
			this->m_root = nullptr;
			return;
		}
		this->m_root = new BTreeNode<T>(m_order);//建立树根
		this->m_root->child.clear();//先清理多余的空孩子
		std::queue<BTN(T)>q;//引入辅助队列按层次遍历拷贝
		std::queue<BTN(T)>tq;//引入辅助队列按层次遍历拷贝
		q.push(t.m_root);//树根入队
		tq.push(this->m_root);//本树树根入队
this->m_root->key = t.m_root->key;//复制根的关键码
this->m_root->same = t.m_root->same;//赋值根的相同值对象
		while (!q.empty())
		{
			BTN(T)p = q.front();
			q.pop();
			BTN(T)tp = tq.front();
			tq.pop();
		int count = p->child.size();
			for (int i = 0; i < count; ++i) {
				if (p->child[i]) {
					q.push(p->child[i]);//添加所有孩子入队
					BTN(T)n = new BTreeNode<T>(m_order);
					n->child.clear();//先清理多余的空孩子
					n->key = p->child[i]->key;//复制关键码
					n->same = p->child[i]->same;//复制相同值
					n->parent = tp;//向上联接
					tq.push(n);//本树孩子入队
					tp->child.insert(tp->child.end(),n);//添加孩子;向下联接
				}
				else {
					tp->child.insert(tp->child.end(), nullptr);//添加空孩子
				}
			}
			}
	}

	template<typename T>
	TREE_OUTOFLINE BTree<T>::BTree(BTree<T>&&t)
	{
		this->m_hitParentNode =std::move(t.m_hitParentNode); this->m_order = std::move(t.m_order); this->m_size = std::move(t.m_size);//初始化参数
		this->m_root = std::move(t.m_root);//树根移动
		t.m_hitParentNode = nullptr; t.m_order = -1; t.m_size = -1; t.m_root = nullptr;//析构安全
	}

	template<typename T>
	TREE_OUTOFLINE BTree<T> & BTree<T>::operator=(BTree<T> t) &
	{
		// TODO: 在此处插入 return 语句
		this->m_hitParentNode = std::move(t.m_hitParentNode); this->m_order = std::move(t.m_order); this->m_size = std::move(t.m_size);//初始化参数
		this->m_root = std::move(t.m_root);//树根移动
		t.m_hitParentNode = nullptr; t.m_order = -1; t.m_size = -1; t.m_root = nullptr;//析构安全
		return *this;
	}

	template<typename T>
	TREE_OUTOFLINE BTree<T>::~BTree()
	{
		if (!this->m_root)return;//没有根就不删除
		std::queue<BTN(T)>q;//引入辅助队列按层次遍历删除
		q.push(this->m_root);//树根入队
		while (!q.empty())
		{
			BTN(T)p = q.front();
			q.pop();
			int count = p->child.size();
			for (int i = 0; i < count; ++i) {
				if (p->child[i]) {
					q.push(p->child[i]);//添加所有孩子入队
				}
			}
			delete p, p = nullptr;//释放每个节点
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
		// TODO: 在此处插入 return 语句
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
		BTN(T)v = this->m_root; this->m_hitParentNode = nullptr;//从根节点开始遍历 
		while (v)
		{
			int rank = Find(v->key, d);
			if (rank < v->key.size() && v->key[rank] == d)return v;//找到关键码，返回命中节点
			this->m_hitParentNode = v;//记录命中节点的父亲
			v = v->child[rank];//移动到下一层
		}
		return v;
	}
	template<typename T>
	TREE_OUTOFLINE bool BTree<T>::insert(T const &d)
	{
		BTN(T)v = BTree<T>::search(d);
		if (v) {//插入重复值 这里选择在二维容器中记录=号意义上的相同值 
			int rank = Find(v->key, d);//查询适合插入的位置
			ReallocVector(v->same[rank]);//相同值数量可能很大,预分配内存 即不使用默认预分配策略
			v->same[rank].insert(v->same[rank].end(), d);//插入到容器末尾
			++m_size;//规模更新;
		}else {
			int rank = Find(this->m_hitParentNode->key, d);//查询适合插入的位置
			auto it1 = this->m_hitParentNode->key.begin();
			std::advance(it1, rank);
			auto it2 = this->m_hitParentNode->child.begin();
			std::advance(it2, rank+1);//插入位置为关键码的右边即序要加1
			this->m_hitParentNode->key.insert(it1, d);//再合适位置插入
			this->m_hitParentNode->same.insert(this->m_hitParentNode->same.begin()+rank,std::vector<T>());//再合适位置插入空相同值
			this->m_hitParentNode->child.insert(it2, nullptr);//再合适位置插入空孩子
			++m_size;//规模更新;
			solveOverFlow(this->m_hitParentNode);//如发生上溢则做分裂
		}
		return true;
	}
	template<typename T>
	TREE_OUTOFLINE bool BTree<T>::remove(T const &d)
	{
		BTN(T)v = BTree<T>::search(d); if (!v)return false;//不存在返回
		int rank = Find(v->key, d);//查找关键码的秩
		if (v->same[rank].size() > 0) {
			v->key[rank] = v->same[rank][0];//相同值左移出来
			v->same[rank].erase(v->same[rank].begin());//删除关键码
			--this->m_size;//更新规模
		}
		else {
			if (v->child[0]) {//非叶子找后继
				BTN(T)succ = v->child[rank + 1];
				while (succ->child[0])
				{
					succ = succ->child[0];//一直往左
				}
				//交换数据
				v->key[rank] = succ->key[0]; rank = 0; v = succ;
			}
			BTN(T)p = v->child[rank + 1];//获取实际删除目标
			v->key.erase(v->key.begin() + rank); v->child.erase(v->child.begin() + rank + 1);v->same.erase(v->same.begin()+rank);//整理容器
			delete p, p = nullptr;//释放内存
			--this->m_size;//更新规模
			solveUnderFlow(v);//检测是否发生下溢，如是 进行合并处理
		}
		return true;
	}
	template<typename T>
	TREE_OUTOFLINE void BTree<T>::solveOverFlow(BTN(T)v)
	{
		while (v->child.size() > m_order) {//发生上溢 
			int rank = m_order / 2;//要分裂的序
			BTN(T)u = new BTreeNode<T>(m_order);//分裂节点 注：默认构造函数是0个关键码一个分支
			{//移动v右边的关键码和相同值容器到u
				{
					auto it = v->key.begin();
					std::advance(it, rank + 1);
					u->key.insert(u->key.begin(), it, v->key.end());//复制右边到u
					v->key.erase(it, v->key.end());//移除右边
					}
				{
					auto it = v->same.begin();
					std::advance(it, rank + 1);
					u->same.insert(u->same.begin(), it, v->same.end());//复制右边到u
					v->same.erase(it, v->same.end());//移除右边
				}
			}
			{//移动v右边的分支到u
				auto it = v->child.begin();
				std::advance(it, rank + 1);
				u->child.insert(u->child.begin(), it, v->child.end()-1);//复制右边到u
				v->child.erase(it, v->child.end()-1);//移除右边
			}
			u->child[u->child.size()-1] = v->child[v->child.size()-1];//最后一个分支移动到u
			v->child.erase(v->child.end()-1);//移除最后一个分支
			//注：叶节点及内部节点的状态是统一的
			if (u->child[0])
			for (int i = 0; i < m_order - rank; ++i) {
				u->child[i]->parent = u;//更新u孩子的父节点为u
			}
			BTN(T)p = v->parent;
			if (!p) {//若根节点上溢则创建新的根节点处理上溢现象
				this->m_root = p = new BTreeNode<T>(m_order); p->child[0]=v; v->parent = p;//注：0个关键字默认一个分支，替换掉构造函数的空分支
			}
			auto it = v->key.begin();
			std::advance(it, rank);
			auto its = v->same.begin();
			std::advance(its, rank);
			T& key = *it;//获取上溢关键码
			std::vector<T> sames;sames.swap(*its);//获取上溢关键码相同值容器
			rank = Find(p->key, v->key[0]);//找到上溢节点在上一级中的分支位置
			v->key.erase(it);
			v->same.erase(its);
			it = p->key.begin(); std::advance(it, rank);
			p->key.insert(it, key);//插入在父类中的关键码
			p->same.insert(p->same.begin()+rank, sames);//插入在父类中的关键码相同值容器
			auto itc = p->child.begin(); std::advance(itc, rank + 1);
			p->child.insert(itc, u);//分裂节点父亲向下联接
			u->parent = p;//分裂节点向上联接
			v=p;//上溢传播检测
		}
 	}

	template<typename T>
	TREE_OUTOFLINE void BTree<T>::solveUnderFlow(BTN(T)v)
	{
		const int _m2 = (m_order + 1) / 2;//记录分支下限
		while (v->child.size()<(m_order+1)/2)//发生下溢，进行合并处理
		{
			BTN(T)p = v->parent;
			if (!p) {//是根节点 
				if (v->key.empty() && v->child[0]) {//有唯一非空节点即发生下溢，需要删除节点，重新制定根节点
					this->m_root = v->child[0]; this->m_root ->parent= nullptr;
					v->child[0] = nullptr;
					delete v, v = nullptr;//释放内存
				}
				return;
			}
			int rank = 0; while (p->child[rank] != v)++rank;//查找v在父亲中的秩(必然找到)
			//分三种情况处理下溢情况
			//1 左兄弟借一个最大值作为父类的关键码，父类的关键码作为v的最小关键码，然后调整左右孩子分支
			if (rank > 0) {
				BTN(T)lb = p->child[rank - 1];//左兄弟必然存在
					if (lb->child.size() > _m2) {//兄弟足够
						v->key.insert(v->key.begin(), p->key[rank - 1]);//父亲的节点移动到v作为最小值
						v->same.insert(v->same.begin(), p->same[rank - 1]);//移动关键码对应相同值容器
						p->key[rank-1]= lb->key[lb->key.size() - 1];//左兄弟最大值上移到parent
						p->same[rank - 1] = lb->same[lb->same.size() - 1];//移动关键码对应相同值容器
						v->child.insert(v->child.begin(), lb->child[lb->child.size() - 1]);//左兄弟最右孩子作为v最左孩子
						if (v->child[0])v->child[0]->parent = v;
						lb->key.erase(lb->key.end() - 1); lb->child.erase(lb->child.end() - 1),lb->same.erase(lb->same.end()-1);//左兄弟删除移动的对象
						return;//解决了下溢
					}
			}//至此代表没有左兄弟 或左兄弟不能借
			//2 右兄弟借一个最小值作为parent的关键码，parent的关键码作为v的最大关键码 然后调整左右孩子分支
			if (rank + 2 < p->child.size()) {
				BTN(T)rb = p->child[rank + 1];//右兄弟必然存在
					if (rb->child.size() > _m2) {//兄弟足够
						v->key.insert(v->key.end(), p->key[rank]);//父亲的节点移动到v作为最大值
						v->same.insert(v->same.end(), p->same[rank]);//移动关键码对应相同值容器
						p->key[rank]=rb->key[0];//右兄弟最小值上移到parent
						p->same[rank] = rb->same[0];//移动关键码对应相同值容器
						v->child.insert(v->child.end(), rb->child[0]);//左兄弟最右孩子作为v最左孩子
						if (v->child[v->child.size()-1])v->child[v->child.size() - 1]->parent = v;
						rb->key.erase(rb->key.begin()); rb->child.erase(rb->child.begin());rb->same.erase(rb->same.begin());//右兄弟删除移动的对象
						return;//解决了下溢
					}
			}//至此代表没有右兄弟 或右兄弟不能借
			//3 右兄弟或者左兄弟不存在 或者其包含的关键码都不足m/2（向上取值）个 进行合并处理
			if (0 < rank) {
				BTN(T)lb = p->child[rank - 1]; //左兄弟必然存在
				lb->key.insert(lb->key.end(), p->key[rank - 1]);//parent的关键码接入
				lb->same.insert(lb->same.end(), p->same[rank - 1]);//移动关键码对应相同值容器
				p->child.erase(p->child.begin() + rank); p->key.erase(p->key.begin() + rank - 1);p->same.erase(p->same.begin()+rank-1);//整理移除parent的关键字和孩子 关键码对应相同值容器
				lb->child.insert(lb->child.end(), v->child[0]); v->child.erase(v->child.begin());
				if (lb->child[lb->child.size() - 1])lb->child[lb->child.size() - 1]->parent = lb;//先移动v的最左侧到左兄弟的右侧
				while (!v->key.empty()) {
					lb->key.insert(lb->key.end(), v->key[0]); v->key.erase(v->key.begin());//移动v的关键字到左兄弟中
					lb->same.insert(lb->same.end(), v->same[0]); v->same.erase(v->same.begin());//移动关键码对应相同值容器
					lb->child.insert(lb->child.end(), v->child[0]); v->child.erase(v->child.begin());
					if (lb->child[lb->child.size() - 1])lb->child[lb->child.size() - 1]->parent = lb;//依次移动v剩下的孩子
				}
				delete v, v = nullptr;//释放下溢节点内存
				v = p;//失衡传播处理
				continue;
			}else {
				BTN(T)rb = p->child[rank + 1];//右兄弟必然存在
				rb->key.insert(rb->key.begin(), p->key[rank ]);//parent的关键码接入
				rb->same.insert(rb->same.begin(), p->same[rank]);//移动关键码对应相同值容器
				p->child.erase(p->child.begin() + rank); p->key.erase(p->key.begin() + rank ); p->same.erase(p->same.begin() + rank);//整理移除parent的关键字和孩子 关键码对应相同值容器
				rb->child.insert(rb->child.begin(), v->child[v->child.size()-1]); v->child.erase(v->child.end()-1);
				if (rb->child[0])rb->child[0]->parent = rb;//先移动v的最右侧到右兄弟的左侧
				while (!v->key.empty()) {
					rb->key.insert(rb->key.begin(), v->key[v->key.size()-1]); v->key.erase(v->key.end()-1);//移动v的关键字到右兄弟中
					rb->same.insert(rb->same.begin(), v->same[v->same.size() - 1]); v->same.erase(v->same.end() - 1);//移动关键码对应相同值容器
					rb->child.insert(rb->child.begin(), v->child[v->child.size()-1]); v->child.erase(v->child.end() - 1);
					if (rb->child[0])rb->child[0]->parent = rb;//依次移动v剩下的孩子
				}
				delete v, v = nullptr;//释放下溢节点内存
				v = p;//失衡传播处理
				continue;
			}
			}
	}

};

#endif // !BTREE_CPP_CPP

