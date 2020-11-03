#ifndef STRING_ALGORITHM_KMP
#define STRING_ALGORITHM_KMP

/*
kmp算法
const char*操作
*/

#include<vector>


	/*
	参数为字符串集合char，以及匹配字符集p
	返回P位于char从左到右方向上第一次出现的索引
	O(n+m)
	*/
	int kmp_match(char*t, char*p);


#endif // !STRING_ALGORITHM_KMP

