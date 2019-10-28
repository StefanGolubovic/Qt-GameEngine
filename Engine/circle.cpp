#include "circle.h"

Circle::Circle()
{
    pressed = false;
    setFlag(ItemIsMovable);
}

QRectF Circle::boundingRect() const
{
    return shape().boundingRect();
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::black);

    if(pressed) {
        brush.setColor(Qt::red);
    }
    else {
        brush.setColor(Qt::green);
    }

    painter->fillRect(rec, brush);
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

QPainterPath Circle::shape() const
{
    QPainterPath path;
    QLineF line = QLineF(pos_x, pos_y, pos_x + 100, pos_y + 100);
            qreal radAngle = line.angle() * M_PI / 180;
            qreal selectionOffset = 3;
            qreal dx = selectionOffset * sin(radAngle);
            qreal dy = selectionOffset * cos(radAngle);
            QPointF offset1 = QPointF(dx, dy);
            QPointF offset2 = QPointF(-dx, -dy);
            path.moveTo(line.p1() + offset1);
            path.lineTo(line.p1() + offset2);
            path.lineTo( line.p2() + offset2);
            path.lineTo( line.p2() + offset1);

    return path;
}
