#include "candata.h"

CANData::CANData() {
    this->speed = 0;
    this->batTemp = 0;
    this->inversorTemp = 0;
    this->engineTemp = 0;
    this->bat = 0;
}

// Dado el id de un error lo agrega a los errores DTC recibidos por el bus CAN
void CANData::addError(int id) {
    DTCCanError error = DTCCanError::fromInt(id);
    this->canErrors.push_back(error);
}

CANData::~CANData (){

}
