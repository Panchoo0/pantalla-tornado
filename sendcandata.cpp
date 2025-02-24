#include "sendcandata.h"

SendCANData::SendCANData(QObject *parent) : QThread(parent)
{

}

//This method is called when sendData->start() is executed in mainwindow.cpp
void SendCANData::run()
{
    // //File descriptor for a socket
    // int sock;

    // //sockaddr structure of CAN J1939 for DI5
    // struct sockaddr_can di5Address;
    // di5Address.can_family = AF_CAN;
    // di5Address.can_ifindex = if_nametoindex("can0");    //Enter the CAN channel on which data will be sent
    // di5Address.can_addr.j1939.addr = 0x01;              //Enter the address of DI5 here
    // di5Address.can_addr.j1939.pgn = J1939_NO_PGN;
    // di5Address.can_addr.j1939.name = J1939_NO_NAME;

    // //sockaddr structure of CAN J1939 for RC40
    // struct sockaddr_can rc40Address;
    // rc40Address.can_family = AF_CAN;
    // rc40Address.can_ifindex = if_nametoindex("can0");   //Enter the CAN channel on which data will be sent
    // rc40Address.can_addr.j1939.addr = 0x03;             //Enter the address of RC40 here
    // rc40Address.can_addr.j1939.pgn = 0x0FF05;           //Enter the PGN
    // rc40Address.can_addr.j1939.name = J1939_NO_NAME;
    // uint8_t data[8] = {dataValue};                      //Enter the length of data in bytes and its value

    // //Create a socket
    // //On success, a file descriptor for the new socket is returned.
    // //On error, -1 is returned, and errno is set to indicate the error.
    // if ((sock = socket(AF_CAN, SOCK_DGRAM, CAN_J1939)) < 0)
    // {
    //     qCritical() << "Error creating socket error " << errno << " which means " << strerror(errno);
    //     return;
    // }

    // //To enable sending broadcast packets
    // setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &data, sizeof(data));

    // //Binds the socket to the address
    // if (bind(sock, (struct sockaddr *)&di5Address, sizeof(di5Address)) < 0)
    // {
    //     qCritical() << "Error binding socket error " << errno << " which means " << strerror(errno);
    //     close(sock);
    //     return;
    // }

    // //Sends the message
    // //On success, returns the number of characters sent
    // //On error, -1 is returned, and errno is set appropriately.
    // int nbytes = sendto(sock, data, sizeof(data), 0, (sockaddr*)&rc40Address, sizeof(rc40Address));

    // qInfo() << "Datos enviados";
    // if (nbytes < 0)
    // {
    //     qCritical() << "Error reading socket error " << errno << " which means " << strerror(errno);
    //     close(sock);
    //     return;
    // }

    // //Close the socket after message is sent
    // close(sock);
}
