#include "batterypanel.h"
#include "ui_batterypanel.h"
#include <QListWidgetItem>
#include <QLabel>
#include <QDebug>

#include <QScroller>


// Widget que maneja la información de la batería en el panel de información avanzada
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

    // Habilitamos el scroll mediante el gesto de arrastrar
    QScroller::grabGesture(ui->tempCellTabScrollArea, QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
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
    ui->instantCurrentValue->setText(QString::number(canData->bess.inst_current) + " A");
    ui->instantVoltageValue->setText(QString::number(canData->bess.inst_voltage) + " V");
    ui->SOCValue->setText(QString::number(canData->bess.SoC) + " %");
}

void BatteryPanel::message3() {
    ui->meanTempValue->setText(QString::number(canData->bess.avgTemp) + "° C");
    ui->minTempValue->setText(QString::number(canData->bess.minTemp) + "° C");
    ui->maxTempValue->setText(QString::number(canData->bess.maxTemp) + "° C");
}

void BatteryPanel::message7() {
    QString highLVHigh;
    switch (canData->processVars.LvVoltageTooHigh) {
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
    items[trama]->setVoltage1(canData->voltageCells[trama]);
    items[trama + 1]->setVoltage1(canData->voltageCells[trama + 1]);
    items[trama + 2]->setVoltage1(canData->voltageCells[trama + 2]);
}

void BatteryPanel::bess2(int trama) {
    tempItems[trama]->updateT1(canData->tempCells[trama]);
    tempItems[trama + 1]->updateT1(canData->tempCells[trama + 1]);
    tempItems[trama + 2]->updateT1(canData->tempCells[trama + 2]);
    tempItems[trama + 3]->updateT1(canData->tempCells[trama + 3]);
    tempItems[trama + 4]->updateT1(canData->tempCells[trama + 4]);
    tempItems[trama + 5]->updateT1(canData->tempCells[trama + 5]);
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

void BatteryPanel::assertMessage1() {
    assert(
        ui->instantCurrentValue->text() == (QString::number(canData->bess.inst_current) + " A")
    );

    assert(
        ui->instantVoltageValue->text() == (QString::number(canData->bess.inst_voltage) + " V")
    );

    assert(
        ui->SOCValue->text() == (QString::number(canData->bess.SoC) + " %")
    );
}

void BatteryPanel::assertMessage3() {
    assert(
        ui->meanTempValue->text() == (QString::number(canData->bess.avgTemp) + "° C")
        );

    assert(
        ui->maxTempValue->text() == (QString::number(canData->bess.maxTemp) + "° C")
        );

    assert(
        ui->minTempValue->text() == (QString::number(canData->bess.minTemp) + "° C")
        );
}

void BatteryPanel::assertBess1(int trama, float v1, float v2, float v3) {
    assert(
        this->items[trama - 1]->v1->text() == (QString::number(v1) +  " V")
        );
    assert(
        this->items[trama]->v1->text() == (QString::number(v2) +  " V")
        );
    assert(
        this->items[trama + 1]->v1->text() == (QString::number(v3) +  " V")
        );
}

void BatteryPanel::assertBess2(int trama, int t1, int t2, int t3, int t4, int t5, int t6) {

    assert(
        this->tempItems[trama - 1]->t1->text() == (QString::number(t1) +  "° C")
        );

    assert(
        this->tempItems[trama]->t1->text() == (QString::number(t2) +  "° C")
        );

    assert(
        this->tempItems[trama + 1]->t1->text() == (QString::number(t3) +  "° C")
        );

    assert(
        this->tempItems[trama + 2]->t1->text() == (QString::number(t4) +  "° C")
        );

    assert(
        this->tempItems[trama + 3]->t1->text() == (QString::number(t5) +  "° C")
        );

    assert(
        this->tempItems[trama + 4]->t1->text() == (QString::number(t6) +  "° C")
        );
}

void BatteryPanel::assertBess3(int chargeEnergyAcumulated, int dischargeEnergyAcumulated, float energyOneCharge) {
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

void BatteryPanel::assertBess4() {
    assert(
        ui->SOHValue->text() == (QString::number(canData->SOH) + " %")
    );

    assert(
        ui->maxCellVoltageValue->text() == (QString::number(canData->maxVoltage) + " V")
        );

    assert(
        ui->minCellVoltageValue->text() == (QString::number(canData->minVoltage) + " V")
        );

    assert(
        ui->meanCellVoltageValue->text() == (QString::number(canData->meanVoltage) + " V")
        );
}
