#include "adminpanel.h"
#include "ui_adminpanel.h"
#include <QProxyStyle>
#include <QStyleOption>
#include <qobject.h>
#include <QDebug>

AdminPanel::AdminPanel(CANData *canData,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminPanel)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    this->canData = canData;

    // Creamos el panel de la información del motor
    engineWidget = new EngineWidget(canData, this);
    engineWidget->setGeometry(125, 0, 675, 440);
    engineWidget->hide();

    // Creamos el panel que muestra la información de la baterías
    errorsPanel = new ErrorsPanel(canData, this);
    errorsPanel->setGeometry(125, 0, 675, 440);
    errorsPanel->hide();

    batteryPanel = new BatteryPanel(canData, this);
    batteryPanel->setGeometry(125, 0, 675, 440);
    batteryPanel->hide();

    processVarsWidget = new ProcessVarsWidget(canData, this);
    processVarsWidget->setGeometry(125, 0, 675, 440);
    processVarsWidget->hide();

    this->onTabChange(TABS::ENGINE);

    // Nos aseguramos de que el botón para cerrar el widget quede por encima del resto de widgets
    this->engineWidget->stackUnder(ui->closeButton);
    this->errorsPanel->stackUnder(ui->closeButton);
    this->batteryPanel->stackUnder(ui->closeButton);
    this->processVarsWidget->stackUnder(ui->closeButton);

    this->hide();
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

// Función que actualiza la UI al hacer click sobre uno de los botones del panel de navegación
void AdminPanel::onTabChange(TABS tab) {
    QString defaultTabButtonStyle = "background-color: transparent; border: none; color: white";
    QString highlightedTabButtonStyle = "background-color: transparent; border: 4px solid #00A6A7; color: #00A6A7";

    // Primero se actualiza el estilo para los botones, destacando al que esté seleccionado
    switch (tab) {
    case TABS::ENGINE:
        ui->engineTabButton->setStyleSheet(highlightedTabButtonStyle);
        ui->batteryTabButton->setStyleSheet(defaultTabButtonStyle);
        ui->processVarsButton->setStyleSheet(defaultTabButtonStyle);
        ui->errorsTabButton->setStyleSheet(defaultTabButtonStyle);

        engineWidget->show();
        errorsPanel->hide();
        batteryPanel->hide();
        processVarsWidget->hide();
        break;
    case TABS::BATTERY:
        ui->engineTabButton->setStyleSheet(defaultTabButtonStyle);
        ui->batteryTabButton->setStyleSheet(highlightedTabButtonStyle);
        ui->processVarsButton->setStyleSheet(defaultTabButtonStyle);
        ui->errorsTabButton->setStyleSheet(defaultTabButtonStyle);

        engineWidget->hide();
        errorsPanel->hide();
        batteryPanel->show();
        processVarsWidget->hide();
        break;
    case TABS::PROCESS_VARS:
        ui->engineTabButton->setStyleSheet(defaultTabButtonStyle);
        ui->batteryTabButton->setStyleSheet(defaultTabButtonStyle);
        ui->processVarsButton->setStyleSheet(highlightedTabButtonStyle);
        ui->errorsTabButton->setStyleSheet(defaultTabButtonStyle);

        engineWidget->hide();
        errorsPanel->hide();
        batteryPanel->hide();
        processVarsWidget->show();
        break;
    case TABS::ERRORS:
        ui->engineTabButton->setStyleSheet(defaultTabButtonStyle);
        ui->batteryTabButton->setStyleSheet(defaultTabButtonStyle);
        ui->processVarsButton->setStyleSheet(defaultTabButtonStyle);
        ui->errorsTabButton->setStyleSheet(highlightedTabButtonStyle);

        engineWidget->hide();
        errorsPanel->show();
        batteryPanel->hide();
        processVarsWidget->hide();
        break;
    default:
        break;
    }
}

void AdminPanel::on_engineTabButton_clicked()
{
    this->onTabChange(TABS::ENGINE);
}


void AdminPanel::on_batteryTabButton_clicked()
{
this->onTabChange(TABS::BATTERY);
}

void AdminPanel::on_processVarsButton_clicked()
{
    this->onTabChange(TABS::PROCESS_VARS);
}

void AdminPanel::on_errorsTabButton_clicked()
{
    this->onTabChange(TABS::ERRORS);
}


void AdminPanel::on_closeButton_clicked()
{
    this->hide();
}




