#include "candata.h"
#include <utils.h>
#include <bits/stdc++.h>
#include <QDebug>

CANData::CANData() {
}

// Función para recibir un mensaje proveniente del socket conectado con el bus CAN
// Actualiza la información del objeto en función del mensaje
// Emite una señal para indicar el tipo de mensaje recibido y actualizar la información según corresponda
void CANData::receiveMessage(unsigned char sourceAddress, unsigned int pgn, uint8_t* receivedData) {

    switch (pgn) {
    case 0x100: {
        batteryCurrent = Utils::getShiftedData(0, 16, receivedData);
        batteryVoltage = Utils::getShiftedData(16, 16, receivedData);
        SOC = Utils::getShiftedData(32, 8, receivedData);

        emit message1();
        break;
    }
    case 0x200: {
        engineCurrent = Utils::getShiftedData(0, 12, receivedData);
        engineTorque = Utils::getShiftedData(12, 12, receivedData);
        engineVoltage = Utils::getShiftedData(24, 12, receivedData);
        rpm = Utils::getShiftedData(36, 12, receivedData);
        setpoint = Utils::getShiftedData(48, 16, receivedData);

        emit message2();
        break;
    }
    case 0x300: {
        engineTemp = Utils::getShiftedData(0, 8, receivedData);
        inversorTemp = Utils::getShiftedData(8, 8, receivedData);
        batTemp = Utils::getShiftedData(16, 8, receivedData);
        batMaxTemp = Utils::getShiftedData(24, 8, receivedData);
        batMinTemp = Utils::getShiftedData(32, 8, receivedData);

        emit message3();
        break;
    }
    case 0x400: {
        dcdc1Current = Utils::getShiftedData(0, 16, receivedData);
        dcdc2Current = Utils::getShiftedData(16, 16, receivedData);
        dcdc1HVCurrent = Utils::getShiftedData(32, 16, receivedData);
        dcdc2HVCurrent = Utils::getShiftedData(48, 16, receivedData);

        emit message4();
        break;
    }
    case 0x500: {
        dcdc1OutputVoltage = Utils::getShiftedData(0, 16, receivedData);
        dcdc2OutputVoltage = Utils::getShiftedData(16, 16, receivedData);
        dcdc1InputVoltage = Utils::getShiftedData(32, 16, receivedData);
        dcdc2InputVoltage = Utils::getShiftedData(48, 16, receivedData);

        emit message5();
        break;
    }
    case 0x600: {
        posResistanceSIM100 = Utils::getShiftedData(0, 16, receivedData);
        negResistanceSIM100 = Utils::getShiftedData(16, 16, receivedData);
        posResistanceBMU = Utils::getShiftedData(32, 16, receivedData);
        negResistanceBMU = Utils::getShiftedData(48, 16, receivedData);

        emit message6();
        break;
    }
    case 0x700: {
        lvError = Utils::getShiftedData(0, 4, receivedData);
        hvError = Utils::getShiftedData(4, 4, receivedData);

        state = Utils::getShiftedData(8, 4, receivedData);

        inhibitState = Utils::getShiftedData(12, 1, receivedData);
        busHVDischarged = Utils::getShiftedData(13, 1, receivedData);
        pduContactorClose = Utils::getShiftedData(14, 1, receivedData);
        hvOn = Utils::getShiftedData(15, 1, receivedData);
        lvHigh = Utils::getShiftedData(16, 2, receivedData);
        dcdc1Overtemp = Utils::getShiftedData(18, 1, receivedData);
        dcdc2Overtemp = Utils::getShiftedData(19, 1, receivedData);
        atsFanFault = Utils::getShiftedData(20, 1, receivedData);
        atsPumpFault =Utils::getShiftedData(21, 1, receivedData);
        edsOvertemp = Utils::getShiftedData(22, 1, receivedData);
        obcOvertemp = Utils::getShiftedData(23, 1, receivedData);
        edsInError = Utils::getShiftedData(24, 1, receivedData);
        edsCouldntClear = Utils::getShiftedData(25, 1, receivedData);
        dcdcHighDifference = Utils::getShiftedData(26, 1, receivedData);
        batModule1 = Utils::getShiftedData(27, 1, receivedData);
        batModule2 = Utils::getShiftedData(28, 1, receivedData);
        batModule3 = Utils::getShiftedData(29, 1, receivedData);
        batModule4 = Utils::getShiftedData(30, 1, receivedData);
        contactorPdu = Utils::getShiftedData(31, 1, receivedData);
        sim100Stucked = Utils::getShiftedData(32, 1, receivedData);
        couldntPowerOnBMS = Utils::getShiftedData(33, 1, receivedData);
        bessPowerOffHv = Utils::getShiftedData(34, 1, receivedData);
        requiredHvOff = Utils::getShiftedData(35, 1, receivedData);
        pedal2Anormal = Utils::getShiftedData(36, 1, receivedData);
        pedal1Anormal = Utils::getShiftedData(37, 1, receivedData);
        hvilPdu = Utils::getShiftedData(38, 1, receivedData);
        hvilObc = Utils::getShiftedData(39, 1, receivedData);
        hvilEds = Utils::getShiftedData(40, 1, receivedData);
        hvilDddc= Utils::getShiftedData(41, 1, receivedData);
        termistorLVOutOfRange = Utils::getShiftedData(42, 1, receivedData);
        termistorHVOutOfRange = Utils::getShiftedData(43, 1, receivedData);
        pduTempExcess = Utils::getShiftedData(44, 1, receivedData);
        overturn = Utils::getShiftedData(45, 1, receivedData);
        doorOpen = Utils::getShiftedData(46, 1, receivedData);
        parkingState = Utils::getShiftedData(47, 1, receivedData);
        estadoMarcha = Utils::getShiftedData(48, 2, receivedData);

        emit message7();
        break;
    }

    case 0xC100: {
        int trama = Utils::getShiftedData(0, 16, receivedData);
        voltageCells[trama * 3] = Utils::getShiftedData(16, 16, receivedData);
        voltageCells[trama * 3 + 1]  = Utils::getShiftedData(32, 16, receivedData);
        voltageCells[trama * 3 + 2]  = Utils::getShiftedData(48, 16, receivedData);

        emit bess1(trama);
        break;
    }
    case 0xC200: {
        int trama = Utils::getShiftedData(0, 16, receivedData);
        tempCells[trama * 6] = Utils::getShiftedData(16, 8, receivedData);
        tempCells[trama * 6 + 1]  = Utils::getShiftedData(24, 8, receivedData);
        tempCells[trama * 6 + 2]  = Utils::getShiftedData(32, 8, receivedData);
        tempCells[trama * 6 + 3]  = Utils::getShiftedData(40, 8, receivedData);
        tempCells[trama * 6 + 4]  = Utils::getShiftedData(48, 8, receivedData);
        tempCells[trama * 6 + 5]  = Utils::getShiftedData(56, 8, receivedData);

        emit bess2(trama);
        break;
    }
    case 0xC300: {
        chargeEnergyAcumulated = Utils::getShiftedData(0, 24, receivedData);
        dischargeEnergyAcumulated = Utils::getShiftedData(24, 24, receivedData);
        energyOneCharge = Utils::getShiftedData(48, 16, receivedData);

        emit bess3();
        break;
    }
    case 0xC400: {
        // TODO: revisar este SOC con el otro y ver cual es el de verdad
        SOC = Utils::getShiftedData(0, 8, receivedData);
        SOH = Utils::getShiftedData(8, 8, receivedData);
        maxVoltage = Utils::getShiftedData(16, 16, receivedData);
        minVoltage = Utils::getShiftedData(32, 16, receivedData);
        meanVoltage = Utils::getShiftedData(48, 16, receivedData);

        emit bess4();
        break;
    }
    case 0xC500: {
        posChargeTempDC = Utils::getShiftedData(0, 8, receivedData);
        negChargeTempDC = Utils::getShiftedData(8, 8, receivedData);
        dcConected = Utils::getShiftedData(16, 2, receivedData);
        bmsChargingMode = Utils::getShiftedData(18, 2, receivedData);
        heatState = Utils::getShiftedData(20, 1, receivedData);
        coolingState = Utils::getShiftedData(21, 1, receivedData);
        bmuContactor = Utils::getShiftedData(22, 2, receivedData);
        bmsFailures = Utils::getShiftedData(24, 8, receivedData);

        emit bess5();
        break;
    }
    case 0xC600: {
        edsFailures = Utils::getShiftedData(0, 8, receivedData);
        dcdc1Failures = Utils::getShiftedData(8, 8, receivedData);
        dcdc2Failures = Utils::getShiftedData(16, 8, receivedData);
        sim100Failures = Utils::getShiftedData(24, 8, receivedData);
        obcFailures = Utils::getShiftedData(32, 8, receivedData);
        emixFailures = Utils::getShiftedData(40, 8, receivedData);

        emit emix1();
        break;
    }
    case 0xD000: {
        dcdc1ErrorCode = Utils::getShiftedData(0, 16, receivedData);
        dcdc2ErrorCode = Utils::getShiftedData(16, 16, receivedData);

        emit faults1();

        break;
    }
    case 0xD100: {
        edsErrorCode = Utils::getShiftedData(0, 16, receivedData);
        obcErrorCode = Utils::getShiftedData(16, 16, receivedData);

        emit faults2();
        break;
    }
    default:
        break;
    }

}

