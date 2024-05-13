#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int vertex;
    struct node* next;
} Node;

typedef struct {
    int nodeCount;
    Node** adjList;
} Graph;

Graph* initGraph() {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->nodeCount = 0;
    return graph;
}

void addVertex(Graph* graph) {
    graph->nodeCount++;
    graph->adjList = realloc(graph->adjList, graph->nodeCount * sizeof(Node*));
    graph->adjList[graph->nodeCount - 1] = NULL;
}

void addEdge(Graph* graph, int start, int end) {
    if (start < 0 || start >= graph->nodeCount 
        || end < 0 || end >= graph->nodeCount) return;

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = end;
    newNode->next = graph->adjList[start];
    graph->adjList[start] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = start;
    newNode->next = graph->adjList[end];
    graph->adjList[end] = newNode;
}

void removeEdge(Graph* graph, int start, int end) {
    if (start < 0 || start >= graph->nodeCount 
        || end < 0 || end >= graph->nodeCount) return;
    
    Node** pNode = &graph->adjList[start];
    while (*pNode) {
        Node* current = *pNode;
        if (current->vertex == end) {
            *pNode = current->next;
            free(current);
            break;
        }
        pNode = &current->next;
    }

    pNode = &graph->adjList[end];
    while (*pNode) {
        Node* current = *pNode;
        if (current->vertex == start) {
            *pNode = current->next;
            free(current);
            break;
        }
        pNode = &current->next;
    }
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->nodeCount; i++) {
        Node* temp = graph->adjList[i];
        printf("Adjacency list of vertex %d:\n head", i);
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->nodeCount; i++) {
        Node* node = graph->adjList[i];
        while (node) {
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->adjList);
    free(graph);
}

int main() {
    Graph* graph = initGraph();
    
    int v = 0;

    printf("정점 개수: ");
    scanf("%d", &v);

    for (int i = 0;i < v;i++) {
        addVertex(graph);
    }

    char command[10];
    int num1, num2;
    printf("Commands: insert <vertex1> <vertex2>, del <vertex1> <vertex2>, exit\n");
    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "insert") == 0) {
            scanf("%d %d", &num1, &num2);
            addEdge(graph, num1, num2);
            printGraph(graph);
        } else if (strcmp(command, "del") == 0) {
            scanf("%d %d", &num1, &num2);
            removeEdge(graph, num1, num2);
            printGraph(graph);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
        }
    }

    freeGraph(graph);

    return 0;
}
