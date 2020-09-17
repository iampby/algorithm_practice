#pragma once
#include "Graph.cpp"
#include<stack>
#include<map>
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
					 std::cout << u<< v << std::endl;
					}else {
					  type(v, u) = Etype::Cross;//����Ѿ�������Ϊ���
				  }
			  }
			  status(v) = VStatus::Visited;
		  }
		}
	  template<typename Tv, typename Te>
	   void Graph<Tv, Te>::DFS(int v, int &clock, std::queue<int>&qcc)
	  {
		   std::stack<int>S;//���븨��ջ
		 dTime(v) = ++clock;
		   status(v) = VStatus::Discover;
		  S.push(v);//��ʼ�����
		  qcc.push(v);
		   while (!S.empty())
		   {
			   int v =S.top();
			//   m.insert_or_assign(v, v);//��¼��
			  if (status(v) == VStatus::Visited) {
				  S.pop();//����Ѿ����ʹ���ɾ��,ִ����һ���������
				  continue;
			  }
			  int u = -1;
			for (u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
				   if (status(u) == VStatus::Undiscover) {
					   status(u) = VStatus::Discover;//���Ϊ�ѷ���
					   S.push(u);
					   qcc.push(u);
					   type(v, u) = Etype::Tree; parent(u) = v;//���ߣ�
					   dTime(v) = ++clock;
					   break;//����ѭ��ȥִ����һ���������
				   }else if(status(u)==VStatus::Visited){
					   type(v, u) = (dTime(v) < dTime(u)) ? Etype::Forward : Etype::Cross;
					   continue;//��һ���ھ�dfs
				   }else{
					   type(v, u) = Etype::Backward;
					   continue;//��һ���ھ�dfs
				   }
			   }
			if(u==-1)
			   status(v) = VStatus::Visited;//�ѷ������
		   }
		 }
	template<typename Tv, typename Te>
	Graph<Tv,Te>::Graph():
		n(0),e(0)
	{
		
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
	 std::vector<std::queue<int> > Graph<Tv, Te>::bfs(int s)
	 {
		 reset(); int clock = 0; int v = s;
		 std::vector<std::queue<int> >vqcc;//��ͬ����Ŀ�ĵ����
		 do
			 if (VStatus::Undiscover == status(v)) {
				 std::queue<int>qcc;
				BFS(v, clock, qcc);//������ͨ������
				if (qcc.size() > 1)vqcc.push_back(qcc);
			 }
while (s != (v = (++v%n)));//����ȫ����
		
		 return vqcc;
	 }

	 template<typename Tv, typename Te>
	 std::vector<std::queue<int> > Graph<Tv, Te>::dfs(int s)
	 {
		 reset(); int clock = 0; int v = s;
		 std::vector<std::queue<int> >vqcc;//��ͬ����Ŀ�ĵ����
		 do
			 if (VStatus::Undiscover == status(v)) {
				 std::queue<int>qcc;
				 DFS(v, clock, qcc);//������ͨ������
				 if (qcc.size() > 1)vqcc.push_back(qcc);
			 }
		 while (s != (v = (++v%n)));//����ȫ����

		 return vqcc;
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
		long long j = -1;
		LET&el = E[i];//�ڽ�����
		int length = el.size();
		if (length > 0) {
			Edge<Te>* &ev = *(el.begin());
			 j =(long long)ev->address;
			 if (n > 1) {
				 j = (j - (long long)&V[0]) / ((long long)&V[1] - (long long)&V[0]);
			return j;
			 }
			 else {
				 if (n == 1) {
					 if (j == (long long)&V[0])return 0;
				 }
				 else return -1;
			 }
		}else {
		return j;
		}
}
	template<typename Tv, typename Te>
	 int Graph<Tv, Te>::nextNbr(int i, int j)
	{
		 GH::Vertex<Tv>&vj =V[j];
		 LET &el = E[i];
		 TLEI it = el.begin();
		 TLECI end = el.end();
		 while (it !=end)
		 {
			 Edge<Te>* &ei= *it;
			 if (ei->address == &vj) {
				++it;
				if (it == end)return -1;
				Edge<Te>* &ej = *it;//��ȡ��һ���ڽӵ�
				 if (n > 1) {
					 j = ((long long)ej->address - (long long)&V[0]) / ((long long)&V[1] - (long long)&V[0]);
					 return j;
				 }else {//�������
					 if (n == 1) {
						 if ((long long)ej->address == (long long)&V[0])return 0;
					 }
					 else return -1;
				 }
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
			 if (i == -1) {
				V.push_back(tv);
				 r = n;
				 ++n;
				 std::list<Edge<Te>*>t;
				 E.push_back(t);
				 return r;
			 }else {
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
			 if(i<0||i>=n)return Tv();
			 GH::Vertex<Tv>&tv = V[i];//���涥��
			
			 //�����ڽ�������Դ
			 {
				 LET&el = E[i];//�ڽ�����
				 TLEI it = el.begin();
				 TLECI end = el.end();
				 while (it != end)
				 {
					 Edge<Te>*&ei = *it;
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
			//ɾ�����е����
			 size_t length =E.size();
			 for (size_t pos = 0; pos < length; pos++)
			 {
				 LET&el = E[pos];//�ڽ�����
				 TLEI it = el.begin();
				 TLECI end = el.end();
				 while (it != end)
				 {
					 Edge<Te>*&ei = *it;
					 if (&tv == ei->address) {
						 delete ei,ei = nullptr;
						 el.erase(it);
						 --e;
						 break;
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
		GH::Vertex<Tv>&jv = V[j];//��������
		LET&el = E[i];//�ڽ�����
		TLEI it = el.begin();
		TLECI end = el.end();
		while (it !=end)
		{
			Edge<Te>* &ev= *it;
			if (&jv == ev->address)
				return true;
			++it;
		}
		return false;
	}
	template<typename Tv, typename Te>
	 Te Graph<Tv, Te>::remove(int i, int j)
	{
		 GH::Vertex<Tv>&jv = V[j];//��������
		 LET&el = E[i];//�ڽ�����
		 TLEI it = el.begin();
		 TLECI end = el.end();
		 while (it != end)
		 {
			 Edge<Te>* &ev = *it;
			 if (&jv == ev->address) {
				 Te data = ev->data;
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
		  GH::Vertex<Tv>&jv = V[j];//��������
		  LET&el = E[i];//�ڽ�����
		  TLEI it = el.begin();
		  TLECI end = el.end();
		  while (it != end)
		  {
			  Edge<Te>* &ev = *it;
			  if (&jv == ev->address) {
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
		 GH::Vertex<Tv>&jv = V[j];//��������
		 LET&el = E[i];//�ڽ�����
		 TLEI it = el.begin();
		 TLECI end = el.end();
		 while (it != end)
		 {
			 Edge<Te>* &ev = *it;
			 if (&jv == ev->address) {
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
		  GH::Vertex<Tv>&jv = V[j];//��������
		  LET&el = E[i];//�ڽ�����
		  TLEI it = el.begin();
		  TLECI end = el.end();
		  while (it != end)
		  {
			  Edge<Te>* &ev = *it;
			  if (&jv == ev->address) {
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
		   if (i >= n || i < 0 || j >=n || j < 0)return;//�������
		   if (exists(i, j))return;
		   GH::Vertex<Tv>&tv = V[j];
		   Edge<Te>*v = new Edge<Te>(edge, weight);
		   v->address = &tv;
		   LET&el = E[i];
		   el.push_back(v);
		   ++e;
		   V[i].outDegree++;
		   V[j].inDegree--;
		}
	}


