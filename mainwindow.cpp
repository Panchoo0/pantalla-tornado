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

    this->startDate = QDateTime();
    // Inicializamos el timer que actualiza la hora
    datetimeTimer = new QTimer(this);
    connect(datetimeTimer, SIGNAL(timeout()), this, SLOT(updateDateTime()));
    datetimeTimer->start(100);

    calcConsumptionTimer = new QTimer(this);
    connect(calcConsumptionTimer, SIGNAL(timeout()), this, SLOT(calcConsumption()));
    calcConsumptionTimer->start(CONSUMPTION_TIME_GAP);

    // Objeto con la información proveniente del bus CAN
    data = new CANData();

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

    // Creamos el widget para las alertas
    notificationsWidget = new NotificationsWidget(this->data,this);
    notificationsWidget->setGeometry(398, 18, 384, 94);

    // Iniciamos la conexión con el bus CAN
    this->startReceivingCAN();

    // Iniciamos el thread que mantiene la comunicación por UDS
    sender = new UDSCanData();
    sender->start();

    // Conectamos el thread secundario para recibir las señales
    connect(this->receiver, &ReceiveCANData::messageReceived, this, &MainWindow::receiveMessage);
    connect(this->receiver, &ReceiveCANData::debugMessage, this, &MainWindow::receiveDebugMessage);
    connect(this->data, &CANData::dbgMessage, this, &MainWindow::receiveDebugMessage);

    // Mensajes por uds
    connect(this->sender, &UDSCanData::dbgMessage, this, &MainWindow::receiveDebugMessage);
    connect(this->sender, &UDSCanData::udsMessage, this->data, &CANData::receiveUDSMessage);

    // Señal en caso de recibir un error por el protocolo UDS
    connect(this->data, &CANData::canError, this->adminPanel->errorsPanel, &ErrorsPanel::canError);

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
    connect(this->data, &CANData::message7, this, &MainWindow::message7);

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

    // this->testCan();
    // this->testCanErrors();

    testigos = new TestigoController(ui->testigosWidget);

    connect(this->data, &CANData::canTestigo, this->testigos, &TestigoController::addTestigo);
    connect(this->data, &CANData::updateMainWindow, this, &MainWindow::updateMainWindow);
}

// SLOT que actualiza algunos de los valores de la pantalla principal
void MainWindow::updateMainWindow() {
    QString text;

    if (data->MarchState == 1) {
        text = "D";
    } else if (data->MarchState == 2) {
        text = "N";
    } else {
        text = "R";
    }
    ui->marcha->setText(text);

    // max entre dcvoltage y hvvoltagedcdc 1 y 2
    // float voltageHV = std::max(data->eds.instVoltage, data->HVVoltageDCDC1, data->HVVoltageDCDC2);
    float voltageHV = std::max(data->eds.instVoltage, data->HVVoltageDCDC1);
    voltageHV = std::max(voltageHV, data->HVVoltageDCDC2);
    ui->voltageHVValue->setText(QString::number(voltageHV) + " V");

    float maxVoltageLV = std::max(data->LVVoltageDCDC1, data->LVVoltageDCDC2);
    ui->voltageLVValue->setText(QString::number(maxVoltageLV) + " V");

    ui->currentHVValue->setText(QString::number(data->PackcurrentBESS) + " A");

    float maxCurrentLV = std::max(data->dcdc1.lvCurr, data->dcdc2.lvCurr);
    ui->currentLVValue->setText(QString::number(maxCurrentLV) + " A");

    // AÚN NO PROBADOS vvv

    // Faltan factores de calculo para estos datos
    int S = data->eds.instCurr * data->eds.instVoltage;
    this->updateSpeed(S);

    // Autonomía
    float E_total = 140.95;
    float kw_15 = consumptionTotal / consumption.size();
    if (kw_15 == 0) return;
    float E_actual = 0;
    float autonomy = (E_actual - E_total * 0.1) / kw_15;

    int hours = autonomy;
    int minutes = (autonomy - (long) autonomy) * 60;

    ui->autonomyVal->setText(QString::number(hours) + ":" + QString::number(minutes));
}

// Calcula el consumo cada CONSUMPTION_TIME_GAP ms, guardando las mediciones de los últimos
// minutos establecidos en CONSUMPTION_TIME_MEASURE ms (15 minutos), para obtener el promedio
// de consumo durante este periodo
void MainWindow::calcConsumption() {
    float instConsumption = data->bess.inst_current * data->bess.inst_voltage;
    consumptionTotal += instConsumption;
    if (consumption.size() >= CONSUMPTION_TIME_MEASURE / CONSUMPTION_TIME_GAP) {
        consumptionTotal -= consumption.front();
        consumption.pop();
    }
    consumption.push(instConsumption);
}

