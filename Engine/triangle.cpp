#include "triangle.h"
#include <QDebug>
#include <QMessageBox>

Triangle::Triangle(QGroupBox *gBoxTriangle,QGroupBox *gBoxSquare, QList<QLineEdit*> *gbLineEdits)
{
    pressed = false;

    this->gBoxTriangle = gBoxTriangle;
    this->gBoxSquare = gBoxSquare;
    this->gbLineEdits = gbLineEdits;
    point1.rx() = 10;
    point1.ry() = 10;
    point2.rx() = 10;
    point2.ry() = 100;
    point3.rx() = 100;
    point3.ry() = 10;

//    polygon << point1 << point2 << point3;

    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
}

QRectF Triangle::boundingRect() const
{
    return QRectF(10, 10, 200, 200);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygonF polygon;
    polygon << point1 << point2 << point3;

    if(pressed){
        painter->setBrush(Qt::red);
    }
    else{
        painter->setBrush(Qt::green);
    }

    qDebug() << this->pos();

    if (scene()->collidingItems(this).isEmpty()) {
//        qDebug() << "No collision!";
    }
    else {
        //collision
        qDebug() << "Collision!";
    }

    setTextGroupBox(gbLineEdits,point1, point2, point3, this->pos());

    painter->drawPolygon(polygon);
}



void Triangle::setTextGroupBox(QList<QLineEdit*> *gbLineEdits, QPointF p1, QPointF p2, QPointF p3, QPointF location)
{
    QLineEdit* line = gbLineEdits->at(0);
    line->setPlaceholderText(QString::number(p1.rx()));
    line = gbLineEdits->at(1);
    line->setPlaceholderText(QString::number(p1.ry()));
    line = gbLineEdits->at(2);
    line->setPlaceholderText(QString::number(p2.rx()));
    line = gbLineEdits->at(3);
    line->setPlaceholderText(QString::number(p2.ry()));
    line = gbLineEdits->at(4);
    line->setPlaceholderText(QString::number(p3.rx()));
    line = gbLineEdits->at(5);
    line->setPlaceholderText(QString::number(p3.ry()));
    line = gbLineEdits->at(6);
    line->setPlaceholderText(QString::number(location.rx()));
    line = gbLineEdits->at(7);
    line->setPlaceholderText(QString::number(location.ry()));
}

void Triangle::keyPressEvent(QKeyEvent *event)
{
    QLineEdit *p1lineX = gbLineEdits->at(0);
    QLineEdit *p1lineY = gbLineEdits->at(1);
    QLineEdit *p2lineX = gbLineEdits->at(2);
    QLineEdit *p2lineY = gbLineEdits->at(3);
    QLineEdit *p3lineX = gbLineEdits->at(4);
    QLineEdit *p3lineY = gbLineEdits->at(5);

    QLineEdit *figureX = gbLineEdits->at(6);
    QLineEdit *figureY = gbLineEdits->at(7);

    if (p1lineX->text() == "" || p1lineY->text() == "" || p2lineX->text() == ""
            || p2lineY->text() == "" || p3lineX->text() == "" || p3lineY->text() == ""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Please fill all fields !");
        msgBox.exec();
        return;
    }

    this->setPos(qreal(figureX->text().toInt()), qreal(figureY->text().toInt()));
    this->update();

    point1.setX(p1lineX->text().toInt());
    point1.setY(p1lineY->text().toInt());
    point2.setX(p2lineX->text().toInt());
    point2.setY(p2lineY->text().toInt());
    point3.setX(p3lineX->text().toInt());
    point3.setY(p3lineY->text().toInt());

    p1lineX->clear();
    p1lineY->clear();
    p2lineX->clear();
    p2lineY->clear();
    p3lineX->clear();
    p3lineY->clear();
    figureX->clear();
    figureY->clear();
}

QPainterPath Triangle::shape() const
{

    QPolygonF polygon;
    polygon << point1 << point2 << point3;
    QPainterPath path;
    path.addPolygon(polygon);
    return path;
}

void Triangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    gBoxSquare->hide();
    gBoxTriangle->show();
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Triangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
