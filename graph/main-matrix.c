#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct {
    int nodeCount;
    int matrix[MAX_SIZE][MAX_SIZE];
} Graph;

Graph initGraph() {
    Graph graph;
    graph.nodeCount = 0;
    for (int i = 0;i < MAX_SIZE;i++) {
        for (int j = 0;j < MAX_SIZE;j++) {
            graph.matrix[i][j] = 0;
        }
    }
    return graph;
}

void addVertex(Graph *graph) {
    if (graph->nodeCount == MAX_SIZE) return;
    graph->nodeCount++;
    for (int i = 0;i < graph->nodeCount;i++) {
        graph->matrix[graph->nodeCount - 1][i] = 0;
        graph->matrix[i][graph->nodeCount - 1] = 0;
    }
}

void addEdge(Graph *graph, int start, int end) {
    if (start < 0 || start >= graph->nodeCount 
        || end < 0 || end >= graph->nodeCount) return;

    graph->matrix[start][end] = 1;
    graph->matrix[end][start] = 1;
}

void removeEdge(Graph *graph, int start, int end) {
    if (start < 0 || start >= graph->nodeCount 
        || end < 0 || end >= graph->nodeCount) return;

    graph->matrix[start][end] = 0;
    graph->matrix[end][start] = 0;
}

void printGraph(Graph *graph) {
    for (int i = 0; i < graph->nodeCount; i++) {
        for (int j = 0; j < graph->nodeCount; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Graph graph = initGraph();
    
    int v = 0;

    printf("정점 개수: ");
    scanf("%d", &v);

    for (int i = 0;i < v;i++) {
        addVertex(&graph);
    }

    char command[10];
    int num1, num2;
    printf("Commands: insert <vertex1> <vertex2>, del <vertex1> <vertex2>, exit\n");
    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "insert") == 0) {
            scanf("%d %d", &num1, &num2);
            addEdge(&graph, num1, num2);
            printGraph(&graph);
        } else if (strcmp(command, "del") == 0) {
            scanf("%d %d", &num1, &num2);
            removeEdge(&graph, num1, num2);
            printGraph(&graph);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
        }
    }

    return 0;
}
