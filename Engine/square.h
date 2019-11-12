#ifndef SQUARE_H
#define SQUARE_H
#include "globalinfo.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>

class Square : public QGraphicsItem
{
public:
    Square(GlobalInfo *globalInfo, QString randomID);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    bool pressed;
    QList<QLineEdit*> *gbLineEdits;
    QSpinBox *squareAngle;
    QString randomID;
    GlobalInfo *globalInfo;
    QList<QGroupBox*> *gBoxes;

    void setTextGroupBox(QList<QLineEdit*> *gbLineEdits, QSpinBox *spinAngle, QPointF location);
    int type() const override;//dodali
    qreal getScaleX() const;
    qreal getScaleY() const;
    qreal getSpeed() const;
    qreal getAngle() const;

private:
    qreal scaleX, scaleY;
    qreal angle;
    qreal speed;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // SQUARE_H
