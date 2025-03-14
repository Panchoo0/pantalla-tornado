#ifndef CANDATA_H
#define CANDATA_H

#include <QObject>
#include "dtccanerror.h"
#include <QDebug>

class Bess {
public:
    float inst_current; // J1939 -> message1
    float inst_voltage; // J1939 -> message1
    int SoC; // J1939 -> message1
    int avgTemp; // J1939 -> message3
    int maxTemp; // J1939 -> message3
    int minTemp; // J1939 -> message3
    int Rp; // J1939 -> message6
    int Rn; // J1939 -> message6

    Bess() {
        this->SoC = 0;
        this->inst_current = 0;
        this->inst_voltage = 0;
        this->avgTemp = 0;
        this->maxTemp = 0;
        this->minTemp = 0;
        this->Rp = 0;
        this->Rn = 0;
    }

    Bess* clone() {
        Bess* b = new Bess();
        b->inst_current = this->inst_current;
        b->inst_voltage = this->inst_voltage;
        b->SoC = this->SoC;
        b->avgTemp = this->avgTemp;
        b->maxTemp = this->maxTemp;
        b->minTemp = this->minTemp;
        b->Rp = this->Rp;
        b->Rn = this->Rn;

        return b;
    }

    bool operator==(Bess& other) const {

        return (
            (this->inst_current == other.inst_current) &&
            (this->inst_voltage == other.inst_voltage) &&
            (this->SoC == other.SoC) &&
            (this->avgTemp == other.avgTemp) &&
            (this->maxTemp == other.maxTemp) &&
            (this->minTemp == other.minTemp) &&
            (this->Rp == other.Rp) &&
            (this->Rn == other.Rn)
        );
    }
};


class Eds {
public:
    int instCurr; // J1939 -> message2
    int instTorque; // J1939 -> message2
    float instVoltage; // J1939 -> message2 || UDS -> 0xA01B;
    float instRPM; // J1939 -> message2
    int txSetpoint; // J1939 -> message2
    int motorTemp; // J1939 -> message3
    int invTemp; // J1939 -> message3;

    Eds() {
        this->instCurr = 0;
        this->instTorque = 0;
        this->instVoltage = 0;
        this->instRPM = 0;
        this->txSetpoint = 0;
        this->motorTemp = 0;
        this->invTemp = 0;
    }

    Eds* clone() {
        Eds* e = new Eds();
        e->instCurr = this->instCurr;
        e->instTorque = this->instTorque;
        e->instVoltage = this->instVoltage;
        e->instRPM = this->instRPM;
        e->txSetpoint = this->txSetpoint;
        e->motorTemp = this->motorTemp;
        e->invTemp = this->invTemp;

        return e;
    }

    bool operator==(Eds& other) const {
        return (
            (other.instCurr == this->instCurr) &&
            (other.instTorque == this->instTorque) &&
            (other.instVoltage == this->instVoltage)&&
            (other.instRPM == this->instRPM) &&
            (other.txSetpoint == this->txSetpoint) &&
            (other.motorTemp == this->motorTemp) &&
            (other.invTemp == this->invTemp)
            );
    }
};

class Dcdc {
public:
    float lvCurr; // J1939 -> message4
    float hvCurr; // J1939 -> message4
    float VVout; // J1939 -> message5
    float Vin; // J1939 -> message5

    Dcdc() {
        this->lvCurr = 0;
        this->hvCurr = 0;
        this->VVout = 0;
        this->Vin = 0;
    }

    Dcdc* clone() {
        Dcdc* d = new Dcdc();
        d->lvCurr = this->lvCurr;
        d->hvCurr = this->hvCurr;
        d->VVout = this->VVout;
        d->Vin = this->Vin;

        return d;
    }

    bool operator==(Dcdc& other) const {
        return (
            (other.lvCurr == this->lvCurr) &&
            (other.hvCurr == this->hvCurr) &&
            (other.VVout == this->VVout) &&
            (other.Vin == this->Vin)
            );
    }
};

class Sim100 {
public:
    int Rp; // J1939 -> message6
    int Rn; // J1939 -> message6

    Sim100() {
        this->Rp = 0;
        this->Rn = 0;
    }

    Sim100* clone() {
        Sim100* s = new Sim100();
        s->Rp = this->Rp;
        s->Rn = this->Rn;

        return s;
    }

    bool operator==(Sim100& other) const {
        return (
            (other.Rp == this->Rp) &&
            (other.Rn == this->Rn)
            );
    }
};

