#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <candata.h>
#include <adminpanel.h>
#include <notificationswidget.h>
#include <receivecandata.h>
#include <sendcandata.h>

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

    bool isAdminPanelOpen;
    AdminPanel *adminPanel;
    NotificationsWidget *notificationsWidget;

    ReceiveCANData* receiver;
    SendCANData* sender;


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    void startReceivingCAN();
    void activateCANChannel();

private:
    void assertMessage1(int current, int voltage, int soc);
    void testMessage1(int current, int voltage, int soc);

    void testMessage2(int engineCurrent, int engineTorque, int engineVoltage, int rpm, int setpoint);

    void assertMessage3(int engineTemp, int inversorTemp, int batTemp, int batMaxTemp, int batMinTemp);
    void testMessage3(int engineTemp, int inversorTemp, int batTemp, int batMaxTemp, int batMinTemp);

    void testMessage4(int dcdc1Current, int dcdc2Current, int dcdc1HVCurrent, int dcdc2HVCurrent);

    void testMessage5(int dcdc1OutputVoltage, int dcdc2OutputVoltage, int dcdc1InputVoltage, int dcdc2InputVoltage);

    void testMessage6(int posResistanceSIM100, int negResistanceSIM100, int posResistanceBMU, int negResistanceBMU);

    void testBess1(int trama, int v1, int v2, int v3);
    void testBess2(int trama, int t1, int t2, int t3, int t4, int t5, int t6);
    void testBess3(int chargeEnergyAcumulated, int dischargeEnergyAcumulated, int energyOneCharge);
    void testBess4(int SOC, int SOH, int minVoltage, int maxVoltage, int meanVoltage);
    void testBess5(int posChargeTempDC, int negChargeTempDC, int dcConected, int bmsChargingMode, int coolingState, int heatState, int bmuContactor, int bmsFailures);

    void emix1(int edsFailures, int dcdc1Failures, int dcdc2Failures, int sim100Failures, int obcFailures, int emixFailures);
    void faults1(int dcdc1ErrorCode, int dcdc2ErrorCode);
    void faults2(int edsErrorCode, int obcErrorCode);

private slots:
    void updateDateTime();
    void updateSpeed();
    void updateEngineTemp();
    void updateInversorTemp();
    void updateBatTemp();
    void updateBat();

    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_verticalSlider_valueChanged(int value);
    void on_pushButton_clicked();
    void on_confButton_clicked();

    void message1();
    void message3();

    void receiveMessage(unsigned char sourceAddress, unsigned int pgn, uint8_t* receivedData);
    void receiveDebugMessage(QString msg);

    void sendMessage();

    void testCan();
};
#endif // MAINWINDOW_H
