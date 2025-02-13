#include "checkboxwidget.h"
#include <QMainWindow>

// Recibe el ancho del checkbox junto al componente padre
CheckboxWidget::CheckboxWidget(QWidget* parent, int width): QPushButton(parent) {
    this->checked = false;

    this->setGeometry(0, 0, width, width);
    this->setStyleSheet("border: 2px solid #00A6A7; background-color: #363636; border-radius: 5px;");

    // Se crea el fondo que se muestra cuando está seleccionado
    this->Check = new QWidget(this);
    this->Check->setGeometry(4, 4, width - 8, width - 8);
    this->Check->setStyleSheet("background-color: #00A6A7; border-radius: 2px;");
    this->Check->hide();

    connect(this, &CheckboxWidget::clicked, this, &CheckboxWidget::onChange);
}

void CheckboxWidget::onChange() {
    this->checked = !this->checked;
    this->Check->setVisible(this->checked);
}

// CheckboxWidget::~CheckboxWidget() {

// }
