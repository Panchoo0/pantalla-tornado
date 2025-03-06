#ifndef TESTIGOCONTROLLER_H
#define TESTIGOCONTROLLER_H

#include <QLabel>
#include <QTimer>

enum TestigoState {
    ON,
    FLASH
};

struct Testigo {
    QLabel* image;
    TestigoState state;
};

enum TESTIGOS {
    DCDCD,
    SIM100,
    HVIL
};


class TestigoController: public QWidget
{
    Q_OBJECT
public:
    std::vector<Testigo> testigos;
    QTimer *testigosTimer;

    TestigoController(QWidget* parent = nullptr);

    void addTestigo(TESTIGOS testigo, TestigoState state);

private slots:
    void animateTestigos();
};

#endif // TESTIGOCONTROLLER_H
