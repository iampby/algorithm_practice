#pragma once
#include<list>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<memory>
namespace GH {
#define TLEI typename std::list<Edge<Te>*>::iterator  //�ڽ��������������
#define TLECI typename std::list<Edge<Te>*>::const_iterator//�ڽ�����������������
#define LET std::list<Edge<Te>*>   //�ڽ���������
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
		int dTime, fTime;//ʱ���ǩ
		explicit Vertex(Tv const& d) :
			data(d), inDegree(0), outDegree(0), status(VStatus::Undiscover), parent(-1), priority(INT_MAX),dTime(-1),fTime(-1)
		{}

	};
	template<typename Te = int>
	struct Edge {
	   Te data; Etype type; int weight;
	   int address;//���ǳ���(u,v)�Ķ���v��V�е�����
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
		virtual void BFS(int, int&, std::queue<int>&);//��ͨ�򣬹����������
		virtual void DFS(int, int&, std::queue<int>&);//��ͨ�򣬹����������
		virtual bool DFSTSort(int v,  std::stack<Tv>*);//��ͨ��dfs�ز�����
		public:
		Graph();
		explicit Graph(Graph<Tv, Te>  &);
		~Graph();                   
	public:
	
		//�㷨
		virtual	std::shared_ptr<std::vector<std::queue<int> > > bfs(int);//������������㷨 ����Ϊ��� ����һ�������б�ָ��ָ��,ͼ���еĹ���������
		virtual	std::shared_ptr<std::vector<std::queue<int> > > dfs(int);//������������㷨 ����Ϊ��� ����һ�������б�����ָ��,ͼ���е�����������
		virtual	std::shared_ptr <std::stack<Tv> >dfsTopologicalSort(int s);//����dfs���ز������㷨
		virtual std::shared_ptr <std::queue<Tv> >bfsTopologicalSort(int s);//����bfs���ز������㷨
		virtual int findFirstOrigin();//�ҵ���һ�����Ϊ0�����Ȳ�Ϊ0�Ķ���λ��
		virtual int nextOrigin(int i);//�ҵ������i����һ�����Ϊ0�����Ȳ�Ϊ0�Ķ���λ��
	
		//�������
		virtual  Tv&Vertex(int i);//���㱣�������
		virtual int inDegree(int i);//���
		virtual int outDegree(int i);//����
		virtual int firstNbr(int i);//��һ���ڽӶ���
		virtual int nextNbr(int i, int j);//�����ĳ���ڽӶ������һ���ڽӶ���
		//���Ը�ֵ����
		virtual VStatus&status(int);
		virtual int& parent(int);
		virtual int&priority(int i);
		virtual int&dTime(int i);
		virtual int&fTime(int i);
		//���㶯̬����
		virtual int insert(Tv const&vertex,int i=-1);//-1�������ĩβ ĩβ���뻨��O(1)
		virtual Tv remove(int i);
	 //�߲���
		
		virtual bool exists(int i, int j);
		//��ֵ��������
		virtual Etype& type(int i, int j);
		virtual Te& edge(int i, int j);//������
		virtual int& weight(int i, int j);
		//�ߵĶ�̬����
		virtual void insert(Te const&edge,int weight,int i,int j);
		virtual Te remove(int i, int j);//ɾ����i,j��
	public:
		int n;//������
		int e;//����
	
		std::vector<GH::Vertex<Tv> >V;//���㼯
		std::vector<std::list<GH::Edge<Te>*> >E;// �߼���
		 
	};
	
}
