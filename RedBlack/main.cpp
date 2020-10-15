// RedBlack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<ctime>
#include"RedBlack.h"
using namespace RBT;
using namespace std;
void testRBT();
template<typename T>
void testHeight(RedBlcak<T>tree);//树平衡检测
int main()
{
	testRBT();
}
void testRBT() {
	RedBlcak<int>tree;
	srand(time(NULL));
	int low, up = 0;
	do {
		low = rand() % 1000;
		up = rand() % 1000;
		if (up < low) {
			swap(up, low);
		}
	} while (up - low > 200|| up - low<20);
	vector<int>num;
	for (int i = low; i < up; ++i) {
		num.insert(num.end(), i);
	}
	vector<int>r;
	int n = 0;

	cout << "inserted:"<< endl;
	while (!num.empty())
	{
		int s = rand() % (num.size());
		auto it = num.begin();
		advance(it, s);
		cout << *it<< " ";
		tree.insert(*it);
		r.emplace_back(*it);
		num.erase(it);
		++n;
	}

	cout << "\ninserted count: " << n << ",tree size:" << tree.size() << ",tree black height: "<<tree.height()<<endl;
	cout << "\ntest tree balance...\n";
	testHeight( tree);
	cout << endl;
	//前序遍历
	cout << "preorder traversal:" << endl;
	tree.preorderTraversal();
	//中序遍历
	cout << endl;
	cout << "inorder traversal:" << endl;
	tree.inorderTraversal();
	//后序遍历
	cout << endl;
	cout << "postorder traversal:" << endl;
	tree.postorderTraversal();
	//层次遍历
	cout << endl;
	cout << "level traversal:" << endl;
	tree.levelTraversal();
	cout << endl;
	cout << endl; cout << endl; cout << endl;

	//构造函数和移动构造函数测试
	cout << "copy constructor tree:" << endl;
	cout << "old tree root is " << tree.root()->data << endl;
	RedBlcak<int>t = tree;
	cout << "new tree root is " << t.root()->data << endl;
	cout << "inorder traversal:" << endl;
	t.inorderTraversal();
	cout << endl;
	cout << endl;
	cout << "move constructor tree:" << endl;
	RedBlcak<int>t1 = std::move(tree);
	cout << "new tree root is " << t1.root()->data << endl;
	cout << "inorder traversal:" << endl;
	t1.inorderTraversal();
	cout << endl; cout << endl;
	cout << "inorder traversal old tree:" << endl;
	cout << endl;
	tree.inorderTraversal();
	
	
	cout << "remove all:\n";
	int sum = t1.size() / 2;
	while (t1.size() > 0)
	{
		int s = rand() % (r.size());
		auto it =r.begin();
		advance(it, s);
		cout << *it << " ";
		t1.remove(*it);
		r.erase(it);
		if (t1.size() == sum) {
			cout << "\n\na test of balance:(blank is normal)\n";
			testHeight(t1);
			cout << endl;
	 }
	}
	cout << "\ntree isempty:" << t1.empty() << ",tree size:" << t1.size()<<",tree black height:"<< t1.height() << endl;
	cout << "inorder traversal empty tree:" << endl;
	t1.inorderTraversal();
	cout << endl;
};
template<typename T>
void testHeight(RedBlcak<T>tree) {
	BNP(T)n = tree.root();
	std::queue< BTN::BinTreeNode<T>*>Q;//引入辅助队列
	Q.push(n);//根节点先入队
	while (!Q.empty())
	{
		BinTreeNode<T>*p = Q.front();//引用队头
		if (tree.test(p)) {
			std::cout << "!!!!!!!!!!error:tree is't balanced!\n";
		}
		Q.pop();//删除已访问节点
		if (p->hasLeftChild()) {
			Q.push(p->left);
		}
		if (p->hasRightChild()) {
			Q.push(p->right);
		}
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
