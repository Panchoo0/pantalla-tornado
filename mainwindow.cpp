#include "mainwindow.h"
#include "ui_adminpanel.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QProcess>
#include <utils.h>
#include <bits/stdc++.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setGeometry(0,0, 800, 480);

    // Inicializamos el timer que actualiza la hora
    datetimeTimer = new QTimer(this);
    connect(datetimeTimer, SIGNAL(timeout()), this, SLOT(updateDateTime()));
    datetimeTimer->start(100);

    // Inicializamos los datos que provendran del bus CAN
    data = new CANData();
    // sender = new SendCANData();

    // Configuración para poner el botón de configuración por sobre su ícono
    ui->confIcon->stackUnder(ui->confButton);

    // Configuración para la aguja
    QGraphicsScene *needleScene = new QGraphicsScene(0, 0,200, 200);
    QPixmap needleImage(":/images/pantallaPrincipal/aguja.png");
    QGraphicsPixmapItem* needleItem = needleScene->addPixmap(needleImage);
    needleItem->setPos(80, -12);
    ui->needleContainer->rotate(-135);
    ui->needleContainer->setScene(needleScene);

    // Cargamos las imágenes de los iconos de temperatura y batería
    this->lowTempIcon = QPixmap(":/images/pantallaPrincipal/temp_icono_baja.png");
    this->regularTempIcon = QPixmap(":/images/pantallaPrincipal/temp_icono_media.png");
    this->highTempIcon = QPixmap(":/images/pantallaPrincipal/temp_icono_alta.png");

    this->lowBatIcon = QPixmap(":/images/pantallaPrincipal/bat_relleno_bajo.png");
    this->regularBatIcon = QPixmap(":/images/pantallaPrincipal/bat_relleno_medio.png");
    this->highBatIcon = QPixmap(":/images/pantallaPrincipal/bat_relleno_alto.png");

    // Creamos el widget para el panel de administración
    adminPanel = new AdminPanel(data, this);
    adminPanel->setGeometry(0, 0, 800, 440);
    isAdminPanelOpen = false;

    // dummy data
    this->data->addError(2);

    // Creamos el widget para las alertas
    notificationsWidget = new NotificationsWidget(this->data,this);
    notificationsWidget->setGeometry(398, 18, 384, 94);

    // Iniciamos la conexión con el bus CAN
    this->startReceivingCAN();

    // Conectamos el thread secundario para recibir las señales
    connect(this->receiver, &ReceiveCANData::messageReceived, this, &MainWindow::receiveMessage);
    connect(this->receiver, &ReceiveCANData::debugMessage, this, &MainWindow::receiveDebugMessage);

    // Conectamos las señales de cada tipo de mensaje con sus correspondientes widgets interesados.

    // Message1
    connect(this->data, &CANData::message1, this->adminPanel->batteryPanel, &BatteryPanel::message1);
    connect(this->data, &CANData::message1, this, &MainWindow::message1);

    // Message2
    connect(this->data, &CANData::message2, this->adminPanel->engineWidget, &EngineWidget::message2);

    // Message3
    connect(this->data, &CANData::message3, this, &MainWindow::message3);
    connect(this->data, &CANData::message3, this->adminPanel->batteryPanel, &BatteryPanel::message3);
    connect(this->data, &CANData::message3, this->adminPanel->engineWidget, &EngineWidget::message3);

    // Message4
    connect(this->data, &CANData::message4, this->adminPanel->engineWidget, &EngineWidget::message4);

    // Message5
    connect(this->data, &CANData::message5, this->adminPanel->engineWidget, &EngineWidget::message5);

    // Message6
    connect(this->data, &CANData::message6, this->adminPanel->engineWidget, &EngineWidget::message6);

    // Message7
    connect(this->data, &CANData::message7, this->adminPanel->processVarsWidget, &ProcessVarsWidget::message7);
    connect(this->data, &CANData::message7, this->adminPanel->batteryPanel, &BatteryPanel::message7);

    // Bess1
    connect(this->data, &CANData::bess1, this->adminPanel->batteryPanel, &BatteryPanel::bess1);

    // Bess2
    connect(this->data, &CANData::bess2, this->adminPanel->batteryPanel, &BatteryPanel::bess2);

    // Bess3
    connect(this->data, &CANData::bess3, this->adminPanel->batteryPanel, &BatteryPanel::bess3);

    // Bess4
    connect(this->data, &CANData::bess4, this->adminPanel->batteryPanel, &BatteryPanel::bess4);

    // Bess5
    connect(this->data, &CANData::bess5, this->adminPanel->engineWidget, &EngineWidget::bess5);
    connect(this->data, &CANData::bess5, this->adminPanel->processVarsWidget, &ProcessVarsWidget::bess5);

    // Emix
    connect(this->data, &CANData::emix1, this->adminPanel->processVarsWidget, &ProcessVarsWidget::emix1);

    // Faults1
    connect(this->data, &CANData::faults1, this->adminPanel->processVarsWidget, &ProcessVarsWidget::faults1);

    // Faults2
    connect(this->data, &CANData::faults2, this->adminPanel->processVarsWidget, &ProcessVarsWidget::faults2);

    this->testCan();

    // Hacer scrolleable el área de variables de proceso
    // test -> clone y equal para candata
    // Ver posicionamiento de pantalla secundaria
}

