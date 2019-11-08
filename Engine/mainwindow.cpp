#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sceneloader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBoxSquare->hide();
    ui->groupBoxTriangle->hide();
    ui->groupBoxElipse->hide();
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

        square = new Square(ui->groupBoxSquare, ui->groupBoxTriangle, ui->groupBoxElipse,gbLineEdits, ui->spinBoxAngle);
        square->setFocus();
        scene->addItem(square);
    }
    if(item->text(0) == "Elipse"){

        QList<QLineEdit*> *gbLineEdits = new QList<QLineEdit*>;
        gbLineEdits->append(ui->elipseX);
        gbLineEdits->append(ui->elipseY);
        gbLineEdits->append(ui->elipseScaleX);
        gbLineEdits->append(ui->elipseScaleY);

        elipse = new Elipse(ui->groupBoxElipse,ui->groupBoxTriangle, ui->groupBoxSquare, gbLineEdits, ui->elipseAngle);
        elipse->setFocus();
        scene->addItem(elipse);
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

        triangle = new Triangle(ui->groupBoxTriangle, ui->groupBoxSquare, ui->groupBoxElipse, gbLineEdits, ui->spinBoxTriangle);
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

void MainWindow::on_actionSave_triggered()
{
    SceneLoader* s = new SceneLoader();
    s->sceneSave(scene);
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, QObject::tr("Choose File"),"../Qt-GameEngine/");
    SceneLoader* s = new SceneLoader();
    scene->clear();
    QJsonArray list = s->sceneLoad(fileName);
    for(auto it : list){
       if(it.toObject()["name"].toString().compare("Elipse")==0){
           QList<QLineEdit*> *gbLineEdits = new QList<QLineEdit*>;
           gbLineEdits->append(ui->elipseX);
           gbLineEdits->append(ui->elipseY);
           gbLineEdits->append(ui->elipseScaleX);
           gbLineEdits->append(ui->elipseScaleY);

           elipse = new Elipse(ui->groupBoxElipse,ui->groupBoxTriangle, ui->groupBoxSquare, gbLineEdits, ui->elipseAngle);
           elipse->setFocus();
           elipse->setX(it.toObject()["locationX"].toDouble());
           elipse->setY(it.toObject()["locationY"].toDouble());
           scene->addItem(elipse);

       }else if(it.toObject()["name"].toString().compare("Square")==0){
           QList<QLineEdit*> *gbLineEdits = new QList<QLineEdit*>;
           gbLineEdits->append(ui->lineX);
           gbLineEdits->append(ui->lineY);
           gbLineEdits->append(ui->lineScaleX);
           gbLineEdits->append(ui->lineScaleY);

           square = new Square(ui->groupBoxSquare, ui->groupBoxTriangle, ui->groupBoxElipse,gbLineEdits, ui->spinBoxAngle);
           square->setFocus();
           square->setX(it.toObject()["locationX"].toDouble());
           square->setY(it.toObject()["locationY"].toDouble());
           scene->addItem(square);

       }else if(it.toObject()["name"].toString().compare("Triangle")==0){
           QList<QLineEdit*> *gbLineEdits = new QList<QLineEdit*>;
           gbLineEdits->append(ui->pOneLineX);
           gbLineEdits->append(ui->pOneLineY);
           gbLineEdits->append(ui->pTwoLineX);
           gbLineEdits->append(ui->pTwoLineY);
           gbLineEdits->append(ui->pThreeLineX);
           gbLineEdits->append(ui->pThreeLineY);
           gbLineEdits->append(ui->figureX);
           gbLineEdits->append(ui->figureY);

           triangle = new Triangle(ui->groupBoxTriangle, ui->groupBoxSquare, ui->groupBoxElipse, gbLineEdits, ui->spinBoxTriangle);
           triangle->setFocus();
           triangle->setX(it.toObject()["locationX"].toDouble());
           triangle->setY(it.toObject()["locationY"].toDouble());
           scene->addItem(triangle);

       }

    }
}
Ui::MainWindow* MainWindow::getUi () const{
    return ui;
}
