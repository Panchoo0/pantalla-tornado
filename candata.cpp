#include "candata.h"
#include <utils.h>
#include <bits/stdc++.h>
#include <QDebug>

CANData::CANData() {
}

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
        setpoint = Utils::getShiftedData(48, 12, receivedData);

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
        pedal1Anormal = Utils::getShiftedData(36, 1, receivedData);
        pedal2Anormal = Utils::getShiftedData(37, 1, receivedData);
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

void CANData::assertMessage1(int current, int voltage, int soc) {
    assert(this->batteryCurrent == current);
    assert(this->batteryVoltage == voltage);
    assert(this->SOC == soc);
}

void CANData::assertMessage2(int engineCurrent, int engineTorque, int engineVoltage, int rpm, int setpoint) {
    assert(this->engineCurrent == engineCurrent);
    assert(this->engineTorque == engineTorque);
    assert(this->engineVoltage == engineVoltage);
    assert(this->rpm == rpm);
    assert(this->setpoint == setpoint);
}

void CANData::assertMessage3(int engineTemp, int inversorTemp, int batTemp, int batMaxTemp, int batMinTemp) {
    assert(this->engineTemp == engineTemp);
    assert(this->inversorTemp == inversorTemp);
    assert(this->batTemp == batTemp);
    assert(this->batMaxTemp == batMaxTemp);
    assert(this->batMinTemp == batMinTemp);
}

void CANData::assertMessage4(int dcdc1Current, int dcdc2Current, int dcdc1HVCurrent, int dcdc2HVCurrent) {
    assert(this->dcdc1Current == dcdc1Current);
    assert(this->dcdc2Current == dcdc2Current);
    assert(this->dcdc1HVCurrent == dcdc1HVCurrent);
    assert(this->dcdc2HVCurrent == dcdc2HVCurrent);
}

void CANData::assertMessage5(int dcdc1OutputVoltage, int dcdc2OutputVoltage, int dcdc1InputVoltage, int dcdc2InputVoltage) {
    assert(this->dcdc1OutputVoltage == dcdc1OutputVoltage);
    assert(this->dcdc2OutputVoltage == dcdc2OutputVoltage);
    assert(this->dcdc1InputVoltage == dcdc1InputVoltage);
    assert(this->dcdc2InputVoltage == dcdc2InputVoltage);
}

void CANData::assertMessage6(int posResistanceSIM100, int negResistanceSIM100, int posResistanceBMU, int negResistanceBMU) {
    assert(this->posResistanceSIM100 == posResistanceSIM100);
    assert(this->negResistanceSIM100 == negResistanceSIM100);
    assert(this->posResistanceBMU == posResistanceBMU);
    assert(this->negResistanceBMU == negResistanceBMU);

}

void CANData::assertBess1(int trama, int v1, int v2, int v3) {
    assert(this->voltageCells[trama * 3] == v1);
    assert(this->voltageCells[trama * 3 + 1] == v2);
    assert(this->voltageCells[trama * 3 + 2] == v3);
}

void CANData::assertBess2(int trama, int t1, int t2, int t3, int t4, int t5, int t6) {
    assert(this->tempCells[trama * 6] == t1);
    assert(this->tempCells[trama * 6 + 1] == t2);
    assert(this->tempCells[trama * 6 + 2] == t3);
    assert(this->tempCells[trama * 6 + 3] == t4);
    assert(this->tempCells[trama * 6 + 4] == t5);
    assert(this->tempCells[trama * 6 + 5] == t6);
}

void CANData::assertBess3(int chargeEnergyAcumulated, int dischargeEnergyAcumulated, int energyOneCharge) {
    assert(this->chargeEnergyAcumulated == chargeEnergyAcumulated);
    assert(this->dischargeEnergyAcumulated == dischargeEnergyAcumulated);
    assert(this->energyOneCharge == energyOneCharge);
}



void CANData::assertBess4(int SOC, int SOH, int minVoltage, int maxVoltage, int meanVoltage) {
    assert(this->SOC == SOC);
    assert(this->SOH == SOH);
    assert(this->maxVoltage == maxVoltage);
    assert(this->minVoltage == minVoltage);
    assert(this->meanVoltage == meanVoltage);
}

void CANData::assertBess5(int posChargeTempDC, int negChargeTempDC, int dcConected, int bmsChargingMode, int coolingState, int heatState, int bmuContactor, int bmsFailures) {
    assert(this->posChargeTempDC == posChargeTempDC);
    assert(this->negChargeTempDC == negChargeTempDC);
    assert(this->dcConected == dcConected);
    assert(this->bmsChargingMode == bmsChargingMode);
    assert(this->coolingState == coolingState);
    assert(this->heatState == heatState);
    assert(this->bmuContactor == bmuContactor);
    assert(this->bmsFailures == bmsFailures);
}

void CANData::assertEmix1(int edsFailures, int dcdc1Failures, int dcdc2Failures, int sim100Failures, int obcFailures, int emixFailures) {
    assert(this->edsFailures == edsFailures);
    assert(this->dcdc1Failures == dcdc1Failures);
    assert(this->dcdc2Failures == dcdc2Failures);
    assert(this->sim100Failures == sim100Failures);
    assert(this->obcFailures == obcFailures);
    assert(this->emixFailures == emixFailures);
}

void CANData::assertFaults1(int dcdc1ErrorCode, int dcdc2ErrorCode) {
    assert(this->dcdc1ErrorCode == dcdc1ErrorCode);
    assert(this->dcdc2ErrorCode == dcdc2ErrorCode);
}

void CANData::assertFaults2(int edsErrorCode, int obcErrorCode) {
    assert(this->edsErrorCode == edsErrorCode);
    assert(this->obcErrorCode == obcErrorCode);
}

// Dado el id de un error lo agrega a los errores DTC recibidos por el bus CAN
void CANData::addError(int id) {
    DTCCanError error = DTCCanError::fromInt(id);
    this->canErrors.push_back(error);
}

CANData::~CANData (){

}