void MainWindow::message1() {
    this->updateBat();
}

void MainWindow::message3() {
    this->updateBatTemp();
    this->updateEngineTemp();
    this->updateInversorTemp();
}

void MainWindow::receiveDebugMessage(QString msg) {
    // ui->debug_msg->setText(msg);
    qInfo() << msg;
}

// Función que actualiza el tiempo en el tablero
void MainWindow::updateDateTime() {
    QString text = QTime::currentTime().toString("HH:mm");
    ui->time->setText(text);

    QDate date = QDate::currentDate();
    QLocale locale(QLocale::Spanish, QLocale::Chile);
    QString formattedDate = locale.dayName(date.dayOfWeek()) + " " +
                            QString::number(date.day()) + " de " +
                            locale.monthName(date.month());
    ui->date->setText(formattedDate);
}

// Función que actualiza la velocidad, tanto el número como la rotación de la aguja.
void MainWindow::updateSpeed()
{
    // ui->needleContainer->rotate(270 * (value - this->data->speed) / 120.0f);
    // ui->speedValue->setText(QString::number(value));

    // this->data->speed = value;
}

// Función que actualiza la temperatura del motor
void MainWindow::updateEngineTemp() {
    // Actualizamos el ícono según el valor
    if (this->data->engineTemp < 30) {
        ui->engineTempIcon->setPixmap(this->lowTempIcon);
    } else if (this->data->engineTemp < 50) {
        ui->engineTempIcon->setPixmap(this->regularTempIcon);
    } else {
        ui->engineTempIcon->setPixmap(this->highTempIcon);
    }

    // Actualizamos el texto
    ui->engineTempValue->setText(QString::number(this->data->engineTemp) + "° C");
}

// Función que actualiza la temperatura del inversor
void MainWindow::updateInversorTemp() {

    // Actualizamos el ícono según el valor
    if (this->data->inversorTemp < 30) {
        ui->inversorTempIcon->setPixmap(this->lowTempIcon);
    } else if (this->data->inversorTemp < 50) {
        ui->inversorTempIcon->setPixmap(this->regularTempIcon);
    } else {
        ui->inversorTempIcon->setPixmap(this->highTempIcon);
    }

    // Actualizamos el texto
    ui->inversorValue->setText(QString::number(this->data->inversorTemp) + "° C");
}

// Función que actualiza la temperatura de la batería
void MainWindow::updateBatTemp() {

    // Actualizamos el ícono según el valor
    if (this->data->batTemp < 30) {
        ui->batTempIcon->setPixmap(this->lowTempIcon);
    } else if (this->data->batTemp < 50) {
        ui->batTempIcon->setPixmap(this->regularTempIcon);
    } else {
        ui->batTempIcon->setPixmap(this->highTempIcon);
    }

    // Actualizamos el texto
    ui->batTempValue->setText(QString::number(this->data->batTemp) + "° C");
}

// Función que actualiza la carga de la batería.
// Recibe la nueva carga de la batería en un entero que representa el porcentaje
void MainWindow::updateBat() {

    // Para crear la animación de la batería se corta la parte superior de la imágen
    int iconHeight = this->highBatIcon.height();
    int croppedY = 100 - this->data->SOC; // Porciento de cuanto se cortará la imágen
    int cropY = (iconHeight * croppedY) / 100; // Cuantos pixeles en el eje Y serán cortados
    int croppedHeight = iconHeight - cropY; // Nueva altura de la imagen

    QPixmap croppedPixmap;
    // Se elige la imágen según la carga restante
    if (this->data->SOC < 30)  {
        croppedPixmap = this->highBatIcon.copy(0, cropY, this->highBatIcon.width(), croppedHeight);
    } else if (this->data->SOC < 50) {
        croppedPixmap = this->regularBatIcon.copy(0, cropY, this->highBatIcon.width(), croppedHeight);
    } else {
        croppedPixmap = this->lowBatIcon.copy(0, cropY, this->highBatIcon.width(), croppedHeight);
    }

    // Se deja el espacio arriba correspondiente a la altura que fue recortada
    QString style = QString::fromStdString("margin-top: " + std::to_string(iconHeight - croppedHeight) + "px;");

    ui->batFill->setPixmap(croppedPixmap);
    ui->batFill->setStyleSheet(style);

    ui->batValue->setText(QString::number(this->data->SOC));
}

