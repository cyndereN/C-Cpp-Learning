// 1. 深度优先遍历
// (类似一棵二叉树的前序遍历)
// 非递归：
// 1.利用栈实现
// 2.从源节点开始把节点按照深度放入栈，然后弹出
// 3.每弹出一个点，把该节点下一个没有进过栈的邻接点放入栈
// 4.直到栈为空
// 邻接矩阵O(V^2), 邻接表O(V+E)


// 2.广度优先遍历
// 非递归：
// 1.利用栈实现
// 2.从源节点开始把节点按照深度放入栈，然后弹出
// 3.每弹出一个点，把该节点下一个没有进过栈的邻接点放入栈
// 4.直到栈为空
// BFS适合找到最短路，因为找到之后立刻返回，而DFS则判断所有情况