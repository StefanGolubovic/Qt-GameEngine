#include "circle.h"
#include <QDebug>

Circle::Circle()
{
    pressed = false;
    setFlag(ItemIsMovable);
}

QRectF Circle::boundingRect() const
{
    return QRectF(10, 10, 100, 100);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);
    if(pressed) {
        brush.setColor(Qt::red);
    }
    else {
        brush.setColor(Qt::green);
    }

    if (!scene()->items().isEmpty()){
        qDebug() << scene()->items().at(0)->pos();
    }

    painter->drawEllipse(rec);
}

void Circle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Circle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