void MainWindow::message7() {
    // Si el estado es MOTOR_ON se comienza la medición para el trip
    if (this->startDate.isValid() || data->processVars.EMIX_state != 2) return;
    this->startDate = QDateTime::currentDateTime();
}

// Función para testear el recibimiento de errores DTC por el protocolo UDS
void MainWindow::testCanErrors() {
    uint8_t data[] = {0x05, 0x62, 0xA0, 0xF0, 0x1};
    uint8_t data2[] = {0x05, 0x62, 0xA0, 0xF0, 0x2};
    uint8_t data3[] = {0x05, 0x62, 0xA0, 0xF4, 0x12};
    this->data->receiveUDSMessage(data);
    this->data->receiveUDSMessage(data2);
    this->data->receiveUDSMessage(data3);
}

// Función que recibe la señal por un nuevo mensaje message1
void MainWindow::message1() {
    this->updateBat();
}

// Función que recibe la señal por un nuevo mensaje message3
void MainWindow::message3() {
    this->updateBatTemp();
    this->updateEngineTemp();
    this->updateInversorTemp();
}

// Función de debug
void MainWindow::receiveDebugMessage(QString msg) {
    // ui->debug_msg->setText(ui->debug_msg->text() + "\n" + msg);
    qInfo() << msg;
}

// Función que actualiza el tiempo en el tablero
// y el trip
void MainWindow::updateDateTime() {
    QString text = QTime::currentTime().toString("HH:mm");
    ui->time->setText(text);

    QDate date = QDate::currentDate();
    QLocale locale(QLocale::Spanish, QLocale::Chile);
    QString formattedDate = locale.dayName(date.dayOfWeek()) + " " +
                            QString::number(date.day()) + " de " +
                            locale.monthName(date.month());
    ui->date->setText(formattedDate);

    // Se actualiza el trip
    if (!this->startDate.isValid()) return;
    const qint64 deltaMs = this->startDate.msecsTo(QDateTime::currentDateTime());
    std::tuple<int, int, int> time = Utils::fromMsToHoursMinutesSeconds(deltaMs);

    ui->tripVal->setText(QString::number(std::get<0>(time)) + ":" + QString::number(std::get<1>(time)));
}

// Función que actualiza la ui de la velocidad, tanto el número como la rotación de la aguja.
void MainWindow::updateSpeed(int value)
{
    ui->needleContainer->rotate(270 * (value - this->speed) / 120.0f);
    ui->speedValue->setText(QString::number(value));

    this->speed = value;
}

// Función que actualiza la ui de la temperatura del motor
void MainWindow::updateEngineTemp() {
    // Actualizamos el ícono según el valor
    if (this->data->eds.motorTemp < 30) {
        ui->engineTempIcon->setPixmap(this->lowTempIcon);
    } else if (this->data->eds.motorTemp < 50) {
        ui->engineTempIcon->setPixmap(this->regularTempIcon);
    } else {
        ui->engineTempIcon->setPixmap(this->highTempIcon);
    }

    // Actualizamos el texto
    ui->engineTempValue->setText(QString::number(this->data->eds.motorTemp) + "° C");
}

// Función que actualiza la ui de la temperatura del inversor
void MainWindow::updateInversorTemp() {

    // Actualizamos el ícono según el valor
    if (this->data->eds.invTemp < 30) {
        ui->inversorTempIcon->setPixmap(this->lowTempIcon);
    } else if (this->data->eds.invTemp  < 50) {
        ui->inversorTempIcon->setPixmap(this->regularTempIcon);
    } else {
        ui->inversorTempIcon->setPixmap(this->highTempIcon);
    }

    // Actualizamos el texto
    ui->inversorValue->setText(QString::number(this->data->eds.invTemp) + "° C");
}

// Función que actualiza la ui de la temperatura de la batería
void MainWindow::updateBatTemp() {

    // Actualizamos el ícono según el valor
    if (this->data->bess.avgTemp < 30) {
        ui->batTempIcon->setPixmap(this->lowTempIcon);
    } else if (this->data->bess.avgTemp < 50) {
        ui->batTempIcon->setPixmap(this->regularTempIcon);
    } else {
        ui->batTempIcon->setPixmap(this->highTempIcon);
    }

    // Actualizamos el texto
    ui->batTempValue->setText(QString::number(this->data->bess.avgTemp) + "° C");
}

