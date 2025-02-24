#include "processvarswidget.h"
#include "ui_processvarswidget.h"
#include <checkboxwidget.h>
#include <QDebug>
#include <utils.h>

ProcessVarsWidget::ProcessVarsWidget(CANData *data, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProcessVarsWidget)
{
    ui->setupUi(this);

    ui->scrollAreaWidgetContents->setMinimumSize(200, 1375);

    this->data = data;
}

void ProcessVarsWidget::message7() {
    qInfo() << "message 7";
    QString inhibitState = data->inhibitState == 1 ? "Estado\nnormal" : "Parada de\nemergencia";
    ui->inhibitStateValue->setText(inhibitState);
    ui->hvBusDischargedValue->setChecked(data->busHVDischarged == 1);
    ui->pduContactorCloseValue->setChecked(data->pduContactorClose == 1);
    ui->hvOnValue->setChecked(data->hvOn == 1);
    ui->dcdc1OvertempValue->setChecked(data->dcdc1Overtemp == 1);
    ui->dcdc2OvertempValue->setChecked(data->dcdc2Overtemp == 1);

    ui->atsFanFaultValue->setChecked(data->atsFanFault == 1);
    ui->atsPumpFaultValue->setChecked(data->atsPumpFault == 1);

    ui->edsOvertempValue->setChecked(data->edsOvertemp == 1);
    ui->obcOvertempValue->setChecked(data->obcOvertemp == 1);

    ui->edsInErrorValue->setChecked(data->edsInError == 1);
    ui->edsCouldntClearValue->setChecked(data->edsCouldntClear == 1);

    ui->dcdcHighDifferenceValue->setChecked(data->dcdcHighDifference == 1);

    ui->module1Value->setChecked(data->batModule1 == 1);
    ui->module2Value->setChecked(data->batModule2 == 1);
    ui->module3Value->setChecked(data->batModule3 == 1);
    ui->module4Value->setChecked(data->batModule4 == 1);

    ui->contactorPduValue->setChecked(data->contactorPdu == 1);
    ui->sim100StuckedValue->setChecked(data->sim100Stucked == 1);

    ui->couldntPowerOnBMSValue->setChecked(data->couldntPowerOnBMS == 1);
    ui->bessPowerOffHvValue->setChecked(data->bessPowerOffHv == 1);
    ui->requiredHvOffValue->setChecked(data->requiredHvOff == 1);

    ui->pedal1Value->setChecked(data->pedal1Anormal == 1);
    ui->pedal2Value->setChecked(data->pedal2Anormal == 1);

    ui->hvilPduValue->setChecked(data->hvilPdu == 1);
    ui->hvilObcValue->setChecked(data->hvilObc == 1);
    ui->hvilEdsValue->setChecked(data->hvilEds == 1);
    ui->hvilDcdcValue->setChecked(data->hvilDddc == 1);

    ui->termistorLVOutOfRangeValue->setChecked(data->termistorLVOutOfRange);
    ui->termistorHVOutOfRangeValue->setChecked(data->termistorHVOutOfRange);

    ui->pduTempExcessValue->setChecked(data->pduTempExcess == 1);
    ui->overturnValue->setChecked(data->overturn == 1);
    ui->doorOpenValue->setChecked(data->doorOpen == 1);
    ui->parkingStateValue->setChecked(data->parkingState == 1);

    QString marcha;
    switch (data->estadoMarcha) {
    case 0:
        marcha = "Neutro";
        break;
    case 1:
        marcha = "Delante";
        break;
    case 2:
        marcha = "Trasera";
        break;
    default:
        break;
    }
    ui->estadoMarchaValue->setText(marcha);
}

void ProcessVarsWidget::bess5() {
    QString bmsChargingMode;
    switch (data->bmsChargingMode) {
    case 0:
        bmsChargingMode = "No Conectada";
        break;
    case 1:
        bmsChargingMode = "Pistola única\nconectada";
        break;
    case 2:
        bmsChargingMode = "Pistola doble\nconectada";
        break;
    default:
        break;
    }
    ui->bmsChargingModeValue->setText(bmsChargingMode);

    QString heatingState = data->heatState == 1 ? "Calentando" : "No calentando";
    QString coolingState = data->coolingState == 1 ? "Enfriando" : "No enfriando";
    QString bmuState;
    switch (data->bmuContactor) {
    case 1:
        bmuState = "Abierto";
        break;
    case 2:
        bmuState = "Cerrado";
        break;
    case 3:
        bmuState = "Inválido";
        break;
    default:
        break;
    }

    ui->heatStateValue->setText(heatingState);
    ui->coolingStateValue->setText(coolingState);
    ui->bmuContactorValue->setText(bmuState);

    ui->bmsFailuresValue->setText(QString::number(data->bmsFailures));
}

void ProcessVarsWidget::emix1() {
    ui->edsFailuresValue->setText(QString::number(data->edsFailures));
    ui->dcdc1FailuresValue->setText(QString::number(data->dcdc1Failures));
    ui->dcdc2FailuresValue->setText(QString::number(data->dcdc2Failures));
    ui->sim100FailuresValue->setText(QString::number(data->sim100Failures));
    ui->obcFailuresValue->setText(QString::number(data->obcFailures));
    ui->emixFailuresValue->setText(QString::number(data->emixFailures));
}

void ProcessVarsWidget::faults1() {
    uchar b1 = this->data->dcdc1ErrorCode >> 8;
    uchar b2 = this->data->dcdc1ErrorCode & 0xFF;
    uchar data1[] = {b1, b2};
    ui->dcdcd1ErrorCodeValue->setText(Utils::toHexString(data1, 2));

    uchar b3 = this->data->dcdc2ErrorCode >> 8;
    uchar b4 = this->data->dcdc2ErrorCode & 0xFF;
    uchar data2[] = {b3, b4};
    ui->dcdcd2ErrorCodeValue->setText(Utils::toHexString(data2, 2));


}

void ProcessVarsWidget::faults2() {
    uchar b5 = this->data->edsErrorCode >> 8;
    uchar b6 = this->data->edsErrorCode & 0xFF;
    uchar data3[] = {b5, b6};
    ui->edsErrorCodeValue->setText(Utils::toHexString(data3, 2));

    uchar b7 = this->data->obcErrorCode >> 8;
    uchar b8 = this->data->obcErrorCode & 0xFF;
    uchar data4[] = {b7, b8};
    ui->obcErrorCodeValue->setText(Utils::toHexString(data4, 2));
}

ProcessVarsWidget::~ProcessVarsWidget()
{
    delete ui;
}
