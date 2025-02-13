#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

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
    datetimeTimer->start(500);

    // Inicializamos los datos que provendran el bus CAN
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

    // Cargamos las imágenes de los iconos de temperatura
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

    this->data->addError(2);

    notificationsWidget = new NotificationsWidget(this->data,this);
    notificationsWidget->setGeometry(398, 18, 384, 94);

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
void MainWindow::updateSpeed(int value)
{
    ui->needleContainer->rotate(270 * (value - this->data->speed) / 120.0f);
    ui->speedValue->setText(QString::number(value));

    this->data->speed = value;
}

// Función que actualiza la temperatura del motor
void MainWindow::updateEngineTemp(int value) {
    this->data->engineTemp = value;

    // Actualizamos el ícono según el valor
    if (value <30) {
        ui->engineTempIcon->setPixmap(this->lowTempIcon);
    } else if (value < 50) {
        ui->engineTempIcon->setPixmap(this->regularTempIcon);
    } else {
        ui->engineTempIcon->setPixmap(this->highTempIcon);
    }

    // Actualizamos el texto
    ui->engineTempValue->setText(QString::number(value) + "° C");
}

// Función que actualiza la temperatura del inversor
void MainWindow::updateInversorTemp(int value) {
    this->data->inversorTemp = value;

    // Actualizamos el ícono según el valor
    if (value <30) {
        ui->inversorTempIcon->setPixmap(this->lowTempIcon);
    } else if (value < 50) {
        ui->inversorTempIcon->setPixmap(this->regularTempIcon);
    } else {
        ui->inversorTempIcon->setPixmap(this->highTempIcon);
    }

    // Actualizamos el texto
    ui->inversorValue->setText(QString::number(value) + "° C");
}

// Función que actualiza la temperatura de la batería
void MainWindow::updateBatTemp(int value) {
    this->data->batTemp = value;

    // Actualizamos el ícono según el valor
    if (value <30) {
        ui->batTempIcon->setPixmap(this->lowTempIcon);
    } else if (value < 50) {
        ui->batTempIcon->setPixmap(this->regularTempIcon);
    } else {
        ui->batTempIcon->setPixmap(this->highTempIcon);
    }

    // Actualizamos el texto
    ui->batTempValue->setText(QString::number(value) + "° C");
}

// Función que actualiza la carga de la batería.
// Recibe la nueva carga de la batería en un entero que representa el porcentaje
void MainWindow::updateBat(int value) {
    this->data->bat = value;

    // Para crear la animación de la batería se corta la parte superior de la imágen
    int iconHeight = this->highBatIcon.height();
    int croppedY = 100 - value; // Porciento de cuanto se cortará la imágen
    int cropY = (iconHeight * croppedY) / 100; // Cuantos pixeles en el eje Y serán cortados
    int croppedHeight = iconHeight - cropY; // Nueva altura de la imagen

    QPixmap croppedPixmap;
    // Se elige la imágen según la carga restante
    if (value < 30)  {
        croppedPixmap = this->highBatIcon.copy(0, cropY, this->highBatIcon.width(), croppedHeight);
    } else if (value < 50) {
        croppedPixmap = this->regularBatIcon.copy(0, cropY, this->highBatIcon.width(), croppedHeight);
    } else {
        croppedPixmap = this->lowBatIcon.copy(0, cropY, this->highBatIcon.width(), croppedHeight);
    }

    QString style = QString::fromStdString("margin-top: " + std::to_string(iconHeight - croppedHeight) + "px;");

    ui->batFill->setPixmap(croppedPixmap);
    ui->batFill->setStyleSheet(style);

    ui->batValue->setText(QString::number(value));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->updateSpeed(value);
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    this->updateInversorTemp(value);
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    this->updateEngineTemp(value);
}


void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    this->updateBatTemp(value);
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    this->updateBat(value);
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
}


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

