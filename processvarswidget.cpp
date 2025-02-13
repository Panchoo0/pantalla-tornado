#include "processvarswidget.h"
#include "ui_processvarswidget.h"
#include <checkboxwidget.h>

ProcessVarsWidget::ProcessVarsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProcessVarsWidget)
{
    ui->setupUi(this);
}

ProcessVarsWidget::~ProcessVarsWidget()
{
    delete ui;
}
