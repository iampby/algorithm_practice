#ifndef HASHTABLE_HPP_HPP
#define HASHTABLE_HPP_HPP

#include<iostream>
#include"Dictionary.h"
#include"Entry.h"
#include"BitMap.h"

namespace HT {
	using namespace BM;
	template<typename K,typename V>
	class HashTable:public Dictionary<K,V>
	{
	public:
		HashTable(uint32_t m);//����һ������(����)��С��m��ɢ�б�
		~HashTable();
		int capacity()const;
		//�ʵ�ӿ�
		 int size()const ;
		 bool insert(K const&  key, V const&  value);
		 V* get(K const& key) ;
		 bool remove(K const& key);
	protected:
		HashTable() = default;
		uint32_t map(const uint32_t&k)const;//���ýӿ�ӳ�亯�� ��ȡӳ��ֵ ����Ϊmyhashת���Ĺؼ���ֵ
		uint32_t probe(const uint32_t&i,int j)const;//���ýӿ���̽���� ��ȡ��һ����̽���� ����Ϊӳ���ַ����
		uint32_t probe1(const K&key);//����ƽ������ ����ƥ��������� ��һ�����ҵ�
		uint32_t probe2(const K&key);//����ƽ������ ���ҿɲ��������
		void rehash();//��ɢ�У��������������50%һ��
		void insert(Entry<K, V>*);//rehashʱֱ�Ӳ���ָ��

		typedef uint32_t(*myHash)(const K&key); //�ؼ������ɽӿ�
		typedef uint32_t(*myMap)(const uint32_t&k,uint32_t m); //�ؼ���ӳ��ӿ� ��������
		typedef uint32_t(*myProbe)(const uint32_t&i, uint32_t m,int j); //��̽�ӿ�
	protected:
		Entry<K, V>**m_pBucArr;//Ͱ����
		uint32_t m_m;//����m
		uint32_t m_n;//������n
		BitMap*m_pLazyRemovalMark;
	};

}

#include"HashTable.cpp"


#endif // !HASHTABLE_HPP_HPP

