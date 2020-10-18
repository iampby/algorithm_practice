// KdTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<iostream>
#include"K_2dTree.h"
#include<time.h>
using namespace std;
using namespace C2dTree;
int main()
{
	vector<K_2dData<float, int> >vec;
srand((unsigned)time(NULL));
	int n = 0;
		n = rand() % 100000 + 10000;
	vec.resize(n);
	printf("bulding  random  2d-Tree with a scale of %d...\n\t ", n);
	while (n>0)
	{
		float t1 = (float)rand() / RAND_MAX * (rand()%200000);
		int t2 = rand() % 200000;
		K_2dData<float, int>t(t1, t2);
		vec.push_back(t);
		--n;
	}
	int vcount = vec.size();
	K_2dTree<float, int>k_2dTree;
	clock_t tm = clock();
	k_2dTree.build(vec);
	 tm = clock()-tm;
	 printf(" taking %g sec\n\t", (double)(tm) / CLOCKS_PER_SEC);
	 float min1 = (float)rand() / RAND_MAX * (rand()%30000), max1 = min1*(rand() % 6);
	 int min2 = rand()% 30000, max2 =min2*rand()%6;
	 if (min1 > max1)swap(min1, max1); if (min2 > max2)swap(min2, max2);
	// int min2 =100, max2 = 1000;
	// float min1 = 200, max1 =10000;
	printf("range-searching ramdomly(%g～%g,%d～%d) ...\n\toutput of data processing :\n",min1,max1,min2,max2);
	int _size = k_2dTree.m_nodes.size();
	tm = clock();
	int res_sum= k_2dTree.seach(min1, max1, min2, max2);
	tm = clock()-tm;
	printf("\n\tfound:%d, percent:%.2f%%\n\tend\n\t",res_sum, (float)res_sum /_size*100);
	printf("once range-searching takes %g sec\n\t", (double)(tm) / CLOCKS_PER_SEC);
	printf("looking data set of searching by  traversal ...\n\t");
	res_sum = 0;
	tm = clock();
	for (size_t i = 0; i < _size; i++)
	{
		if (k_2dTree.m_nodes[i]->m_pBoundary->x >= min1 && k_2dTree.m_nodes[i]->m_pBoundary->x <= max1 && k_2dTree.m_nodes[i]->m_pBoundary->y >= min2 && k_2dTree.m_nodes[i]->m_pBoundary->y <= max2 && ++res_sum)
			//printf("(%f,%d)\n\t", k_2dTree.m_nodes[i]->m_pBoundary->x, k_2dTree.m_nodes[i]->m_pBoundary->y);
			;
	}
	tm = clock() - tm;
	printf("\n\tfound:%d, percent:%.2f%%\n\tend\n\t", res_sum, (float)res_sum/_size*100);
	printf("once searching by traversal takes %g sec\n\t", (double)(tm) / CLOCKS_PER_SEC);
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
