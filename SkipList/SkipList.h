#ifndef SKIPLIST_H_H
#define SKIPLIST_H_H
/*
��ת��
*/

#include"Dictionary.h"
#include"QuadList.h"
#include"Entry.h"
#include<list>
#include<time.h>

namespace SKL {
	
	template<typename T>
	void Visit(T&e) {
		std::cout << "(" << e.key << "," << e.value << ") ";
	}


	template<typename K, typename V>
	class SkipList :public Dictionary<K, V>, public std::list <QuadList <Entry<K,V> >*>
	{
	public:
		typedef void(*Visit)(Entry<K,V>&);
		SkipList();
		~SkipList();

		int level()const;//���
		//�ʵ�ӿ�
		virtual int size()const;//bottom������
		virtual bool insert(K const& key, V const&  value);
		virtual V* get(K const& key);
		virtual bool remove(K const& key);
		template<typename Vst=Visit>
		void traversal(Vst visit=SKL::Visit);
	protected:
		SKL_OUTOFLINE bool skipSearch(int& adv, QQLN_OUT_(K, V)*&p, K &key);
	};

	template<typename K, typename V>
	SKL_OUTOFLINE SkipList<K, V>::SkipList()
	{
		srand((unsigned int)time(nullptr));//Ĭ�ϵ���ʱ����һ���������
	}

	template<typename K, typename V>
	SKL_OUTOFLINE SkipList<K, V>::~SkipList()
	{
		auto it = this->begin();
		auto end = this->end();
		while (it != end) {
			(*it)->clear();//�������������
			++it;
		}
		std::list <QuadList <Entry<K, V> >*>t;
		this->swap(t);//�������
	}

	template<typename K, typename V>
	SKL_OUTOFLINE int SkipList<K, V>::level() const
	{
		return std::list::size();
	}

	template<typename K, typename V>
	SKL_OUTOFLINE int SkipList<K, V>::size() const
	{
		return this->empty()?0:this->front()->size();//list��Ϊ���򷵻صײ�ȫ��������
	}

	template<typename K, typename V>
	SKL_OUTOFLINE bool SkipList<K, V>::insert(K const& key, V const& value)
	{
		Ey(K, V)e(key, value);
		if (this->empty())this->CallList(K,V)::insert(this->end(),new QuadList<Ey(K,V)>);//����ײ�
		List_QEIt(K, V)it = (--this->end());
		int adv = this->CallList(K, V)::size() - 1;
		QQLN_OUT_(K, V)* p = (*it)->first();//�����һ���ڵ㿪ʼ
		if (skipSearch(adv, p, RVarConst(K, key)))
			while (p->t_pBlow)p = p->t_pBlow;//��������ֵͬ��ת������
		//�½�һ������
		it = this->begin();//����
		QQLN_OUT_(K, V)*b = (*it)->insertAsSuccAbove(e, p);
		//srand((unsigned int)time(nullptr));//�����ڶ��ʹ�õĵط�ʹ��srand
		while (rand()&1)
		{
			while ((*it)->isValid(p)&&!p->t_pAbove) p=p->t_pPreced;//�Ҳ����ڵ�ǰ�߶ȵĵ�һ��ǰ����Ϊֱ��ǰ��
			if (!(*it)->isValid(p)) {//ֱ��ǰ��Ϊ���ڱ�
				if (it == --this->end()) {//��ǰ����Ϊ���
					this->CallList(K, V)::push_back(new QuadList <Entry<K, V> >);//�����µĶ���
}
				p = (*(++it))->first()->t_pPreced;//ת����һ������ڱ� ���½��ڵ��ֱ��ǰ�� ����һ��
			}
			else {
				p = p->t_pAbove;//�ڵ�����һ����Ϊֱ��ǰ��
				++it;//����һ��
			}
			b= (*it)->insertAsSuccAbove(e, p,b);//�����½ڵ�
		}
		return true;
	}

	template<typename K, typename V>
	SKL_OUTOFLINE V* SkipList<K, V>::get(K const & key)
	{
		if (this->empty())return nullptr;
		int adv = CallList(K, V)::size()-1;
		QQLN_OUT_(K,V)* p =(*(--this->end()))->first();//�����һ���ڵ㿪ʼ
		return   skipSearch(adv,p,RVarConst(K,key))?&(p->t_entry.value): nullptr;
	}

	template<typename K, typename V>
	SKL_OUTOFLINE bool SkipList<K, V>::remove(K const & key)
	{
		if (this->empty())return false;
		List_QEIt(K, V)it = (--this->end());
		int adv = this->CallList(K, V)::size() - 1;
		QQLN_OUT_(K, V)* p = (*it)->first();//�����һ���ڵ㿪ʼ
		if (!skipSearch(adv, p, RVarConst(K, key)))return false;//������
		it = (this->begin());
		std::advance(it, adv);//���²�μ�¼
		while (true) {
			QQLN_OUT_(K, V)*lower = p->t_pBlow;//��¼�±߽ڵ�
			(*it)->remove(p);//����������ɾ���ڵ�
			p = lower;//���½ڵ�λ��
			if (it == this->begin())break;
			--it;//����½�һ��
		}
		return true;
	}


	template<typename K, typename V>
	template<typename Vst>
	SKL_OUTOFLINE void SkipList<K, V>::traversal(Vst  visit)
	{
		if (this->empty())return;
		auto p = this->front();//�ײ�
		p->traversal(visit);//�������ȫ������
	}


	template<typename K, typename V>
	SKL_OUTOFLINE bool SkipList<K, V>::skipSearch(int& adv, QQLN_OUT_(K, V)*&p, K &key)
	{
		List_QEIt(K, V) it = this->begin(); 
		std::advance(it, adv);
		while (true)
		{
			while (p->t_pSucced&&p->t_entry.key <= key)
				p = p->t_pSucced;
			p = p->t_pPreced;
			if (p->t_pPreced&&p->t_entry.key == key)return true;
			if (it == this->begin())return false;
			--it;
			--adv;
			p = p->t_pPreced ? p->t_pBlow : (*it)->first();
		}
	}


};

#endif // !SKIPLIST_H_H


