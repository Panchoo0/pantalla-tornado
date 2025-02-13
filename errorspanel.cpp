#include "errorspanel.h"
#include "ui_errorspanel.h"
#include <QDebug>
#include <QScrollBar>

ErrorsPanel::ErrorsPanel(CANData *canData, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ErrorsPanel)
{
    ui->setupUi(this);

    this->canData = canData;


}

void ErrorsPanel::addError() {

    int row = this->canData->canErrors.size() - 1;
    DTCCanError error = this->canData->canErrors[row];
    new ErrorListItem(ui->table, row, error);

}

ErrorsPanel::~ErrorsPanel()
{
    delete ui;
}
