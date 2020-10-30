#ifndef PRIORITYQUEUE_H_H
#define PRIORITYQUEUE_H_H
/*
优先级队列接口 
*/

#define PQ_OUTOFLINE
template<typename T>
class PriorityQueue
{
public:
	PriorityQueue() = default;
	~PriorityQueue() = default;
	//接口 注：不负责检测,和stl一致
	virtual void push(T const&) = 0;//插入词条
	virtual  const T& top() = 0;//弹出堆顶
	virtual void pop() = 0;//删除堆顶 
};



#endif // ! PRIORITYQUEUE_H_H
