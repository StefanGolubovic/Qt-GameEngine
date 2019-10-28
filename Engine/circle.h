#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtMath>

class Circle : public QGraphicsItem
{
public:
    Circle();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QPainterPath shape() const override;

    bool pressed;

private:
    double pos_x = 100;
    double pos_y = 100;
    double size = 100;


};

#endif // CIRCLE_H
