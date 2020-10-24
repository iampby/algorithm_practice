#include "BitMap.h"

namespace BM {
	//�޷��Ű汾


	BitMap::BitMap(int n)
	{
		this->m_n = n;
		std::vector<unsigned long long >nvec(m_n, 0);
		m_bitSet.swap(nvec);//����Ϊ0
	}

	BitMap::~BitMap()
	{
	}

	void BitMap::reset()
	{
		std::vector<unsigned long long >nvec(m_n, 0);
		m_bitSet.swap(nvec);//����Ϊ0
	}

	bool BitMap::set(unsigned long long k)
	{
		int index = k >> 6; //��������
		if (index >= m_bitSet.size())return false;
		m_bitSet[index] = (m_bitSet[index] | (unsigned long long)1 << (k << 58 >> 58));//�ظ�ֵ
		return true;
	}

	void BitMap::clear(unsigned long  long k)
	{
		int index = k >> 6; //��������
		if (index >= m_bitSet.size())return;
		if (test(k))
			m_bitSet[index] = m_bitSet[index] ^ (unsigned long long)1 << (k << 58 >> 58);//�ظ�ֵ
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

	//�з��Ű汾


	SBitMap::SBitMap(int n)
	{
		this->m_n = n;
		this->m_bitSet.resize(n);
		m_nBitSet = new BitMap(n);//��������
	}

	SBitMap::~SBitMap()
	{
		delete m_nBitSet, m_nBitSet = nullptr;
	}

	void SBitMap::reset()
	{
		this->BitMap::reset();//ת�������
		m_nBitSet->reset();
	}

	bool SBitMap::set(long long k)
	{
		if (k >> 63 & 1) {//��Ǹ����� ������λ�������ж�������ʹ�����ΪO��1��
			return m_nBitSet->set((-k));//ע������~k����Ҳ��O��1�� ��+1�������ȶ��������
		}
		else {
			return this->BitMap::set(k);
		}
		return true;
	}

	void SBitMap::clear(long long k)
	{
		if (k >> 63 & 1) {//��Ǹ����� ������λ�������ж�������ʹ�����ΪO��1��
			m_nBitSet->clear((-k));//ע������~k����Ҳ��O��1�� ��+1�������ȶ��������
		}
		else {
			this->BitMap::clear(k);
		}
	}

	bool SBitMap::test(long long k)
	{
		if (k >> 63 & 1) {//��Ǹ����� ������λ�������ж�������ʹ�����ΪO��1��
			return m_nBitSet->test((-k));//ע������~k����Ҳ��O��1�� ��+1�������ȶ��������
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