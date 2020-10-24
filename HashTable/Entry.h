#ifndef ENTRY_H_H
#define ENTRY_H_H
/*
��ֵ�Դ���
*/

namespace HT {
	template <typename K, typename V> struct Entry { //����ģ����
		K key; V value; //�ؼ��롢��ֵ
		Entry(K k = K(), V v = V()) : key(k), value(v) {}; //Ĭ�Ϲ��캯��
		Entry(Entry<K, V> const& e) : key(e.key), value(e.value) {}; //���ڿ�¡�Ĺ��캯��
		bool operator< (Entry<K, V> const& e) { return key < e.key; }  //�Ƚ�����С��
		bool operator> (Entry<K, V> const& e) { return key > e.key; }  //�Ƚ���������
		bool operator== (Entry<K, V> const& e) { return key == e.key; } //�е���������
		bool operator!= (Entry<K, V> const& e) { return key != e.key; } //�е�����������
	}; //�����ڱȽ������е������Ӵ����󣬲����ϸ����ִ��������Ӧ�Ĺؼ���
}

#endif // !ENTRY_H_H