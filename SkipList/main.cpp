// SkipList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"SkipList.h"
#include <iostream>
#include<vector>
using namespace std;
using namespace SKL;
void testSkiplist();
int main()
{
	testSkiplist();
}
void testSkiplist() {
	SkipList<float, int>skl;
	int n =rand()% 400000 +100000;
	vector<float>r;
	r.reserve(n);
	clock_t tm = clock();
	printf(" inserting %d nodes...\n",n);
	while (n-->0)
	{
		float k = (float)rand() / RAND_MAX * (rand()%100000);
		int v = rand() % 100000;
		skl.insert(k, v);
		r.push_back(k);
	}
	tm = clock() - tm;
	printf(" taking %g sec\nnow scale is %d\n", (double)(tm) / CLOCKS_PER_SEC,skl.size());
	printf(" traversing...\n");
	tm = clock();
	//skl.traversal();
	tm = clock() - tm;
	printf(" \ntaking %g sec\n", (double)(tm) / CLOCKS_PER_SEC);
	float rc = rand() % r.size() / (float)r.size();
	printf("removeing %.2f%% randomly(%d)...\n",rc*100, (int)(rc * r.size()));
	rc = (int)(rc*r.size());
	tm = clock();
	while (rc>0.0)
	{
		int pos = rand() % r.size();
		auto it = r.begin();
		std::advance(it, pos);
		skl.remove(*it);
		//printf("removing %f\n",*it);
		r.erase(it);
		--rc;;
	}
	tm = clock() - tm;
	printf(" \ntaking %g sec\nnow scale is %d\n", (double)(tm) / CLOCKS_PER_SEC,skl.size());
	printf(" traversing...\n");
	tm = clock();
	//skl.traversal();
	tm = clock() - tm;
	printf(" \ntaking %g sec\n", (double)(tm) / CLOCKS_PER_SEC);
	rc = rand() % r.size() / (float)r.size();
	printf("getting %.2f%% randomly(%d)...\n", rc * 100, (int)(rc * r.size()));
	rc = (int)(rc*r.size());
	tm = clock();
	while (rc > 0.0)
	{
		int pos = rand() % r.size();
		auto it = r.begin();
		std::advance(it, pos);
		int* v=skl.get(*it);
		//printf("getting value %d with key %g\n", *v,*it);
		r.erase(it);
		--rc;;
	}
	tm = clock() - tm;
	printf(" \ntaking %g sec\n", (double)(tm) / CLOCKS_PER_SEC);
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
