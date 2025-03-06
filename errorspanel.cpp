#include "errorspanel.h"
#include "ui_errorspanel.h"
#include <QDebug>
#include <QScrollBar>
#include <QScroller>

// Widget utilizado para mostrar los errores DTC en el panel de información avanzada
ErrorsPanel::ErrorsPanel(CANData *canData, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ErrorsPanel)
{
    ui->setupUi(this);

    this->canData = canData;

    // Configuración para permiter el scroll al arrastrar
    QScroller::grabGesture(ui->scrollAreaWidgetContents, QScroller::LeftMouseButtonGesture);

    // Creamos cada item de los errores almacenados en memoria
    for (unsigned long int i = 0; i < this->canData->allErrors.size(); i++) {
        this->addError(i);
    }

    // Marcamos como clickeada la checkbox y luego conectamos el click
    // con el cambio de estado de la checkbox y con la función que se encarga de
    // filtrar y ordenera las filas de la tabla.
    ui->dcdc1Checkbox->setChecked(true);
    ui->dcdc1Checkbox->connectClick();
    connect(ui->dcdc1Checkbox, &CheckboxWidget::clicked, this, &ErrorsPanel::onDcdc1Check);

    // Llamamos a la función on_dateSorterButton_clicked para que las filas queden ordenadas por las más recientes
    this->on_dateSorterButton_clicked();
}

// Función que se encarga de actualizar las posiciones de las filas de la tabla
// Oculta aquellas filas que se encuentren filtradas según el equipo
void ErrorsPanel::sort() {
    // Posición actual de la siguiente fila a mostrar
    int count = 0;
    for (int i = 0; i < this->items.size(); i++) {
        if (this->items[i]->error->equipment == "DCDC1" && !this->showDcdc1) {
            // Si no se encuentra marcado el DCDC1 entonces se 'ocultan' estas filas
            this->items[i]->updatePosition(-20);

        } else {
            // En caso contrario ese actualiza la posición del elemento UI de la fila, asignadole su fila
            this->items[i]->updatePosition(count);
            count++;
        }
    }

    // Actualizamos el alto de la tabla
    ui->scrollAreaWidgetContents->setMinimumHeight(ErrorListItem::height * count);

}

// Dada una fila se agrega a la tabla el error correspondiente
void ErrorsPanel::addError(int row) {
    // Se crea el elemento UI
    ErrorListItem* item = new ErrorListItem(ui->scrollAreaWidgetContents, row, &this->canData->allErrors[row]);
    // Se actualiza el alto de la tabla
    ui->scrollAreaWidgetContents->setMinimumHeight(ErrorListItem::height * (row + 1));
    this->items.push_back(item);
}

// Slot que recibe la señal al recibir por el bus CAN otro error
void ErrorsPanel::canError() {
    this->addError(this->canData->allErrors.size() - 1);
}

ErrorsPanel::~ErrorsPanel()
{
    delete ui;
}

// Slot que se ejecuta al hacer click sobre el header de fecha en la tabla
// Se reordenan las filas según los 3 posibles ordenes (ASC, DESC, NONE)
void ErrorsPanel::on_dateSorterButton_clicked()
{
    this->dateSorterMode = static_cast<SORTER_MODE> ((this->dateSorterMode + 1) % 3);

    switch (this->dateSorterMode) {
    case SORTER_MODE::NONE:
        struct {
            bool operator()(const ErrorListItem* a, const ErrorListItem* b) const { return a->originalRow < b->originalRow; }
        } ogPosition;

        std::sort(&this->items.front(), &this->items.back(), ogPosition);
        ui->dateSorter->setVisible(false);
        break;
    case SORTER_MODE::ASC:
        struct {
            bool operator()(const ErrorListItem* a, const ErrorListItem* b) const {

                return a->error->date < b->error->date; }
        } ascComparer;

        std::sort(this->items.begin(), this->items.end(), ascComparer);
        ui->dateSorter->setPixmap(QPixmap(":/panelConfiguracion/images/panelConfiguracion/AscIcon.png"));
        ui->dateSorter->show();
        break;
    case SORTER_MODE::DESC:
        struct {
            bool operator()(const ErrorListItem* a, const ErrorListItem* b) const {
                return a->error->date > b->error->date; }
        } descComparer;

        std::sort(this->items.begin(), this->items.end(), descComparer);
        ui->dateSorter->setPixmap(QPixmap(":/panelConfiguracion/images/panelConfiguracion/DescIcon.png"));
        ui->dateSorter->show();
        break;
    default:
        break;
    }

    this->sort();
}

// Slot que recibe la señal de click sobre la checkbox para el filtro del equipo DCDC1
void ErrorsPanel::onDcdc1Check() {
    this->showDcdc1 = !this->showDcdc1;
    this->sort();
}

