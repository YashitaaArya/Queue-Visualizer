#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the graphics scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Connect buttons to slots
    connect(ui->pushButtonEnqueue, &QPushButton::clicked, this, &MainWindow::enqueue);
    connect(ui->pushButtonDequeue, &QPushButton::clicked, this, &MainWindow::dequeue);
    connect(ui->pushButtonClear, &QPushButton::clicked, this, &MainWindow::clearQueue);

    drawQueue(); // Draw initial empty queue
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Enqueue operation
void MainWindow::enqueue()
{
    QString value = ui->lineEditInput->text().trimmed();
    if(value.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a value to enqueue.");
        return;
    }

    queue.push(value);
    ui->lineEditInput->clear();
    drawQueue();
    ui->labelStatus->setText("Enqueued: " + value);
}

// Dequeue operation
void MainWindow::dequeue()
{
    if(queue.empty()) {
        QMessageBox::warning(this, "Warning", "Queue is empty. Cannot dequeue.");
        return;
    }

    QString value = queue.front();
    queue.pop();
    drawQueue();
    ui->labelStatus->setText("Dequeued: " + value);
}

// Clear the queue
void MainWindow::clearQueue()
{
    while(!queue.empty()) {
        queue.pop();
    }
    drawQueue();
    ui->labelStatus->setText("Queue cleared.");
}

// Draw the queue on the graphics scene
void MainWindow::drawQueue()
{
    scene->clear();

    if(queue.empty()) {
        scene->addText("Queue is empty")->setPos(50, 50);
        return;
    }

    // Draw rectangles and text for each element
    int boxWidth = 50;
    int boxHeight = 50;
    int spacing = 10;
    int x = 10;
    int y = 50;

    std::queue<QString> temp = queue;  // Copy to iterate

    while(!temp.empty()) {
        QString val = temp.front();
        temp.pop();

        QGraphicsRectItem *rect = scene->addRect(x, y, boxWidth, boxHeight);
        QGraphicsTextItem *text = scene->addText(val);
        text->setPos(x + boxWidth/4, y + boxHeight/4);

        x += boxWidth + spacing;
    }
}