class ProcessVars {
public:
    int LV_Error_Level;
    int HV_Error_Level;
    int EMIX_state;
    bool EMIX_inhibitState;
    bool isHVBusDischarged;
    bool IsPDUmainRelayClosed;
    bool IsHVOn;
    int LvVoltageTooHigh;
    bool DCDC1Overtemp;
    bool DCDC2Overtemp;
    bool ATS_Fan_Fault;
    bool ATS_Pump_Fault;
    bool EDSOvertemp;
    bool OBCOvertemp;
    bool EDSinError;
    bool EDScantClearError;
    bool DCDCsPwrDifference2Large;
    bool BESS_Module1TempTooLarge;
    bool BESS_Module2TempTooLarge;
    bool BESS_Module3TempTooLarge;
    bool BESS_Module4TempTooLarge;
    bool PDUMainRelayCantChangeState;
    bool Sim100Stuck;
    bool ImpossibleToSwitchOnBMS;
    bool BMSrequestsHvOff;
    bool HvOffIsRequired;
    bool Pedal2Abnormal;
    bool Pedal1Abnormal;
    bool PDU_HvilAlarm;
    bool OBC_HvilAlarm;
    bool EDS_HvilAlarm;
    bool DCDCs_HvilAlarm;
    bool LvThermistorOutOfRange;
    bool HvThermistorOutOfRange;
    bool PDUOvertemp;
    bool OverturnEvent;
    bool CabinDoorOpen;
    bool ParkingRelayState;
    int MarchState;

    ProcessVars* clone() {
        ProcessVars* p = new ProcessVars();
        p->LV_Error_Level = this->LV_Error_Level;
        p->HV_Error_Level = this->HV_Error_Level;
        p->EMIX_state = this->EMIX_state;
        p->EMIX_inhibitState = this->EMIX_inhibitState;
        p->isHVBusDischarged = this->isHVBusDischarged;
        p->IsPDUmainRelayClosed = this->IsPDUmainRelayClosed;
        p->IsHVOn = this->IsHVOn;
        p->LvVoltageTooHigh = this->LvVoltageTooHigh;
        p->DCDC1Overtemp = this->DCDC1Overtemp;
        p->DCDC2Overtemp = this->DCDC2Overtemp;
        p->ATS_Fan_Fault = this->ATS_Fan_Fault;
        p->ATS_Pump_Fault = this->ATS_Pump_Fault;
        p->EDSOvertemp = this->EDSOvertemp;
        p->OBCOvertemp = this->OBCOvertemp;
        p->EDSinError = this->EDSinError;
        p->EDScantClearError = this->EDScantClearError;
        p->DCDCsPwrDifference2Large = this->DCDCsPwrDifference2Large;
        p->BESS_Module1TempTooLarge = this->BESS_Module1TempTooLarge;
        p->BESS_Module2TempTooLarge = this->BESS_Module2TempTooLarge;
        p->BESS_Module3TempTooLarge = this->BESS_Module3TempTooLarge;
        p->BESS_Module4TempTooLarge = this->BESS_Module4TempTooLarge;
        p->PDUMainRelayCantChangeState = this->PDUMainRelayCantChangeState;
        p->Sim100Stuck = this->Sim100Stuck;
        p->ImpossibleToSwitchOnBMS = this->ImpossibleToSwitchOnBMS;
        p->BMSrequestsHvOff = this->BMSrequestsHvOff;
        p->HvOffIsRequired = this->HvOffIsRequired;
        p->Pedal2Abnormal = this->Pedal2Abnormal;
        p->Pedal1Abnormal = this->Pedal1Abnormal;
        p->PDU_HvilAlarm = this->PDU_HvilAlarm;
        p->OBC_HvilAlarm = this->OBC_HvilAlarm;
        p->EDS_HvilAlarm = this->EDS_HvilAlarm;
        p->DCDCs_HvilAlarm = this->DCDCs_HvilAlarm;
        p->LvThermistorOutOfRange = this->LvThermistorOutOfRange;
        p->HvThermistorOutOfRange = this->HvThermistorOutOfRange;
        p->PDUOvertemp = this->PDUOvertemp;
        p->OverturnEvent = this->OverturnEvent;
        p->CabinDoorOpen = this->CabinDoorOpen;
        p->ParkingRelayState = this->ParkingRelayState;
        p->MarchState = this->MarchState;

        return p;
    }

