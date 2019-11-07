#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBoxSquare->hide();
    ui->groupBoxTriangle->hide();
    ui->mainScene->installEventFilter(this);

    scene = new QGraphicsScene(ui->mainScene);
    QGraphicsView *view = new QGraphicsView(scene);

//    view->show();

    view->setFixedSize(800, 600);

    ui->mainScene->setScene(scene);
    ui->mainScene->setSceneRect(0, 0, 5000, 500);
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
        gbLineEdits->append(ui->lineScaleX);
        gbLineEdits->append(ui->lineScaleY);
        QSpinBox *spinAngle = ui->spinBoxAngle;
        square = new Square(ui->groupBoxSquare, ui->groupBoxTriangle,gbLineEdits, spinAngle);
        square->setFocus();
        scene->addItem(square);
    }
    if(item->text(0) == "Circle"){
        circle = new Circle();
        scene->addItem(circle);
    }
    if(item->text(0) == "Triangle"){
        QList<QLineEdit*> *gbLineEdits = new QList<QLineEdit*>;
        gbLineEdits->append(ui->pOneLineX);
        gbLineEdits->append(ui->pOneLineY);
        gbLineEdits->append(ui->pTwoLineX);
        gbLineEdits->append(ui->pTwoLineY);
        gbLineEdits->append(ui->pThreeLineX);
        gbLineEdits->append(ui->pThreeLineY);
        gbLineEdits->append(ui->figureX);
        gbLineEdits->append(ui->figureY);

        triangle = new Triangle(ui->groupBoxTriangle, ui->groupBoxSquare, gbLineEdits);
        triangle->setFocus();
        scene->addItem(triangle);
    }

    if(item->text(0) == "Choose from default"){
        QString fileName = QFileDialog::getOpenFileName(this, tr("Choose File"),"../Qt-GameEngine/backgrounds/", tr("Images (*.png *.jpg)"));
        QPixmap pix(fileName);
        qDebug() << pix ;
        ui->mainScene->setBackgroundBrush(pix.scaled(ui->mainScene->width(),ui->mainScene->height(),  Qt::KeepAspectRatio));
    }

}
