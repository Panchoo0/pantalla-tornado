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
    QString inhibitState = data->processVars.EMIX_inhibitState? "Estado\nnormal" : "Parada de\nemergencia";
    assert(ui->inhibitStateValue->text() == inhibitState);
    assert(ui->hvBusDischargedValue->checked == data->processVars.isHVBusDischarged);
    assert(ui->pduContactorCloseValue->checked == data->processVars.IsPDUmainRelayClosed);

    assert(ui->hvOnValue->checked == data->processVars.IsHVOn);
    assert(ui->dcdc1OvertempValue->checked == data->processVars.DCDC1Overtemp);
    assert(ui->dcdc2OvertempValue->checked == data->processVars.DCDC2Overtemp);

    assert(ui->atsFanFaultValue->checked == data->processVars.ATS_Fan_Fault);
    assert(ui->atsPumpFaultValue->checked == data->processVars.ATS_Pump_Fault);

    assert(ui->edsOvertempValue->checked == data->processVars.EDSOvertemp);
    assert(ui->obcOvertempValue->checked == data->processVars.OBCOvertemp);

    assert(ui->dcdcHighDifferenceValue->checked == data->processVars.DCDCsPwrDifference2Large);

    assert(ui->module1Value->checked == data->processVars.BESS_Module1TempTooLarge);
    assert(ui->module2Value->checked == data->processVars.BESS_Module2TempTooLarge);
    assert(ui->module3Value->checked == data->processVars.BESS_Module3TempTooLarge);
    assert(ui->module4Value->checked == data->processVars.BESS_Module4TempTooLarge);

    assert(ui->contactorPduValue->checked == data->processVars.PDUMainRelayCantChangeState);
    assert(ui->sim100StuckedValue->checked == data->processVars.Sim100Stuck);

    assert(ui->couldntPowerOnBMSValue->checked == data->processVars.ImpossibleToSwitchOnBMS);
    assert(ui->bessPowerOffHvValue->checked == data->processVars.BMSrequestsHvOff);
    assert(ui->requiredHvOffValue->checked == data->processVars.HvOffIsRequired);

    assert(ui->pedal1Value->checked == data->processVars.Pedal2Abnormal);
    assert(ui->pedal2Value->checked == data->processVars.Pedal1Abnormal);

    assert(ui->hvilPduValue->checked == data->processVars.PDU_HvilAlarm);
    assert(ui->hvilObcValue->checked == data->processVars.OBC_HvilAlarm);
    assert(ui->hvilEdsValue->checked == data->processVars.EDS_HvilAlarm);
    assert(ui->hvilDcdcValue->checked == data->processVars.DCDCs_HvilAlarm);

    assert(ui->termistorLVOutOfRangeValue->checked == data->processVars.LvThermistorOutOfRange);
    assert(ui->termistorHVOutOfRangeValue->checked == data->processVars.HvThermistorOutOfRange);

    assert(ui->pduTempExcessValue->checked == data->processVars.PDUOvertemp);
    assert(ui->overturnValue->checked == data->processVars.OverturnEvent);
    assert(ui->doorOpenValue->checked == data->processVars.CabinDoorOpen);
    assert(ui->parkingStateValue->checked == data->processVars.ParkingRelayState);

    QString marcha;
    switch (data->processVars.MarchState) {
    case 1:
        marcha = "Delante";
        break;
    case 2:
        marcha = "Neutro";
        break;
    case 3:
        marcha = "Trasera";
        break;
    default:
        break;
    }
    assert(ui->estadoMarchaValue->text() == marcha);
}

void ProcessVarsWidget::message7() {
    QString inhibitState = data->processVars.EMIX_inhibitState ? "Estado\nnormal" : "Parada de\nemergencia";
    ui->inhibitStateValue->setText(inhibitState);
    ui->hvBusDischargedValue->setChecked(data->processVars.isHVBusDischarged);
    ui->pduContactorCloseValue->setChecked(data->processVars.IsPDUmainRelayClosed);
    ui->hvOnValue->setChecked(data->processVars.IsHVOn);
    ui->dcdc1OvertempValue->setChecked(data->processVars.DCDC1Overtemp);
    ui->dcdc2OvertempValue->setChecked(data->processVars.DCDC2Overtemp);

    ui->atsFanFaultValue->setChecked(data->processVars.ATS_Fan_Fault);
    ui->atsPumpFaultValue->setChecked(data->processVars.ATS_Pump_Fault);

    ui->edsOvertempValue->setChecked(data->processVars.EDSOvertemp);
    ui->obcOvertempValue->setChecked(data->processVars.OBCOvertemp);

    ui->edsInErrorValue->setChecked(data->processVars.EDSinError);
    ui->edsCouldntClearValue->setChecked(data->processVars.EDScantClearError);

    ui->dcdcHighDifferenceValue->setChecked(data->processVars.DCDCsPwrDifference2Large);

    ui->module1Value->setChecked(data->processVars.BESS_Module1TempTooLarge);
    ui->module2Value->setChecked(data->processVars.BESS_Module2TempTooLarge);
    ui->module3Value->setChecked(data->processVars.BESS_Module3TempTooLarge);
    ui->module4Value->setChecked(data->processVars.BESS_Module4TempTooLarge);

    ui->contactorPduValue->setChecked(data->processVars.PDUMainRelayCantChangeState);
    ui->sim100StuckedValue->setChecked(data->processVars.Sim100Stuck);

    ui->couldntPowerOnBMSValue->setChecked(data->processVars.ImpossibleToSwitchOnBMS);
    ui->bessPowerOffHvValue->setChecked(data->processVars.BMSrequestsHvOff);
    ui->requiredHvOffValue->setChecked(data->processVars.HvOffIsRequired);

    ui->pedal1Value->setChecked(data->processVars.Pedal2Abnormal);
    ui->pedal2Value->setChecked(data->processVars.Pedal1Abnormal);

    ui->hvilPduValue->setChecked(data->processVars.PDU_HvilAlarm);
    ui->hvilObcValue->setChecked(data->processVars.OBC_HvilAlarm);
    ui->hvilEdsValue->setChecked(data->processVars.EDS_HvilAlarm);
    ui->hvilDcdcValue->setChecked(data->processVars.DCDCs_HvilAlarm);

    ui->termistorLVOutOfRangeValue->setChecked(data->processVars.LvThermistorOutOfRange);
    ui->termistorHVOutOfRangeValue->setChecked(data->processVars.HvThermistorOutOfRange);

    ui->pduTempExcessValue->setChecked(data->processVars.PDUOvertemp);
    ui->overturnValue->setChecked(data->processVars.OverturnEvent);
    ui->doorOpenValue->setChecked(data->processVars.CabinDoorOpen);
    ui->parkingStateValue->setChecked(data->processVars.ParkingRelayState);

    QString marcha;
    switch (data->processVars.MarchState) {
    case 1:
        marcha = "Delante";
        break;
    case 2:
        marcha = "Neutro";
        break;
    case 3:
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
