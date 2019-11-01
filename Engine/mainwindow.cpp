#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->hide();
    ui->mainScene->installEventFilter(this);

    scene = new QGraphicsScene(this);
    ui->mainScene->setScene(scene);
    ui->mainScene->setRenderHint(QPainter::Antialiasing);

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

        QList<QLineEdit*> *gbLineEdits = new QList<QLineEdit*>;
        gbLineEdits->append(ui->lineX);
        gbLineEdits->append(ui->lineY);
        gbLineEdits->append(ui->lineSize);
        QSpinBox *spinAngle = ui->spinBoxAngle;
        square = new Square(ui->groupBox,gbLineEdits, spinAngle);
        square->setFocus();
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
