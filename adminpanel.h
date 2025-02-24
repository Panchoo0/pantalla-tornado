#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include <enginewidget.h>
#include <errorspanel.h>
#include <batterypanel.h>
#include <processvarswidget.h>
#include <candata.h>

enum TABS {
    ENGINE,
    BATTERY,
    PROCESS_VARS,
    ERRORS
};

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QDialog
{
    Q_OBJECT

public:
    EngineWidget *engineWidget;
    ErrorsPanel *errorsPanel;
    BatteryPanel *batteryPanel;
    ProcessVarsWidget *processVarsWidget;
    CANData *canData;

    explicit AdminPanel(CANData *canData, QWidget *parent = nullptr);
    ~AdminPanel();

private:
    void onTabChange(TABS tab);
private slots:
    void on_engineTabButton_clicked();

    void on_batteryTabButton_clicked();

    void on_errorsTabButton_clicked();

    void on_closeButton_clicked();

    void on_processVarsButton_clicked();
public:
    Ui::AdminPanel *ui;
};

#endif // ADMINPANEL_H