// Dado el id de un error lo agrega a los errores DTC recibidos por el bus CAN
void CANData::addError(int id) {
    DTCCanError error = DTCCanError::fromInt(id);
    this->canErrors.push_back(error);
}

CANData* CANData::clone() {
    CANData* data = new CANData();

    data->speed = this->speed;

    // Message 1
    data->batteryCurrent = this->batteryCurrent;
    data->batteryVoltage = this->batteryVoltage;
    data->SOC = this->SOC;

    // Message 2
    data->engineCurrent = this->engineCurrent;
    data->engineTorque = this->engineTorque;
    data->engineVoltage = this->engineVoltage;
    data->rpm = this->rpm;
    data->setpoint = this->setpoint;

    // Message 3
    data->engineTemp = this->engineTemp;
    data->inversorTemp = this->inversorTemp;
    data->batTemp = this->batTemp;
    data->batMaxTemp = this->batMaxTemp;
    data->batMinTemp = this->batMinTemp;

    // Message 4
    data->dcdc1Current = this->dcdc1Current;
    data->dcdc2Current = this->dcdc2Current;
    data->dcdc1HVCurrent = this->dcdc1HVCurrent;
    data->dcdc2HVCurrent = this->dcdc2HVCurrent;

    // Message 5
    data->dcdc1OutputVoltage = this->dcdc1OutputVoltage;
    data->dcdc2OutputVoltage = this->dcdc2OutputVoltage;
    data->dcdc1InputVoltage = this->dcdc1InputVoltage;
    data->dcdc2InputVoltage = this->dcdc2InputVoltage;

    // Message 6
    data->posResistanceSIM100 = this->posResistanceSIM100;
    data->negResistanceSIM100 = this->negResistanceSIM100;
    data->posResistanceBMU = this->posResistanceBMU;
    data->negResistanceBMU = this->negResistanceBMU;

    // Message 7
    data->lvError = this->lvError;
    data->hvError = this->hvError;

    data->state = this->state;

    data->inhibitState = this->inhibitState;
    data->busHVDischarged = this->busHVDischarged;
    data->pduContactorClose = this->pduContactorClose;

    data->hvOn = this->hvOn;
    data->lvHigh = this->lvHigh;

    data->dcdc1Overtemp = this->dcdc1Overtemp;
    data->dcdc2Overtemp = this->dcdc2Overtemp;

    data->atsFanFault = this->atsFanFault;
    data->atsPumpFault = this->atsPumpFault;

    data->edsOvertemp = this->edsOvertemp;
    data->obcOvertemp = this->obcOvertemp;

    data->edsInError = this->edsInError;
    data->edsCouldntClear = this->edsCouldntClear;

    data->dcdcHighDifference = this->dcdcHighDifference;

    data->batModule1 = this->batModule1;
    data->batModule2 = this->batModule2;
    data->batModule3 = this->batModule3;
    data->batModule4 = this->batModule4;

    data->contactorPdu = this->contactorPdu;
    data->sim100Stucked = this->sim100Stucked;

    data->couldntPowerOnBMS = this->couldntPowerOnBMS;

    data->bessPowerOffHv = this->bessPowerOffHv;
    data->requiredHvOff = this->requiredHvOff;

    data->pedal1Anormal = this->pedal1Anormal;
    data->pedal2Anormal = this->pedal2Anormal;

    data->hvilPdu = this->hvilPdu;
    data->hvilObc = this->hvilObc;
    data->hvilEds = this->hvilEds;
    data->hvilDddc = this->hvilDddc;

    data->termistorLVOutOfRange = this->termistorLVOutOfRange;
    data->termistorHVOutOfRange = this->termistorHVOutOfRange;

    data->pduTempExcess = this->pduTempExcess;
    data->overturn = this->overturn;
    data->doorOpen = this->doorOpen;
    data->parkingState = this->parkingState;
    data->estadoMarcha = this->estadoMarcha;

    // Bess1
    for (int i = 0; i < 194 * 3;  i++) {
        data->voltageCells[i] = this->voltageCells[i];
    }

    // Bess2
    for (int i = 0; i < 18 * 6; i++) {
        data->tempCells[i] = this->tempCells[i];
    }

    // Bess3
    data->chargeEnergyAcumulated = this->chargeEnergyAcumulated;
    data->dischargeEnergyAcumulated = this->dischargeEnergyAcumulated;
    data->energyOneCharge = this->energyOneCharge;

    // Bess4
    data->SOH = this->SOH;
    data->minVoltage = this->minVoltage;
    data->maxVoltage = this->maxVoltage;
    data->meanVoltage = this->meanVoltage;

    // Bess5
    data->posChargeTempDC = this->posChargeTempDC;
    data->negChargeTempDC = this->negChargeTempDC;
    data->dcConected = this->dcConected;

    data->bmsChargingMode = this->bmsChargingMode;
    data->coolingState = this->coolingState;
    data->heatState = this->heatState;

    data->bmuContactor = this->bmuContactor;
    data->bmsFailures = this->bmsFailures;

    // Emix1
    data->edsFailures  = this->edsFailures;
    data->dcdc1Failures = this->dcdc1Failures;
    data->dcdc2Failures = this->dcdc2Failures;
    data->sim100Failures = this->sim100Failures;
    data->obcFailures  = this->obcFailures;
    data->emixFailures  = this->emixFailures;

    // Faults1
    data->dcdc1ErrorCode = this->dcdc1ErrorCode;
    data->dcdc2ErrorCode = this->dcdc2ErrorCode;

    // Faults2
    data->edsErrorCode = this->edsErrorCode;
    data->obcErrorCode = this->obcErrorCode;


    return data;
}

