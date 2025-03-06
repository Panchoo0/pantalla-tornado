#ifndef CHECKBOXWIDGET_H
#define CHECKBOXWIDGET_H

#include <QPushButton>

// Clase que simula un botón de checkbox
class CheckboxWidget: public QPushButton
{
public:
    bool checked;
    CheckboxWidget( QWidget* parent = nullptr, int width = 20);
    /*~CheckboxWidget()*/;
    void connectClick();

public slots:
    void setChecked(bool checked);
    void onClick();

private:
    QWidget* Check;
};

#endif // CHECKBOXWIDGET_H
