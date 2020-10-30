// PQ_LeftHeap.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<time.h>
#include<chrono>
#include"PQ_LeftHeap.hpp"

using namespace std;

void testConstructor2();
void testFunc();
int main()
{
	testFunc();
	testConstructor2();
}
void testFunc() {
	PQ_LeftHeap<> pq;
	srand((unsigned int)time(NULL));
	int n =rand()%20000000; int max = -RAND_MAX;
	printf("\ttesting inserting %d...\n\t", n);
	auto tm = chrono::steady_clock::now();
	while (n-- > 0)
	{
		int v = rand() % 2 ? rand() : -rand();
		if (max < v) {  max = v; }
		pq.push(v);
	}
	auto dur = chrono::duration<double>(chrono::steady_clock::now() - tm);
	printf("takes %lf sec...\n\tthe top of priority queue is %d,real maxinum value is %d...\n\t", dur.count(), pq.top(), max);
	printf("the NPL of priority queue is %d...\n\t", pq.NPL());
	printf("removing the top...\n\t");
	pq.pop();
	printf("now the top is %d...\n\t", pq.top());
	printf("removing all...\n\t");
	tm = chrono::steady_clock::now();
	int last = pq.top();
	while (!pq.empty())
	{
		if (pq.top() > last)cout << "algorithm error!\n\t";
		pq.pop();
	}
	dur = chrono::duration<double>(chrono::steady_clock::now() - tm);
	printf("takes %lf sec...\n\tthe size of priority queue is %d...\n\t", dur.count(), pq.size());
};
void testConstructor2() {
	srand((unsigned int)time(NULL));
	int n = rand() % 20000000;; int max = RAND_MAX;
	vector<int>vec(n);
	while (n-- > 0)
	{
		int v = rand() % 2 ? rand() : -rand();
		if (max > v)max = v;
		vec[n] = v;
	}
	printf("testing constructor with argument  vector's capacity is  %d...\n\t", vec.size());
	auto tm = chrono::steady_clock::now();
	PQ_LeftHeap<int, myGreater<int> >pq(std::move(vec));
	auto dur = chrono::duration<double>(chrono::steady_clock::now() - tm);
	printf("takes %lf sec...\n\tthe top of priority queue is %d,real  mininum value is %d...\n\t", dur.count(), pq.top(), max);
	printf("the NPL of priority queue is %d...\n\t",pq.NPL());
	printf("removing the top...\n\t");
	pq.pop();
	printf("now the top is %d...\n\t", pq.top());
	printf("removing all...\n\t");
	tm = chrono::steady_clock::now();
	int last=pq.top();
	while (!pq.empty())
	{
		if(pq.top()<last)cout<<"algorithm error!\n\t";
		pq.pop();
	}
	dur = chrono::duration<double>(chrono::steady_clock::now() - tm);
	printf("takes %lf sec...\n\tthe size of priority queue is %d...\n\t", dur.count(), pq.size());
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
