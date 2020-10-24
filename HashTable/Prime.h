#ifndef PRIME_H_H
#define PRIME_H_H
#include<iostream>
//#include<deque>
/*
求素数 
方法一:(此方法需建表，不适用，改为质因数分析法)
构建素数表的方式计算
(1) 设定变量P=0, 作为标志变量, P=0表示N为素数, P=1表示N不是素数;设定变量K, K为N的位数.如果K=1, 则T1={3, 7}.
(2) 如果TK-1不存在, 先计算生成TK-2;如果TK-1存在, M从素数表TK-1中依次取值循环执行 (3) ;
(3) 如果M小于等于根号N, 则N除以M;若余数为零, 则P=1, 跳到 (5) ;
(4) 取TK-1中的下一数值回到 (3) .如全部取完, 则到 (5) ;
(5) 如果P=0, 则N是素数, 否则N不是素数.
方法二
奇数是由素数和奇合数组成的，用奇合数公式判断
N0=4k1*k2＋2k1＋2k2＋1  奇合数公式
推 k2=((N0-1)/2-k1)/(2k1+1)
k2为整数
1=<k1<(N0-1)/6-1/3
*/
/*
效率 O(2sqrt(number)/5)
*/
static bool isPrime(const uint32_t & number)
{
	//方法一 不适用
	/*
	if (number == 0)return false;//极端情况
	bool p = true;//标记变量
	
	uint32_t k =(uint32_t)log10(number)+1;//位数
if (k == 1) {
	if ( number != 2 && number != 3 && number != 5 && number != 7)p = false;
	return p;
	}
uint32_t _1 = number - number / 10 * 10;
if (_1 == 1 || _1 == 7 || _1 == 3 || _1 == 9) {//奇数 执行检测
	std::deque<uint32_t>T;//集合
	T.push_back(3); T.push_back(7);//T1
	if (k == 2) {
		uint32_t _s = T.size();

		for (uint32_t i = 0; i < _s; ++i) {
			if (number%T[i] == 0) {
				p = false;
				break;
			}
}
		return p;
	}
	else {//生成Tk-1 
		uint16_t _max = (uint32_t)pow(10, k - 1);
		uint32_t _1 = 1;//个位数
		for (uint32_t i = 11; i < _max; ) {
			uint32_t _range = sqrt(i);
			switch (_1)//质因数分析法求素数集合
			{
			case 1:
			{
				bool p = true;//标记变量
				for (uint32_t j = 3; j <= _range; j += 10) {
					if (i%j == 0 || i % (j + 6) == 0 || (i % (j + 8) == 0 && (j + 8) != i)) {//有可能溢出为i 过滤一下
						p = false;
						break;
					}
				}
				if (p) T.push_back(i);
				_1 = 3;//下一步为3
				i += 2;//跳2步
			}
			break;
			case 3:
			{
				bool p = true;//标记变量
				for (uint32_t j = 3; j <= _range; j += 10) {
					if (i%j == 0 || i % (j + 4) == 0) {
						p = false;
						break;
					}
				}
				if (p) T.push_back(i);
				_1 = 7;//下一步为7
				i += 4;//跳4步
			}
			break;
			case 7:
			{
				bool p = true;//标记变量
				for (uint32_t j = 3; j <= _range; j += 10) {
					if (i%j == 0 || i % (j + 4) == 0) {
						p = false;
						break;
					}
				}
				if (p) T.push_back(i);
				_1 = 9;//下一步为9
				i += 2;//跳2步
			}
			break;
			case 9:
			{
				bool p = true;//标记变量
				for (uint32_t j = 3; j <= _range; j += 10) {
					if (i%j == 0 || i % (j + 4) == 0 || i % (j + 6) == 0) {
						p = false;
						break;
					}
				}
				if (p) T.push_back(i);
				_1 = 1;//下一步为1
				i += 2;//跳2步
			}
			break;
			default://逻辑错误
				std::cerr << "error:finding prime logic is't normal!!!\n";
				exit(-1);
			}
		}
		//Tk-1取值判断
		{
			uint32_t _s = T.size();
			uint32_t _range = sqrt(number);
				for (uint32_t i = 0; i < _s; ++i) {
					if (T[i] > _range) break;
					if (number%T[i] == 0)
					{
						p = false;
						break;
					}
				}
			return p;
		}
	}
}
return false;
*/
//方法一 质因数分析法
bool p = true;//标记变量
if (number < 12) {//过滤掉特殊值11,有利于下面质因数分析执行
	if (number != 2 && number != 3 && number != 5 && number != 7&&number!=11)p = false;
	return p;
}
uint32_t _1 = number - number / 10 * 10;
if (_1 == 1 || _1 == 7 || _1 == 3 || _1 == 9) {//奇数 执行检测
	//质因数分析法求素数集合
	uint32_t _range = sqrt(number);
		for (uint32_t j = 3; j <= _range; j += 10) {
			if (number%j == 0 || number % (j + 6) == 0 || number % (j + 8) == 0||number%(j+4)==0) {
				p = false;
				break;
			}
		}
		return p;
}
return false;
};
/*
方法二 效率低下 O（number/6）
N0 = 4k1*k2＋2k1＋2k2＋1  奇合数公式
推 k2 = ((N0 - 1) / 2 - k1) / (2k1 + 1)
k2为整数
1 = < k1 < (N0 - 1) / 6 - 1 / 3
*/
static bool isPrime_Formula(const uint32_t & number) {
	bool p = true;
	if (number<10) {
		if (number != 2 && number != 3 && number != 5 && number != 7)p = false;
		return p;
	}
	uint32_t _1 = number - number / 10 * 10;
	if (_1 == 1 || _1 == 7 || _1 == 3 || _1 == 9) {//奇数 执行Tk-1检测
		uint32_t _mk1 = (double)(number - 1) / 6 - (double)1 / 3 + 1;
		for (int i = 1; i < _mk1; ++i) {
			double k2 = ((double)(number - 1) / 2 - i) / (2 * i + 1);
			if (k2 == (uint32_t)k2) {//奇合数
				p = false;
				break;
			}
		}
		return p;
	}
	return false;
}
#endif // !PRIME_H_H

