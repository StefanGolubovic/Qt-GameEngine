#ifndef ELIPSE_H
#define ELIPSE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtMath>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QMessageBox>

class Elipse : public QGraphicsItem
{

//ui->groupBoxElipse,ui->groupBoxTriangle, ui->groupBoxSquare, gbLineEdits, ui->elipseAngle
public:
    Elipse(QGroupBox* gBoxElipse, QGroupBox* gBoxTriangle, QGroupBox* gBoxSquare, QList<QLineEdit *> *gbLineEdits, QSpinBox *spinAngle);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QPainterPath shape() const override;
    void setTextGroupBox(QList<QLineEdit*> *gbLineEdits, QPointF location);

    QGroupBox* gBoxElipse;
    QGroupBox* gBoxTriangle;
    QGroupBox* gBoxSquare;
    QList<QLineEdit*> *gbLineEdits;


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    int type() const override;//dodali
    int getAngle() const;
    QSpinBox* getSpinAngle() const;
    qreal getScaleX() const;
    qreal getScaleY() const;
    QPointF getLocation() const;
    void setScaleX(qreal scX);
    void setScaleY(qreal scY);
    void setLocation(QPointF loc);
    void setAngle(int ang);

private:
    QSpinBox *spinAngle;
    int angle;
    qreal scaleX;
    qreal scaleY;
    QPointF location;
    bool pressed;
};

#endif
