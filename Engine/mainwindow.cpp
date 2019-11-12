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

    //Initializing Square info for globaInfo object
    QList<QLineEdit*> *gbLineEditsSquare = new QList<QLineEdit*>;
    gbLineEditsSquare->append(ui->squareX);
    gbLineEditsSquare->append(ui->squareY);
    gbLineEditsSquare->append(ui->squareScaleX);
    gbLineEditsSquare->append(ui->squareScaleY);

    //Initializing Elipse info for globaInfo object
    QList<QLineEdit*> *gbLineEditsElipse = new QList<QLineEdit*>;
    gbLineEditsElipse->append(ui->elipseX);
    gbLineEditsElipse->append(ui->elipseY);
    gbLineEditsElipse->append(ui->elipseScaleX);
    gbLineEditsElipse->append(ui->elipseScaleY);

    //Initializing Triangle info for globaInfo object
    QList<QLineEdit*> *gbLineEditsTriangle = new QList<QLineEdit*>;
    gbLineEditsTriangle->append(ui->pOneLineX);
    gbLineEditsTriangle->append(ui->pOneLineY);
    gbLineEditsTriangle->append(ui->pTwoLineX);
    gbLineEditsTriangle->append(ui->pTwoLineY);
    gbLineEditsTriangle->append(ui->pThreeLineX);
    gbLineEditsTriangle->append(ui->pThreeLineY);
    gbLineEditsTriangle->append(ui->figureX);
    gbLineEditsTriangle->append(ui->figureY);

    //Initializing GroupBox info for globaInfo object
    QList<QGroupBox*> *gBoxes = new QList<QGroupBox*>;
    gBoxes->append(ui->groupBoxSquare);
    gBoxes->append(ui->groupBoxElipse);
    gBoxes->append(ui->groupBoxTriangle);

    //Initializing QSpinAngles info for globaInfo object


    this->globalInfo = new GlobalInfo(gbLineEditsSquare, gbLineEditsElipse, gbLineEditsTriangle,
                                      gBoxes, ui->squareAngle,ui->elipseAngle, ui->triangleAngle);

    scene = new QGraphicsScene(ui->mainScene);
    QGraphicsView *view = new QGraphicsView(scene);

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

        QString randomID = generateRandomID();

        square = new Square(globalInfo, randomID);
        square->setFocus();
        scene->addItem(square);
    }
    if(item->text(0) == "Elipse"){

        QString randomID = generateRandomID();

        elipse = new Elipse(globalInfo, randomID);

        elipse->setFocus();
        scene->addItem(elipse);
    }
    if(item->text(0) == "Triangle"){

        QString randomID = generateRandomID();

        triangle = new Triangle(globalInfo, randomID);
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

           elipse = new Elipse(globalInfo,it.toObject()["randomID"].toString());
           elipse->setFocus();
           elipse->setX(it.toObject()["locationX"].toDouble());
           elipse->setY(it.toObject()["locationY"].toDouble());
           scene->addItem(elipse);

       }else if(it.toObject()["name"].toString().compare("Square")==0){
           QList<QLineEdit*> *gbLineEdits = new QList<QLineEdit*>;
           gbLineEdits->append(ui->squareX);
           gbLineEdits->append(ui->squareY);
           gbLineEdits->append(ui->squareScaleX);
           gbLineEdits->append(ui->squareScaleY);

           square = new Square(globalInfo, it.toObject()["randomID"].toString());
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
           triangle = new Triangle(globalInfo, it.toObject()["randomID"].toString());
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

QString MainWindow::gen_random() {
    QString s = "";
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    int size = 12;
    for (int i = 0; i < size; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return s;
}

QString MainWindow::generateRandomID()
{
    QString randomID = gen_random();
    bool unique = true;
    while(true) {
        for(QGraphicsItem* item :scene->items()){
            if(item->type() == 1){
                Elipse* eObj = qgraphicsitem_cast<Elipse*>(item);
                if(eObj->randomID == randomID){
                    unique = false;
                }
            }
        }
        if(unique){
            break;
        }
        else{
            randomID = gen_random();
        }
    }

    return randomID;
}

void MainWindow::on_elipseButton_clicked()
{
//    qDebug() << globalInfo->currentID;
    for(QGraphicsItem* gi : ui->mainScene->items()) {
        if(gi->type() == 1) {
            Elipse* eObj = qgraphicsitem_cast<Elipse*>(gi);
            if(eObj->randomID == globalInfo->currentID){
                eObj->saveChanges();
            }
        }
    }
}

void MainWindow::on_squareButton_clicked()
{
//    qDebug() << globalInfo->currentID;

    for(QGraphicsItem* gi : ui->mainScene->items()) {
        if(gi->type() == 2) {
            Square* eObj = qgraphicsitem_cast<Square*>(gi);
            if(eObj->randomID == globalInfo->currentID){
                eObj->saveChanges();
            }
        }
    }
}

void MainWindow::on_triangleButton_clicked()
{
//    qDebug() << globalInfo->currentID;
    for(QGraphicsItem* gi : ui->mainScene->items()) {
        if(gi->type() == 3) {
            Triangle* eObj = qgraphicsitem_cast<Triangle*>(gi);
            if(eObj->randomID == globalInfo->currentID){
                eObj->saveChanges();
            }
        }
    }
}
