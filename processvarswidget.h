#ifndef PROCESSVARSWIDGET_H
#define PROCESSVARSWIDGET_H

#include <QWidget>
#include <candata.h>

namespace Ui {
class ProcessVarsWidget;
}

class ProcessVarsWidget : public QWidget
{
    Q_OBJECT

public:
    CANData *data;
    explicit ProcessVarsWidget(CANData *data, QWidget *parent = nullptr);
    ~ProcessVarsWidget();
public slots:
    void message7();
    void bess5();
    void emix1();
    void faults1();
    void faults2();
private:
    Ui::ProcessVarsWidget *ui;
};

#endif // PROCESSVARSWIDGET_H
