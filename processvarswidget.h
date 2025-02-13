#ifndef PROCESSVARSWIDGET_H
#define PROCESSVARSWIDGET_H

#include <QWidget>

namespace Ui {
class ProcessVarsWidget;
}

class ProcessVarsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessVarsWidget(QWidget *parent = nullptr);
    ~ProcessVarsWidget();

private:
    Ui::ProcessVarsWidget *ui;
};

#endif // PROCESSVARSWIDGET_H
