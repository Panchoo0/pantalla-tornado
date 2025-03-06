#include "notificationswidget.h"
#include "ui_notificationswidget.h"
#include <QTimer>
#include <utils.h>

// Widget que maneja las alertas mostradas en la pantalla principal
NotificationsWidget::NotificationsWidget(CANData *canData,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NotificationsWidget)
{
    ui->setupUi(this);
    this->canData = canData;

    // timer para cambiar de alerta
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextNotification()));
    timer->start(1000);
}

// Función para cambiar de alerta
void NotificationsWidget::nextNotification() {
    if (this->canData->canErrors.size() == 0) return;
    this->currentSlide = (this->currentSlide + 1) % this->canData->canErrors.size();
    DTCCanError error = this->canData->canErrors[this->currentSlide];
    uchar b1 = error.code >> 8;
    uchar b2 = error.code & 0xFF;
    uchar hex_b[] = {b1, b2};
    ui->category->setText(error.category);
    ui->from->setText(error.equipment);
    // ui->code->setText("Código: " + QString::number(error.code));
    ui->code->setText("Id: " + Utils::toHexString(hex_b, 2));
    ui->description->setText(error.description);
}

NotificationsWidget::~NotificationsWidget()
{
    delete ui;
}
