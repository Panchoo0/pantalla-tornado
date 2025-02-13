#ifndef DTCCANERROR_H
#define DTCCANERROR_H

#include <QString>
#include <QDateTime>

// Clase que guarda la información de un error DTC recibido a través de un bus CAN
class DTCCanError
{
public:
    int code;
    int priority;
    QDateTime date;
    QString description;
    QString category;
    QString from;

public:
    DTCCanError(int priority, QString category, QString from, QString description, QDateTime date);

    static DTCCanError fromInt(int id);
};

#endif // DTCCANERROR_H
