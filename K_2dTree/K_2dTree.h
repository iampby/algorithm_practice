#ifndef K_2DTREE_H_H
#define K_2DTREE_H_H
/*
2d-Tree,��ʵ���˶������ά���ݵ�kd-tree���ɺͷ�Χ����,,ʵ����С��Χ���ұȱ����죬��Χ������������stl����װ��ԭ������ܶ࣡
*/
#include<vector>
#include<queue>
#include<algorithm>
namespace C2dTree {
	//��ά���� ע��û��ʵ��ָ�����͵İ汾��T1 T2����Ϊָ������ 
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
	//Ĭ�Ϸ�Χ��ѯȡ�õĽڵ����ݴ�����
	template<typename T1,typename T2>
	struct  ReS_Processor{
		void operator()(K_2dData<T1,T2>*d)
		{
			//std::cout << " find a data of group:(" << d->x << "," << d->y << ")\n";
		}
	};
	//2d-��
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
			bool m_dim;//ά��ָ�� 0Ϊx�Ữ��
			int m_left,m_right;
			int m_parent;
			K_2dData<T1,T2>* m_pBoundary;//������x�Ữ�ֿռ䣬Ҳ�ǽڵ��ά����
		};
		K_2dTree();
		~K_2dTree();
		//����
		void build(std::vector<K_2dData<T1, T2> > );//������
		template<typename Res_Processor=ReS_Processor<T1,T2> >
		int seach(T1 , T1 , T2 , T2 , Res_Processor= ReS_Processor<T1, T2>());//��Χ����
	protected:
		bool isLeaf(K_2dNode*n) 
		{
			return n->m_left == -1 && n->m_right == -1;
		}
	public:
		std::vector<K_2dNode*> m_nodes; //�������ڵ�
		int m_height;//���� ��û�м���
		int m_root;//����
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
	//�ö��а���η���ڵ�
	template<typename T1, typename T2>
	inline void K_2dTree<T1, T2>::build(std::vector<K_2dData<T1, T2> >  sets)
	{
		if (sets.empty())return;//�������
		if (m_nodes.size() > 0) {//���֮ǰ���ɵ��ڴ�
			this->~K_2dTree();
		}
		m_nodes.reserve(sets.size() *1.5);//1.5���ڴ�Ԥ��
		m_nodes.resize(sets.size());//�����㹻��С
		std::queue<std::vector<K_2dData<T1, T2> > >Q;//���븨�����У�����ع���
		std::queue<int >dQ;//parent���
		int n = 0;//��ǽڵ�λ��
		this->m_root = n;//�������
		Q.push(sets);//�����
		dQ.push(-1);
		//less�Ƚ���
		auto comp1 = [](K_2dData<T1, T2> a, K_2dData<T1, T2> b) {return a.x < b.x; };
		auto comp2 = [](K_2dData<T1, T2> a, K_2dData<T1, T2> b) {return a.y < b.y; };
			while (!Q.empty())
			{
				std::vector<K_2dData<T1, T2> > tvec=std::move(Q.front());
				Q.pop();//ɾ������
				int& tp = dQ.front();//���ڵ�����
				dQ.pop();
				K_2dNode*tparent = nullptr;
				if (tp > -1) tparent = (m_nodes[tp]);//���ڵ��ȡ
				bool tdim = (tparent)?tparent->m_dim:true;//���ڵ�ά��
				int tmid = tvec.size() / 2;//�м�ֵ
				if (tdim) {//��һά
					std::sort(tvec.begin(), tvec.end(), comp1);//����1
				}
				else {
					std::sort(tvec.begin(), tvec.end(), comp2);//����2
				}
					K_2dData<T1, T2> *td= new K_2dData<T1, T2>(tvec[tmid].x, tvec[tmid].y);
					K_2dNode*tn = new K_2dNode(!tdim,-1,-1,tp,td);//�����ڵ� ��������
					if (tparent) {//��������
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
					m_nodes[n] = tn;//����ڵ�
					//���Ӽ��ϴ���
					std::vector<K_2dData<T1, T2> > lc;
					std::copy(tvec.begin(), tvec.begin() + tmid , std::back_inserter(lc));
					if (lc.size() > 0) {
						Q.push(lc);//���Ӽ������
						dQ.push(n);
					}
					//�Һ��Ӽ��ϴ���
					std::vector<K_2dData<T1, T2> > rc;
					std::copy(tvec.begin()+tmid+1, tvec.end(), std::back_inserter(rc));
					if (rc.size() > 0) {
						Q.push(rc);//�Һ��Ӽ������
						dQ.push(n);
					}
++n;//����ƫ��1
			}
	}

	template<typename T1, typename T2>
	template<typename Res_Processor>
	inline int K_2dTree<T1, T2>::seach(T1 _1min, T1 _1max, T2 _2min, T2 _2max, Res_Processor rec_procr)
	{
		if (_1min > _1max || _2min > _2max || !m_nodes.size()) {
			std::cout << "range-searching is of failure...\n";
			return -1;//�˻�����
		}
		int count = 0;
		int pos= m_root;
		std::queue<int>Q;//��������
		Q.push(pos);
		while (!Q.empty())
		{
				pos = Q.front();
				Q.pop();
				if (pos==-1)continue;//�սڵ�
K_2dNode*n = m_nodes[pos];
			bool dim = n->m_dim;
				if (!dim) {
					if (n->m_pBoundary->x > _1max) {//����λ�����
						Q.push(n->m_left);
					}
					else if (n->m_pBoundary->x < _1min) {//����λ���ұ�
						Q.push(n->m_right);
					}else {//�ཻ
						if (!(n->m_pBoundary->y < _2min || n->m_pBoundary->y > _2max)) {//������
							++count;
							rec_procr(n->m_pBoundary);//�����ѯ����
							}
						Q.push(n->m_left);
						Q.push(n->m_right);
					}
				}
				else {
					if (n->m_pBoundary->y > _2max) {//����λ�����
						Q.push(n->m_left);
					}
					else if (n->m_pBoundary->y < _2min) {//����λ���ұ�
						Q.push(n->m_right);
					}
					else {//�ཻ
						if (!(n->m_pBoundary->x < _1min || n->m_pBoundary->x > _1max)) {//������
							++count;
							rec_procr(n->m_pBoundary);//�����ѯ����
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