// Función que actualiza la ui de la carga de la batería.
// Recibe la nueva carga de la batería en un entero que representa el porcentaje
void MainWindow::updateBat() {

    // Para crear la animación de la batería se corta la parte superior de la imágen
    int iconHeight = this->highBatIcon.height();
    int croppedY = 100 - this->data->bess.SoC; // Porciento de cuanto se cortará la imágen
    int cropY = (iconHeight * croppedY) / 100; // Cuantos pixeles en el eje Y serán cortados
    int croppedHeight = iconHeight - cropY; // Nueva altura de la imagen

    QPixmap croppedPixmap;
    // Se elige la imágen según la carga restante
    if (this->data->bess.SoC < 30)  {
        croppedPixmap = this->highBatIcon.copy(0, cropY, this->highBatIcon.width(), croppedHeight);
    } else if (this->data->bess.SoC < 50) {
        croppedPixmap = this->regularBatIcon.copy(0, cropY, this->highBatIcon.width(), croppedHeight);
    } else {
        croppedPixmap = this->lowBatIcon.copy(0, cropY, this->highBatIcon.width(), croppedHeight);
    }

    // Se deja el espacio arriba correspondiente a la altura que fue recortada
    QString style = QString::fromStdString("margin-top: " + std::to_string(iconHeight - croppedHeight) + "px;");

    ui->batFill->setPixmap(croppedPixmap);
    ui->batFill->setStyleSheet(style);

    ui->batValue->setText(QString::number(this->data->bess.SoC));
}

