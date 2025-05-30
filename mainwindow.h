#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <queue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void enqueue();
    void dequeue();
    void clearQueue();

private:
    Ui::MainWindow *ui;
    std::queue<QString> queue;        // Store queue elements as strings
    QGraphicsScene *scene;            // For visualization

    void drawQueue();
};

#endif // MAINWINDOW_H
