#ifndef ENGINEWIDGET_H
#define ENGINEWIDGET_H

#include <QWidget>
#include <candata.h>

namespace Ui {
class EngineWidget;
}

class EngineWidget : public QWidget
{
    Q_OBJECT

public:
    CANData *canData;
    explicit EngineWidget(CANData *canData, QWidget *parent = nullptr);
    ~EngineWidget();

    void assertMessage2(int engineCurrent, int engineTorque, int engineVoltage, int rpm, int setpoint);
    void assertMessage3(int engineTemp, int inversorTemp, int batTemp, int batMaxTemp, int batMinTemp);
    void assertMessage4(int dcdc1Current, int dcdc2Current, int dcdc1HVCurrent, int dcdc2HVCurrent);
    void assertMessage5(int dcdc1OutputVoltage, int dcdc2OutputVoltage, int dcdc1InputVoltage, int dcdc2InputVoltage);
    void assertMessage6(int posResistanceSIM100, int negResistanceSIM100, int posResistanceBMU, int negResistanceBMU);

    void assertBess5(int posChargeTempDC, int negChargeTempDC, int dcConected, int bmsChargingMode, int coolingState, int heatState, int bmuContactor, int bmsFailures);

public slots:

    void message2();
    void message3();
    void message4();
    void message5();
    void message6();

    void bess5();

private:
    Ui::EngineWidget *ui;
};

#endif // ENGINEWIDGET_H
