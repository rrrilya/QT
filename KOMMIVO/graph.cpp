#include "graph.h"

Graph::Graph(int numVertices) {
    for (int i = 0; i < numVertices; ++i) {
        addVertex();
    }
}

void Graph::addVertex() {
    int index = vertices.size();
    vertices.emplace_back(index);

    for (auto& row : adjacencyMatrix) {
        row.push_back(std::numeric_limits<int>::max());
    }

    adjacencyMatrix.emplace_back(vertices.size(), std::numeric_limits<int>::max());
}

void Graph::removeVertex(int index) {
    vertices.erase(vertices.begin() + index);

    for (auto& row : adjacencyMatrix) {
        row.erase(row.begin() + index);
    }

    adjacencyMatrix.erase(adjacencyMatrix.begin() + index);
}

void Graph::addEdge(int from, int to, int weight) {
    edges.emplace_back(from, to, weight);
    adjacencyMatrix[from][to] = weight;
}

void Graph::removeEdge(int from, int to) {
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it->from == from && it->to == to) {
            edges.erase(it);
            break;
        }
    }

    adjacencyMatrix[from][to] = std::numeric_limits<int>::max();
}

void Graph::setWeight(int from, int to, int weight) {
    for (auto& edge : edges) {
        if (edge.from == from && edge.to == to) {
            edge.weight = weight;
            break;
        }
    }

    adjacencyMatrix[from][to] = weight;
}

const std::vector<Graph::Edge>& Graph::getEdges() const {
    return edges;
}

const std::vector<std::vector<int>>& Graph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

const std::vector<Graph::Vertex>& Graph::getVertices() const {
    return vertices;
}
