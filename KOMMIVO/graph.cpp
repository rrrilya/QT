#include "graph.h"
#include <QMessageBox>
using namespace std;

Graph::Graph(int vertices) {
    numVertices = vertices;

    adjacencyMatrix.resize(numVertices, vector<int>(numVertices, 0));
    for (int i = 0; i < numVertices; i++) {
        adjacencyMatrix[i][i] = 0;
    }
}

int Graph::getNumVertices() const {
    return numVertices;
}

int Graph::getEdgeWeight(int v1, int v2) const {
    return adjacencyMatrix[v1][v2];
}

void Graph::addEdge(int v1, int v2, int weight) {
    adjacencyMatrix[v1][v2] = weight;
}

vector<int> Graph::getVertices() const {
    vector<int> vertices(numVertices);
    for (int i = 0; i < numVertices; i++) {
        vertices[i] = i;
    }
    return vertices;
}

void Graph::addVertex() {
    numVertices++;
    adjacencyMatrix.resize(numVertices, vector<int>(numVertices, 0));
    for (int i = 0; i < numVertices - 1; i++) {
        adjacencyMatrix[i].resize(numVertices);
    }
}

void Graph::removeVertex(int vertex) {
    if (vertex < 0 || vertex >= numVertices) {
        QMessageBox::critical(nullptr, "Ошибка", "Неверный номер вершины");
        return;
    }
    numVertices--;
    for (int i = 0; i < numVertices; i++) {
        adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + vertex);
    }

    adjacencyMatrix.erase(adjacencyMatrix.begin() + vertex);
}

vector<std::vector<int>> Graph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

void Graph::removeEdge(int v1, int v2) {
    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
        QMessageBox::critical(nullptr, "Ошибка", "Неверные номера вершин");
        return;
    }
    adjacencyMatrix[v1][v2] = 0;
    adjacencyMatrix[v2][v1] = 0;
}

void Graph::editEdgeWeight(int v1, int v2, int weight) {
    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
        QMessageBox::critical(nullptr, "Ошибка", "Неверные номера вершин");
        return;
    }
    adjacencyMatrix[v1][v2] = weight;
}
