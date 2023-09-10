#include "PacketReceiver.h"
#include "types.h"

#include <QUdpSocket>
#include <QDataStream>

PacketReceiver::PacketReceiver(QObject *parent)
    : QObject{parent}
{
    connect(&socket, &QUdpSocket::readyRead, this, &PacketReceiver::startReceive);
    socket.bind(QHostAddress::Any, 2417);
}


void PacketReceiver::startReceive() {
    while (socket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket.pendingDatagramSize());

        socket.readDatagram(datagram.data(), datagram.size());

        PacketData packet;
        QDataStream stream(&datagram, QIODevice::ReadOnly);

        stream >> packet.packetId;
        stream >> packet.data;

        qDebug() << packet.packetId;
    }
}
