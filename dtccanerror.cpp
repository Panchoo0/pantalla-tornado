#include "dtccanerror.h"

DTCCanError::DTCCanError(int priority, QString category, QString from, QString description, QDateTime date) {
    this->priority = priority;
    this->category = category;
    this->from = from;
    this->description = description;
    this->date = date;
}

// Constructor que dado un id retorna toda la información de dicho error
DTCCanError DTCCanError::fromInt(int id) {
    int priority = 0;
    QString category;
    QString description;
    QString from;
    QDateTime date = QDateTime::currentDateTime();

    switch (id) {
    case 0:
        priority = 0;
        from = "DCDC 1";
        category = "Batería LV";
        description = "Low voltage battery voltage\n is over the threshold.\nGot to fault state  ( DCDC shut down)";
        break;
    case 1:
        priority = 0;
        from = "DCDC 1";
        category = "Batería LV";
        description = "Low voltage battery voltage\n is under the threshold.\nGot to fault state  ( DCDC shut down)";
        break;
    case 2:
        priority = 1;
        from = "DCDC 1";
        category = "Batería HV";
        description = "High voltage battery voltage\n is over the threshold.\nGot to fault state  ( DCDC shut down)";
        break;
    default:
        break;
    }
    return DTCCanError(
        priority,
        category,
        from,
        description,
        date
    );
}
