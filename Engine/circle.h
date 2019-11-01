#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtMath>
#include <QGraphicsScene>

class Circle : public QGraphicsItem
{
public:
    Circle();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    bool pressed;
};

#endif // CIRCLE_H