// Función que recibe un mensaje CAN y actualiza sus valores
// Se podría eliminar esta indirección conectando directamente la señal del thread secundario con el objeto CANData
void MainWindow::receiveMessage(unsigned char sourceAddress, unsigned int pgn, uint8_t* receivedData)
{
    // Transformamos a hexadecimal el pgn para debugear
    std::stringstream ss;
    ss << std::hex << pgn;
    std::string pgn_hex = ss.str();

    this->receiveDebugMessage(
        "Recibido desde " +
        QString::number(sourceAddress) +
        " con pgn: " + QString::fromStdString(pgn_hex) +
        " bytes: " +
        Utils::toHexString((uchar *)receivedData, 8)
    );

    this->data->receiveMessage(sourceAddress, pgn, receivedData);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->updateSpeed();
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    this->updateInversorTemp();
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    this->updateEngineTemp();
}


void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    this->updateBatTemp();
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    this->updateBat();
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
}

// Handler del click del botón de configuración
void MainWindow::on_confButton_clicked()
{
    if (isAdminPanelOpen) {
        adminPanel->hide();
    }
    else {
        adminPanel->show();
    }
    isAdminPanelOpen = !isAdminPanelOpen;
}

// Función que configura el bus CAN de la pantalla e inicia la conexión del socket con este
void MainWindow::startReceivingCAN() {
    this->activateCANChannel();
    this->receiver = new ReceiveCANData();
    this->receiver->start();
}

//Function to activate CAN channel of DI5 on which the data will be sent/received
// COPIADA DEL EJEMPLO
void MainWindow::activateCANChannel()
{
    QProcess *myProcess = new QProcess(this);
    QStringList arguments;

    //Set CAN channel,bitrate and txqueulen
    //txqueulen means Transmit Queue Length - This is the internal message buffer size for CAN port
    //More information on this can be found in C_CPP_Developerguide_BR.pdf
    QString canChannel = "can0";
    QString bitrate = "250000";
    QString txqueulen = "1000";

    myProcess->setWorkingDirectory("/opt");

    //First stop CAN port
    arguments.clear();
    arguments << canChannel << "down";
    myProcess->start("ifconfig", arguments);
    myProcess->waitForFinished();

    //Set bitrate
    arguments.clear();
    arguments << "link" << "set" << canChannel << "type" << "can" << "bitrate" << bitrate;
    myProcess->start("ip", arguments);
    myProcess->waitForFinished();

    //Set Transmit Queue Length
    arguments.clear();
    arguments << canChannel << "txqueuelen" << txqueulen;
    myProcess->start("ifconfig", arguments);
    myProcess->waitForFinished();

    //Start CAN port
    arguments.clear();
    arguments << canChannel << "up";
    myProcess->start("ifconfig", arguments);
    myProcess->waitForFinished();

    //Output the CAN channel status on console
    arguments.clear();
    arguments << canChannel;
    myProcess->start("ifconfig", arguments);
    myProcess->waitForFinished();

    //Read the console to check if CAN channel is activated
    QString output = myProcess->readAllStandardOutput();
    if (output.contains(canChannel) && !(output.contains("UP RUNNING")))
    {
        this->receiveDebugMessage("Error al activar bus CAN");
    }

    this->receiveDebugMessage("CAN Activado");
}

void MainWindow::sendMessage() {
}

