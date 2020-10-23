// BitMap.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include"BitMap.h"
#include <iostream>
#include<chrono>
using namespace std;
void testPerformance();//对640000个数据标记，测试性能
int main()
{
	testPerformance();
}
void testPerformance() {
	int n = 640000;
	SBitMap bm(10000);
	printf("test set() with a scale of %d..\n\t", n);
	auto tm =  chrono::steady_clock::now();
	for (int i = 0; i < n; ++i) {
		bm.set(rand() % 2 ? i : (-i));
	}
	auto dur = chrono::duration<double>((chrono::steady_clock::now())-tm);
	printf("takes %g sec..\n\t", dur.count());
	printf("test test() with a scale of %d..\n\t", n);
	tm = chrono::steady_clock::now();
	for (int i = 0; i < n; ++i) {
		bm.test(rand() % 2 ? i : (-i));
	}
	dur = chrono::duration<double>((chrono::steady_clock::now()) - tm);
	printf("takes %g sec..\n\t", dur.count());
	printf("test clear() with a scale of %d..\n\t", n);
	tm = chrono::steady_clock::now();
	for (int i = 0; i < n; ++i) {
		bm.clear(rand() % 2 ? i : (-i));
	}
	dur = chrono::duration<double>((chrono::steady_clock::now()) - tm);
	printf("takes %g sec..\n\t", dur.count());
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
