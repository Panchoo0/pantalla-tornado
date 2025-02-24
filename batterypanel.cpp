#include "batterypanel.h"
#include "ui_batterypanel.h"
#include <QListWidgetItem>
#include <QLabel>
#include <QDebug>

BatteryPanel::BatteryPanel(CANData *data, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BatteryPanel)
{
    canData = data;
    ui->setupUi(this);

    // Se inicializa cada uno de las celdas de las baterías, creando su item ui
    for (int i = 0; i < 194; i++) {
        CellListItem *item = new CellListItem(ui->scrollAreaWidgetContents, i);
        this->items[i] = item;
    }

    ui->scrollAreaWidgetContents->setMinimumSize(200, 1950);

    // Se inicializa cada una de las celdas de las temperaturas, creando su ui
    for (int i = 0; i < 18; i++) {
        TempListItem *item = new TempListItem(ui->tempCellTabScrollAreaWidgetContents, i);
        this->tempItems[i] = item;
    }

    ui->tempCellTabScrollAreaWidgetContents->setMinimumSize(200, 550);
}

BatteryPanel::~BatteryPanel()
{
    delete ui;
}

// Función que cambia la pestaña seleccionada en el menú de batería
void BatteryPanel::changeCurrentTab(int index) {
    ui->tabWidget->setCurrentIndex(index);
    QString highligthText = "border-bottom: 4px solid #00A6A7; \nborder-radius: 5px; \ncolor: #00A6A7;\nfont-size: 14px;";
    QString normalText = "border-bottom: 2px solid #656565; \nborder-radius: 5px; \ncolor: #656565;\nfont-size: 14px;";

    // Se cambia el estilo para que quede marcado la pestaña seleccionada
    if (index == 0) {
        ui->generalInfo->setStyleSheet(highligthText);
        ui->voltageInfo->setStyleSheet(normalText);
        ui->tempInfo->setStyleSheet(normalText);
    } else if (index == 1) {
        ui->generalInfo->setStyleSheet(normalText);
        ui->voltageInfo->setStyleSheet(highligthText);
        ui->tempInfo->setStyleSheet(normalText);
    } else {
        ui->generalInfo->setStyleSheet(normalText);
        ui->voltageInfo->setStyleSheet(normalText);
        ui->tempInfo->setStyleSheet(highligthText);
    }
}

void BatteryPanel::on_generalInfo_clicked()
{
    this->changeCurrentTab(0);
}


void BatteryPanel::on_voltageInfo_clicked()
{
    this->changeCurrentTab(1);
}


void BatteryPanel::on_tempInfo_clicked()
{
    this->changeCurrentTab(2);
}

void BatteryPanel::message1() {
    ui->instantCurrentValue->setText(QString::number(canData->batteryCurrent) + " A");
    ui->instantVoltageValue->setText(QString::number(canData->batteryVoltage) + " V");
    ui->SOCValue->setText(QString::number(canData->SOC) + " %");
}

void BatteryPanel::message3() {
    ui->meanTempValue->setText(QString::number(canData->batTemp) + "° C");
    ui->minTempValue->setText(QString::number(canData->batMinTemp) + "° C");
    ui->maxTempValue->setText(QString::number(canData->batMaxTemp) + "° C");
}

void BatteryPanel::message7() {
    QString highLVHigh;
    switch (canData->lvHigh) {
    case 0:
        highLVHigh = "Normal";
        break;
    case 1:
        highLVHigh = "Voltaje\nalto";
    case 2:
        highLVHigh = "Voltaje\nmuy alto";
    default:
        break;
    }
    ui->highLVValue->setText(highLVHigh);
}

void BatteryPanel::bess1(int trama) {
    items[trama]->setVoltage1(canData->voltageCells[trama * 3]);
    items[trama]->setVoltage2(canData->voltageCells[trama * 3 + 1]);
    items[trama]->setVoltage3(canData->voltageCells[trama * 3 + 2]);
}

