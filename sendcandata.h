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


class SendCANData : public QObject
{
    Q_OBJECT

public:
        //File descriptor for a socket
    int sock;
    SendCANData(QObject *parent = nullptr);

    void sendMessage(uint8_t* data, int length);
    void sendEDS();
    void sendSIM100();
    void sendFaultBess();
    void sendFaultDcdc1();
    void sendFaultDcdc2();
    void sendFaultObc();
    void sendFaultEmix();
    void sendChargeStatusBMS();

};

#endif // SENDCANDATA_H

