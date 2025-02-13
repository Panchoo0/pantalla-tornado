#include "batterypanel.h"
#include "ui_batterypanel.h"
#include <QListWidgetItem>
#include <QLabel>

BatteryPanel::BatteryPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BatteryPanel)
{
    ui->setupUi(this);

    // Se inicializa cada uno de las celdas de las baterías, creando su item ui
    for (int i = 0; i < 194; i++) {
        CellListItem *item = new CellListItem(ui->scrollAreaWidgetContents, i);
        item->setVoltage1(10);
        item->setVoltage2(12);
        item->setVoltage3(13);
        this->items[i] = item;
    }

    ui->scrollAreaWidgetContents->setMinimumSize(200, 1950);

    // Se inicializa cada una de las celdas de las temperaturas, creando su ui
    for (int i = 0; i < 18; i++) {
        TempListItem *item = new TempListItem(ui->tempCellTabScrollAreaWidgetContents, i);
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