// Test para comprobar si se actualizan correctamente los valores
void MainWindow::testCan() {
    this->testMessage1(1011, 120, 24);
    this->testMessage2(12, 11, 12, 1, 0);
    this->testMessage3(3, 12,10, 255, 12);
    this->testMessage4(12,123, 1221, 187);
    this->testMessage5(120, 1232, 83, 8912);
    this->testMessage6(103, 1458, 93, 2);

    this->testBess1(0, 10, 102, 29);
    this->testBess2(11, 12, 129, 192, 32, 12, 84);
    this->testBess3(12, 1029, 12);
    this->testBess4(12, 92, 1, 83, 44);
    this->testBess5(12, 123, 1, 1, 1, 1, 1, 1);

    uchar data[] = {0xff, 0b11111111, 0b10111111, 0b11111111, 0b11111111, 0b11111111, 0b01000000, 0b00000000};
    this->receiveMessage(0, 0x700, data);

    uchar data2[] = {3, 4, 5, 6, 7, 8, 0 ,0};
    this->emix1(12, 15, 19, 21, 34, 56);

    this->faults1(12, 12456);
    this->faults2(12431, 120);

}

void MainWindow::assertMessage1(int _current, int _voltage, int soc) {
    assert(ui->batValue->text() == QString::number(soc));
}

void MainWindow::testMessage1(int current, int voltage, int soc) {
    uchar b1_current = current >> 8;
    uchar b2_current = current & 0xff;

    uchar b1_voltage = voltage >> 8;
    uchar b2_voltage = voltage & 0xff;


    uchar b1_soc = soc & 0xff;

    uchar data[] = {b1_current, b2_current, b1_voltage, b2_voltage, b1_soc, 0, 0, 0};
    this->receiveMessage(0, 0x100, data);

    this->data->assertMessage1(current, voltage, soc);
    this->assertMessage1(current, voltage, soc);
    this->adminPanel->batteryPanel->assertMessage1(current, voltage, soc);
}

void MainWindow::testMessage2(int engineCurrent, int engineTorque, int engineVoltage, int rpm, int setpoint) {
    uchar b1_current = engineCurrent >> 4;
    uchar b2_current = (engineCurrent & 0xf) << 4;

    uchar b1_torque = engineTorque >> 8;
    uchar b2_torque  = engineTorque & 0xf;

    uchar b1_voltage = engineVoltage >> 4;
    uchar b2_voltage = (engineVoltage & 0xf) << 4;

    uchar b1_rpm= rpm >> 8;
    uchar b2_rpm = rpm & 0xf;

    uchar b1_setpoint = setpoint >> 8;
    uchar b2_setpoint = setpoint & 0xff;


    uchar b2 = b2_current | b1_torque;
    uchar b5 = b2_voltage | b1_rpm;

    uchar data[] = {b1_current, b2, b2_torque, b1_voltage, b5, b2_rpm, b1_setpoint, b2_setpoint};
    this->receiveMessage(0, 0x200, data);

    this->data->assertMessage2(engineCurrent, engineTorque, engineVoltage, rpm, setpoint);
    this->adminPanel->engineWidget->assertMessage2(engineCurrent, engineTorque, engineVoltage, rpm, setpoint);

}

void MainWindow::assertMessage3(int engineTemp, int inversorTemp, int batTemp, int batMaxTemp, int batMinTemp){
    assert(
        ui->engineTempValue->text() == (QString::number(engineTemp) + "° C")
        );

    assert(
        ui->inversorValue->text() == (QString::number(inversorTemp) + "° C")
    );

    assert(
        ui->batTempValue->text() == (QString::number(batTemp) + "° C")
        );
}

void MainWindow::testMessage3(int engineTemp, int inversorTemp, int batTemp, int batMaxTemp, int batMinTemp) {
    uchar b_engineTemp = engineTemp & 0xff;
    uchar b_inversorTemp = inversorTemp & 0xff;
    uchar b_batTemp = batTemp & 0xff;
    uchar b_batMaxTemp = batMaxTemp & 0xff;
    uchar b_batMinTemp = batMinTemp & 0xff;

    uchar data[] = {b_engineTemp, b_inversorTemp, b_batTemp, b_batMaxTemp, b_batMinTemp};
    this->receiveMessage(0, 0x300, data);

    this->data->assertMessage3(engineTemp, inversorTemp, batTemp, batMaxTemp, batMinTemp);
    this->assertMessage3(engineTemp, inversorTemp, batTemp, batMaxTemp, batMinTemp);
    this->adminPanel->batteryPanel->assertMessage3(engineTemp, inversorTemp, batTemp, batMaxTemp, batMinTemp);
    this->adminPanel->engineWidget->assertMessage3(engineTemp, inversorTemp, batTemp, batMaxTemp, batMinTemp);
}

