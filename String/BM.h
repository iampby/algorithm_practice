#ifndef STRING_ALGORITHM_BM
#define STRING_ALGORITHM_BM

/*
����BM���㷨��sunday,bmh��
const char*����
*/

#include<unordered_map>


/*
�ۺ�gs��bc���Ե�bm�㷨
����Ϊ�ַ�������t���Լ�ƥ���ַ���p
����Pλ��t�д����ҷ����ϵ�һ�γ��ֵ�����
O(n+m) ����n/m)
*/
int bm_match(char*t, char*p);

/*
����Ϊ�ַ�������t���Լ�ƥ���ַ���p
����Pλ��t�д����ҷ����ϵ�һ�γ��ֵ�����
O(n*m) ����n/m)
*/
int bc_match(char*t, char*p);

/*
gs����
����Ϊ�ַ�������t���Լ�ƥ���ַ���p
����Pλ��t�д����ҷ����ϵ�һ�γ��ֵ�����
O(n+m+m)
*/
int gs_match(char*t, char*p);

/*
����Ϊ�ַ�������t���Լ�ƥ���ַ���p
����Pλ��t�д����ҷ����ϵ�һ�γ��ֵ�����
Sundayƽ�����ܵ�ʱ�临�Ӷ�ΪO(n)����������ʱ�临�Ӷ�ΪO(n * m)
*/
int sunday_match(char*t, char*p);


#endif // !STRING_ALGORITHM_BM

