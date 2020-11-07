#ifndef ALGORITHM_SORT_H_H_H
#define ALGORITHM_SORT_H_H_H

/*
归并排序
思想：对2个有序序列合并成一个有序序列，每次迭代中，只需比较2个待归并向量的首元素，
取大于或者小于到输出向量的末尾，直到某个为空，则另一个向量元素依次输出到输出向量
O(nlogn）
*/
#include"MergeSort.cpp"

/*
起泡排序
O(n^2)
*/
#include"BubbleSort.cpp"

/*
选择排序
概念:序列分为无序的前缀和有序的后缀，不断从前缀选出最大值作为后缀的首元素
O(nlogn)
*/
#include"SelectSort.cpp"

/*
快速排序
概念：通过分治策略，不停地选取轴点划分空间，得到有序序列，如果序列S经排序后为S'，如有轴点mi，lo为最低为，hi为最高位,则:
1 S[mi]=S'[mi]
2 S[lo,mi)=S'[lo,min)全体成员相同
3 S(mi,hi)=S'(mi,hi)全体成员相同
O(nlogn)
*/
#include"QuickSort.cpp"

/*
希尔排序
概念：等效的把一维A[]向量视为一个二维矩阵B[][],若取行宽w 则有对应关系
B[i][j]=A[i*w+j]或A[k]=B[k/w][k%w] w为增量 w={1,w1,...,wk,...},取 wi<n的最后一个增量开始迭代
每次按增量对A进行w-排序 直到w=1 排序完成
增量序列：Sedgewick序列 实际应用效率综合最优 9*4^k-9*2^k+1(k从0起) 或 4^k-3*2^k+1(从2起) 轮流执行但前者先执行
O（n^(4/3)） 平均O(7/6)
*/
#include"ShellSort.cpp"

#endif // !ALGORITHM_SORT_H_H_H

