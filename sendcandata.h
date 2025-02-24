#ifndef SENDCANDATA_H
#define SENDCANDATA_H

#include <QObject>
#include <QThread>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <net/if.h>
#include <unistd.h>
#include <QDebug>
#include <stdint.h>
// #include <src/kernel-headers/include/linux/can.h>
// #include <src/kernel-headers/include/linux/can/j1939.h>

class SendCANData : public QThread
{
    Q_OBJECT

public:
    SendCANData(QObject *parent = nullptr);

    //Data to be sent to RC40
    unsigned char dataValue;

protected:
    //run() method of sendData is overridden to add the code for sending data
    void run() override;
};

#endif // SENDCANDATA_H