void BatteryPanel::bess2(int trama) {
    tempItems[trama]->updateT1(canData->tempCells[trama * 6]);
    tempItems[trama]->updateT2(canData->tempCells[trama * 6 + 1]);
    tempItems[trama]->updateT3(canData->tempCells[trama * 6 + 2]);
    tempItems[trama]->updateT4(canData->tempCells[trama * 6 + 3]);
    tempItems[trama]->updateT5(canData->tempCells[trama * 6 + 4]);
    tempItems[trama]->updateT6(canData->tempCells[trama * 6 + 5]);
}

void BatteryPanel::bess3() {
    ui->chargeEnergyValue->setText(QString::number(canData->chargeEnergyAcumulated) + " kwh");
    ui->dischargeEnergyValue->setText(QString::number(canData->dischargeEnergyAcumulated) + " kwh");
    ui->oneChargeEnergyValue->setText(QString::number(canData->energyOneCharge) + " kwh");
}

void BatteryPanel::bess4() {
    ui->SOHValue->setText(QString::number(canData->SOH) + " %");
    ui->maxCellVoltageValue->setText(QString::number(canData->maxVoltage) + " V");
    ui->minCellVoltageValue->setText(QString::number(canData->minVoltage) +  " V");
    ui->meanCellVoltageValue->setText(QString::number(canData->meanVoltage) + " V");
}

void BatteryPanel::assertMessage1(int current, int voltage, int soc) {
    assert(
        ui->instantCurrentValue->text() == (QString::number(current) + " A")
    );

    assert(
        ui->instantVoltageValue->text() == (QString::number(voltage) + " V")
    );

    assert(
        ui->SOCValue->text() == (QString::number(soc) + " %")
    );
}

void BatteryPanel::assertMessage3(int engineTemp, int inversorTemp, int batTemp, int batMaxTemp, int batMinTemp) {
    assert(
        ui->meanTempValue->text() == (QString::number(batTemp) + "° C")
        );

    assert(
        ui->maxTempValue->text() == (QString::number(batMaxTemp) + "° C")
        );

    assert(
        ui->minTempValue->text() == (QString::number(batMinTemp) + "° C")
        );
}

void BatteryPanel::assertBess1(int trama, int v1, int v2, int v3) {
    assert(
        this->items[trama ]->v1->text() == (QString::number(v1) +  " V")
        );
    assert(
        this->items[trama]->v2->text() == (QString::number(v2) +  " V")
        );
    assert(
        this->items[trama]->v3->text() == (QString::number(v3) +  " V")
        );
}

void BatteryPanel::assertBess2(int trama, int t1, int t2, int t3, int t4, int t5, int t6) {

    assert(
        this->tempItems[trama]->t1->text() == (QString::number(t1) +  "° C")
        );

    assert(
        this->tempItems[trama]->t2->text() == (QString::number(t2) +  "° C")
        );

    assert(
        this->tempItems[trama]->t3->text() == (QString::number(t3) +  "° C")
        );

    assert(
        this->tempItems[trama]->t4->text() == (QString::number(t4) +  "° C")
        );

    assert(
        this->tempItems[trama]->t5->text() == (QString::number(t5) +  "° C")
        );

    assert(
        this->tempItems[trama]->t6->text() == (QString::number(t6) +  "° C")
        );
}

void BatteryPanel::assertBess3(int chargeEnergyAcumulated, int dischargeEnergyAcumulated, int energyOneCharge) {
    assert(
        ui->chargeEnergyValue->text() == (QString::number(chargeEnergyAcumulated) + " kwh")
        );

    assert(
        ui->dischargeEnergyValue->text() == (QString::number(dischargeEnergyAcumulated) + " kwh")
        );

    assert(
        ui->oneChargeEnergyValue->text() == (QString::number(energyOneCharge) + " kwh")
        );
}

void BatteryPanel::assertBess4(int SOC, int SOH, int minVoltage, int maxVoltage, int meanVoltage) {
    assert(
        ui->SOHValue->text() == (QString::number(SOH) + " %")
    );

    assert(
        ui->maxCellVoltageValue->text() == (QString::number(maxVoltage) + " V")
        );

    assert(
        ui->minCellVoltageValue->text() == (QString::number(minVoltage) + " V")
        );

    assert(
        ui->meanCellVoltageValue->text() == (QString::number(meanVoltage) + " V")
        );
}
