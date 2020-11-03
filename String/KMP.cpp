#include"KMP.h"

/*
����Ϊƥ���ַ���
���� next������ʧ��ʱָʾ����
O(m)
*/
std::vector<int> buildNext(char*p) {
	int m = strlen(p), j = 0;
	std::vector<int>next(m, -1);//next��� next[0]=-1
	if (m == 0)return next;//�˻����
	int t = next[0];//��¼t next[j+1]=next[next[j]]+1
	//�����൱�ڶ�ƥ�䴮����һλ������ƥ��
	while (j < m - 1)//j���ɻ��j+1
	{
		if (0 > t || p[j] == p[t]) {
			++j; ++t;
			next[j] = (p[j] != p[t] ? t : next[t]);//next[j+1]=next[next[j]]+1  if p[j] == p[t]  ��Ϊ-1
		}
		else {
			t = next[t];//����t �� next[j+1]
		}
	}
	return next;
}

int kmp_match(char*t, char*p) {
	std::vector<int>next(buildNext(p));//����next���
	if (next.empty())return -1;//�˻����
	int n = strlen(t), i = 0;
	int m = strlen(p), j = 0;
	while (j < m&&i < n)
	{
		if (j < 0 || t[i] == p[j]) {//ƥ�����ʧ��ʱ��ƥ����p �򲽽�
			++i; ++j;
		}
		else j = next[j];//��������ֱ��-1
	}
	if (i - j > n - m)return -1;//ʧ��
	return i - j;
}