// Función que recibe un mensaje CAN y actualiza sus valores
// Se podría eliminar esta indirección conectando directamente la señal del thread secundario con el objeto CANData
// Se mantiene solo para facilitar el debug
void MainWindow::receiveMessage(unsigned char sourceAddress, unsigned int pgn, uint8_t* receivedData)
{
    this->data->receiveMessage(sourceAddress, pgn, receivedData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}

// Handler del click del botón de panel de información avanzada
void MainWindow::on_confButton_clicked()
{
    if (adminPanel->isVisible()) {
        adminPanel->hide();
    }
    else {
        adminPanel->show();
    }
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
    QString bitrate = "500000";
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

// Test para comprobar si se actualizan correctamente los valores al recibir un mensaje CAN
void MainWindow::testCan() {
    srand (time(NULL));
    int iteraciones = 10;
    for (int i = 0; i < iteraciones; i++) {
        this->testMessage1();
        this->testMessage2();
        this->testMessage3();
        this->testMessage4();
        this->testMessage5();
        this->testMessage6();
        this->testMessage7();

        this->testBess1();
        this->testBess2();
        this->testBess3();
        this->testBess4();
        this->testBess5();

        this->testEmix1();
        this->testFaults1();
        this->testFaults2();
    }

}

// Comprueba si se actualizó el panel tras recibir un message1
void MainWindow::assertMessage1() {
    assert(ui->batValue->text() == QString::number(this->data->bess.SoC));
}


void MainWindow::testMessage1() {
    // Obtenemos valores random
    int current = rand() % 0xFFFF;
    int voltage = rand() % 0xFFFF;
    int soc = rand() % 100;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->bess.inst_current = Utils::round(current, 0.1, -1000);
    canData->bess.inst_voltage = Utils::round(voltage, 0.1);
    canData->bess.SoC = Utils::round(soc, 0.4);

    // Transformamos los valores según el protocolo de message1
    uchar b1_current = current >> 8;
    uchar b2_current = current & 0xff;

    uchar b1_voltage = voltage >> 8;
    uchar b2_voltage = voltage & 0xff;

    uchar b1_soc = soc & 0xff;

    uchar data[] = {b1_current, b2_current, b1_voltage, b2_voltage, b1_soc, 0, 0, 0};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0x100, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    // Comprobamos que se actualizó la información en los widgets
    this->assertMessage1();
}

void MainWindow::testMessage2() {
    // Obtenemos valores random
    int engineCurrent = rand() % 0xFFF;
    int engineTorque = rand() % 0xFFF;
    int engineVoltage = rand() % 0xFFF;
    int rpm = rand() % 0xFFF;
    int setpoint = rand() % 0xFFFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->eds.instCurr = engineCurrent;
    canData->eds.instTorque = engineTorque;
    canData->eds.instVoltage = engineVoltage;
    canData->eds.instRPM = Utils::round(rpm, 0.0859375, -2750);;
    canData->eds.txSetpoint = setpoint;

    // Transformamos los valores según el protocolo de message2
    uchar b1_current = engineCurrent >> 4;
    uchar b2_current = (engineCurrent & 0xF) << 4;

    uchar b1_torque = engineTorque >> 8;
    uchar b2_torque  = engineTorque & 0xFF;

    uchar b1_voltage = engineVoltage >> 4;
    uchar b2_voltage = (engineVoltage & 0xF) << 4;

    uchar b1_rpm= rpm >> 8;
    uchar b2_rpm = rpm & 0xFF;

    uchar b1_setpoint = setpoint >> 8;
    uchar b2_setpoint = setpoint & 0xff;

    uchar b2 = b2_current | b1_torque;
    uchar b5 = b2_voltage | b1_rpm;

    uchar data[] = {b1_current, b2, b2_torque, b1_voltage, b5, b2_rpm, b1_setpoint, b2_setpoint};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0x200, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->engineWidget->assertMessage2();
}

void MainWindow::assertMessage3(){
    assert(
        ui->engineTempValue->text() == (QString::number(data->eds.motorTemp) + "° C")
        );

    assert(
        ui->inversorValue->text() == (QString::number(data->eds.invTemp) + "° C")
    );

    assert(
        ui->batTempValue->text() == (QString::number(data->bess.avgTemp) + "° C")
        );
}

void MainWindow::testMessage3() {
    // Obtenemos valores aleatorios
    uchar engineTemp = rand() % 0xFF;
    uchar inversorTemp = rand() % 0xFF;
    uchar batTemp = rand() % 0xFF;
    uchar batMaxTemp = rand() % 0xFF;
    uchar batMinTemp = rand() % 0xFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->eds.motorTemp = engineTemp - 40;
    canData->eds.invTemp = inversorTemp - 40;
    canData->bess.avgTemp = batTemp;
    canData->bess.maxTemp = batMaxTemp;
    canData->bess.minTemp = batMinTemp;

    uchar data[] = {engineTemp, inversorTemp, batTemp, batMaxTemp, batMinTemp};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0x300, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    // Comprobamos que se actualizó la información en los widgets
    this->assertMessage3();
    this->adminPanel->batteryPanel->assertMessage3();
    this->adminPanel->engineWidget->assertMessage3();
}

void MainWindow::testMessage4() {
    // Obtenemos valores aleatorios
    int dcdc1Current = rand() % 0xFFFF;
    int dcdc2Current = rand() % 0xFFFF;
    int dcdc1HVCurrent = rand() % 0xFFFF;
    int dcdc2HVCurrent = rand() % 0xFFFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->dcdc1.lvCurr = Utils::round(dcdc1Current, 0.1 , 3212.7);
    canData->dcdc2.lvCurr = Utils::round(dcdc2Current, 0.1 , 3212.7);
    canData->dcdc1.hvCurr = Utils::round(dcdc1HVCurrent, 0.1 , 3212.7);
    canData->dcdc2.hvCurr = Utils::round(dcdc2HVCurrent, 0.1 , 3212.7);

    // Transformamos los valores según el protocolo de message4
    uchar b1 = dcdc1Current >> 8;
    uchar b2 = dcdc1Current & 0xff;

    uchar b3 = dcdc2Current >> 8;
    uchar b4 = dcdc2Current & 0xff;

    uchar b5 = dcdc1HVCurrent >> 8;
    uchar b6 = dcdc1HVCurrent & 0xff;

    uchar b7 = dcdc2HVCurrent >> 8;
    uchar b8 = dcdc2HVCurrent & 0xff;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7, b8};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0x400, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->engineWidget->assertMessage4();
}

void MainWindow::testMessage5() {
    // Obtenemos valores aleatorios
    int dcdc1OutputVoltage = rand() % 0xFF;
    int dcdc2OutputVoltage = rand() % 0xFF;
    int dcdc1InputVoltage = rand() % 0xFF;
    int dcdc2InputVoltage = rand() % 0xFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->dcdc1.VVout = Utils::round(dcdc1OutputVoltage, 0.05);
    canData->dcdc2.VVout = Utils::round(dcdc2OutputVoltage, 0.05);
    canData->dcdc1.Vin = Utils::round(dcdc1InputVoltage, 0.05);
    canData->dcdc2.Vin = Utils::round(dcdc2InputVoltage, 0.05);

    // Transformamos los valores según el protocolo de message5
    uchar b1 = dcdc1OutputVoltage >> 8;
    uchar b2 = dcdc1OutputVoltage &0xff;

    uchar b3 = dcdc2OutputVoltage >> 8;
    uchar b4 = dcdc2OutputVoltage &0xff;

    uchar b5 = dcdc1InputVoltage >> 8;
    uchar b6 = dcdc1InputVoltage &0xff;

    uchar b7 = dcdc2InputVoltage >> 8;
    uchar b8 = dcdc2InputVoltage &0xff;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7, b8};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0x500, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->engineWidget->assertMessage5();
}

