// Sort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<algorithm>
#include<vector>
#include<time.h>
#include<chrono>
#include<queue>
#include"sort.h"
#include"K_Select.h"

using namespace std;
void testPerformance();//测试性能 测试结果：冒泡>希尔>归并>快排>选择
void testKtestPerformance();//比O（nlogn)略胜一筹

void testMerge();
void testBubble();
void testSelect();
void testQuick();
void testShell();

//k-选取测试功能
void testKSelect();

int main()
{
	srand(time(nullptr));
	
	//testMerge(); testBubble(); testSelect();testQuick();testShell();
	testPerformance();
	////testKSelect();
	//testKtestPerformance();
}
void testPerformance() {
	int count =  rand() % 3+1;
	int R = 10000000;
	printf("\ttesting %d the performance of sort algorithm :\n\t", count);

	int tn = count;
	while (tn-- > 0)
	{
		int n = rand()*rand()%R;
		printf("\n\tthe %d times test with scale %d...\n\t", count - tn,n);
		vector<int>v; v.reserve(n);
		list<int>l;
		for (int i = 0; i < n; ++i) {
			int t = rand()*rand();
			v.push_back(t);
			l.push_back(t);
		}

		printf("\ttesting the selection sort with vector:\n\t");
		auto tm = chrono::steady_clock::now();
		selectSort<>(v);
		chrono::duration<double> dur = chrono::steady_clock::now() - tm;
		printf("\t... takes %lf sec ...\n\t", dur.count());

		printf("\ttesting the quick sort with vector:\n\t");
		tm = chrono::steady_clock::now();
		quickSort<>(v);
		dur = chrono::steady_clock::now() - tm;
		printf("\t... takes %lf sec ...\n\t", dur.count());

		
		printf("\ttesting the merge sort with vector:\n\t");
		tm = chrono::steady_clock::now();
		mergeSort<>(v);
		 dur = chrono::steady_clock::now() - tm;
		printf("\t... takes %lf sec ...\n\t", dur.count());

		printf("\ttesting the merge sort with list:\n\t");
		 tm = chrono::steady_clock::now();
		mergeSort<>(l);
		 dur = chrono::steady_clock::now() - tm;
		printf("\t... takes %lf sec ...\n\t", dur.count());

		printf("\ttesting the bubble sort with vector:\n\t");
		tm = chrono::steady_clock::now();
		bubbleSort<>(v);
		dur = chrono::steady_clock::now() - tm;
		printf("\t... takes %lf sec ...\n\t", dur.count());

		printf("\ttesting the bubble sort with list:\n\t");
		tm = chrono::steady_clock::now();
		bubbleSort<>(l);
		dur = chrono::steady_clock::now() - tm;
		printf("\t... takes %lf sec ...\n\t", dur.count());

		printf("\ttesting the shell sort:\n\t");
		tm = chrono::steady_clock::now();
		shellSort<>(v);
		dur = chrono::steady_clock::now() - tm;
		printf("\t... takes %lf sec ...\n\t", dur.count());

	}
	printf("\n\tend\n\t");
};
void testKtestPerformance() {
	int R = 20000000;
	int count = rand() % 10 + 1;
	int n = rand()*rand() % R;
	printf("\ttest the k-select %d times with scale %d:\n\t", count,n);
	int t = 0;
while (count-- > 0)
	{
	printf("\...the %d times...\n\t",++t);
	vector<int>x1; x1.reserve(n);
		for (int i = 0; i < n; ++i) {
			x1.push_back(rand());
		}
	
		int k = rand() % x1.size();
		printf("\ttest the k-select with k=%d:\n\t", k);
		auto tm = chrono::steady_clock::now();
		int kv = k_select(x1, k);
		chrono::duration<double> dur1 = chrono::steady_clock::now() - tm;
		tm = chrono::steady_clock::now();
		sort(x1.begin(),x1.end());
		chrono::duration<double> dur2 = chrono::steady_clock::now() - tm;
		printf("\tcontrast:takes %lf sec and k with %d,real takes %lf sec and k with %d...\n\t", dur1.count(),kv, dur2.count(), x1[k]);
		printf("\n\t");
	}
	printf("end\n\t");
};
void testKSelect() {
 int count = rand() % 10+1;
	printf("\ttest the k-select %d times:\n\t", count);
	int n = 21;
	while (count-->0)
	{
	vector<int>x1;
	for (int i = 0; i < n; ++i) {
		x1.push_back(rand());
	}
	int k = rand() % x1.size();
	printf("\ttest the k-select with k=%d:\n\t",k);
	int kv = k_select(x1, k);
	quickSort(x1);
	printf("\tresult of quick sort for vector:\n\t");
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ", x1[i]);
	}
	printf("\n\t");
	printf("contrast:k with %d,real with %d...\n\t",kv,x1[k]);
	printf("\n\t");
}
printf("end\n\t");
};

