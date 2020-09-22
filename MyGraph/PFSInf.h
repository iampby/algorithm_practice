#pragma once
#include"Graph.h"
//各种pfs搜索优先级更新实现
//约定：优先级数越大优先级越低
//BFS版 把到起点的距离作为优先级数，即越近优先级越高
template <typename Tv, typename Te> 
void BfsPU(GH::Graph<Tv,Te>*g, int uk, int v, std::priority_queue <GH::PVertex, std::vector<GH::PVertex>, GH::PVertex >&pq) { //针对BFS算法的顶点优先级更新器
	if (g->status(v) == GH::VStatus::Undiscover) { //对于uk每一尚未被发现的邻接顶点v
		if (g->priority(v) > g->priority(uk) + 1) { //将其到起点的距离作为优先级数
			g->priority(v) = g->priority(uk) + 1; //更新优先级（数）
			g->parent(v) = uk; //更新父节点
			pq.push(GH::PVertex(v,g->priority(v)));//入队优先级队列
		} //如此效果等同于，先被发现者优先
	}
};
//DFS版 把到起点距离的负数作为优先级数，即越远优先级越高
template <typename Tv, typename Te>
void DfsPU(GH::Graph<Tv, Te>*g, int uk, int v, std::priority_queue <GH::PVertex, std::vector<GH::PVertex>, GH::PVertex >&pq) { //针对DFS算法的顶点优先级更新器
	if (g->status(v) == GH::VStatus::Undiscover) { //对于uk每一尚未被发现的邻接顶点v
			if (g->priority(v) > g->priority(uk) - 1) { //将其到起点距离的负数作为优先级数
				g->priority(v) = g->priority(uk) - 1; //更新优先级（数）
				g->parent(v) = uk; //更新父节点
				pq.push(GH::PVertex(v, g->priority(v)));//入队优先级队列
				return; //注意：与BfsPU()不同，这里只要有一个邻接顶点可更新，即可立即返回
			}
	}
};
/*
prim版 每次Tk到Tk+1，把Vk之外的顶点到Vk的距离当做顶点V的优先级数,即符合约定：优先级数越大优先级越低
实际上，每次uk都是当前树中优先级最低的顶点，只需检测uk的邻居,如果边权重小于v的优先级数就把v更新为uk
*/
template <typename Tv, typename Te>
void PrimPU(GH::Graph<Tv, Te>*g, int uk, int v, std::priority_queue <GH::PVertex, std::vector<GH::PVertex>, GH::PVertex >&pq) { //针对prim算法的顶点优先级更新器
if(g->status(v) == GH::VStatus::Undiscover) { //对于uk每一尚未被发现的邻接顶点v
		if(g->priority(v) > g->weight(uk, v)) {
			g->priority(v) = g->weight(uk, v); //更新优先级（数）
			g->parent(v) = uk; //更新父节点
			pq.push(GH::PVertex(v, g->priority(v)));//入队优先级队列
		}
	}
};
/*
Dijkstra版  从T1开始迭代找uk+1 扩展成Tk+1 也就是对边的权重转化为优先级，找优先级最高的，即|P（uk+1）-P（s）|是最小的，也就是找割的一条最短跨越边
*/
template <typename Tv, typename Te>
void DijkstraPU(GH::Graph<Tv, Te>*g, int uk, int v, std::priority_queue <GH::PVertex, std::vector<GH::PVertex>, GH::PVertex >&pq) { //针对prim算法的顶点优先级更新器
	if (g->status(v) == GH::VStatus::Undiscover) { //对于uk每一尚未被发现的邻接顶点v
		int w = g->priority(uk) + g->weight(uk, v);
		if (g->priority(v) > w) {
			g->priority(v) = w; //更新优先级（数）
			g->parent(v) = uk; //更新父节点
			pq.push(GH::PVertex(v, g->priority(v)));//入队优先级队列
		}
	}
};