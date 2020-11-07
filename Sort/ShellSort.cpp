
#include"Comparer.h"
#include<vector>


template<typename T=int>
size_t sedk_lastIncrement(size_t n, bool&formula1, int&increment);

/*
希尔排序
概念：等效的把一维A[]向量视为一个二维矩阵B[][],若取行宽w 则有对应关系
B[i][j]=A[i*w+j]或A[k]=B[k/w][k%w] w为增量 w={1,w1,...,wk,...},取 wi<n的最后一个增s量开始迭代 
每次按增量对A进行w-排序 直到w=1 排序完成
增量序列：Sedgewick序列 实际应用效率综合最优 9*4^k-9*2^k+1(k从0起) 或 4^k-3*2^k+1(从2起) 轮流执行但前者先执行
O（n^(4/3)） 平均O(7/6)
*/
template<typename T = int, typename _Comparer = MyLess<T> >
void shellSort(std::vector<T>&_dst, _Comparer _comparer = MyLess<T>()) {
	int n = _dst.size();  
	bool one; int increment;
	size_t k = sedk_lastIncrement(n, one, increment);
	for (; increment > 0; ) {
		for (int i = increment; i < n; i += increment) {//increment-排序
			T bv = _dst[i];//记录点 
			int li = i - increment;//同一列的上一个点
			while (li>=0&&_comparer(bv,_dst[li]))
			{
				_dst[li + increment] = _dst[li];; li -= increment;
			}
			_dst[li + increment] = bv;//归为迭代交换的值bv
		}
		//更新增量
		if (one) {
			one = !one;
			k += 1;
			increment = pow(4, k) - 3 * pow(2, k) + 1;
		}
		else {
			one = !one;
			k -= 2;
			increment = 9 * pow(4, k) - 9 * pow(2, k) + 1;
		}
	}
}

/*
返回Sedgewick增量序列的小于n的最后一个增量
formula1==true指示最后一个增量使用9 * 4 ^ k - 9 * 2 ^ k + 1得到 否则 4 ^ k - 3 * 2 ^ k + 1得到
返回值为k
*/
template<typename T>
size_t sedk_lastIncrement(size_t n, bool&formula1, int&increment)
{
	//9 * 4 ^ k - 9 * 2 ^ k + 1(k从0起)或 4 ^ k - 3 * 2 ^ k + 1(从2起)
	int k = (n - 1) / 9;
	k = log2(k) / 2;
	increment = 9 * pow(4, k) - 9 * pow(2, k) + 1;
	formula1 = true;//代表上一次使用9 * 4 ^ k - 9 * 2 ^ k + 1公式
	while (increment < n)
	{
		if (formula1) {
			k += 2;
			increment = pow(4, k) - 3 * pow(2, k) + 1;
			formula1 = false;
		}
		else {
			k -= 1;
			increment = 9 * pow(4, k) - 9 * pow(2, k) + 1;
			formula1 = true;
		}
	}
	if (formula1) {
		k += 1;
		formula1 = !formula1;
		increment = pow(4, k) - 3 * pow(2, k) + 1;
	}
	else {
		k -= 2;
		formula1 = !formula1;
		increment = 9 * pow(4, k) - 9 * pow(2, k) + 1;
	}
	return k;
}
