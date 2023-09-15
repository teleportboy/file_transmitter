#include "Packet.h"
#include <QDebug>

Packet::Packet(QObject* parent) : QObject(parent) {
    isSent = false;
}

void Packet::trySendPacket() {
    QUdpSocket socket;

    if (!isSent) {
        QByteArray dataToSend;
        QDataStream stream(&dataToSend, QIODevice::WriteOnly);
        //что то более общее надо
        stream << packet.packetId;
        stream << packet.packetType;
        stream << packet.packetsCount;
        stream << packet.fileName;
        stream << packet.data;

        socket.writeDatagram(dataToSend, *address, port);
        return;
    }

    stopPacketSending();
}

void Packet::packetSent() {
    isSent = true;
}

void Packet::stopPacketSending() {
    timer->stop();
    disconnect(timer, nullptr, nullptr, nullptr);
    deleteLater();
}

void Packet::startPacketSending() {
    connect(timer, &QTimer::timeout, this, &Packet::trySendPacket);
    timer->start(msDelayResent);
}

Packet::~Packet() {
    //delete timer;
    delete address;
}

PacketBuilder::PacketBuilder(QObject* parent) {
    packet = new Packet(parent);
}

PacketBuilder& PacketBuilder::setData(QByteArray data) {
    packet->packet.data = data;
    return *this;
}

PacketBuilder& PacketBuilder::setAddress(QString address) {
    packet->address = new QHostAddress(address);
    return *this;
}

PacketBuilder& PacketBuilder::setPort(quint16 port) {
    packet->port = port;
    return *this;
}

PacketBuilder& PacketBuilder::setPacketId(int id) {
    packet->packet.packetId = id;
    return *this;
}

PacketBuilder& PacketBuilder::setPaketType(PacketType type) {
    packet->packet.packetType = type;
    return *this;
}

PacketBuilder& PacketBuilder::setMsDelayResent(int msDelay) {
    packet->msDelayResent = msDelay;
    packet->timer = new QTimer(packet);
    return *this;
}

PacketBuilder& PacketBuilder::setTotalPackets(int totalPackets) {
    packet->packet.packetsCount = totalPackets;
    return *this;
}

PacketBuilder& PacketBuilder::setFileName(QString fileName) {
    packet->packet.fileName = fileName;
    return *this;
}

Packet* PacketBuilder::buildPacket() {
    return packet;
}
