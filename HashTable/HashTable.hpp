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
		HashTable(uint32_t m);//创建一个容量(素数)不小于m的散列表
		~HashTable();
		int capacity()const;
		//词典接口
		 int size()const ;
		 bool insert(K const&  key, V const&  value);
		 V* get(K const& key) ;
		 bool remove(K const& key);
	protected:
		HashTable() = default;
		uint32_t map(const uint32_t&k)const;//调用接口映射函数 获取映射值 参数为myhash转化的关键码值
		uint32_t probe(const uint32_t&i,int j)const;//调用接口试探函数 获取下一个试探索引 参数为映射地址索引
		uint32_t probe1(const K&key);//线性平方搜索 查找匹配键的索引 不一定查找到
		uint32_t probe2(const K&key);//线性平方搜索 查找可插入的索引
		void rehash();//重散列，控制填充因子在50%一下
		void insert(Entry<K, V>*);//rehash时直接插入指针

		typedef uint32_t(*myHash)(const K&key); //关键码生成接口
		typedef uint32_t(*myMap)(const uint32_t&k,uint32_t m); //关键码映射接口 返回索引
		typedef uint32_t(*myProbe)(const uint32_t&i, uint32_t m,int j); //试探接口
	protected:
		Entry<K, V>**m_pBucArr;//桶数组
		uint32_t m_m;//容量m
		uint32_t m_n;//词条数n
		BitMap*m_pLazyRemovalMark;
	};

}

#include"HashTable.cpp"


#endif // !HASHTABLE_HPP_HPP

