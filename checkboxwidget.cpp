#include "checkboxwidget.h"
#include <QMainWindow>

// Widget para simular un checkbox
// Recibe el ancho del checkbox junto al componente padre
CheckboxWidget::CheckboxWidget(QWidget* parent, int width): QPushButton(parent) {
    this->checked = false;

    this->setGeometry(0, 0, width, width);
    this->setStyleSheet("border: 2px solid #00A6A7; background-color: #2c2c2c; border-radius: 4px;");

    // Se crea el fondo que se muestra cuando está seleccionado
    this->Check = new QWidget(this);
    this->Check->setGeometry(5, 5, width - 10, width - 10);
    this->Check->setStyleSheet("background-color: #00A6A7; border-radius: 3px;");
    this->Check->hide();

    // connect(this, &CheckboxWidget::clicked, this, &CheckboxWidget::onChange);
}

void CheckboxWidget::setChecked(bool checked) {
    this->checked = checked;
    this->Check->setVisible(this->checked);
}
