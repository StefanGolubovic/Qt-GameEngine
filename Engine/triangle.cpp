#include "triangle.h"

Triangle::Triangle()
{
    pressed = false;
    setFlag(ItemIsMovable);
}

QRectF Triangle::boundingRect() const
{
    return QRectF(10, 10, 100, 100);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(10,10) << QPoint(10,100) << QPoint(100,10);
    if(pressed){
        painter->setBrush(Qt::red);
    }
    else{
        painter->setBrush(Qt::green);
    }

    painter->drawPolygon(polygon);
}

void Triangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Triangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