void MainWindow::testMessage4(int dcdc1Current, int dcdc2Current, int dcdc1HVCurrent, int dcdc2HVCurrent) {
    uchar b1 = dcdc1Current >> 8;
    uchar b2 = dcdc1Current &0xff;

    uchar b3 = dcdc2Current >> 8;
    uchar b4 = dcdc2Current &0xff;

    uchar b5 = dcdc1HVCurrent >> 8;
    uchar b6 = dcdc1HVCurrent &0xff;

    uchar b7 = dcdc2HVCurrent >> 8;
    uchar b8 = dcdc2HVCurrent &0xff;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7, b8};
    this->receiveMessage(0, 0x400, data);

    this->data->assertMessage4(dcdc1Current, dcdc2Current, dcdc1HVCurrent, dcdc2HVCurrent);
    this->adminPanel->engineWidget->assertMessage4(dcdc1Current, dcdc2Current, dcdc1HVCurrent, dcdc2HVCurrent);
}

void MainWindow::testMessage5(int dcdc1OutputVoltage, int dcdc2OutputVoltage, int dcdc1InputVoltage, int dcdc2InputVoltage) {
    uchar b1 = dcdc1OutputVoltage >> 8;
    uchar b2 = dcdc1OutputVoltage &0xff;

    uchar b3 = dcdc2OutputVoltage >> 8;
    uchar b4 = dcdc2OutputVoltage &0xff;

    uchar b5 = dcdc1InputVoltage >> 8;
    uchar b6 = dcdc1InputVoltage &0xff;

    uchar b7 = dcdc2InputVoltage >> 8;
    uchar b8 = dcdc2InputVoltage &0xff;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7, b8};
    this->receiveMessage(0, 0x500, data);

    this->data->assertMessage5(dcdc1OutputVoltage, dcdc2OutputVoltage, dcdc1InputVoltage, dcdc2InputVoltage);
    this->adminPanel->engineWidget->assertMessage5(dcdc1OutputVoltage, dcdc2OutputVoltage, dcdc1InputVoltage, dcdc2InputVoltage);
}

void MainWindow::testMessage6(int posResistanceSIM100, int negResistanceSIM100, int posResistanceBMU, int negResistanceBMU) {
    uchar b1 = posResistanceSIM100 >> 8;
    uchar b2 = posResistanceSIM100 &0xff;

    uchar b3 = negResistanceSIM100 >> 8;
    uchar b4 = negResistanceSIM100 &0xff;

    uchar b5 = posResistanceBMU >> 8;
    uchar b6 = posResistanceBMU &0xff;

    uchar b7 = negResistanceBMU >> 8;
    uchar b8 = negResistanceBMU &0xff;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7, b8};
    this->receiveMessage(0, 0x600, data);

    this->data->assertMessage6(posResistanceSIM100, negResistanceSIM100, posResistanceBMU, negResistanceBMU);
    this->adminPanel->engineWidget->assertMessage6(posResistanceSIM100, negResistanceSIM100, posResistanceBMU, negResistanceBMU);
}

void MainWindow::testBess1(int trama, int v1, int v2, int v3) {
    uchar b1 = trama >> 8;
    uchar b2 = trama & 0xFF;

    uchar b3 = v1 >> 8;
    uchar b4 = v1 & 0xFF;

    uchar b5 = v2 >> 8;
    uchar b6 = v2 & 0xFF;

    uchar b7 = v3 >> 8;
    uchar b8 = v3 & 0xFF;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7, b8};
    this->receiveMessage(0, 0xC100, data);

    this->data->assertBess1(trama, v1, v2, v3);
    this->adminPanel->batteryPanel->assertBess1(trama, v1, v2, v3);
}


void MainWindow::testBess2(int trama, int t1, int t2, int t3, int t4, int t5, int t6){
    uchar b1 = trama >> 8;
    uchar b2 = trama & 0xff;

    uchar b3 = t1 & 0xff;
    uchar b4 = t2 & 0xff;

    uchar b5 = t3 & 0xff;
    uchar b6 = t4 & 0xff;

    uchar b7 = t5 & 0xff;
    uchar b8 = t6 & 0xff;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7, b8};
    this->receiveMessage(0, 0xC200, data);

    this->data->assertBess2(trama, t1, t2, t3, t4, t5, t6);
    this->adminPanel->batteryPanel->assertBess2(trama, t1, t2, t3, t4, t5, t6);
}


