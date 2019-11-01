#include "square.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGroupBox>
#include <QString>

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
    line->setPlaceholderText(QString::number(scale));
}

void Square::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key is pressed";
    QLineEdit *lineX = gbLineEdits->at(0);
    QLineEdit *lineY = gbLineEdits->at(1);
    QLineEdit *lineScale = gbLineEdits->at(2);
    this->setPos(lineX->text().toInt(), lineY->text().toInt());
    scale = lineScale->text().toFloat();
    this->setScale(scale);
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
    qDebug() << "Focused" << this->pos();
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
