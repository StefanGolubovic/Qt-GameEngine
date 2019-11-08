#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPoint>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>


class Triangle : public QGraphicsItem
{
public:
    Triangle(QGroupBox *gBoxTriangle,QGroupBox *gBoxSquare, QGroupBox* gBoxElipse, QList<QLineEdit*> *gbLineEdits, QSpinBox *spinBoxTriangle);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;


    void setTextGroupBox(QList<QLineEdit*> *gbLineEdits, QPointF p1, QPointF p2, QPointF p3, QPointF location);

    QGroupBox *gBoxTriangle;
    QGroupBox *gBoxSquare;
    QGroupBox *gBoxElipse;
    QList<QLineEdit*> *gbLineEdits;
    QSpinBox *spinBoxTriangle;
    int type() const override;//dodali
    QPoint getPoint1() const;
    QPoint getPoint2() const;
    QPoint getPoint3() const;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    QPainterPath shape() const override;

    QList<QPoint> points;
    QPoint point1;
    QPoint point2;
    QPoint point3;
    bool pressed;

};

#endif // TRIANGLE_H
