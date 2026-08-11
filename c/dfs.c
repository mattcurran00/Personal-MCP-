#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//struct for a node in the adjacency list
struct Node {
    int data;
    struct Node* next; //pointer to the structure Node
};

// struct for the list 
struct List {
    struct Node* head; //pointer to the structure node
};
// struct for the graph 
struct Graph{
    int vertices;
    struct List* array; //pointer to the structure List
};

struct Node* createNewNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data; //new structs data field is equals to data
    newNode->next = NULL; // since this is the newest one, we say there isnt a next. 
    return newNode; //return a TYPE that is a structure to a Node. "head" is assigning it a name
    //think of it as assigning any other type, like an int
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->array = (struct List*)malloc(sizeof(struct List) * vertices);

    for(int i = 0;i < vertices;i++){
        graph->array[i].head = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest){

    struct Node* newNode = createNewNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void DFS(struct Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d", vertex);
    struct Node* currentNode = graph->array[vertex].head;
    while(currentNode) {
        int adjacentVertex = currentNode->data;
        if (!visited[adjacentVertex]){
            DFS(graph, adjacentVertex, visited);
        }
        currentNode = currentNode->next;
    }
}

void DFSTraversal(struct Graph* graph, int* order, int orderSize){
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    for (int i = 0;i < graph->vertices;i++){
        visited[i] = false;
    }
    for (int i = 0;i < orderSize; i++){
        if(!visited[order[i]]){
            DFS(graph, order[i], visited);
        }
    }
    free(visited);
}

int main(){

    int vertices = 4;
    struct Graph* graph = createGraph(vertices);
    
    addEdge(graph, 2, 0);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 0, 1);
    printf("\nNumber of vertices: %d\n", vertices);

    int order[] = {2, 0, 1, 3};
    int orderSize = sizeof(order) / sizeof(order[0]);

    printf("Following is Depth First Traversal (starting from vertex 2):\n");
    DFSTraversal(graph, order, orderSize);
    return 0;
}