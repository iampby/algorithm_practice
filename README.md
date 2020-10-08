Splay树实现
---
继承于二叉搜索树，二叉搜索树采用“3+4”重构方法对树进行zig、zag，树的遍历实现了先序、中序、后序、层次遍历。同时，树也对拷贝和移动构造进行了区分。<br />
先序和后序采用的是同种遍历方法，额外消耗O(2)的空间进行回溯追踪，中序采用找后继的方法，无额外空间消耗，比起栈遍历，前者要遍历次数多一些,层次遍历采用队列的方式遍历，仅仅遍历树一次，额外消耗空间等于叶节点数。

Splay树允许插入相同值，查找时如有相同值即查找最右的那个值，插入有2种方法，BST插入再伸展及访问伸展的方法，删除操作执行的伸展为其后继，即新根节点值大于等于原先的值。实现含有多余信息即高度及相关操作。
