#include "receivecandata.h"
// Comentar estos include para ver desarrollo local
#include <src/kernel-headers/include/linux/can.h>
#include <src/kernel-headers/include/linux/can/j1939.h>

ReceiveCANData::ReceiveCANData(QObject *parent): QThread(parent) {
}

void ReceiveCANData::run()
{
    // Comentar el cuerpo de esta función para ver desarrollo local

    qInfo() << "(J1939) Comenzado a recibir datos";
    //sockaddr structure of CAN J1939 for DI5
    struct sockaddr_can di5Address;
    di5Address.can_family = AF_CAN;
    di5Address.can_ifindex = if_nametoindex("can0"); //Enter the CAN channel on which data will be received
    di5Address.can_addr.j1939.addr = 0xE1;           //Enter the address of DI5 here
    di5Address.can_addr.j1939.pgn = J1939_NO_PGN;
    di5Address.can_addr.j1939.name = J1939_NO_NAME;

    // sockaddr structure of CAN J1939 for
    struct sockaddr_can rc40Address;
    socklen_t rc40AddressLength = sizeof(rc40Address);
    rc40Address.can_family = AF_CAN;
    rc40Address.can_ifindex = if_nametoindex("can0"); //Enter the CAN channel on which data will be received
    rc40Address.can_addr.j1939.addr = 0x00;           //Enter the address of RC40 here

    //Mention the length of Data to be received in bytes
    uint8_t receivedData[128];

    //Create a socket
    //On success, a file descriptor for the new socket is returned.
    //On error, -1 is returned, and errno is set to indicate the error.
    if ((sock = socket(AF_CAN, SOCK_DGRAM, CAN_J1939)) < 0)
    {
        qInfo() << "(J1939) Error al crear socket";
        emit debugMessage("Error al crear socket");
        qCritical() << "Error creating socket error " << errno << " which means " << strerror(errno);
        return;
    }

    //To enable sending broadcast packets
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &receivedData, sizeof(receivedData));

    //Binds the socket to the address
    if (bind(sock, (struct sockaddr *)&di5Address, sizeof(di5Address)) < 0)
    {
        qInfo() << "(J1939) Error al bindear socket";
        qCritical() << "(J1939) Error binding socket error" << errno << "which means" << strerror(errno);
        close(sock);
        return;
    }

    while (true)
    {
        //Receives messages from socket
        //Returns the number of bytes received, or -1 if an error occurred.
        int nbytes = recvfrom(sock, receivedData, sizeof(receivedData), 0, (sockaddr*)&rc40Address, &rc40AddressLength);
        if (nbytes < 0)
        {
            qInfo() << "(J1939) Error al recibir datos";
            qCritical() << "(J1939) Error reading socket error" << errno << "which means" << strerror(errno);
            close(sock);
            return;
        }

        //Emit the message
        emit messageReceived(rc40Address.can_addr.j1939.addr, rc40Address.can_addr.j1939.pgn, receivedData);
    }
}


void ReceiveCANData::closeSocket()
{
    close(sock);
}
