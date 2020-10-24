#ifndef DICTIONARY_H_H
#define DICTIONARY_H_H
/*
������ʵ䶨��
*/

	template<typename K, typename V>
	class Dictionary
	{
	public:
		//�ӿڶ���
		virtual int size()const = 0;
		virtual bool insert(K const&  key, V const&  value) = 0;
		virtual V* get(K const& key) = 0;
		virtual bool remove(K const& key) = 0;
	};

#endif // !DICTIONARY_H_H

