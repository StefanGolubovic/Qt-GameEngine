#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

class Square : public QGraphicsItem
{
public:
    Square();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    bool pressed;

protected:
    qreal angle;
    qreal speed;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SQUARE_H