void MainWindow::testMessage6() {
    // Obtenemos valores aleatorios
    int posResistanceSIM100 = rand() % 0xFF;
    int negResistanceSIM100 = rand() % 0xFF;
    int posResistanceBMU = rand() % 0xFF;
    int negResistanceBMU = rand() % 0xFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->sim100.Rp = posResistanceSIM100;
    canData->sim100.Rn = negResistanceSIM100;
    canData->bess.Rp = posResistanceBMU;
    canData->bess.Rn = negResistanceBMU;

    // Transformamos los valores según el protocolo de message6
    uchar b1 = posResistanceSIM100 >> 8;
    uchar b2 = posResistanceSIM100 &0xff;

    uchar b3 = negResistanceSIM100 >> 8;
    uchar b4 = negResistanceSIM100 &0xff;

    uchar b5 = posResistanceBMU >> 8;
    uchar b6 = posResistanceBMU &0xff;

    uchar b7 = negResistanceBMU >> 8;
    uchar b8 = negResistanceBMU &0xff;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7, b8};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0x600, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->engineWidget->assertMessage6();
}

void MainWindow::testMessage7() {
    // Obtenemos valores aleatorios
    int lvError = rand() % 7;
    int hvError = rand() % 7;
    int state = rand() % 7;
    int inhibitState = rand() % 2;
    int busHVDischarged = rand() % 2;
    int pduContactorClose = rand() % 2;
    int hvOn = rand() % 2;
    int lvHigh = rand() % 3;
    int dcdc1Overtemp = rand() % 2;
    int dcdc2Overtemp = rand() % 2;
    int atsFanFault = rand() % 2;
    int atsPumpFault = rand() % 2;
    int edsOvertemp = rand() % 2;
    int obcOvertemp = rand() % 2;
    int edsInError = rand() % 2;
    int edsCouldntClear = rand() % 2;
    int dcdcHighDifference = rand() % 2;
    int batModule1 = rand() % 2;
    int batModule2 = rand() % 2;
    int batModule3 = rand() % 2;
    int batModule4 = rand() % 2;
    int contactorPdu = rand() % 2;
    int sim100Stucked = rand() % 2;
    int couldntPowerOnBMS = rand() % 2;
    int bessPowerOffHv = rand() % 2;
    int requiredHvOff = rand() % 2;
    int pedal1Anormal = rand() % 2;
    int pedal2Anormal = rand() % 2;
    int hvilPdu = rand() % 2;
    int hvilObc = rand() % 2;
    int hvilEds = rand() % 2;
    int hvilDddc = rand() % 2;
    int termistorLVOutOfRange = rand() % 2;
    int termistorHVOutOfRange = rand() % 2;
    int pduTempExcess = rand() % 2;
    int overturn = rand() % 2;
    int doorOpen = rand() % 2;
    int parkingState = rand() % 2;
    int estadoMarcha = rand() % 3;


    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->processVars.LV_Error_Level = lvError;
    canData->processVars.HV_Error_Level = hvError;
    canData->processVars.EMIX_state = state;
    canData->processVars.EMIX_inhibitState = inhibitState;
    canData->processVars.isHVBusDischarged = busHVDischarged;
    canData->processVars.IsPDUmainRelayClosed = pduContactorClose;
    canData->processVars.IsHVOn = hvOn;
    canData->processVars.LvVoltageTooHigh = lvHigh;
    canData->processVars.DCDC1Overtemp = dcdc1Overtemp;
    canData->processVars.DCDC2Overtemp = dcdc2Overtemp;
    canData->processVars.ATS_Fan_Fault = atsFanFault;
    canData->processVars.ATS_Pump_Fault = atsPumpFault;
    canData->processVars.EDSOvertemp = edsOvertemp;
    canData->processVars.OBCOvertemp = obcOvertemp;
    canData->processVars.EDSinError = edsInError;
    canData->processVars.EDScantClearError = edsCouldntClear;
    canData->processVars.DCDCsPwrDifference2Large = dcdcHighDifference;
    canData->processVars.BESS_Module1TempTooLarge = batModule1;
    canData->processVars.BESS_Module2TempTooLarge = batModule2;
    canData->processVars.BESS_Module3TempTooLarge = batModule3;
    canData->processVars.BESS_Module4TempTooLarge = batModule4;
    canData->processVars.PDUMainRelayCantChangeState = contactorPdu;
    canData->processVars.Sim100Stuck = sim100Stucked;
    canData->processVars.ImpossibleToSwitchOnBMS = couldntPowerOnBMS;
    canData->processVars.BMSrequestsHvOff = bessPowerOffHv;
    canData->processVars.HvOffIsRequired = requiredHvOff;
    canData->processVars.Pedal2Abnormal = pedal2Anormal;
    canData->processVars.Pedal1Abnormal = pedal1Anormal;
    canData->processVars.PDU_HvilAlarm = hvilPdu;
    canData->processVars.OBC_HvilAlarm = hvilObc;
    canData->processVars.EDS_HvilAlarm = hvilEds;
    canData->processVars.DCDCs_HvilAlarm = hvilDddc;
    canData->processVars.LvThermistorOutOfRange = termistorLVOutOfRange;
    canData->processVars.HvThermistorOutOfRange = termistorHVOutOfRange;
    canData->processVars.PDUOvertemp = pduTempExcess;
    canData->processVars.OverturnEvent = overturn;
    canData->processVars.CabinDoorOpen = doorOpen;
    canData->processVars.ParkingRelayState = parkingState;
    canData->processVars.MarchState = estadoMarcha;

    // Transformamos los valores según el protocolo de message6
    uchar b0_4 = lvError << 4;
    uchar b4_8 = hvError;

    uchar byte1 = b0_4 | b4_8;

    uchar b8_12 = state << 4;
    uchar b12_13 = inhibitState << 3;
    uchar b13_14 = busHVDischarged << 2;
    uchar b14_15 = pduContactorClose << 1;
    uchar b15_16 = hvOn;

    uchar byte2 = b8_12 | b12_13 | b13_14 | b14_15 | b15_16;

    uchar b16_18 = lvHigh << 6;
    uchar b18_19 = dcdc1Overtemp << 5;
    uchar b19_20 = dcdc2Overtemp << 4;
    uchar b20_21 = atsFanFault << 3;
    uchar b21_22 = atsPumpFault << 2;
    uchar b22_23 = edsOvertemp << 1;
    uchar b23_24 = obcOvertemp;

    uchar byte3 = b16_18 | b18_19 | b19_20 | b20_21 | b21_22 | b22_23 | b23_24;

    uchar b24_25 = edsInError << 7;
    uchar b25_26 = edsCouldntClear << 6;
    uchar b26_27 = dcdcHighDifference << 5;
    uchar b27_28 = batModule1 << 4;
    uchar b28_29 = batModule2 << 3;
    uchar b29_30 = batModule3 << 2;
    uchar b30_31 = batModule4 << 1;
    uchar b31_32 = contactorPdu;

    uchar byte4 = b24_25 | b25_26 | b26_27 | b27_28 | b28_29 | b29_30 | b30_31 | b31_32;

    uchar b32_33 = sim100Stucked << 7;
    uchar b33_34 = couldntPowerOnBMS << 6;
    uchar b34_35 = bessPowerOffHv << 5;
    uchar b35_36 = requiredHvOff << 4;
    uchar b36_37 = pedal2Anormal << 3;
    uchar b37_38 = pedal1Anormal << 2;
    uchar b38_39 = hvilPdu << 1;
    uchar b39_40 = hvilObc;

    uchar byte5 = b32_33 | b33_34 | b34_35 | b35_36 | b36_37 | b37_38 | b38_39 | b39_40;

    uchar b40_41 = hvilEds << 7;
    uchar b41_42 = hvilDddc << 6;
    uchar b42_43 = termistorLVOutOfRange << 5;
    uchar b43_44 = termistorHVOutOfRange << 4;
    uchar b44_45 = pduTempExcess << 3;
    uchar b45_46 = overturn << 2;
    uchar b46_47 = doorOpen << 1;
    uchar b47_48 = parkingState;

    uchar byte6 = b40_41 | b41_42 | b42_43 | b43_44 | b44_45 | b45_46 | b46_47 | b47_48;

    uchar byte7 = estadoMarcha << 6;

    uchar data[] = {byte1, byte2, byte3, byte4, byte5, byte6, byte7, 00};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0x700, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->processVarsWidget->assertMessage7();


}

