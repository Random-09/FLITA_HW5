#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph {
    int** matrix;
    int verticesNum;
} Graph_t;

char* getData(FILE* filePtr) {
    fseek(filePtr, 0, SEEK_END);
    int fileLen = ftell(filePtr) - 1;
    fseek(filePtr, 0, SEEK_SET);
    char* data;
    data = (char *) malloc(sizeof(char) * fileLen);
    fread(data, sizeof(char), fileLen, filePtr);
    data[fileLen] = '\0';
    return data;
}

int getVerticesNum(const char* data) {
    int count = 0;
    int i = 0;
    while (data[i] != '\n') {
        if (data[i] != ' ')
            count++;
        i++;
    }
    return count;
}

Graph_t* initGraph(int verticesNum) {
    Graph_t* graph = (Graph_t *) malloc(sizeof(Graph_t));
    graph->verticesNum = verticesNum;
    graph->matrix = (int **) malloc(verticesNum * sizeof(int *));
    for (int i = 0; i < verticesNum; i++) {
        graph->matrix[i] = (int *) malloc(verticesNum * sizeof(int));
    }
    return graph;
}

void strToGraph(Graph_t* graph, char* data) {
    char* token;
    for (int i = 0; i < graph->verticesNum; i++) {
        for (int j = 0; j < graph->verticesNum; j++) {
            token = strtok_r(data, "\n ", &data);
            graph->matrix[i][j] = atoi(token);
        }
    }
}

void printVerticesByDegree(Graph_t* graph, int degree) {
    for (int i = 0; i < graph->verticesNum; i++) {
        int count = 0;
        for (int j = 0; j < graph->verticesNum; j++) {
            count += graph->matrix[i][j];
        }
        if (count == degree)
            printf("Vertex with degree of %d: %d\n", degree, i + 1);
    }
}

void freeGraph(Graph_t* graph) {
    for (int i = 0; i < graph->verticesNum; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        puts("Wrong number of arguments!");
        exit(EXIT_FAILURE);
    }
    const char* filePath = argv[1];
    int degree = atoi(argv[2]);
    FILE* filePtr = fopen(filePath, "r");
    if (filePtr == NULL) {
        puts("Error opening file");
        exit(EXIT_FAILURE);
    }
    char* data = getData(filePtr);
    fclose(filePtr);
    int vertices = getVerticesNum(data);
    Graph_t* graph = initGraph(vertices);
    strToGraph(graph, data);
    free(data);
    printVerticesByDegree(graph, degree);
    freeGraph(graph);
    return EXIT_SUCCESS;
}

// TODO
// Find every vertex of a graph with a certain vertex degree
// Graph is implemented using adjacency matrix