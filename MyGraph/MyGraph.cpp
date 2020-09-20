// MyGraph.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<memory>
#include<string>
#include"Graph.h"
using namespace GH;
using namespace std;
void BCCTest();
int main()
{
	BCCTest();
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
