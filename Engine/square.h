#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>

class Square : public QGraphicsItem
{
public:
    Square(QGroupBox* gbox, QList<QLineEdit*> *gbLineEdits, QSpinBox *spinAngle);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    bool pressed;
    QGroupBox* gBox;
    QList<QLineEdit*> *gbLineEdits;
    QSpinBox *spinAngle;
    void setTextGroupBox(QList<QLineEdit*> *gbLineEdits, QSpinBox *spinAngle, QPointF location);

protected:
    qreal scaleX, scaleY;
    qreal angle;
    qreal speed;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // SQUARE_H
