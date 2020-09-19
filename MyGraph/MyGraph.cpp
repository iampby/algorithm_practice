// MyGraph.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<memory>
#include"Graph.h"
using namespace GH;
using namespace std;
int main()
{
	Graph<int,int> g;  
	g.insert(0);
	for (int i =1; i <7; ++i) {
		g.insert(i,1);
	}

	g.insert(0,1,0,1);
	g.insert(0, 1, 0, 2);
	g.insert(0, 1, 1, 2);
	g.insert(0, 1, 1, 3);
	g.insert(0, 1, 1, 4);
	g.insert(0, 1, 3, 4);
	g.insert(0, 1, 5,1);
	for (int i = 0; i < g.V.size(); ++i) {
		cout << "i=" << i << ",data=" << g.V[i].data <<",inDegree="<< g.V[i].inDegree << ",outDegree="<< g.V[i].outDegree << endl;;
	}
	cout << endl;
	int f= g.findFirstOrigin();
	std::cout << "f=" << f << endl;
		shared_ptr<queue<int> >x = g.bfsTopologicalSort(f);
		std::cout << "s=" <<x->size() << endl;
		while (!x->empty())
		{
			cout <<x->front();
			x->pop();
		}
	
}                                                                                                        

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
