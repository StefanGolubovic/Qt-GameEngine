#include "globalinfo.h"

GlobalInfo::GlobalInfo(QList<QLineEdit*> *gbLineEditsSquare, QList<QLineEdit*> *gbLineEditsElipse,
                       QList<QLineEdit*> *gbLineEditsTriangle, QList<QGroupBox*> *gBoxes,
                       QSpinBox *squareAngle, QSpinBox *elipseAngle, QSpinBox *triangleAngle)
{
    this->gbLineEditsSquare = gbLineEditsSquare;
    this->gbLineEditsElipse = gbLineEditsElipse;
    this->gbLineEditsTriangle = gbLineEditsTriangle;
    this->squareAngle = squareAngle;
    this->elipseAngle = elipseAngle;
    this->triangleAngle = triangleAngle;
    this->gBoxes = gBoxes;

    this->currentID = "";
}

void GlobalInfo::setID(QString id)
{
    this->currentID = id;
}

QString GlobalInfo::getID()
{
    return this->currentID;
}
