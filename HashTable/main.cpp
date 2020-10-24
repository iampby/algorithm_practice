// HashTable.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<chrono>
#include<string>
#include"HashTable.hpp"
#include"Prime.h"

//#define RAND

#ifdef RAND
#define HASH_RAND_MYHASH_INT
#define HASH_RAND_MYMAP
#define HASH_RAND_MYPROBE
#endif // RAND
#include"RelatedFunc.h"

using namespace std;
using namespace HT;
void testPrime();
void testHash();
int main()
{
	//testPrime();
	testHash();
}
void testHash() {

	HashTable<uint32_t,int>ht(50000);
	int n = 30;
	srand(time(nullptr));
	while (--n > 0)rand();
	n=rand()%500000+100000;
	printf("inserting with a scale of %d...\n\t", n);
	auto tm = chrono::steady_clock::now();
	for (int i = 0; i < n; ++i) {
		int k =rand()%n;
		if (!ht.insert(k, k)) {
			//printf("inserting is't successful,the found entry with key %d and value %d\n\t", k, *ht.get(k));
		}
	}
	auto dur = chrono::duration<double>(chrono::steady_clock::now() - tm);
	printf("takes %lf sec...\n\t", dur.count());
	printf("hash table has size %d and capacity %d...\n\t", ht.size(),ht.capacity());
	{
		int range = rand() % n/2;
		printf("removing radomly %d times...\n\t", range);
		tm = chrono::steady_clock::now();
		while (range > 0)
		{
			int k = rand() % n;
			if(ht.remove(k)){
				//printf("query result  is equal zero after  removing entry with key %d ?%d\n\t ", k, ht.get(k) == nullptr);
			}
			--range;
		}
		dur = chrono::duration<double>(chrono::steady_clock::now() - tm);
		printf("takes %lf sec...\n\t", dur.count());
	}
	int range = rand() % n;
	printf("query radomly %d times...\n\t", range);
	tm = chrono::steady_clock::now();
	int _s=0;
	while (range > 0)
	{
		int k = rand() % n;
		int*v = ht.get(k);
		
		if (v) {
			//printf("found the entry with key %d and value %d\n\t", k, *v);
			++_s;
		}
		else {
			//printf("not found key %d\n\t", k);
		}
		--range;
	}
	dur = chrono::duration<double>(chrono::steady_clock::now() - tm);
	printf("takes %lf sec...\n\t", dur.count());
	printf("found %d \n\t",_s);
}
void testPrime() {
	int n = 0;
	int num = 100000;
	cout << "starting to find the prime with a scale of "<<num << endl;
	auto tm = chrono::steady_clock::now();
	for (int i = 0; i < num;++i) {
		if (isPrime(i)) {
			++n;
		}
	}
	auto dur = chrono::duration<double>(chrono::steady_clock::now()-tm);
	cout <<"findding "<<n<<" prime takes "<<dur.count()<<" sec..."<< endl;
  n = 0;
	cout << "starting to find the prime with a scale of " << num << endl;
	tm = chrono::steady_clock::now();
	for (int i = 0; i < num; ++i) {
	
		if (isPrime_Formula(i)) {
			++n;
		}
	}
	dur = chrono::duration<double>(chrono::steady_clock::now() - tm);
	cout << "findding " << n << " prime takes " << dur.count() << " sec..." << endl;
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
