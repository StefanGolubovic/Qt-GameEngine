#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QtCore>
#include <QtGui>
#include <QTimer>
#include "square.h"
#include "circle.h"
#include "triangle.h"

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
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsItem *square;
    QGraphicsItem *circle;
    QGraphicsItem *triangle;
    QTimer *timer;

};
#endif // MAINWINDOW_H
