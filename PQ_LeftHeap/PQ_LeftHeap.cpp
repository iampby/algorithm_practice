#ifndef PQ_LEFTHEAP_CPP_CPP
#define PQ_LEFTHEAP_CPP_CPP

#include<queue>
#include "PQ_LeftHeap.hpp"

template<typename T, typename _Comparer>
TREE_OUTOFLINE PQ_LeftHeap<T, _Comparer>::PQ_LeftHeap()
{
}

template<typename T, typename _Comparer>
PQ_LeftHeap<T, _Comparer>::PQ_LeftHeap(std::vector<T>&&set)
{
	if (set.empty())return;
	this->m_root= heapify(set);//������ȫ����� ���ֶ���
  this->m_size += set.size();//���¹�ģ
	std::vector<T>_rs; _rs.swap(set);//��ʧ����
}

template<typename T, typename _Comparer>
PQ_LeftHeap<T, _Comparer>::PQ_LeftHeap(std::vector<T>&set)
{
	int _s = set.size();
	for (int i = 0; i < _s; ++i) {
		push(set[i]);
	}
}

template<typename T, typename _Comparer>
PQ_LeftHeap<T, _Comparer>::~PQ_LeftHeap()
{
}

template<typename T, typename _Comparer>
void PQ_LeftHeap<T, _Comparer>::push(T const &e)
{
	BTN::BNP(T)_right = new BTN::BinTreeNode<T>(e);//�Ҷѽ���
	this->m_root = PQ_LeftHeap<T, _Comparer>::merge(this->m_root, _right);//��������
	++this->m_size;//���¹�ģ
}

template<typename T, typename _Comparer>
 const T & PQ_LeftHeap<T, _Comparer>::top()
{
	 return this->m_root->data;
}

