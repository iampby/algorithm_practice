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
					}else{
					  type(v, u) = Etype::Cross;//如果已经处理则为跨边
				  }
			  }
			  status(v) = VStatus::Visited;
		  }
		}
	  template<typename Tv, typename Te>
	   void Graph<Tv, Te>::DFS(int v, int &clock, std::queue<int>&qcc)
	  {
		std::stack<int>S;//引入辅助栈 记录当前顶点位置
		int u = -1;//记录顶点的迭代位置
		 dTime(v) = ++clock;
		   status(v) = VStatus::Discover;
		  S.push(v);//初始化起点
		  qcc.push(v);
		   while (!S.empty())
		   {
			   //加个标签，用来跳出for循环而不适用if..else
			   label:
			   int v =S.top();
			//   m.insert_or_assign(v, v);//记录点
			  if (status(v) == VStatus::Visited) {
				  S.pop();//如果已经访问过，删除,执行下一次深度搜索
				  u = v;//记录迭代位置
				  continue;
			  }
			  if(u==-1)u= firstNbr(v);//邻接链表第一次迭代
			  else u = nextNbr(v, u);//获取顶点下一次迭代位置
			for (; -1 < u;) {
				switch ( status(u)) {
				case VStatus::Undiscover:
					   status(u) = VStatus::Discover;//标记为已发现
					  S.push(u);
					   qcc.push(u);
					   type(v, u) = Etype::Tree; parent(u) = v;//树边；
					   dTime(v) = ++clock;
					   u = -1;//第一次发现 标记迭代位置为-1
					  goto label;//跳出循环去执行下一次深度搜索
				case  VStatus::Visited:
					   type(v, u) = (dTime(v) < dTime(u)) ? Etype::Forward : Etype::Cross;
					   break;//下一个邻居dfs
				case VStatus::Discover:
					   type(v, u) = Etype::Backward;
					   break;//下一个邻居dfs
				   }
				u = nextNbr(v, u);
			   }
			if(u==-1)
			   status(v) = VStatus::Visited;//已访问完毕
		   }
		 }
	   template<typename Tv, typename Te>
	    bool Graph<Tv, Te>::DFSTSort(int v, std::stack<Tv>*S)
	   {
			std::stack<int>s;//引入辅助栈，记录迭代位置 栈顶为当前迭代位置
			int u = -1;//记录顶点的迭代位置
			s.push(v);
			status(v) = VStatus::Discover;
			while (!s.empty())
			{
				//加个标签，用来跳出for循环而不适用if..else
			label:
				int v = s.top();
				if (status(v) == VStatus::Visited) {
					s.pop();
					u = v;//记录顶点当前迭代位置
					continue;
				}
				if(u == -1)u = firstNbr(v);//邻接链表第一次迭代
				else u = nextNbr(v, u);//获取顶点下一次迭代位置
				while (-1<u) {
					switch (status(u)) {
					case VStatus::Undiscover:
					parent(u) = v;
						status(u) = VStatus::Discover;
						s.push(u);//插入当前位置
						u = -1;//第一次发现 标记迭代位置为-1
						goto label;
					case VStatus::Discover:
						return false;
					}
					u = nextNbr(v, u);
				}
				if (u == -1) {
					status(v) = VStatus::Visited;
					S->push(Vertex(v));//被访问即入栈
					}
			}
	   }

		template<typename Tv, typename Te>
		void Graph<Tv, Te>::BCC(int v, int & clock, std::stack<int>& S, std::list<int>& apSet)
		{
			std::stack<int>s;//引入辅助栈，记录顶点位置 栈顶为当前顶点位置
			int u=-1;//记录顶点的迭代位置
			s.push(v);
			S.push(v);//v被发现入栈
			fTime(v) = dTime(v) = ++clock;//用fTime代表heighest connected ancestor(hca)
			status(v) = VStatus::Discover;
		while (!s.empty())
			{
				//加个标签，用来跳出for循环而不适用if..else
			label:
				int v = s.top();
				if (status(v) == VStatus::Visited) {
					s.pop();
					u = v;//记录顶点当前迭代位置
					continue;
				}
				if(u == -1)u = firstNbr(v);//邻接链表第一次迭代
				for (; -1 < u; ) {
					switch (status(u)) {
					case VStatus::Undiscover:
						parent(u)=v;
						s.push(u);//进行下一次迭代
						S.push(u);//已访问则入记录栈
						fTime(u) = dTime(u) = ++clock;//用fTime代表heighest connected ancestor(hca)
						status(u) = VStatus::Discover;
u = -1;//第一次发现 标记迭代位置为-1
						goto label;
					case VStatus::Discover:
						if (u != parent(v)) {
							fTime(v) = std::min(fTime(v), dTime(u));//首先排除无向图单边的情况，然后遵循越小越高的原则，最高为树根,对hca进行更新
						}
break;
					case VStatus::Visited:
						if (parent(u) == v) {//树边
							if (fTime(u)<dTime(v)) {//如果hca小于v的时间标签 说明是后向边
								fTime(v) = std::min(fTime(u), fTime(v));//反过来 v也有一个后向边，更新时间标签
							}else {
								while (true)
								{
									int tv = S.top();
									if (tv == v) {
										apSet.push_back(v);//关节点找到
										break;
									}
									S.pop();//删除点以找到关节点
								}
							}
						}else {//非树边
							type(v, u) = (dTime(v) < dTime(u)) ? Etype::Forward : Etype::Cross;
						}
						break;
					}
					u = nextNbr(v, u);
					}
				if (u == -1) {
					status(v) = VStatus::Visited;
				}
			}
		}
		template<typename Tv, typename Te>
		void Graph<Tv, Te>::BCC(int v, int&clock, std::stack<int>&S, std::list<std::list<Edge<Te> > >&bccSet)
		{
			std::stack<int>s;//引入辅助栈，记录顶点位置 栈顶为当前顶点位置
			int u = -1;//记录顶点的迭代位置
			bool f = false;//标记 true为找到后向边，即不用新建一个双连通域
			s.push(v);
			S.push(v);//v被发现入栈
			fTime(v) = dTime(v) = ++clock;//用fTime代表heighest connected ancestor(hca)
			status(v) = VStatus::Discover;
			while (!s.empty())
			{
				//加个标签，用来跳出for循环而不适用if..else
			label:
				int v = s.top();
				if (status(v) == VStatus::Visited) {
					s.pop();
					u = v;//记录顶点当前迭代位置
					continue;
				}
				if (u == -1)u = firstNbr(v);//邻接链表第一次迭代
				for (; -1 < u; ) {
					switch (status(u)) {
					case VStatus::Undiscover:
						parent(u) = v;
						s.push(u);//进行下一次迭代
						S.push(u);//已访问则入记录栈
						fTime(u) = dTime(u) = ++clock;//用fTime代表heighest connected ancestor(hca)
						status(u) = VStatus::Discover;
						u = -1;//第一次发现 标记迭代位置为-1
						goto label;
					case VStatus::Discover:
						if (u != parent(v)) {
							f = true;//找到一个后向边 作为新的双连通域的起点
							Edge<Te>&et = getEdge(v, u);//获取边
							std::list<Edge<Te> >let;//新连通域
							let.push_back(et);//新连通域起点边
							bccSet.push_back(let);
							fTime(v) = std::min(fTime(v), dTime(u));//首先排除无向图单边的情况，然后遵循越小越高的原则，最高为树根,对hca进行更新
						}
						break;
					case VStatus::Visited:
						if (parent(u) == v) {//树边
							if (fTime(u) < dTime(v)) {//如果hca小于v的时间标签 说明是后向边
								fTime(v) = std::min(fTime(u), fTime(v));//反过来 v也有一个后向边，更新时间标签
							}
							else {
								if (!f) {
									std::list<Edge<Te> >let;//新连通域
									bccSet.push_back(let);
								}
								std::list<Edge<Te> >&let = *--(bccSet.end());
									while (true)
								{
									int tv = S.top();
									if (tv != v) {
									int& pv = parent(tv);
									Edge<Te>&et = getEdge(pv, tv);//获取边
										let.push_back(et);//新连通域起点边
										S.pop();//删除点以找到边
									}else break;
									}
								f = false;//重置后向边标记
							}
						}
						else {//非树边
							type(v, u) = (dTime(v) < dTime(u)) ? Etype::Forward : Etype::Cross;
						}
						break;
					}
					u = nextNbr(v, u);
				}
				if (u == -1) {
					status(v) = VStatus::Visited;
				}
			}
		}

		template<typename Tv, typename Te>
		 void Graph<Tv, Te>::BCC(int v, int & clock, std::stack<int>& S, std::list<int>&apSet, std::list<std::list<Edge<Te> > >& bccSet)
		{
			 std::stack<int>s;//引入辅助栈，记录顶点位置 栈顶为当前顶点位置
			 int u = -1;//记录顶点的迭代位置
			 bool f = false;//标记 true为找到后向边，即不用新建一个双连通域
			 s.push(v);
			 S.push(v);//v被发现入栈
			 fTime(v) = dTime(v) = ++clock;//用fTime代表heighest connected ancestor(hca)
			 status(v) = VStatus::Discover;
			 while (!s.empty())
			 {
				 //加个标签，用来跳出for循环而不适用if..else
			 label:
				 int v = s.top();
				 if (status(v) == VStatus::Visited) {
					 s.pop();
					 u = v;//记录顶点当前迭代位置
					 continue;
				 }
				 if (u == -1)u = firstNbr(v);//邻接链表第一次迭代
				 for (; -1 < u; ) {
					 switch (status(u)) {
					 case VStatus::Undiscover:
						 parent(u) = v;
						 s.push(u);//进行下一次迭代
						 S.push(u);//已访问则入记录栈
						 fTime(u) = dTime(u) = ++clock;//用fTime代表heighest connected ancestor(hca)
						 status(u) = VStatus::Discover;
						 u = -1;//第一次发现 标记迭代位置为-1
						 goto label;
					 case VStatus::Discover:
						 if (u != parent(v)) {
							 f = true;//找到一个后向边 作为新的双连通域的起点
							 Edge<Te>&et = getEdge(v, u);//获取边
							 std::list<Edge<Te> >let;//新连通域
							 let.push_back(et);//新连通域起点边
							 bccSet.push_back(let);
							 fTime(v) = std::min(fTime(v), dTime(u));//首先排除无向图单边的情况，然后遵循越小越高的原则，最高为树根,对hca进行更新
						 }
						 break;
					 case VStatus::Visited:
						 if (parent(u) == v) {//树边
							 if (fTime(u) < dTime(v)) {//如果hca小于v的时间标签 说明是后向边
								 fTime(v) = std::min(fTime(u), fTime(v));//反过来 v也有一个后向边，更新时间标签
							 }
							 else {
								 if (!f) {
									 std::list<Edge<Te> >let;//新连通域
									 bccSet.push_back(let);
								 }
								 std::list<Edge<Te> >&let = *--(bccSet.end());
								 while (true)
								 {
									 int tv = S.top();
									 if (tv != v) {
										 int& pv = parent(tv);
										 Edge<Te>&et = getEdge(pv, tv);//获取边
										 let.push_back(et);//新连通域起点边
										 S.pop();//删除点以找到边
									 }
									 else {
										 apSet.push_back(v);//关节点找到
										 break;
									 }
								 }
								 f = false;//重置后向边标记
							 }
						 }
						 else {//非树边
							 type(v, u) = (dTime(v) < dTime(u)) ? Etype::Forward : Etype::Cross;
						 }
						 break;
					 }
					 u = nextNbr(v, u);
				 }
				 if (u == -1) {
					 status(v) = VStatus::Visited;
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
		}


	 template<typename Tv, typename Te>
	 std::shared_ptr<std::list<std::queue<int> > > Graph<Tv, Te>::bfs(int s)
	 {
		 reset(); int clock = 0; int v = s;
		 std::list<std::queue<int> >*vqccv = new std::list<std::queue<int> >;
		 std::shared_ptr<std::list<std::queue<int> > > vqcc(vqccv);//连通分量点记录队列向量
		 std::weak_ptr<std::list<std::queue<int> > > pw(vqcc);//引入weak_ptr打破循环引用
		 do {
			 if (VStatus::Undiscover == status(v)) {
				 std::queue<int>qcc;
				 BFS(v, clock, qcc);//单个连通域搜索
				 vqcc->push_back(qcc);
			 }
		 } while (s != (v = (++v%n)));//遍历全部点
		
		 return vqcc;
	 }

	 template<typename Tv, typename Te>
	 std::shared_ptr<std::list<std::queue<int> > > Graph<Tv, Te>::dfs(int s)
	 {
		 reset(); int clock = 0; int v = s;
		 std::list<std::queue<int> >*vqccv = new std::list<std::queue<int> >;
		 std::shared_ptr<std::list<std::queue<int> > > vqcc(vqccv);//连通分量点记录队列向量
		 std::weak_ptr<std::list<std::queue<int> > > pw(vqcc);//引入weak_ptr打破循环引用
		 do
			 if (VStatus::Undiscover == status(v)) {
				 std::queue<int>qcc;
				 DFS(v, clock, qcc);//单个连通域搜索
				vqcc->push_back(qcc);//
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
	    std::list<int> Graph<Tv, Te>::getArtPoint(int s)
	   {
		   reset(); int clock = 0; int v = s; std::stack<int>S;//栈S记录已访问的顶点
		   std::list<int>apSet;//关节点集合
		   do
			   if (VStatus::Undiscover == status(v)) {
				   BCC(v, clock, S, apSet);//关节点版
				   int origin = S.top();
				   S.pop();//删除剩下来的起点
				   if (!apSet.empty()) {
					   if (apSet.back() == origin)
						   apSet.pop_back();//删除关节点中最后多余的一个起点
				   }
			   }
		   while (s!=(v=++v%n));
		   return apSet;
	   }

		template<typename Tv, typename Te>
		 std::list<std::list<Edge<Te> > > Graph<Tv, Te>::bcc(int s)
		{
			 reset(); int clock = 0; int v = s; std::stack<int>S;//栈S记录已访问的顶点
			 std::list<std::list<Edge<Te> > >bccSet;//关节点集合
			 do
				 if (VStatus::Undiscover == status(v)) {
					 BCC(v, clock, S, bccSet);//关节点版
					 S.pop();//删除剩下来的起点
				 }
			 while (s != (v = ++v%n));
			 return bccSet;
		}

		 template<typename Tv, typename Te>
		  void Graph<Tv, Te>::bcc(int s,std::list<int>& apSet, std::list<std::list<Edge<Te>>>& bccSet)
		 {
			  reset(); int clock = 0; int v = s; std::stack<int>S;//栈S记录已访问的顶点
			do
				  if (VStatus::Undiscover == status(v)) {
					  BCC(v, clock, S, apSet,bccSet);//关节点版
					  int origin = S.top();//起点
					  S.pop();//删除剩下来的起点
					  if (!apSet.empty()) {
						  if(apSet.back()==origin)
						  apSet.pop_back();//删除关节点中最后多余的一个起点
					  }
				  }
			  while (s != (v = ++v%n));
			 }

		  template<typename Tv, typename Te>
		  std::list<Edge<Te> >  Graph<Tv, Te>::prim(int s)
		  {
			  reset(); priority(s) = 0;
			  std::list<Edge<Te> > MST;
status(s) = VStatus::Visited;
			  std::priority_queue <PVertex, std::vector<PVertex>, PVertex >pq;//优先级队列记录优先级
			  for (int i = 0; i < n; i++) { //共需引入n个顶点和n-1条边 即n个点遍历，最短n-1条边
				for (int j = firstNbr(s); -1 < j; j = nextNbr(s, j)) //枚举s的所有邻居j
					  if ((status(j) == VStatus::Undiscover) && (priority(j) > weight(s, j))) //对邻接顶点j做松弛
					  {
						  priority(j) = weight(s, j); parent(j) = s;
						  pq.push(PVertex(j, priority(j)));//入队优先级队列
					  } //与Dijkstra算法唯一的不同之处
				
				  //找到最高优先级顶点，顶点迭代位置移动到最高优先级顶点
				  if (pq.empty())break;//防极端情况 同时也代表T树生成
					  s = pq.top().index;//顶点迭代位置移动到最高优先级顶点
				  pq.pop();//Tk扩展为Tk+1，把优先级记录从补集V\U去掉
				 //如果已访问过，说明是更新时多出来的点，在这里去掉
				  while (status(s) == VStatus::Visited) {
					  if (pq.empty()) {
						  goto label;//防极端情况 同时也代表T树生成
					  }
					  s = pq.top().index;//顶点迭代位置移动到最高优先级顶点
					  pq.pop();//Tk扩展为Tk+1，把优先级记录从补集V\U去掉
				  }
				  status(s) = VStatus::Visited;
				  int &p = parent(s);
				  if (-1 != p) {
					  type(p, s) = Etype::Tree; //引入当前的s
					  Edge<Te>&et = getEdge(p, s);//获取边
					  MST.push_back(et);//保存支撑树的边
				  }
			  }
		  label:;//结束标签，强制退出循环
return MST;
		  }

		  template<typename Tv, typename Te>
		   std::list<Edge<Te>> Graph<Tv, Te>::dijkstra(int s)
		  {
			   std::list<Edge<Te> >SPT;//最短路径树
			   reset(); priority(s) = 0;
			   status(s) = VStatus::Visited;
			   std::priority_queue <PVertex, std::vector<PVertex>, PVertex >pq;//优先级队列记录优先级
			   for (int i = 0; i < n; i++) { //共需引入n个顶点和n-1条边 即n个点遍历，最短n-1条边
				   for (int j = firstNbr(s); -1 < j; j = nextNbr(s, j)) { //枚举s的所有邻居j
					   int p = priority(s) + weight(s, j);
					   if ((status(j) == VStatus::Undiscover) && (priority(j) >p)) //对邻接顶点j做松弛
					   {
						   priority(j) =p; parent(j) = s;
						   pq.push(PVertex(j, priority(j)));//入队优先级队列
					   } //与Prim算法唯一的不同之处
				   }
				   //找到最高优先级顶点，顶点迭代位置移动到最高优先级顶点
				   if (pq.empty())break;//防极端情况 同时也代表T树生成
				   s = pq.top().index;//顶点迭代位置移动到最高优先级顶点
				   pq.pop();//Tk扩展为Tk+1，把优先级记录从补集V\U去掉
				  //如果已访问过，说明是更新时多出来的点，在这里去掉
				   while (status(s) == VStatus::Visited) {
					   if (pq.empty()) {
						   goto label;//防极端情况 同时也代表T树生成
					   }
					   s = pq.top().index;//顶点迭代位置移动到最高优先级顶点
					   pq.pop();//Tk扩展为Tk+1，把优先级记录从补集V\U去掉
				   }
				   status(s) = VStatus::Visited;
				   int &p = parent(s);
				   if (-1 != p) {
					   type(p, s) = Etype::Tree; //引入当前的s
					   Edge<Te>&et = getEdge(p, s);//获取边
					   SPT.push_back(et);//保存SPT的边
				   }
			   }
		   label:;//结束标签，强制退出循环
			  return SPT;
		  }

		

		  template<typename Tv, typename Te>
		  void Graph<Tv, Te>::PFS(int v, PU& priorityUpdater)
		  {
			 priority(v) =0; //初始化为0
			 parent(v) = -1;//起点无父节点
status(v) = VStatus::Visited;
			std::priority_queue <PVertex, std::vector<PVertex>, PVertex >pq;//优先级队列记录优先级
			std::cout << v << " ";
			
			while (true)
			 {
				 for (int w = firstNbr(v); -1 < w; w = nextNbr(v, w))
					 priorityUpdater(this, v, w,pq);//更新顶点w的父顶点及优先级
				 //找到最高优先级顶点，顶点迭代位置移动到最高优先级顶点
				 if (pq.empty())break;//T树生成
				v = pq.top().index;//顶点迭代位置移动到最高优先级顶点
				 pq.pop();//Tk扩展为Tk+1，把优先级记录从补集V\U去掉
				 //如果已访问过，说明是更新时多出来的点，在这里去掉
				 while (status(v) == VStatus::Visited) {
					 if (pq.empty()) {
						goto label;//防极端情况 同时也代表T树生成
					 }
					 v = pq.top().index;//顶点迭代位置移动到最高优先级顶点
					 pq.pop();//Tk扩展为Tk+1，把优先级记录从补集V\U去掉
					}
				 status(v) = VStatus::Visited;
				 int &p = parent(v);
				 if (-1 != p) {
					 type(p, v) = Etype::Tree; //引入当前的s
					 std::cout << v << " ";
					 std::cout << edge(p, v) << " ";
					}
				 }

		label:;//结束标签，强制退出循环
			
		  }

		  template<typename Tv, typename Te>
		  void Graph<Tv, Te>::pfs(int s, PU priorityUpdater)
		  {
			  reset(); int v = s;
			  std::cout << "PFS搜索：\n输出格式(vertex|edge ... )" << std::endl;
			  do 
				  if (status(v) == VStatus::Undiscover) {
					  PFS(v, priorityUpdater); //更新单个连通域的顶点优先级
				  }
			  while (s != (v=++v%n));//遍历顶点
			  std::cout <<  std::endl;
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
	 Edge<Te>& Graph<Tv, Te>::getEdge(int i, int j)
	{
		// TODO: 在此处插入 return 语句
		 LET&el = E[i];//邻接链表
		 TLEI it = el.begin();
		 TLECI end = el.end();
		 while (it != end)
		 {
			 Edge<Te>* &ev = *it;
			 if (j == ev->address) {
				 return  *ev;
			 }
			 ++it;
		 }
		 Edge<Te> err(Te(),-1);
		 return err;
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
		   if (i >= n || i < 0 || j >= n || j < 0) {
			   return;//极端情况
		   }
		   if (exists(i, j)) {
			   return;
		   }
		  Edge<Te>*v = new Edge<Te>(edge, weight);
		   v->address =j;
		   LET&el = E[i];
		   el.push_back(v);
		   ++e;
		   V[i].outDegree++;
		   V[j].inDegree++;
		}
	}


