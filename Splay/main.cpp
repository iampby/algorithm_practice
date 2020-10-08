// Splay.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<vector>
#include<ctime>
#include"Splay.h"

using namespace std;
using namespace ST;
//随机生成树
void testSplay();//测试伸展树的插入删除 搜索功能
int main()
{
	testSplay();
}
void testSplay() {
	Splay<int>tree;
	srand(time(NULL));
	int low, up = 0;
	do {
		low = rand() % 1000;
		up = rand() % 1000;
		if (up < low) {
			swap(up, low);
		}
} while (up-low>500|| up - low<20);
vector<int>num;
for (int i = low; i <up; ++i) {
	num.insert(num.end(), i);
}
vector<int>r;
while (!num.empty())
{
	int s = rand()%(num.size());
	auto it = num.begin();
	advance(it, s);
	switch (rand() % 2)
	{
	case 0: {
		(tree).insert(s, Splay<int>::InsertByBSTInsert);
	}
			break;
	default: {
		(tree).insert(s, Splay<int>::InsertBySearch);
	}
			 break;
	}
	num.erase(it);
	r.insert(r.end(), s);
}
cout << "start inorder traversal:\n";
tree.inorderTraversal();
cout << "\nstart preorder traversal:\n";
tree.preorderTraversal();
cout <<"\nsearch last "<<r.at((up-low)/2) <<endl;
tree.searchLast(r.at((up - low) / 2));
cout << "start inorder traversal:\n";
tree.inorderTraversal();
cout << "\nstart preorder traversal:\n";
tree.preorderTraversal();
int x = rand() % r.size();
cout << "\nremove: " << r.at(x) << endl;
tree.remove(r.at(x));
{
	auto it = r.begin(); advance(it, x);
	r.erase(it);
}
cout << "start inorder traversal:\n";
tree.inorderTraversal();
cout << "\nstart preorder traversal:\n";
tree.preorderTraversal();

cout << "\nremove all randomly:";
while (!r.empty())
{
	x= rand()%r.size();
	auto it = r.begin();
	advance(it, x);
	tree.remove(*it);
	r.erase(it);
	}
cout << endl;
cout << "start inorder traversal:\n";
tree.inorderTraversal();
cout << "\nempty tree  represent as normal!\n";
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
