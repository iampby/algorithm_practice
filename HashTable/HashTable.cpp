#ifndef HASHTABLE_CPP_CPP
#define HASHTABLE_CPP_CPP
#include"HashTable.hpp"
#include"Prime.h"

namespace HT {
	template<typename K, typename V>
	inline HashTable<K, V>::HashTable(uint32_t m)
	{
		m = m | 1;//奇数
		while (!isPrime(m))
		{
			m += 2;
		}
		this->m_m = m;
		m_n = 0;
		m_pBucArr = new Entry<K, V>*[m_m];//桶数组
		memset(m_pBucArr, 0, sizeof(Entry<K, V>*)*m_m);//初始化为空指针
		m_pLazyRemovalMark = new BitMap(m_m);
	}
	template<typename K, typename V>
	inline HashTable<K, V>::~HashTable()
	{
		for (uint32_t i = 0; i < m_m; ++i) {
			delete m_pBucArr[i];
		}
		delete[]m_pBucArr,m_pBucArr=nullptr;
		delete m_pLazyRemovalMark, m_pLazyRemovalMark = nullptr;
	}

	template<typename K, typename V>
	int HashTable<K, V>::capacity() const
	{
		return m_m;
	}
	
	template<typename K, typename V>
	 int HashTable<K, V>::size() const
	{
		return this->m_n;
	}
	 template<typename K, typename V>
	 bool HashTable<K, V>::insert(K const & key, V const & value)
	 {
		 uint32_t r = probe1(key);
		 if (m_pBucArr[r])return false;
		 r = probe2(key);
		 m_pBucArr[r] = new Entry<K, V>(key, value);
		 ++m_n;
		 if (m_n * 2 > m_m)rehash();
		 return true;
	 }
	 template<typename K, typename V>
	 V * HashTable<K, V>::get(K const & key)
	 {
		 uint32_t r = probe1(key);
		 return m_pBucArr[r] ? &(m_pBucArr[r]->value) : nullptr;
	 }
	 template<typename K, typename V>
	 bool HashTable<K, V>::remove(K const & key)
	 {
		 uint32_t r = probe1(key);
		 if (!m_pBucArr[r])return false;
		 delete m_pBucArr[r], m_pBucArr[r] = nullptr;
		 --m_n;
		 m_pLazyRemovalMark->set(r);
		 return true;
	 }
	 template<typename K, typename V>
	 inline uint32_t HashTable<K, V>::map(const uint32_t&k) const
	 {
		 myMap fm = ::myMap;
		 return fm(k, this->m_m);//返回映射值
	 }
	 template<typename K, typename V>
	 inline uint32_t HashTable<K, V>::probe(const uint32_t & i,int j) const
	 {
		 myProbe mp = ::myProbe;
		 return mp(i,m_m,j);//获取下一个试探映射值
	 }
	 
	 template<typename K, typename V>
	 inline uint32_t HashTable<K, V>::probe1(const K & key)
	 {
		 myHash mh = ::myHash;
		 uint32_t r = map(mh(key));
		 int j = 0;
		 while ((m_pBucArr[r]&&m_pBucArr[r]->key!=key||(!m_pBucArr[r]&&m_pLazyRemovalMark->test(r))))
		 {
			
			 r = probe(r,++j);
		}
		 return r;
	 }
	 template<typename K, typename V>
	 inline uint32_t HashTable<K, V>::probe2(const K& key)
	 {
		 myHash mh = ::myHash;
		 uint32_t r = map(mh(key));
		 int j = 0;
		 while (m_pBucArr[r])
		 {
			 r = probe(r,++j);
		 }
		 return r;
	 }
	 template<typename K, typename V>
	 inline void HashTable<K, V>::rehash()
	 {
		 Entry<K, V>**old = m_pBucArr;
		 int old_m = m_m;
		 m_m = (m_m * 2)|1;//至少2倍扩容
		 m_n = 0; 
		 while (!isPrime(m_m))
		 {
			 m_m += 2;
		 }
		 delete m_pLazyRemovalMark;
		 m_pLazyRemovalMark = new BitMap(m_m);
		 m_pBucArr = new Entry<K, V>*[m_m];//2倍扩容
		 memset(m_pBucArr, 0, sizeof(Entry<K, V>*)*m_m);//初始化为空
		 for (uint32_t i = 0; i < old_m; ++i) {
			 if (old[i]) {
				 insert(old[i]);//转移内容
			 }
		 }
		 delete[] old;//释放数组内存
	 }
	 template<typename K, typename V>
	 void HashTable<K, V>::insert(Entry<K, V>*e)
	 {
		 uint32_t r = probe2(e->key);
		 m_pBucArr[r] = e;
		 ++m_n;
	 }
}


#endif //!HASHTABLE_CPP_CPP