    bool operator==(ProcessVars& other) const {

        return (
            (other.LV_Error_Level == this->LV_Error_Level) &&
            (other.HV_Error_Level == this->HV_Error_Level) &&
            (other.EMIX_state == this->EMIX_state) &&
            (other.EMIX_inhibitState == this->EMIX_inhibitState) &&
            (other.isHVBusDischarged == this->isHVBusDischarged) &&
            (other.IsPDUmainRelayClosed == this->IsPDUmainRelayClosed) &&
            (other.IsHVOn == this->IsHVOn) &&
            (other.LvVoltageTooHigh == this->LvVoltageTooHigh) &&
            (other.DCDC1Overtemp == this->DCDC1Overtemp) &&
            (other.DCDC2Overtemp == this->DCDC2Overtemp) &&
            (other.ATS_Fan_Fault == this->ATS_Fan_Fault) &&
            (other.ATS_Pump_Fault == this->ATS_Pump_Fault) &&
            (other.EDSOvertemp == this->EDSOvertemp) &&
            (other.OBCOvertemp == this->OBCOvertemp) &&
            (other.EDSinError == this->EDSinError) &&
            (other.EDScantClearError == this->EDScantClearError) &&
            (other.DCDCsPwrDifference2Large == this->DCDCsPwrDifference2Large) &&
            (other.BESS_Module1TempTooLarge == this->BESS_Module1TempTooLarge) &&
            (other.BESS_Module2TempTooLarge == this->BESS_Module2TempTooLarge) &&
            (other.BESS_Module3TempTooLarge == this->BESS_Module3TempTooLarge) &&
            (other.BESS_Module4TempTooLarge == this->BESS_Module4TempTooLarge) &&
            (other.PDUMainRelayCantChangeState == this->PDUMainRelayCantChangeState) &&
            (other.Sim100Stuck == this->Sim100Stuck) &&
            (other.ImpossibleToSwitchOnBMS == this->ImpossibleToSwitchOnBMS) &&
            (other.BMSrequestsHvOff == this->BMSrequestsHvOff) &&
            (other.HvOffIsRequired == this->HvOffIsRequired) &&
            (other.Pedal2Abnormal == this->Pedal2Abnormal) &&
            (other.Pedal1Abnormal == this->Pedal1Abnormal) &&
            (other.PDU_HvilAlarm == this->PDU_HvilAlarm) &&
            (other.OBC_HvilAlarm == this->OBC_HvilAlarm) &&
            (other.EDS_HvilAlarm == this->EDS_HvilAlarm) &&
            (other.DCDCs_HvilAlarm == this->DCDCs_HvilAlarm) &&
            (other.LvThermistorOutOfRange == this->LvThermistorOutOfRange) &&
            (other.HvThermistorOutOfRange == this->HvThermistorOutOfRange) &&
            (other.PDUOvertemp == this->PDUOvertemp) &&
            (other.OverturnEvent == this->OverturnEvent) &&
            (other.CabinDoorOpen == this->CabinDoorOpen) &&
            (other.ParkingRelayState == this->ParkingRelayState) &&
            (other.MarchState == this->MarchState)
            );
    }
};


// Clase cuya función es almacenar todos los datos actualizados obtenidos a través del bus CAN
class CANData : public QObject
{
    Q_OBJECT

public:
    int speed; // Borrar

    Bess bess;
    Eds eds;
    Dcdc dcdc1;
    Dcdc dcdc2;
    Sim100 sim100;
    ProcessVars processVars;

    // Bess1
    float voltageCells[194];

    // Bess2
    int tempCells[18];

    // Bess3
    int chargeEnergyAcumulated;
    int dischargeEnergyAcumulated;
    float energyOneCharge;

    // Bess4
    int SOH;
    float minVoltage;
    float maxVoltage;
    float meanVoltage;

    // Bess5
    int posChargeTempDC;
    int negChargeTempDC;
    int dcConected;

    int bmsChargingMode;
    int coolingState;
    int heatState;

    int bmuContactor;
    int bmsFailures;

    // Emix1
    int edsFailures;
    int dcdc1Failures;
    int dcdc2Failures;
    int sim100Failures;
    int obcFailures;
    int emixFailures;

    // Faults1
    int dcdc1ErrorCode;
    int dcdc2ErrorCode;

    // Faults2
    int edsErrorCode;
    int obcErrorCode;