void MainWindow::testBess1() {
    // Obtenemos valores aleatorios
    int trama = ((rand() % 63) * 3) + 1;
    int v1 = rand() % 0xFFFF;
    int v2 = rand() % 0xFFFF;
    int v3 = rand() % 0xFFFF;

    float fc = 0.001;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->voltageCells[trama - 1] = Utils::round(v1, fc);
    canData->voltageCells[trama] = Utils::round(v2, fc);
    canData->voltageCells[trama + 1] = Utils::round(v3, fc);

    // Transformamos los valores según el protocolo de bess1
    uchar b2 = trama >> 8;
    uchar b1 = trama & 0xFF;

    uchar b4 = v1 >> 8;
    uchar b3 = v1 & 0xFF;

    uchar b6 = v2 >> 8;
    uchar b5 = v2 & 0xFF;

    uchar b8 = v3 >> 8;
    uchar b7 = v3 & 0xFF;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7, b8};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0xC100, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->batteryPanel->assertBess1(trama, Utils::round(v1, fc), Utils::round(v2, fc), Utils::round(v3, fc));
}

void MainWindow::testBess2(){
    // Obtenemos valores aleatorios
    int trama = ((rand() % 3) * 6 + 1);
    int t1 = rand() % 0xFF;
    int t2 = rand() % 0xFF;
    int t3 = rand() % 0xFF;
    int t4 = rand() % 0xFF;
    int t5 = rand() % 0xFF;
    int t6 = rand() % 0xFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->tempCells[trama - 1] = t1;
    canData->tempCells[trama] = t2;
    canData->tempCells[trama + 1] = t3;
    canData->tempCells[trama + 2] = t4;
    canData->tempCells[trama + 3] = t5;
    canData->tempCells[trama + 4] = t6;

    // Transformamos los valores según el protocolo de bess2
    uchar b2 = trama >> 8;
    uchar b1 = trama & 0xff;

    uchar b3 = t1 & 0xff;
    uchar b4 = t2 & 0xff;

    uchar b5 = t3 & 0xff;
    uchar b6 = t4 & 0xff;

    uchar b7 = t5 & 0xff;
    uchar b8 = t6 & 0xff;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7, b8};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0xC200, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->batteryPanel->assertBess2(trama, t1, t2, t3, t4, t5, t6);
}

