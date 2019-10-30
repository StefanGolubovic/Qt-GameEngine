#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPoint>


class Triangle : public QGraphicsItem
{
public:
    Triangle();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<QPoint> points;
    QPoint point1;
    QPoint point2;
    QPoint point3;
    bool pressed;

};

#endif // TRIANGLE_H
