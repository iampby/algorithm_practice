#include"BM.h"


/*
生成BC表 用map记录 参数为匹配串
返回map用与失配时指示步进
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
生成SS表 用vector记录 参数为匹配串
返回vector用与失配时指示（|MS[j]|）长度，即P[0，j]与P[m-j-1,m)的匹配后缀的最大长度
O(m)
*/
std::vector<int>buildSS(char*p) {
	int m = strlen(p);//m
	std::vector<int>ss(m, 0);//SS 初始化为0
	if (ss.empty())return ss;//退化
	int hi = m - 1, lo = m - 1;//表示好后缀 即p(lo,hi]=p[m-hi+lo,m)
	int j = m - 1;//自右向左的迭代位置
	ss[j] = m;//第一个移动整列
	//生成ss,从右边第二个开始迭代
	while (--j >= 0) {
		//情况一 通过之前记录的最长后缀  p(lo,hi]=p[m-hi+lo,m)可知  即lo-hi之间与m-hi+lo-m-1之间对应的后缀长度是一致的
		//但有可能发生重复片段如 xbacdbacdbacdba,依照第二个a的后缀计算第三个a时 MJ[j]值是大于j-lo的,但第一个a的MJ[j]是远远小于第三个a的MJ[j]值
		//即当对应的后缀MJ[j]大于j-lo时,超出了记录的后缀的预知力,这是需要更新最长后缀
		int opj = m - hi + j - 1;
		if (lo < j&&ss[opj] <= j - lo) {
			ss[j] = ss[opj];
		}
		else {//情况二 不能利用记录的友缀信息 即出现后缀的不能预知字符（因对应字符超出预测范围）或者后缀已经利用完
			hi = j; lo = std::_Min_value(hi, lo);//更新hi与lo,使其在超出预知力时继续循环检测，或者重新检测后缀
			while (lo >= 0 && p[lo] == p[m - 1 - hi + lo])
				--lo;
			ss[j] = hi - lo;//记录
		}
	}
	return ss;
}

/*
生成GS表 用vector记录 参数为匹配串
返回vector用与失配时指示p右移位数
O(m)
*/
std::vector<int>buildGS(char*p) {
	int m = strlen(p);
	std::vector<int>gs(m, m);
	if (gs.empty())return gs;//退化
	std::vector<int>ss = buildSS(p);//ss表

	int j = -1; int i = 0;//标记情况1上次更新位置作为新更新的起点位置，不覆盖之前的更新
	while (++j < m - 1)//遍历全部 j<=m+2 w=u存在
	{
		if (ss[m - 1 - j] == m - 1 - j + 1) {//情况1  没有V(k),gs[j]=m-|V(k)| 即ss[j]=j+1的左侧全部取m-j-1 自右向左
			while (i < j)
			{
				gs[i] = std::_Min_value(j, gs[i]);;//选取小的作为位移量
				++i;
			}
		}//情况2 gs[j]=j-k  即含有真后缀 p[j]<=j gs[m-ss[j]-1]=m-j-1  自左向右
		gs[m - ss[j] - 1] = m - j - 1;//选取小的位移距离
	}
	return gs;
}

int bm_match(char*t, char*p) {
	int n = strlen(t), i = 0;
	int m = strlen(p), j = 0;
	if (n < m || m == 0)return -1;//退化
	std::unordered_map<char, int>bc(buildBC(p));//坏字符表
	std::vector<int>gs(buildGS(p));//gs表
	while (n >= i + m)//溢出条件
	{
		j = m - 1;//自右向左匹配
		while (p[j] == t[i + j])
			if (--j < 0) {
				return i;//匹配成功
			}
		auto it = bc.find(t[i + j]);
		int  _bc = j - (it == bc.end() ? j - m : it->second);
		i += std::_Max_value(_bc, gs[j]);//取gs与bc策略中的较大位移者
	};
	return -1;
}

int bc_match(char*t, char*p) {
	int n = strlen(t), i = 0;
	int m = strlen(p), j = 0;
	if (n < m || m == 0)return -1;//退化
	std::unordered_map<char, int> bc = buildBC(p);//坏字符表
	while (n >= i + m)//溢出条件
	{
		j = m - 1;//自右向左匹配
		while (p[j] == t[i + j])
			if (--j < 0)return i;//匹配成功
		auto it = bc.find(t[i + j]);
		int _mv = j - (it == bc.end() ? j - m : it->second);//t左移bc[t[i+j]]; 
		if (_mv < 0)i += 1;//负数往返移动 简单右移动
		else
			i += _mv;
	};
	return -1;
}

int gs_match(char*t, char*p) {
	int n = strlen(t), i = 0;
	int m = strlen(p), j = 0;
	if (n < m || m == 0)return -1;//退化
	std::vector<int>gs = buildGS(p);//gs表
	while (n >= i + m)//溢出条件
	{
		j = m - 1;//自右向左匹配
		while (p[j] == t[i + j])
			if (--j < 0)return i;//匹配成功
		i += gs[j];
	};
	return -1;
}

int sunday_match(char*t, char*p) {
	int n = strlen(t), i = 0;
	int m = strlen(p), j = 0;
	if (n < m || m == 0)return -1;//退化
	std::unordered_map<char, int> bc = buildBC(p);//坏字符表
	while (n >= i + m + 1)//溢出条件
	{
		j = m - 1;//自右向左匹配
		while (p[j] == t[i + j])
			if (--j < 0)return i;//匹配成功
		auto it = bc.find(t[i + m]);
		if (it == bc.end()) {//情况1 如果t匹配子串之后一位不存在则整个移动m+i+1
			i += m + 1;
		}
		else {//情况二 存在则找最右的k即最短移位到m+i 即m-k
			i += m - it->second;
		}
	};
	if (i <= n - m) {
		j = 0;//自左向右匹配
		while (p[j] == t[i + j])
			if (++j == m)return i;//匹配成功
	}
	return -1;
}

