// AVL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"AVL.h"
#include <iostream>
#include<string>
#include<time.h>
using namespace std;
using namespace N_AVL;
//测试全为固定生成树
void testBTN();//树节点功能测试 size zig zag
void testTraversal();//二叉树遍历测试
void testBST();//测试二叉搜索树的插入删除功能
void testAVL();//测试AVL功能 这是随机生成树
int main()
{
	//testBTN();
	//testTraversal();
	//testBST();
	testAVL();

}
void testAVL() {
	AVL<int>tree;
	srand(time(NULL));
	int low, up = 0;
	do {
		low = rand() % 2000;
		up = rand() % 2000;
		if (up < low) {
			swap(up, low);
		}
	} while (up - low > 500);
	vector<int>num;
	for (int i = low; i < up; ++i) {
		num.insert(num.end(), i);
	}
	vector<int>r(num);
	while (!num.empty())
	{
		int s = rand() % (num.size());
		auto it = num.begin();
		advance(it, s);
		tree.insert(*it);
		num.erase(it);
	}
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
	cout << "tree root is " <<tree.root()->data<< endl;
	cout << endl;
	cout << "remove tree root " << tree.root()->data << endl;
	tree.remove(tree.root()->data);
	cout << "now tree root is " << tree.root()->data << endl;
	cout << "inorder traversal:" << endl;
	tree.inorderTraversal();
	cout << endl;
	int x = rand() % r.size();
	auto it = r.begin();
	cout << "remove "  <<r.at(x)<< endl;
	tree.remove(r.at(x));
	advance(it, x);
	r.erase(it);
	cout << "now tree root is " << tree.root()->data << endl;
	cout << "inorder traversal:" << endl;
	tree.inorderTraversal();
	cout << endl;
	 x = rand() % r.size();
	it = r.begin();
	advance(it, x);
	cout << "remove  " <<*it<< endl;
	tree.remove(*it);
	cout << "now tree root is " << tree.root()->data << endl;
	cout << "inorder traversal:" << endl;
	tree.inorderTraversal();
	cout << endl;
	 x = rand() % r.size();
	it = r.begin();
	advance(it, x);
	cout << "remove  " <<*it<< endl;
	tree.remove(*it);
	cout << "now tree root is " << tree.root()->data << endl;
	cout << "inorder traversal:" << endl;
	tree.inorderTraversal();
	cout << endl;
	cout << endl; cout << endl; cout << endl;
	//构造函数和移动构造函数测试
	cout <<"copy constructor tree:"<< endl;
	AVL<int>t=tree;
	cout << "new tree root is " << t.root()->data << endl;
	cout << "inorder traversal:" << endl;
	t.inorderTraversal();
	cout << endl;
	cout << endl;
	cout << "move constructor tree:" << endl;
	AVL<int>t1 =std::move(tree);
	cout << "new tree root is " << t1.root()->data << endl;
	cout << "inorder traversal:" << endl;
	t1.inorderTraversal();
	cout << endl; cout << endl;
	cout << "inorder traversal old tree:" << endl;
	cout << endl;
	tree.inorderTraversal();
}
//BST功能测试
void testBST() {
	BinSearchTree <int>tree;

	srand(time(NULL));
	switch (rand() % 2)
	{	
	case 0:
	{
		tree.insertAsRoot(16);
		BinTreeNode<int> *left = tree.insertAsLeft(tree.root(), 10);
		BinTreeNode<int> *right = tree.insertAsRight(tree.root(), 25);
		right = tree.insertAsLeft(right, 19);
		tree.insertAsRight(right, 22);
		tree.insertAsLeft(right, 17);
		right = tree.insertAsRight(left, 11);
		right = tree.insertAsRight(right, 15);
		tree.insertAsLeft(right, 13);
		left = tree.insertAsLeft(left, 5);
		tree.insertAsRight(left, 8);
		left = tree.insertAsLeft(left, 2);
		tree.insertAsRight(left, 4);
		right = tree.insertAsRight(tree.root()->right, 28);
		tree.insertAsLeft(right, 27);
		right = tree.insertAsRight(right, 37);
		tree.insertAsLeft(right, 33);
	}
	break;
	case 1:
	{
		tree.insert(16);
		tree.insert(10);
		tree.insert(25);
		tree.insert(19);
		tree.insert(22);
		tree.insert(17);
		tree.insert(11);
		tree.insert(15);
		tree.insert(13);
		tree.insert(5);
		tree.insert(8);
		tree.insert(2);
		tree.insert(4);
		tree.insert(28);
		tree.insert(27);
		tree.insert(37);
		tree.insert(33);
	}
	}

	//中序遍历
	cout << "looking here,inorder traversal result:" << endl;
	tree.inorderTraversal(InorderTraversal<int>());
	cout << endl;
	
	cout <<"insert:20 9 1 12 18"<< endl;
	tree.insert(20); tree.insert(9); tree.insert(12); tree.insert(1); tree.insert(18);
	cout << "looking here,inorder traversal result:" << endl;
	tree.inorderTraversal(InorderTraversal<int>());
	cout << endl;
	cout << "insert:16 16 2 16 27 37 37 11" << endl;
	tree.insert(16); tree.insert(16); tree.insert(2); tree.insert(16); tree.insert(27); tree.insert(37); tree.insert(37); tree.insert(11);
	cout << "looking here,inorder traversal result:" << endl;
	tree.inorderTraversal(InorderTraversal<int>()); 
	cout << endl;
	cout << "remove:16 16 2 16 27 37 37 11" << endl;
	tree.remove(16); tree.remove(16); tree.remove(2); tree.remove(16); tree.remove(27); tree.remove(37); tree.remove(37); tree.remove(11);
	cout << "looking here,inorder traversal result:" << endl;
	tree.inorderTraversal(InorderTraversal<int>());
	cout << endl;
	cout << "remove:20 9 1 12 18" << endl;
	tree.remove(20); tree.remove(9); tree.remove(1); tree.remove(12); tree.remove(18);
	cout << "looking here,inorder traversal result:" << endl;
	tree.inorderTraversal(InorderTraversal<int>());
	cout << endl;
}
void testTraversal() {
	BinTree<string>tree;
	tree.insertAsRoot("i");
	BinTreeNode<string> *left= tree.insertAsLeft(tree.root(),"d");
	BinTreeNode<string> *right =tree.insertAsLeft(left, "c");
	right=tree.insertAsLeft(right, "a");
	tree.insertAsRight(right, "b");
	right=tree.insertAsRight(left, "h");
	left=tree.insertAsLeft(right, "f");
	tree.insertAsRight(left, "g");
	tree.insertAsLeft(left, "e");
	right=tree.insertAsRight(tree.root(), "l");
	left=tree.insertAsLeft(right, "k");
	tree.insertAsLeft(left, "j");	
	right=tree.insertAsRight(right, "n");
	tree.insertAsLeft(right, "m");
	right = tree.insertAsRight(right, "p");
	 tree.insertAsLeft(right, "o");
	 //树层次排序为:i   d l   c h k n   a f j m p   b e g o  
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
}

