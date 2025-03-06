QT       += core gui
QT  += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    adminpanel.cpp \
    batterypanel.cpp \
    candata.cpp \
    checkboxwidget.cpp \
    dtccanerror.cpp \
    enginewidget.cpp \
    errorspanel.cpp \
    main.cpp \
    mainwindow.cpp \
    notificationswidget.cpp \
    processvarswidget.cpp \
    receivecandata.cpp \
    sendcandata.cpp \
    testigocontroller.cpp \
    utils.cpp

HEADERS += \
    adminpanel.h \
    batterypanel.h \
    candata.h \
    checkboxwidget.h \
    dtccanerror.h \
    enginewidget.h \
    errorspanel.h \
    mainwindow.h \
    notificationswidget.h \
    processvarswidget.h \
    receivecandata.h \
    sendcandata.h \
    testigocontroller.h \
    utils.h

FORMS += \
    adminpanel.ui \
    batterypanel.ui \
    enginewidget.ui \
    errorspanel.ui \
    mainwindow.ui \
    notificationswidget.ui \
    processvarswidget.ui



#Include the SYSROOT path
INCLUDEPATH += $$[QT_SYSROOT]/usr


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Readme.md
