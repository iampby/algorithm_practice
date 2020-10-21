#ifndef BITMAP_H_H
#define BITMAP_H_H
/*
λͼʵ�֣�2���汾����һ����64λ���޷�����������һ���Ա����з��ţ�Ƕ��һ��λͼ��
*/
//�޷��Ű汾
#include<vector>
class BitMap 
{ 
public:
	explicit BitMap(int n);//ָ�����ݱ��淶Χ��+n*64
	~BitMap();
 // �ӿ�
	 void reset();
	 bool set(unsigned long  long k);
	 void clear(unsigned long  long k);
	 bool test(unsigned long  long k);
	 void resize(int n);
protected:
	BitMap() = default;//�ɼ̳б��
protected:
	std::vector<unsigned long long > m_bitSet;//�ö�άָ�뱣�����ݼ���
	int m_n;//�����ģ
};

/*
---------------------------------------------------------------------------------------------
*/

//�з��Ű汾
class SBitMap :public BitMap
{
public:
	explicit SBitMap(int n );//ָ�����ݱ��淶Χ��+-n*64
	~SBitMap();
	//�ӿ�
	 void reset();
	 bool set(long long k);
	void clear(long long k);
	  bool test(long long k);
	  void resize(int n);
protected:
	SBitMap() = default;//�ɼ̳б��
protected:
	BitMap* m_nBitSet;//���޷���λͼ������� ע��������Ա����������ʹ�� ������ָ������
};

#endif // !BITMAP_H_H

