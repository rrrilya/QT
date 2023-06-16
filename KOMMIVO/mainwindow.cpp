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
    : QMainWindow(parent), ui(new Ui::MainWindow), graph(0)
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

int findMin(const vector<int> &arr)
{
    return *min_element(arr.begin(), arr.end());
}

int findMinIndex(const vector<int> &arr)
{
    auto minElement = min_element(arr.begin(), arr.end());
    return minElement != arr.end() ? distance(arr.begin(), minElement) : -1;
}

struct Edge
{
    int source;
    int destination;
    int weight;
};

class Graph
{
public:
    int vertexCount;
    vector<vector<int>> adjacencyMatrix;

    Graph(int count)
    {
        vertexCount = count;
        adjacencyMatrix.resize(vertexCount, vector<int>(vertexCount, INF));
    }

    void addEdge(int source, int destination, int weight)
    {
        adjacencyMatrix[source][destination] = weight;
        adjacencyMatrix[destination][source] = weight;
    }

    void removeEdge(int source, int destination)
    {
        adjacencyMatrix[source][destination] = INF;
        adjacencyMatrix[destination][source] = INF;
    }

    vector<Edge> getEdges()
    {
        vector<Edge> edges;
        for (int i = 0; i < vertexCount; ++i)
        {
            for (int j = i + 1; j < vertexCount; ++j)
            {
                if (adjacencyMatrix[i][j] != INF)
                {
                    Edge edge;
                    edge.source = i;
                    edge.destination = j;
                    edge.weight = adjacencyMatrix[i][j];
                    edges.push_back(edge);
                }
            }
        }
        return edges;
    }
};

void MainWindow::onVertexCountChanged()
{
    QString text = vertexCountLineEdit->text();
    bool ok;
    int vertexCount = text.toInt(&ok);
    if (ok)
    {
        graph = new Graph(vertexCount);
        graphWidget->setGraph(graph);
        graphWidget->update();
    }
}

void MainWindow::addVertex()
{
    if (graph == nullptr)
    {
        QMessageBox::information(this, "Ошибка", "Сначала установите количество вершин");
        return;
    }
    int newVertexCount = graph->vertexCount + 1;
    graph->adjacencyMatrix.resize(newVertexCount, vector<int>(newVertexCount, INF));
    graph->vertexCount = newVertexCount;
    graphWidget->setGraph(graph);
    graphWidget->update();
}

void MainWindow::removeVertex()
{
    if (graph == nullptr)
    {
        QMessageBox::information(this, "Ошибка", "Сначала установите количество вершин");
        return;
    }
    int vertexIndex = QInputDialog::getInt(this, "Удаление вершины", "Введите индекс вершины для удаления:");
    if (vertexIndex < 0 || vertexIndex >= graph->vertexCount)
    {
        QMessageBox::information(this, "Ошибка", "Некорректный индекс вершины");
        return;
    }
    graph->adjacencyMatrix.erase(graph->adjacencyMatrix.begin() + vertexIndex);
    for (int i = 0; i < graph->vertexCount; ++i)
    {
        graph->adjacencyMatrix[i].erase(graph->adjacencyMatrix[i].begin() + vertexIndex);
    }
    graph->vertexCount--;
    graphWidget->setGraph(graph);
    graphWidget->update();
}

void MainWindow::addEdge()
{
    if (graph == nullptr)
    {
        QMessageBox::information(this, "Ошибка", "Сначала установите количество вершин");
        return;
    }
    bool ok;
    int source = QInputDialog::getInt(this, "Добавление ребра", "Введите начальную вершину:", 0, 0, graph->vertexCount - 1, 1, &ok);
    if (!ok)
        return;
    int destination = QInputDialog::getInt(this, "Добавление ребра", "Введите конечную вершину:", 0, 0, graph->vertexCount - 1, 1, &ok);
    if (!ok)
        return;
    int weight = QInputDialog::getInt(this, "Добавление ребра", "Введите вес ребра:", 0, 0, INT_MAX, 1, &ok);
    if (!ok)
        return;
    graph->addEdge(source, destination, weight);
    graphWidget->update();
}

void MainWindow::removeEdge()
{
    if (graph == nullptr)
    {
        QMessageBox::information(this, "Ошибка", "Сначала установите количество вершин");
        return;
    }
    bool ok;
    int source = QInputDialog::getInt(this, "Удаление ребра", "Введите начальную вершину:", 0, 0, graph->vertexCount - 1, 1, &ok);
    if (!ok)
        return;
    int destination = QInputDialog::getInt(this, "Удаление ребра", "Введите конечную вершину:", 0, 0, graph->vertexCount - 1, 1, &ok);
    if (!ok)
        return;
    graph->removeEdge(source, destination);
    graphWidget->update();
}

void MainWindow::runDijkstra()
{
    if (graph == nullptr)
    {
        QMessageBox::information(this, "Ошибка", "Сначала установите количество вершин");
        return;
    }
    bool ok;
    int source = QInputDialog::getInt(this, "Алгоритм Дейкстры", "Введите начальную вершину:", 0, 0, graph->vertexCount - 1, 1, &ok);
    if (!ok)
        return;

    vector<int> distances(graph->vertexCount, INF);
    distances[source] = 0;

    vector<bool> visited(graph->vertexCount, false);

    for (int i = 0; i < graph->vertexCount - 1; ++i)
    {
        int minDistance = INF;
        int minVertex = -1;

        for (int j = 0; j < graph->vertexCount; ++j)
        {
            if (!visited[j] && distances[j] < minDistance)
            {
                minDistance = distances[j];
                minVertex = j;
            }
        }

        if (minVertex == -1)
            break;

        visited[minVertex] = true;

        for (int j = 0; j < graph->vertexCount; ++j)
        {
            int weight = graph->adjacencyMatrix[minVertex][j];
            if (!visited[j] && weight != INF && distances[minVertex] + weight < distances[j])
                distances[j] = distances[minVertex] + weight;
        }
    }

    QString result;
    for (int i = 0; i < graph->vertexCount; ++i)
    {
        if (distances[i] == INF)
            result += QString::number(i) + ": INF\n";
        else
            result += QString::number(i) + ": " + QString::number(distances[i]) + "\n";
    }

    QMessageBox::information(this, "Алгоритм Дейкстры", result);
}
