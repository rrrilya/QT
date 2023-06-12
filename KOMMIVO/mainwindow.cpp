#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <queue>
#include <QMessageBox>
#include <QLineEdit>
#include <QIntValidator>
#include <QInputDialog>
#include <QVBoxLayout>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), graph(0)
{
    ui->setupUi(this);
    setStyleSheet("background-color: #333333; color: #ffffff;");

    graphWidget = new GraphWidget(this);
    reshButton = new QPushButton("Решение", this);
    connect(reshButton, &QPushButton::clicked, this, &MainWindow::resh);

    vertexCountLineEdit = new QLineEdit(this);
    vertexCountLineEdit->setPlaceholderText("Число вершин");
    vertexCountLineEdit->setValidator(new QIntValidator(2, 100, this));

    connect(vertexCountLineEdit, &QLineEdit::textChanged, this, &MainWindow::onVertexCountChanged);

    adjacencyMatrixButton = new QPushButton("Матрица смежности", this);
    connect(adjacencyMatrixButton, &QPushButton::clicked, this, &MainWindow::showAdjacencyMatrix);

    addVertexButton = new QPushButton("Добавить вершину", this);
    connect(addVertexButton, &QPushButton::clicked, this, &MainWindow::addVertex);

    addEdgeButton = new QPushButton("Добавить ребро", this);
    connect(addEdgeButton, &QPushButton::clicked, this, &MainWindow::addEdge);

    removeEdgeButton = new QPushButton("Удалить ребро", this);
    connect(removeEdgeButton, &QPushButton::clicked, this, &MainWindow::removeEdge);

    removeVertexButton = new QPushButton("Удалить вершину", this);
    connect(removeVertexButton, &QPushButton::clicked, this, &MainWindow::removeVertex);

    editEdgeWeightButton = new QPushButton("Изменить вес ребра", this);
    connect(editEdgeWeightButton, &QPushButton::clicked, this, &MainWindow::editWeight);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(vertexCountLineEdit, 0, 0, 1, 2);
    layout->addWidget(addVertexButton, 1, 0);
    layout->addWidget(removeVertexButton, 1, 1);
    layout->addWidget(addEdgeButton, 2, 0);
    layout->addWidget(removeEdgeButton, 2, 1);
    layout->addWidget(editEdgeWeightButton, 3, 0);
    layout->addWidget(reshButton, 4, 0);
    layout->addWidget(adjacencyMatrixButton, 4, 1);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(graphWidget);
    rightLayout->setAlignment(Qt::AlignTop);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(layout, 1);
    mainLayout->addLayout(rightLayout, 3);

    QWidget *widget = new QWidget(this);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
}


MainWindow::~MainWindow()
{
    delete ui;
}

const int INF = numeric_limits<int>::max();

int findMin(const vector<int>& arr) {
    int minVal = INF;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    return minVal;
}

int findMinIndex(const vector<int>& arr) {
    int minIndex = -1;
    int minVal = INF;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
            minIndex = i;
        }
    }
    return minIndex;
}

PathInfo solveTSP(const Graph& graph, int startVertex) {
    int numVertices = graph.getNumVertices();

    priority_queue<PathInfo, vector<PathInfo>, function<bool(const PathInfo&, const PathInfo&)>> pq(
        [](const PathInfo& p1, const PathInfo& p2) {
            return p1.cost > p2.cost;
        }
        );

    vector<int> path;
    path.push_back(startVertex);
    PathInfo initialPath(path, 0);
    pq.push(initialPath);

    int lowerBound = INF;

    while (!pq.empty()) {
        PathInfo currentPath = pq.top();
        pq.pop();

        int currentVertex = currentPath.path.back();
        int currentCost = currentPath.cost;

        if (currentPath.path.size() == numVertices) {
            int finalCost = currentCost + graph.getEdgeWeight(currentVertex, startVertex);
            return PathInfo(currentPath.path, finalCost);
        }

        vector<int> remainingVertices = graph.getVertices();
        for (int vertex : currentPath.path) {
            remainingVertices.erase(remove(remainingVertices.begin(), remainingVertices.end(), vertex), remainingVertices.end());
        }

        for (int nextVertex : remainingVertices) {
            int edgeWeight = graph.getEdgeWeight(currentVertex, nextVertex);

            if (edgeWeight == 0)
                continue;

            int nextCost = currentCost + edgeWeight;

            int minRemainingEdgeWeight = INF;
            for (int vertex : remainingVertices) {
                int remainingEdgeWeight = graph.getEdgeWeight(nextVertex, vertex);
                if (remainingEdgeWeight < minRemainingEdgeWeight)
                    minRemainingEdgeWeight = remainingEdgeWeight;
            }
            int lowerBoundCost = nextCost + minRemainingEdgeWeight;
            if (lowerBoundCost >= lowerBound)
                continue;

            vector<int> newPath = currentPath.path;
            newPath.push_back(nextVertex);
            PathInfo newPathInfo(newPath, nextCost);
            pq.push(newPathInfo);
        }
    }

    return PathInfo({}, INF);
}

