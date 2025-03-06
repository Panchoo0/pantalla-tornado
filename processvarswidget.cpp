#include "processvarswidget.h"
#include "ui_processvarswidget.h"
#include <checkboxwidget.h>
#include <QDebug>
#include <QScroller>
#include <utils.h>

// Widget que se encarga de mostrar la información de las variables de proceso en el panel de información avanzada.
ProcessVarsWidget::ProcessVarsWidget(CANData *data, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProcessVarsWidget)
{
    ui->setupUi(this);

    ui->scrollAreaWidgetContents->setMinimumSize(200, 1050);

    // Habilitamos el scroll mediante el gesto de arrastre
    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);

    this->data = data;
}

void ProcessVarsWidget::assertMessage7() {
    QString inhibitState = data->inhibitState == 1 ? "Estado\nnormal" : "Parada de\nemergencia";
    assert(ui->inhibitStateValue->text() == inhibitState);
    assert(ui->hvBusDischargedValue->checked == (data->busHVDischarged == 1));
    assert(ui->pduContactorCloseValue->checked == (data->pduContactorClose == 1));

    assert(ui->hvOnValue->checked == (data->hvOn == 1));
    assert(ui->dcdc1OvertempValue->checked == (data->dcdc1Overtemp == 1));
    assert(ui->dcdc2OvertempValue->checked == (data->dcdc2Overtemp == 1));

    assert(ui->atsFanFaultValue->checked == (data->atsFanFault == 1));
    assert(ui->atsPumpFaultValue->checked == (data->atsPumpFault == 1));

    assert(ui->edsOvertempValue->checked == (data->edsOvertemp== 1));
    assert(ui->obcOvertempValue->checked == (data->obcOvertemp == 1));

    assert(ui->dcdcHighDifferenceValue->checked == (data->dcdcHighDifference == 1));

    assert(ui->module1Value->checked == (data->batModule1 == 1));
    assert(ui->module2Value->checked == (data->batModule2 == 1));
    assert(ui->module3Value->checked == (data->batModule3 == 1));
    assert(ui->module4Value->checked == (data->batModule4 == 1));

    assert(ui->contactorPduValue->checked == (data->contactorPdu == 1));
    assert(ui->sim100StuckedValue->checked == (data->sim100Stucked == 1));

    assert(ui->couldntPowerOnBMSValue->checked == (data->couldntPowerOnBMS == 1));
    assert(ui->bessPowerOffHvValue->checked == (data->bessPowerOffHv == 1));
    assert(ui->requiredHvOffValue->checked == (data->requiredHvOff == 1));

    assert(ui->pedal1Value->checked == (data->pedal1Anormal == 1));
    assert(ui->pedal2Value->checked == (data->pedal2Anormal == 1));

    assert(ui->hvilPduValue->checked == (data->hvilPdu == 1));
    assert(ui->hvilObcValue->checked == (data->hvilObc == 1));
    assert(ui->hvilEdsValue->checked == (data->hvilEds == 1));
    assert(ui->hvilDcdcValue->checked == (data->hvilDddc == 1));

    assert(ui->termistorLVOutOfRangeValue->checked == (data->termistorLVOutOfRange == 1));
    assert(ui->termistorHVOutOfRangeValue->checked == (data->termistorHVOutOfRange == 1));

    assert(ui->pduTempExcessValue->checked == (data->pduTempExcess == 1));
    assert(ui->overturnValue->checked == (data->overturn == 1));
    assert(ui->doorOpenValue->checked == (data->doorOpen == 1));
    assert(ui->parkingStateValue->checked == (data->parkingState == 1));

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
    assert(ui->estadoMarchaValue->text() == marcha);
}

void ProcessVarsWidget::message7() {
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

void ProcessVarsWidget::assertBess5() {
    QString bmsChargingMode;
    switch (data->bmsChargingMode) {
    case 0:
        bmsChargingMode = "No\nConectada";
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
    assert(ui->bmsChargingModeValue->text() == bmsChargingMode);

    QString heatingState = data->heatState == 1 ? "Calentando" : "No\ncalentando";
    QString coolingState = data->coolingState == 1 ? "Enfriando" : "No\nenfriando";
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

    assert(ui->heatStateValue->text() == heatingState);
    assert(ui->coolingStateValue->text() == coolingState);
    assert(ui->bmuContactorValue->text() == bmuState);
    assert(ui->bmsFailuresValue->text() == QString::number(data->bmsFailures));


}

void ProcessVarsWidget::bess5() {
    QString bmsChargingMode;
    switch (data->bmsChargingMode) {
    case 0:
        bmsChargingMode = "No\nConectada";
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

    QString heatingState = data->heatState == 1 ? "Calentando" : "No\ncalentando";
    QString coolingState = data->coolingState == 1 ? "Enfriando" : "No\nenfriando";
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

void ProcessVarsWidget::assertEmix1() {
    assert(ui->edsFailuresValue->text() == QString::number(data->edsFailures));
    assert(ui->dcdc1FailuresValue->text() == QString::number(data->dcdc1Failures));
    assert(ui->dcdc2FailuresValue->text() == QString::number(data->dcdc2Failures));
    assert(ui->sim100FailuresValue->text() == QString::number(data->sim100Failures));
    assert(ui->obcFailuresValue->text() == QString::number(data->obcFailures));
    assert(ui->emixFailuresValue->text() == QString::number(data->emixFailures));
}

void ProcessVarsWidget::emix1() {
    ui->edsFailuresValue->setText(QString::number(data->edsFailures));
    ui->dcdc1FailuresValue->setText(QString::number(data->dcdc1Failures));
    ui->dcdc2FailuresValue->setText(QString::number(data->dcdc2Failures));
    ui->sim100FailuresValue->setText(QString::number(data->sim100Failures));
    ui->obcFailuresValue->setText(QString::number(data->obcFailures));
    ui->emixFailuresValue->setText(QString::number(data->emixFailures));
}

void ProcessVarsWidget::assertFaults1() {
    uchar b1 = this->data->dcdc1ErrorCode >> 8;
    uchar b2 = this->data->dcdc1ErrorCode & 0xFF;
    uchar data1[] = {b1, b2};
    assert(ui->dcdcd1ErrorCodeValue->text() == Utils::toHexString(data1, 2));

    uchar b3 = this->data->dcdc2ErrorCode >> 8;
    uchar b4 = this->data->dcdc2ErrorCode & 0xFF;
    uchar data2[] = {b3, b4};
    assert(ui->dcdcd2ErrorCodeValue->text() == Utils::toHexString(data2, 2));
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

void ProcessVarsWidget::assertFaults2() {
    uchar b5 = this->data->edsErrorCode >> 8;
    uchar b6 = this->data->edsErrorCode & 0xFF;
    uchar data3[] = {b5, b6};
    assert(ui->edsErrorCodeValue->text() == Utils::toHexString(data3, 2));

    uchar b7 = this->data->obcErrorCode >> 8;
    uchar b8 = this->data->obcErrorCode & 0xFF;
    uchar data4[] = {b7, b8};
    assert(ui->obcErrorCodeValue->text() == Utils::toHexString(data4, 2));
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
