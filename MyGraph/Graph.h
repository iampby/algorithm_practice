#pragma once
#include "Graph.cpp"
namespace GH{
	template<typename Tv, typename Te>
	 void Graph<Tv, Te>::reset()
	{
		 for (int i = 0; i < n; ++i) {
			 status(i) = VStatus::Undiscover; parent(i) = -1;
			 priority(i) = INT_MAX;
			 dTime(i) = -1; fTime(i) = -1;
			 LET &el = E[i];
			 TLEI it = el.begin();
			 TLECI end = el.end();
			 while (it != end)
			 {
				 Edge<Te>*&ev = *it;
				 ev->type = Etype::Undetermine;
				 ++it;
			 }
		 }
	}
	 template<typename Tv, typename Te>
	  void Graph<Tv, Te>::BFS(int v, int &clock, std::queue<int>&qcc)
	 {
		  std::queue<int> Q;//引入辅助队列
		  status(v) = VStatus::Discover;
		  Q.push(v);//初始化起点
		  while (!Q.empty())
		  {
			  int v = Q.front();
			  Q.pop();//取出元素并删除
			  qcc.push(v);
			  dTime(v) = ++clock;
			 for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
				 if (status(u) == VStatus::Undiscover) {
					  status(u) = VStatus::Discover;//标记为已发现
					 Q.push(u);
					 type(v, u) = Etype::Tree; parent(u) = v;//树边；
					 std::cout << u<< v << std::endl;
					}else {
					  type(v, u) = Etype::Cross;//如果已经处理则为跨边
				  }
			  }
			  status(v) = VStatus::Visited;
		  }
		}
	  template<typename Tv, typename Te>
	   void Graph<Tv, Te>::DFS(int v, int &clock, std::queue<int>&qcc)
	  {
		   std::stack<int>S;//引入辅助栈
		 dTime(v) = ++clock;
		   status(v) = VStatus::Discover;
		  S.push(v);//初始化起点
		  qcc.push(v);
		   while (!S.empty())
		   {
			   int v =S.top();
			//   m.insert_or_assign(v, v);//记录点
			  if (status(v) == VStatus::Visited) {
				  S.pop();//如果已经访问过，删除,执行下一次深度搜索
				  continue;
			  }
			  int u = -1;
			for (u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
				   if (status(u) == VStatus::Undiscover) {
					   status(u) = VStatus::Discover;//标记为已发现
					   S.push(u);
					   qcc.push(u);
					   type(v, u) = Etype::Tree; parent(u) = v;//树边；
					   dTime(v) = ++clock;
					   break;//跳出循环去执行下一次深度搜索
				   }else if(status(u)==VStatus::Visited){
					   type(v, u) = (dTime(v) < dTime(u)) ? Etype::Forward : Etype::Cross;
					   continue;//下一个邻居dfs
				   }else{
					   type(v, u) = Etype::Backward;
					   continue;//下一个邻居dfs
				   }
			   }
			if(u==-1)
			   status(v) = VStatus::Visited;//已访问完毕
		   }
		 }
	   template<typename Tv, typename Te>
	    bool Graph<Tv, Te>::DFSTSort(int v, std::stack<Tv>*S)
	   {
			std::stack<int>s;//引入辅助栈，记录迭代位置 栈顶为当前迭代位置
			s.push(v);
			status(v) = VStatus::Discover;
			while (!s.empty())
			{
				int v = s.top();
				if (status(v) == VStatus::Visited) {
					s.pop();
					continue;
				}
				int u = -1;
				for (u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
					VStatus& ss = status(u);
					//std::cout << "u=" << u << "s=" << (int)ss <<"v="<<v<< std::endl;
					if (ss == VStatus::Undiscover) {
						parent(u) = v;
						ss = VStatus::Discover;
						s.push(u);//当前位置
						std::cout << "v=" << v << "u=" << u << std::endl;
						break;
					}else if (ss == VStatus::Discover) {
						std::cout << "not directed acicling graph" << std::endl;
						return false;
					}
				}
				if (u == -1) {
					status(v) = VStatus::Visited;
					S->push(Vertex(v));//被访问即入栈
					}
			}
	   }

	

	template<typename Tv, typename Te>
	Graph<Tv,Te>::Graph():
		n(0),e(0)
	{
		
	}
	template<typename Tv, typename Te>
	 Graph<Tv, Te>::Graph(Graph<Tv,Te>  &g)
	{
		 this->V = g.V;
		 this->E.resize(g.E.size());//扩容一致
		 this->n = g.n;
		 this->e = g.e;
		int length = g.E.size();
		 for (int i = 0; i < length; i++)
		 {
			 LET&gel = g.E[i];
			 LET el;//新对象的邻接链表
			TLECI end = gel.cend();
			 TLEI it = gel.begin();
			 while (it!=end)
			 {
				 Edge<Te>* &gev= *it;
				 Edge<Te>*ev = new Edge<Te>(gev->data,gev->weight,gev->type, gev->address);//新边值
				el.push_back(ev);
				 ++it;
			 }
			 this->E[i]=el;//容器赋值
		 }
	}
	template<typename Tv, typename Te>
	 Graph<Tv, Te>::~Graph()
	{
		 size_t length = E.size();
		 for (size_t i = 0; i < length; i++)
		 {
			 LET&el = E[i];
			 TLEI b = el.begin();
			 TLECI end = el.end();
			 while (b != end) {
				 Edge<Te>*&ev = *b;
				 delete ev, ev = nullptr;
				 ++b;
			 }
			 el.clear();
		 }
		 std::cout << "~Graph()"<<std::endl;
	}

	 template<typename Tv, typename Te>
	 std::shared_ptr<std::vector<std::queue<int> > > Graph<Tv, Te>::bfs(int s)
	 {
		 reset(); int clock = 0; int v = s;
		 std::vector<std::queue<int> >*vqccv = new std::vector<std::queue<int> >;
		 std::shared_ptr<std::vector<std::queue<int> > > vqcc(vqccv);//连通分量点记录队列向量
		 std::weak_ptr<std::vector<std::queue<int> > > pw(vqcc);//引入weak_ptr打破循环引用
		 do
			 if (VStatus::Undiscover == status(v)) {
				 std::queue<int>qcc;
				BFS(v, clock, qcc);//单个连通域搜索
				if (qcc.size() > 1)vqcc->push_back(qcc);
			 }
while (s != (v = (++v%n)));//遍历全部点
		
		 return vqcc;
	 }

	 template<typename Tv, typename Te>
	 std::shared_ptr<std::vector<std::queue<int> > > Graph<Tv, Te>::dfs(int s)
	 {
		 reset(); int clock = 0; int v = s;
		 std::vector<std::queue<int> >*vqccv = new std::vector<std::queue<int> >;
		 std::shared_ptr<std::vector<std::queue<int> > > vqcc(vqccv);//连通分量点记录队列向量
		 std::weak_ptr<std::vector<std::queue<int> > > pw(vqcc);//引入weak_ptr打破循环引用
		 do
			 if (VStatus::Undiscover == status(v)) {
				 std::queue<int>qcc;
				 DFS(v, clock, qcc);//单个连通域搜索
				 if (qcc.size() > 1)vqcc->push_back(qcc);
			 }
		 while (s != (v = (++v%n)));//遍历全部点

		 return vqcc;
	 }

	 template<typename Tv, typename Te>
	  std::shared_ptr<std::stack<Tv> > Graph<Tv, Te>::dfsTopologicalSort(int s)
	 {
		  reset(); int v = s;
		  std::stack<Tv>*sstv = new std::stack<Tv>;
		  std::shared_ptr<std::stack<Tv> >sst(sstv);//
		  std::weak_ptr<std::stack<Tv> > pw(sst);//引入weak_ptr打破循环引用
		  do {
			  if (status(v) == VStatus::Undiscover)
				  if (!DFSTSort(v, sstv)) {
					  while (!sstv->empty())sstv->pop();
					  break;
				  }
		  } while (s!=(v=++v%n));
		 return sst;
	 }

	  template<typename Tv, typename Te>
	   std::shared_ptr<std::queue<Tv> > Graph<Tv, Te>::bfsTopologicalSort(int s)
	  {
		   reset(); int v = s; int clock = 0;
		   std::queue<Tv>*sqtv = new std::queue<Tv>;
		   std::shared_ptr<std::queue<Tv> >sqt(sqtv);//
		   std::weak_ptr<std::queue<Tv> > pw(sqt);//引入weak_ptr打破循环引用
		   if (V[s].inDegree != 0 && V[s].outDegree == 0)return sqt; 
		   Graph<Tv, Te>TG(*this);
	    int size = TG.V.size();
		   //清除不成边顶点
		 for (int i = 0; i <size;) {
			 if (TG.V[i].inDegree == 0 && TG.V[i].outDegree == 0) {
				TG.remove(i);//删除顶点
				--size;//标记数减一
			continue;
			 }
			 ++i;
		 }
		
		 int o = TG.findFirstOrigin();
		 while (o != -1) {
			 sqtv->push(TG.Vertex(o));//保存入度为0 的顶点
			 TG.remove(o);
		
			 o = TG.findFirstOrigin();
		 }
		 for (int i = 0; i < TG.V.size();++i) {
			 if (TG.V[i].inDegree == 0 && TG.V[i].outDegree == 0) {
				 sqtv->push(TG.Vertex(i));
} else {//有环路
				 while (!sqtv->empty())
				 {
					 sqtv->pop();
				 }
				return sqt;
			 }
			}
		   return sqt;
	  }

	 template<typename Tv, typename Te>
	  int Graph<Tv, Te>::findFirstOrigin()
	 {
		  for (int i = 0; i < n; ++i) {
			  if (V[i].inDegree == 0 && V[i].outDegree != 0) {
				  return i;
			  }
		  }
		  return -1;
	 }

	  template<typename Tv, typename Te>
	   int Graph<Tv, Te>::nextOrigin(int i)
	  {
		   i += 1;
		   if (i < 0 || i >= n)return -1;
		   for (; i < n; ++i) {
			   if (V[i].inDegree == 0 && V[i].outDegree != 0) {
				   return i;
			   }
		   }
		   return -1;
	}

	
	template<typename Tv, typename Te>
	 Tv & Graph<Tv, Te>::Vertex(int i)
	{
		return V[i].data;
		// TODO: 在此处插入 return 语句
	}
	 template<typename Tv, typename Te>
	 int Graph<Tv, Te>::inDegree(int i)
	 {
		 return V[i].inDegree;
	 }
	 template<typename Tv, typename Te>
	int Graph<Tv, Te>::outDegree(int i)
	 {
		return V[i].outDegree;
	 }
	template<typename Tv, typename Te>
	int Graph<Tv, Te>::firstNbr(int i)
	{
		LET&el = E[i];//邻接链表
		int length = el.size();
		if (length > 0) {
			Edge<Te>* &ev = *(el.begin());
			return ev->address;
		}else {
		return -1;
		}
}
	template<typename Tv, typename Te>
	 int Graph<Tv, Te>::nextNbr(int i, int j)
	{
		 if (i < 0 || i >= n)return -1;//极端情况
	     LET &el = E[i];
		 TLEI it = el.begin();
		 TLECI end = el.end();
		 while (it !=end)
		 {
			 Edge<Te>* &ei= *it;
			 if (ei->address ==j) {
				++it;
				if (it == end)return -1;
				Edge<Te>* &ej = *it;//获取下一个邻接点
				return ej->address;
				}
			 ++it;
		 }
		return -1;
	}
	 template<typename Tv, typename Te>
	  VStatus & Graph<Tv, Te>::status(int i)
	 {
		 // TODO: 在此处插入 return 语句
		  return V[i].status;
	 }
	  template<typename Tv, typename Te>
	   int & Graph<Tv, Te>::parent(int i)
	  {
		  // TODO: 在此处插入 return 语句
		   return V[i].parent;
	  }
	   template<typename Tv, typename Te>
	    int & Graph<Tv, Te>::priority(int i)
	   {
		   // TODO: 在此处插入 return 语句
			return V[i].priority;
	   }
		template<typename Tv, typename Te>
		inline int & Graph<Tv, Te>::dTime(int i)
		{
			// TODO: 在此处插入 return 语句
			return V[i].dTime;
		}
		template<typename Tv, typename Te>
		int & Graph<Tv, Te>::fTime(int i)
		{
			// TODO: 在此处插入 return 语句
			return V[i].fTime;
		}
		template<typename Tv, typename Te>
		 int Graph<Tv, Te>::insert(Tv const & vertex,int i)
		{
			 int r = -1;
			 if (i < -1 || i > n)return r;
			 GH::Vertex<Tv>tv(vertex);
			 if (i == -1||i==n) {//末尾插入 o(1)时间
				 V.push_back(tv);
				 r = n;
				 ++n;
				 std::list<Edge<Te>*>t;
				 E.push_back(t);
				 return r;
			 }else {
				 //中间插入 O(n+e)
				 //遍历更新边地址索引
				 for (int i = 0; i < n; ++i)
				 {
					 LET&el = E[i];
					 TLEI it = el.begin();
					 TLECI end = el.cend();
					 while (it!=end)
					 {
						Edge<Te>*&ev = *it;
						if (ev->address >= i) {
							ev->address += 1;//索引加一
						}
						++it;
					 }
				 }
				 //插入新的顶点和边
				 {
						 auto it = V.begin();
						 std::advance(it, i);
						 V.insert(it, tv);
						 ++n;
					 }
					 //插入邻接链表
					 auto it = E.begin();
					 std::advance(it, i);
					 std::list<Edge<Te>*>t;
					 E.insert(it, t);
					return i;
			 }
		}
		template<typename Tv, typename Te>
		 Tv Graph<Tv, Te>::remove(int i)
		{
			 if (i < 0 || i >= n) {
				 std::cout << "err!" << std::endl;
				 return Tv();
			 }
			 GH::Vertex<Tv>&tv = V[i];//保存顶点
			
			 //清理邻接链表资源
			 {
				 LET&el = E[i];//邻接链表
				TLEI it = el.begin();
				 TLECI end = el.end();
				 while (it != end)
				 {
					 Edge<Te>*&ei = *it;
					 V[ei->address].inDegree -= 1;//边（v,u）的u顶点入度-1
					 delete ei, ei = nullptr;
					 ++it;
				 }
				 e -= el.size();//边数控制
				 el.clear();
			 }
				 auto a = E.begin();
				 std::advance(a, i);
				 E.erase(a);//删除所有的出边
				 auto  at = V.begin();
				 std::advance(at, i);
				 V.erase(at);//顶点删除
				 --n;//更新顶点数
			//删除所有的入边 更新地址索引
			 size_t length =E.size();
			 for (size_t pos = 0; pos < length; pos++)
			 {
				 LET&el = E[pos];//邻接链表
				TLEI it = el.begin();
				 TLECI end = el.end();
				 while (it != end)
				 {
					 Edge<Te>*&ei = *it;
					 if (ei->address > i) {
						 ei->address -= 1;//索引减一
					 } else if (i == ei->address) {
						 V[ei->address].outDegree -= 1;//边（v,u）的v顶点出度-1
						 delete ei,ei = nullptr;
						it= el.erase(it);//更新迭代器
						 --e;
						 continue;//继续排查 更新索引
					 }
					 ++it;
				 }
}
			 return tv.data;
		}
	template<typename Tv, typename Te>
	bool Graph<Tv, Te>::exists(int i, int j)
	{
		if (i >= n || i < 0 || j >= n || j < 0)return false;
		LET&el = E[i];//邻接链表
		TLEI it = el.begin();
		TLECI end = el.end();
		while (it !=end)
		{
			Edge<Te>* &ev= *it;
			if (j == ev->address)
				return true;
			++it;
		}
		return false;
	}
	template<typename Tv, typename Te>
	 Te Graph<Tv, Te>::remove(int i, int j)
	{
		 if (i < 0 || i >= n || j < 0 || j >= n)return Te();
		LET&el = E[i];//邻接链表
		 TLEI it = el.begin();
		 TLECI end = el.end();
		 while (it != end)
		 {
			 Edge<Te>* &ev = *it;
			 if (j == ev->address) {
				 Te& data = ev->data;
				 el.erase(it);
				 delete ev, ev = nullptr;
				 --e;
				 --(V[i].outDegree);
				 --(V[j].inDegree);
				 return data;
			 }
			 ++it;
		 }
		return Te();
	}
	 template<typename Tv, typename Te>
	  Etype & Graph<Tv, Te>::type(int i, int j)
	 {
		 // TODO: 在此处插入 return 语句
		 LET&el = E[i];//邻接链表
		  TLEI it = el.begin();
		  TLECI end = el.end();
		  while (it != end)
		  {
			  Edge<Te>* &ev = *it;
			  if (j == ev->address) {
				return  ev->type;
			  }
			  ++it;
		  }
		  Etype err = Etype::Undetermine;
		  return err;
	 }
	 template<typename Tv, typename Te>
	 Te & Graph<Tv, Te>::edge(int i, int j)
	 {
		 // TODO: 在此处插入 return 语句
		 LET&el = E[i];//邻接链表
		 TLEI it = el.begin();
		 TLECI end = el.end();
		 while (it != end)
		 {
			 Edge<Te>* &ev = *it;
			 if (j == ev->address) {
				 return  ev->data;
			 }
			 ++it;
		 }
		 Te err = Te();
		return err;
	 }
	 template<typename Tv, typename Te>
	  int & Graph<Tv, Te>::weight(int i, int j)
	 {
		 // TODO: 在此处插入 return 语句
		  LET&el = E[i];//邻接链表
		  TLEI it = el.begin();
		  TLECI end = el.end();
		  while (it != end)
		  {
			  Edge<Te>* &ev = *it;
			  if (j == ev->address) {
				  return  ev->weight;
			  }
			  ++it;
		  }
		  int err=-1;
		  return err;
	 }
	  template<typename Tv, typename Te>
	   void Graph<Tv, Te>::insert(Te const & edge, int weight, int i, int j)
	  {
		   if (i >= n || i < 0 || j >=n || j < 0)return;//极端情况
		   if (exists(i, j))return;
		   Edge<Te>*v = new Edge<Te>(edge, weight);
		   v->address =j;
		   LET&el = E[i];
		   el.push_back(v);
		   ++e;
		   V[i].outDegree++;
		   V[j].inDegree++;
		}
	}