void MainWindow::testBess3() {
    // Obtenemos valores aleatorios
    int chargeEnergyAcumulated = rand() % 0xFFFFFF;
    int dischargeEnergyAcumulated = rand() % 0xFFFFFF;
    int energyOneCharge = rand() % 0xFFFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->chargeEnergyAcumulated = chargeEnergyAcumulated;
    canData->dischargeEnergyAcumulated = dischargeEnergyAcumulated;
    canData->energyOneCharge = Utils::round(energyOneCharge, 0.1);

    // Transformamos los valores según el protocolo de bess3
    uchar b1 = chargeEnergyAcumulated >> 16;
    uchar b2 = (chargeEnergyAcumulated >> 8) & 0xFF;
    uchar b3 = chargeEnergyAcumulated & 0xFF;

    uchar b4 = dischargeEnergyAcumulated >> 16;
    uchar b5 = (dischargeEnergyAcumulated >> 8) & 0xFF;
    uchar b6 = dischargeEnergyAcumulated & 0xFF;

    uchar b7 = energyOneCharge >> 8;
    uchar b8 = energyOneCharge & 0xFF;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7,b8};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0xC300, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->batteryPanel->assertBess3(chargeEnergyAcumulated, dischargeEnergyAcumulated, Utils::round(energyOneCharge, 0.1));
}

void MainWindow::testBess4() {
    // Obtenemos valores aleatorios
    int SOC = rand() % 101;
    int SOH = rand() % 0xFF;
    int maxVoltage = rand() % 0xFFFF;
    int minVoltage = rand() % 0xFFFF;
    int meanVoltage = rand() % 0xFFFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->bess.SoC = Utils::round(SOC, 0.4);
    canData->SOH = Utils::round(SOH, 0.4);
    canData->maxVoltage = Utils::round(maxVoltage, 0.001);
    canData->minVoltage = Utils::round(minVoltage, 0.001);
    canData->meanVoltage = Utils::round(meanVoltage, 0.001);

    // Transformamos los valores según el protocolo de message5
    uchar b1 = SOC & 0xFF;
    uchar b2 = SOH & 0xFF;

    uchar b3 = maxVoltage >> 8;
    uchar b4 = maxVoltage & 0xFF;

    uchar b5 = minVoltage >> 8;
    uchar b6 = minVoltage & 0xFF;

    uchar b7 = meanVoltage >> 8;
    uchar b8 = meanVoltage & 0xFF;

    uchar data[] = {b1, b2, b3, b4, b5, b6, b7,b8};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0xC400, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->batteryPanel->assertBess4();
}

