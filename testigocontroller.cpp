#include "testigocontroller.h"
#include <QDebug>
#include <algorithm>

// Widget que maneja el área de testigos
TestigoController::TestigoController(QWidget* parent): QWidget(parent) {
    testigosTimer = new QTimer(this);
    connect(testigosTimer, SIGNAL(timeout()), this, SLOT(animateTestigos()));
    testigosTimer->start(500);

    this->addTestigo(TESTIGOS::ESTOP);
    this->addTestigo(TESTIGOS::SIM100);
    this->addTestigo(TESTIGOS::ATS);
}

// Función que crea la animación de los testigos parpadeantes
void TestigoController::animateTestigos() {
    for (int i = 0; i < this->testigos.size(); i++) {
        if (this->testigos[i].state == TestigoState::FLASH) {
            if (this->testigos[i].image->isVisible()) {
                this->testigos[i].image->hide();
            } else {
                this->testigos[i].image->show();
            }
        }
    }
}

// Dado un tipo de testigo y su estado lo agrega al sector de testigos
void TestigoController::addTestigo(TESTIGOS testigo) {
    QPixmap pixmap;

    // Si el testigo ya se encuentra encendido no se hace nada
    for (TestigoUI t : this->testigos) {
        if (t.testigo == testigo) return;
    }

    switch (testigo) {
    case TESTIGOS::OFF:
        return;
    case TESTIGOS::DCDC:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/dcdcalert.png");
        break;
    case TESTIGOS::SIM100:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/sim100alert.png");
        break;
    case TESTIGOS::EDS:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/edsalert.png");
        break;
    case TESTIGOS::BESS:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/bessalert.png");
        break;
    case TESTIGOS::BTMS:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/btmsalert.png");
        break;
    case TESTIGOS::TEMP:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/tempalert.png");
        break;
    case TESTIGOS::HVIL:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/hvilalert.png");
        break;
    case TESTIGOS::SENSOR:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/sensoralert.png");
        break;
    case TESTIGOS::HOOD_OPEN:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/hoodalert.png");
        break;
    case TESTIGOS::ESTOP:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/estopalert.png");
        break;
    case TESTIGOS::BATT_LV:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/batlvsalert.png");
        break;
    case TESTIGOS::ATS:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/bathvalert.png");
        break;
    case TESTIGOS::FIRE:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/firealert.png");
        break;
    case TESTIGOS::BATT_HV:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/batthvalert.png");
        break;
    case TESTIGOS::CONTACTOR:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/contactoralert.png");
        break;
    default:
        break;
    }

    QLabel* label = new QLabel(this);
    label->setPixmap(pixmap);
    label->setGeometry(this->testigos.size() * 30, 5, 30, 30);

    TestigoUI testigoItem;
    testigoItem.image = label;
    testigoItem.testigo = testigo;
    testigoItem.state = TestigoState::FLASH;

    this->testigos.push_back(testigoItem);
}
