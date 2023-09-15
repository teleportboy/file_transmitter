#include "PacketReceiver.h"
#include "types.h"

#include <QUdpSocket>
#include <QDataStream>

PacketReceiver::PacketReceiver(int port, QObject *parent)
    : QObject{parent}
{
    connect(&socket, &QUdpSocket::readyRead, this, &PacketReceiver::startReceive);
    socket.bind(QHostAddress::Any, port);
}

void PacketReceiver::startReceive() {
    while (socket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket.pendingDatagramSize());

        QHostAddress senderAddress;
        socket.readDatagram(datagram.data(), datagram.size(), &senderAddress);

        PacketData packet;
        QDataStream stream(&datagram, QIODevice::ReadOnly);

        //переделать
        stream >> packet.packetId;
        stream >> packet.packetType;
        stream >> packet.packetsCount;
        stream >> packet.fileName;
        stream >> packet.data;

        switch (packet.packetType) {
            case PacketType::SendFilePacket:
                emit addPacketToFile(packet);
                emit approvePacket(senderAddress.toString(), 2417, packet);
                break;

            case PacketType::ApproveFilePacket:
                emit packetReceived(packet.packetId);
                break;
        }
    }
}
