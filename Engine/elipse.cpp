#include "elipse.h"
#include <QDebug>

Elipse::Elipse(QGroupBox* gBoxElipse, QGroupBox* gBoxTriangle, QGroupBox* gBoxSquare, QList<QLineEdit *> *gbLineEdits, QSpinBox *spinAngle)
{
    this->gBoxElipse = gBoxElipse;
    this->gBoxTriangle = gBoxTriangle;
    this->gBoxSquare = gBoxSquare;
    this->gbLineEdits = gbLineEdits;
    this->spinAngle = spinAngle;
    scaleX = 1;
    scaleY = 1;
    angle = 0;

    pressed = false;
    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
}

QRectF Elipse::boundingRect() const
{
    return QRectF(10, 10, 100, 100);
}

void Elipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);
    if(pressed) {
        brush.setColor(Qt::red);
    }
    else {
        brush.setColor(Qt::green);
    }

    if (scene()->collidingItems(this).isEmpty()) {
        qDebug() << "No collision!";
    }
    else {
        //collision
        qDebug() << "Collision!";
    }

    location = this->pos();
    setTextGroupBox(gbLineEdits, location);



    painter->setBrush(brush);
    painter->drawEllipse(rec);
}

QPainterPath Elipse::shape() const
{
    QPainterPath path;
    path.addEllipse(QPointF(60, 60), 50, 50);
    return path;
}

void Elipse::setTextGroupBox(QList<QLineEdit *> *gbLineEdits, QPointF location)
{
    QLineEdit *line = gbLineEdits->at(0);
    line->setPlaceholderText(QString::number(location.rx()));
    line = gbLineEdits->at(1);
    line->setPlaceholderText(QString::number(location.ry()));
    line = gbLineEdits->at(2);
    line->setPlaceholderText(QString::number(scaleX));
    line = gbLineEdits->at(3);
    line->setPlaceholderText(QString::number(scaleY));
}

void Elipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    gBoxTriangle->hide();
    gBoxSquare->hide();
    gBoxElipse->show();
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Elipse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Elipse::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key is pressed";
    QLineEdit *lineX = gbLineEdits->at(0);
    QLineEdit *lineY = gbLineEdits->at(1);
    QLineEdit *lineScaleX = gbLineEdits->at(2);
    QLineEdit *lineScaleY = gbLineEdits->at(3);
    if (lineX->text() == "" || lineY->text() == "" || lineScaleX->text() == "" || lineScaleY->text() == ""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Please fill all fields !");
        msgBox.exec();
        return;
    }
    scaleX = qreal(lineScaleX->text().toFloat());
    scaleY = qreal(lineScaleY->text().toFloat());

    angle = spinAngle->text().toInt();

    this->setPos(qreal(lineX->text().toInt()), qreal(lineY->text().toInt()));
    this->update();
    QPointF location = this->pos();

    qDebug() << (location);
    QTransform t;
    t.translate(location.rx(), location.ry());
    t.rotate(qreal(angle));
    t.scale(scaleX, scaleY);
    t.translate(-location.rx(), -location.ry());
    this->setTransform(t);
    t.reset();

    lineX->clear();
    lineY->clear();

    lineScaleX->clear();
    lineScaleY->clear();
}
//override type
int Elipse::type() const {return 1;}
int Elipse::getAngle() const{
    return angle;
}
qreal Elipse::getScaleX() const{
    return scaleX;
}
qreal Elipse::getScaleY() const{
    return scaleY;
}
QPointF Elipse::getLocation() const{
    return location;
}
void Elipse::setScaleX(qreal scX){
    scaleX = scX;
}
void Elipse::setScaleY(qreal scY){
    scaleY = scY;
}
void Elipse::setLocation(QPointF loc){
    location = loc;
}
void Elipse::setAngle(int ang){
    angle = ang;
}
