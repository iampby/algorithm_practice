// MyGraph.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<memory>
#include<string>
#include<functional>
#include"Graph.h"
#include"PFSInf.h"
using namespace GH;
using namespace std;
void PFSForDijkstra();
void PFSForPrim();
void PFSForDFS();
void PFSForBFS();
void BCCTest();
void BFSTest();
void DFSTest();
void PrimTest();
void DijkstraTest();
int main()
{
	//BFSTest();
	//PFSForBFS();
	//DFSTest();
	//PFSForDFS();
	//PFSForPrim();
	//PrimTest();
	PFSForDijkstra();
	DijkstraTest();
}  
void DijkstraTest() {
	Graph<int, string> g;
	for (int i = 0; i < 8; ++i) {
		g.insert(i);
	}
	g.insert("AB", 25, 1, 2);
	g.insert("BD", 2, 2, 4);
	g.insert("CF", 5, 3, 6); g.insert("CD", 30, 3, 4); g.insert("CB", 18, 3, 2);
	g.insert("DG", 16, 4, 7); g.insert("DE", 11, 4, 5);
	g.insert("EB", 6, 5, 2); g.insert("EG", 6, 5, 7);
	g.insert("FD", 20, 6, 4); g.insert("FG", 40, 6, 7);
	g.insert("SA", 9, 0, 1); g.insert("SC", 14, 0, 3); g.insert("SF", 15, 0, 6);


	std::cout << "顶点数据：" << endl;
	for (int i = 0; i < g.V.size(); ++i) {
		cout << "i=" << i << ",data=" << g.V[i].data << ",inDegree=" << g.V[i].inDegree << ",outDegree=" << g.V[i].outDegree << endl;;
	}
	cout << "dijkstra生成最短路径树:" << endl;

	cout << "f=" << g.findFirstOrigin() << endl;
	std::list<Edge<string> >x = g.dijkstra(g.findFirstOrigin());
	auto j = x.begin();
	auto end = x.cend();

	while (j != end)
	{
		cout << (*j).data << " ";
		++j;
	}

	cout << endl;
	}
void PFSForDijkstra() {
	Graph<int, string> g;
	for (int i = 0; i < 8; ++i) {
		g.insert(i);
	}
	g.insert("AB", 25, 1, 2);
	g.insert("BD", 2, 2, 4);
	g.insert("CF", 5, 3, 6); g.insert("CD", 30, 3, 4); g.insert("CB", 18, 3, 2);
	g.insert("DG", 16, 4, 7); g.insert("DE", 11, 4, 5);
	g.insert("EB", 6, 5, 2); g.insert("EG", 6, 5, 7);
	g.insert("FD", 20, 6, 4); g.insert("FG", 40, 6, 7);
	g.insert("SA", 9, 0, 1); g.insert("SC", 14, 0, 3); g.insert("SF", 15, 0, 6);


	std::cout << "顶点数据：" << endl;
	for (int i = 0; i < g.V.size(); ++i) {
		cout << "i=" << i << ",data=" << g.V[i].data << ",inDegree=" << g.V[i].inDegree << ",outDegree=" << g.V[i].outDegree << endl;;
	}
	cout << "PFS for Dijkstra:" << endl;

	cout << "f=" << g.findFirstOrigin() << endl;
	g.pfs(g.findFirstOrigin(), DijkstraPU<int, string>);
	cout << endl;
	for (int i = 0; i < g.n; i++)
	{
		cout << "i=" << i << ",priority=" << g.V[i].priority << endl;
	}
	cout << endl;
}
void PrimTest() {
	Graph<int, string> g;
	g.insert(-1);//为了字面匹配 末尾会多余显示一个点
	for (int i = 1; i < 9; ++i) {
		g.insert(i);
	}
	g.insert("AX", 9999, 1, 0); g.insert("XA", 9999, 0, 1);//加0边正常显示
	g.insert("AD", 6, 1, 4); g.insert("AB", 4, 1, 2); g.insert("AG", 7, 1, 7);
	g.insert("BC", 12, 2, 3);
	g.insert("DG", 2, 4, 7); g.insert("DE", 13, 4, 5); g.insert("DC", 9, 4, 3);
	g.insert("GE", 11, 7, 5); g.insert("GH", 14, 7, 8);
	g.insert("EC", 1, 5, 3); g.insert("EF", 5, 5, 6); g.insert("EH", 8, 5, 8);
	g.insert("CF", 2, 3, 6); g.insert("CH", 10, 3, 8);
	g.insert("FH", 7, 6, 8);

	g.insert("DA", 6, 4, 1); g.insert("BA", 4, 2, 1); g.insert("GA", 7, 7, 1);
	g.insert("CB", 12, 3, 2);
	g.insert("GD", 2, 7, 4); g.insert("ED", 13, 5, 4); g.insert("CD", 9, 3, 4);
	g.insert("EG", 11, 5, 7); g.insert("HG", 14, 8, 7);
	g.insert("CE", 1, 3, 5); g.insert("FE", 5, 6, 5); g.insert("HE", 8, 8, 5);
	g.insert("FC", 2, 6, 3); g.insert("HC", 10, 8, 3);
	g.insert("HF", 7, 8, 6);

	std::cout << "顶点数据：" << endl;
	for (int i = 0; i < g.V.size(); ++i) {
		cout << "i=" << i << ",data=" << g.V[i].data << ",inDegree=" << g.V[i].inDegree << ",outDegree=" << g.V[i].outDegree << endl;;
	}
	cout << "prim生成最小支撑树:" << endl;

	cout << "f=" << 1 << endl;
	std::list<Edge<string> >x=g.prim(1);
auto j = x.begin();
		auto end = x.cend();
	
		while (j != end)
		{
			cout << (*j).data << " ";
			++j;
		}

	cout << endl;
	}
