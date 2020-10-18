#ifndef K_2DTREE_H_H
#define K_2DTREE_H_H
/*
2d-Tree,简单实现了对任意二维数据的kd-tree生成和范围查找,,实践中小范围查找比遍历快，大范围查找由于用了stl及封装的原因会慢很多！
*/
#include<vector>
#include<queue>
#include<algorithm>
namespace C2dTree {
	//二维数据 注：没有实现指针类型的版本，T1 T2不能为指针类型 
	template<typename T1=float, typename T2 = float>
	struct K_2dData
	{
		T1 x;
		T2 y;
		K_2dData() = default;
K_2dData(T1 &_x, T1 &_y) :
			x(_x), y(_y) {}
K_2dData(T1 const & _x, T1 const &_y) :
	x(_x), y(_y) {}
K_2dData&operator=(K_2dData const &k2d) {
	this->x = k2d.x; this->y = k2d.y;
	return *this;
}
	};
	//默认范围查询取得的节点数据处理器
	template<typename T1,typename T2>
	struct  ReS_Processor{
		void operator()(K_2dData<T1,T2>*d)
		{
			//std::cout << " find a data of group:(" << d->x << "," << d->y << ")\n";
		}
	};
	//2d-树
	template<typename T1 = float, typename T2 = float>
	class K_2dTree
	{
	public:
	
		struct K_2dNode
		{
			K_2dNode() : m_dim(false), m_left(-1), m_right(-1),m_parent(-1), m_pBoundary(nullptr) {}
			K_2dNode(bool _dim, int _left, int _right,int _parent, K_2dData<T1, T2>* _boundary)
				: m_dim(_dim), m_left(_left), m_right(_right),m_parent(_parent), m_pBoundary(_boundary) {}
			~K_2dNode() {
				delete m_pBoundary,m_pBoundary=nullptr;
			}
			bool m_dim;//维度指定 0为x轴划分
			int m_left,m_right;
			int m_parent;
			K_2dData<T1,T2>* m_pBoundary;//即是以x轴划分空间，也是节点二维数据
		};
		K_2dTree();
		~K_2dTree();
		//功能
		void build(std::vector<K_2dData<T1, T2> > );//生成树
		template<typename Res_Processor=ReS_Processor<T1,T2> >
		int seach(T1 , T1 , T2 , T2 , Res_Processor= ReS_Processor<T1, T2>());//范围查找
	protected:
		bool isLeaf(K_2dNode*n) 
		{
			return n->m_left == -1 && n->m_right == -1;
		}
	public:
		std::vector<K_2dNode*> m_nodes; //所有树节点
		int m_height;//树高 还没有计算
		int m_root;//树根
		};
	
	template<typename T1, typename T2>
	inline K_2dTree<T1, T2>::K_2dTree():
		m_height(-1),m_root(-1)
	{
	}

