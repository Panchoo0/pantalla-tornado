#ifndef BATTERYPANEL_H
#define BATTERYPANEL_H

#include <QWidget>
#include <QLabel>
#include <candata.h>


// Widget auxiliar para represantar cada item de la lista de temperaturas de celdas
class TempListItem: public QWidget {
public:
    QLabel* t1;

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

        t1 = new QLabel("", this);
        t1->setGeometry(20, 35, 180, 30);
        t1->setStyleSheet("color: white; font-size: 16px;");
        t1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    }

    void updateT1(int temp) {
        t1->setText(QString::number(temp) + "° C");
    }

};

// Widget auxiliar para representar cada item de la lista de voltajes de celdas
// Contiene el número de fila junto a los 3 voltajes posibles
class CellListItem: public QWidget {
public:
    QLabel* v1;

    CellListItem(QWidget *parent, int rowVal): QWidget(parent) {
        this->setStyleSheet("border-bottom: 2px solid #00A6A7; color: white;");
        this->setGeometry((rowVal % 3) * (195 + 25) + 20, rowVal / 3 * (20 + 10), 195, 20);

        QLabel* row = new QLabel(QString::number(rowVal + 1), this);
        row->setGeometry(0, 0, 28, 20);
        row->setStyleSheet("color: #00A6A7;");
        row->setAlignment(Qt::AlignHCenter);

        QLabel* sep = new QLabel("", this);
        sep->setGeometry(28, 0, 2, 20);
        sep->setStyleSheet("background-color: #00A6A7;");

        this->v1 = new QLabel(this);
        this->v1->setGeometry(30, 0, 165, 20);
        this->v1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    void setVoltage1(float voltage) {
        this->v1->setText(QString::number(voltage) + " V");
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
    TempListItem* tempItems[36];
    explicit BatteryPanel(CANData *canData, QWidget *parent = nullptr);
    ~BatteryPanel();

    void changeCurrentTab(int index);

public:
    void assertMessage1();
    void assertMessage3();
    void assertBess1(int trama, float v1, float v2, float v3);
    void assertBess2(int trama, int t1, int t2, int t3, int t4, int t5, int t6);
    void assertBess3(int chargeEnergyAcumulated, int dischargeEnergyAcumulated, float energyOneCharge);
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