template<typename T, typename _Comparer>
 void PQ_LeftHeap<T, _Comparer>::pop()
{
	 BTN::BNP(T)_top = this->m_root;
	 BTN::BNP(T)_left = _top->left; BTN::BNP(T)_right = _top->right;
	 delete _top, _top = nullptr;
	 this->m_root = PQ_LeftHeap<T, _Comparer>::merge(_left, _right);//��������
	 --this->m_size;//���¹�ģ
}

 template<typename T, typename _Comparer>
 int PQ_LeftHeap<T, _Comparer>::NPL() const
 {
	 return PQ_LeftHeap<T, _Comparer>::NPL(this->m_root);
 }

 template<typename T, typename _Comparer>
 BTN::BNP(T) PQ_LeftHeap<T, _Comparer>::merge(BTN::BNP(T) a, BTN::BNP(T) b)
 {
	 if (!b)return a;
	 if (!a)return b;
	 _Comparer f_comparer;
	 BTN::BNP(T) _left = a;
     BTN::BNP(T) _right = b;//Ҫ�ϲ������ҶѸ��ڵ��ʼ��
	 BTN::BNP(T)_last = nullptr;//��¼���һ�����ڸ���npl
	 //��֤����
	 if (f_comparer(_left->data, _right->data)) {
		 std::swap(_left, _right);//��֤��ϲ���ʱ��֤����
	 }
	 _last = _right;
	 BTN::BNP(T) r = _left;
	 if (!_left->left) {
		 _left->left = _right;
		 _right->parent = _left;
		 goto end;
	 }
	 else if (!_left->right) {
		 _left->right = _right;
		 _right->parent = _left;
		 goto end;
	 }
  _left = _left->right;
	 while (true)
	 {
		 if (f_comparer(_left->data, _right->data)) {
			 BTN::BNP(T)_rc = _left;
			 std::swap(_left, _right);//��֤��ϲ���ʱ��֤����
			 _rc->parent->right = _left;//ȡ���ҶѴ�ֵ���½���
			 _left->parent = _rc->parent;//��������
			}
		 _last = _right;
		if (!_left->left) {
			_left->left = _right;
			_right->parent = _left;
			goto end;
		}
		else if (!_left->right) {
			_left->right = _right;
			_right->parent = _left;
			goto end;
		}
		_left = _left->right;
	 }
 end: 
	 //����npl����֤������
	 PQ_LeftHeap<T, _Comparer>::updateNPL(_last);
	 _last = _last->parent;
	 {
		 while (_last!=r)
		 {
			 if (NPL(_last->left) < NPL(_last->right)) {
				 std::swap(_last->left, _last->right);
			}
			 PQ_LeftHeap<T, _Comparer>::updateNPL(_last);
			 _last = _last->parent;
		 }
		 PQ_LeftHeap<T, _Comparer>::updateNPL(r);
	 return r;
	 }
 }


 template<typename T, typename _Comparer>
 BTN::BNP(T) PQ_LeftHeap<T, _Comparer>::heapify(std::vector<T>&set)
 {
	 //���õ�����lambda
	 std::vector<BTN::BNP(T)>heap(set.size(),nullptr);//��ʼ����ȫ�����Ϊnull
	 int _s = set.size();
	 auto percolateDown = [&](int i) {
		 int _il = (i << 1) + 1, _ir = (i << 1) + 2;
	do{
		BTN::BNP(T)&_left = heap[_il];//����
				 BTN::BNP(T)&_right = heap[_ir];//�Һ���
				 if (!f_comparer(_left->data, _right->data)) {
					 if (!f_comparer(_left->data, heap[i]->data)) {
						std::swap(_left->data,heap[i]->data);//���������븸�׵�ָ��ֵ
						 i = _il;
					 }
					 else break;
				 }
				 else {
					 if (!f_comparer(_right->data, heap[i]->data)) {
						 std::swap(_right->data, heap[i]->data);//���������븸�׵�ָ��ֵ
						 i = _ir;
					 }
					 else break;
				 }
	}while (0 < (_il= (i << 1) + 1) && (_ir= (i << 1) + 2) < _s);
	 };
	 //���ⲿ�ڵ㣨�ǿ�)����������ȫ����Ѽ���ʽ��
	 int _lastInternal = ((_s - 2) >> 1);
	 for (int j = _lastInternal +1; j < _s; ++j) {//�ȴ����ⲿ�ڵ�
		 heap[j] = new BTN::BinTreeNode<T>(set[j]);
	 }
	 if (!((_lastInternal << 1) + 2 < _s)) {//�ų����ӽڵ�
		 int _il = (_lastInternal << 1) + 1;
		 heap[_lastInternal]= new BTN::BinTreeNode<T>(set[_lastInternal]);
		 heap[_il]->parent = heap[_lastInternal];
		 heap[_lastInternal]->left = heap[_il];//˫������
		 PQ_LeftHeap<T, _Comparer>::updateNPL(heap[_lastInternal]);//����npl
		 if (!f_comparer(heap[_il]->data, heap[_lastInternal]->data)) { //����
			 heap[_il]->swap(heap[_lastInternal]);
		 }
         _lastInternal -= 1;//����+1
	 }
for (int j = _lastInternal; j >= 0; --j) {//�����ڲ��ڵ�
		 heap[j] = new BTN::BinTreeNode<T>(set[j]);
		 int _il = (j << 1) + 1, _ir = (j << 1) + 2;
		 heap[j]->left = heap[_il]; heap[_il]->parent = heap[j];
		 heap[j]->right = heap[_ir]; heap[_ir]->parent = heap[j];//˫������
		 PQ_LeftHeap<T, _Comparer>::updateNPL(heap[j]);//����npl
         percolateDown(j);//����
		 }
return heap[0];
 }

 template<typename T, typename _Comparer>
 int PQ_LeftHeap<T, _Comparer>::updateNPL(BTN::BNP(T)n)
 {
	 return (n->m_height=1+__min((PQ_LeftHeap<T, _Comparer>::NPL(n->left)),(PQ_LeftHeap<T, _Comparer>::NPL(n->right))));
 }

 template<typename T, typename _Comparer>
 int PQ_LeftHeap<T, _Comparer>::NPL(BTN::BNP(T) n) 
 {
	 return n?n->m_height:-1;//�͸߶ȱ���һ�£���npl�����������ĸ߶�
 }
 

#endif // !PQ_LEFTHEAP_CPP_CPP