void testShell() {
	int n = 21;
	vector<int>x1;
	printf("\tstarting to shell sort for vector:\n\t\tvector:\n\t");
	for (int i = 0; i < n; ++i) {
		x1.push_back(rand());
	}
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ", x1[i]);
	}
	printf("\n\t");
	shellSort(x1);
	printf("\tresult of shell sort for vector:\n\t");
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ", x1[i]);
	}
	printf("\n\t");

	printf("end\n\t");
};
void testQuick() {
	int n = 21;
	vector<int>x1;
	printf("\tstarting to quick sort for vector:\n\t\tvector:\n\t");
	for (int i = 0; i < n; ++i) {
		x1.push_back(rand());
	}
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ", x1[i]);
	}
	printf("\n\t");
	quickSort(x1);
	printf("\tresult of quick sort for vector:\n\t");
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ", x1[i]);
	}
	printf("\n\t");

	printf("end\n\t");
};
void testSelect() {
	int n = 21;
	vector<int>x1;
	printf("\tstarting to selection sort for vector:\n\t\tvector:\n\t");
	for (int i = 0; i < n; ++i) {
		x1.push_back(rand());
	}
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ", x1[i]);
	}
	printf("\n\t");
	selectSort(x1);
	printf("\tresult of selecting sort for vector:\n\t");
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ", x1[i]);
	}
	printf("\n\t");

	printf("end\n\t");
};
void testBubble() {
	int n = 21;
	vector<int>x1;
	printf("\tstarting to bubble sort for vector:\n\t\tvector:\n\t");
	for (int i = 0; i < n; ++i) {
		x1.push_back(rand());
	}
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ", x1[i]);
	}
	printf("\n\t");
	bubbleSort(x1);
	printf("\tresult of bubble sort for vector:\n\t");
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ", x1[i]);
	}
	printf("\n\t");

	list<int>x2;
	printf("starting to bubble sort for list:\n\t\tlist:\n\t");
	for (int i = 0; i < n; ++i) {
		x2.push_back(rand());
	}
	{
		auto it = x2.begin();
		while (it != x2.end())
		{
			printf("\t%d ", *it);
			++it;
		}
	}
	printf("\n\t");
	bubbleSort<int>(x2);
	printf("\tresult of bubble sort for list:\n\t");
	{
		auto it = x2.begin();
		while (it != x2.end())
		{
			printf("\t%d ", *it);
			++it;
		}
	}
	printf("\n\t");

	printf("end\n\t");
};

void testMerge() {
	int  n=21;
	vector<int>x1;
	printf("\tstarting to merge sort for vector:\n\t\tvector:\n\t");
	for (int i = 0; i < n; ++i) {
		x1.push_back(rand());
	}
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ", x1[i]);
	}
	printf("\n\t");
	mergeSort<int>(x1);
	printf("\tresult of merge sort for vector:\n\t");
	for (int i = 0; i < x1.size(); ++i) {
		printf("\t%d ",x1[i]);
	}
	printf("\n\t");

	list<int>x2;
	printf("starting to merge sort for list:\n\t\tlist:\n\t");
	for (int i = 0; i < n; ++i) {
		x2.push_back(rand());
	}
	{
		auto it = x2.begin();
		while (it != x2.end())
		{
			printf("\t%d ", *it);
			++it;
		}
	}
	printf("\n\t");
	mergeSort<>(x2);
	printf("\tresult of merge sort for list:\n\t");
	{
		auto it = x2.begin();
		while (it != x2.end())
		{
			printf("\t%d ", *it);
			++it;
		}
	}
	printf("\n\t");
	printf("end\n\t");
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