void PFSForPrim() {
	Graph<int, string> g;
	g.insert(-1);//为了字面匹配 末尾会多余显示一个点
	for (int i = 1; i < 9; ++i) {
		g.insert(i);
	}
	g.insert("AX", 9999, 1, 0); g.insert("XA", 9999, 0, 1);//加0边正常显示
	g.insert("AD", 6, 1, 4); g.insert("AB", 4, 1, 2); g.insert("AG", 7, 1, 7);
	g.insert("BC", 12, 2, 3);
	g.insert("DG", 2, 4, 7);g.insert("DE", 13, 4, 5);g.insert("DC", 9, 4, 3);
	g.insert("GE", 11, 7, 5);g.insert("GH", 14, 7, 8);
	g.insert("EC", 1, 5, 3);g.insert("EF", 5, 5, 6);g.insert("EH", 8, 5, 8);
	g.insert("CF", 2, 3, 6); g.insert("CH", 10, 3, 8);
	g.insert("FH", 7, 6, 8);

	g.insert("DA", 6, 4, 1); g.insert("BA", 4, 2, 1); g.insert("GA", 7, 7, 1);
	g.insert("CB", 12, 3, 2);
	g.insert("GD", 2, 7, 4); g.insert("ED", 13, 5, 4); g.insert("CD", 9, 3, 4);
	g.insert("EG", 11,5, 7); g.insert("HG", 14, 8, 7);
	g.insert("CE", 1, 3, 5); g.insert("FE", 5,6, 5); g.insert("HE", 8, 8, 5);
	g.insert("FC", 2, 6, 3); g.insert("HC", 10, 8, 3);
	g.insert("HF", 7, 8, 6);

	std::cout << "顶点数据：" << endl;
	for (int i = 0; i < g.V.size(); ++i) {
		cout << "i=" << i << ",data=" << g.V[i].data << ",inDegree=" << g.V[i].inDegree << ",outDegree=" << g.V[i].outDegree << endl;;
	}
	cout << "PFS for Prim:" << endl;

	cout << "f=" << 1 << endl;
	g.pfs(1, PrimPU<int, string>);
	cout <<  endl;
	for (int i = 0; i < g.n; i++)
	{
		cout << "i=" << i << ",priority=" << g.V[i].priority << endl;
	}
	cout << endl;
}
void PFSForDFS() {
	Graph<int, string> g;
	g.insert(0);
	for (int i = 1; i < 8; ++i) {
		g.insert(i,1);
	}
	g.insert(-1);
	g.insert("AC", 1, 1, 3);
	g.insert("AE", 1, 1, 5);
	g.insert("SA", 1, 0,1);
	g.insert("SC", 1, 0, 3);
	g.insert("SD", 1, 0, 4);
	g.insert("DB", 1, 4, 2);
	g.insert("CB", 1, 3, 2);
	g.insert("EF", 1, 5, 6);
	g.insert("EG", 1, 5, 7);
	g.insert("GF", 1, 7, 6);
	g.insert("GB", 1, 7, 2);
	std::cout << "顶点数据：" << endl;
	for (int i = 0; i < g.V.size(); ++i) {
		cout << "i=" << i << ",data=" << g.V[i].data << ",inDegree=" << g.V[i].inDegree << ",outDegree=" << g.V[i].outDegree << endl;;
	}
	cout <<"PFS for DFS:" <<endl;
	cout << "f=" << g.findFirstOrigin()<< endl;
	g.pfs(g.findFirstOrigin(), DfsPU<int, string>);
	for (int i = 0; i < g.n; i++)
	{
		cout << "i=" << i << ",priority=" << g.V[i].priority << endl;
	}
	cout << endl;
}
void PFSForBFS() {
	Graph<int, string> g;
	g.insert(0);
	for (int i = 1; i < 8; ++i) {
		g.insert(i, 1);
	}
	g.insert(-1);
	g.insert("AC", 1, 1, 3);
	g.insert("AE", 1, 1, 5);
	g.insert("SA", 1, 0, 1);
	g.insert("SC", 1, 0, 3);
	g.insert("SD", 1, 0, 4);
	g.insert("DB", 1, 4, 2);
	g.insert("CB", 1, 3, 2);
	g.insert("EF", 1, 5, 6);
	g.insert("EG", 1, 5, 7);
	g.insert("GF", 1, 7, 6);
	g.insert("GB", 1, 7, 2);
	std::cout << "顶点数据：" << endl;
	for (int i = 0; i < g.V.size(); ++i) {
		cout << "i=" << i << ",data=" << g.V[i].data << ",inDegree=" << g.V[i].inDegree << ",outDegree=" << g.V[i].outDegree << endl;;
	}
	cout << "PFS for BFS:" << endl;

	cout << "f=" << g.findFirstOrigin() << endl;
	g.pfs(g.findFirstOrigin(), BfsPU<int, string>);
	for (int i = 0; i < g.n; i++)
	{
		cout << "i=" << i << ",priority=" << g.V[i].priority << endl;
	}
	cout << endl;
}
void DFSTest() {
	Graph<int, string> g;
	g.insert(0);
	for (int i = 1; i < 8; ++i) {
		g.insert(i, 1);
	}
	g.insert(-1);
	g.insert("AC", 1, 1, 3);
	g.insert("AE", 1, 1, 5);
	g.insert("SA", 1, 0, 1);
	g.insert("SC", 1, 0, 3);
	g.insert("SD", 1, 0, 4);
	g.insert("DB", 1, 4, 2);
	g.insert("CB", 1, 3, 2);
	g.insert("EF", 1, 5, 6);
	g.insert("EG", 1, 5, 7);
	g.insert("GF", 1, 7, 6);
	g.insert("GB", 1, 7, 2);
	std::cout << "顶点数据：" << endl;
	for (int i = 0; i < g.V.size(); ++i) {
		cout << "i=" << i << ",data=" << g.V[i].data << ",inDegree=" << g.V[i].inDegree << ",outDegree=" << g.V[i].outDegree << endl;;
	}
	cout << endl;
	cout << "f=" << g.findFirstOrigin() << endl;
	std::shared_ptr<std::list<std::queue<int> > >x = g.dfs(g.findFirstOrigin());
	auto i = x->begin();
	auto end = x->end();
	cout << "深度优先搜索：" << endl;
	while (i != end)
	{
		std::queue<int>&v = *i;
		cout << "一颗dfs树：";
		while (!v.empty())
		{
			cout << v.front() << " ";
			v.pop();
		}
		cout << endl;
		++i;
	}
	cout << endl;
}
void BFSTest() {
	Graph<int, string> g;
	g.insert(0);
	for (int i = 1; i < 8; ++i) {
		g.insert(i, 1);
	}
	g.insert(-1);
	g.insert("AC", 1, 1, 3);
	g.insert("AE", 1, 1, 5);
	g.insert("SA", 1, 0, 1);
	g.insert("SC", 1, 0, 3);
	g.insert("SD", 1, 0, 4);
	g.insert("DB", 1, 4, 2);
	g.insert("CB", 1, 3, 2);
	g.insert("EF", 1, 5, 6);
	g.insert("EG", 1, 5, 7);
	g.insert("GF", 1, 7, 6);
	g.insert("GB", 1, 7, 2);
	std::cout << "顶点数据：" << endl;
	for (int i = 0; i < g.V.size(); ++i) {
		cout << "i=" << i << ",data=" << g.V[i].data << ",inDegree=" << g.V[i].inDegree << ",outDegree=" << g.V[i].outDegree << endl;;
	}
	cout << endl;
	cout << "f="<< g.findFirstOrigin() <<endl;
	std::shared_ptr<std::list<std::queue<int> > >x = g.bfs(g.findFirstOrigin());
	auto i = x->begin();
	auto end = x->end();
	cout <<  "广度优先搜索："<<endl;
	while (i!=end)
	{
		std::queue<int>&v = *i;
		cout << "一颗bfs树：";
		while (!v.empty())
		{
			cout << v.front() << " ";
			v.pop();
		}
		cout << endl;
		++i;
	}
	cout << endl;
}
//双连通域分解例子(关节点及双连通域版)
void BCCTest() {
	Graph<int, string> g;
	g.insert(1);
	for (int i = 2; i < 11; ++i) {
		g.insert(i);
	}
	g.insert(0);
	g.insert("AB", 1, 1, 2);
	g.insert("BA", 1, 2, 1);
	g.insert("BC", 1, 2, 3); g.insert("CB", 1, 3, 2);
	//g.insert("CD", 1, 3, 4); g.insert("DC", 1, 4, 3);
	g.insert("DE", 1, 4, 5); g.insert("ED", 1, 5, 4);
	g.insert("EG", 1, 5, 7); g.insert("GE", 1, 7, 5);
	g.insert("GF", 1, 7, 6); g.insert("FG", 1, 6, 7);
	g.insert("DG", 1, 4, 7); g.insert("GD", 1, 7, 4);
	g.insert("CH", 1, 3, 8); g.insert("HC", 1, 8, 3);
	g.insert("HA", 1, 8, 1); g.insert("AH", 1, 1, 8);
	g.insert("AI", 1, 1, 9); g.insert("IA", 1, 9, 1);
	g.insert("AJ", 1, 1, 10); g.insert("JA", 1, 10, 1);
	g.insert("JI", 1, 10, 9); g.insert("IJ", 1, 9, 10);
	std::cout << "顶点数据：" << endl;
	for (int i = 0; i < g.V.size(); ++i) {
		cout << "i=" << i << ",data=" << g.V[i].data << ",inDegree=" << g.V[i].inDegree << ",outDegree=" << g.V[i].outDegree << endl;;
	}
	cout << endl;

	std::list<std::list<Edge<string> > >bccSet;
	list<int>apSet;
	g.bcc(1,apSet, bccSet);
	std::cout << "关节点：" << endl;
	for (int i = 0; i < apSet.size(); i++)
	{
		auto it = apSet.begin();
		advance(it, i);
		cout << (*it) << " ";
	}
	std::cout << std::endl;
	std::cout << "双连通域分解：" << endl;
	for (int i = 0; i < bccSet.size(); i++)
	{
		auto it = bccSet.begin();
		advance(it, i);
		list<Edge<string> >&v = *it;
		auto j = v.begin();
		auto end = v.cend();
		std::cout << "第"<<i+1<<"个双连通域：" << endl;
		while (j != end)
		{
			cout << (*j).data << " ";
			++j;
		}
		cout << endl;
	}
};
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