	template<typename T1, typename T2>
	inline K_2dTree<T1, T2>::~K_2dTree()
	{
		int _size = m_nodes.size();
		for (int i = 0; i < _size; ++i) {
			K_2dNode *&p= m_nodes[i];
			delete p, p = nullptr;
		}
		m_nodes.reserve(0);
		m_root = -1; m_height = -1;

	}
	//用队列按层次分配节点
	template<typename T1, typename T2>
	inline void K_2dTree<T1, T2>::build(std::vector<K_2dData<T1, T2> >  sets)
	{
		if (sets.empty())return;//极端情况
		if (m_nodes.size() > 0) {//清空之前生成的内存
			this->~K_2dTree();
		}
		m_nodes.reserve(sets.size() *1.5);//1.5倍内存预留
		m_nodes.resize(sets.size());//分配足够大小
		std::queue<std::vector<K_2dData<T1, T2> > >Q;//引入辅助队列，层次重构树
		std::queue<int >dQ;//parent标记
		int n = 0;//标记节点位置
		this->m_root = n;//树根标记
		Q.push(sets);//根入队
		dQ.push(-1);
		//less比较器
		auto comp1 = [](K_2dData<T1, T2> a, K_2dData<T1, T2> b) {return a.x < b.x; };
		auto comp2 = [](K_2dData<T1, T2> a, K_2dData<T1, T2> b) {return a.y < b.y; };
			while (!Q.empty())
			{
				std::vector<K_2dData<T1, T2> > tvec=std::move(Q.front());
				Q.pop();//删除集合
				int& tp = dQ.front();//父节点索引
				dQ.pop();
				K_2dNode*tparent = nullptr;
				if (tp > -1) tparent = (m_nodes[tp]);//父节点获取
				bool tdim = (tparent)?tparent->m_dim:true;//父节点维度
				int tmid = tvec.size() / 2;//中间值
				if (tdim) {//第一维
					std::sort(tvec.begin(), tvec.end(), comp1);//排序1
				}
				else {
					std::sort(tvec.begin(), tvec.end(), comp2);//排序2
				}
					K_2dData<T1, T2> *td= new K_2dData<T1, T2>(tvec[tmid].x, tvec[tmid].y);
					K_2dNode*tn = new K_2dNode(!tdim,-1,-1,tp,td);//建立节点 向上联接
					if (tparent) {//向下联接
						//std::cout<<"parent:(" << tparent->m_pBoundary->x << "," << tparent->m_pBoundary->y << ")\n";
						if (tparent->m_left == -1) {
							//std::cout << "left:(" << tn->m_pBoundary->x << "," << tn->m_pBoundary->y << ")\n";
							tparent->m_left = n;
						}
						else {
							//std::cout << "right:(" << tn->m_pBoundary->x << "," << tn->m_pBoundary->y << ")\n";
							tparent->m_right = n;
						}
					}
					else {
						//std::cout << "root:(" << tn->m_pBoundary->x << "," << tn->m_pBoundary->y << ")\n";
					}
					m_nodes[n] = tn;//保存节点
					//左孩子集合处理
					std::vector<K_2dData<T1, T2> > lc;
					std::copy(tvec.begin(), tvec.begin() + tmid , std::back_inserter(lc));
					if (lc.size() > 0) {
						Q.push(lc);//左孩子集合入队
						dQ.push(n);
					}
					//右孩子集合处理
					std::vector<K_2dData<T1, T2> > rc;
					std::copy(tvec.begin()+tmid+1, tvec.end(), std::back_inserter(rc));
					if (rc.size() > 0) {
						Q.push(rc);//右孩子集合入队
						dQ.push(n);
					}
++n;//向量偏移1
			}
	}

	template<typename T1, typename T2>
	template<typename Res_Processor>
	inline int K_2dTree<T1, T2>::seach(T1 _1min, T1 _1max, T2 _2min, T2 _2max, Res_Processor rec_procr)
	{
		if (_1min > _1max || _2min > _2max || !m_nodes.size()) {
			std::cout << "range-searching is of failure...\n";
			return -1;//退化处理
		}
		int count = 0;
		int pos= m_root;
		std::queue<int>Q;//辅助队列
		Q.push(pos);
		while (!Q.empty())
		{
				pos = Q.front();
				Q.pop();
				if (pos==-1)continue;//空节点
K_2dNode*n = m_nodes[pos];
			bool dim = n->m_dim;
				if (!dim) {
					if (n->m_pBoundary->x > _1max) {//区域位于左边
						Q.push(n->m_left);
					}
					else if (n->m_pBoundary->x < _1min) {//区域位于右边
						Q.push(n->m_right);
					}else {//相交
						if (!(n->m_pBoundary->y < _2min || n->m_pBoundary->y > _2max)) {//包含点
							++count;
							rec_procr(n->m_pBoundary);//处理查询数据
							}
						Q.push(n->m_left);
						Q.push(n->m_right);
					}
				}
				else {
					if (n->m_pBoundary->y > _2max) {//区域位于左边
						Q.push(n->m_left);
					}
					else if (n->m_pBoundary->y < _2min) {//区域位于右边
						Q.push(n->m_right);
					}
					else {//相交
						if (!(n->m_pBoundary->x < _1min || n->m_pBoundary->x > _1max)) {//包含点
							++count;
							rec_procr(n->m_pBoundary);//处理查询数据
						}
						Q.push(n->m_left);
						Q.push(n->m_right);
					}
				}
		}
		return count;
	}
}

#endif // !K_2DTREE_H_H
