#ifndef QUADLIST_H_H
#define QUADLIST_H_H

/*
������
*/

#include"D_macro.h"

namespace SKL {

	template<typename T>
	class QuadList
	{
	public:
		//�ڵ�
		struct QuaListNode
		{
			T t_entry;//����
			//�ĸ�����ڵ�
			QLN t_pPreced, *t_pSucced;
			QLN t_pAbove, *t_pBlow;
			QuaListNode(T e = T(), QLN p = nullptr, QLN s = nullptr, QLN a = nullptr, QLN b = nullptr);
	
			QLN insertAsSuccAbove(T const&e, QLN b = nullptr);
		};
		QuadList();
		~QuadList();

		int clear();//�������
		int size()const;
		bool empty()const;
		bool isValid(QLN) const;
		QLN first() const;
		QLN last() const;
		QLN insertAsSuccAbove(T const &e, QLN p, QLN b = nullptr);
		T remove(QLN p); //ɾ�����Ϸ���λ��p���Ľڵ㣬���ر�ɾ���ڵ����ֵ
		 template <typename VST> //����QuaList���Ը��ڵ�����ʵʩvisit����
		 void  traversal(VST& visit);//���ú���������ƣ���ȫ�����޸�
			
	private:
		int m_size; QLN m_pHeader; QLN m_pTrailer;//��ģ ͷβ�ڱ�
	};

	template<typename T>
	inline QuadList<T>::QuaListNode::QuaListNode(T e, QLN p, QLN s, QLN a, QLN b) :
		t_entry(e), t_pPreced(p), t_pSucced(s), t_pAbove(a), t_pBlow(b) {}



	template<typename T>
	inline QQLN_OUT(T)* QuadList<T>::QuaListNode::insertAsSuccAbove(T const&e, QLN b)
	{
		QQLN_OUT(T)*x = new QQLN_OUT(T)(e, this, t_pSucced, nullptr, b);
		t_pSucced->t_pPreced = x; t_pSucced = x;//ˮƽ����
		if (b) {
			b->t_pAbove = x;//��ֱ����
		}
		return x;//�����½ڵ�
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
		while (0 < m_size)remove(m_pHeader->t_pSucced); //���ɾ�����нڵ�
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
		p->t_pPreced->t_pSucced = p->t_pSucced; p->t_pSucced->t_pPreced = p->t_pPreced;//ˮƽ����
		//if (p->t_pAbove)p->t_pAbove->t_pBlow = p->t_pBlow; if (p->t_pBlow)p->t_pBlow->t_pAbove = p->t_pAbove;//��ֱ����
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
