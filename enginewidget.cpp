#include "enginewidget.h"
#include "ui_enginewidget.h"

EngineWidget::EngineWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EngineWidget)
{
    ui->setupUi(this);
}

EngineWidget::~EngineWidget()
{
    delete ui;
}