bool CANData::operator==(CANData& other) const {
    bool message1 = (
        this->batteryCurrent == other.batteryCurrent &&
        this->batteryVoltage == other.batteryVoltage &&
        this->SOC == other.SOC
    );

    bool message2 = (
        this->engineCurrent == other.engineCurrent &&
        this->engineTorque == other.engineTorque &&
        this->engineVoltage == other.engineVoltage &&
        this->rpm == other.rpm &&
        this->setpoint == other.setpoint
    );

    bool message3 = (
        this->engineTemp == other.engineTemp &&
        this->inversorTemp == other.inversorTemp &&
        this->batTemp == other.batTemp &&
        this->batMaxTemp == other.batMaxTemp &&
        this->batMinTemp == other.batMinTemp
    );

    bool message4 = (
        this->dcdc1Current == other.dcdc1Current &&
        this->dcdc2Current == other.dcdc2Current &&
        this->dcdc1HVCurrent == other.dcdc1HVCurrent &&
        this->dcdc2HVCurrent == other.dcdc2HVCurrent
    );

    bool message5 = (
        this->dcdc1OutputVoltage == other.dcdc1OutputVoltage &&
        this->dcdc2OutputVoltage == other.dcdc2OutputVoltage &&
        this->dcdc1InputVoltage == other.dcdc1InputVoltage &&
        this->dcdc2InputVoltage == other.dcdc2InputVoltage
    );

    bool message6 = (
        this->posResistanceSIM100 == other.posResistanceSIM100 &&
        this->negResistanceSIM100 == other.negResistanceSIM100 &&
        this->posResistanceBMU == other.posResistanceBMU &&
        this->negResistanceBMU == other.negResistanceBMU
    );

    bool message7 = (
        // Message 7
        this->lvError == other.lvError &&
        this->hvError == other.hvError &&

        this->state == other.state &&

        this->inhibitState == other.inhibitState &&
        this->busHVDischarged == other.busHVDischarged &&
        this->pduContactorClose == other.pduContactorClose &&

        this->hvOn == other.hvOn &&
        this->lvHigh == other.lvHigh &&

        this->dcdc1Overtemp == other.dcdc1Overtemp &&
        this->dcdc2Overtemp == other.dcdc2Overtemp &&

        this->atsFanFault == other.atsFanFault &&
        this->atsPumpFault == other.atsPumpFault &&

        this->edsOvertemp == other.edsOvertemp &
        this->obcOvertemp == other.obcOvertemp &

        this->edsInError == other.edsInError &&
        this->edsCouldntClear == other.edsCouldntClear &&

        this->dcdcHighDifference == other.dcdcHighDifference &&

        this->batModule1 == other.batModule1 &&
        this->batModule2 == other.batModule2 &&
        this->batModule3 == other.batModule3 &&
        this->batModule4 == other.batModule4 &&

        this->contactorPdu == other.contactorPdu &&
        this->sim100Stucked == other.sim100Stucked &&

        this->couldntPowerOnBMS == other.couldntPowerOnBMS &&

        this->bessPowerOffHv == other.bessPowerOffHv &&
        this->requiredHvOff == other.requiredHvOff &&

        this->pedal1Anormal == other.pedal1Anormal &&
        this->pedal2Anormal == other.pedal2Anormal &&

        this->hvilPdu == other.hvilPdu &&
        this->hvilObc == other.hvilObc &&
        this->hvilEds == other.hvilEds &&
        this->hvilDddc == other.hvilDddc &&

        this->termistorLVOutOfRange == other.termistorLVOutOfRange &&
        this->termistorHVOutOfRange == other.termistorHVOutOfRange &&

        this->pduTempExcess == other.pduTempExcess &&
        this->overturn == other.overturn &&
        this->doorOpen == other.doorOpen &&
        this->parkingState == other.parkingState &&
        this->estadoMarcha == other.estadoMarcha
    );

    bool bess1 = true;

    for (int i = 0; i < 194 * 3; i++) {
        if (this->voltageCells[i] != other.voltageCells[i]) {
            return false;
        }
    }

    bool bess2 = true;

    for (int i = 0; i < 18 * 6; i++) {
        if (this->tempCells[i] != other.tempCells[i]) {
            qInfo() << "Trama" << i;
            qInfo() << this->tempCells[i];
            qInfo() << other.tempCells[i];
            return false;
        }
    }

    bool bess3 = (
        this->chargeEnergyAcumulated == other.chargeEnergyAcumulated &&
        this->dischargeEnergyAcumulated == other.dischargeEnergyAcumulated &&
        this->energyOneCharge == other.energyOneCharge
    );

    bool bess4 = (
        this->SOC == other.SOC &&
        this->SOH == other.SOH &&
        this->minVoltage == other.minVoltage &&
        this->maxVoltage == other.maxVoltage &&
        this->meanVoltage == other.meanVoltage
    );

    bool bess5 = (
        this->posChargeTempDC == other.posChargeTempDC &&
        this->negChargeTempDC == other.negChargeTempDC &&
        this->dcConected == other.dcConected &&
        this->bmsChargingMode == other.bmsChargingMode &&
        this->coolingState == other.coolingState &&
        this->heatState == other.heatState &&
        this->bmuContactor == other.bmuContactor &&
        this->bmsFailures == other.bmsFailures
    );

    bool emix1 = (
        this->edsFailures == other.edsFailures &&
        this->dcdc1Failures == other.dcdc1Failures &&
        this->dcdc2Failures == other.dcdc2Failures &&
        this->sim100Failures == other.sim100Failures &&
        this->obcFailures == other.obcFailures &&
        this->emixFailures == other.emixFailures
    );

    bool faults1 = (
        this->dcdc1ErrorCode == other.dcdc1ErrorCode &&
        this->dcdc2ErrorCode == other.dcdc2ErrorCode
    );

    bool faults2 =(
        this->edsErrorCode == other.edsErrorCode &&
        this->obcErrorCode == other.obcErrorCode
    );


    return (
        message1 && message2 && message3 && message4 &&
        message5 && message6 && message7 &&
        bess1 && bess2 && bess3 && bess4 && bess5&&
        emix1 &&
        faults1 && faults2
    );
}

CANData::~CANData (){

}
