#ifndef CANDATA_H
#define CANDATA_H

#include <QObject>
#include "dtccanerror.h"

// Clase cuya función es almacenar todos los datos actualizados obtenidos a través del bus CAN
class CANData : public QObject
{
    Q_OBJECT

public:
    int speed; // Borrar

    // Message 1
    int batteryCurrent;
    int batteryVoltage;
    int SOC;

    // Message 2
    int engineCurrent;
    int engineTorque;
    int engineVoltage;
    int rpm;
    int setpoint;

    // Message 3
    int engineTemp;
    int inversorTemp;
    int batTemp;
    int batMaxTemp;
    int batMinTemp;

    // Message 4
    int dcdc1Current;
    int dcdc2Current;
    int dcdc1HVCurrent;
    int dcdc2HVCurrent;

    // Message 5
    int dcdc1OutputVoltage;
    int dcdc2OutputVoltage;
    int dcdc1InputVoltage;
    int dcdc2InputVoltage;

    // Message 6
    int posResistanceSIM100;
    int negResistanceSIM100;
    int posResistanceBMU;
    int negResistanceBMU;

    // Message 7
    int lvError;
    int hvError;

    int state;

    int inhibitState;
    int busHVDischarged;
    int pduContactorClose;

    int hvOn;
    int lvHigh;

    int dcdc1Overtemp;
    int dcdc2Overtemp;

    int atsFanFault;
    int atsPumpFault;

    int edsOvertemp;
    int obcOvertemp;

    int edsInError;
    int edsCouldntClear;

    int dcdcHighDifference;

    int batModule1;
    int batModule2;
    int batModule3;
    int batModule4;

    int contactorPdu;
    int sim100Stucked;

    int couldntPowerOnBMS;

    int bessPowerOffHv;
    int requiredHvOff;

    int pedal1Anormal;
    int pedal2Anormal;

    int hvilPdu;
    int hvilObc;
    int hvilEds;
    int hvilDddc;

    int termistorLVOutOfRange;
    int termistorHVOutOfRange;

    int pduTempExcess;
    int overturn;
    int doorOpen;
    int parkingState;
    int estadoMarcha;

    // Bess1
    int voltageCells[194 * 3];

    // Bess2
    int tempCells[18 * 6];

    // Bess3
    int chargeEnergyAcumulated;
    int dischargeEnergyAcumulated;
    int energyOneCharge;

    // Bess4
    int SOH;
    int minVoltage;
    int maxVoltage;
    int meanVoltage;

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

public slots:
    void receiveMessage(unsigned char sourceAddress, unsigned int pgn, uint8_t* receivedData);



};

#endif // CANDATA_H
