#ifndef UDSCANDATA_H
#define UDSCANDATA_H

#include <QObject>
#include <QThread>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <net/if.h>
#include <unistd.h>
#include <QDebug>
#include <stdint.h>


class UDSCanData : public QThread
{
    Q_OBJECT

public:
    UDSCanData(QObject *parent = nullptr);

protected:
    void run() override;
signals:
    void udsMessage(uint8_t *data);
    void dbgMessage(QString msg);
};

#endif // UDSCANDATA_H

