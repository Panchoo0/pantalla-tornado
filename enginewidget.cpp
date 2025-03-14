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
    ui->currentValue->setText(QString::number(canData->eds.instCurr) + " A");
    ui->torqueValue->setText(QString::number(canData->eds.instTorque) + " nm");
    ui->voltageValue->setText(QString::number(canData->eds.instVoltage) + " V");
    ui->RPMValue->setText(QString::number(canData->eds.instRPM) + " RPM");
    ui->setpointValue->setText(QString::number(canData->eds.txSetpoint) + " RPM");
}

void EngineWidget::message3() {
    ui->tempValue->setText(QString::number(canData->eds.motorTemp) + "° C");

}

void EngineWidget::message4() {
    ui->dcdc1OutputCurrentValue->setText(QString::number(canData->dcdc1.lvCurr) + " A");
    ui->dcdc2OutputCurrentValue->setText(QString::number(canData->dcdc2.lvCurr) + " A");
    ui->dcdc1InputCurrentHVValue->setText(QString::number(canData->dcdc1.hvCurr) + " A");
    ui->dcdc2InputCurrentHVValue->setText(QString::number(canData->dcdc2.hvCurr) + " A");

}

void EngineWidget::message5() {
    ui->dcdc1OutputVoltageValue->setText(QString::number(canData->dcdc1.VVout) + " V");
    ui->dcdc2OutputVoltageValue->setText(QString::number(canData->dcdc2.VVout) + " V");
    ui->dcdc1InputVoltageValue->setText(QString::number(canData->dcdc1.Vin) + " V");
    ui->dcdc2InputVoltageValue->setText(QString::number(canData->dcdc2.Vin) + " V");
}

void EngineWidget::message6() {
    ui->sim100posValue->setText(QString::number(canData->sim100.Rp) + " kΩ");
    ui->sim100negValue->setText(QString::number(canData->sim100.Rn) + " kΩ");
    ui->bmuposValue->setText(QString::number(canData->bess.Rp) + " kΩ");
    ui->bmunegValue->setText(QString::number(canData->bess.Rn) + " kΩ");

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

void EngineWidget::assertMessage2() {
    assert(
        ui->currentValue->text() == (QString::number(canData->eds.instCurr) + " A" )
    );

    assert(
        ui->torqueValue->text() == (QString::number(canData->eds.instTorque) + " nm" )
    );

    assert(
        ui->voltageValue->text() == (QString::number(canData->eds.instVoltage) + " V" )
    );

    assert(
        ui->RPMValue->text() == (QString::number(canData->eds.instRPM) + " RPM" )
    );

    assert(
        ui->setpointValue->text() == (QString::number(canData->eds.txSetpoint) + " RPM" )
    );
}

void EngineWidget::assertMessage3() {
    assert(
        ui->tempValue->text() == (QString::number(canData->eds.motorTemp) + "° C")
    );
}

void EngineWidget::assertMessage4() {
    assert(
        ui->dcdc1OutputCurrentValue->text() == (QString::number(canData->dcdc1.lvCurr) + " A")
    );

    assert(
        ui->dcdc2OutputCurrentValue->text() == (QString::number(canData->dcdc2.lvCurr) + " A")
        );

    assert(
        ui->dcdc1InputCurrentHVValue->text() == (QString::number(canData->dcdc1.hvCurr) + " A")
        );

    assert(
        ui->dcdc2InputCurrentHVValue->text() == (QString::number(canData->dcdc2.hvCurr) + " A")
        );
}

void EngineWidget::assertMessage5() {
    assert(
        ui->dcdc1OutputVoltageValue->text() == (QString::number(canData->dcdc1.VVout) + " V")
        );

    assert(
        ui->dcdc2OutputVoltageValue->text() == (QString::number(canData->dcdc2.VVout) + " V")
        );

    assert(
        ui->dcdc1InputVoltageValue->text() == (QString::number(canData->dcdc1.Vin) + " V")
        );

    assert(
        ui->dcdc2InputVoltageValue->text() == (QString::number(canData->dcdc2.Vin) + " V")
        );
}

void EngineWidget::assertMessage6() {
    assert(
        ui->sim100posValue->text() == QString::number(canData->sim100.Rp) + " kΩ"
        );

    assert(
        ui->sim100negValue->text() == QString::number(canData->sim100.Rn) + " kΩ"
        );

    assert(
        ui->bmuposValue->text() == QString::number(canData->bess.Rp) + " kΩ"
        );

    assert(
        ui->bmunegValue->text() == QString::number(canData->bess.Rn) + " kΩ"
        );
}

void EngineWidget::assertBess5() {
    assert(
        ui->posTempDCChargeValue->text() == (QString::number(canData->posChargeTempDC) + "° C")
    );

    assert(
        ui->negTempDCChargeValue->text() == (QString::number(canData->negChargeTempDC) + "° C")
        );

    QString isDCConectedLabel;
    switch (canData->dcConected) {
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
