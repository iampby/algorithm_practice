#ifndef BITMAP_H_H
#define BITMAP_H_H
/*
位图实现：2个版本，其一可以64位的无符号整数，另一可以保存有符号（嵌套一个位图）
*/
//无符号版本
#include<vector>
class BitMap 
{ 
public:
	explicit BitMap(int n);//指定数据保存范围：+n*64
	~BitMap();
 // 接口
	 void reset();
	 bool set(unsigned long  long k);
	 void clear(unsigned long  long k);
	 bool test(unsigned long  long k);
	 void resize(int n);
protected:
	BitMap() = default;//可继承标记
protected:
	std::vector<unsigned long long > m_bitSet;//用二维指针保存数据集合
	int m_n;//数组规模
};

/*
---------------------------------------------------------------------------------------------
*/

//有符号版本
class SBitMap :public BitMap
{
public:
	explicit SBitMap(int n );//指定数据保存范围：+-n*64
	~SBitMap();
	//接口
	 void reset();
	 bool set(long long k);
	void clear(long long k);
	  bool test(long long k);
	  void resize(int n);
protected:
	SBitMap() = default;//可继承标记
protected:
	BitMap* m_nBitSet;//用无符号位图保存符号 注：保护成员不能在类外使用 这里用指针跳过
};

#endif // !BITMAP_H_H

