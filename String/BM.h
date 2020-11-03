#ifndef STRING_ALGORITHM_BM
#define STRING_ALGORITHM_BM

/*
基于BM的算法，sunday,bmh等
const char*操作
*/

#include<unordered_map>


/*
综合gs与bc策略的bm算法
参数为字符串集合t，以及匹配字符集p
返回P位于t中从左到右方向上第一次出现的索引
O(n+m) Ω（n/m)
*/
int bm_match(char*t, char*p);

/*
参数为字符串集合t，以及匹配字符集p
返回P位于t中从左到右方向上第一次出现的索引
O(n*m) Ω（n/m)
*/
int bc_match(char*t, char*p);

/*
gs策略
参数为字符串集合t，以及匹配字符集p
返回P位于t中从左到右方向上第一次出现的索引
O(n+m+m)
*/
int gs_match(char*t, char*p);

/*
参数为字符串集合t，以及匹配字符集p
返回P位于t中从左到右方向上第一次出现的索引
Sunday平均性能的时间复杂度为O(n)，最差情况的时间复杂度为O(n * m)
*/
int sunday_match(char*t, char*p);


#endif // !STRING_ALGORITHM_BM

