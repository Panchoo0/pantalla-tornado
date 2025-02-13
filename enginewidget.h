#ifndef ENGINEWIDGET_H
#define ENGINEWIDGET_H

#include <QWidget>

namespace Ui {
class EngineWidget;
}

class EngineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EngineWidget(QWidget *parent = nullptr);
    ~EngineWidget();

private:
    Ui::EngineWidget *ui;
};

#endif // ENGINEWIDGET_H
