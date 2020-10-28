#ifndef PQ_COMPLETEHEAP_CPP_CPP
#define PQ_COMPLETEHEAP_CPP_CPP

#include "PQ_CompleteHeap.hpp"

template<typename T, typename _Comparer>
PQ_OUTOFLINE PQ_CompleteHeap<T, _Comparer>::PQ_CompleteHeap()
{
}

template<typename T, typename _Comparer>
PQ_OUTOFLINE PQ_CompleteHeap<T, _Comparer>::PQ_CompleteHeap(std::vector<T>&& set)
{
	*dynamic_cast<std::vector<T>*>(this) =std::move(set);
	heapify();
}

template<typename T, typename _Comparer>
 void PQ_CompleteHeap<T, _Comparer>::push(T const & e)
{
	 this->vector<T>::insert(this->vector<T>::end(), e);
	 percolateUp(size()-1);//上滤调整
}

template<typename T, typename _Comparer>
const T & PQ_CompleteHeap<T, _Comparer>::top()
{
	return (*this)[0];
}

template<typename T, typename _Comparer>
void PQ_CompleteHeap<T, _Comparer>::pop()
{
	(*this)[0] = (*this)[this->size() - 1];
	this->vector<T>::erase(--this->vector<T>::end());
	percolateDown(0);
}

template<typename T, typename _Comparer>
PQ_OUTOFLINE int PQ_CompleteHeap<T, _Comparer>::size() const
{
	return this->vector<T>::size();
}


template<typename T, typename _Comparer>
PQ_OUTOFLINE int PQ_CompleteHeap<T, _Comparer>::left(int i) const
{
	return 1+(i<<1);
}

template<typename T, typename _Comparer>
PQ_OUTOFLINE int PQ_CompleteHeap<T, _Comparer>::right(int i) const
{
	return 2+(i<<1);
}

template<typename T, typename _Comparer>
PQ_OUTOFLINE int PQ_CompleteHeap<T, _Comparer>::parent(int i) const
{
	return ((i-1)>>1);
}

template<typename T, typename _Comparer>
PQ_OUTOFLINE bool PQ_CompleteHeap<T, _Comparer>::hasParent(int i) const
{
	return i>0;
}

template<typename T, typename _Comparer>
PQ_OUTOFLINE bool PQ_CompleteHeap<T, _Comparer>::isVaildIndex(int i) const
{
	return i>-1&&i<size();
}

template<typename T, typename _Comparer>
PQ_OUTOFLINE void PQ_CompleteHeap<T, _Comparer>::percolateDown( int i)
{
	while (isVaildIndex(left(i)))
	{
		if (isVaildIndex(right(i))) {
			T&_l = (*this)[left(i)];
			T&_r = (*this)[right(i)];
			if (!f_comparer(_l, _r)) {
               if (!f_comparer(_l, (*this)[i])) {
					std::swap(_l, (*this)[i]);
						i = left(i);
				}
				else break;
			}
			else {
				if (!f_comparer(_r, (*this)[i])) {
					std::swap(_r, (*this)[i]);
						i = right(i);
				}
				else break;
			}
		}
		else {
			T&_l = (*this)[left(i)];
			if (!f_comparer(_l, (*this)[i])) {
				std::swap(_l, (*this)[i]);
				i = left(i);
			}
			else break;
		}
	}
}

template<typename T, typename _Comparer>
PQ_OUTOFLINE void PQ_CompleteHeap<T, _Comparer>::percolateUp(int i)
{
	while (hasParent(i))//上滤到根
	{
		T&p =(*this)[parent(i)];
		T&v = (*this)[i];
		if (!f_comparer(v, p)) {
			std::swap(p, v);
			i = parent(i);
		}
		else
			break;
	}
}

template<typename T, typename _Comparer>
PQ_OUTOFLINE void PQ_CompleteHeap<T, _Comparer>::heapify()
{
	for (int i = parent(size() - 1); i >= 0; --i) {
		percolateDown(i);
	}
}

#endif // !PQ_COMPLETEHEAP_CPP_CPP
