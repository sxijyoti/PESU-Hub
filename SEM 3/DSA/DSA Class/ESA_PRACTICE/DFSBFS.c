void DFS(int graph[V][V], int visited[V], int v){
    visited[v]=1;
    printf("%d",v);

    for(int i=0; i<V; i++){
        if(graph[V][i] && !visited[i]){
            DFS(graph,visited,i);
        }
    }
}

void BFS(int graph[V][V], int visited[V], int start){
    enqueue(start);
    visited[start]=1;

    while(!isempty()){
        int vertex = dequeue();
        printf("%d", vertex);

        for(int i = 0; i < V; i++)
    }
}