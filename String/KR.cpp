#include "KR.h"
#include"Prime.h"

//m需要选取合适的模 这里选取最大值和不选取一样
//constexpr uint64_t M =  18446744073709551611;//32位最大素数为散列表长度 
constexpr uint64_t R= 31;//基数:这里借鉴 BKDR Hash

/*
BKDR Hash
*/
uint64_t BKDRHash(const char*c){
	uint64_t hash = 0;
	//直到字符串第一个00
	while (uint64_t ch =(uint64_t)*c++)
	{
		hash = hash * 1313 + ch;//可取31,131,1313...
	}
	return hash;
}

uint64_t digit(char c) {
	return c ;
}

/*
暴力匹配m个字符是否相等 O(m)
参数 字符串 匹配串 位置 长度
*/
bool isMatch(char*t,char*p,uint64_t pos,uint64_t m) {
	size_t i = 0;
	for (; i < m ;) {
		if (t[pos++] != p[i++])return false;
	}
	return true;
}

/*
更新码 O(1)
参数 t:字符集 k:当前位置 m:长度 dm：最高位影响值 hashCode：更新码
O(1)
*/
void updateHash(char*t, uint64_t&k,uint64_t m,uint64_t&dm,uint64_t&hashCode ) {
	hashCode = (hashCode - digit(t[k - 1]) * dm) ;
	hashCode = (hashCode*R+ digit(t[k+m-1]));
}

int kr_match(char * t, char * p)
{
	const uint64_t n = strlen(t);const uint64_t m = strlen(p);
	if (n < m || m == 0)return -1;//退化
	uint64_t dm = 1; uint64_t ht = 0, hm = 0;
	for (uint64_t i = 1; i < m; ++i) {
		dm = (dm*R);
	}
	for (uint64_t i = 0; i < m; ++i)
	{
		hm = (hm*R + digit(p[i]));
		ht = (ht*R + digit(t[i]));
	}
	int _c = n - m;
	for (uint64_t i = 0; ;) {
		if (ht == hm) {
			if (isMatch(t, p, i, m))return i;
		}
		if (++i >_c)return -1;
		updateHash(t,i,m,dm,ht);//更新下一段码
	}
}

