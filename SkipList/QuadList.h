#ifndef QUADLIST_H_H
#define QUADLIST_H_H

/*
四联表
*/

#include"D_macro.h"

namespace SKL {

	template<typename T>
	class QuadList
	{
	public:
		//节点
		struct QuaListNode
		{
			T t_entry;//词条
			//四个方向节点
			QLN t_pPreced, *t_pSucced;
			QLN t_pAbove, *t_pBlow;
			QuaListNode(T e = T(), QLN p = nullptr, QLN s = nullptr, QLN a = nullptr, QLN b = nullptr);
	
			QLN insertAsSuccAbove(T const&e, QLN b = nullptr);
		};
		QuadList();
		~QuadList();

		int clear();//清空内容
		int size()const;
		bool empty()const;
		bool isValid(QLN) const;
		QLN first() const;
		QLN last() const;
		QLN insertAsSuccAbove(T const &e, QLN p, QLN b = nullptr);
		T remove(QLN p); //删除（合法）位置p处的节点，返回被删除节点的数值
		 template <typename VST> //遍历QuaList，对各节点依次实施visit操作
		 void  traversal(VST& visit);//利用函数对象机制，可全局性修改
			
	private:
		int m_size; QLN m_pHeader; QLN m_pTrailer;//规模 头尾哨兵
	};

	template<typename T>
	inline QuadList<T>::QuaListNode::QuaListNode(T e, QLN p, QLN s, QLN a, QLN b) :
		t_entry(e), t_pPreced(p), t_pSucced(s), t_pAbove(a), t_pBlow(b) {}



	template<typename T>
	inline QQLN_OUT(T)* QuadList<T>::QuaListNode::insertAsSuccAbove(T const&e, QLN b)
	{
		QQLN_OUT(T)*x = new QQLN_OUT(T)(e, this, t_pSucced, nullptr, b);
		t_pSucced->t_pPreced = x; t_pSucced = x;//水平联接
		if (b) {
			b->t_pAbove = x;//垂直联接
		}
		return x;//返回新节点
	};


template<typename T>
	SKL_OUTOFLINE QuadList<T>::QuadList()
	{
		m_pHeader = new QuaListNode();
		m_pTrailer = new QuaListNode();
		m_pHeader->t_pSucced = m_pTrailer; m_pHeader->t_pPreced = nullptr;
		m_pTrailer->t_pPreced = m_pHeader; m_pTrailer->t_pSucced = nullptr;
		m_pHeader->t_pAbove = nullptr; m_pHeader->t_pBlow = nullptr;
		m_pTrailer->t_pAbove = nullptr; m_pTrailer->t_pBlow = nullptr;
		m_size = 0;
	}

	template<typename T>
	SKL_OUTOFLINE QuadList<T>::~QuadList()
	{
		clear(); 
		delete m_pHeader, m_pHeader = nullptr; delete m_pTrailer, m_pTrailer = nullptr;
	}
	
	template<typename T>
	SKL_OUTOFLINE int QuadList<T>::clear()
	{
		int oldSize = m_size;
		while (0 < m_size)remove(m_pHeader->t_pSucced); //逐个删除所有节点
		return oldSize;
	}

	template<typename T>
	SKL_OUTOFLINE int QuadList<T>::size() const
	{
		return m_size;
	}

	template<typename T>
	SKL_OUTOFLINE bool QuadList<T>::empty() const
	{
		return m_size < 1;
	}

	template<typename T>
	SKL_OUTOFLINE QQLN_OUT(T)* QuadList<T>::first() const
	{
		return m_pHeader->t_pSucced;
	}

	template<typename T>
	SKL_OUTOFLINE QQLN_OUT(T)* QuadList<T>::last() const
	{
		return m_pTrailer->t_pPreced;
	}

	template<typename T>
	SKL_OUTOFLINE T QuadList<T>::remove(QQLN_OUT(T)*p)
	{
		QLN t_pPreced, *t_pSucced;
		QLN t_pAbove, *t_pBlow;
		p->t_pPreced->t_pSucced = p->t_pSucced; p->t_pSucced->t_pPreced = p->t_pPreced;//水平联接
		//if (p->t_pAbove)p->t_pAbove->t_pBlow = p->t_pBlow; if (p->t_pBlow)p->t_pBlow->t_pAbove = p->t_pAbove;//垂直联接
		T e = p->t_entry; delete p, p = nullptr; --m_size;
		return e;
	}

	template<typename T>
	SKL_OUTOFLINE QQLN_OUT(T)* QuadList<T>::insertAsSuccAbove(T const & e, QQLN_OUT(T)* p, QQLN_OUT(T)* b)
	{
		++this->m_size; return p->insertAsSuccAbove(e,b);
	}

	template<typename T>
	SKL_OUTOFLINE bool QuadList<T>::isValid(QLN p) const
	{
		return (p&&m_pTrailer != p && m_pHeader != p);
	}
	
	template<typename T>
	template<typename VST>
	inline void QuadList<T>::traversal(VST & visit)
	{ 
		QLN p = m_pHeader;
		while ((p = p->t_pSucced) != m_pTrailer) visit(p->t_entry);
	}

};

#endif // !QUADLIST_H_H
