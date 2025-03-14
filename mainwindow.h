#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <candata.h>
#include <adminpanel.h>
#include <notificationswidget.h>
#include <receivecandata.h>
#include <UDSCanData.h>
#include <testigocontroller.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer* datetimeTimer;
    CANData *data;

    QPixmap lowTempIcon;
    QPixmap regularTempIcon;
    QPixmap highTempIcon;

    QPixmap lowBatIcon;
    QPixmap regularBatIcon;
    QPixmap highBatIcon;

    AdminPanel *adminPanel;
    NotificationsWidget *notificationsWidget;

    ReceiveCANData* receiver;
    UDSCanData* sender;

    TestigoController* testigos;

    QTimer* udsTimer;

    QDateTime startDate;


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    void startReceivingCAN();
    void activateCANChannel();

    void assertMessage1();
    void assertMessage3();

    void testMessage1();
    void testMessage2();
    void testMessage3();
    void testMessage4();
    void testMessage5();
    void testMessage6();
    void testMessage7();
    void testBess1();
    void testBess2();
    void testBess3();
    void testBess4();
    void testBess5();

    void testEmix1();
    void testFaults1();
    void testFaults2();

private slots:
    void updateDateTime();
    void updateSpeed();
    void updateEngineTemp();
    void updateInversorTemp();
    void updateBatTemp();
    void updateBat();

    void updateMainWindow();

    void on_pushButton_clicked();
    void on_confButton_clicked();

    void message1();
    void message3();
    void message7();

    void receiveMessage(unsigned char sourceAddress, unsigned int pgn, uint8_t* receivedData);
    void receiveDebugMessage(QString msg);

    void testCan();
    void testCanErrors();

};
#endif // MAINWINDOW_H
