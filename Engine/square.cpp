#include "square.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGroupBox>
#include <QString>
#include <QMessageBox>
#include <QTransform>

Square::Square(QGroupBox* gbox, QList<QLineEdit*> *gbLineEdits, QSpinBox *spinAngle)
{
    angle = 0;
    setRotation(angle);
    speed = 5;
    pressed = false;
    this->gBox = gbox;
    this->gbLineEdits = gbLineEdits;
    this->spinAngle = spinAngle;
    scale = 1;
    scaleX = 1;
    scaleY = 1;
    this->setScale(scale);

    int startX = 0;
    int startY = 0;

    setPos(startX, startY);
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

    setTextGroupBox(gbLineEdits, spinAngle, this->pos());


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
    this->setPos(lineX->text().toInt(), lineY->text().toInt());
    lineX->clear();
    lineY->clear();
    QSpinBox *spinBox = spinAngle;
    this->setRotation(spinBox->text().toInt());
//    scale = qreal(lineScale->text().toFloat());
    QTransform transform = this->transform().scale(qreal(lineScaleX->text().toFloat()),qreal(lineScaleY->text().toFloat()));
    this->setTransform(transform);
    this->update();
//    this->setScale(scale);
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
    gBox->show();
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
