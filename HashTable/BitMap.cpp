#include "BitMap.h"

namespace BM {
	//无符号版本


	BitMap::BitMap(int n)
	{
		this->m_n = n;
		std::vector<unsigned long long >nvec(m_n, 0);
		m_bitSet.swap(nvec);//重置为0
	}

	BitMap::~BitMap()
	{
	}

	void BitMap::reset()
	{
		std::vector<unsigned long long >nvec(m_n, 0);
		m_bitSet.swap(nvec);//重置为0
	}

	bool BitMap::set(unsigned long long k)
	{
		int index = k >> 6; //数组索引
		if (index >= m_bitSet.size())return false;
		m_bitSet[index] = (m_bitSet[index] | (unsigned long long)1 << (k << 58 >> 58));//重赋值
		return true;
	}

	void BitMap::clear(unsigned long  long k)
	{
		int index = k >> 6; //数组索引
		if (index >= m_bitSet.size())return;
		if (test(k))
			m_bitSet[index] = m_bitSet[index] ^ (unsigned long long)1 << (k << 58 >> 58);//重赋值
	}

	bool BitMap::test(unsigned long long  k)
	{
		int index = k >> 6;
		return   index < m_bitSet.size() && (m_bitSet[index] & (unsigned long long)1 << (k << 58 >> 58));
	}

	void BitMap::resize(int n)
	{
		this->m_n = n;
		m_bitSet.resize(n);
		m_bitSet.reserve(n);
	}

	/*
	---------------------------------------------------------------------------------------------
	*/

	//有符号版本


	SBitMap::SBitMap(int n)
	{
		this->m_n = n;
		this->m_bitSet.resize(n);
		m_nBitSet = new BitMap(n);//负数集合
	}

	SBitMap::~SBitMap()
	{
		delete m_nBitSet, m_nBitSet = nullptr;
	}

	void SBitMap::reset()
	{
		this->BitMap::reset();//转基类调用
		m_nBitSet->reset();
	}

	bool SBitMap::set(long long k)
	{
		if (k >> 63 & 1) {//标记负数数 这里用位操作来判定正负，使其操作为O（1）
			return m_nBitSet->set((-k));//注：尽管~k操作也是O（1） 但+1操作不稳定且慢许多
		}
		else {
			return this->BitMap::set(k);
		}
		return true;
	}

	void SBitMap::clear(long long k)
	{
		if (k >> 63 & 1) {//标记负数数 这里用位操作来判定正负，使其操作为O（1）
			m_nBitSet->clear((-k));//注：尽管~k操作也是O（1） 但+1操作不稳定且慢许多
		}
		else {
			this->BitMap::clear(k);
		}
	}

	bool SBitMap::test(long long k)
	{
		if (k >> 63 & 1) {//标记负数数 这里用位操作来判定正负，使其操作为O（1）
			return m_nBitSet->test((-k));//注：尽管~k操作也是O（1） 但+1操作不稳定且慢许多
		}
		else {
			return this->BitMap::test(k);
		}
	}

	void SBitMap::resize(int n)
	{
		this->BitMap::resize(n);
		m_nBitSet->resize(n);
	}
}