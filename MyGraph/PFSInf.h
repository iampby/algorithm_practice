#pragma once
#include"Graph.h"
//����pfs�������ȼ�����ʵ��
//Լ�������ȼ���Խ�����ȼ�Խ��
//BFS�� �ѵ����ľ�����Ϊ���ȼ�������Խ�����ȼ�Խ��
template <typename Tv, typename Te> 
void BfsPU(GH::Graph<Tv,Te>*g, int uk, int v, std::priority_queue <GH::PVertex, std::vector<GH::PVertex>, GH::PVertex >&pq) { //���BFS�㷨�Ķ������ȼ�������
	if (g->status(v) == GH::VStatus::Undiscover) { //����ukÿһ��δ�����ֵ��ڽӶ���v
		if (g->priority(v) > g->priority(uk) + 1) { //���䵽���ľ�����Ϊ���ȼ���
			g->priority(v) = g->priority(uk) + 1; //�������ȼ�������
			g->parent(v) = uk; //���¸��ڵ�
			pq.push(GH::PVertex(v,g->priority(v)));//������ȼ�����
		} //���Ч����ͬ�ڣ��ȱ�����������
	}
};
//DFS�� �ѵ�������ĸ�����Ϊ���ȼ�������ԽԶ���ȼ�Խ��
template <typename Tv, typename Te>
void DfsPU(GH::Graph<Tv, Te>*g, int uk, int v, std::priority_queue <GH::PVertex, std::vector<GH::PVertex>, GH::PVertex >&pq) { //���DFS�㷨�Ķ������ȼ�������
	if (g->status(v) == GH::VStatus::Undiscover) { //����ukÿһ��δ�����ֵ��ڽӶ���v
			if (g->priority(v) > g->priority(uk) - 1) { //���䵽������ĸ�����Ϊ���ȼ���
				g->priority(v) = g->priority(uk) - 1; //�������ȼ�������
				g->parent(v) = uk; //���¸��ڵ�
				pq.push(GH::PVertex(v, g->priority(v)));//������ȼ�����
				return; //ע�⣺��BfsPU()��ͬ������ֻҪ��һ���ڽӶ���ɸ��£�������������
			}
	}
};
/*
prim�� ÿ��Tk��Tk+1����Vk֮��Ķ��㵽Vk�ľ��뵱������V�����ȼ���,������Լ�������ȼ���Խ�����ȼ�Խ��
ʵ���ϣ�ÿ��uk���ǵ�ǰ�������ȼ���͵Ķ��㣬ֻ����uk���ھ�,�����Ȩ��С��v�����ȼ����Ͱ�v����Ϊuk
*/
template <typename Tv, typename Te>
void PrimPU(GH::Graph<Tv, Te>*g, int uk, int v, std::priority_queue <GH::PVertex, std::vector<GH::PVertex>, GH::PVertex >&pq) { //���prim�㷨�Ķ������ȼ�������
if(g->status(v) == GH::VStatus::Undiscover) { //����ukÿһ��δ�����ֵ��ڽӶ���v
		if(g->priority(v) > g->weight(uk, v)) {
			g->priority(v) = g->weight(uk, v); //�������ȼ�������
			g->parent(v) = uk; //���¸��ڵ�
			pq.push(GH::PVertex(v, g->priority(v)));//������ȼ�����
		}
	}
};
/*
Dijkstra��  ��T1��ʼ������uk+1 ��չ��Tk+1 Ҳ���ǶԱߵ�Ȩ��ת��Ϊ���ȼ��������ȼ���ߵģ���|P��uk+1��-P��s��|����С�ģ�Ҳ�����Ҹ��һ����̿�Խ��
*/
template <typename Tv, typename Te>
void DijkstraPU(GH::Graph<Tv, Te>*g, int uk, int v, std::priority_queue <GH::PVertex, std::vector<GH::PVertex>, GH::PVertex >&pq) { //���prim�㷨�Ķ������ȼ�������
	if (g->status(v) == GH::VStatus::Undiscover) { //����ukÿһ��δ�����ֵ��ڽӶ���v
		int w = g->priority(uk) + g->weight(uk, v);
		if (g->priority(v) > w) {
			g->priority(v) = w; //�������ȼ�������
			g->parent(v) = uk; //���¸��ڵ�
			pq.push(GH::PVertex(v, g->priority(v)));//������ȼ�����
		}
	}
};