// B+Tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<time.h>
#include"BAddTree.h"

using namespace BAT;
using namespace std;
void testBTree();//功能测试
//记录
class Entry
{
public:
	Entry() = default;
	Entry(int k, float e) { this->k = k; this->e = e; };
	~Entry()=default;
	int key()const {//接口函数
		return k;
	};
	float e;
private:
	int k;
	
};
//遍历函数
auto itf = [&](deque <Entry*>&e) {
	int _s = e.size();
	for (int i = 0; i < _s; ++i) {
		printf(" %d ", e[i]->key());
	}
};

int main()
{

	srand(time(NULL));
	testBTree();
}
void testBTree() {
	 BAddTree<int,Entry>tree(5);
	int low, up = 0;
	do {
		low = rand() % 100;
		up = rand() % 100;
		if (up < low) {
			swap(up, low);
		}
	} while (up - low > 1000 || up - low < 20);
	vector<Entry>num;
	for (int i = low; i < up; ++i) {
		num.insert(num.end(),Entry(rand(),(float)rand()/rand()));
	}
	vector<Entry>r;
	cout << "insert values the fllowing:\n" << endl;
	while (!num.empty())
	{
		int s = rand() % (num.size());
		auto it = num.begin();
		advance(it, s);

		cout << num[s].key() << " ";
		bool ok=tree.insert(num[s]);
		if(ok){
		r.insert(r.end(), num[s]);
		}
		else {
			cout << "\n\n\n inserting the entry had failed:" << it->key() << "\n\n";
		}
		num.erase(it);
	}
	cout << "\ntree size:\n" << tree.size() << endl;
	cout << "start  traversal:\n";
 tree.list_traversal(itf);
	cout << endl;
	cout << "remove randomly:\n\t";
	int n = 0;
	while (n++ < 3)
	{
		int x = rand() % r.size();
		auto it = r.begin();
		advance(it, x);
		bool ok=tree.remove(*it);
		if (ok) {
			cout <<it->key() << " ";
		}
		else {
			cout << "\n\n\n removing the entry had failed:"<<it->key()<<"\n\n";
		}
		r.erase(it);
	}
	cout << endl;
	cout << "now tree size:\n" << tree.size() << endl;
	cout << "now i traversal:\n";
	tree.list_traversal(itf);
	cout << endl;
	cout << "remove randomly:\n\t";
	n = 0;
	while (n++ < 3)
	{
		int x = rand() % r.size();
		auto it = r.begin();
		advance(it, x);
		bool ok = tree.remove(*it);
		if (ok) {
			cout << it->key() << " ";
		}
		else {
			cout << "\n\n\n removing the entry had failed:" << it->key() << "\n\n";
		}
		r.erase(it);
	}
	cout << endl;
	cout << "now tree size:\n" << tree.size() << endl;
	cout << "now traversal:\n";
	tree.list_traversal(itf);
	cout << endl;
	cout << "remove all:\n\t";
	n = 0;
	while ( r.size()>0)
	{
		int x = rand() % r.size();
		auto it = r.begin();
		advance(it, x);
		bool ok = tree.remove(*it);
		if (ok) {
			cout << it->key() << " ";
		}
		else {
			cout << "\n\n\n removing the entry had failed:" << it->key() << "\n\n";
		}
		r.erase(it);
	}
	cout << endl;
	cout << "now tree size:\n" << tree.size() << endl;
	cout << "now traversal:\n";
	tree.list_traversal(itf);
	cout << endl;
	//重插
	{
		low, up = 0;
		do {
			low = rand() % 100;
			up = rand() % 100;
			if (up < low) {
				swap(up, low);
			}
		} while (up - low > 1000 || up - low < 20);
		for (int i = low; i < up; ++i) {
			num.insert(num.end(), Entry(rand(), (float)rand() / rand()));
		}
		cout << "insert values the fllowing:\n" << endl;
		while (!num.empty())
		{
			int s = rand() % (num.size());
			auto it = num.begin();
			advance(it, s);

			cout << num[s].key() << " ";
			bool ok = tree.insert(num[s]);
			if (ok) {
				r.insert(r.end(), num[s]);
			}
			else {
				cout << "\n\n\n inserting the entry had failed:" << it->key() << "\n\n";
			}
			num.erase(it);
		}
		cout << endl;
		cout << "now tree size:\n" << tree.size() << endl;
		cout << "now traversal:\n";
		tree.list_traversal(itf);
		cout << endl;
		cout << "remove randomly:\n\t";
		int n =rand()%(r.size()-1)+1;
		while (n-- > 0)
		{
			int x = rand() % r.size();
			auto it = r.begin();
			advance(it, x);
			bool ok = tree.remove(*it);
			if (ok) {
				cout << it->key() << " ";
			}
			else {
				cout << "\n\n\n removing the entry had failed:" << it->key() << "\n\n";
			}
			r.erase(it);
		}
		cout << endl;
		cout << "now tree size:\n" << tree.size() << endl;
		cout << "now i traversal:\n";
		tree.list_traversal(itf);
		cout << endl;
	}
}