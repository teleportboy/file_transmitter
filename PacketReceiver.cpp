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

        QHostAddress senderAddress;
        socket.readDatagram(datagram.data(), datagram.size(), &senderAddress);

        PacketData packet;
        QDataStream stream(&datagram, QIODevice::ReadOnly);

        //переделать эту парашу а то напрягает каждый раз когда структура пакета расширяется
        stream >> packet.packetId;
        stream >> packet.packetType;
        stream >> packet.packetsCount;
        stream >> packet.fileExtension;
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

        //qDebug() << packet.packetId << packet.packetType << packet.packetsCount << packet.fileExtension;
    }
}
