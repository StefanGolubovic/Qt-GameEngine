#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QGraphicsView>
#include <QGroupBox>
#include <QtCore>
#include <QtGui>
#include <QTimer>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include <iostream>
#include <QTranslator>
#include "square.h"
#include "elipse.h"
#include "triangle.h"
#include "globalinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow* getUi () const;
    QString gen_random();
    QString currentID;
    GlobalInfo *globalInfo;

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_elipseButton_clicked();

    void on_squareButton_clicked();

    void on_triangleButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsItem *square;
    QGraphicsItem *elipse;
    QGraphicsItem *triangle;
    QTimer *timer;
};
#endif // MAINWINDOW_H
