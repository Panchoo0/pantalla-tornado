#ifndef ERRORSPANEL_H
#define ERRORSPANEL_H

#include <QWidget>
#include <QLabel>
#include <dtccanerror.h>
#include <candata.h>

class ErrorListItem: public QWidget {
public:
    QLabel* date;
    QLabel* ID;
    QLabel* equipment;
    QLabel* description;

    ErrorListItem(QWidget *parent, int row, DTCCanError error): QWidget(parent) {
        this->setGeometry(0, 25 + row * 35, 635, 60);
        this->setStyleSheet("border-bottom: 2px solid #00A6A7; font-size: 14px; color: white");

        date = new QLabel(this);
        date->setGeometry(0, 0, 145, 60);
        date->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        ID = new QLabel(this);
        ID->setGeometry(145, 0, 115, 60);
        ID->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        equipment = new QLabel(this);
        equipment->setGeometry(260, 0, 115, 60);
        equipment->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        description = new QLabel(this);
        description->setGeometry(375, 0, 260, 60);
        description->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        this->updateRow(error);
    }

    void updateRow( DTCCanError error) {
        this->date->setText(error.date.toString("dddd, dd MMMM yy"));
        this->ID->setText(QString::number(error.code));
        this->equipment->setText(error.from);
        this->description->setText(error.description);

    }
};


namespace Ui {
class ErrorsPanel;
}

class ErrorsPanel : public QWidget
{
    Q_OBJECT

public:
    CANData *canData;
    explicit ErrorsPanel(CANData *canData, QWidget *parent = nullptr);
    ~ErrorsPanel();

public slots:
    void addError();

private:
    Ui::ErrorsPanel *ui;
};

#endif // ERRORSPANEL_H
