#include "candata.h"
#include <utils.h>
#include <bits/stdc++.h>
#include <QDebug>
#include <fstream>
#include <QDateTime>

CANData::CANData() {
    this->bess = Bess();
    this->eds = Eds();
    this->dcdc1 = Dcdc();
    this->dcdc2 = Dcdc();
    this->sim100 = Sim100();
    this->processVars = ProcessVars();
    // this->canErrors = std::vector<DTCCanError>();
    // this->allErrors = std::vector<DTCCanError>();
    this->readCanErrorsFromFile();

    for (int i = 0; i < 194; i++) {
        this->voltageCells[i] = 0;
    }
}

// Función para recibir un mensaje proveniente del socket conectado con el bus CAN
// Actualiza la información del objeto en función del mensaje
// Emite una señal para indicar el tipo de mensaje recibido y actualizar la información según corresponda
void CANData::receiveMessage(unsigned char sourceAddress, unsigned int pgn, uint8_t* receivedData) {
    uchar b1_pgn = pgn >> 8;
    uchar b2_pgn = pgn & 0xFF;
    uchar b_pgn[] = {b1_pgn, b2_pgn};
    QString hex_pgn = Utils::toHexString(b_pgn, 2);
    // emit dbgMessage("Mensaje CAN recibido pgn: " + hex_pgn + "; data: " + Utils::toHexString(receivedData, 8));

    switch (pgn) {
    case 0x100: {
        bess.inst_current = Utils::round(Utils::getShiftedData(0, 16, receivedData), 0.1, -1000);
        bess.inst_voltage = Utils::round(Utils::getShiftedData(16, 16, receivedData), 0.1);
        bess.SoC = Utils::round(Utils::getShiftedData(32, 8, receivedData), 0.4);

        emit message1();
        break;
    }
    case 0x200: {
        eds.instCurr = Utils::getShiftedData(0, 12, receivedData);
        eds.instTorque = Utils::getShiftedData(12, 12, receivedData);
        eds.instVoltage = Utils::getShiftedData(24, 12, receivedData);
        eds.instRPM = Utils::round(Utils::getShiftedData(36, 12, receivedData), 0.0859375, -2750);
        eds.txSetpoint = Utils::getShiftedData(48, 16, receivedData);

        emit message2();
        break;
    }
    case 0x300: {
        eds.motorTemp = Utils::getShiftedData(0, 8, receivedData) - 40;
        eds.invTemp = Utils::getShiftedData(8, 8, receivedData) - 40;
        bess.avgTemp = Utils::getShiftedData(16, 8, receivedData);
        bess.maxTemp = Utils::getShiftedData(24, 8, receivedData);
        bess.minTemp = Utils::getShiftedData(32, 8, receivedData);

        emit message3();
        break;
    }
    case 0x400: {
        dcdc1.lvCurr = Utils::round(Utils::getShiftedData(0, 16, receivedData), 0.1 , 3212.7);
        dcdc2.lvCurr = Utils::round(Utils::getShiftedData(16, 16, receivedData), 0.1, 3212.7);
        dcdc1.hvCurr = Utils::round(Utils::getShiftedData(32, 16, receivedData), 0.1, 3212.7);
        dcdc2.hvCurr = Utils::round(Utils::getShiftedData(48, 16, receivedData), 0.1, 3212.7);

        emit message4();
        break;
    }
    case 0x500: {
        dcdc1.VVout = Utils::round(Utils::getShiftedData(0, 16, receivedData), 0.05);
        dcdc2.VVout = Utils::round(Utils::getShiftedData(16, 16, receivedData), 0.05);
        dcdc1.Vin = Utils::round(Utils::getShiftedData(32, 16, receivedData), 0.05);
        dcdc2.Vin = Utils::round(Utils::getShiftedData(48, 16, receivedData), 0.05);

        emit message5();
        break;
    }
    case 0x600: {
        sim100.Rp = Utils::getShiftedData(0, 16, receivedData);
        sim100.Rn = Utils::getShiftedData(16, 16, receivedData);
        bess.Rp = Utils::getShiftedData(32, 16, receivedData);
        bess.Rn = Utils::getShiftedData(48, 16, receivedData);

        emit message6();
        break;
    }
    case 0x700: {
        processVars.LV_Error_Level = Utils::getShiftedData(0, 4, receivedData);
        processVars.HV_Error_Level = Utils::getShiftedData(4, 4, receivedData);

        processVars.EMIX_state = Utils::getShiftedData(8, 4, receivedData);

        processVars.EMIX_inhibitState = Utils::getShiftedData(12, 1, receivedData);
        processVars.isHVBusDischarged = Utils::getShiftedData(13, 1, receivedData);
        processVars.IsPDUmainRelayClosed = Utils::getShiftedData(14, 1, receivedData);
        processVars.IsHVOn = Utils::getShiftedData(15, 1, receivedData);
        // Posiblemente aquí este corrido el bit de inicio en el excel
        processVars.LvVoltageTooHigh = Utils::getShiftedData(16, 2, receivedData);
        processVars.DCDC1Overtemp = Utils::getShiftedData(18, 1, receivedData);
        processVars.DCDC2Overtemp = Utils::getShiftedData(19, 1, receivedData);
        processVars.ATS_Fan_Fault = Utils::getShiftedData(20, 1, receivedData);
        processVars.ATS_Pump_Fault =Utils::getShiftedData(21, 1, receivedData);
        processVars.EDSOvertemp = Utils::getShiftedData(22, 1, receivedData);
        processVars.OBCOvertemp = Utils::getShiftedData(23, 1, receivedData);
        processVars.EDSinError = Utils::getShiftedData(24, 1, receivedData);
        processVars.EDScantClearError = Utils::getShiftedData(25, 1, receivedData);
        processVars.DCDCsPwrDifference2Large = Utils::getShiftedData(26, 1, receivedData);
        processVars.BESS_Module1TempTooLarge = Utils::getShiftedData(27, 1, receivedData);
        processVars.BESS_Module2TempTooLarge = Utils::getShiftedData(28, 1, receivedData);
        processVars.BESS_Module3TempTooLarge = Utils::getShiftedData(29, 1, receivedData);
        processVars.BESS_Module4TempTooLarge = Utils::getShiftedData(30, 1, receivedData);
        processVars.PDUMainRelayCantChangeState = Utils::getShiftedData(31, 1, receivedData);
        processVars.Sim100Stuck = Utils::getShiftedData(32, 1, receivedData);
        processVars.ImpossibleToSwitchOnBMS = Utils::getShiftedData(33, 1, receivedData);
        processVars.BMSrequestsHvOff = Utils::getShiftedData(34, 1, receivedData);
        processVars.HvOffIsRequired = Utils::getShiftedData(35, 1, receivedData);
        processVars.Pedal2Abnormal = Utils::getShiftedData(36, 1, receivedData);
        processVars.Pedal1Abnormal = Utils::getShiftedData(37, 1, receivedData);
        processVars.PDU_HvilAlarm = Utils::getShiftedData(38, 1, receivedData);
        processVars.OBC_HvilAlarm = Utils::getShiftedData(39, 1, receivedData);
        processVars.EDS_HvilAlarm = Utils::getShiftedData(40, 1, receivedData);
        processVars.DCDCs_HvilAlarm = Utils::getShiftedData(41, 1, receivedData);
        processVars.LvThermistorOutOfRange = Utils::getShiftedData(42, 1, receivedData);
        processVars.HvThermistorOutOfRange = Utils::getShiftedData(43, 1, receivedData);
        processVars.PDUOvertemp = Utils::getShiftedData(44, 1, receivedData);
        processVars.OverturnEvent = Utils::getShiftedData(45, 1, receivedData);
        processVars.CabinDoorOpen = Utils::getShiftedData(46, 1, receivedData);
        processVars.ParkingRelayState = Utils::getShiftedData(47, 1, receivedData);
        processVars.MarchState = Utils::getShiftedData(48, 2, receivedData);

        emit message7();
        break;
    }
    case 0xC100: {
        uchar trama1 = Utils::getShiftedData(0, 8, receivedData);
        uchar trama2 = Utils::getShiftedData(8, 8, receivedData);
        int trama = trama1 + (trama2 << 8) - 1;

        if (trama > 194) {
            qInfo() << "Trama de voltaje inválida:" << trama;
            return;
        }

        float fc = 0.001;

        int v1 = (uchar) Utils::getShiftedData(16, 8, receivedData);
        int v2 = (uchar) Utils::getShiftedData(24, 8, receivedData);
        int v3 = (uchar) Utils::getShiftedData(32, 8, receivedData);
        int v4 = (uchar) Utils::getShiftedData(40, 8, receivedData);
        int v5 = (uchar) Utils::getShiftedData(48, 8, receivedData);
        int v6 = (uchar) Utils::getShiftedData(56, 8, receivedData);

        voltageCells[trama] =     Utils::round(v1 + (v2 <<  8), fc);
        voltageCells[trama + 1] = Utils::round(v3 + (v4 <<  8), fc);
        voltageCells[trama + 2] = Utils::round(v5 + (v6 <<  8), fc);

        emit bess1(trama);
        break;
    }
    case 0xC200: {
        uchar trama1 = Utils::getShiftedData(0, 8, receivedData);
        uchar trama2 = Utils::getShiftedData(8, 8, receivedData);

        int trama = trama1 + (trama2 << 8) - 1;

        if (trama > 13) {
            qInfo() << "Trama de temp inválida:" << trama;
            return;
        }
        tempCells[trama] = Utils::getShiftedData(16, 8, receivedData);
        tempCells[trama + 1]  = Utils::getShiftedData(24, 8, receivedData);
        tempCells[trama + 2]  = Utils::getShiftedData(32, 8, receivedData);
        tempCells[trama + 3]  = Utils::getShiftedData(40, 8, receivedData);
        tempCells[trama + 4]  = Utils::getShiftedData(48, 8, receivedData);
        tempCells[trama + 5]  = Utils::getShiftedData(56, 8, receivedData);

        emit bess2(trama);
        break;
    }
    case 0xC300: {
        chargeEnergyAcumulated = Utils::getShiftedData(0, 24, receivedData);
        dischargeEnergyAcumulated = Utils::getShiftedData(24, 24, receivedData);
        energyOneCharge = Utils::round(Utils::getShiftedData(48, 16, receivedData), 0.1);

        emit bess3();
        break;
    }
    case 0xC400: {
        // TODO: revisar este SOC con el otro y ver cual es el de verdad
        bess.SoC = Utils::round(Utils::getShiftedData(0, 8, receivedData), 0.4);
        SOH = Utils::round(Utils::getShiftedData(8, 8, receivedData), 0.4);
        maxVoltage = Utils::round(Utils::getShiftedData(16, 16, receivedData), 0.001);
        minVoltage = Utils::round(Utils::getShiftedData(32, 16, receivedData), 0.001);
        meanVoltage = Utils::round(Utils::getShiftedData(48, 16, receivedData), 0.001);

        emit bess4();
        break;
    }
    case 0xC500: {
        posChargeTempDC = Utils::getShiftedData(0, 8, receivedData) - 40;
        negChargeTempDC = Utils::getShiftedData(8, 8, receivedData) - 40;
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
        qInfo() << "Mensaje J1939 no reconocido con pgn: " << hex_pgn;
        break;
    }

}

void CANData::receiveUDSMessage(uint8_t* receivedData) {
    int resID = Utils::getShiftedData(8, 8, receivedData);
    int DID = Utils::getShiftedData(16, 16, receivedData);
    if (resID != 0x62) {
        qInfo() << "Mensaje con otra resID: " << resID;
        return;
    }

    switch (DID) {
    case 0xA011: {
        Maxcellvoltage = (ushort) Utils::getShiftedData(32, 16, receivedData);
        maxVoltage = Utils::round(Maxcellvoltage, 0.001);
        emit bess4();
        break;
    }
    case 0xA012: {
        Mincellvoltage = (ushort) Utils::getShiftedData(32, 16, receivedData);
        minVoltage = Utils::round(Mincellvoltage, 0.001);
        emit bess4();
        break;
    }
    case 0xA013: {
        Maxpacktemperature = (uchar) Utils::getShiftedData(32, 8, receivedData);
        Maxpacktemperature -= 40;
        emit
        break;
    }
    case 0xA016: {
        isHVOn = Utils::getShiftedData(32, 8, receivedData) == 1;
        processVars.IsHVOn = isHVOn;
        emit message7();
        break;
    }
    case 0xA018: {
        InletcoolantTemperatureMotor = (uchar) Utils::getShiftedData(32, 8, receivedData) - 40;
        eds.motorTemp = InletcoolantTemperatureMotor;
        emit message3();
        emit updateMainWindow();
        break;
    }
    case 0xA019: {
        InletcoolantTemperatureInverter = (uchar) Utils::getShiftedData(32, 8, receivedData) - 40;
        emit message3();
        break;
    }
    case 0xA01B: {
        DCVoltageFeedbackRx = Utils::round((ushort)Utils::getShiftedData(32, 16, receivedData), 0.4375, -875);
        eds.instVoltage = DCVoltageFeedbackRx;
        emit message2();
        break;
    }
    case 0xA01E: {
        PositiveinsulationResistancesim100 = (ushort) Utils::getShiftedData(32, 16, receivedData);
        sim100.Rp = PositiveinsulationResistancesim100;
        emit message6();
        break;
    }
    case 0xA01F: {
        NegativeinsulationResistancesim100 = (ushort) Utils::getShiftedData(32, 16, receivedData);
        sim100.Rn = NegativeinsulationResistancesim100;
        emit message6();
        break;
    }
    case 0xA020: {
        Averagecellvoltage = (ushort) Utils::getShiftedData(32, 16, receivedData);
        meanVoltage = Utils::round(Averagecellvoltage, 0.001);
        emit bess4();
        break;
    }
    case 0xA023: {
        SoC = (uchar) Utils::getShiftedData(32, 8, receivedData);
        bess.SoC = Utils::round(SoC, 0.4);
        emit message1();
        break;
    }
    case 0xA028: {
        posChargeTempDC = Utils::getShiftedData(32, 8, receivedData) - 40;
        emit bess5();
        break;
    }
    case 0xA02A: {
        negChargeTempDC = Utils::getShiftedData(32, 8, receivedData) - 40;
        emit bess5();
        break;
    }
    case 0xA02B: {
        PackVoltage = Utils::round((ushort) Utils::getShiftedData(32, 16, receivedData), 0.1) ;
        emit updateMainWindow();
        break;
    }
    case 0xA031: {
        DCDC1coolantinT = Utils::getShiftedData(32, 8, receivedData);
        break;
    }
    case 0xA033: {
        DCDC2coolantinT = Utils::getShiftedData(32, 8, receivedData);
        break;
    }
    case 0xA03D: {
        Electricalisolation = Utils::getShiftedData(32, 16, receivedData);
        break;
    }
    case 0xA03E: {
        HVCurrentDCDC1 = (ushort) Utils::getShiftedData(32, 16, receivedData);
        dcdc1.hvCurr = Utils::round(HVCurrentDCDC1, 0.1, -3212.7);
        emit message4();
        break;
    }
    case 0xA040: {
        LVCurrentDCDC1 = (ushort) Utils::getShiftedData(32, 16, receivedData);
        dcdc1.lvCurr = Utils::round(LVCurrentDCDC1, 0.1, -3212.7);
        emit message4();
        break;
    }
    case 0xA041: {
        LVVoltageDCDC1 = Utils::round((ushort) Utils::getShiftedData(32, 16, receivedData), 0.01);
        emit updateMainWindow();
        break;
    }
    case 0xA042: {
        LVCurrentDCDC2 = (ushort) Utils::getShiftedData(32, 16, receivedData);
        dcdc2.lvCurr = Utils::round(LVCurrentDCDC2, 0.1, -3212.7);
        emit message4();
        break;
    }
    case 0xA044: {
        HVCurrentDCDC2 = (ushort) Utils::getShiftedData(32, 16, receivedData);
        dcdc2.hvCurr = Utils::round(HVCurrentDCDC2, 0.1, -3212.7);
        emit message4();
        break;
    }
    case 0xA049: {
        InhibitState = (uchar) Utils::getShiftedData(32, 8, receivedData);
        processVars.EMIX_inhibitState = InhibitState;
        emit message7();
        break;
    }
    case 0xA05A: {
        processVars.LvThermistorOutOfRange = Utils::getShiftedData(32, 16, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA05B: {
        processVars.HvThermistorOutOfRange = Utils::getShiftedData(32, 16, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA066: {
        LVVoltageDCDC2 = Utils::round((ushort) Utils::getShiftedData(32, 16, receivedData), 0.01);
        emit updateMainWindow();
    }
    case 0xA0C0: {
        processVars.Pedal1Abnormal = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0C1: {
        processVars.Pedal2Abnormal = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0CD: {
        processVars.OBCOvertemp = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0CE: {
        processVars.EDSOvertemp = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0CF: {
        processVars.DCDC1Overtemp = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0D0: {
        processVars.DCDC2Overtemp = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0D1: {
        processVars.ATS_Pump_Fault = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0D2: {
        processVars.ATS_Fan_Fault = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0D3: {
        processVars.EDSinError = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0D4: {
        processVars.EDScantClearError = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0D6: {
        processVars.DCDCsPwrDifference2Large = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0E4: {
        processVars.Sim100Stuck = Utils::getShiftedData(32, 8, receivedData);
        emit message7();
        break;
    }
    case 0xA0E7: {
        processVars.ImpossibleToSwitchOnBMS = Utils::getShiftedData(32, 8, receivedData) == 1;
        emit message7();
        break;
    }
    case 0xA0EB: {
        FaultCodeEDS = (uchar) Utils::getShiftedData(32, 8, receivedData);
        
        if (FaultCodeEDS == 0) return;

        this->addError(FaultCodeEDS + 0xD300);
        emit canError();
        emit canTestigo(this->allErrors[this->allErrors.size() - 1].testigo);
        break;
    }
    case 0xA0EE: {
        FaultCodeSIM100 = (uchar) Utils::getShiftedData(32, 8, receivedData);

        if (FaultCodeSIM100 == 0) {
            emit dbgMessage("Sin errores");
            return;
        }

        this->addError(FaultCodeSIM100 + 0xD200);
        emit canError();
        emit canTestigo(this->allErrors[this->allErrors.size() - 1].testigo);
        break;
    }
    case 0xA0EF: {
        FaultCodeBESS = (uchar) Utils::getShiftedData(32, 8, receivedData);
        if (FaultCodeBESS == 0) return;


        this->addError(FaultCodeBESS + 0xD400);
        emit canError();
        emit canTestigo(this->allErrors[this->allErrors.size() - 1].testigo);
        break;
    }
    case 0xA0F0: {
        FaultCodeDCDC1 = (uchar) Utils::getShiftedData(32, 8, receivedData);
        if (FaultCodeDCDC1 == 0) return;

        this->addError(FaultCodeDCDC1 + 0xD000);
        emit canError();
        emit canTestigo(this->allErrors[this->allErrors.size() - 1].testigo);
        break;
    }
    case 0xA0F1: {
        FaultCodeDCDC2 = (uchar) Utils::getShiftedData(32, 8, receivedData);

        if (FaultCodeDCDC2 == 0) return;

        this->addError(FaultCodeDCDC2 + 0xD100);
        emit canError();
        emit canTestigo(this->allErrors[this->allErrors.size() - 1].testigo);
        break;
    }
    case 0xA0F2: {
        FaultCodeOBC = (uchar) Utils::getShiftedData(32, 8, receivedData);

        if (FaultCodeOBC == 0) return;

        this->addError(FaultCodeOBC + 0xD700);
        emit canError();
        emit canTestigo(this->allErrors[this->allErrors.size() - 1].testigo);
        break;
    }
    case 0xA0F3: {
        FaultCodeEMIX = (uchar) Utils::getShiftedData(32, 8, receivedData);

        if (FaultCodeEMIX == 0) return;

        this->addError(FaultCodeEMIX + 0xD600);
        emit canError();
        emit canTestigo(this->allErrors[this->allErrors.size() - 1].testigo);
        break;
    }
    case 0xA0F4: {
        MarchState = (uchar) Utils::getShiftedData(32, 8, receivedData);
        emit updateMainWindow();
        emit message7();
        break;
    }
    default: {
    }

    }
}

// Dado el id de un error lo agrega a los errores DTC recibidos por el bus CAN
void CANData::addError(int id) {
    DTCCanError error = DTCCanError::fromInt(id);
    std::ofstream file("errors.csv", std::ofstream::app);
    file << id << "," << error.date.toString().toStdString() << "\n";
    file.close();

    this->canErrors.push_back(error);
    this->allErrors.push_back(error);
}

// Función que lee los errores CAN almacenados en la pantalla al encender el equipo
void CANData::readCanErrorsFromFile() {
    std::ifstream file("errors.csv");

    std::string string_line;
    while (std::getline(file, string_line))
    {
        // // El archivo cuenta con 2 columnas: ID | Fecha
        // std::vector<std::string> tokens = Utils::split(string_line, ",");
        // int id = std::stoi(tokens[0]);
        // QDateTime date = QDateTime::fromString(QString::fromStdString(tokens[1]));

        // DTCCanError error = DTCCanError::fromInt(id);
        // error.date = date;
        // this->allErrors.push_back(error);
    }
    file.close();
}

// Falta agregar las variables de UDS
CANData* CANData::clone() {
    CANData* data = new CANData();
    data->speed = this->speed;

    data->bess = *(this->bess.clone());
    data->eds = *(this->eds.clone());
    data->dcdc1 = *(this->dcdc1.clone());
    data->dcdc2 = *(this->dcdc2.clone());
    data->sim100 = *(this->sim100.clone());

    // Message 7
    data->processVars = *(this->processVars.clone());

    // Bess1
    for (int i = 0; i < 194;  i++) {
        data->voltageCells[i] = this->voltageCells[i];
    }

    // Bess2
    for (int i = 0; i < 18; i++) {
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

// Falta agregar las variables de UDS
bool CANData::operator==(CANData& other) const {
    bool message1 = this->bess == other.bess;
    bool message2 = this->eds == other.eds;
    bool message4 = this->dcdc1 == other.dcdc1 && this->dcdc2 == other.dcdc2;
    bool message6 = this->sim100 == other.sim100;
    bool message7 = this->processVars == other.processVars;

    if (!message1) qInfo() << "message1" << message1;
    if (!message2) qInfo() << "message2" << message2;
    if (!message4) qInfo() << "message4" << message4;
    if (!message6) qInfo() << "message6" << message6;
    if (!message7) qInfo() << "message7" << message7;

    for (int i = 0; i < 194; i++) {
        if (this->voltageCells[i] != other.voltageCells[i]) {
            qInfo() << "BESS1";
            return false;
        }
    }


    for (int i = 0; i < 18; i++) {
        if (this->tempCells[i] != other.tempCells[i]) {
            qInfo() << "BESS2";
            return false;
        }
    }

    bool bess3 = (
        this->chargeEnergyAcumulated == other.chargeEnergyAcumulated &&
        this->dischargeEnergyAcumulated == other.dischargeEnergyAcumulated &&
        this->energyOneCharge == other.energyOneCharge
    );

    if (!bess3) {
        qInfo() << "BESS3";
        qInfo() << (this->chargeEnergyAcumulated == other.chargeEnergyAcumulated);
        qInfo() << (this->dischargeEnergyAcumulated == other.dischargeEnergyAcumulated);
        qInfo() << (this->energyOneCharge == other.energyOneCharge);
    }

    bool bess4 = (
        this->SOH == other.SOH &&
        this->minVoltage == other.minVoltage &&
        this->maxVoltage == other.maxVoltage &&
        this->meanVoltage == other.meanVoltage
    );

    if (!bess4) {
        qInfo() << "BESS4";
        qInfo() << (this->SOH == other.SOH);
        qInfo() << (this->minVoltage == other.minVoltage);
        qInfo() << (this->maxVoltage == other.maxVoltage);
        qInfo() << (this->meanVoltage == other.meanVoltage);
    }

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

    if (!bess5) qInfo() << "BESS5";

    bool emix1 = (
        this->edsFailures == other.edsFailures &&
        this->dcdc1Failures == other.dcdc1Failures &&
        this->dcdc2Failures == other.dcdc2Failures &&
        this->sim100Failures == other.sim100Failures &&
        this->obcFailures == other.obcFailures &&
        this->emixFailures == other.emixFailures
    );

    if (!emix1) qInfo() << "emix1";

    bool faults1 = (
        this->dcdc1ErrorCode == other.dcdc1ErrorCode &&
        this->dcdc2ErrorCode == other.dcdc2ErrorCode
    );

    if (!faults1) qInfo() << "faults1";

    bool faults2 =(
        this->edsErrorCode == other.edsErrorCode &&
        this->obcErrorCode == other.obcErrorCode
    );

    if (!faults2) qInfo() << "faults2";


    return (
        message1 && message2 && message4 &&
        message6 && message7 &&
        bess3 && bess4 && bess5&&
        emix1 &&
        faults1 && faults2
    );
}

CANData::~CANData (){

}
