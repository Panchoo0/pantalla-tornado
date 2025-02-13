#ifndef NOTIFICATIONSWIDGET_H
#define NOTIFICATIONSWIDGET_H

#include <QWidget>
#include <candata.h>

namespace Ui {
class NotificationsWidget;
}

class NotificationsWidget : public QWidget
{
    Q_OBJECT

public:
    QTimer* timer;
    CANData *canData;
    int currentSlide;
    explicit NotificationsWidget(CANData *canData, QWidget *parent = nullptr);
    ~NotificationsWidget();


private:
    Ui::NotificationsWidget *ui;

private slots:
    void nextNotification();
};

#endif // NOTIFICATIONSWIDGET_H
