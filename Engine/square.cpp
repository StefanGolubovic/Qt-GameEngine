#include "square.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGroupBox>
#include <QString>
#include <QMessageBox>
#include <QTransform>

Square::Square(GlobalInfo *globalInfo, QString randomID)
{
    angle = 0;
    pressed = false;
    this->globalInfo = globalInfo;
    this->gBoxes = globalInfo->gBoxes;
    this->gbLineEdits = globalInfo->gbLineEditsSquare;
    this->squareAngle = globalInfo->squareAngle;
    scaleX = 1;
    scaleY = 1;
    this->randomID = randomID;

    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
}

QRectF Square::boundingRect() const
{
    return QRectF(10, 10, 100, 100);
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);
    if(pressed){
        brush.setColor(Qt::red);
    }
    else {
        brush.setColor(Qt::green);
    }
    QPointF location = this->pos();

    setTextGroupBox(gbLineEdits, squareAngle, this->pos());


    if (scene()->collidingItems(this).isEmpty()) {
//        qDebug() << "No collision!";
    }
    else {
        //collision
//        qDebug() << "Collision!";
    }

    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

void Square::setTextGroupBox(QList<QLineEdit *> *gbLineEdits, QSpinBox *spinAngle, QPointF location)
{
    QLineEdit *line = gbLineEdits->at(0);
    line->setPlaceholderText(QString::number(location.rx()));
    line = gbLineEdits->at(1);
    line->setPlaceholderText(QString::number(location.ry()));
    line = gbLineEdits->at(2);
    line->setPlaceholderText(QString::number(scaleX));
    line = gbLineEdits->at(3);
    line->setPlaceholderText(QString::number(scaleY));
}

void Square::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key is pressed";
    QLineEdit *lineX = gbLineEdits->at(0);
    QLineEdit *lineY = gbLineEdits->at(1);
    QLineEdit *lineScaleX = gbLineEdits->at(2);
    QLineEdit *lineScaleY = gbLineEdits->at(3);
    if (lineX->text() == "" || lineY->text() == "" || lineScaleX->text() == "" || lineScaleY->text() == ""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Please fill all fields !");
        msgBox.exec();
        return;
    }
    scaleX = qreal(lineScaleX->text().toFloat());
    scaleY = qreal(lineScaleY->text().toFloat());

    QSpinBox *spinBox = squareAngle;

    this->setPos(qreal(lineX->text().toInt()), qreal(lineY->text().toInt()));
    this->update();
    QPointF location = this->pos();

    qDebug() << (location);
    QTransform t;
    t.translate(location.rx(), location.ry());
    t.rotate(qreal(spinBox->text().toFloat()));
    t.scale(scaleX, scaleY);
    t.translate(-location.rx(), -location.ry());
    this->setTransform(t);
    t.reset();

    lineX->clear();
    lineY->clear();

    lineScaleX->clear();
    lineScaleY->clear();
}


void Square::advance(int phase)
{
    if(!phase){
        return;
    }
}

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    for(QGroupBox* box : *this->gBoxes) {
        if(box->title() != "Square Info") {
            box->hide();
        }
        else{
            box->show();
        }
    }

    globalInfo->currentID = this->randomID;
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Square::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
//override
int Square::type() const {return 2;}

qreal Square::getAngle() const{
    return angle;
}
qreal Square::getScaleX() const{
    return scaleX;
}
qreal Square::getScaleY() const{
    return scaleY;
}
qreal Square::getSpeed() const{
    return speed;
}