    // Provenientes de uds
    // UDS
    bool HVOffRequested;
    bool EMIXHvShouldBeOn;
    bool FailToHV;
    bool AnyCellUnderVoltage;
    bool AnyCellOverVoltage;
    bool PDUMainContactorClosed;
    bool HVOFFIsNeeded;
    bool HardwareErrorFlag;
    bool NoNewEstimatesflag;
    bool HVBusDischarged;
    uchar CurrentState;
    uint Debug1NVM;
    bool HighUncertaintyFlag;
    bool HighBatteryVoltageFlag;
    uchar BessFaultLevel;
    ushort SetpointSpeedTx;
    ushort Maxcellvoltage;
    ushort Mincellvoltage;
    char Maxpacktemperature;
    uchar Rpuncertainty;
    uchar LVerrorlevel;
    bool isHVOn;
    uchar HVerrorlevel;
    uchar InletcoolantTemperatureMotor;
    uchar InletcoolantTemperatureInverter;
    uchar Rnuncertainty;
    float DCVoltageFeedbackRx;
    ushort TorqueFeedbackRx;
    ushort SpeedFeedbackRx;
    ushort PositiveinsulationResistancesim100;
    ushort NegativeinsulationResistancesim100;
    ushort Averagecellvoltage;
    uchar SumofBESSfaults;
    uchar Modulewithmaxtemperature;
    uchar SoC;
    bool Lowbatteryvoltageflag;
    bool Debug2CAN1;
    bool DCDC1RequiresBalancing;
    bool DCDC2RequiresBalancing;
    uchar DCgunTemperaturePos;
    uchar FeedbackSetpointMode;
    uchar DCgunTemperatureNeg;
    float PackVoltage;
    ushort BessContactorStatus;
    ushort ApplicationCoreLoad;
    ushort ApplicationCoreLoadMaxCurrentSession;
    ushort ApplicationCoreLoadMaxLifetime;
    uchar ModulewithMinTemperature;
    uchar DCDC1coolantinT;
    uchar DCDC1coolantoutT;
    uchar DCDC2coolantinT;
    uchar LastfaultcodeBess;
    uchar DCDC2coolantoutT;
    uchar DCDC1State;
    uchar DCDC2State;
    uchar ElectricalIsolationUncertainty;
    ushort RC40LVVoltage;
    ushort Positiveinsulationvaluebess;
    ushort Negativeinsulationvaluebess;
    ushort Systeminsulationvaluebess;
    ushort Electricalisolation;
    ushort HVCurrentDCDC1;
    uchar PDUT1HV;
    ushort LVCurrentDCDC1;
    float LVVoltageDCDC1;
    ushort LVCurrentDCDC2;
    uchar PDUT2HV;
    ushort HVCurrentDCDC2;
    uchar Isolationstatusbits;
    uchar PDUT3LV;
    uchar PDUT4LV;
    uchar PDUT5LV;
    uchar InhibitState;
    ushort PackcurrentBESS;
    ushort UmaxLVDCDC1;
    ushort UminLVDCDC1;
    ushort Dcdc1HvLevel;
    ushort Sim100HvLevel;
    ushort Debug3Sim1001;
    ushort DcmDspDatasignal80;
    ushort DcmDspDatasignal81;
    ushort DcmDspDatasignal82;
    ushort SingleChargeEnergy;
    ushort DcmDspDatasignal84;
    ushort DcmDspDatasignal85;
    ushort DcmDspDatasignal86;
    ushort DcmDspDatasignal87;
    ushort DcmDspDatasignal88;
    ushort DcmDspDatasignal89;
    ushort EmixSumOfFaults;
    ushort BessSumOfFaults;
    ushort Sim100SumOfFaults;
    ushort EdsSumOfFaults;
    ushort DCDC1SumOfFaults;
    ushort DCDC2SumOfFaults;
    ushort SystemSumOfFaults;
    ushort DcmDspDatasignal99;
    ushort DcmDspDatasignal100;
    ushort DcmDspDatasignal101;
    float LVVoltageDCDC2;
    ushort DcmDspDatasignal103;
    uint SingleChargeTime;
    uint WorkingTimeRC;
    uint DcmDspDatasignal106;
    uint DcmDspDatasignal107;
    uint DcmDspDatasignal108;
    uint DcmDspDatasignal109;
    int DcmDspDatasignal110;
    int DcmDspDatasignal111;
    uchar EDSState;
    uchar DcChrgANegCantClose;
    uchar DcChrgANegWelded;
    uchar FaultCodeEDS;
    uchar EmixHvLevel;
    uchar BessHvLevel;
    uchar FaultCodeSIM100;
    uchar FaultCodeBESS;
    uchar FaultCodeDCDC1;
    uchar FaultCodeDCDC2;
    uchar FaultCodeOBC;
    uchar FaultCodeEMIX;
    uchar MarchState;
    uchar ChargeStatusBMS;
    ushort HVVoltageDCDC1;
    ushort HVVoltageDCDC2;
    ushort CurrentFeedbackRx;


    std::vector<DTCCanError> canErrors; // Utilizado para ver los errores generados durante el encendido
    std::vector<DTCCanError> allErrors; // Utilizado para ver todos los errores
    CANData();
    void readCanErrorsFromFile();
    void addError(int id);
    ~CANData();

    CANData* clone();

    bool operator==(CANData& other) const;

signals:
    // Señales enviadas al recibir un mensaje
    void message1();
    void message2();
    void message3();
    void message4();
    void message5();
    void message6();
    void message7();
    void bess1(int trama);
    void bess2(int trama);
    void bess3();
    void bess4();
    void bess5();
    void emix1();
    void faults1();
    void faults2();

    // Señal enviada al recibir un error
    void canError();
    void canTestigo(TESTIGOS testigo);

    void dbgMessage(QString msg);

    void updateMainWindow();

public slots:
    void receiveMessage(unsigned char sourceAddress, unsigned int pgn, uint8_t* receivedData);
    void receiveUDSMessage(uint8_t* receivedData);


};

#endif // CANDATA_H
