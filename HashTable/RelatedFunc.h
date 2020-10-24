#ifndef  RELATEDFUNC_H_H
#define RELATEDFUNC_H_H

#include<iostream>

#ifdef HASH_RAND_MYHASH_INT //随机数生成码 注意跨平台移植兼容性
inline uint32_t myHash(const uint32_t&key)
{
	srand(key);//生成随机数列
	return rand();
}
inline uint32_t myHash(const int&key)
{
	srand(key);//生成随机数列
	return rand();
}
#else
inline uint32_t myHash(const uint32_t&key)
{
	return key;
}
inline uint32_t myHash(const int&key)
{
	return key;
}
#endif //  HASH_RAND_MYHASH 
#ifdef HASH_RAND_MYMAP //随机数映射 注意跨平台移植兼容性
inline uint32_t myMap(const uint32_t&k, uint32_t m) {
	srand(k);
	return  rand() % m;
}
#else 
static int a=0, b=0;
inline uint32_t myMap(const uint32_t&k, uint32_t m) {//MAD法
	if (a == 0) {
		 a = m + 1;
		 b = 3;
		while (m%b == 0)
		{
			b += 2;
		}
	}
	return (k * a + b)%m;
}
#endif // HASH_RAND_MYMAP
#ifdef HASH_RAND_MYPROBE
static int a = 0, b = 0;
inline uint32_t myProbe(const uint32_t&k, uint32_t m, int j) {//随机线性法试探
	srand(k);
	return  (rand()+  j) % m;
}
#else
inline uint32_t myProbe(const uint32_t&k, uint32_t m, int j) {//线性平方法试探
	return  (k + j * j) % m;
}
#endif // HASH_RAND_MYPROBE


#endif // ! RELATEDFUNC_H_H

