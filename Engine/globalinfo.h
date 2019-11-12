#ifndef GLOBALINFO_H
#define GLOBALINFO_H

#include <QList>
#include <QLineEdit>
#include <QGroupBox>
#include <QSpinBox>


class GlobalInfo
{
public:
    GlobalInfo(QList<QLineEdit*> *gbLineEditsSquare, QList<QLineEdit*> *gbLineEditsElipse,
               QList<QLineEdit*> *gbLineEditsTriangle, QList<QGroupBox*> *gBoxes,
               QSpinBox *squareAngle, QSpinBox *elipseAngle, QSpinBox *triangleAngle);

    QList<QLineEdit*> *gbLineEditsSquare;
    QList<QLineEdit*> *gbLineEditsElipse;
    QList<QLineEdit*> *gbLineEditsTriangle;
    QSpinBox *squareAngle;
    QSpinBox *elipseAngle;
    QSpinBox *triangleAngle;
    QList<QGroupBox*> *gBoxes;
    QString currentID;

    void setID(QString id);
    QString getID();
};

#endif // GLOBALINFO_H
