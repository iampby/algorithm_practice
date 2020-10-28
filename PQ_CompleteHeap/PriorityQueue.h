#ifndef PRIORITYQUEUE_H_H
#define PRIORITYQUEUE_H_H
/*
���ȼ����нӿ� 
*/

#define PQ_OUTOFLINE
template<typename T>
class PriorityQueue
{
public:
	PriorityQueue() = default;
	~PriorityQueue() = default;
	//�ӿ� ע����������,��stlһ��
	virtual void push(T const&) = 0;//�������
	virtual  const T& top() = 0;//�����Ѷ�
	virtual void pop() = 0;//ɾ���Ѷ� 
};



#endif // ! PRIORITYQUEUE_H_H
