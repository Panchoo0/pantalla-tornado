#include "notificationswidget.h"
#include "ui_notificationswidget.h"
#include <QTimer>

NotificationsWidget::NotificationsWidget(CANData *canData,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NotificationsWidget)
{
    ui->setupUi(this);
    this->canData = canData;

    // timer

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextNotification()));
    timer->start(1000);
}

void NotificationsWidget::nextNotification() {
    this->currentSlide = (this->currentSlide + 1) % this->canData->canErrors.size();
    DTCCanError error = this->canData->canErrors[this->currentSlide];

    ui->category->setText(error.category);
    ui->from->setText(error.from);
    ui->priority->setText("Prioridad: " + QString::number(error.priority));
    ui->desciption->setText(error.description);
}

NotificationsWidget::~NotificationsWidget()
{
    delete ui;
}
