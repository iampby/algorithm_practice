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
		  std::queue<int> Q;//���븨������
		  status(v) = VStatus::Discover;
		  Q.push(v);//��ʼ�����
		  while (!Q.empty())
		  {
			  int v = Q.front();
			  Q.pop();//ȡ��Ԫ�ز�ɾ��
			  qcc.push(v);
			  dTime(v) = ++clock;
			 for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
				 if (status(u) == VStatus::Undiscover) {
					  status(u) = VStatus::Discover;//���Ϊ�ѷ���
					 Q.push(u);
					 type(v, u) = Etype::Tree; parent(u) = v;//���ߣ�
					}else{
					  type(v, u) = Etype::Cross;//����Ѿ�������Ϊ���
				  }
			  }
			  status(v) = VStatus::Visited;
		  }
		}
	  template<typename Tv, typename Te>
	   void Graph<Tv, Te>::DFS(int v, int &clock, std::queue<int>&qcc)
	  {
		std::stack<int>S;//���븨��ջ ��¼��ǰ����λ��
		int u = -1;//��¼����ĵ���λ��
		 dTime(v) = ++clock;
		   status(v) = VStatus::Discover;
		  S.push(v);//��ʼ�����
		  qcc.push(v);
		   while (!S.empty())
		   {
			   //�Ӹ���ǩ����������forѭ����������if..else
			   label:
			   int v =S.top();
			//   m.insert_or_assign(v, v);//��¼��
			  if (status(v) == VStatus::Visited) {
				  S.pop();//����Ѿ����ʹ���ɾ��,ִ����һ���������
				  u = v;//��¼����λ��
				  continue;
			  }
			  if(u==-1)u= firstNbr(v);//�ڽ������һ�ε���
			  else u = nextNbr(v, u);//��ȡ������һ�ε���λ��
			for (; -1 < u;) {
				switch ( status(u)) {
				case VStatus::Undiscover:
					   status(u) = VStatus::Discover;//���Ϊ�ѷ���
					  S.push(u);
					   qcc.push(u);
					   type(v, u) = Etype::Tree; parent(u) = v;//���ߣ�
					   dTime(v) = ++clock;
					   u = -1;//��һ�η��� ��ǵ���λ��Ϊ-1
					  goto label;//����ѭ��ȥִ����һ���������
				case  VStatus::Visited:
					   type(v, u) = (dTime(v) < dTime(u)) ? Etype::Forward : Etype::Cross;
					   break;//��һ���ھ�dfs
				case VStatus::Discover:
					   type(v, u) = Etype::Backward;
					   break;//��һ���ھ�dfs
				   }
				u = nextNbr(v, u);
			   }
			if(u==-1)
			   status(v) = VStatus::Visited;//�ѷ������
		   }
		 }
	   template<typename Tv, typename Te>
	    bool Graph<Tv, Te>::DFSTSort(int v, std::stack<Tv>*S)
	   {
			std::stack<int>s;//���븨��ջ����¼����λ�� ջ��Ϊ��ǰ����λ��
			int u = -1;//��¼����ĵ���λ��
			s.push(v);
			status(v) = VStatus::Discover;
			while (!s.empty())
			{
				//�Ӹ���ǩ����������forѭ����������if..else
			label:
				int v = s.top();
				if (status(v) == VStatus::Visited) {
					s.pop();
					u = v;//��¼���㵱ǰ����λ��
					continue;
				}
				if(u == -1)u = firstNbr(v);//�ڽ������һ�ε���
				else u = nextNbr(v, u);//��ȡ������һ�ε���λ��
				while (-1<u) {
					switch (status(u)) {
					case VStatus::Undiscover:
					parent(u) = v;
						status(u) = VStatus::Discover;
						s.push(u);//���뵱ǰλ��
						u = -1;//��һ�η��� ��ǵ���λ��Ϊ-1
						goto label;
					case VStatus::Discover:
						return false;
					}
					u = nextNbr(v, u);
				}
				if (u == -1) {
					status(v) = VStatus::Visited;
					S->push(Vertex(v));//�����ʼ���ջ
					}
			}
	   }

		template<typename Tv, typename Te>
		void Graph<Tv, Te>::BCC(int v, int & clock, std::stack<int>& S, std::list<int>& apSet)
		{
			std::stack<int>s;//���븨��ջ����¼����λ�� ջ��Ϊ��ǰ����λ��
			int u=-1;//��¼����ĵ���λ��
			s.push(v);
			S.push(v);//v��������ջ
			fTime(v) = dTime(v) = ++clock;//��fTime����heighest connected ancestor(hca)
			status(v) = VStatus::Discover;
		while (!s.empty())
			{
				//�Ӹ���ǩ����������forѭ����������if..else
			label:
				int v = s.top();
				if (status(v) == VStatus::Visited) {
					s.pop();
					u = v;//��¼���㵱ǰ����λ��
					continue;
				}
				if(u == -1)u = firstNbr(v);//�ڽ������һ�ε���
				for (; -1 < u; ) {
					switch (status(u)) {
					case VStatus::Undiscover:
						parent(u)=v;
						s.push(u);//������һ�ε���
						S.push(u);//�ѷ��������¼ջ
						fTime(u) = dTime(u) = ++clock;//��fTime����heighest connected ancestor(hca)
						status(u) = VStatus::Discover;
u = -1;//��һ�η��� ��ǵ���λ��Ϊ-1
						goto label;
					case VStatus::Discover:
						if (u != parent(v)) {
							fTime(v) = std::min(fTime(v), dTime(u));//�����ų�����ͼ���ߵ������Ȼ����ѭԽСԽ�ߵ�ԭ�����Ϊ����,��hca���и���
						}
break;
					case VStatus::Visited:
						if (parent(u) == v) {//����
							if (fTime(u)<dTime(v)) {//���hcaС��v��ʱ���ǩ ˵���Ǻ����
								fTime(v) = std::min(fTime(u), fTime(v));//������ vҲ��һ������ߣ�����ʱ���ǩ
							}else {
								while (true)
								{
									int tv = S.top();
									if (tv == v) {
										apSet.push_back(v);//�ؽڵ��ҵ�
										break;
									}
									S.pop();//ɾ�������ҵ��ؽڵ�
								}
							}
						}else {//������
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
			std::stack<int>s;//���븨��ջ����¼����λ�� ջ��Ϊ��ǰ����λ��
			int u = -1;//��¼����ĵ���λ��
			bool f = false;//��� trueΪ�ҵ�����ߣ��������½�һ��˫��ͨ��
			s.push(v);
			S.push(v);//v��������ջ
			fTime(v) = dTime(v) = ++clock;//��fTime����heighest connected ancestor(hca)
			status(v) = VStatus::Discover;
			while (!s.empty())
			{
				//�Ӹ���ǩ����������forѭ����������if..else
			label:
				int v = s.top();
				if (status(v) == VStatus::Visited) {
					s.pop();
					u = v;//��¼���㵱ǰ����λ��
					continue;
				}
				if (u == -1)u = firstNbr(v);//�ڽ������һ�ε���
				for (; -1 < u; ) {
					switch (status(u)) {
					case VStatus::Undiscover:
						parent(u) = v;
						s.push(u);//������һ�ε���
						S.push(u);//�ѷ��������¼ջ
						fTime(u) = dTime(u) = ++clock;//��fTime����heighest connected ancestor(hca)
						status(u) = VStatus::Discover;
						u = -1;//��һ�η��� ��ǵ���λ��Ϊ-1
						goto label;
					case VStatus::Discover:
						if (u != parent(v)) {
							f = true;//�ҵ�һ������� ��Ϊ�µ�˫��ͨ������
							Edge<Te>&et = getEdge(v, u);//��ȡ��
							std::list<Edge<Te> >let;//����ͨ��
							let.push_back(et);//����ͨ������
							bccSet.push_back(let);
							fTime(v) = std::min(fTime(v), dTime(u));//�����ų�����ͼ���ߵ������Ȼ����ѭԽСԽ�ߵ�ԭ�����Ϊ����,��hca���и���
						}
						break;
					case VStatus::Visited:
						if (parent(u) == v) {//����
							if (fTime(u) < dTime(v)) {//���hcaС��v��ʱ���ǩ ˵���Ǻ����
								fTime(v) = std::min(fTime(u), fTime(v));//������ vҲ��һ������ߣ�����ʱ���ǩ
							}
							else {
								if (!f) {
									std::list<Edge<Te> >let;//����ͨ��
									bccSet.push_back(let);
								}
								std::list<Edge<Te> >&let = *--(bccSet.end());
									while (true)
								{
									int tv = S.top();
									if (tv != v) {
									int& pv = parent(tv);
									Edge<Te>&et = getEdge(pv, tv);//��ȡ��
										let.push_back(et);//����ͨ������
										S.pop();//ɾ�������ҵ���
									}else break;
									}
								f = false;//���ú���߱��
							}
						}
						else {//������
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
			 std::stack<int>s;//���븨��ջ����¼����λ�� ջ��Ϊ��ǰ����λ��
			 int u = -1;//��¼����ĵ���λ��
			 bool f = false;//��� trueΪ�ҵ�����ߣ��������½�һ��˫��ͨ��
			 s.push(v);
			 S.push(v);//v��������ջ
			 fTime(v) = dTime(v) = ++clock;//��fTime����heighest connected ancestor(hca)
			 status(v) = VStatus::Discover;
			 while (!s.empty())
			 {
				 //�Ӹ���ǩ����������forѭ����������if..else
			 label:
				 int v = s.top();
				 if (status(v) == VStatus::Visited) {
					 s.pop();
					 u = v;//��¼���㵱ǰ����λ��
					 continue;
				 }
				 if (u == -1)u = firstNbr(v);//�ڽ������һ�ε���
				 for (; -1 < u; ) {
					 switch (status(u)) {
					 case VStatus::Undiscover:
						 parent(u) = v;
						 s.push(u);//������һ�ε���
						 S.push(u);//�ѷ��������¼ջ
						 fTime(u) = dTime(u) = ++clock;//��fTime����heighest connected ancestor(hca)
						 status(u) = VStatus::Discover;
						 u = -1;//��һ�η��� ��ǵ���λ��Ϊ-1
						 goto label;
					 case VStatus::Discover:
						 if (u != parent(v)) {
							 f = true;//�ҵ�һ������� ��Ϊ�µ�˫��ͨ������
							 Edge<Te>&et = getEdge(v, u);//��ȡ��
							 std::list<Edge<Te> >let;//����ͨ��
							 let.push_back(et);//����ͨ������
							 bccSet.push_back(let);
							 fTime(v) = std::min(fTime(v), dTime(u));//�����ų�����ͼ���ߵ������Ȼ����ѭԽСԽ�ߵ�ԭ�����Ϊ����,��hca���и���
						 }
						 break;
					 case VStatus::Visited:
						 if (parent(u) == v) {//����
							 if (fTime(u) < dTime(v)) {//���hcaС��v��ʱ���ǩ ˵���Ǻ����
								 fTime(v) = std::min(fTime(u), fTime(v));//������ vҲ��һ������ߣ�����ʱ���ǩ
							 }
							 else {
								 if (!f) {
									 std::list<Edge<Te> >let;//����ͨ��
									 bccSet.push_back(let);
								 }
								 std::list<Edge<Te> >&let = *--(bccSet.end());
								 while (true)
								 {
									 int tv = S.top();
									 if (tv != v) {
										 int& pv = parent(tv);
										 Edge<Te>&et = getEdge(pv, tv);//��ȡ��
										 let.push_back(et);//����ͨ������
										 S.pop();//ɾ�������ҵ���
									 }
									 else {
										 apSet.push_back(v);//�ؽڵ��ҵ�
										 break;
									 }
								 }
								 f = false;//���ú���߱��
							 }
						 }
						 else {//������
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
		 this->E.resize(g.E.size());//����һ��
		 this->n = g.n;
		 this->e = g.e;
		int length = g.E.size();
		 for (int i = 0; i < length; i++)
		 {
			 LET&gel = g.E[i];
			 LET el;//�¶�����ڽ�����
			TLECI end = gel.cend();
			 TLEI it = gel.begin();
			 while (it!=end)
			 {
				 Edge<Te>* &gev= *it;
				 Edge<Te>*ev = new Edge<Te>(gev->data,gev->weight,gev->type, gev->address);//�±�ֵ
				el.push_back(ev);
				 ++it;
			 }
			 this->E[i]=el;//������ֵ
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
		 std::shared_ptr<std::list<std::queue<int> > > vqcc(vqccv);//��ͨ�������¼��������
		 std::weak_ptr<std::list<std::queue<int> > > pw(vqcc);//����weak_ptr����ѭ������
		 do {
			 if (VStatus::Undiscover == status(v)) {
				 std::queue<int>qcc;
				 BFS(v, clock, qcc);//������ͨ������
				 vqcc->push_back(qcc);
			 }
		 } while (s != (v = (++v%n)));//����ȫ����
		
		 return vqcc;
	 }

	 template<typename Tv, typename Te>
	 std::shared_ptr<std::list<std::queue<int> > > Graph<Tv, Te>::dfs(int s)
	 {
		 reset(); int clock = 0; int v = s;
		 std::list<std::queue<int> >*vqccv = new std::list<std::queue<int> >;
		 std::shared_ptr<std::list<std::queue<int> > > vqcc(vqccv);//��ͨ�������¼��������
		 std::weak_ptr<std::list<std::queue<int> > > pw(vqcc);//����weak_ptr����ѭ������
		 do
			 if (VStatus::Undiscover == status(v)) {
				 std::queue<int>qcc;
				 DFS(v, clock, qcc);//������ͨ������
				vqcc->push_back(qcc);//
			 }
		 while (s != (v = (++v%n)));//����ȫ����

		 return vqcc;
	 }

	 template<typename Tv, typename Te>
	  std::shared_ptr<std::stack<Tv> > Graph<Tv, Te>::dfsTopologicalSort(int s)
	 {
		  reset(); int v = s;
		  std::stack<Tv>*sstv = new std::stack<Tv>;
		  std::shared_ptr<std::stack<Tv> >sst(sstv);//
		  std::weak_ptr<std::stack<Tv> > pw(sst);//����weak_ptr����ѭ������
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
		   std::weak_ptr<std::queue<Tv> > pw(sqt);//����weak_ptr����ѭ������
		   if (V[s].inDegree != 0 && V[s].outDegree == 0)return sqt; 
		   Graph<Tv, Te>TG(*this);
	    int size = TG.V.size();
		   //������ɱ߶���
		 for (int i = 0; i <size;) {
			 if (TG.V[i].inDegree == 0 && TG.V[i].outDegree == 0) {
				TG.remove(i);//ɾ������
				--size;//�������һ
			continue;
			 }
			 ++i;
		 }
		
		 int o = TG.findFirstOrigin();
		 while (o != -1) {
			 sqtv->push(TG.Vertex(o));//�������Ϊ0 �Ķ���
			 TG.remove(o);
		
			 o = TG.findFirstOrigin();
		 }
		 for (int i = 0; i < TG.V.size();++i) {
			 if (TG.V[i].inDegree == 0 && TG.V[i].outDegree == 0) {
				 sqtv->push(TG.Vertex(i));
} else {//�л�·
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
		   reset(); int clock = 0; int v = s; std::stack<int>S;//ջS��¼�ѷ��ʵĶ���
		   std::list<int>apSet;//�ؽڵ㼯��
		   do
			   if (VStatus::Undiscover == status(v)) {
				   BCC(v, clock, S, apSet);//�ؽڵ��
				   int origin = S.top();
				   S.pop();//ɾ��ʣ���������
				   if (!apSet.empty()) {
					   if (apSet.back() == origin)
						   apSet.pop_back();//ɾ���ؽڵ����������һ�����
				   }
			   }
		   while (s!=(v=++v%n));
		   return apSet;
	   }

		template<typename Tv, typename Te>
		 std::list<std::list<Edge<Te> > > Graph<Tv, Te>::bcc(int s)
		{
			 reset(); int clock = 0; int v = s; std::stack<int>S;//ջS��¼�ѷ��ʵĶ���
			 std::list<std::list<Edge<Te> > >bccSet;//�ؽڵ㼯��
			 do
				 if (VStatus::Undiscover == status(v)) {
					 BCC(v, clock, S, bccSet);//�ؽڵ��
					 S.pop();//ɾ��ʣ���������
				 }
			 while (s != (v = ++v%n));
			 return bccSet;
		}

		 template<typename Tv, typename Te>
		  void Graph<Tv, Te>::bcc(int s,std::list<int>& apSet, std::list<std::list<Edge<Te>>>& bccSet)
		 {
			  reset(); int clock = 0; int v = s; std::stack<int>S;//ջS��¼�ѷ��ʵĶ���
			do
				  if (VStatus::Undiscover == status(v)) {
					  BCC(v, clock, S, apSet,bccSet);//�ؽڵ��
					  int origin = S.top();//���
					  S.pop();//ɾ��ʣ���������
					  if (!apSet.empty()) {
						  if(apSet.back()==origin)
						  apSet.pop_back();//ɾ���ؽڵ����������һ�����
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
			  std::priority_queue <PVertex, std::vector<PVertex>, PVertex >pq;//���ȼ����м�¼���ȼ�
			  for (int i = 0; i < n; i++) { //��������n�������n-1���� ��n������������n-1����
				for (int j = firstNbr(s); -1 < j; j = nextNbr(s, j)) //ö��s�������ھ�j
					  if ((status(j) == VStatus::Undiscover) && (priority(j) > weight(s, j))) //���ڽӶ���j���ɳ�
					  {
						  priority(j) = weight(s, j); parent(j) = s;
						  pq.push(PVertex(j, priority(j)));//������ȼ�����
					  } //��Dijkstra�㷨Ψһ�Ĳ�֮ͬ��
				
				  //�ҵ�������ȼ����㣬�������λ���ƶ���������ȼ�����
				  if (pq.empty())break;//��������� ͬʱҲ����T������
					  s = pq.top().index;//�������λ���ƶ���������ȼ�����
				  pq.pop();//Tk��չΪTk+1�������ȼ���¼�Ӳ���V\Uȥ��
				 //����ѷ��ʹ���˵���Ǹ���ʱ������ĵ㣬������ȥ��
				  while (status(s) == VStatus::Visited) {
					  if (pq.empty()) {
						  goto label;//��������� ͬʱҲ����T������
					  }
					  s = pq.top().index;//�������λ���ƶ���������ȼ�����
					  pq.pop();//Tk��չΪTk+1�������ȼ���¼�Ӳ���V\Uȥ��
				  }
				  status(s) = VStatus::Visited;
				  int &p = parent(s);
				  if (-1 != p) {
					  type(p, s) = Etype::Tree; //���뵱ǰ��s
					  Edge<Te>&et = getEdge(p, s);//��ȡ��
					  MST.push_back(et);//����֧�����ı�
				  }
			  }
		  label:;//������ǩ��ǿ���˳�ѭ��
return MST;
		  }

		  template<typename Tv, typename Te>
		   std::list<Edge<Te>> Graph<Tv, Te>::dijkstra(int s)
		  {
			   std::list<Edge<Te> >SPT;//���·����
			   reset(); priority(s) = 0;
			   status(s) = VStatus::Visited;
			   std::priority_queue <PVertex, std::vector<PVertex>, PVertex >pq;//���ȼ����м�¼���ȼ�
			   for (int i = 0; i < n; i++) { //��������n�������n-1���� ��n������������n-1����
				   for (int j = firstNbr(s); -1 < j; j = nextNbr(s, j)) { //ö��s�������ھ�j
					   int p = priority(s) + weight(s, j);
					   if ((status(j) == VStatus::Undiscover) && (priority(j) >p)) //���ڽӶ���j���ɳ�
					   {
						   priority(j) =p; parent(j) = s;
						   pq.push(PVertex(j, priority(j)));//������ȼ�����
					   } //��Prim�㷨Ψһ�Ĳ�֮ͬ��
				   }
				   //�ҵ�������ȼ����㣬�������λ���ƶ���������ȼ�����
				   if (pq.empty())break;//��������� ͬʱҲ����T������
				   s = pq.top().index;//�������λ���ƶ���������ȼ�����
				   pq.pop();//Tk��չΪTk+1�������ȼ���¼�Ӳ���V\Uȥ��
				  //����ѷ��ʹ���˵���Ǹ���ʱ������ĵ㣬������ȥ��
				   while (status(s) == VStatus::Visited) {
					   if (pq.empty()) {
						   goto label;//��������� ͬʱҲ����T������
					   }
					   s = pq.top().index;//�������λ���ƶ���������ȼ�����
					   pq.pop();//Tk��չΪTk+1�������ȼ���¼�Ӳ���V\Uȥ��
				   }
				   status(s) = VStatus::Visited;
				   int &p = parent(s);
				   if (-1 != p) {
					   type(p, s) = Etype::Tree; //���뵱ǰ��s
					   Edge<Te>&et = getEdge(p, s);//��ȡ��
					   SPT.push_back(et);//����SPT�ı�
				   }
			   }
		   label:;//������ǩ��ǿ���˳�ѭ��
			  return SPT;
		  }

		

		  template<typename Tv, typename Te>
		  void Graph<Tv, Te>::PFS(int v, PU& priorityUpdater)
		  {
			 priority(v) =0; //��ʼ��Ϊ0
			 parent(v) = -1;//����޸��ڵ�
status(v) = VStatus::Visited;
			std::priority_queue <PVertex, std::vector<PVertex>, PVertex >pq;//���ȼ����м�¼���ȼ�
			std::cout << v << " ";
			
			while (true)
			 {
				 for (int w = firstNbr(v); -1 < w; w = nextNbr(v, w))
					 priorityUpdater(this, v, w,pq);//���¶���w�ĸ����㼰���ȼ�
				 //�ҵ�������ȼ����㣬�������λ���ƶ���������ȼ�����
				 if (pq.empty())break;//T������
				v = pq.top().index;//�������λ���ƶ���������ȼ�����
				 pq.pop();//Tk��չΪTk+1�������ȼ���¼�Ӳ���V\Uȥ��
				 //����ѷ��ʹ���˵���Ǹ���ʱ������ĵ㣬������ȥ��
				 while (status(v) == VStatus::Visited) {
					 if (pq.empty()) {
						goto label;//��������� ͬʱҲ����T������
					 }
					 v = pq.top().index;//�������λ���ƶ���������ȼ�����
					 pq.pop();//Tk��չΪTk+1�������ȼ���¼�Ӳ���V\Uȥ��
					}
				 status(v) = VStatus::Visited;
				 int &p = parent(v);
				 if (-1 != p) {
					 type(p, v) = Etype::Tree; //���뵱ǰ��s
					 std::cout << v << " ";
					 std::cout << edge(p, v) << " ";
					}
				 }

		label:;//������ǩ��ǿ���˳�ѭ��
			
		  }

		  template<typename Tv, typename Te>
		  void Graph<Tv, Te>::pfs(int s, PU priorityUpdater)
		  {
			  reset(); int v = s;
			  std::cout << "PFS������\n�����ʽ(vertex|edge ... )" << std::endl;
			  do 
				  if (status(v) == VStatus::Undiscover) {
					  PFS(v, priorityUpdater); //���µ�����ͨ��Ķ������ȼ�
				  }
			  while (s != (v=++v%n));//��������
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
		// TODO: �ڴ˴����� return ���
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
		LET&el = E[i];//�ڽ�����
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
		 if (i < 0 || i >= n)return -1;//�������
	     LET &el = E[i];
		 TLEI it = el.begin();
		 TLECI end = el.end();
		 while (it !=end)
		 {
			 Edge<Te>* &ei= *it;
			 if (ei->address ==j) {
				++it;
				if (it == end)return -1;
				Edge<Te>* &ej = *it;//��ȡ��һ���ڽӵ�
				return ej->address;
				}
			 ++it;
		 }
		return -1;
	}
	 template<typename Tv, typename Te>
	  VStatus & Graph<Tv, Te>::status(int i)
	 {
		 // TODO: �ڴ˴����� return ���
		  return V[i].status;
	 }
	  template<typename Tv, typename Te>
	   int & Graph<Tv, Te>::parent(int i)
	  {
		  // TODO: �ڴ˴����� return ���
		   return V[i].parent;
	  }
	   template<typename Tv, typename Te>
	    int & Graph<Tv, Te>::priority(int i)
	   {
		   // TODO: �ڴ˴����� return ���
			return V[i].priority;
	   }
		template<typename Tv, typename Te>
		inline int & Graph<Tv, Te>::dTime(int i)
		{
			// TODO: �ڴ˴����� return ���
			return V[i].dTime;
		}
		template<typename Tv, typename Te>
		int & Graph<Tv, Te>::fTime(int i)
		{
			// TODO: �ڴ˴����� return ���
			return V[i].fTime;
		}
		template<typename Tv, typename Te>
		 int Graph<Tv, Te>::insert(Tv const & vertex,int i)
		{
			 int r = -1;
			 if (i < -1 || i > n)return r;
			 GH::Vertex<Tv>tv(vertex);
			 if (i == -1||i==n) {//ĩβ���� o(1)ʱ��
				 V.push_back(tv);
				 r = n;
				 ++n;
				 std::list<Edge<Te>*>t;
				 E.push_back(t);
				 return r;
			 }else {
				 //�м���� O(n+e)
				 //�������±ߵ�ַ����
				 for (int i = 0; i < n; ++i)
				 {
					 LET&el = E[i];
					 TLEI it = el.begin();
					 TLECI end = el.cend();
					 while (it!=end)
					 {
						Edge<Te>*&ev = *it;
						if (ev->address >= i) {
							ev->address += 1;//������һ
						}
						++it;
					 }
				 }
				 //�����µĶ���ͱ�
				 {
						 auto it = V.begin();
						 std::advance(it, i);
						 V.insert(it, tv);
						 ++n;
					 }
					 //�����ڽ�����
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
			 GH::Vertex<Tv>&tv = V[i];//���涥��
			
			 //�����ڽ�������Դ
			 {
				 LET&el = E[i];//�ڽ�����
				TLEI it = el.begin();
				 TLECI end = el.end();
				 while (it != end)
				 {
					 Edge<Te>*&ei = *it;
					 V[ei->address].inDegree -= 1;//�ߣ�v,u����u�������-1
					 delete ei, ei = nullptr;
					 ++it;
				 }
				 e -= el.size();//��������
				 el.clear();
			 }
				 auto a = E.begin();
				 std::advance(a, i);
				 E.erase(a);//ɾ�����еĳ���
				 auto  at = V.begin();
				 std::advance(at, i);
				 V.erase(at);//����ɾ��
				 --n;//���¶�����
			//ɾ�����е���� ���µ�ַ����
			 size_t length =E.size();
			 for (size_t pos = 0; pos < length; pos++)
			 {
				 LET&el = E[pos];//�ڽ�����
				TLEI it = el.begin();
				 TLECI end = el.end();
				 while (it != end)
				 {
					 Edge<Te>*&ei = *it;
					 if (ei->address > i) {
						 ei->address -= 1;//������һ
					 } else if (i == ei->address) {
						 V[ei->address].outDegree -= 1;//�ߣ�v,u����v�������-1
						 delete ei,ei = nullptr;
						it= el.erase(it);//���µ�����
						 --e;
						 continue;//�����Ų� ��������
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
		LET&el = E[i];//�ڽ�����
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
		// TODO: �ڴ˴����� return ���
		 LET&el = E[i];//�ڽ�����
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
		LET&el = E[i];//�ڽ�����
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
		 // TODO: �ڴ˴����� return ���
		 LET&el = E[i];//�ڽ�����
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
		 // TODO: �ڴ˴����� return ���
		 LET&el = E[i];//�ڽ�����
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
		 // TODO: �ڴ˴����� return ���
		  LET&el = E[i];//�ڽ�����
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
			   return;//�������
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


