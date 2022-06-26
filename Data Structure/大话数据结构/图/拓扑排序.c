// 在一个表示工程的有向图中，用顶点表示活动，用弧
// 表示活动之间的优先关系，这样的有向图为顶点表示活动的网，我们称之为AOV网（Activity On Vertex Network）

// 拓扑排序，就是对一个有向图构造拓扑序列的过程
// 若全部顶点被输出，说明他是不存在环（回路）的AOV网；
// 如果输出顶点少了，则存在回路，不是AOV网

// O(V+E)

// 拓扑排序基本思路：从AOV网选择一个入度为0的顶点输出，然后删去此顶点，
// 并删除以此顶点为尾的弧，继续重复此步骤，知道输出全部顶点或者AOV网中不存在入度为0的顶点

Status TopologicalSort(GraphAdjList GL){
    EdgeNode *e;
    int i, k, gettop;
    int top = 0;
    int count = 0;
    int *stack; // 建栈存储入度为0的顶点
    stack = (int*) malloc (GL->numVertexes * sizeof(int));

    for(i = 0; i<GL->numVertexes; i++)
        if(GL->adjList[i].in == 0)
            stack[++top] = i;
    
    while (top!=0){
        gettop = stack[top--];
        printf("%d -> ", GL->adjList[gettop].data);
        count++; // 统计输出顶点数
        for(e=GL->adjList[gettop].firstedge; e; e=e->next){ // 对此顶点弧表遍历
            k = e->adjvex;

            if(!(--GL->adjList[k].in)) // k号顶点邻接点入度减1
                stack[++top] = k;      // 为0则入栈
        }
    }

    if(count<GL->numVertexes)
        return ERROR;
    else
        return OK;
}