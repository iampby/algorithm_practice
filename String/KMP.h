#ifndef STRING_ALGORITHM_KMP
#define STRING_ALGORITHM_KMP

/*
kmp�㷨
const char*����
*/

#include<vector>


	/*
	����Ϊ�ַ�������char���Լ�ƥ���ַ���p
	����Pλ��char�����ҷ����ϵ�һ�γ��ֵ�����
	O(n+m)
	*/
	int kmp_match(char*t, char*p);


#endif // !STRING_ALGORITHM_KMP