void testBTN() {
	BinTreeNode<int> root;
	root.data = 3;
	BinTreeNode<int>*p= root.insertAsLeft(1);
	p->insertAsLeft(0);
	p->insertAsRight(2);
	p = root.insertAsRight(5);
	p->insertAsLeft(4);
	p = p->insertAsRight(6);
	p->insertAsRight(7);
	cout << "root size:"<<root.size() << endl;
	cout << "left child  size:" << root.left->size()<< endl;
	cout << "right child  size:" << root.right->size() << endl;
	cout << "right child's right child size:" << p->size() << endl;
	cout <<"zig and zag test of new binary search tree:"<< endl;


	BinTree<string>tree;
	tree.insertAsRoot("i");
	BinTreeNode<string> *left = tree.insertAsLeft(tree.root(), "d");
	BinTreeNode<string> *right = tree.insertAsLeft(left, "c");
	right = tree.insertAsLeft(right, "a");
	tree.insertAsRight(right, "b");
	right = tree.insertAsRight(left, "h");
	left = tree.insertAsLeft(right, "f");
	tree.insertAsRight(left, "g");
	tree.insertAsLeft(left, "e");
	right = tree.insertAsRight(tree.root(), "l");
	left = tree.insertAsLeft(right, "k");
	tree.insertAsLeft(left, "j");
	right = tree.insertAsRight(right, "n");
	tree.insertAsLeft(right, "m");
	right = tree.insertAsRight(right, "p");
	tree.insertAsLeft(right, "o");
	cout << "current level traversal:" << endl;
	tree.levelTraversal();
	cout << endl;
	cout << "current inorder traversal:" << endl;
	tree.inorderTraversal();
	cout << endl;
	cout << "zig(i):" << endl;
	tree.root()->zig();
	cout << "now level traversal:" << endl;
	tree.levelTraversal();
	cout << endl;
	cout << "now inorder traversal:" << endl;
	tree.inorderTraversal();
	cout << endl;
	cout << "zag(n):" << endl;
	tree.root()->right->right->zag();
	cout << "now level traversal:" << endl;
	tree.levelTraversal();
	cout << endl;
	cout << "now inorder traversal:" << endl;
	tree.inorderTraversal();
	cout << endl;

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
