#ifndef DTCCANERROR_H
#define DTCCANERROR_H

#include <QString>
#include <QDateTime>
#include <testigocontroller.h>

// Clase que guarda la información de un error DTC recibido a través de un bus CAN
class DTCCanError
{
public:
    int code;
    QDateTime date;
    QString description;
    QString category;
    QString equipment;
    TESTIGOS testigo;

public:
    DTCCanError(int code, QString category, QString equipment, QString description, QDateTime date, TESTIGOS testigo);

    static DTCCanError fromInt(int id);
};

#endif // DTCCANERROR_H