void MainWindow::testBess5() {
    // Obtenemos valores aleatorios
    int posChargeTempDC = rand() % 0xFF;
    int negChargeTempDC = rand() % 0xFF;
    int dcConected = rand() % 3;
    int bmsChargingMode = rand() % 3;
    int coolingState = rand() % 1;
    int heatState = rand() % 1;
    int bmuContactor = rand() % 3;
    int bmsFailures = rand() % 0xFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->posChargeTempDC = posChargeTempDC - 40;
    canData->negChargeTempDC = negChargeTempDC - 40;
    canData->dcConected = dcConected;
    canData->bmsChargingMode = bmsChargingMode;
    canData->coolingState = coolingState;
    canData->heatState = heatState;
    canData->bmuContactor = bmuContactor;
    canData->bmsFailures = bmsFailures;

    // Transformamos los valores según el protocolo de bess5
    uchar b1 = posChargeTempDC & 0xFF;
    uchar b2 = negChargeTempDC & 0xFF;

    uchar b3_0_2 = dcConected << 6;
    uchar b3_2_4 = bmsChargingMode << 4;
    uchar b3_4_5 = coolingState << 3;
    uchar b3_5_6 = heatState << 2;
    uchar b3_6_8 = bmuContactor;

    uchar b3 = b3_0_2 | b3_2_4 | b3_4_5 | b3_5_6 | b3_6_8;
    uchar b4 = bmsFailures;

    uchar data[] = {b1, b2, b3, b4, 0, 0, 0, 0};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0xC500, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->engineWidget->assertBess5();
    this->adminPanel->processVarsWidget->assertBess5();

}

void MainWindow::testEmix1() {
    int edsFailures = rand() % 0xFF;
    int dcdc1Failures = rand() % 0xFF;
    int dcdc2Failures = rand() % 0xFF;
    int sim100Failures = rand() % 0xFF;
    int obcFailures = rand() % 0xFF;
    int emixFailures = rand() % 0xFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->edsFailures = edsFailures;
    canData->dcdc1Failures = dcdc1Failures;
    canData->dcdc2Failures = dcdc2Failures;
    canData->sim100Failures = sim100Failures;
    canData->obcFailures = obcFailures;
    canData->emixFailures = emixFailures;

    // Transformamos los valores según el protocolo de emix1
    uchar b1 = edsFailures;
    uchar b2 = dcdc1Failures;
    uchar b3 = dcdc2Failures;
    uchar b4 = sim100Failures;
    uchar b5 = obcFailures ;
    uchar b6 = emixFailures;

    uchar data[] = {b1, b2, b3, b4, b5, b6, 0, 0};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0xC600, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->processVarsWidget->assertEmix1();
}

void MainWindow::testFaults1() {
    int dcdc1ErrorCode = rand() % 0xFFFF;
    int dcdc2ErrorCode = rand() % 0xFFFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->dcdc1ErrorCode = dcdc1ErrorCode;
    canData->dcdc2ErrorCode = dcdc2ErrorCode;

    // Transformamos los valores según el protocolo de faults1
    uchar b1 = dcdc1ErrorCode >> 8;
    uchar b2 = dcdc1ErrorCode & 0xFF;

    uchar b3 = dcdc2ErrorCode >> 8;
    uchar b4 = dcdc2ErrorCode & 0xFF;

    uchar data[] = {b1, b2, b3, b4, 0, 0, 0, 0};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0xD000, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->processVarsWidget->assertFaults1();

}

void MainWindow::testFaults2() {
    int edsErrorCode = rand() % 0xFFFF;
    int obcErrorCode = rand() % 0xFFFF;

    // Clonamos el objeto y actualizamos sus valores
    CANData *canData = this->data->clone();
    canData->edsErrorCode = edsErrorCode;
    canData->obcErrorCode = obcErrorCode;

    // Transformamos los valores según el protocolo de faults1
    uchar b1 = edsErrorCode >> 8;
    uchar b2 = edsErrorCode & 0xFF;

    uchar b3 = obcErrorCode >> 8;
    uchar b4 = obcErrorCode & 0xFF;

    uchar data[] = {b1, b2, b3, b4, 0, 0, 0, 0};

    // Simulamos la recepción del mensaje
    this->receiveMessage(0, 0xD100, data);

    // Comprobamos que se actualizó correctamente el objeto con los datos
    assert((*canData) == (*this->data));

    this->adminPanel->processVarsWidget->assertFaults2();

}
