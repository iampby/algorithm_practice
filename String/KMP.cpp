#include"KMP.h"

/*
参数为匹配字符串
返回 next表用与失配时指示步进
O(m)
*/
std::vector<int> buildNext(char*p) {
	int m = strlen(p), j = 0;
	std::vector<int>next(m, -1);//next表格 next[0]=-1
	if (m == 0)return next;//退化情况
	int t = next[0];//记录t next[j+1]=next[next[j]]+1
	//以下相当于对匹配串左移一位进行自匹配
	while (j < m - 1)//j即可获得j+1
	{
		if (0 > t || p[j] == p[t]) {
			++j; ++t;
			next[j] = (p[j] != p[t] ? t : next[t]);//next[j+1]=next[next[j]]+1  if p[j] == p[t]  设为-1
		}
		else {
			t = next[t];//更新t 即 next[j+1]
		}
	}
	return next;
}

int kmp_match(char*t, char*p) {
	std::vector<int>next(buildNext(p));//构造next表格
	if (next.empty())return -1;//退化情况
	int n = strlen(t), i = 0;
	int m = strlen(p), j = 0;
	while (j < m&&i < n)
	{
		if (j < 0 || t[i] == p[j]) {//匹配或者失配时已匹配完p 则步进
			++i; ++j;
		}
		else j = next[j];//不断右移直至-1
	}
	if (i - j > n - m)return -1;//失配
	return i - j;
}