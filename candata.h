#ifndef CANDATA_H
#define CANDATA_H

#include <QObject>
#include "dtccanerror.h"

// Clase cuya función es almacenar todos los datos actualizados obtenidos a través del bus CAN
class CANData
{
public:
    int speed;
    int batTemp;
    int inversorTemp;
    int engineTemp;
    int bat;

    std::vector<DTCCanError> canErrors;
    CANData();
    void addError(int id);
    ~CANData();

signals:
    void valueChanged();

};

#endif // CANDATA_H
