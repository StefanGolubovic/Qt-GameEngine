#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QPen>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->mainScene->setScene(scene);
    ui->mainScene->setRenderHint(QPainter::Antialiasing);
//    scene->setSceneRect(-200, -200, 300, 300);

//    QPen pen = QPen(Qt::red);
//    QLineF topLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
//    QLineF leftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
//    QLineF rightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
//    QLineF bottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

//    scene->addLine(topLine, pen);
//    scene->addLine(leftLine, pen);
//    scene->addLine(rightLine, pen);
//    scene->addLine(bottomLine, pen);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(100);


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
