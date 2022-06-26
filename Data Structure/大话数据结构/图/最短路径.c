// 1. 迪杰斯特拉
int dijkstra(int num){
    int* distance;
	distance = calloc(num, sizeof(int));
    
	bool* book; // Record city visited
	book = calloc(num, sizeof(bool));

    // init 
    for(int i = 0 ; i < num ; i++){
        for(int j = 0 ; j < num ; j++)
            if(i!=j && matrix[i][j] == 0)
                matrix[i][j] = INF;
            else
                matrix[i][j] = matrix[i][j];
        distance[i] = matrix[0][i];  // start from index 0 (capital)
        book[i] = false;
    }

    book[0] = true;
    int nextNode, minDistance, count = 1;

    while(count < num-1) {
        minDistance = INF + 1;

        for(int i = 0 ; i < num ; i++) {
            if (distance[i] < minDistance && !book[i]) {
                minDistance = distance[i];
                nextNode = i;
            }
        }

        book[nextNode] = true;

        for (int i = 0; i < num; i++)
            if (!book[i])
                if (minDistance + matrix[nextNode][i] < distance[i])
                    distance[i] = minDistance + matrix[nextNode][i];
        
        count++;
    }
}

// 2. bellman-ford O(VE)

// 3. floyd-warshall O(V^3)