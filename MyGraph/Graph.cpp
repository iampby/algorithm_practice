#pragma once
#include<list>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<memory>
namespace GH {
#define TLEI typename std::list<Edge<Te>*>::iterator  //邻接链表迭代器声明
#define TLECI typename std::list<Edge<Te>*>::const_iterator//邻接链表常量迭代器声明
#define LET std::list<Edge<Te>*>   //邻接链表声明
	enum class VStatus {
		Undiscover,
		Discover,
		Visited
	};
	enum class Etype {
		Undetermine,
		Tree,
		Cross,
		Forward,
		Backward
	};
	template<typename Tv = int>
	struct Vertex {
		 Tv data; int inDegree; int outDegree; VStatus status;
		int parent; int priority;
		int dTime, fTime;//时间标签
		explicit Vertex(Tv const& d) :
			data(d), inDegree(0), outDegree(0), status(VStatus::Undiscover), parent(-1), priority(INT_MAX),dTime(-1),fTime(-1)
		{}

	};
	template<typename Te = int>
	struct Edge {
	   Te data; Etype type; int weight;
	   int address;//边是出边(u,v)的顶点v在V中的索引
		Edge(Te const& d, int w) :
			data(d), weight(w), type(Etype::Undetermine),address(-1)
		{}
		Edge(Te const& d, int& w, Etype&t,int&a ) :
			data(d), weight(w), type(t), address(a)
		{}
		explicit Edge(Edge<Te> const &e) {
			this->data = e.data;
			this->weight = e.weight;
			this->address = e.address;
			this->type = e.type;
		}
		Edge<Te>& operator=(Edge<Te>  &e) {
			this->data = e.data;
			this->weight = e.weight;
			this->address = e.address;
			this->type = e.type;
			return *this;
		}
	};
	template<typename Tv=int,typename Te=int>
	class Graph
	{
		virtual void reset();
		virtual void BFS(int, int&, std::queue<int>&);//连通域，广度优先搜索
		virtual void DFS(int, int&, std::queue<int>&);//连通域，广度优先搜索
		virtual bool DFSTSort(int v,  std::stack<Tv>*);//连通域，dfs拓补排序
		//无向图BCC算法（单个）
		virtual void BCC(int v,int&clock,std::stack<int>&S,std::list<int>&apSet);//获取关节点
		virtual void BCC(int v, int&clock, std::stack<int>&S, std::list<std::list<Edge<Te> > >&bccSet);//获取双连通域 一个二维链表
		virtual void BCC(int v, int&clock, std::stack<int>&S, std::list<int>&apSet, std::list<std::list<Edge<Te> > >&bccSet);//获取双连通域 一个二维链表  获取关节点列表
		public:
		Graph();
		explicit Graph(Graph<Tv, Te>  &);
		~Graph();                   
	public:
	
		//算法
		//注：如果返回的是局部变量，容器可以直接引用返回的局部对象的内存，这里用智能指针主要为了锻炼智能指针的使用，也是由于开始对stl各种性质不太熟悉
		virtual	std::shared_ptr<std::list<std::queue<int> > > bfs(int);//广度优先搜索算法 参数为起点 返回一个队列列表指针指针,图所有的广度搜索结果
		virtual	std::shared_ptr<std::list<std::queue<int> > > dfs(int);//深度优先搜索算法 参数为起点 返回一个队列列表智能指针,图所有的深度搜索结果
		virtual	std::shared_ptr <std::stack<Tv> >dfsTopologicalSort(int s);//基于dfs的拓补排序算法
		virtual std::shared_ptr <std::queue<Tv> >bfsTopologicalSort(int s);//基于bfs的拓补排序算法
		//无向图BCC算法
		virtual std::list<int> getArtPoint(int s);//获取无向图的关节点列表(只是顶点索引)
		virtual std::list<std::list<Edge<Te> > > bcc(int s);//获取无向图的各个最大双连通域(边集合)
		virtual void  bcc(int s,std::list<int>&apSet, std::list<std::list<Edge<Te> > >&bccSet);//获取无向图的各个最大双连通域(边集合)和关节点列表

		virtual int findFirstOrigin();//找到第一个入度为0，出度不为0的顶点位置
		virtual int nextOrigin(int i);//找到相对于i的下一个入度为0，出度不为0的顶点位置
	
		//顶点操作
		virtual  Tv&Vertex(int i);//顶点保存的数据
		virtual int inDegree(int i);//入度
		virtual int outDegree(int i);//出度
		virtual int firstNbr(int i);//第一个邻接顶点
		virtual int nextNbr(int i, int j);//相对于某个邻接顶点的下一个邻接顶点
		//属性赋值函数
		virtual VStatus&status(int);
		virtual int& parent(int);
		virtual int&priority(int i);
		virtual int&dTime(int i);
		virtual int&fTime(int i);
		//顶点动态操作
		virtual int insert(Tv const&vertex,int i=-1);//-1代表插入末尾 末尾插入花费O(1)
		virtual Tv remove(int i);
	 //边操作
		
		virtual bool exists(int i, int j);
		virtual Edge<Te>& getEdge(int i, int j);//获取边
		//赋值操作函数
		virtual Etype& type(int i, int j);
		virtual Te& edge(int i, int j);//边数据
virtual int& weight(int i, int j);
		//边的动态操作
		virtual void insert(Te const&edge,int weight,int i,int j);
		virtual Te remove(int i, int j);//删除（i,j）
	public:
		int n;//顶点数
		int e;//边数
	
		std::vector<GH::Vertex<Tv> >V;//顶点集
		std::vector<std::list<GH::Edge<Te>*> >E;// 边集合
		 
	};

}
