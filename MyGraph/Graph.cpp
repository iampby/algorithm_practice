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
	};
	template<typename Tv=int,typename Te=int>
	class Graph
	{
		virtual void reset();
		virtual void BFS(int, int&, std::queue<int>&);//连通域，广度优先搜索
		virtual void DFS(int, int&, std::queue<int>&);//连通域，广度优先搜索
		virtual bool DFSTSort(int v,  std::stack<Tv>*);//连通域，dfs拓补排序
		public:
		Graph();
		explicit Graph(Graph<Tv, Te>  &);
		~Graph();                   
	public:
	
		//算法
		virtual	std::shared_ptr<std::vector<std::queue<int> > > bfs(int);//广度优先搜索算法 参数为起点 返回一个队列列表指针指针,图所有的广度搜索结果
		virtual	std::shared_ptr<std::vector<std::queue<int> > > dfs(int);//深度优先搜索算法 参数为起点 返回一个队列列表智能指针,图所有的深度搜索结果
		virtual	std::shared_ptr <std::stack<Tv> >dfsTopologicalSort(int s);//基于dfs的拓补排序算法
		virtual std::shared_ptr <std::queue<Tv> >bfsTopologicalSort(int s);//基于bfs的拓补排序算法
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