void MainWindow::resh()
{
    if (!graph)
    {
        QMessageBox::warning(this, "Ошибка", "Граф не создан!");
        return;
    }

    // Отображение диалогового окна для выбора начальной вершины
    bool ok;
    int startVertex = QInputDialog::getInt(this, "Начальная вершина", "Введите номер начальной вершины (от 0 до " +
                                                   QString::number(graph->vertexCount() - 1) + "):", 0, 0,
                                                   graph->vertexCount() - 1, 1, &ok);
    if (!ok)
        return;

    vector<int> dist(graph->vertexCount(), INF); // Массив расстояний до каждой вершины
    vector<bool> visited(graph->vertexCount(), false); // Массив для отметки посещенных вершин
    dist[startVertex] = 0; // Расстояние до начальной вершины равно 0

    // Цикл по всем вершинам графа
    for (int i = 0; i < graph->vertexCount(); ++i)
    {
        int currentVertex = -1;
        int minDist = INF;

        // Находим непосещенную вершину с минимальным расстоянием
        for (int j = 0; j < graph->vertexCount(); ++j)
        {
            if (!visited[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                currentVertex = j;
            }
        }

        // Если не удалось найти непосещенную вершину, алгоритм завершается
        if (currentVertex == -1)
            break;

        visited[currentVertex] = true; // Помечаем текущую вершину как посещенную

        // Обновляем расстояния до смежных вершин
        for (int j = 0; j < graph->vertexCount(); ++j)
        {
            if (graph->isConnected(currentVertex, j) && !visited[j])
            {
                int weight = graph->getWeight(currentVertex, j);
                if (dist[currentVertex] + weight < dist[j])
                {
                    dist[j] = dist[currentVertex] + weight;
                }
            }
        }
    }

    // Отображение результатов алгоритма
    QString result;
    for (int i = 0; i < graph->vertexCount(); ++i)
    {
        result += "Расстояние до вершины " + QString::number(i) + ": ";
        if (dist[i] == INF)
            result += "недостижимо";
        else
            result += QString::number(dist[i]);
        result += "\n";
    }

    QMessageBox::information(this, "Результаты", result);
}

void MainWindow::onVertexCountChanged(const QString& text)
{
    bool ok;
    int vertexCount = text.toInt(&ok);

    if (ok) {
        updateGraph(vertexCount);
    } else {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите целое число вершин.");
    }
}

void MainWindow::updateGraph(int vertexCount)
{
    graph = Graph(vertexCount);

    if (vertexCount < 2) {
        QMessageBox::warning(this, "Ошибка", "Число вершин должно быть не менее 2.");
        return;
    }
    bool ok = true;
    while(ok){
        int startikVertex = QInputDialog::getInt(this, "Начальная вершина", "Введите номер начальной вершины для ребра", 0, 0, vertexCount - 1, 1, &ok);
        int endVertex = QInputDialog::getInt(this, "Конечная вершина", "Введите номер конечной вершины для ребра", 0, 0, vertexCount - 1, 1, &ok);
        int weight = QInputDialog::getInt(this, "Вес ребра", "Введите вес ребра", 0, 0, std::numeric_limits<int>::max(), 1, &ok);
        graph.addEdge(startikVertex, endVertex, weight);
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Создание ребра", "Хотите создать еще одно ребро?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            ok = false;
        }
    }
    graphWidget->visGraph(graph);
}

void MainWindow::showAdjacencyMatrix()
{
    int numVertices = graph.getNumVertices();
    std::vector<std::vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();

    QString matrixString;

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            matrixString += QString::number(adjacencyMatrix[i][j]) + "\t";
        }
        matrixString += "\n";
    }

    QMessageBox::information(this, "Матрица смежности", matrixString);
}

void MainWindow::addVertex() {
    graph.addVertex();
    updateGraph(graph.getNumVertices());
    graphWidget->visGraph(graph);
}

void MainWindow::addEdge()
{
    int numVertices = graph.getNumVertices();
    int startikVertex = QInputDialog::getInt(this, "Начальная вершина", "Введите номер начальной вершины для ребра", 0, 0, numVertices - 1, 1);
    int endVertex = QInputDialog::getInt(this, "Конечная вершина", "Введите номер конечной вершины для ребра", 0, 0, numVertices - 1, 1);
    int weight = QInputDialog::getInt(this, "Вес ребра", "Введите вес ребра", 0, 0, std::numeric_limits<int>::max(), 1);
    graph.addEdge(startikVertex, endVertex, weight);
    graphWidget->visGraph(graph);
}

void MainWindow::removeEdge()
{
    bool ok = true;
    int numVertices = graph.getNumVertices();
    while(ok){
        int startikVertex = QInputDialog::getInt(this, "Начальная вершина", "Введите номер начальной вершины для ребра", 0, 0, numVertices - 1, 1, &ok);
        int endVertex = QInputDialog::getInt(this, "Конечная вершина", "Введите номер конечной вершины для ребра", 0, 0, numVertices - 1, 1, &ok);
        graph.removeEdge(startikVertex, endVertex);
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Удаление ребра", "Хотите удалить еще одно ребро?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            ok = false;
        }
    }
    graphWidget->visGraph(graph);
}

void MainWindow::removeVertex()
{
    int numVertices = graph.getNumVertices();
    int Vertex = QInputDialog::getInt(this, "Вершина", "Введите номер удаляемой вершины", 0, 0, numVertices - 1, 1);
    graph.removeVertex(Vertex);
    graphWidget->visGraph(graph);
}

void MainWindow::editWeight()
{
    int numVertices = graph.getNumVertices();
    int startikVertex = QInputDialog::getInt(this, "Начальная вершина", "Введите номер начальной вершины для ребра", 0, 0, numVertices - 1, 1);
    int endVertex = QInputDialog::getInt(this, "Конечная вершина", "Введите номер конечной вершины для ребра", 0, 0, numVertices - 1, 1);
    int weight = QInputDialog::getInt(this, "Новый вес ребра", "Введите новый вес ребра", 0, 0, std::numeric_limits<int>::max(), 1);
    graph.editEdgeWeight(startikVertex, endVertex, weight);
    graphWidget->visGraph(graph);
}
