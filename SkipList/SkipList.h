#ifndef SKIPLIST_H_H
#define SKIPLIST_H_H
/*
跳转表
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

		int level()const;//层高
		//词典接口
		virtual int size()const;//bottom词条数
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
		srand((unsigned int)time(nullptr));//默认调用时设置一个随机数列
	}

	template<typename K, typename V>
	SKL_OUTOFLINE SkipList<K, V>::~SkipList()
	{
		auto it = this->begin();
		auto end = this->end();
		while (it != end) {
			(*it)->clear();//清除各层四联表
			++it;
		}
		std::list <QuadList <Entry<K, V> >*>t;
		this->swap(t);//清空所有
	}

	template<typename K, typename V>
	SKL_OUTOFLINE int SkipList<K, V>::level() const
	{
		return std::list::size();
	}

	template<typename K, typename V>
	SKL_OUTOFLINE int SkipList<K, V>::size() const
	{
		return this->empty()?0:this->front()->size();//list不为空则返回底层全部词条数
	}

	template<typename K, typename V>
	SKL_OUTOFLINE bool SkipList<K, V>::insert(K const& key, V const& value)
	{
		Ey(K, V)e(key, value);
		if (this->empty())this->CallList(K,V)::insert(this->end(),new QuadList<Ey(K,V)>);//插入底层
		List_QEIt(K, V)it = (--this->end());
		int adv = this->CallList(K, V)::size() - 1;
		QQLN_OUT_(K, V)* p = (*it)->first();//顶层第一个节点开始
		if (skipSearch(adv, p, RVarConst(K, key)))
			while (p->t_pBlow)p = p->t_pBlow;//如已有雷同值，转到塔底
		//新建一座新塔
		it = this->begin();//塔底
		QQLN_OUT_(K, V)*b = (*it)->insertAsSuccAbove(e, p);
		//srand((unsigned int)time(nullptr));//不能在多次使用的地方使用srand
		while (rand()&1)
		{
			while ((*it)->isValid(p)&&!p->t_pAbove) p=p->t_pPreced;//找不低于当前高度的第一个前驱作为直接前驱
			if (!(*it)->isValid(p)) {//直接前驱为首哨兵
				if (it == --this->end()) {//当前塔高为最高
					this->CallList(K, V)::push_back(new QuadList <Entry<K, V> >);//创建新的顶层
}
				p = (*(++it))->first()->t_pPreced;//转到上一层的首哨兵 即新建节点的直接前驱 上升一层
			}
			else {
				p = p->t_pAbove;//节点上升一层作为直接前驱
				++it;//上升一层
			}
			b= (*it)->insertAsSuccAbove(e, p,b);//建立新节点
		}
		return true;
	}

	template<typename K, typename V>
	SKL_OUTOFLINE V* SkipList<K, V>::get(K const & key)
	{
		if (this->empty())return nullptr;
		int adv = CallList(K, V)::size()-1;
		QQLN_OUT_(K,V)* p =(*(--this->end()))->first();//顶层第一个节点开始
		return   skipSearch(adv,p,RVarConst(K,key))?&(p->t_entry.value): nullptr;
	}

	template<typename K, typename V>
	SKL_OUTOFLINE bool SkipList<K, V>::remove(K const & key)
	{
		if (this->empty())return false;
		List_QEIt(K, V)it = (--this->end());
		int adv = this->CallList(K, V)::size() - 1;
		QQLN_OUT_(K, V)* p = (*it)->first();//顶层第一个节点开始
		if (!skipSearch(adv, p, RVarConst(K, key)))return false;//不存在
		it = (this->begin());
		std::advance(it, adv);//更新层次记录
		while (true) {
			QQLN_OUT_(K, V)*lower = p->t_pBlow;//记录下边节点
			(*it)->remove(p);//在四联表中删除节点
			p = lower;//更新节点位置
			if (it == this->begin())break;
			--it;//层次下降一层
		}
		return true;
	}


	template<typename K, typename V>
	template<typename Vst>
	SKL_OUTOFLINE void SkipList<K, V>::traversal(Vst  visit)
	{
		if (this->empty())return;
		auto p = this->front();//底层
		p->traversal(visit);//有序遍历全部数据
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


