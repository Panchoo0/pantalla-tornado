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

    void assertMessage2();
    void assertMessage3();
    void assertMessage4();
    void assertMessage5();
    void assertMessage6();

    void assertBess5();

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
