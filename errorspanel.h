#ifndef ERRORSPANEL_H
#define ERRORSPANEL_H

#include <QWidget>
#include <QLabel>
#include <dtccanerror.h>
#include <candata.h>

enum SORTER_MODE {
    NONE,
    ASC,
    DESC,
};


class ErrorListItem: public QWidget {
public:
    int originalRow;

    QLabel* date;
    QLabel* ID;
    QLabel* equipment;
    QLabel* description;
    DTCCanError* error;
    static const int height = 120;

    ErrorListItem(QWidget *parent, int row, DTCCanError& error): QWidget(parent) {
        this->originalRow = row;

        this->setGeometry(0, row * height, 635, height);
        this->setStyleSheet("border-bottom: 2px solid #00A6A7; font-size: 14px; color: white");

        date = new QLabel(this);
        date->setGeometry(0, 0, 145, height);
        date->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        ID = new QLabel(this);
        ID->setGeometry(145, 0, 115, height);
        ID->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        equipment = new QLabel(this);
        equipment->setGeometry(260, 0, 115, height);
        equipment->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        description = new QLabel(this);
        description->setGeometry(375, 0, 260, height);
        description->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        this->updateRow(error);
        this->error = &error;
    }

    void updateRow(DTCCanError& error) {
        this->date->setText(error.date.toString("dddd, dd MMMM yy"));
        this->ID->setText(QString::number(error.code));
        this->equipment->setText(error.equipment);
        this->description->setText(error.description);
    }

    void updatePosition(int row) {
        this->setGeometry(0, row * height, 635, height);
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
    SORTER_MODE dateSorterMode = SORTER_MODE::ASC;
    bool showDcdc1 = true;
    std::vector<ErrorListItem *> items;

    explicit ErrorsPanel(CANData *canData, QWidget *parent = nullptr);
    ~ErrorsPanel();

    void sort();

public slots:
    void addError(int row);
    void canError();

private slots:
    void on_dateSorterButton_clicked();
    void onDcdc1Check();

private:
    Ui::ErrorsPanel *ui;
};

#endif // ERRORSPANEL_H
