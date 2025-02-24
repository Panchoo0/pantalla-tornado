#ifndef RECEIVECANDATA_H
#define RECEIVECANDATA_H

#include <QObject>
#include <QThread>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <net/if.h>
#include <unistd.h>
#include <QDebug>
#include <stdint.h>



class ReceiveCANData: public QThread
{
    Q_OBJECT

public:
    ReceiveCANData(QObject *parent = nullptr);
signals:
    //Signal to emit the received message to MainWindow
    void messageReceived(unsigned char, unsigned int, uint8_t*);
    void debugMessage(QString msg);
public slots:
    //To close the socket once Exit button in the MainWindow is clicked
    void closeSocket();

protected:
    //run() method of ReceiveData is overridden to add the code for receiving data
    void run() override;

private:
    //File descriptor for a socket
    int sock;
};

#endif // RECEIVECANDATA_H
