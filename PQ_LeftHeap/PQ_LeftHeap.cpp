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
	this->m_root= heapify(set);//构造完全二叉堆 保持堆序
  this->m_size += set.size();//更新规模
	std::vector<T>_rs; _rs.swap(set);//丢失内容
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
	BTN::BNP(T)_right = new BTN::BinTreeNode<T>(e);//右堆建立
	this->m_root = PQ_LeftHeap<T, _Comparer>::merge(this->m_root, _right);//更新树根
	++this->m_size;//更新规模
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
	 this->m_root = PQ_LeftHeap<T, _Comparer>::merge(_left, _right);//更新树根
	 --this->m_size;//更新规模
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
     BTN::BNP(T) _right = b;//要合并的左右堆根节点初始化
	 BTN::BNP(T)_last = nullptr;//记录最后一个用于更新npl
	 //保证堆序
	 if (f_comparer(_left->data, _right->data)) {
		 std::swap(_left, _right);//保证左合并右时保证堆序
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
			 std::swap(_left, _right);//保证左合并右时保证堆序
			 _rc->parent->right = _left;//取左右堆大值向下接入
			 _left->parent = _rc->parent;//向上联接
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
	 //更新npl并保证左倾性
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
	 //即用的引用lambda
	 std::vector<BTN::BNP(T)>heap(set.size(),nullptr);//初始化完全二叉堆为null
	 int _s = set.size();
	 auto percolateDown = [&](int i) {
		 int _il = (i << 1) + 1, _ir = (i << 1) + 2;
	do{
		BTN::BNP(T)&_left = heap[_il];//左孩子
				 BTN::BNP(T)&_right = heap[_ir];//右孩子
				 if (!f_comparer(_left->data, _right->data)) {
					 if (!f_comparer(_left->data, heap[i]->data)) {
						std::swap(_left->data,heap[i]->data);//交换孩子与父亲的指向值
						 i = _il;
					 }
					 else break;
				 }
				 else {
					 if (!f_comparer(_right->data, heap[i]->data)) {
						 std::swap(_right->data, heap[i]->data);//交换孩子与父亲的指向值
						 i = _ir;
					 }
					 else break;
				 }
	}while (0 < (_il= (i << 1) + 1) && (_ir= (i << 1) + 2) < _s);
	 };
	 //自外部节点（非空)到根创建完全二叉堆即左式堆
	 int _lastInternal = ((_s - 2) >> 1);
	 for (int j = _lastInternal +1; j < _s; ++j) {//先创建外部节点
		 heap[j] = new BTN::BinTreeNode<T>(set[j]);
	 }
	 if (!((_lastInternal << 1) + 2 < _s)) {//排除单子节点
		 int _il = (_lastInternal << 1) + 1;
		 heap[_lastInternal]= new BTN::BinTreeNode<T>(set[_lastInternal]);
		 heap[_il]->parent = heap[_lastInternal];
		 heap[_lastInternal]->left = heap[_il];//双向联接
		 PQ_LeftHeap<T, _Comparer>::updateNPL(heap[_lastInternal]);//更新npl
		 if (!f_comparer(heap[_il]->data, heap[_lastInternal]->data)) { //下滤
			 heap[_il]->swap(heap[_lastInternal]);
		 }
         _lastInternal -= 1;//进度+1
	 }
for (int j = _lastInternal; j >= 0; --j) {//创建内部节点
		 heap[j] = new BTN::BinTreeNode<T>(set[j]);
		 int _il = (j << 1) + 1, _ir = (j << 1) + 2;
		 heap[j]->left = heap[_il]; heap[_il]->parent = heap[j];
		 heap[j]->right = heap[_ir]; heap[_ir]->parent = heap[j];//双向联接
		 PQ_LeftHeap<T, _Comparer>::updateNPL(heap[j]);//更新npl
         percolateDown(j);//下滤
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
	 return n?n->m_height:-1;//和高度保持一致，即npl等于满子树的高度
 }
 

#endif // !PQ_LEFTHEAP_CPP_CPP
