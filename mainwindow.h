#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <candata.h>
#include <adminpanel.h>
#include <notificationswidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer* datetimeTimer;
    CANData *data;

    QPixmap lowTempIcon;
    QPixmap regularTempIcon;
    QPixmap highTempIcon;

    QPixmap lowBatIcon;
    QPixmap regularBatIcon;
    QPixmap highBatIcon;

    bool isAdminPanelOpen;
    AdminPanel *adminPanel;
    NotificationsWidget *notificationsWidget;


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
private slots:
    void updateDateTime();
    void updateSpeed(int value);
    void updateEngineTemp(int value);
    void updateInversorTemp(int value);
    void updateBatTemp(int value);
    void updateBat(int value);
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_verticalSlider_valueChanged(int value);
    void on_pushButton_clicked();
    void on_confButton_clicked();
};
#endif // MAINWINDOW_H
