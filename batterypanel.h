#ifndef BATTERYPANEL_H
#define BATTERYPANEL_H

#include <QWidget>
#include <QLabel>
#include <candata.h>


// Widget auxiliar para represantar cada item de la lista de temperaturas de celdas
class TempListItem: public QWidget {
public:

    QLabel* t1;
    QLabel* t2;
    QLabel* t3;
    QLabel* t4;
    QLabel* t5;
    QLabel* t6;

public:
    TempListItem(QWidget *parent, int rowVal): QWidget(parent) {
        this->setGeometry(7 + rowVal % 3 * 220, rowVal / 3 * 90, 210, 83);

        QLabel* row = new QLabel(QString::number(rowVal + 1), this);
        row->setGeometry(0, 0, 210, 15);
        row->setStyleSheet("color: #00A6A7");
        row->setAlignment(Qt::AlignHCenter);

        QLabel *dec = new QLabel(this);
        dec->setGeometry(85, 15, 40, 4);
        dec->setStyleSheet("background-color: #00A6A7; border-radius: 10px; border: 1px solid #00A6A7;");

        QLabel *contenedor = new QLabel(this);
        contenedor->setGeometry(0, 19, 210, 64);
        contenedor->setStyleSheet("border-radius: 10px; border: 2px solid #00A6A7;");

        QLabel *t1Label = new QLabel("N1", this);
        t1Label->setGeometry(2 + 5, 19 + 2, 68 - 10, 11);
        t1Label->setStyleSheet("color: #656565; font-size: 10px;");
        t1Label->setAlignment(Qt::AlignHCenter);

        t1 = new QLabel("", this);
        t1->setGeometry(2 + 4, 19 + 2 + 11, 68 - 4, 17);
        t1->setStyleSheet("color: white; font-size: 16px;");
        t1->setAlignment(Qt::AlignHCenter);

        QLabel *t2Label = new QLabel("N2", this);
        t2Label->setGeometry(2 + 5 + 68, 19 + 2, 68 - 10, 11);
        t2Label->setStyleSheet("color: #656565; font-size: 10px;");
        t2Label->setAlignment(Qt::AlignHCenter);

        t2 = new QLabel("", this);
        t2->setGeometry(2 + 4 + 68, 19 + 2 + 11, 68 - 4, 17);
        t2->setStyleSheet("color: white; font-size: 16px;");
        t2->setAlignment(Qt::AlignHCenter);

        QLabel *t3Label = new QLabel("N3", this);
        t3Label->setGeometry(2 + 5 + 68 * 2, 19 + 2, 68 - 10, 11);
        t3Label->setStyleSheet("color: #656565; font-size: 10px;");
        t3Label->setAlignment(Qt::AlignHCenter);

        t3 = new QLabel("", this);
        t3->setGeometry(2 + 4 + 68 * 2, 19 + 2 + 11, 68 - 4, 17);
        t3->setStyleSheet("color: white; font-size: 16px;");
        t3->setAlignment(Qt::AlignHCenter);

        QLabel *t4Label = new QLabel("N4", this);
        t4Label->setGeometry(2 + 5, 19 + 2 + 29, 68 - 10, 11);
        t4Label->setStyleSheet("color: #656565; font-size: 10px;");
        t4Label->setAlignment(Qt::AlignHCenter);

        t4 = new QLabel("", this);
        t4->setGeometry(2 + 4, 19 + 2 + 11 + 29, 68 - 4, 17);
        t4->setStyleSheet("color: white; font-size: 16px;");
        t4->setAlignment(Qt::AlignHCenter);

        QLabel *t5Label = new QLabel("N5", this);
        t5Label->setGeometry(2 + 5 + 68, 19 + 2 + 29, 68 - 10, 11);
        t5Label->setStyleSheet("color: #656565; font-size: 10px;");
        t5Label->setAlignment(Qt::AlignHCenter);

        t5 = new QLabel("", this);
        t5->setGeometry(2 + 4 + 68, 19 + 2 + 11 + 29, 68 - 4, 17);
        t5->setStyleSheet("color: white; font-size: 16px;");
        t5->setAlignment(Qt::AlignHCenter);

        QLabel *t6Label = new QLabel("N6", this);
        t6Label->setGeometry(2 + 5 + 68 * 2, 19 + 2 + 29, 68 - 10, 11);
        t6Label->setStyleSheet("color: #656565; font-size: 10px;");
        t6Label->setAlignment(Qt::AlignHCenter);

        t6 = new QLabel("", this);
        t6->setGeometry(2 + 4 + 68 * 2, 19 + 2 + 11 + 29, 68 - 4, 17);
        t6->setStyleSheet("color: white; font-size: 16px;");
        t6->setAlignment(Qt::AlignHCenter);
    }

