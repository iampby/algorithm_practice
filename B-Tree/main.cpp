// B-Tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<time.h>
#include"BTree.h"
using namespace std;
using namespace BT;
void testBTree();//功能测试
int main()
{
	testBTree();
}
void testBTree() {
	BTree<int>tree(4);
	srand(time(NULL));
	int low, up = 0;
	do {
		low = rand() % 100;
		up = rand() %100;
		if (up < low) {
			swap(up, low);
		}
	} while (up - low >50 || up - low < 20);
	vector<int>num;
	for (int i = low; i < up; ++i) {
		num.insert(num.end(), i);
	}
	vector<int>r;
	cout << "insert values the fllowing:"  << endl;
while (!num.empty())
	{
		int s = rand() % (num.size());
		auto it = num.begin();
		advance(it, s);
		tree.insert(s);
		r.insert(r.end(), s);
		cout << s << " ";
		num.erase(it);
	}
	cout << "\ntree size:\n" << tree.size() << endl;
	cout << "start inorder traversal:\n";
	tree.traversal();
	cout << endl;
	cout << "remove randomly:";
	int n = 0;
	while (n++<3)
	{
		int x = rand() % r.size();
		auto it = r.begin();
		advance(it, x);
		tree.remove(*it);
		cout << *it << " ";
		r.erase(it);
}
	cout << endl;
	cout << "now tree size:\n" << tree.size() << endl;
	cout << "now inorder traversal:\n";
	tree.traversal();
	cout << endl;
	cout << "remove randomly:";
	 n = 0;
	while (n++ < 3)
	{
		int x = rand() % r.size();
		auto it = r.begin();
		advance(it, x);
		tree.remove(*it);
		cout << *it << " ";
		r.erase(it);
	}
	cout << endl;
	cout << "now tree size:\n" << tree.size() << endl;
	cout << "now inorder traversal:\n";
	tree.traversal();
	cout << endl;
	cout << "remove tree root' value:"<<tree.root()->key.at(0)<<endl;
	tree.remove(tree.root()->key.at(0));
	cout << "now tree size:\n" << tree.size() << endl;
	cout << "now inorder traversal:\n";
	tree.traversal();
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
