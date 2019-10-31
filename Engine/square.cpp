#include "square.h"
#include <QRandomGenerator>
#include <QDebug>

Square::Square()
{
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
    angle = (qrand() % 360 );
    setRotation(angle);
    speed = 5;
    pressed = false;

    int startX = 0;
    int startY = 0;

    setPos(startX, startY);
    setFlag(ItemIsMovable);
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

    if (scene()->collidingItems(this).isEmpty()) {
        qDebug() << "No collision!";
    }
    else {
        //collision
        qDebug() << "Collision!";
    }



    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

void Square::advance(int phase)
{
    if(!phase){
        return;
    }

    QPointF location = this->pos();

    setPos(mapToParent(0, (-speed)));



}

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
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
