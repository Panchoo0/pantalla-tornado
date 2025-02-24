#include "enginewidget.h"
#include "ui_enginewidget.h"
#include <QDebug>

// Widget utilizar en la interfaz de información avanzada para mostrar los indicadores de los equipos
// como el motor
EngineWidget::EngineWidget(CANData *canData, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EngineWidget)
{
    ui->setupUi(this);
    this->canData = canData;
}

void EngineWidget::message2() {
    ui->currentValue->setText(QString::number(canData->engineCurrent) + " A");
    ui->torqueValue->setText(QString::number(canData->engineTorque) + " nm");
    ui->voltageValue->setText(QString::number(canData->engineVoltage) + " V");
    ui->RPMValue->setText(QString::number(canData->rpm) + " RPM");
    ui->setpointValue->setText(QString::number(canData->setpoint) + " RPM");
}

void EngineWidget::message3() {
    ui->tempValue->setText(QString::number(canData->engineTemp) + "° C");

}

void EngineWidget::message4() {
    ui->dcdc1OutputCurrentValue->setText(QString::number(canData->dcdc1Current) + " A");
    ui->dcdc2OutputCurrentValue->setText(QString::number(canData->dcdc2Current) + " A");
    ui->dcdc1InputCurrentHVValue->setText(QString::number(canData->dcdc1HVCurrent) + " A");
    ui->dcdc2InputCurrentHVValue->setText(QString::number(canData->dcdc2HVCurrent) + " A");

}

void EngineWidget::message5() {
    ui->dcdc1OutputVoltageValue->setText(QString::number(canData->dcdc1OutputVoltage) + " V");
    ui->dcdc2OutputVoltageValue->setText(QString::number(canData->dcdc2OutputVoltage) + " V");
    ui->dcdc1InputVoltageValue->setText(QString::number(canData->dcdc1InputVoltage) + " V");
    ui->dcdc2InputVoltageValue->setText(QString::number(canData->dcdc2InputVoltage) + " V");
}

void EngineWidget::message6() {
    ui->sim100posValue->setText(QString::number(canData->posResistanceSIM100) + " kΩ");
    ui->sim100negValue->setText(QString::number(canData->negResistanceSIM100) + " kΩ");
    ui->bmuposValue->setText(QString::number(canData->posResistanceBMU) + " kΩ");
    ui->bmunegValue->setText(QString::number(canData->negResistanceBMU) + " kΩ");

}

void EngineWidget::bess5() {
    ui->posTempDCChargeValue->setText(QString::number(canData->posChargeTempDC) + "° C");
    ui->negTempDCChargeValue->setText(QString::number(canData->negChargeTempDC) + "° C");

    int isDCConected = canData->dcConected;
    QString isDCConectedLabel;
    switch (isDCConected) {
    case 0: {
        isDCConectedLabel = "No conectada";
        break;
    }
    case 1: {
        isDCConectedLabel = "Pistola única\nconectada";
        break;
    }
    case 2: {
        isDCConectedLabel = "Pistola doble\nconectada";
        break;
    }
    default:
        break;
    }
    ui->chargeConectedValue->setText(isDCConectedLabel);
}

void EngineWidget::assertMessage2(int engineCurrent, int engineTorque, int engineVoltage, int rpm, int setpoint) {
    assert(
        ui->currentValue->text() == (QString::number(engineCurrent) + " A" )
    );

    assert(
        ui->torqueValue->text() == (QString::number(engineTorque) + " nm" )
    );

    assert(
        ui->voltageValue->text() == (QString::number(engineVoltage) + " V" )
    );

    assert(
        ui->RPMValue->text() == (QString::number(rpm) + " RPM" )
    );

    assert(
        ui->setpointValue->text() == (QString::number(setpoint) + " RPM" )
    );
}

void EngineWidget::assertMessage3(int engineTemp, int inversorTemp, int batTemp, int batMaxTemp, int batMinTemp) {
    assert(
        ui->tempValue->text() == (QString::number(engineTemp) + "° C")
    );
}

void EngineWidget::assertMessage4(int dcdc1Current, int dcdc2Current, int dcdc1HVCurrent, int dcdc2HVCurrent) {
    assert(
        ui->dcdc1OutputCurrentValue->text() == (QString::number(dcdc1Current) + " A")
    );

    assert(
        ui->dcdc2OutputCurrentValue->text() == (QString::number(dcdc2Current) + " A")
        );

    assert(
        ui->dcdc1InputCurrentHVValue->text() == (QString::number(dcdc1HVCurrent) + " A")
        );

    assert(
        ui->dcdc2InputCurrentHVValue->text() == (QString::number(dcdc2HVCurrent) + " A")
        );
}

void EngineWidget::assertMessage5(int dcdc1OutputVoltage, int dcdc2OutputVoltage, int dcdc1InputVoltage, int dcdc2InputVoltage) {
    assert(
        ui->dcdc1OutputVoltageValue->text() == (QString::number(dcdc1OutputVoltage) + " V")
        );

    assert(
        ui->dcdc2OutputVoltageValue->text() == (QString::number(dcdc2OutputVoltage) + " V")
        );

    assert(
        ui->dcdc1InputVoltageValue->text() == (QString::number(dcdc1InputVoltage) + " V")
        );

    assert(
        ui->dcdc2InputVoltageValue->text() == (QString::number(dcdc2InputVoltage) + " V")
        );
}

void EngineWidget::assertMessage6(int posResistanceSIM100, int negResistanceSIM100, int posResistanceBMU, int negResistanceBMU) {
    assert(
        ui->sim100posValue->text() == QString::number(posResistanceSIM100) + " kΩ"
        );

    assert(
        ui->sim100negValue->text() == QString::number(negResistanceSIM100) + " kΩ"
        );

    assert(
        ui->bmuposValue->text() == QString::number(posResistanceBMU) + " kΩ"
        );

    assert(
        ui->bmunegValue->text() == QString::number(negResistanceBMU) + " kΩ"
        );
}

void EngineWidget::assertBess5(int posChargeTempDC, int negChargeTempDC, int dcConected, int bmsChargingMode, int coolingState, int heatState, int bmuContactor, int bmsFailures) {
    assert(
        ui->posTempDCChargeValue->text() == (QString::number(posChargeTempDC) + "° C")
    );

    assert(
        ui->negTempDCChargeValue->text() == (QString::number(negChargeTempDC) + "° C")
        );

    QString isDCConectedLabel;
    switch (dcConected) {
    case 0: {
        isDCConectedLabel = "No conectada";
        break;
    }
    case 1: {
        isDCConectedLabel = "Pistola única\nconectada";
        break;
    }
    case 2: {
        isDCConectedLabel = "Pistola doble\nconectada";
        break;
    }
    default:
        break;
    }

    assert(
        ui->chargeConectedValue->text() == isDCConectedLabel
        );
}

EngineWidget::~EngineWidget()
{
    delete ui;
}