    void updateT1(int temp) {
        t1->setText(QString::number(temp) + "° C");
    }

    void updateT2(int temp) {
        t2->setText(QString::number(temp) + "° C");
    }

    void updateT3(int temp) {
        t3->setText(QString::number(temp) + "° C");
    }

    void updateT4(int temp) {
        t4->setText(QString::number(temp) + "° C");
    }

    void updateT5(int temp) {
        t5->setText(QString::number(temp) + "° C");
    }

    void updateT6(int temp) {
        t6->setText(QString::number(temp) + "° C");
    }
};

// Widget auxiliar para representar cada item de la lista de voltajes de celdas
// Contiene el número de fila junto a los 3 voltajes posibles
class CellListItem: public QWidget {
public:
    QLabel* v1;
    QLabel* v2;
    QLabel* v3;

    CellListItem(QWidget *parent, int rowVal): QWidget(parent) {
        this->setStyleSheet("border-bottom: 2px solid #00A6A7; color: white;");
        this->setGeometry(rowVal % 3 * (195 + 25) + 20, rowVal / 3 * (20 + 10), 195, 20);

        QLabel* row = new QLabel(QString::number(rowVal + 1), this);
        row->setGeometry(0, 0, 28, 20);
        row->setStyleSheet("color: #00A6A7;");
        row->setAlignment(Qt::AlignHCenter);

        QLabel* sep = new QLabel("", this);
        sep->setGeometry(28, 0, 2, 20);
        sep->setStyleSheet("background-color: #00A6A7;");

        this->v1 = new QLabel(this);
        this->v1->setGeometry(30, 0, 55, 20);
        this->v1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        this->v2 = new QLabel(this);
        this->v2->setGeometry(85, 0, 55, 20);
        this->v2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        this->v3 = new QLabel(this);
        this->v3->setGeometry(140, 0, 55, 20);
        this->v3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    void setVoltage1(int voltage) {
        this->v1->setText(QString::number(voltage) + " V");
    }

    void setVoltage2(int voltage) {
        this->v2->setText(QString::number(voltage) + " V");
    }

    void setVoltage3(int voltage) {
        this->v3->setText(QString::number(voltage) + " V");
    }

};


namespace Ui {
class BatteryPanel;
}

// Clase que maneja la ui del panel de la batería, en la pantalla de configuración
class BatteryPanel : public QWidget
{
    Q_OBJECT

public:
    CANData *canData;
    CellListItem* items[194];
    TempListItem* tempItems[18];
    explicit BatteryPanel(CANData *canData, QWidget *parent = nullptr);
    ~BatteryPanel();

    void changeCurrentTab(int index);

public:
    void assertMessage1();
    void assertMessage3();
    void assertBess1(int trama, int v1, int v2, int v3);
    void assertBess2(int trama, int t1, int t2, int t3, int t4, int t5, int t6);
    void assertBess3(int chargeEnergyAcumulated, int dischargeEnergyAcumulated, int energyOneCharge);
    void assertBess4();

public slots:
    void message1();
    void message3();
    void message7();
    void bess1(int trama);
    void bess2(int trama);
    void bess3();
    void bess4();

private slots:
    void on_generalInfo_clicked();

    void on_voltageInfo_clicked();

    void on_tempInfo_clicked();

private:
    Ui::BatteryPanel *ui;
};

#endif // BATTERYPANEL_H
