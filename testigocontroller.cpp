#include "testigocontroller.h"
#include <QDebug>

// Widget que maneja el área de testigos
TestigoController::TestigoController(QWidget* parent): QWidget(parent) {
    testigosTimer = new QTimer(this);
    connect(testigosTimer, SIGNAL(timeout()), this, SLOT(animateTestigos()));
    testigosTimer->start(500);

    // this->addTestigo(TESTIGOS::DCDCD, TestigoState::ON);
    // this->addTestigo(TESTIGOS::SIM100, TestigoState::FLASH);
    // this->addTestigo(TESTIGOS::HVIL, TestigoState::ON);
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
void TestigoController::addTestigo(TESTIGOS testigo, TestigoState state) {
    QPixmap pixmap;
    switch (testigo) {
    case TESTIGOS::DCDCD:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/dcdciconalert.png");
        break;
    case TESTIGOS::SIM100:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/sim100alert.png");
        break;
    case TESTIGOS::HVIL:
        pixmap = QPixmap(":/panelConfiguracion/images/panelConfiguracion/hvilalert.png");
        break;
    default:
        break;
    }

    QLabel* label = new QLabel(this);
    label->setPixmap(pixmap);
    label->setGeometry(this->testigos.size() * 30, 5, 30, 30);

    Testigo testigoItem;
    testigoItem.image = label;
    testigoItem.state = state;

    this->testigos.push_back(testigoItem);
}
