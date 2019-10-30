#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QImage>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->mainScene->setScene(scene);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(item->text(0) == "Square"){
        square = new Square();
        scene->addItem(square);
    }
    if(item->text(0) == "Circle"){
        circle = new Circle();
        scene->addItem(circle);
    }
    if(item->text(0) == "Triangle"){
        triangle = new Triangle();
        scene->addItem(triangle);
    }

    if(item->text(0) == "Choose from default"){

        QString fileName = QFileDialog::getOpenFileName(this, tr("Choose File"),"../Qt-GameEngine/backgrounds/", tr("Images (*.png *.jpg)"));
        QPixmap pix(fileName);
        qDebug() << pix ;
        ui->mainScene->setBackgroundBrush(pix.scaled(ui->mainScene->width(),ui->mainScene->height(),  Qt::KeepAspectRatio));
    }
}
