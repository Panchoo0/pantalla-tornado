#ifndef CHECKBOXWIDGET_H
#define CHECKBOXWIDGET_H

#include <QPushButton>

// Clase que simula un botón de checkbox
class CheckboxWidget: public QPushButton
{
    // Q_OBJECT

public:
    bool checked;
    CheckboxWidget( QWidget* parent = nullptr, int width = 20);
    /*~CheckboxWidget()*/;
public slots:
    void setChecked(bool checked);
private:
    QWidget* Check;
};

#endif // CHECKBOXWIDGET_H