void MainWindow::testBess3(int chargeEnergyAcumulated, int dischargeEnergyAcumulated, int energyOneCharge) {
    uchar b1 = chargeEnergyAcumulated >> 16;
    uchar b2 = (chargeEnergyAcumulated >> 8) & 0xFF;
    uchar b3 = chargeEnergyAcumulated & 0xFF;

    uchar b4 = dischargeEnergyAcumulated >> 16;
    uchar b5 = (dischargeEnergyAcumulated >> 8) & 0xFF;
    uchar b6 = dischargeEnergyAcumulated & 0xFF;

    uchar b7 = energyOneCharge >> 8;
    uchar b8 = energyOneCharge & 0xFF;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7,b8};
    this->receiveMessage(0, 0xC300, data);

    this->data->assertBess3(chargeEnergyAcumulated, dischargeEnergyAcumulated, energyOneCharge);
    this->adminPanel->batteryPanel->assertBess3(chargeEnergyAcumulated, dischargeEnergyAcumulated, energyOneCharge);
}

void MainWindow::testBess4(int SOC, int SOH, int minVoltage, int maxVoltage, int meanVoltage) {
    uchar b1 = SOC & 0xFF;
    uchar b2 = SOH & 0xFF;

    uchar b3 = maxVoltage >> 8;
    uchar b4 = maxVoltage & 0xFF;

    uchar b5 = minVoltage >> 8;
    uchar b6 = minVoltage & 0xFF;

    uchar b7 = meanVoltage >> 8;
    uchar b8 = meanVoltage & 0xFF;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7,b8};
    this->receiveMessage(0, 0xC400, data);

    this->data->assertBess4(SOC, SOH, minVoltage, maxVoltage, meanVoltage);
    this->adminPanel->batteryPanel->assertBess4(SOC, SOH, minVoltage, maxVoltage, meanVoltage);
}

void MainWindow::testBess5(int posChargeTempDC, int negChargeTempDC, int dcConected, int bmsChargingMode, int coolingState, int heatState, int bmuContactor, int bmsFailures) {
    uchar b1 = posChargeTempDC & 0xFF;
    uchar b2 = negChargeTempDC & 0xFF;

    uchar b3_0_2 = (dcConected & 0b11) << 6;
    uchar b3_2_4 = (bmsChargingMode & 0b11) << 4;
    uchar b3_4_5 = (coolingState & 0b1) << 3;
    uchar b3_5_6 = (heatState & 0b1) << 2;
    uchar b3_6_8 = (bmuContactor & 0b11);

    uchar b3 = b3_0_2 | b3_2_4 | b3_4_5 | b3_5_6 | b3_6_8;

    uchar b4 = bmsFailures & 0xFF;

    uchar data[] = {b1, b2, b3, b4, 0, 0, 0, 0};
    this->receiveMessage(0, 0xC500, data);

    this->data->assertBess5(posChargeTempDC, negChargeTempDC, dcConected, bmsChargingMode, coolingState, heatState, bmuContactor, bmsFailures);
    this->adminPanel->engineWidget->assertBess5(posChargeTempDC, negChargeTempDC, dcConected, bmsChargingMode, coolingState, heatState, bmuContactor, bmsFailures);

}

void MainWindow::emix1(int edsFailures, int dcdc1Failures, int dcdc2Failures, int sim100Failures, int obcFailures, int emixFailures) {
    uchar b1 = edsFailures & 0xFF;
    uchar b2 = dcdc1Failures & 0xFF;
    uchar b3 = dcdc2Failures & 0xFF;
    uchar b4 = sim100Failures & 0xFF;
    uchar b5 = obcFailures & 0xFF;
    uchar b6 = emixFailures & 0xFF;

    uchar data[] = {b1, b2, b3, b4, b5, b6, 0, 0};
    this->receiveMessage(0, 0xC600, data);
}

void MainWindow::faults1(int dcdc1ErrorCode, int dcdc2ErrorCode) {
    uchar b1 = dcdc1ErrorCode >> 8;
    uchar b2 = dcdc2ErrorCode & 0xFF;

    uchar b3 = dcdc2ErrorCode >> 8;
    uchar b4 = dcdc2ErrorCode & 0xFF;

    uchar data[] = {b1, b2, b3, b4, 0, 0, 0, 0};
    this->receiveMessage(0, 0xD000, data);
}


void MainWindow::faults2(int edsErrorCode, int obcErrorCode) {
    uchar b1 = edsErrorCode >> 8;
    uchar b2 = edsErrorCode & 0xFF;

    uchar b3 = obcErrorCode >> 8;
    uchar b4 = obcErrorCode & 0xFF;

    uchar data[] = {b1, b2, b3, b4, 0, 0, 0, 0};
    this->receiveMessage(0, 0xD100, data);
}
