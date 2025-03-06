#include "sendcandata.h"
// #include <src/kernel-headers/include/linux/can.h>
// #include <src/kernel-headers/include/linux/can/j1939.h>

SendCANData::SendCANData(QObject *parent) : QObject(parent)
{
    // //sockaddr structure of CAN J1939 for DI5
    // struct sockaddr_can di5Address;
    // di5Address.can_family = AF_CAN;
    // di5Address.can_ifindex = if_nametoindex("can0");    //Enter the CAN channel on which data will be sent
    // di5Address.can_addr.j1939.addr = 0xE1;              //Enter the address of DI5 here
    // di5Address.can_addr.j1939.pgn = J1939_NO_PGN;
    // di5Address.can_addr.j1939.name = J1939_NO_NAME;


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
}

//This method is called when sendData->start() is executed in mainwindow.cpp
void SendCANData::sendMessage(uint8_t* data, int length)
{
    // //sockaddr structure of CAN J1939 for RC40
    // struct sockaddr_can rc40Address;
    // rc40Address.can_family = AF_CAN;
    // rc40Address.can_ifindex = if_nametoindex("can0");   //Enter the CAN channel on which data will be sent
    // rc40Address.can_addr.j1939.addr = 0x02;             //Enter the address of RC40 here
    // rc40Address.can_addr.j1939.pgn = 0xDA02;           //Enter the PGN
    // rc40Address.can_addr.j1939.name = J1939_NO_NAME;

    // //Create a socket
    // //On success, a file descriptor for the new socket is returned.
    // //On error, -1 is returned, and errno is set to indicate the error.

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
}

// Funciones que piden por el protocolo UDS la información de los errores de los equipos
// La respuesta se recibe en el otro thread, contenido en el archivo receivecandata.cpp

void SendCANData::sendEDS() {
    uint8_t data[] = {3, 0x22, 0xA0, 0xEB, 0, 0, 0, 0};
    this->sendMessage(data, 8);
}

void SendCANData::sendSIM100() {
    uint8_t data[] = {3, 0x22, 0xA0, 0xEE, 0, 0, 0, 0};
    this->sendMessage(data, 8);
}

void SendCANData::sendFaultBess() {
    uint8_t data[] = {3, 0x22, 0xA0, 0xEF, 0, 0, 0, 0};
    this->sendMessage(data, 8);
}

void SendCANData::sendFaultDcdc1() {
    uint8_t data[] = {3, 0x22, 0xA0, 0xF0, 0, 0, 0, 0};
    this->sendMessage(data, 8);
}

void SendCANData::sendFaultDcdc2() {
    uint8_t data[] = {3, 0x22, 0xA0, 0xF1, 0, 0, 0, 0};
    this->sendMessage(data, 8);
}

void SendCANData::sendFaultObc() {
    uint8_t data[] = {3, 0x22, 0xA0, 0xF2, 0, 0, 0, 0};
    this->sendMessage(data, 8);
}

void SendCANData::sendFaultEmix() {
    uint8_t data[] = {3, 0x22, 0xA0, 0xF3, 0, 0, 0, 0};
    this->sendMessage(data, 8);
}


void SendCANData::sendChargeStatusBMS() {
    uint8_t data[] = {3, 0x22, 0xA0, 0x53, 0, 0, 0, 0};
    this->sendMessage(data, 8);
}
