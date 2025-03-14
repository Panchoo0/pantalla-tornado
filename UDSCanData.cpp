#include "UDSCanData.h"
// #include <src/kernel-headers/include/linux/can.h>
// #include <src/kernel-headers/include/linux/can/j1939.h>
// #include <src/kernel-headers/include/linux/can/raw.h>
#include <utils.h>
#include <sys/ioctl.h>

UDSCanData::UDSCanData(QObject *parent) : QThread(parent)
{
}

void UDSCanData::run() {
    // int sock;
    // struct sockaddr_can di5Address;
    // socklen_t len = sizeof(di5Address);
    // struct ifreq ifr;

    // if ((sock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    // {
    //     qCritical() << "Error creating socket error " << errno << " which means " << strerror(errno);
    //     return;
    // }

    // strcpy(ifr.ifr_name, "can0");
    // ioctl(sock, SIOCGIFINDEX, &ifr);

    // di5Address.can_family = AF_CAN;
    // di5Address.can_ifindex = ifr.ifr_ifindex;
    // di5Address.can_addr.tp.rx_id = 0x18DAFA01 | CAN_EFF_FLAG;
    // di5Address.can_addr.tp.tx_id = 0x18DA01FA | CAN_EFF_FLAG;

    // // Estructura para recibir los datos
    // struct can_frame rcv_frame;
    // rcv_frame.can_id = 0x18DA01FA | CAN_EFF_FLAG;

    // // Filtro para la id específica
    // // Sin este se reciben todos los mensajes CAN
    // struct can_filter rfilter[1];
    // rfilter[0].can_id = 0x18DAFA01;
    // rfilter[0].can_mask = CAN_EFF_MASK;
    // setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

    // //Binds the socket to the address
    // if (bind(sock, (struct sockaddr *)&di5Address, sizeof(di5Address)) < 0)
    // {
    //     qCritical() << "Error binding socket error " << errno << " which means " << strerror(errno);
    //     close(sock);
    //     return;
    // }

    // // Estructura para enviar la petición
    // struct can_frame send_frame;
    // send_frame.can_id = 0x18DA01FA | CAN_EFF_FLAG;
    // send_frame.can_dlc = 8;
    // send_frame.data[0] = 0x3;
    // send_frame.data[1] = 0x22;

    // int dids[] = {
        // 0xA011, 0xA012, 0xA016, 0xA018, 0xA019, 0xA01E, 0xA01F,
        // 0xA020, 0xA023, 0xA028, 0xA02A, 0xA03E, 0xA040, 0xA042,
        // 0xA044, 0xA049, 0xA05A, 0xA05B, 0xA0C0, 0xA0C1, 0xA0CD,
        // 0xA0CE, 0xA0CF, 0xA0D0, 0xA0D1, 0xA0D2, 0xA0D3, 0xA0D4,
        // 0xA0D6, 0xA0E4, 0xA0E7, 0xA0EB, 0xA0EE, 0xA0EF, 0xA0F0,
        // 0xA0F1, 0xA0F2, 0xA0F3, 0xA0F4
    // };
    // int didsLen = 19;

    // // timeout para la espera de la info solicitada
    // struct timeval tv;
    // tv.tv_sec = 1;
    // tv.tv_usec = 0;
    // setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    // while (true) {
    //     // Se envía una petición para cada did y luego hay una pausa de x ms
    //     for (int didIndex = 0; didIndex < didsLen; didIndex++) {
    //         // Escogemos la did
    //         int did = dids[didIndex];
    //         send_frame.data[2] = did >> 8;
    //         send_frame.data[3] = did & 0xFF;

    //         // Se envía la petición
    //         qInfo() << "Asking for:" << Utils::toHexString(send_frame.data, 4);
    //         int nbytes = send(sock, &send_frame, sizeof(struct can_frame), 0);
    //         if (nbytes < 0)
    //         {
    //             qInfo() << "Error sending socket error " << errno << " which means " << strerror(errno);
    //             emit dbgMessage("Error al enviar datos");
    //         } else {
    //             qInfo() << "Mensaje correctamente enviado";
    //         }

    //         // Se espera la respuesta
    //         int res = recvfrom(sock, &rcv_frame, sizeof(struct can_frame),
    //                               0, (struct sockaddr*)&di5Address, &len);
    //         if (res < 0) {
    //             qInfo() << "Error al leer datos" << errno << strerror(errno);
    //             emit dbgMessage("Error al leer datos" + QString::number(errno) + QString::fromStdString(strerror(errno)));
    //         } else {
    //             qInfo() << "id (hex)" << Utils::toHexString(rcv_frame.can_id);
    //             emit dbgMessage("Mensaje UDS Recibido. Data: " + Utils::toHexString(rcv_frame.data, 8));
    //             emit udsMessage(rcv_frame.data);
    //         }

    //         break;
    //     }

    //     QThread::msleep(2000);
    // }
}

