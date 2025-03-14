#ifndef TESTIGOCONTROLLER_H
#define TESTIGOCONTROLLER_H

#include <QLabel>
#include <QTimer>

enum TestigoState {
    ON,
    FLASH
};

enum TESTIGOS {
    OFF,
    DCDC,
    SIM100,
    EDS,
    BESS,
    BTMS,
    TEMP,
    HVIL,
    SENSOR,
    HOOD_OPEN,
    ESTOP,
    BATT_LV,
    ATS,
    FIRE,
    BATT_HV,
    CONTACTOR
};

struct TestigoUI {
    QLabel* image;
    TestigoState state;
    TESTIGOS testigo;
};


class TestigoController: public QWidget
{
    Q_OBJECT
public:
    std::vector<TestigoUI> testigos;
    QTimer *testigosTimer;

    TestigoController(QWidget* parent = nullptr);

public slots:
    void animateTestigos();
    void addTestigo(TESTIGOS testigo);
};

#endif // TESTIGOCONTROLLER_H
