#include"BM.h"


/*
����BC�� ��map��¼ ����Ϊƥ�䴮
����map����ʧ��ʱָʾ����
O(m)
*/
std::unordered_map<char, int>buildBC(char*p) {
	std::unordered_map<char, int>bc;
	int m = strlen(p);
	bc.reserve(m);
	for (int j = 0; j < m; ++j) {
		bc[p[j]] = j;
	}
	return bc;
}

/*
����SS�� ��vector��¼ ����Ϊƥ�䴮
����vector����ʧ��ʱָʾ��|MS[j]|�����ȣ���P[0��j]��P[m-j-1,m)��ƥ���׺����󳤶�
O(m)
*/
std::vector<int>buildSS(char*p) {
	int m = strlen(p);//m
	std::vector<int>ss(m, 0);//SS ��ʼ��Ϊ0
	if (ss.empty())return ss;//�˻�
	int hi = m - 1, lo = m - 1;//��ʾ�ú�׺ ��p(lo,hi]=p[m-hi+lo,m)
	int j = m - 1;//��������ĵ���λ��
	ss[j] = m;//��һ���ƶ�����
	//����ss,���ұߵڶ�����ʼ����
	while (--j >= 0) {
		//���һ ͨ��֮ǰ��¼�����׺  p(lo,hi]=p[m-hi+lo,m)��֪  ��lo-hi֮����m-hi+lo-m-1֮���Ӧ�ĺ�׺������һ�µ�
		//���п��ܷ����ظ�Ƭ���� xbacdbacdbacdba,���յڶ���a�ĺ�׺���������aʱ MJ[j]ֵ�Ǵ���j-lo��,����һ��a��MJ[j]��ԶԶС�ڵ�����a��MJ[j]ֵ
		//������Ӧ�ĺ�׺MJ[j]����j-loʱ,�����˼�¼�ĺ�׺��Ԥ֪��,������Ҫ�������׺
		int opj = m - hi + j - 1;
		if (lo < j&&ss[opj] <= j - lo) {
			ss[j] = ss[opj];
		}
		else {//����� �������ü�¼����׺��Ϣ �����ֺ�׺�Ĳ���Ԥ֪�ַ������Ӧ�ַ�����Ԥ�ⷶΧ�����ߺ�׺�Ѿ�������
			hi = j; lo = std::_Min_value(hi, lo);//����hi��lo,ʹ���ڳ���Ԥ֪��ʱ����ѭ����⣬�������¼���׺
			while (lo >= 0 && p[lo] == p[m - 1 - hi + lo])
				--lo;
			ss[j] = hi - lo;//��¼
		}
	}
	return ss;
}

/*
����GS�� ��vector��¼ ����Ϊƥ�䴮
����vector����ʧ��ʱָʾp����λ��
O(m)
*/
std::vector<int>buildGS(char*p) {
	int m = strlen(p);
	std::vector<int>gs(m, m);
	if (gs.empty())return gs;//�˻�
	std::vector<int>ss = buildSS(p);//ss��

	int j = -1; int i = 0;//������1�ϴθ���λ����Ϊ�¸��µ����λ�ã�������֮ǰ�ĸ���
	while (++j < m - 1)//����ȫ�� j<=m+2 w=u����
	{
		if (ss[m - 1 - j] == m - 1 - j + 1) {//���1  û��V(k),gs[j]=m-|V(k)| ��ss[j]=j+1�����ȫ��ȡm-j-1 ��������
			while (i < j)
			{
				gs[i] = std::_Min_value(j, gs[i]);;//ѡȡС����Ϊλ����
				++i;
			}
		}//���2 gs[j]=j-k  ���������׺ p[j]<=j gs[m-ss[j]-1]=m-j-1  ��������
		gs[m - ss[j] - 1] = m - j - 1;//ѡȡС��λ�ƾ���
	}
	return gs;
}

int bm_match(char*t, char*p) {
	int n = strlen(t), i = 0;
	int m = strlen(p), j = 0;
	if (n < m || m == 0)return -1;//�˻�
	std::unordered_map<char, int>bc(buildBC(p));//���ַ���
	std::vector<int>gs(buildGS(p));//gs��
	while (n >= i + m)//�������
	{
		j = m - 1;//��������ƥ��
		while (p[j] == t[i + j])
			if (--j < 0) {
				return i;//ƥ��ɹ�
			}
		auto it = bc.find(t[i + j]);
		int  _bc = j - (it == bc.end() ? j - m : it->second);
		i += std::_Max_value(_bc, gs[j]);//ȡgs��bc�����еĽϴ�λ����
	};
	return -1;
}

int bc_match(char*t, char*p) {
	int n = strlen(t), i = 0;
	int m = strlen(p), j = 0;
	if (n < m || m == 0)return -1;//�˻�
	std::unordered_map<char, int> bc = buildBC(p);//���ַ���
	while (n >= i + m)//�������
	{
		j = m - 1;//��������ƥ��
		while (p[j] == t[i + j])
			if (--j < 0)return i;//ƥ��ɹ�
		auto it = bc.find(t[i + j]);
		int _mv = j - (it == bc.end() ? j - m : it->second);//t����bc[t[i+j]]; 
		if (_mv < 0)i += 1;//���������ƶ� �����ƶ�
		else
			i += _mv;
	};
	return -1;
}

int gs_match(char*t, char*p) {
	int n = strlen(t), i = 0;
	int m = strlen(p), j = 0;
	if (n < m || m == 0)return -1;//�˻�
	std::vector<int>gs = buildGS(p);//gs��
	while (n >= i + m)//�������
	{
		j = m - 1;//��������ƥ��
		while (p[j] == t[i + j])
			if (--j < 0)return i;//ƥ��ɹ�
		i += gs[j];
	};
	return -1;
}

int sunday_match(char*t, char*p) {
	int n = strlen(t), i = 0;
	int m = strlen(p), j = 0;
	if (n < m || m == 0)return -1;//�˻�
	std::unordered_map<char, int> bc = buildBC(p);//���ַ���
	while (n >= i + m + 1)//�������
	{
		j = m - 1;//��������ƥ��
		while (p[j] == t[i + j])
			if (--j < 0)return i;//ƥ��ɹ�
		auto it = bc.find(t[i + m]);
		if (it == bc.end()) {//���1 ���tƥ���Ӵ�֮��һλ�������������ƶ�m+i+1
			i += m + 1;
		}
		else {//����� �����������ҵ�k�������λ��m+i ��m-k
			i += m - it->second;
		}
	};
	if (i <= n - m) {
		j = 0;//��������ƥ��
		while (p[j] == t[i + j])
			if (++j == m)return i;//ƥ��ɹ�
	}
	return -1;
}

