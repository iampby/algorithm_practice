// String.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include<chrono>
#include<time.h>
#include"KMP.h"
#include"BM.h"
#include"Prime.h"
#include"KR.h"

using namespace std;
//debug测试
void randTest();//随机测试匹配结果
void randPerformanceTest();//匹配算法随机性能测试
//高强度随机性能测试 对千万级n与千级m随机测试,kr大部分最优其次gs,再次bm略胜bc一筹,kmp略差bm,sunday略差bm一筹
//测试kr最好 gs次之（debug）
void randStengthTest();
//测试全为固定案列
void testSS();
void testGS();

std::vector<int>buildSS(char*p);
std::vector<int>buildGS(char*p);


int main()
{
	srand((unsigned int)time(nullptr));
//	testSS();
	//testGS();
	//randTest();
	//randPerformanceTest();
randStengthTest();
}
void randStengthTest() {
	int count =5;// rand() % 10;
	printf("\ttesting the performance of matching algorithm with hight strength and scale %d:\n\t", count);

	int tn = count;
	while (tn-->0)
	{
		printf("\n\tthe %d times test...\n\t", count - tn);
	int n = rand()*rand();
	int m = rand();
	string t; t.reserve(n);
	string p; p.reserve(m);
	printf("\tt with scale %d  and p with sacele %d:\n\t", n, m);
	auto tm = chrono::steady_clock::now();
	while (n-- > 0)
	{
		t.push_back((rand()% 16 + 97));//97-122
	}
	while (m-- > 0)
	{
		p.push_back((rand()% 16 + 97));//97-122
	}
	//p.append("mmasbsadfsafdsicediadnbicenicxxxopdyiusndgfjisyedmmasfsasmm");
	chrono::duration<double> dur = chrono::steady_clock::now() - tm;
	printf("\ttakes %lf sec for building the t and p...\n\t", dur.count());

	printf("\ttesting the kmp stretagy:\n\t");
   tm = chrono::steady_clock::now();
		int kmp=kmp_match((char*)t.data(), (char*)p.data());
	 dur = chrono::steady_clock::now() - tm;
	printf("\t...kmp stretagy takes %lf sec averagely...\treturn a index %d...\n\t", dur.count()/count,kmp);

	printf("\ttesting the bc stretagy:\n\t");
	tm = chrono::steady_clock::now();
	int bc=	bc_match((char*)t.data(), (char*)p.data());
	dur = chrono::steady_clock::now() - tm;
	printf("\t...bc stretagy takes %lf sec averagely...\treturn a index %d...\n\t\n\t", dur.count() / count,bc);

	printf("\ttesting the gs stretagy:\n\t");
	tm = chrono::steady_clock::now();
		int gs=gs_match((char*)t.data(), (char*)p.data());
	dur = chrono::steady_clock::now() - tm;
	printf("\t...gs stretagy takes %lf sec averagely...\treturn a index %d...\n\t\n\t", dur.count() / count,gs);

	printf("\ttesting the bc and gs stretagy:\n\t");
	tm = chrono::steady_clock::now();
		int bm=bm_match((char*)t.data(), (char*)p.data());
	dur = chrono::steady_clock::now() - tm;
	printf("\t...bc and gs stretagy takes %lf sec averagely...\treturn a index %d...\n\t\n\t", dur.count() / count,bm);

	printf("\ttesting the sunday stretagy:\n\t");
	tm = chrono::steady_clock::now();
	int sd = sunday_match((char*)t.data(), (char*)p.data());
	dur = chrono::steady_clock::now() - tm;
	printf("\t...sunday stretagy takes %lf sec averagely...\treturn a index %d...\n\t\n\t", dur.count() / count, sd);

	printf("\ttesting the Karp-Rabin stretagy:\n\t");
	tm = chrono::steady_clock::now();
	int kr = kr_match((char*)t.data(), (char*)p.data());
	dur = chrono::steady_clock::now() - tm;
	printf("\t...Karp-Rabin stretagy takes %lf sec averagely...\treturn a index %d...\n\t\n\t", dur.count() / count, kr);

	if (kmp != bm || bm != bc || bc != gs || gs != sd||sd!=kr||kr!=kmp) {
		printf("\t\n\t............................................................\n\terror: result of the four string matching algorithm is different\n\t............................................................\n\t\n\t");
		system("pause");
	}

	}
	printf("\n\tend\n\t");
};
void randPerformanceTest() {
	int count = rand()*rand()%50000;
	printf("\ttesting the performance of matching algorithm with scale %d:\n\t", count);

	int tn = count;
	printf("\ttesting the kmp stretagy:\n\t");
	auto tm = chrono::steady_clock::now();
	while (tn-->0)
	{
		int n = rand() % 500;
		int m = n * ((double)rand() / RAND_MAX / 20);//1/4n
		if (rand() % 2)m *= 2;
		else m /= 2;
		if (rand() % 2)m += 1;
		string t; t.reserve(n);
		string p; p.reserve(m);
		while (n-- > 0)
		{
			t.push_back((rand() % 16 +97));//97-122
		}
		while (m-- > 0)
		{
			p.push_back((rand() % 16 +97));//97-122
		}
		 kmp_match((char*)t.data(), (char*)p.data());
	}
	chrono::duration<double> dur = chrono::steady_clock::now() - tm;
	printf("\t...kmp stretagy takes %lf sec...\n\t", dur.count());

	 tn = count;
	printf("\ttesting the bc stretagy:\n\t");
	 tm = chrono::steady_clock::now();
	while (tn-- > 0)
	{
		int n = rand() % 500;
		int m = n * ((double)rand() / RAND_MAX / 20);//1/4n
		if (rand() % 2)m *= 2;
		else m /= 2;
		if (rand() % 2)m += 1;
		string t; t.reserve(n);
		string p; p.reserve(m);
		while (n-- > 0)
		{
			t.push_back((rand() % 16 +97));//97-122
		}
		while (m-- > 0)
		{
			p.push_back((rand() % 16 +97));//97-122
		}
		bc_match((char*)t.data(), (char*)p.data());
	}
	 dur = chrono::steady_clock::now() - tm;
	printf("\t...bc stretagy takes %lf sec...\n\t", dur.count());

	tn = count;
	printf("\ttesting the gs stretagy:\n\t");
	tm = chrono::steady_clock::now();
	while (tn-- > 0)
	{
		int n = rand() % 500;
		int m = n * ((double)rand() / RAND_MAX / 20);//1/4n
		if (rand() % 2)m *= 2;
		else m /= 2;
		if (rand() % 2)m += 1;
		string t; t.reserve(n);
		string p; p.reserve(m);
		while (n-- > 0)
		{
			t.push_back((rand() % 16 + 97));//97-122
		}
		while (m-- > 0)
		{
			p.push_back((rand() % 16 + 97));//97-122
		}
		gs_match((char*)t.data(), (char*)p.data());
	}
	dur = chrono::steady_clock::now() - tm;
	printf("\t...gs stretagy takes %lf sec...\n\t", dur.count());

	tn = count;
	printf("\ttesting the bc and gs stretagy:\n\t");
	tm = chrono::steady_clock::now();
	while (tn-- > 0)
	{
		int n = rand() % 500;
		int m = n * ((double)rand() / RAND_MAX / 20);//1/4n
		if (rand() % 2)m *= 2;
		else m /= 2;
		if (rand() % 2)m += 1;
		string t; t.reserve(n);
		string p; p.reserve(m);
		while (n-- > 0)
		{
			t.push_back((rand() % 16 +97));//97-122
		}
		while (m-- > 0)
		{
			p.push_back((rand() % 16 +97));//97-122
		}
		bm_match((char*)t.data(), (char*)p.data());
	}
	dur = chrono::steady_clock::now() - tm;
	printf("\t...bc and gs stretagy takes %lf sec...\n\t", dur.count());
	printf("\tend\n\t");
};
void randTest() {
	int count = rand() %970 + 30;
	printf("\ttesting the match %d times:\n\t",count);
	chrono::time_point<chrono::steady_clock> tm= chrono::steady_clock::now();
	chrono::duration<double> dur;
	while (count-- > 0)
	{
		int n = rand() % 500;
		int m = n * ((double)rand() / RAND_MAX /20);//1/4n
		if (rand() % 2)m *= 2;
		else m /= 2;
		if (rand()%2)m +=  1;
		string t; t.reserve(n);
		string p; p.reserve(m);
		while (n-- > 0)
		{
			t.push_back((rand() % 16 +97));//97-122
		}
		while (m-- > 0)
		{
			p.push_back((rand() % 16 +97));//97-122
		}
		printf("\tt:\n\t%s\n\t", t.data());
		printf("\tp:\n\t%s\n\t", p.data());

		tm = chrono::steady_clock::now();
		int bm = bm_match((char*)t.data(), (char*)p.data());
		dur = chrono::steady_clock::now() - tm;
		printf("\tbm match takes  %lf sec...return a index %d...\n\t", dur.count(), bm);

		tm = chrono::steady_clock::now();
		int bc = bc_match((char*)t.data(), (char*)p.data());
		dur = chrono::steady_clock::now() - tm;
		printf("\tbc match takes  %lf sec...return a index %d...\n\t", dur.count(), bc);

		tm = chrono::steady_clock::now();
		int gs = gs_match((char*)t.data(), (char*)p.data());
		dur = chrono::steady_clock::now() - tm;
		printf("\tgs match takes %lf sec...return a index %d...\n\t", dur.count(), gs);

		tm = chrono::steady_clock::now();
		int kmp = kmp_match((char*)t.data(), (char*)p.data());
		dur = chrono::steady_clock::now() - tm;
		printf("\tkmp match takes %lf sec...return a index %d...\n\t", dur.count(), kmp);

		if (kmp != bm || bm != bc || bc != gs||gs!=kmp) {
			printf("\t\n\t............................................................\n\terror: result of the four string matching algorithm is different\n\t............................................................\n\t\n\t");
			system("pause");
		}
	}
	printf("\tend\n\t");
};
void testGS() {
	printf("\tbuilding the GS:\n\t");
	const char*p = "iced rice price";//12 12 12 12 12 12 12 12 12 12 6 12 15 15 1
	vector<int>gs = buildGS((char*)p);
	printf("string:\n\ticed rice price\n\t");
	printf("corrected result:\n\t12 12 12 12 12 12 12 12 12 12 6 12 15 15 1\n\t");
	printf("gs:\n\t");
	for (int i = 0; i < gs.size(); ++i) {
		printf("%d ", gs[i]);
	}
	cout << endl;
};
void testSS() {
	printf("\tbuilding the SS:\n\t");
	const char*p = "iced rice price";//0 0 3 0 0 0 0 0 4 0 0 0 0 0 15
	vector<int>ss = buildSS((char*)p);
	printf("string:\n\ticed rice price\n\t");
	printf("corrected result:\n\t0 0 3 0 0 0 0 0 4 0 0 0 0 0 15\n\t");
	printf("ss:\n\t");
	for(int i=0;i<ss.size();++i){
		printf("%d ",ss[i]);
	}
	cout << endl;
};
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
